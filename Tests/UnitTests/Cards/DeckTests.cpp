// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Cards/Cards.hpp>
#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Models/Deck.hpp>

using namespace Hearthstonepp;

TEST(Deck, Constructors)
{
    Deck deck1;
    EXPECT_EQ("Empty", deck1.GetName());
    EXPECT_EQ(+CardClass::INVALID, deck1.GetClass());
    EXPECT_EQ(0u, deck1.GetNumOfCards());

    Deck deck2("Ice Magician", CardClass::MAGE);
    EXPECT_EQ("Ice Magician", deck2.GetName());
    EXPECT_EQ(+CardClass::MAGE, deck2.GetClass());
    EXPECT_EQ(0u, deck2.GetNumOfCards());
}

TEST(Deck, CardControl)
{
    std::vector<Card> druidCards =
        Cards::GetInstance().FindCardByClass(+CardClass::DRUID);
    std::vector<Card> mageCards =
        Cards::GetInstance().FindCardByClass(+CardClass::MAGE);

    Deck deck("Ice Magician", CardClass::MAGE);
    EXPECT_NO_THROW(deck.ShowCardList());
    EXPECT_EQ(true, deck.AddCard(mageCards.at(0).id, 1));
    EXPECT_EQ(true, deck.AddCard(mageCards.at(0).id, 1));
    EXPECT_EQ(false, deck.AddCard(mageCards.at(0).id, 1));
    EXPECT_EQ(false, deck.AddCard(mageCards.at(1).id, 3));
    EXPECT_EQ(false, deck.AddCard(druidCards.at(0).id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());

    EXPECT_EQ(1, static_cast<int>(deck.GetUniqueNumOfCards()));
    EXPECT_EQ(2, static_cast<int>(deck.GetNumOfCards()));

    EXPECT_EQ(true, deck.DeleteCard(mageCards.at(0).id, 1));
    EXPECT_EQ(false, deck.DeleteCard(mageCards.at(0).id, 4));
    EXPECT_EQ(false, deck.DeleteCard(druidCards.at(0).id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());
}

TEST(Deck, GetNumCardInDeck)
{
    std::vector<Card> mageCards =
        Cards::GetInstance().FindCardByClass(+CardClass::MAGE);

    Deck deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0).id, 1);

    EXPECT_EQ(1, static_cast<int>(deck.GetNumCardInDeck(mageCards.at(0).id)));
    EXPECT_EQ(0, static_cast<int>(deck.GetNumCardInDeck(mageCards.at(1).id)));
}

TEST(Deck, GetPrimitiveDeck)
{
    std::vector<Card> mageCards =
        Cards::GetInstance().FindCardByClass(+CardClass::MAGE);

    Deck deck("Ice Magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0).id, 1);

    std::vector<Card> priDeck = deck.GetPrimitiveDeck();

    EXPECT_EQ(priDeck.at(0).id, mageCards.at(0).id);
}