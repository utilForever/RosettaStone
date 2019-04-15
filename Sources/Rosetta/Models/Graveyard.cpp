// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Graveyard.hpp>

namespace RosettaStone
{
Graveyard::Graveyard()
{
    m_cards.reserve(START_DECK_SIZE);
}

Player& Graveyard::GetOwner() const
{
    return *m_owner;
}

void Graveyard::SetOwner(Player& owner)
{
    m_owner = &owner;
}

void Graveyard::AddCard(Entity& card)
{
    m_cards.emplace_back(&card);

    int enchantSize = static_cast<int>(card.appliedEnchantments.size());
    for (int i = enchantSize - 1; i >= 0; --i)
    {
        card.appliedEnchantments[i]->Remove();
    }
}
}  // namespace RosettaStone
