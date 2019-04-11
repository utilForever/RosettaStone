// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <RosettaTorch/ActionEncoder.hpp>

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
}  // namespace RosettaTorch