from PIL import Image
import torch
from torchvision import transforms

from collections import namedtuple, deque
import random

from .simple_dqn import SimpleDQN


model_name_to_model = {
    'simple_dqn': SimpleDQN
}

def model_transforms(model_name, dtype):
    # simple_dqn
    return transforms.Compose([
        transforms.ToPILImage(),
        transforms.Resize(40, interpolation=Image.CUBIC),
        transforms.ToTensor(),
        transforms.ConvertImageDtype(dtype)
    ])

Transition = namedtuple(
    'Transition',
    ('state', 'action', 'next_state', 'reward')
)

class ReplayMemory(object):
    def __init__(self, capacity):
        self.memory = deque([], maxlen=capacity)

    def push(self, *args):
        """Save a transition"""
        self.memory.append(Transition(*args))

    def sample(self, batch_size):
        return random.sample(self.memory, batch_size)

    def __len__(self):
        return len(self.memory)

    def state_dict(self):
        return {
            'memory': [
                Transition(
                    *(item.detach() if item is not None else item for item in transition)
                ) for transition in self.memory
            ]
        }

    def load_state_dict(self, state_dict):
        self.memory = deque(state_dict['memory'], maxlen=self.memory.maxlen)

    def cuda(self):
        return self.to('cuda')

    def cpu(self):
        return self.to('cpu')

    def to(self, target):
        is_device = False
        if isinstance(target, torch.device):
            is_device = True
        elif isinstance(target, str):
            try:
                torch.device(target)
                is_device = True
            except RuntimeError:
                pass

        new_memory = ReplayMemory(self.memory.maxlen)
        for transition in self.memory:
            state = transition.state.to(target)

            # We should not change the dtype of action
            action = transition.action
            if is_device:
                action = action.to(target)

            next_state = transition.next_state
            if next_state is not None:
                next_state = next_state.to(target)

            reward = transition.reward.to(target)
            new_memory.push(state, action, next_state, reward)
        return new_memory
