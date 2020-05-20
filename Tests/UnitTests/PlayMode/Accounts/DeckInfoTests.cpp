// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Accounts/DeckInfo.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[DeckInfo] - Constructors")
{
    const DeckInfo deck1;
    CHECK_EQ(deck1.GetName(), "Empty");
    CHECK_EQ(deck1.GetClass(), CardClass::INVALID);
    CHECK_EQ(deck1.GetNumOfCards(), 0u);

    const DeckInfo deck2("Ice Magician", CardClass::MAGE);
    CHECK_EQ(deck2.GetName(), "Ice Magician");
    CHECK_EQ(deck2.GetClass(), CardClass::MAGE);
    CHECK_EQ(deck2.GetNumOfCards(), 0u);
}

TEST_CASE("[DeckInfo] - CardControl")
{
    std::vector<Card*> druidCards =
        Cards::GetInstance().FindCardByClass(CardClass::DRUID);
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    CHECK_NOTHROW(deck.ShowCardList());
    CHECK(deck.AddCard(mageCards.at(0)->id, 1));
    CHECK_EQ(deck.GetCard(0).second, 1u);
    CHECK(deck.AddCard(mageCards.at(0)->id, 1));
    CHECK_EQ(deck.GetCard(0).second, 2u);
    CHECK_FALSE(deck.AddCard(mageCards.at(0)->id, 1));
    CHECK_FALSE(deck.AddCard(mageCards.at(1)->id, 3));
    CHECK_FALSE(deck.AddCard(druidCards.at(0)->id, 1));
    CHECK_NOTHROW(deck.ShowCardList());

    CHECK_EQ(deck.GetUniqueNumOfCards(), 1u);
    CHECK_EQ(deck.GetNumOfCards(), 2u);

    CHECK_EQ(deck.GetCard(0).second, 2u);
    CHECK(deck.DeleteCard(mageCards.at(0)->id, 1));
    // CHECK_EQ(deck.GetCard(0).second, 1u);
    CHECK_FALSE(deck.DeleteCard(mageCards.at(0)->id, 4));
    CHECK_FALSE(deck.DeleteCard(druidCards.at(0)->id, 1));
    CHECK_NOTHROW(deck.ShowCardList());
}

TEST_CASE("[DeckInfo] - GetNumCardInDeck")
{
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);

    CHECK_EQ(deck.GetNumCardInDeck(mageCards.at(0)->id), 1u);
    CHECK_EQ(deck.GetNumCardInDeck(mageCards.at(1)->id), 0u);
}

TEST_CASE("[DeckInfo] - GetPrimitiveDeck")
{
    std::vector<Card*> mageCards =
        Cards::GetInstance().FindCardByClass(CardClass::MAGE);

    DeckInfo deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);

    std::vector<Card*> priDeck = deck.GetPrimitiveDeck();

    CHECK_EQ(priDeck.at(0)->id, mageCards.at(0)->id);
}

TEST_CASE("[DeckInfo] - GetCardIDs")
{
    const std::string INNKEEPER_EXPERT_WARLOCK =
        "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
    auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

    CHECK_EQ(deck.size(), 30u);

    for (const auto& cardID : deck)
    {
        Card* card = Cards::GetInstance().FindCardByID(cardID);
        CHECK_EQ((card->GetCardClass() == CardClass::WARLOCK ||
                  card->GetCardClass() == CardClass::NEUTRAL),
                 true);
    }
}