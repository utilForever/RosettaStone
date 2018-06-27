#ifndef UNITTEST_GENERATOR_H
#define UNITTEST_GENERATOR_H

#include <Syncs/AgentStructures.h>
#include <Tasks/TaskMeta.h>

#include <random>

using namespace Hearthstonepp;

namespace TestUtils
{
    size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr);

    TaskMetaTrait GenerateRandomTrait();
    TaskMeta GenerateRandomTaskMeta();

    void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                           const std::unique_ptr<BYTE[]>& buffer2, size_t size);
}

#endif //UNITTEST_GENERATOR_HPP