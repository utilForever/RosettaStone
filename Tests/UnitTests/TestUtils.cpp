#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Cards/Cards.h>

using namespace Hearthstonepp;

namespace TestUtils
{
    size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr)
    {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> data(0, 255);

        size_t size = data(gen);
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

	void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                           const std::unique_ptr<BYTE[]>& buffer2, size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            EXPECT_EQ(buffer1[i], buffer2[i]);
        }
    }



	void ExpectCardEqual(const Card* card1, const Card* card2)
	{
        bool equal = card1->id == card2->id && card1->rarity == card2->rarity &&
					 card1->faction == card2->faction &&
                     card1->cardSet == card2->cardSet &&
                     card1->cardClass == card2->cardClass &&
                     card1->cardType == card2->cardType &&
                     card1->race == card2->race && card1->name == card2->name &&
                     card1->text == card2->text &&
                     card1->isCollectible == card2->isCollectible &&
                     card1->cost == card2->cost &&
                     card1->mechanics == card2->mechanics &&
                     card1->maxAllowedInDeck == card2->maxAllowedInDeck; 

		EXPECT_EQ(equal, true);
	}
}