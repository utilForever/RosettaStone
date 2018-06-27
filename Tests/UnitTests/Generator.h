#ifndef UNITTEST_GENERATOR_H
#define UNITTEST_GENERATOR_H

#include <Tasks/TaskMeta.h>

#include <random>

using namespace Hearthstonepp;

namespace TestUtils
{
    void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                           const std::unique_ptr<BYTE[]>& buffer2, size_t size);

    size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr);

    TaskMetaTrait GenerateRandomTrait();
    TaskMeta GenerateRandomTaskMeta();
}



#endif //UNITTEST_GENERATOR_HPP