// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Card.hpp>

#include <iostream>

namespace RosettaStone
{
void Card::Initialize()
{
    maxAllowedInDeck = (rarity == Rarity::LEGENDARY) ? 1 : 2;
}

bool Card::HasGameTag(GameTag gameTag) const
{
    return gameTags.find(gameTag) != gameTags.end();
}

std::size_t Card::GetMaxAllowedInDeck() const
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
    std::cout << "Rarity: " << EnumToStr<Rarity>(rarity) << '\n';
    std::cout << "Faction: " << EnumToStr<Faction>(faction) << '\n';
    std::cout << "CardSet: " << EnumToStr<CardSet>(cardSet) << '\n';
    std::cout << "CardClass: " << EnumToStr<CardClass>(cardClass) << '\n';
    std::cout << "CardType: " << EnumToStr<CardType>(cardType) << '\n';
    std::cout << "Race: " << EnumToStr<Race>(race) << '\n';
}
}  // namespace RosettaStone
