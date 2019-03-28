// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/Aura.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Aura::Aura(std::string&& enchantmentID, AuraType type)
    : m_enchantmentID(enchantmentID), m_type(type)
{
    // Do nothing
}

void Aura::Activate(Entity& owner)
{
    owner.GetOwner().GetGame()->auras.emplace_back(this);

    switch (m_type)
    {
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            owner.GetOwner().GetField().AddAura(this);
            break;
        }
    }
}
}  // namespace RosettaStone
