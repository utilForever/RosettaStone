// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

namespace TestUtils
{
Card GenerateMinionCard(std::string&& id, int attack, int health)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::MINION);

    card.id = std::move(id);
    card.gameTags[GameTag::ATK] = attack;
    card.gameTags[GameTag::DAMAGE] = 0;
    card.gameTags[GameTag::HEALTH] = health;
    card.gameTags[GameTag::COST] = 0;

    return card;
}

Card GenerateWeaponCard(std::string&& id, int attack, int durability)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::WEAPON);

    card.id = std::move(id);
    card.gameTags[GameTag::ATK] = attack;
    card.gameTags[GameTag::DURABILITY] = durability;

    return card;
}

Card GenerateEnchantmentCard(std::string&& id)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::ENCHANTMENT);

    card.id = std::move(id);

    return card;
}

void PlayMinionCard(Player* player, Card* card)
{
    FieldZone& fieldZone = *(player->GetFieldZone());
    const std::map<GameTag, int> tags;

    const auto minion = new Minion(player, card, tags);
    fieldZone.Add(minion);
    fieldZone[minion->GetZonePosition()]->player = player;
}

void PlayWeaponCard(Player* player, Card* card)
{
    const std::map<GameTag, int> tags;

    const auto weapon = new Weapon(player, card, tags);
    player->GetHero()->AddWeapon(*weapon);
}

void PlayEnchantmentCard(Player* player, Card* card, Entity* target)
{
    GraveyardZone& graveyardZone = *(player->GetGraveyardZone());
    const std::map<GameTag, int> tags;

    const auto enchantment = new Enchantment(player, card, tags, target, -1);
    graveyardZone.Add(enchantment);
}

void ExpectCardEqual(const Card& card1, const Card& card2)
{
    EXPECT_EQ(card1.id, card2.id);
    EXPECT_EQ(card1.name, card2.name);
    EXPECT_EQ(card1.text, card2.text);
    EXPECT_EQ(card1.GetCardClass(), card2.GetCardClass());
    EXPECT_EQ(card1.GetCardSet(), card2.GetCardSet());
    EXPECT_EQ(card1.GetCardType(), card2.GetCardType());
    EXPECT_EQ(card1.GetFaction(), card2.GetFaction());
    EXPECT_EQ(card1.GetRace(), card2.GetRace());
    EXPECT_EQ(card1.GetRarity(), card2.GetRarity());
    EXPECT_EQ(card1.gameTags.at(GameTag::COLLECTIBLE),
              card2.gameTags.at(GameTag::COLLECTIBLE));
    EXPECT_EQ(card1.gameTags.at(GameTag::COST),
              card2.gameTags.at(GameTag::COST));
    EXPECT_EQ(card1.gameTags.at(GameTag::ATK), card2.gameTags.at(GameTag::ATK));
    EXPECT_EQ(card1.gameTags.at(GameTag::HEALTH),
              card2.gameTags.at(GameTag::HEALTH));
    EXPECT_EQ(card1.gameTags.at(GameTag::DURABILITY),
              card2.gameTags.at(GameTag::DURABILITY));
    EXPECT_EQ(card1.gameTags, card2.gameTags);
    EXPECT_EQ(card1.playRequirements, card2.playRequirements);
    EXPECT_EQ(card1.entourages, card2.entourages);
    EXPECT_EQ(card1.maxAllowedInDeck, card2.maxAllowedInDeck);
}
}  // namespace TestUtils
