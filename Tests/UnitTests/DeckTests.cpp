#include "gtest/gtest.h"

#include <Models/Deck.h>
#include <Enums/Enums.h>

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
	EXPECT_EQ(0, deck.AddCard(mageCards.at(0)->GetID(), 1));
	EXPECT_EQ(0, deck.AddCard(mageCards.at(0)->GetID(), 1));
	EXPECT_EQ(-1, deck.AddCard(mageCards.at(0)->GetID(), 1));
	EXPECT_EQ(-1, deck.AddCard(mageCards.at(1)->GetID(), 3));
	EXPECT_EQ(-1, deck.AddCard(druidCards.at(0)->GetID(), 1));
	EXPECT_NO_THROW(deck.ShowCardList());

	EXPECT_EQ(1, (int)deck.GetUniqueNumOfCards());
	EXPECT_EQ(2, (int)deck.GetNumOfCards());

	EXPECT_EQ(0, deck.DeleteCard(mageCards.at(0)->GetID(), 1));
	EXPECT_EQ(-1, deck.DeleteCard(mageCards.at(0)->GetID(), 4));
	EXPECT_EQ(-1, deck.DeleteCard(druidCards.at(0)->GetID(), 1));
	EXPECT_NO_THROW(deck.ShowCardList());
}

TEST(TestDeck, GetNumCardInDeck)
{
	std::vector<Card*> mageCards = Cards::GetInstance()->FindCardByClass(+CardClass::MAGE);

	Deck deck("ice magician", CardClass::MAGE);
	deck.AddCard(mageCards.at(0)->GetID(), 1);

	EXPECT_EQ(1, (int)deck.GetNumCardInDeck(mageCards.at(0)->GetID()));
	EXPECT_EQ(0, (int)deck.GetNumCardInDeck(mageCards.at(1)->GetID()));
}

TEST(TestDeck, GetPrimitiveDeck)
{
	std::vector<Card*> mageCards = Cards::GetInstance()->FindCardByClass(+CardClass::MAGE);

	Deck deck("ice magician", CardClass::MAGE);
	deck.AddCard(mageCards.at(0)->GetID(), 1);
    std::vector<const Card*> priDeck = deck.GetPrimitiveDeck();

	EXPECT_EQ(priDeck.at(0), mageCards.at(0));
}