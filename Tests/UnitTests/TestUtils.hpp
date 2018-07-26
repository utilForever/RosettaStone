#ifndef UNITTEST_GENERATOR_H
#define UNITTEST_GENERATOR_H

#include "gtest/gtest.h"

#include <Cards/Card.h>
#include <Tasks/TaskMeta.h>

#include <random>

using namespace Hearthstonepp;

namespace TestUtils
{
std::size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]> &ptr,
                                 size_t maximumSize = 255)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> data(0, 255);

    size_t size = gen() % maximumSize;
    ptr = std::make_unique<BYTE[]>(size);

    for (size_t i = 0; i < size; ++i)
    {
        ptr[i] = static_cast<BYTE>(data(gen));
    }

	return size;
}

TaskMetaTrait GenerateRandomTrait()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    int sizeTaskID = static_cast<int>(TaskID::_size());
    int sizeMetaData = static_cast<int>(MetaData::GAME_END);

    TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
    MetaData metaData = static_cast<MetaData>(gen() % sizeMetaData);
    BYTE userID = gen() % 2;

    TaskMetaTrait randomTrait(taskID, metaData, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    TaskMetaTrait trait = GenerateRandomTrait();

    std::unique_ptr<BYTE[]> ptr;
    size_t size = GenerateRandomBuffer(ptr);

    TaskMeta randomTaskMeta(trait, size, std::move(ptr));
    return randomTaskMeta;
}

std::unique_ptr<ITask*> GenerateReturnTask(const TaskMeta& meta)
{

}

void ExpectBufferEqual(const std::unique_ptr<BYTE[]> &buffer1,
                       const std::unique_ptr<BYTE[]> &buffer2, std::size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer1[i], buffer2[i]);
    }
}

void ExpectCardEqual(const Card *card1, const Card *card2)
{
    EXPECT_EQ(card1->id, card2->id);
    EXPECT_EQ(card1->rarity, card2->rarity);
    EXPECT_EQ(card1->faction, card2->faction);
    EXPECT_EQ(card1->cardSet, card2->cardSet);
    EXPECT_EQ(card1->cardClass, card2->cardClass);
    EXPECT_EQ(card1->cardType, card2->cardType);
    EXPECT_EQ(card1->race, card2->race);
    EXPECT_EQ(card1->name, card2->name);
    EXPECT_EQ(card1->text, card2->text);
    EXPECT_EQ(card1->isCollectible, card2->isCollectible);
    EXPECT_EQ(card1->cost, card2->cost);
    EXPECT_EQ(card1->mechanics, card2->mechanics);
    EXPECT_EQ(card1->playRequirements, card2->playRequirements);
    EXPECT_EQ(card1->entourages, card2->entourages);
    EXPECT_EQ(card1->maxAllowedInDeck, card2->maxAllowedInDeck);

    EXPECT_EQ(card1->attack, card2->attack);
    EXPECT_EQ(card1->health, card2->health);

    EXPECT_EQ(card1->durability, card2->durability);
}
}  // namespace TestUtils

#endif  // UNITTEST_GENERATOR_HPP
