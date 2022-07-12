import os
# chdir is required before importing torch, since otherwise
# "python scripts_universal/train_rl_model_cuda.py" won't work in install mode
os.chdir(os.path.dirname(os.path.abspath(__file__)))

import argparse
from datetime import datetime, timedelta
from itertools import count
import logging
import random
import re
import sys
from time import time

import torch
from torch.utils.tensorboard import SummaryWriter
import numpy as np

from common.disclaimer import gym_disclaimer

try:
    import gym
except ModuleNotFoundError:
    print(gym_disclaimer)
    sys.exit(0)

from common.rl_models import model_name_to_model, model_transforms, ReplayMemory
from common.rl_utils import get_screen, select_action, optimize_model


def main():
    os.makedirs('data/train_rl_model_cuda', exist_ok=True)
    logging.basicConfig(
        level=logging.DEBUG,
        filename=f'data/train_rl_model_cuda/log_{datetime.now().strftime("%Y_%m_%d_%H_%M_%S")}.log',
        filemode='a+',
        format='%(asctime)-15s %(levelname)-8s %(message)s'
    )
    logging.info(f'Running {" ".join(sys.argv)}')
    # Output logs to file and to stderr
    logging.getLogger().addHandler(logging.StreamHandler())

    parser = argparse.ArgumentParser(
        description=(
            'Trains a reinforcement learning model with dtype=torch.float32 '
            'using CUDA, writes the snapshots and the results into the '
            'data/train_rl_model_cuda/ folder. Resumes the training from the last '
            'epoch if the training was started and interrupted before. NOTE: '
            'this script is always randomized since deterministic versions of '
            'some operators are not available.'
        ),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument(
        '--model-name', dest='model_name', type=str, default='simple_dqn', choices=['simple_dqn'],
        help='the model to train'
    )
    parser.add_argument(
        '--episodes', default=50, type=int,
        help='train for the specified number of episodes'
    )
    parser.add_argument(
        '--batch-size', dest='batch_size', default=128, type=int,
        help='batch size'
    )

    args = parser.parse_args()

    # Some required operators in pytorch do not have deterministic versions
    args.random = True

    if not args.random:
        # Make the result reproducible
        random_seed = 42
        torch.manual_seed(random_seed)
        random.seed(random_seed)
        np.random.seed(0)
        torch.use_deterministic_algorithms(True)
        env.seed(random_seed)

    dtype = torch.float32

    model_name = args.model_name
    model = model_name_to_model[model_name]
    transform = model_transforms(model_name, dtype)

    episodes = args.episodes
    if episodes <= 0:
        logging.error('--episodes has to be >= 1')
        return
    batch_size = args.batch_size
    if batch_size <= 0:
        logging.error('--batch-size has to be >= 1')
        return

    # Create the environment
    env = gym.make('CartPole-v0').unwrapped
    gamma = 0.999
    eps_start = 0.9
    eps_end = 0.05
    eps_decay = 200
    target_update = 10

    # Get screen dimensions
    env.reset()
    env.render()
    init_screen = get_screen(env, transform)
    screen_height, screen_width = init_screen.shape[-2:]

    # Get number of actions from gym action space
    n_actions = env.action_space.n

    # Create the model
    policy_net = model(screen_height, screen_width, n_actions).cuda()
    target_net = model(screen_height, screen_width, n_actions).cuda()

    optimizer = torch.optim.RMSprop(policy_net.parameters())
    criterion = torch.nn.SmoothL1Loss()
    memory = ReplayMemory(10000)

    model_file_name = f'data/train_rl_model_cuda/{model_name}_{{:05d}}.pth'

    # Check if there are snapshots
    snapshot_epoch = -1
    snapshot_file_name = None
    for file_name in os.listdir('data/train_rl_model_cuda'):
        if m := re.match(f'{model_name}_([0-9]+).pth', file_name):
            new_snapshot_epoch = int(m.group(1))
            if new_snapshot_epoch > snapshot_epoch:
                snapshot_epoch = new_snapshot_epoch
                snapshot_file_name = file_name

    if snapshot_file_name is not None:
        snapshot = torch.load(os.path.join('data/train_rl_model_cuda', snapshot_file_name))
        episode = snapshot['episode'] + 1
        steps_done = snapshot['steps_done']
        memory.load_state_dict(snapshot['memory'])
        policy_net.load_state_dict(snapshot['policy_model_state_dict'])
        target_net.load_state_dict(snapshot['target_model_state_dict'])
        optimizer.load_state_dict(snapshot['optimizer_state_dict'])
        logging.info(f'Continuing training from episode {episode}')
    else:
        episode = 0
        steps_done = 0
        target_net.load_state_dict(policy_net.state_dict())

    policy_net.train()
    target_net.eval()

    tensorboard_writer = SummaryWriter(
        log_dir=f'data/train_rl_model_cuda/tensorboard_{model_name}'
    )

    logging.info(f'Training {model_name} model with {dtype}')
    episode_durations = []
    while episode < episodes:
        # Initialize the environment and state
        env.reset()
        env.render()
        last_screen = get_screen(env, transform).cuda()
        current_screen = get_screen(env, transform).cuda()
        state = current_screen - last_screen
        train_loss = 0.0
        sum_of_rewards = 0.0
        train_start_time = time()
        for t in count():
            # Select and perform an action
            action = select_action(env, policy_net, state, steps_done, eps_start, eps_end, eps_decay, device='cuda')
            steps_done += 1
            _, reward, done, _ = env.step(action.item())
            env.render()
            sum_of_rewards += reward
            reward = torch.tensor([reward], device='cuda')

            # Observe new state
            last_screen = current_screen
            current_screen = get_screen(env, transform).cuda()
            if not done:
                next_state = current_screen - last_screen
            else:
                next_state = None

            # Store the transition in memory
            memory.push(state, action, next_state, reward)

            # Move to the next state
            state = next_state

            # Perform one step of the optimization (on the policy network)
            train_loss += optimize_model(
                policy_net, target_net, criterion, optimizer, memory,
                batch_size, gamma, dtype=dtype, device='cuda'
            )
            if done:
                episode_durations.append(t + 1)
                # plot_durations(episode_durations)
                break
        # Update the target network, copying all weights and biases in DQN
        if episode % target_update == 0:
            target_net.load_state_dict(policy_net.state_dict())
        train_end_time = time()
        train_time = timedelta(seconds=train_end_time - train_start_time)
        train_loss /= episode_durations[-1]

        logging.info(
            f'Episode {episode} done. Training time: {train_time}, '
            f'loss: {train_loss}, '
            f'sum of rewards: {sum_of_rewards}'
        )

        # Save the snapshot
        torch.save({
            'episode': episode,
            'steps_done': steps_done,
            'model_name': model_name,
            'memory': memory.state_dict(),
            'policy_model_state_dict': policy_net.state_dict(),
            'target_model_state_dict': target_net.state_dict(),
            'optimizer_state_dict': optimizer.state_dict()
        }, model_file_name.format(episode))

        tensorboard_writer.add_scalar('Loss/train', train_loss, episode)
        tensorboard_writer.add_scalar('SumOfRewards/train', sum_of_rewards, episode)
        tensorboard_writer.flush()

        episode += 1

    env.render()
    env.close()

    logging.info('Done')

if __name__ == '__main__':
    main()
