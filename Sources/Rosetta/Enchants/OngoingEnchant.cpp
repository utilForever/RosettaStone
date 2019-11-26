// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/OngoingEnchant.hpp>
#include <Rosetta/Models/Playable.hpp>

#include <utility>

namespace RosettaStone
{
OngoingEnchant::OngoingEnchant(std::vector<IEffect*> effects)
    : Enchant(std::move(effects))
{
    // Do nothing
}

void OngoingEnchant::ActivateTo(Entity* entity, int num1, int num2)
{
    Clone(dynamic_cast<Playable*>(entity));
}

void OngoingEnchant::Clone(Playable* clone)
{
    auto copy = new OngoingEnchant(effects);
}
}  // namespace RosettaStone
