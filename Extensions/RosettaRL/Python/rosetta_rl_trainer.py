# Copyright (c) 2026 Chris Ohk

import torch


def train(model, batches, checkpoint):
    """Train the bound model and save shared weights after all batches succeed.

    Each batch contains observations, policy targets and outcomes. Returns the
    final batch's pre-update (policy, value, total) losses as Python floats.
    """
    optimizer = torch.optim.SGD(model.parameters(), lr=0.01)
    model.train()
    last_losses = None

    for observations, policy_targets, outcomes in batches:
        policy_loss, value_loss, total_loss = model.training_losses(
            model(observations), policy_targets, outcomes
        )
        optimizer.zero_grad()
        total_loss.backward()
        optimizer.step()
        last_losses = (policy_loss, value_loss, total_loss)

    if last_losses is None:
        raise ValueError("Training requires at least one batch")

    model.save_checkpoint(checkpoint)
    return tuple(loss.item() for loss in last_losses)
