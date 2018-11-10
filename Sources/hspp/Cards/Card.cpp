// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Card.h>

#include <algorithm>
#include <iostream>

namespace Hearthstonepp
{
void Card::Initialize()
{
    maxAllowedInDeck = (rarity == +Rarity::LEGENDARY) ? 1 : 2;
}

bool Card::HasMechanic(GameTag mechanic) const
{
    return std::find(mechanics.begin(), mechanics.end(), mechanic) !=
           mechanics.end();
}

unsigned int Card::GetMaxAllowedInDeck() const
{
    return maxAllowedInDeck;
}

void Card::ShowBriefInfo() const
{
    std::cout << name.c_str() << " (" << id.c_str() << ") ";
}

void Card::ShowInfo() const
{
    std::cout << "ID: " << id.c_str() << '\n';
    std::cout << "Name: " << name.c_str() << '\n';
    std::cout << "Text: " << text.c_str() << '\n';
    std::cout << "Rarity: " << rarity._to_string() << '\n';
    std::cout << "Faction: " << faction._to_string() << '\n';
    std::cout << "CardSet: " << cardSet._to_string() << '\n';
    std::cout << "CardClass: " << cardClass._to_string() << '\n';
    std::cout << "CardType: " << cardType._to_string() << '\n';
    std::cout << "Race: " << race._to_string() << '\n';
}
}  // namespace Hearthstonepp