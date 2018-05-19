#include "gtest/gtest.h"

#include <Models/Card.h>
#include <Enums/Enums.h>

using namespace Hearthstonepp;

TEST(TestCard, Constructer)
{
	std::vector<GameTag> tags;
	std::map<PlayReq, int> reqs;
	std::vector<std::string> entourages;
	Card card1("cardTest", Rarity::COMMON, Faction::NEUTRAL, CardSet::NONE,
		CardClass::NEUTRAL, CardType::MINION, Race::DRAGON, "card", "this is test card", true,
		1, 1, 20, 20,
		tags,
		reqs,
		entourages
	);

	Card card2("cardTest2", Rarity::LEGENDARY, Faction::NEUTRAL, CardSet::NONE,
		CardClass::NEUTRAL, CardType::MINION, Race::DRAGON, "card2", "this is test card2", true,
		1, 1, 20, 20,
		tags,
		reqs,
		entourages
	);

	EXPECT_NO_THROW(card1.ShowBriefInfo());
	EXPECT_NO_THROW(card1.ShowInfo());
	EXPECT_EQ("cardTest", card1.GetID());
	EXPECT_EQ(Rarity::COMMON, card1.GetRarity());
	EXPECT_EQ(CardClass::NEUTRAL, card1.GetCardClass());
	EXPECT_EQ(CardType::MINION, card1.GetCardType());
	EXPECT_EQ(Race::DRAGON, card1.GetRace());
	EXPECT_EQ(1, card1.GetCost());
	EXPECT_EQ(1, card1.GetAttack());
	EXPECT_EQ(20, card1.GetHealth());
	EXPECT_EQ(20, card1.GetDurability());
	EXPECT_EQ(2, card1.GetMaxAllowedInDeck());
	EXPECT_EQ(1, card2.GetMaxAllowedInDeck());
}