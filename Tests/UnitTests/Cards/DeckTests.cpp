#include "gtest/gtest.h"

#include <hspp/Cards/Deck.h>
#include <hspp/Enums/CardEnums.h>

using namespace Hearthstonepp;

TEST(TestDeck, Constructors)
{
    Deck deck1;
    EXPECT_EQ("Empty", deck1.GetName());
    EXPECT_EQ(+CardClass::INVALID, deck1.GetClass());
    EXPECT_EQ(0, (int)deck1.GetNumOfCards());

    Deck deck2("ice magician", CardClass::MAGE);
    EXPECT_EQ("ice magician", deck2.GetName());
    EXPECT_EQ(+CardClass::MAGE, deck2.GetClass());
    EXPECT_EQ(0, (int)deck2.GetNumOfCards());
}

TEST(TestDeck, CardControl) 
{
    std::vector<Card*> druidCards = Cards::GetInstance()->FindCardByClass(+CardClass::DRUID);
    std::vector<Card*> mageCards = Cards::GetInstance()->FindCardByClass(+CardClass::MAGE);

    Deck deck("ice magician", CardClass::MAGE);
    EXPECT_NO_THROW(deck.ShowCardList());
    EXPECT_EQ(true, deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(true, deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(false, deck.AddCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(false, deck.AddCard(mageCards.at(1)->id, 3));
    EXPECT_EQ(false, deck.AddCard(druidCards.at(0)->id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());

    EXPECT_EQ(1, static_cast<int>(deck.GetUniqueNumOfCards()));
    EXPECT_EQ(2, static_cast<int>(deck.GetNumOfCards()));

    EXPECT_EQ(true, deck.DeleteCard(mageCards.at(0)->id, 1));
    EXPECT_EQ(false, deck.DeleteCard(mageCards.at(0)->id, 4));
    EXPECT_EQ(false, deck.DeleteCard(druidCards.at(0)->id, 1));
    EXPECT_NO_THROW(deck.ShowCardList());
}

TEST(TestDeck, GetNumCardInDeck)
{
    std::vector<Card*> mageCards = Cards::GetInstance()->FindCardByClass(+CardClass::MAGE);

    Deck deck("ice magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);

    EXPECT_EQ(1, static_cast<int>(deck.GetNumCardInDeck(mageCards.at(0)->id)));
    EXPECT_EQ(0, static_cast<int>(deck.GetNumCardInDeck(mageCards.at(1)->id)));
}

TEST(TestDeck, GetPrimitiveDeck)
{
    std::vector<Card*> mageCards = Cards::GetInstance()->FindCardByClass(+CardClass::MAGE);

    Deck deck("ice magician", CardClass::MAGE);
    deck.AddCard(mageCards.at(0)->id, 1);
    std::vector<const Card*> priDeck = deck.GetPrimitiveDeck();

    EXPECT_EQ(priDeck.at(0), mageCards.at(0));
}