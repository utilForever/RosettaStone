#ifndef UNITTEST_TESTUTILS_H
#define UNITTEST_TESTUTILS_H

#include "gtest/gtest.h"

#include <Cards/Card.h>
#include <Tasks/TaskMeta.h>

#include <random>

using namespace Hearthstonepp;

namespace TestUtils
{
std::size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]> &ptr,
                                 size_t maximumSize = 255);

TaskMetaTrait GenerateRandomTrait();

TaskMeta GenerateRandomTaskMeta();

void ExpectBufferEqual(const std::unique_ptr<BYTE[]> &buffer1,
                       const std::unique_ptr<BYTE[]> &buffer2,
                       std::size_t size);

void ExpectCardEqual(const Card *card1, const Card *card2);
}  // namespace TestUtils

#endif  // UNITTEST_TESTUTILS_H
