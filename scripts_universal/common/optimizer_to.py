import torch


def optimizer_to(optimizer, target):
    for param in optimizer.state.values():
        if isinstance(param, torch.Tensor):
            param.data = param.data.to(target)
            if param._grad is not None:
                param._grad.data = param._grad.data.to(target)
        elif isinstance(param, dict):
            for subparam in param.values():
                if isinstance(subparam, torch.Tensor):
                    subparam.data = subparam.data.to(target)
                    if subparam._grad is not None:
                        subparam._grad.data = subparam._grad.data.to(target)
