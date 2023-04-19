// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Enchants/SwapCostEnchant.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
void SwapCostEnchant::ActivateTo(Entity* entity, [[maybe_unused]] int num1,
                                 [[maybe_unused]] int num2)
{
    auto& playables = entity->game->taskStack.playables;

    if (playables.size() != 2)
    {
        return;
    }

    const int cost0 = playables[0]->GetCost();
    const int cost1 = playables[1]->GetCost();

    playables[0]->SetCost(cost1);
    playables[1]->SetCost(cost0);

    playables.clear();
}
}  // namespace RosettaStone::PlayMode
