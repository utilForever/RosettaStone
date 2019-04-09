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
    maxAllowedInDeck = (GetRarity() == Rarity::LEGENDARY) ? 1 : 2;
}

CardClass Card::GetCardClass() const
{
    return static_cast<CardClass>(gameTags.at(GameTag::CLASS));
}

CardSet Card::GetCardSet() const
{
    return static_cast<CardSet>(gameTags.at(GameTag::CARD_SET));
}

CardType Card::GetCardType() const
{
    return static_cast<CardType>(gameTags.at(GameTag::CARDTYPE));
}

Faction Card::GetFaction() const
{
    return static_cast<Faction>(gameTags.at(GameTag::FACTION));
}

Race Card::GetRace() const
{
    return static_cast<Race>(gameTags.at(GameTag::CARDRACE));
}

Rarity Card::GetRarity() const
{
    return static_cast<Rarity>(gameTags.at(GameTag::RARITY));
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
    std::cout << "Rarity: " << EnumToStr<Rarity>(GetRarity()) << '\n';
    std::cout << "Faction: " << EnumToStr<Faction>(GetFaction()) << '\n';
    std::cout << "CardSet: " << EnumToStr<CardSet>(GetCardSet()) << '\n';
    std::cout << "CardClass: " << EnumToStr<CardClass>(GetCardClass()) << '\n';
    std::cout << "CardType: " << EnumToStr<CardType>(GetCardType()) << '\n';
    std::cout << "Race: " << EnumToStr<Race>(GetRace()) << '\n';
}
}  // namespace RosettaStone
