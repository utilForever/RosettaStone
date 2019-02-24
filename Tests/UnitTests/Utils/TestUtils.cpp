// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

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

    const auto sizeTaskID = static_cast<int>(TaskID::_size());
    const auto sizeTaskStatus = static_cast<int>(TaskStatus::GAME_END);

    const TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
    const auto taskStatus = static_cast<TaskStatus>(gen() % sizeTaskStatus);
    const std::size_t userID = gen() % 2;

    const TaskMetaTrait randomTrait(taskID, taskStatus, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    return TaskMeta(GenerateRandomTrait(), GenerateRandomBuffer());
}

Card GenerateMinionCard(std::string&& id, std::size_t attack,
                        std::size_t health)
{
    Card card;
    card.cardType = CardType::MINION;

    card.id = std::move(id);
    card.attack = attack;
    card.health = health;

    return card;
}

void PlayMinionCard(Player& player, Card& card)
{
    Battlefield& playerField = player.GetField();

    const auto minion = new Minion(player, card);
    const auto minionPos = playerField.FindEmptyPos().value_or(
        std::numeric_limits<std::size_t>::max());

    if (minionPos != std::numeric_limits<std::size_t>::max())
    {
        playerField.AddMinion(*minion, minionPos);
        playerField.GetMinion(minionPos)->SetOwner(player);
    }
}

void ExpectCardEqual(const Card& card1, const Card& card2)
{
    EXPECT_EQ(card1.id, card2.id);
    EXPECT_EQ(card1.rarity, card2.rarity);
    EXPECT_EQ(card1.faction, card2.faction);
    EXPECT_EQ(card1.cardSet, card2.cardSet);
    EXPECT_EQ(card1.cardClass, card2.cardClass);
    EXPECT_EQ(card1.cardType, card2.cardType);
    EXPECT_EQ(card1.race, card2.race);
    EXPECT_EQ(card1.name, card2.name);
    EXPECT_EQ(card1.text, card2.text);
    EXPECT_EQ(card1.isCollectible, card2.isCollectible);
    EXPECT_EQ(card1.cost, card2.cost);
    EXPECT_EQ(card1.mechanics, card2.mechanics);
    EXPECT_EQ(card1.playRequirements, card2.playRequirements);
    EXPECT_EQ(card1.entourages, card2.entourages);
    EXPECT_EQ(card1.maxAllowedInDeck, card2.maxAllowedInDeck);

    EXPECT_EQ(card1.attack, card2.attack);
    EXPECT_EQ(card1.health, card2.health);

    EXPECT_EQ(card1.durability, card2.durability);
}
}  // namespace TestUtils
