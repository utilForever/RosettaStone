// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Commons/Macros.hpp>

#include <random>

namespace TestUtils
{
Box<int> GenerateRandomBuffer(size_t maximumSize)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    Box<int> box(gen() % maximumSize + 1);
    for (size_t i = 0; i < box.size(); ++i)
    {
        box[i] = gen() % 255;
    }

    return std::move(box);
}

TaskMetaTrait GenerateRandomTrait()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    const auto sizeTaskID = static_cast<int>(TaskID::_size());
    const auto sizeTaskStatus = static_cast<int>(TaskStatus::GAME_END);

    const TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
    const auto taskStatus = static_cast<TaskStatus>(gen() % sizeTaskStatus);
    const BYTE userID = gen() % 2;

    const TaskMetaTrait randomTrait(taskID, taskStatus, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    return TaskMeta(GenerateRandomTrait(), GenerateRandomBuffer());
}

Card GenerateMinionCard(std::string&& id, size_t attack, size_t health)
{
    Card card;
    card.cardType = CardType::MINION;

    card.id = std::move(id);
    card.attack = attack;
    card.health = health;

    return card;
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
