import os
# chdir is required before importing torch, since otherwise
# "python scripts_universal/train_rl_model_change_type_and_resume.py" won't work in install mode
os.chdir(os.path.dirname(os.path.abspath(__file__)))

import argparse
from datetime import datetime, timedelta
from itertools import count
import logging
import pathlib
import random
import sys
from time import time

import torch
import numpy as np

from common.disclaimer import gym_disclaimer

try:
    import gym
except ModuleNotFoundError:
    print(gym_disclaimer)
    sys.exit(0)

from common.dtype_name_to_dtype import dtype_name_to_dtype
from common.optimizer_to import optimizer_to
from common.rl_models import model_name_to_model, model_transforms, ReplayMemory
from common.rl_utils import get_screen, select_action, optimize_model


def main():
    os.makedirs('data/train_rl_model_change_type_and_resume', exist_ok=True)
    logging.basicConfig(
        level=logging.DEBUG,
        filename=f'data/train_rl_model_change_type_and_resume/log_{datetime.now().strftime("%Y_%m_%d_%H_%M_%S")}.log',
        filemode='a+',
        format='%(asctime)-15s %(levelname)-8s %(message)s'
    )
    logging.info(f'Running {" ".join(sys.argv)}')
    # Output logs to file and to stderr
    logging.getLogger().addHandler(logging.StreamHandler())

    parser = argparse.ArgumentParser(
        description=(
            'Loads a model snapshot that was created by train_rl_model_cuda.py, '
            'converts it to the specified type, and trains it for one more '
            'episode. NOTE: '
            'this script is always randomized since deterministic versions of '
            'some operators are not available.'
        ),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument(
        'snapshot', type=str,
        help='the snapshot file (*.pth)'
    )
    parser.add_argument(
        '--dtype', default='cfloatwithsubnormals', choices=['cfloatwithsubnormals'],
        help='batch size'
    )
    parser.add_argument(
        '--batch-size', dest='batch_size', default=6, type=int,
        help='batch size'
    )

    args = parser.parse_args()

    if args.dtype not in dtype_name_to_dtype:
        logging.error(f'Invalid dtype: {args.dtype}')
        return

    dtype = dtype_name_to_dtype[args.dtype]
    batch_size = args.batch_size
    if batch_size <= 0:
        logging.error('--batch-size has to be >= 1')
        return

    snapshot = torch.load(args.snapshot)

    if 'model_name' not in snapshot or 'memory' not in snapshot:
        logging.error('Invalid snapshot. Please specify a snapshot created by train_rl_model_cuda.py.')
        return
    model_name = snapshot['model_name']

    model = model_name_to_model[model_name]
    transform = model_transforms(model_name, dtype)

    output_snapshot_name = pathlib.Path(args.snapshot)
    output_snapshot_name = output_snapshot_name.with_name(
        output_snapshot_name.stem + '_resumed' + output_snapshot_name.suffix
    )

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
    policy_net = model(screen_height, screen_width, n_actions)
    target_net = model(screen_height, screen_width, n_actions)

    optimizer = torch.optim.RMSprop(policy_net.parameters())
    criterion = torch.nn.SmoothL1Loss()
    memory = ReplayMemory(10000)

    # Load the snapshot
    episode = snapshot['episode'] + 1
    steps_done = snapshot['steps_done']
    memory.load_state_dict(snapshot['memory'])
    policy_net.load_state_dict(snapshot['policy_model_state_dict'])
    target_net.load_state_dict(snapshot['target_model_state_dict'])
    optimizer.load_state_dict(snapshot['optimizer_state_dict'])

    # Convert the model to target dtype
    memory = memory.cpu().to(dtype)
    policy_net = policy_net.to(dtype)
    target_net = target_net.to(dtype)
    optimizer_to(optimizer, dtype)

    policy_net.train()
    target_net.eval()

    logging.info(f'Training {model_name} model with {dtype}')
    # Initialize the environment and state
    env.reset()
    env.render()
    episode_durations = []
    last_screen = get_screen(env, transform)
    current_screen = get_screen(env, transform)
    state = current_screen - last_screen
    train_loss = 0.0
    sum_of_rewards = 0.0
    train_start_time = time()
    for t in count():
        # Select and perform an action
        action = select_action(env, policy_net, state, steps_done, eps_start, eps_end, eps_decay)
        steps_done += 1
        _, reward, done, _ = env.step(action.item())
        env.render()
        sum_of_rewards += reward
        reward = torch.tensor([reward])

        # Observe new state
        last_screen = current_screen
        current_screen = get_screen(env, transform)
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
            batch_size, gamma, dtype=dtype
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
    }, output_snapshot_name)

    logging.info('Done')

if __name__ == '__main__':
    main()
