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
    // vector shape: [4 + 13 * 5 = 69]
    // [ONE_HOT_TASKID #4]
    // [SOURCE: [ONE_HOT_PLACE_INFO #3] [ONE_HOT_INDEX #10]]
    // [TARGET: [...] #4]
    torch::Tensor tensor = torch::empty(ActionTensorSize, torch::kInt8);

    // Write ont-hot encoded TaskID.
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
        // Initialize
        fill_zero(start);
        if (entity == nullptr)
        {
            return;
        }

        Player& player = game.GetCurrentPlayer();

        // If entity is on the hand of current player.
        if (auto pos = player.GetHand().FindCardPos(*entity); pos.has_value())
        {
            tensor[start + CurrentHandOffset] = 1;
            tensor[start + TargetPlaceSize + pos.value()] = 1;
        }
        // If entity is minion.
        else if (Minion* minion = dynamic_cast<Minion*>(entity);
                 minion != nullptr)
        {
            // If entity is on the field of current player.
            if (auto pos = player.GetField().FindMinionPos(*minion);
                pos.has_value())
            {
                tensor[start + CurrentFieldOffset] = 1;
                tensor[start + TargetPlaceSize + pos.value()] = 1;
            }
            // If entity is on the field of other player.
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

    // Write source.
    write(TaskIDSize, action.source);
    // Write target.
    for (size_t i = 0; i < NumTarget; ++i)
    {
        write(TaskIDSize + (i + 1) * EntityEncodeSize, action.target[i]);
    }
    return tensor;
}
}  // namespace RosettaTorch