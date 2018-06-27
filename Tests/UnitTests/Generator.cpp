#include "Generator.h"
#include "gtest/gtest.h"

using namespace Hearthstonepp;

namespace TestUtils
{
    void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                           const std::unique_ptr<BYTE[]>& buffer2, size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            EXPECT_EQ(buffer1[i], buffer2[i]);
        }
    }

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
}