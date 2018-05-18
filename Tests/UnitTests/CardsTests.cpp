#include "gtest/gtest.h"

#include <Models/Cards.h>
#include <Enums/Enums.h>

using namespace Hearthstonepp;

TEST(TestCards, Singleton) 
{
	Cards* cards = Cards::GetInstance();

	EXPECT_EQ(cards, Cards::GetInstance());
}

TEST(TestCards, FindCardByID)
{
	const Card* card1 = Cards::GetInstance()->FindCardByID("AT_001");
	const Card* card2 = Cards::GetInstance()->FindCardByID("");
	
	EXPECT_EQ("AT_001", card1->GetID());
	EXPECT_EQ(nullptr, card2);
}

TEST(TestCards, FindCardByRarity)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByRarity(Rarity::COMMON);
	std::vector<Card*> cards2 = cards->FindCardByRarity(Rarity::RARE);
	std::vector<Card*> cards3 = cards->FindCardByRarity(Rarity::EPIC);
	std::vector<Card*> cards4 = cards->FindCardByRarity(Rarity::LEGENDARY);
	std::vector<Card*> cards5 = cards->FindCardByRarity(Rarity::FREE);
	std::vector<Card*> cards6 = cards->FindCardByRarity(Rarity::INVALID);
	std::vector<Card*> cards7 = cards->FindCardByRarity(Rarity::UNKNOWN_6);

	EXPECT_EQ(Rarity::COMMON, cards1.front()->GetRarity());
	EXPECT_EQ(Rarity::RARE, cards2.front()->GetRarity());
	EXPECT_EQ(Rarity::EPIC, cards3.front()->GetRarity());
	EXPECT_EQ(Rarity::LEGENDARY, cards4.front()->GetRarity());
	EXPECT_EQ(Rarity::FREE, cards5.front()->GetRarity());
	EXPECT_EQ(true, cards6.empty());
	EXPECT_EQ(true, cards7.empty());
}

TEST(TestCards, FindCardByClass)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByClass(CardClass::DEATHKNIGHT);
	std::vector<Card*> cards2 = cards->FindCardByClass(CardClass::DREAM);
	std::vector<Card*> cards3 = cards->FindCardByClass(CardClass::DRUID);
	std::vector<Card*> cards4 = cards->FindCardByClass(CardClass::HUNTER);
	std::vector<Card*> cards5 = cards->FindCardByClass(CardClass::MAGE);
	std::vector<Card*> cards6 = cards->FindCardByClass(CardClass::NEUTRAL);
	std::vector<Card*> cards7 = cards->FindCardByClass(CardClass::PALADIN);
	std::vector<Card*> cards8 = cards->FindCardByClass(CardClass::PRIEST);
	std::vector<Card*> cards9 = cards->FindCardByClass(CardClass::INVALID);

	EXPECT_EQ(CardClass::DEATHKNIGHT, cards1.front()->GetCardClass());
	EXPECT_EQ(CardClass::DREAM, cards2.front()->GetCardClass());
	EXPECT_EQ(CardClass::DRUID, cards3.front()->GetCardClass());
	EXPECT_EQ(CardClass::HUNTER, cards4.front()->GetCardClass());
	EXPECT_EQ(CardClass::MAGE, cards5.front()->GetCardClass());
	EXPECT_EQ(CardClass::NEUTRAL, cards6.front()->GetCardClass());
	EXPECT_EQ(CardClass::PALADIN, cards7.front()->GetCardClass());
	EXPECT_EQ(CardClass::PRIEST, cards8.front()->GetCardClass());
	EXPECT_EQ(true, cards9.empty());
}
