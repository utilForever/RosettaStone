// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

using namespace RosettaStone;

TEST(Cards, GetAllCards)
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllCards();

    ASSERT_FALSE(cards.empty());
    EXPECT_EQ(cards.size(), 8303u);
}

TEST(Cards, GetAllStandardCards)
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllStandardCards();

    ASSERT_FALSE(cards.empty());
    for (auto& card : cards)
    {
        EXPECT_EQ(card->IsStandardSet(), true);
    }
}

TEST(Cards, GetAllWildCards)
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllWildCards();

    ASSERT_FALSE(cards.empty());
    for (auto& card : cards)
    {
        EXPECT_EQ(card->IsWildSet(), true);
    }
}

TEST(Cards, FindCardByID)
{
    const Card* card1 = Cards::GetInstance().FindCardByID("AT_001");
    const Card* card2 = Cards::GetInstance().FindCardByID("");

    EXPECT_EQ(card1->id, "AT_001");
    EXPECT_EQ(card2->id, "");
}

TEST(Cards, FindCardByDbfId)
{
    const Card* card1 = Cards::GetInstance().FindCardByDbfID(559);
    const Card* card2 = Cards::GetInstance().FindCardByDbfID(-999);

    EXPECT_EQ(card1->dbfID, 559);
    EXPECT_EQ(card1->id, "EX1_116");
    EXPECT_EQ(card2->dbfID, 0);
    EXPECT_EQ(card2->id, "");
}

TEST(Cards, FindCardByRarity)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByRarity(Rarity::COMMON);
    std::vector<Card*> cards2 = instance.FindCardByRarity(Rarity::RARE);
    std::vector<Card*> cards3 = instance.FindCardByRarity(Rarity::EPIC);
    std::vector<Card*> cards4 = instance.FindCardByRarity(Rarity::LEGENDARY);
    std::vector<Card*> cards5 = instance.FindCardByRarity(Rarity::FREE);
    std::vector<Card*> cards6 = instance.FindCardByRarity(Rarity::INVALID);

    EXPECT_EQ(Rarity::COMMON, cards1.front()->GetRarity());
    EXPECT_EQ(Rarity::RARE, cards2.front()->GetRarity());
    EXPECT_EQ(Rarity::EPIC, cards3.front()->GetRarity());
    EXPECT_EQ(Rarity::LEGENDARY, cards4.front()->GetRarity());
    EXPECT_EQ(Rarity::FREE, cards5.front()->GetRarity());
    EXPECT_EQ(Rarity::INVALID, cards6.front()->GetRarity());
}

TEST(Cards, FindCardByClass)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 =
        instance.FindCardByClass(CardClass::DEATHKNIGHT);
    std::vector<Card*> cards2 = instance.FindCardByClass(CardClass::DREAM);
    std::vector<Card*> cards3 = instance.FindCardByClass(CardClass::DRUID);
    std::vector<Card*> cards4 = instance.FindCardByClass(CardClass::HUNTER);
    std::vector<Card*> cards5 = instance.FindCardByClass(CardClass::MAGE);
    std::vector<Card*> cards6 = instance.FindCardByClass(CardClass::NEUTRAL);
    std::vector<Card*> cards7 = instance.FindCardByClass(CardClass::PALADIN);
    std::vector<Card*> cards8 = instance.FindCardByClass(CardClass::PRIEST);
    std::vector<Card*> cards9 = instance.FindCardByClass(CardClass::INVALID);

    EXPECT_EQ(CardClass::DEATHKNIGHT, cards1.front()->GetCardClass());
    EXPECT_EQ(CardClass::DREAM, cards2.front()->GetCardClass());
    EXPECT_EQ(CardClass::DRUID, cards3.front()->GetCardClass());
    EXPECT_EQ(CardClass::HUNTER, cards4.front()->GetCardClass());
    EXPECT_EQ(CardClass::MAGE, cards5.front()->GetCardClass());
    EXPECT_EQ(CardClass::NEUTRAL, cards6.front()->GetCardClass());
    EXPECT_EQ(CardClass::PALADIN, cards7.front()->GetCardClass());
    EXPECT_EQ(CardClass::PRIEST, cards8.front()->GetCardClass());
    EXPECT_EQ(CardClass::INVALID, cards9.front()->GetCardClass());
}

TEST(Cards, FindCardBySet)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardBySet(CardSet::CORE);
    std::vector<Card*> cards2 = instance.FindCardBySet(CardSet::EXPERT1);
    std::vector<Card*> cards3 = instance.FindCardBySet(CardSet::HOF);
    std::vector<Card*> cards4 = instance.FindCardBySet(CardSet::NAXX);
    std::vector<Card*> cards5 = instance.FindCardBySet(CardSet::GVG);
    std::vector<Card*> cards6 = instance.FindCardBySet(CardSet::BRM);
    std::vector<Card*> cards7 = instance.FindCardBySet(CardSet::TGT);
    std::vector<Card*> cards8 = instance.FindCardBySet(CardSet::LOE);
    std::vector<Card*> cards9 = instance.FindCardBySet(CardSet::OG);
    std::vector<Card*> cards10 = instance.FindCardBySet(CardSet::KARA);
    std::vector<Card*> cards11 = instance.FindCardBySet(CardSet::GANGS);
    std::vector<Card*> cards12 = instance.FindCardBySet(CardSet::UNGORO);
    std::vector<Card*> cards13 = instance.FindCardBySet(CardSet::ICECROWN);
    std::vector<Card*> cards14 = instance.FindCardBySet(CardSet::LOOTAPALOOZA);
    std::vector<Card*> cards15 = instance.FindCardBySet(CardSet::GILNEAS);
    std::vector<Card*> cards16 = instance.FindCardBySet(CardSet::BOOMSDAY);
    std::vector<Card*> cards17 = instance.FindCardBySet(CardSet::INVALID);

    EXPECT_EQ(CardSet::CORE, cards1.front()->GetCardSet());
    EXPECT_EQ(CardSet::EXPERT1, cards2.front()->GetCardSet());
    EXPECT_EQ(CardSet::HOF, cards3.front()->GetCardSet());
    EXPECT_EQ(CardSet::NAXX, cards4.front()->GetCardSet());
    EXPECT_EQ(CardSet::GVG, cards5.front()->GetCardSet());
    EXPECT_EQ(CardSet::BRM, cards6.front()->GetCardSet());
    EXPECT_EQ(CardSet::TGT, cards7.front()->GetCardSet());
    EXPECT_EQ(CardSet::LOE, cards8.front()->GetCardSet());
    EXPECT_EQ(CardSet::OG, cards9.front()->GetCardSet());
    EXPECT_EQ(CardSet::KARA, cards10.front()->GetCardSet());
    EXPECT_EQ(CardSet::GANGS, cards11.front()->GetCardSet());
    EXPECT_EQ(CardSet::UNGORO, cards12.front()->GetCardSet());
    EXPECT_EQ(CardSet::ICECROWN, cards13.front()->GetCardSet());
    EXPECT_EQ(CardSet::LOOTAPALOOZA, cards14.front()->GetCardSet());
    EXPECT_EQ(CardSet::GILNEAS, cards15.front()->GetCardSet());
    EXPECT_EQ(CardSet::BOOMSDAY, cards16.front()->GetCardSet());
    EXPECT_TRUE(cards17.empty());
}

TEST(Cards, FindCardByType)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByType(CardType::WEAPON);
    std::vector<Card*> cards2 = instance.FindCardByType(CardType::GAME);
    std::vector<Card*> cards3 = instance.FindCardByType(CardType::HERO);
    std::vector<Card*> cards4 = instance.FindCardByType(CardType::HERO_POWER);
    std::vector<Card*> cards5 = instance.FindCardByType(CardType::ENCHANTMENT);
    std::vector<Card*> cards6 = instance.FindCardByType(CardType::ITEM);
    std::vector<Card*> cards7 = instance.FindCardByType(CardType::MINION);
    std::vector<Card*> cards8 = instance.FindCardByType(CardType::PLAYER);
    std::vector<Card*> cards9 = instance.FindCardByType(CardType::SPELL);
    std::vector<Card*> cards10 = instance.FindCardByType(CardType::TOKEN);
    std::vector<Card*> cards11 = instance.FindCardByType(CardType::INVALID);

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

TEST(Cards, FindCardByRace)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards = instance.FindCardByRace(Race::INVALID);

    EXPECT_FALSE(cards.empty());
    EXPECT_NO_THROW(instance.FindCardByRace(Race::ALL));
}

TEST(Cards, FindCardByName)
{
    Cards& instance = Cards::GetInstance();

    const Card* card1 = instance.FindCardByName("Flame Lance");
    EXPECT_EQ(card1->name, "Flame Lance");

    const Card* card2 = instance.FindCardByName("INVALID");
    EXPECT_EQ(card2->name.empty(), true);
}

TEST(Cards, FindCardByCost)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByCost(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByCost(2, 1);

    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(Cards, FindCardByAttack)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByAttack(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByAttack(2, 1);

    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(Cards, FindCardByHealth)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByHealth(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByHealth(2, 1);

    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(Cards, FindCardByGameTag)
{
    Cards& instance = Cards::GetInstance();

    std::vector<GameTag> tags1;
    const std::vector<GameTag> tags2;
    tags1.emplace_back(GameTag::CANT_ATTACK);

    std::vector<Card*> cards1 = instance.FindCardByGameTag(tags1);
    std::vector<Card*> cards2 = instance.FindCardByGameTag(tags2);
    auto gameTags = cards1.front()->gameTags;

    EXPECT_TRUE(gameTags.find(GameTag::CANT_ATTACK) != gameTags.end());
    EXPECT_TRUE(cards2.empty());
}

TEST(Cards, GetHeroCard)
{
    Cards& instance = Cards::GetInstance();

    EXPECT_EQ(instance.FindCardByID("HERO_06")->id,
              instance.GetHeroCard(CardClass::DRUID)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_05")->id,
              instance.GetHeroCard(CardClass::HUNTER)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_08")->id,
              instance.GetHeroCard(CardClass::MAGE)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_04")->id,
              instance.GetHeroCard(CardClass::PALADIN)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_09")->id,
              instance.GetHeroCard(CardClass::PRIEST)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_03")->id,
              instance.GetHeroCard(CardClass::ROGUE)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_02")->id,
              instance.GetHeroCard(CardClass::SHAMAN)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_07")->id,
              instance.GetHeroCard(CardClass::WARLOCK)->id);
    EXPECT_EQ(instance.FindCardByID("HERO_01")->id,
              instance.GetHeroCard(CardClass::WARRIOR)->id);
    EXPECT_EQ(instance.GetHeroCard(CardClass::DEATHKNIGHT)->id, "");
}

TEST(Cards, GetDefaultHeroPower)
{
    Cards& instance = Cards::GetInstance();

    EXPECT_EQ(instance.FindCardByID("CS2_017")->id,
              instance.GetDefaultHeroPower(CardClass::DRUID)->id);
    EXPECT_EQ(instance.FindCardByID("DS1h_292")->id,
              instance.GetDefaultHeroPower(CardClass::HUNTER)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_034")->id,
              instance.GetDefaultHeroPower(CardClass::MAGE)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_101")->id,
              instance.GetDefaultHeroPower(CardClass::PALADIN)->id);
    EXPECT_EQ(instance.FindCardByID("CS1h_001")->id,
              instance.GetDefaultHeroPower(CardClass::PRIEST)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_083b")->id,
              instance.GetDefaultHeroPower(CardClass::ROGUE)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_049")->id,
              instance.GetDefaultHeroPower(CardClass::SHAMAN)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_056")->id,
              instance.GetDefaultHeroPower(CardClass::WARLOCK)->id);
    EXPECT_EQ(instance.FindCardByID("CS2_102")->id,
              instance.GetDefaultHeroPower(CardClass::WARRIOR)->id);
    EXPECT_EQ(instance.GetDefaultHeroPower(CardClass::DEATHKNIGHT)->id, "");
}

TEST(Cards, FindCardBySpellDamage)
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardBySpellPower(1, 1);
    std::vector<Card*> cards2 = instance.FindCardBySpellPower(2, 1);

    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}
