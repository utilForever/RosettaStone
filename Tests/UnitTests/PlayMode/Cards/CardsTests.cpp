// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Cards] - GetAllCards")
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllCards();

    CHECK_FALSE(cards.empty());
    CHECK_EQ(static_cast<int>(cards.size()), NUM_PLAY_MODE_CARDS);
}

TEST_CASE("[Cards] - GetAllStandardCards")
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllStandardCards();

    CHECK_FALSE(cards.empty());
    for (auto& card : cards)
    {
        CHECK_EQ(card->IsStandardSet(), true);
    }
}

TEST_CASE("[Cards] - GetAllWildCards")
{
    const std::vector<Card*> cards = Cards::GetInstance().GetAllWildCards();

    CHECK_FALSE(cards.empty());
    for (auto& card : cards)
    {
        CHECK_EQ(card->IsWildSet(), true);
    }
}

TEST_CASE("[Cards] - FindCardByID")
{
    const Card* card1 = Cards::GetInstance().FindCardByID("AT_001");
    const Card* card2 = Cards::GetInstance().FindCardByID("");

    CHECK_EQ(card1->id, "AT_001");
    CHECK_EQ(card2->id, "");
}

TEST_CASE("[Cards] - FindCardByDbfId")
{
    const Card* card1 = Cards::GetInstance().FindCardByDbfID(559);
    const Card* card2 = Cards::GetInstance().FindCardByDbfID(-999);

    CHECK_EQ(card1->dbfID, 559);
    CHECK_EQ(card1->id, "EX1_116");
    CHECK_EQ(card2->dbfID, 0);
    CHECK_EQ(card2->id, "");
}

TEST_CASE("[Cards] - FindCardByRarity")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByRarity(Rarity::COMMON);
    std::vector<Card*> cards2 = instance.FindCardByRarity(Rarity::RARE);
    std::vector<Card*> cards3 = instance.FindCardByRarity(Rarity::EPIC);
    std::vector<Card*> cards4 = instance.FindCardByRarity(Rarity::LEGENDARY);
    std::vector<Card*> cards5 = instance.FindCardByRarity(Rarity::FREE);
    std::vector<Card*> cards6 = instance.FindCardByRarity(Rarity::INVALID);

    CHECK_EQ(Rarity::COMMON, cards1.front()->GetRarity());
    CHECK_EQ(Rarity::RARE, cards2.front()->GetRarity());
    CHECK_EQ(Rarity::EPIC, cards3.front()->GetRarity());
    CHECK_EQ(Rarity::LEGENDARY, cards4.front()->GetRarity());
    CHECK_EQ(Rarity::FREE, cards5.front()->GetRarity());
    CHECK_EQ(Rarity::INVALID, cards6.front()->GetRarity());
}

TEST_CASE("[Cards] - FindCardByClass")
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

    CHECK_EQ(CardClass::DEATHKNIGHT, cards1.front()->GetCardClass());
    CHECK_EQ(CardClass::DREAM, cards2.front()->GetCardClass());
    CHECK_EQ(CardClass::DRUID, cards3.front()->GetCardClass());
    CHECK_EQ(CardClass::HUNTER, cards4.front()->GetCardClass());
    CHECK_EQ(CardClass::MAGE, cards5.front()->GetCardClass());
    CHECK_EQ(CardClass::NEUTRAL, cards6.front()->GetCardClass());
    CHECK_EQ(CardClass::PALADIN, cards7.front()->GetCardClass());
    CHECK_EQ(CardClass::PRIEST, cards8.front()->GetCardClass());
    CHECK_EQ(CardClass::INVALID, cards9.front()->GetCardClass());
}

TEST_CASE("[Cards] - FindCardBySet")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardBySet(CardSet::CORE);
    std::vector<Card*> cards2 = instance.FindCardBySet(CardSet::EXPERT1);
    std::vector<Card*> cards3 = instance.FindCardBySet(CardSet::LEGACY);
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

    CHECK_EQ(CardSet::CORE, cards1.front()->GetCardSet());
    CHECK_EQ(CardSet::EXPERT1, cards2.front()->GetCardSet());
    CHECK_EQ(CardSet::LEGACY, cards3.front()->GetCardSet());
    CHECK_EQ(CardSet::NAXX, cards4.front()->GetCardSet());
    CHECK_EQ(CardSet::GVG, cards5.front()->GetCardSet());
    CHECK_EQ(CardSet::BRM, cards6.front()->GetCardSet());
    CHECK_EQ(CardSet::TGT, cards7.front()->GetCardSet());
    CHECK_EQ(CardSet::LOE, cards8.front()->GetCardSet());
    CHECK_EQ(CardSet::OG, cards9.front()->GetCardSet());
    CHECK_EQ(CardSet::KARA, cards10.front()->GetCardSet());
    CHECK_EQ(CardSet::GANGS, cards11.front()->GetCardSet());
    CHECK_EQ(CardSet::UNGORO, cards12.front()->GetCardSet());
    CHECK_EQ(CardSet::ICECROWN, cards13.front()->GetCardSet());
    CHECK_EQ(CardSet::LOOTAPALOOZA, cards14.front()->GetCardSet());
    CHECK_EQ(CardSet::GILNEAS, cards15.front()->GetCardSet());
    CHECK_EQ(CardSet::BOOMSDAY, cards16.front()->GetCardSet());
    CHECK(cards17.empty());
}

TEST_CASE("[Cards] - FindCardByType")
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

    CHECK_EQ(CardType::WEAPON, cards1.front()->GetCardType());
    CHECK_EQ(CardType::HERO, cards3.front()->GetCardType());
    CHECK_EQ(CardType::HERO_POWER, cards4.front()->GetCardType());
    CHECK_EQ(CardType::ENCHANTMENT, cards5.front()->GetCardType());
    CHECK_EQ(CardType::MINION, cards7.front()->GetCardType());
    CHECK_EQ(CardType::SPELL, cards9.front()->GetCardType());
    CHECK(cards2.empty());
    CHECK(cards6.empty());
    CHECK(cards8.empty());
    CHECK(cards10.empty());
    // NOTE: PVPDR_Duels_Buckets_HonorableR, PVPDR_Duels_Buckets_IceCold,
    CHECK(!cards11.empty());
}

TEST_CASE("[Cards] - FindCardByRace")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards = instance.FindCardByRace(Race::INVALID);

    CHECK_FALSE(cards.empty());
    CHECK_NOTHROW(instance.FindCardByRace(Race::ALL));
}

TEST_CASE("[Cards] - FindCardByName")
{
    Cards& instance = Cards::GetInstance();

    const Card* card1 = instance.FindCardByName("Flame Lance");
    CHECK_EQ(card1->name, "Flame Lance");

    const Card* card2 = instance.FindCardByName("INVALID");
    CHECK_EQ(card2->name.empty(), true);
}

TEST_CASE("[Cards] - FindCardByCost")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByCost(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByCost(2, 1);

    CHECK_FALSE(cards1.empty());
    CHECK(cards2.empty());
}

TEST_CASE("[Cards] - FindCardByAttack")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByAttack(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByAttack(2, 1);

    CHECK_FALSE(cards1.empty());
    CHECK(cards2.empty());
}

TEST_CASE("[Cards] - FindCardByHealth")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardByHealth(0, 1);
    std::vector<Card*> cards2 = instance.FindCardByHealth(2, 1);

    CHECK_FALSE(cards1.empty());
    CHECK(cards2.empty());
}

TEST_CASE("[Cards] - FindCardByGameTag")
{
    Cards& instance = Cards::GetInstance();

    std::vector<GameTag> tags1;
    const std::vector<GameTag> tags2;
    tags1.emplace_back(GameTag::CANT_ATTACK);

    std::vector<Card*> cards1 = instance.FindCardByGameTag(tags1);
    std::vector<Card*> cards2 = instance.FindCardByGameTag(tags2);
    auto gameTags = cards1.front()->gameTags;

    CHECK(gameTags.find(GameTag::CANT_ATTACK) != gameTags.end());
    CHECK(cards2.empty());
}

TEST_CASE("[Cards] - GetHeroCard")
{
    Cards& instance = Cards::GetInstance();

    CHECK_EQ(instance.FindCardByID("HERO_06")->id,
             instance.GetHeroCard(CardClass::DRUID)->id);
    CHECK_EQ(instance.FindCardByID("HERO_05")->id,
             instance.GetHeroCard(CardClass::HUNTER)->id);
    CHECK_EQ(instance.FindCardByID("HERO_08")->id,
             instance.GetHeroCard(CardClass::MAGE)->id);
    CHECK_EQ(instance.FindCardByID("HERO_04")->id,
             instance.GetHeroCard(CardClass::PALADIN)->id);
    CHECK_EQ(instance.FindCardByID("HERO_09")->id,
             instance.GetHeroCard(CardClass::PRIEST)->id);
    CHECK_EQ(instance.FindCardByID("HERO_03")->id,
             instance.GetHeroCard(CardClass::ROGUE)->id);
    CHECK_EQ(instance.FindCardByID("HERO_02")->id,
             instance.GetHeroCard(CardClass::SHAMAN)->id);
    CHECK_EQ(instance.FindCardByID("HERO_07")->id,
             instance.GetHeroCard(CardClass::WARLOCK)->id);
    CHECK_EQ(instance.FindCardByID("HERO_01")->id,
             instance.GetHeroCard(CardClass::WARRIOR)->id);
    CHECK_EQ(instance.FindCardByID("HERO_10")->id,
             instance.GetHeroCard(CardClass::DEMONHUNTER)->id);
    CHECK_EQ(instance.GetHeroCard(CardClass::DEATHKNIGHT)->id, "");
}

TEST_CASE("[Cards] - GetDefaultHeroPower")
{
    Cards& instance = Cards::GetInstance();

    CHECK_EQ(instance.FindCardByID("HERO_06bp")->id,
             instance.GetDefaultHeroPower(CardClass::DRUID)->id);
    CHECK_EQ(instance.FindCardByID("HERO_05bp")->id,
             instance.GetDefaultHeroPower(CardClass::HUNTER)->id);
    CHECK_EQ(instance.FindCardByID("HERO_08bp")->id,
             instance.GetDefaultHeroPower(CardClass::MAGE)->id);
    CHECK_EQ(instance.FindCardByID("HERO_04bp")->id,
             instance.GetDefaultHeroPower(CardClass::PALADIN)->id);
    CHECK_EQ(instance.FindCardByID("HERO_09bp")->id,
             instance.GetDefaultHeroPower(CardClass::PRIEST)->id);
    CHECK_EQ(instance.FindCardByID("HERO_03bp")->id,
             instance.GetDefaultHeroPower(CardClass::ROGUE)->id);
    CHECK_EQ(instance.FindCardByID("HERO_02bp")->id,
             instance.GetDefaultHeroPower(CardClass::SHAMAN)->id);
    CHECK_EQ(instance.FindCardByID("HERO_07bp")->id,
             instance.GetDefaultHeroPower(CardClass::WARLOCK)->id);
    CHECK_EQ(instance.FindCardByID("HERO_01bp")->id,
             instance.GetDefaultHeroPower(CardClass::WARRIOR)->id);
    CHECK_EQ(instance.FindCardByID("HERO_10bp")->id,
             instance.GetDefaultHeroPower(CardClass::DEMONHUNTER)->id);
    CHECK_EQ(instance.GetDefaultHeroPower(CardClass::DEATHKNIGHT)->id, "");
}

TEST_CASE("[Cards] - FindCardBySpellDamage")
{
    Cards& instance = Cards::GetInstance();

    std::vector<Card*> cards1 = instance.FindCardBySpellPower(1, 1);
    std::vector<Card*> cards2 = instance.FindCardBySpellPower(2, 1);

    CHECK_FALSE(cards1.empty());
    CHECK(cards2.empty());
}
