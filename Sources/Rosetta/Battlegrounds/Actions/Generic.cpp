// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Battlegrounds/Actions/Generic.hpp>

namespace RosettaStone::Battlegrounds::Generic
{
void AddEnchantment(Card& enchantmentCard, Minion& target, int num)
{
    Power& power = enchantmentCard.power;

    if (auto& enchant = power.GetEnchant(); enchant.has_value())
    {
        enchant.value().ActivateTo(target, num);
    }
}
}  // namespace RosettaStone::Battlegrounds::Generic
