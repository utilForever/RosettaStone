// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/PlayerAuraEffects.hpp>

#include <stdexcept>

namespace RosettaStone
{
int& PlayerAuraEffects::operator[](GameTag tag)
{
    switch (tag)
    {
        case GameTag::TIMEOUT:
            return m_timeOut;
        case GameTag::SPELLPOWER_DOUBLE:
        case GameTag::SPELL_HEALING_DOUBLE:
            return m_spellPowerDouble;
        default:
            throw std::invalid_argument(
                "PlayerAuraEffects::operator[] - Invalid game tag!");
    }
}
}  // namespace RosettaStone
