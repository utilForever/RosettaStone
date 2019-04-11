// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <RosettaTorch/TorchPolicy.hpp>

namespace RosettaTorch
{
torch::Tensor ActionEncoder::ActionToTensor(const Game& game,
                                            const Generic::ActionEncode& action)
{
    torch::Tensor tensor = torch::empty(ActionTensorSize, torch::kInt8);
    for (size_t i = 0; i < TaskIDSize; ++i)
    {
        if (action.taskID == TaskIDs[i])
        {
            tensor[i] = 1;
        }
        else
        {
            tensor[i] = 0;
        }
    }

    auto fill_zero = [&](size_t start) {
        for (size_t i = 0; i < EntityEncodeSize; ++i)
        {
            tensor[start + i] = 0;
        }
    };

    auto write = [&](size_t start, Entity* entity) {
        fill_zero(start);
        if (entity == nullptr)
        {
            return;
        }

        Player& player = game.GetCurrentPlayer();
        if (auto pos = player.GetHand().FindCardPos(*entity); pos.has_value())
        {
            tensor[start + CurrentHandOffset] = 1;
            tensor[start + TargetPlaceSize + pos.value()] = 1;
        }
        else if (Minion* minion = dynamic_cast<Minion*>(entity);
                 minion != nullptr)
        {
            if (auto pos = player.GetField().FindMinionPos(*minion);
                pos.has_value())
            {
                tensor[start + CurrentFieldOffset] = 1;
                tensor[start + TargetPlaceSize + pos.value()] = 1;
            }
            else if (auto pos =
                         game.GetOpponentPlayer().GetField().FindMinionPos(
                             *minion);
                     pos.has_value())
            {
                tensor[start + OpponentFieldOffset] = 1;
                tensor[start + TargetPlaceSize + pos.value()] = 1;
            }
        }
    };

    write(TaskIDSize, action.source);
    for (size_t i = 0; i < NumTarget; ++i)
    {
        write(TaskIDSize + (i + 1) * EntityEncodeSize, action.target[i]);
    }
    return tensor;
}

TorchPolicy::TorchPolicy(std::shared_ptr<ModuleBase> module,
                         GameToVec* gameToVec)
    : m_module(module), m_gameToVec(gameToVec)
{
    // Do nothing
}

TaskMeta TorchPolicy::Next(const Game& game)
{
    std::vector<Generic::ActionEncode> actions =
        Generic::AvailableActions(game);
    return Inference(game, actions);
}

TaskMeta TorchPolicy::ActionToTaskMeta() const
{
    SizedPtr<Entity*> entities(m_action.numTarget);
    for (size_t i = 0; i < m_action.numTarget; ++i)
    {
        entities[i] = m_action.target[i];
    }
    return TaskMeta({ m_action.taskID }, std::move(entities));
}

TaskMeta TorchPolicy::Inference(
    const Game& game, const std::vector<Generic::ActionEncode>& actions)
{
    torch::Tensor context = m_gameToVec->GenerateTensor(game);
    torch::Tensor actionTensor =
        torch::empty({ static_cast<long long>(actions.size()),
                       ActionEncoder::ActionTensorSize },
                     torch::kInt8);

    for (size_t i = 0; i < actions.size(); ++i)
    {
        actionTensor[i] = ActionEncoder::ActionToTensor(game, actions[i]);
    }

    torch::Tensor result = m_module->forward(actionTensor, context);
    size_t idx = result.argmax().item<size_t>();

    m_action = actions[idx];
    return TaskMeta(TaskMetaTrait(m_action.taskID));
}

TaskMeta TorchPolicy::RequireMulligan(Player& player)
{
    std::vector<Generic::ActionEncode> actions;

    Hand& hand = player.GetHand();
    for (size_t i = 0; i < hand.GetNumOfCards(); ++i)
    {
        actions.emplace_back(TaskID::MULLIGAN, hand.GetCard(i));
    }

    // TODO : Multiple Mulligan
    return Inference(*player.GetGame(), actions);
}

TaskMeta TorchPolicy::RequirePlayCard(Player& player)
{
    return ActionToTaskMeta();
}

TaskMeta TorchPolicy::RequireAttack(Player& player)
{
    return ActionToTaskMeta();
}
}  // namespace RosettaTorch