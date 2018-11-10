// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Cards/Cards.h>
#include <hspp/Enums/CardEnums.h>

using namespace Hearthstonepp;

TEST(TestCards, Singleton)
{
    Cards* cards = Cards::GetInstance();

    EXPECT_EQ(cards, Cards::GetInstance());
}

TEST(TestCards, GetAllCards)
{
    const std::vector<Card> cards1 = Cards::GetInstance()->GetAllCards();
    ASSERT_FALSE(cards1.empty());
    EXPECT_EQ(static_cast<int>(cards1.size()), 5216);
}

TEST(TestCards, FindCardByID)
{
    const Card card1 = Cards::GetInstance()->FindCardByID("AT_001");
    const Card card2 = Cards::GetInstance()->FindCardByID("");

    EXPECT_EQ(card1.id, "AT_001");
    EXPECT_EQ(card2.id, "");
}

TEST(TestCards, FindCardByRarity)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByRarity(+Rarity::COMMON);
    std::vector<Card> cards2 = cards->FindCardByRarity(+Rarity::RARE);
    std::vector<Card> cards3 = cards->FindCardByRarity(+Rarity::EPIC);
    std::vector<Card> cards4 = cards->FindCardByRarity(+Rarity::LEGENDARY);
    std::vector<Card> cards5 = cards->FindCardByRarity(+Rarity::FREE);
    std::vector<Card> cards6 = cards->FindCardByRarity(+Rarity::INVALID);
    std::vector<Card> cards7 = cards->FindCardByRarity(+Rarity::UNKNOWN_6);

    EXPECT_EQ(+Rarity::COMMON, cards1.front().rarity);
    EXPECT_EQ(+Rarity::RARE, cards2.front().rarity);
    EXPECT_EQ(+Rarity::EPIC, cards3.front().rarity);
    EXPECT_EQ(+Rarity::LEGENDARY, cards4.front().rarity);
    EXPECT_EQ(+Rarity::FREE, cards5.front().rarity);
    EXPECT_TRUE(cards6.empty());
    EXPECT_TRUE(cards7.empty());
}

TEST(TestCards, FindCardByClass)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByClass(+CardClass::DEATHKNIGHT);
    std::vector<Card> cards2 = cards->FindCardByClass(+CardClass::DREAM);
    std::vector<Card> cards3 = cards->FindCardByClass(+CardClass::DRUID);
    std::vector<Card> cards4 = cards->FindCardByClass(+CardClass::HUNTER);
    std::vector<Card> cards5 = cards->FindCardByClass(+CardClass::MAGE);
    std::vector<Card> cards6 = cards->FindCardByClass(+CardClass::NEUTRAL);
    std::vector<Card> cards7 = cards->FindCardByClass(+CardClass::PALADIN);
    std::vector<Card> cards8 = cards->FindCardByClass(+CardClass::PRIEST);
    std::vector<Card> cards9 = cards->FindCardByClass(+CardClass::INVALID);

    EXPECT_EQ(+CardClass::DEATHKNIGHT, cards1.front().cardClass);
    EXPECT_EQ(+CardClass::DREAM, cards2.front().cardClass);
    EXPECT_EQ(+CardClass::DRUID, cards3.front().cardClass);
    EXPECT_EQ(+CardClass::HUNTER, cards4.front().cardClass);
    EXPECT_EQ(+CardClass::MAGE, cards5.front().cardClass);
    EXPECT_EQ(+CardClass::NEUTRAL, cards6.front().cardClass);
    EXPECT_EQ(+CardClass::PALADIN, cards7.front().cardClass);
    EXPECT_EQ(+CardClass::PRIEST, cards8.front().cardClass);
    EXPECT_TRUE(cards9.empty());
}

TEST(TestCards, FindCardBySet)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardBySet(+CardSet::CORE);
    std::vector<Card> cards2 = cards->FindCardBySet(+CardSet::EXPERT1);
    std::vector<Card> cards3 = cards->FindCardBySet(+CardSet::HOF);
    std::vector<Card> cards4 = cards->FindCardBySet(+CardSet::NAXX);
    std::vector<Card> cards5 = cards->FindCardBySet(+CardSet::GVG);
    std::vector<Card> cards6 = cards->FindCardBySet(+CardSet::BRM);
    std::vector<Card> cards7 = cards->FindCardBySet(+CardSet::TGT);
    std::vector<Card> cards8 = cards->FindCardBySet(+CardSet::LOE);
    std::vector<Card> cards9 = cards->FindCardBySet(+CardSet::OG);
    std::vector<Card> cards10 = cards->FindCardBySet(+CardSet::KARA);
    std::vector<Card> cards11 = cards->FindCardBySet(+CardSet::GANGS);
    std::vector<Card> cards12 = cards->FindCardBySet(+CardSet::UNGORO);
    std::vector<Card> cards13 = cards->FindCardBySet(+CardSet::ICECROWN);
    std::vector<Card> cards14 = cards->FindCardBySet(+CardSet::LOOTAPALOOZA);
    std::vector<Card> cards15 = cards->FindCardBySet(+CardSet::GILNEAS);
    std::vector<Card> cards16 = cards->FindCardBySet(+CardSet::BOOMSDAY);
    std::vector<Card> cards17 = cards->FindCardBySet(+CardSet::INVALID);

    EXPECT_EQ(+CardSet::CORE, cards1.front().cardSet);
    EXPECT_EQ(+CardSet::EXPERT1, cards2.front().cardSet);
    EXPECT_EQ(+CardSet::HOF, cards3.front().cardSet);
    EXPECT_EQ(+CardSet::NAXX, cards4.front().cardSet);
    EXPECT_EQ(+CardSet::GVG, cards5.front().cardSet);
    EXPECT_EQ(+CardSet::BRM, cards6.front().cardSet);
    EXPECT_EQ(+CardSet::TGT, cards7.front().cardSet);
    EXPECT_EQ(+CardSet::LOE, cards8.front().cardSet);
    EXPECT_EQ(+CardSet::OG, cards9.front().cardSet);
    EXPECT_EQ(+CardSet::KARA, cards10.front().cardSet);
    EXPECT_EQ(+CardSet::GANGS, cards11.front().cardSet);
    EXPECT_EQ(+CardSet::UNGORO, cards12.front().cardSet);
    EXPECT_EQ(+CardSet::ICECROWN, cards13.front().cardSet);
    EXPECT_EQ(+CardSet::LOOTAPALOOZA, cards14.front().cardSet);
    EXPECT_EQ(+CardSet::GILNEAS, cards15.front().cardSet);
    EXPECT_EQ(+CardSet::BOOMSDAY, cards16.front().cardSet);
    EXPECT_TRUE(cards17.empty());
}

TEST(TestCards, FindCardByType)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByType(+CardType::WEAPON);
    std::vector<Card> cards2 = cards->FindCardByType(+CardType::GAME);
    std::vector<Card> cards3 = cards->FindCardByType(+CardType::HERO);
    std::vector<Card> cards4 = cards->FindCardByType(+CardType::HERO_POWER);
    std::vector<Card> cards5 = cards->FindCardByType(+CardType::ENCHANTMENT);
    std::vector<Card> cards6 = cards->FindCardByType(+CardType::ITEM);
    std::vector<Card> cards7 = cards->FindCardByType(+CardType::MINION);
    std::vector<Card> cards8 = cards->FindCardByType(+CardType::PLAYER);
    std::vector<Card> cards9 = cards->FindCardByType(+CardType::SPELL);
    std::vector<Card> cards10 = cards->FindCardByType(+CardType::TOKEN);
    std::vector<Card> cards11 = cards->FindCardByType(+CardType::INVALID);

    EXPECT_EQ(+CardType::WEAPON, cards1.front().cardType);
    EXPECT_EQ(+CardType::HERO, cards3.front().cardType);
    EXPECT_EQ(+CardType::HERO_POWER, cards4.front().cardType);
    EXPECT_EQ(+CardType::ENCHANTMENT, cards5.front().cardType);
    EXPECT_EQ(+CardType::MINION, cards7.front().cardType);
    EXPECT_EQ(+CardType::SPELL, cards9.front().cardType);
    EXPECT_TRUE(cards2.empty());
    EXPECT_TRUE(cards6.empty());
    EXPECT_TRUE(cards8.empty());
    EXPECT_TRUE(cards10.empty());
    EXPECT_TRUE(cards11.empty());
}

TEST(TestCards, FindCardByRace)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByRace(+Race::INVALID);
    EXPECT_FALSE(cards1.empty());
    EXPECT_NO_THROW(cards->FindCardByRace(+Race::ALL));
}

TEST(TestCards, FindCardByName)
{
    Cards* cards = Cards::GetInstance();
    const Card card1 = cards->FindCardByName("Flame Lance");
    EXPECT_EQ("Flame Lance", card1.name);
}

TEST(TestCards, FindCardByCost)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByCost(0, 1);
    std::vector<Card> cards2 = cards->FindCardByCost(2, 1);
    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByAttack)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByAttack(0, 1);
    std::vector<Card> cards2 = cards->FindCardByAttack(2, 1);
    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByHealth)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardByHealth(0, 1);
    std::vector<Card> cards2 = cards->FindCardByHealth(2, 1);
    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, FindCardByMechanics)
{
    Cards* cards = Cards::GetInstance();
    std::vector<GameTag> tags1;
    const std::vector<GameTag> tags2;

    tags1.emplace_back(GameTag::CANT_ATTACK);
    std::vector<Card> cards1 = cards->FindCardByMechanics(tags1);
    std::vector<Card> cards2 = cards->FindCardByMechanics(tags2);

    auto cardTags = cards1.front().mechanics;
    EXPECT_TRUE(std::find(cardTags.begin(), cardTags.end(),
                          +GameTag::CANT_ATTACK) != cardTags.end());
    EXPECT_TRUE(cards2.empty());
}

TEST(TestCards, GetHeroCard)
{
    Cards* cards = Cards::GetInstance();
    EXPECT_EQ(cards->FindCardByID("HERO_06").id,
              cards->GetHeroCard(CardClass::DRUID).id);
    EXPECT_EQ(cards->FindCardByID("HERO_05").id,
              cards->GetHeroCard(CardClass::HUNTER).id);
    EXPECT_EQ(cards->FindCardByID("HERO_08").id,
              cards->GetHeroCard(CardClass::MAGE).id);
    EXPECT_EQ(cards->FindCardByID("HERO_04").id,
              cards->GetHeroCard(CardClass::PALADIN).id);
    EXPECT_EQ(cards->FindCardByID("HERO_09").id,
              cards->GetHeroCard(CardClass::PRIEST).id);
    EXPECT_EQ(cards->FindCardByID("HERO_03").id,
              cards->GetHeroCard(CardClass::ROGUE).id);
    EXPECT_EQ(cards->FindCardByID("HERO_02").id,
              cards->GetHeroCard(CardClass::SHAMAN).id);
    EXPECT_EQ(cards->FindCardByID("HERO_07").id,
              cards->GetHeroCard(CardClass::WARLOCK).id);
    EXPECT_EQ(cards->FindCardByID("HERO_01").id,
              cards->GetHeroCard(CardClass::WARRIOR).id);
    EXPECT_EQ(cards->GetHeroCard(CardClass::DEATHKNIGHT).id, "");
}

TEST(TestCards, GetDefaultHeroPower)
{
    Cards* cards = Cards::GetInstance();
    EXPECT_EQ(cards->FindCardByID("CS2_017").id,
              cards->GetDefaultHeroPower(CardClass::DRUID).id);
    EXPECT_EQ(cards->FindCardByID("DS1h_292").id,
              cards->GetDefaultHeroPower(CardClass::HUNTER).id);
    EXPECT_EQ(cards->FindCardByID("CS2_034").id,
              cards->GetDefaultHeroPower(CardClass::MAGE).id);
    EXPECT_EQ(cards->FindCardByID("CS2_101").id,
              cards->GetDefaultHeroPower(CardClass::PALADIN).id);
    EXPECT_EQ(cards->FindCardByID("CS1h_001").id,
              cards->GetDefaultHeroPower(CardClass::PRIEST).id);
    EXPECT_EQ(cards->FindCardByID("CS2_083b").id,
              cards->GetDefaultHeroPower(CardClass::ROGUE).id);
    EXPECT_EQ(cards->FindCardByID("CS2_049").id,
              cards->GetDefaultHeroPower(CardClass::SHAMAN).id);
    EXPECT_EQ(cards->FindCardByID("CS2_056").id,
              cards->GetDefaultHeroPower(CardClass::WARLOCK).id);
    EXPECT_EQ(cards->FindCardByID("CS2_102").id,
              cards->GetDefaultHeroPower(CardClass::WARRIOR).id);
    EXPECT_EQ(cards->GetDefaultHeroPower(CardClass::DEATHKNIGHT).id, "");
}

TEST(TestCards, FindCardBySpellDamage)
{
    Cards* cards = Cards::GetInstance();
    std::vector<Card> cards1 = cards->FindCardBySpellDamage(1, 1);
    std::vector<Card> cards2 = cards->FindCardBySpellDamage(2, 1);
    EXPECT_FALSE(cards1.empty());
    EXPECT_TRUE(cards2.empty());
}
