// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Accounts/DeckInfo.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/DeckCode.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

using namespace RosettaStone;

TEST(DeckInfo, Constructors)
{
    const DeckInfo deck1;
    EXPECT_EQ(deck1.GetName(), "Empty");
    EXPECT_EQ(deck1.GetClass(), CardClass::INVALID);
    EXPECT_EQ(deck1.GetNumOfCards(), 0u);

    const DeckInfo deck2("Ice Magician", CardClass::MAGE);
    EXPECT_EQ(deck2.GetName(), "Ice Magician");
    EXPECT_EQ(deck2.GetClass(), CardClass::MAGE);
    EXPECT_EQ(deck2.GetNumOfCards(), 0u);
}

TEST(DeckInfo, CardControl)
{
    std::vector<Card*> druidCards =
        Cards::GetInstance().FindCardByClass(CardClass::DRUID);
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    EXPECT_NO_THROW(deck.ShowCardList());
    EXPECT_TRUE(deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(deck.GetCard(0).second, 1u);
    EXPECT_TRUE(deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(deck.GetCard(0).second, 2u);
    EXPECT_FALSE(deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_FALSE(deck.AddCard(mageCards.at(1)->id, 3));
    EXPECT_FALSE(deck.AddCard(druidCards.at(0)->id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());

    EXPECT_EQ(deck.GetUniqueNumOfCards(), 1u);
    EXPECT_EQ(deck.GetNumOfCards(), 2u);

    EXPECT_EQ(deck.GetCard(0).second, 2u);
    EXPECT_TRUE(deck.DeleteCard(mageCards.at(0)->id, 1));
    //EXPECT_EQ(deck.GetCard(0).second, 1u);
    EXPECT_FALSE(deck.DeleteCard(mageCards.at(0)->id, 4));
    EXPECT_FALSE(deck.DeleteCard(druidCards.at(0)->id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());
}

TEST(DeckInfo, GetNumCardInDeck)
{
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);

    EXPECT_EQ(deck.GetNumCardInDeck(mageCards.at(0)->id), 1u);
    EXPECT_EQ(deck.GetNumCardInDeck(mageCards.at(1)->id), 0u);
}

TEST(DeckInfo, GetPrimitiveDeck)
{
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);

    std::vector<Card*> priDeck = deck.GetPrimitiveDeck();

    EXPECT_EQ(priDeck.at(0)->id, mageCards.at(0)->id);
}

TEST(DeckInfo, GetCardIDs)
{
    const std::string INNKEEPER_EXPERT_WARLOCK =
        "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
    auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

    EXPECT_EQ(deck.size(), 30u);

    for (const auto& cardID : deck)
    {
        Card* card = Cards::GetInstance().FindCardByID(cardID);
        EXPECT_TRUE(card->GetCardClass() == CardClass::WARLOCK ||
                    card->GetCardClass() == CardClass::NEUTRAL);
    }
}