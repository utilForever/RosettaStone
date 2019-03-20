// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

using namespace RosettaStone;

TEST(Card, Constructer)
{
    Card card1;
    card1.id = "cardTest1";
    card1.rarity = Rarity::COMMON;
    card1.faction = Faction::NEUTRAL;
    card1.cardSet = CardSet::NONE;
    card1.cardClass = CardClass::NEUTRAL;
    card1.cardType = CardType::MINION;
    card1.race = Race::DRAGON;
    card1.name = "card1";
    card1.text = "this is test card1";
    card1.isCollectible = true;
    card1.cost = 1;
    card1.Initialize();

    Card card2;
    card2.id = "cardTest2";
    card2.rarity = Rarity::LEGENDARY;
    card2.faction = Faction::NEUTRAL;
    card2.cardSet = CardSet::NONE;
    card2.cardClass = CardClass::NEUTRAL;
    card2.cardType = CardType::MINION;
    card2.race = Race::DRAGON;
    card2.name = "card2";
    card2.text = "this is test card2";
    card2.isCollectible = true;
    card2.cost = 1;
    card2.Initialize();

    EXPECT_NO_THROW(card1.ShowBriefInfo());
    EXPECT_NO_THROW(card1.ShowInfo());
    EXPECT_EQ("cardTest1", card1.id);
    EXPECT_EQ(+Rarity::COMMON, card1.rarity);
    EXPECT_EQ(+CardClass::NEUTRAL, card1.cardClass);
    EXPECT_EQ(+CardType::MINION, card1.cardType);
    EXPECT_EQ(+Race::DRAGON, card1.race);
    EXPECT_EQ(1, static_cast<int>(card1.cost));
    EXPECT_EQ(2, static_cast<int>(card1.GetMaxAllowedInDeck()));
    EXPECT_EQ(1, static_cast<int>(card2.GetMaxAllowedInDeck()));
    EXPECT_EQ(true, card1.isCollectible);
}

TEST(Card, HasMechanic)
{
    Card card;
    card.id = "cardTest1";
    card.rarity = Rarity::COMMON;
    card.faction = Faction::NEUTRAL;
    card.cardSet = CardSet::NONE;
    card.cardClass = CardClass::NEUTRAL;
    card.cardType = CardType::MINION;
    card.race = Race::DRAGON;
    card.name = "card1";
    card.text = "this is test card1";
    card.isCollectible = true;
    card.cost = 1;
    card.Initialize();

    EXPECT_EQ(false, card.HasMechanic(+GameTag::ADAPT));
}