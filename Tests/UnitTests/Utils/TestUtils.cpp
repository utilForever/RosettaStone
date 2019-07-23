// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Models/Enchantment.hpp>

#include <random>

namespace TestUtils
{
SizedPtr<int> GenerateRandomBuffer(std::size_t maximumSize)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    SizedPtr<int> sizedPtr(gen() % maximumSize + 1);
    for (std::size_t i = 0; i < sizedPtr.size(); ++i)
    {
        sizedPtr[i] = gen() % 255;
    }

    return sizedPtr;
}

TaskMetaTrait GenerateRandomTrait()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    const auto sizeTaskID = static_cast<int>(TaskID::NUM_TASK_ID);
    const auto sizeTaskStatus = static_cast<int>(TaskStatus::NUM_TASK_STATUS);

    const TaskID taskID = static_cast<TaskID>(gen() % sizeTaskID);
    const auto taskStatus = static_cast<TaskStatus>(gen() % sizeTaskStatus);
    const std::size_t userID = gen() % 2;

    const TaskMetaTrait randomTrait(taskID, taskStatus, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    return TaskMeta(GenerateRandomTrait(), GenerateRandomBuffer());
}

Card GenerateMinionCard(std::string&& id, int attack, int health)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::MINION);

    card.id = std::move(id);
    card.gameTags[GameTag::ATK] = attack;
    card.gameTags[GameTag::DAMAGE] = 0;
    card.gameTags[GameTag::HEALTH] = health;

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

void PlayMinionCard(Player& player, Card* card)
{
    FieldZone& fieldZone = player.GetFieldZone();
    const std::map<GameTag, int> tags;

    const auto minion = new Minion(player, card, tags);
    fieldZone.Add(*minion);
    fieldZone[minion->GetZonePosition()]->owner = &player;
}

void PlayWeaponCard(Player& player, Card* card)
{
    const std::map<GameTag, int> tags;

    const auto weapon = new Weapon(player, card, tags);
    player.GetHero()->AddWeapon(*weapon);
}

void PlayEnchantmentCard(Player& player, Card* card, Entity* target)
{
    GraveyardZone& graveyardZone = player.GetGraveyardZone();
    const std::map<GameTag, int> tags;

    const auto enchantment = new Enchantment(player, card, tags, target);
    graveyardZone.Add(*enchantment);
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
