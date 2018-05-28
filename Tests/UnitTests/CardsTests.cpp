#include "gtest/gtest.h"

#include <Models/Cards.h>
#include <Enums/Enums.h>

using namespace Hearthstonepp;

TEST(TestCards, Singleton) 
{
	Cards* cards = Cards::GetInstance();

	EXPECT_EQ(cards, Cards::GetInstance());
}

TEST(TestCards, GetAllCards) 
{
	const std::vector<Card*> cards1 = Cards::GetInstance()->GetAllCards();
	ASSERT_FALSE(cards1.empty());
	EXPECT_EQ(4676, cards1.size());
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
	EXPECT_TRUE(cards6.empty());
	EXPECT_TRUE(cards7.empty());
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
	EXPECT_TRUE(cards9.empty());
}

TEST(TestCards, FindCardByType)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByType(CardType::WEAPON);
	std::vector<Card*> cards2 = cards->FindCardByType(CardType::GAME);
	std::vector<Card*> cards3 = cards->FindCardByType(CardType::HERO);
	std::vector<Card*> cards4 = cards->FindCardByType(CardType::HERO_POWER);
	std::vector<Card*> cards5 = cards->FindCardByType(CardType::ENCHANTMENT);
	std::vector<Card*> cards6 = cards->FindCardByType(CardType::ITEM);
	std::vector<Card*> cards7 = cards->FindCardByType(CardType::MINION);
	std::vector<Card*> cards8 = cards->FindCardByType(CardType::PLAYER);
	std::vector<Card*> cards9 = cards->FindCardByType(CardType::SPELL);
	std::vector<Card*> cards10 = cards->FindCardByType(CardType::TOKEN);
	std::vector<Card*> cards11 = cards->FindCardByType(CardType::INVALID);

	EXPECT_EQ(CardType::WEAPON, cards1.front()->GetCardType());
	EXPECT_EQ(CardType::HERO, cards3.front()->GetCardType());
	EXPECT_EQ(CardType::HERO_POWER, cards4.front()->GetCardType());
	EXPECT_EQ(CardType::ENCHANTMENT, cards5.front()->GetCardType());
	EXPECT_EQ(CardType::MINION, cards7.front()->GetCardType());
	EXPECT_EQ(CardType::SPELL, cards9.front()->GetCardType());
	EXPECT_TRUE(cards2.empty());
	EXPECT_TRUE(cards6.empty());
	EXPECT_TRUE(cards8.empty());
	EXPECT_TRUE(cards10.empty());
	EXPECT_TRUE(cards11.empty());
}

TEST(TestCards, FindCardByRace)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByRace(Race::INVALID);
	EXPECT_FALSE(cards1.empty());
	EXPECT_NO_THROW(cards->FindCardByRace(Race::ALL));
} 

TEST(TestCards, FindCardByName)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByName("Flame Lance");
	std::vector<Card*> cards2 = cards->FindCardByName("");
	EXPECT_EQ("Flame Lance", cards1.front()->GetName());
	EXPECT_EQ(cards2, cards->GetAllCards());
}

TEST(TestCards, FindCardByCost)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByCost(0,1);
	std::vector<Card*> cards2 = cards->FindCardByCost(2,1);
	EXPECT_FALSE(cards1.empty());
	EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByAttack)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByAttack(0,1);
	std::vector<Card*> cards2 = cards->FindCardByAttack(2,1);
	EXPECT_FALSE(cards1.empty());
	EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByHealth)
{
	Cards* cards = Cards::GetInstance();
	std::vector<Card*> cards1 = cards->FindCardByHealth(0,1);
	std::vector<Card*> cards2 = cards->FindCardByHealth(2,1);
	EXPECT_FALSE(cards1.empty());
	EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByMechanics)
{
	Cards* cards = Cards::GetInstance();
	std::vector<GameTag> tags1;
	std::vector<GameTag> tags2;

	tags1.emplace_back(GameTag::CANT_ATTACK);
	std::vector<Card*> cards1 = cards->FindCardByMechanics(tags1);
	std::vector<Card*> cards2 = cards->FindCardByMechanics(tags2);

	auto cardTags = cards1.front()->GetMechanics();
	EXPECT_TRUE(std::find(cardTags.begin(), cardTags.end(), GameTag::CANT_ATTACK) != cardTags.end());
	EXPECT_TRUE(cards2.empty());
}