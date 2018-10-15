// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_UTILS_H
#define UNIT_TESTS_TEST_UTILS_H

#include "gtest/gtest.h"

#include <hspp/Cards/Card.h>
#include <hspp/Tasks/TaskMeta.h>

using namespace Hearthstonepp;

namespace TestUtils
{
struct PlayerGenerator
{
    PlayerGenerator(CardClass class1, CardClass class2);

    Account account1;
    Account account2;

    Deck deck1;
    Deck deck2;

    Player player1;
    Player player2;
};

std::size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr,
                                 size_t maximumSize = 255);

TaskMetaTrait GenerateRandomTrait();

TaskMeta GenerateRandomTaskMeta();

std::unique_ptr<Card> GenerateMinionCard(std::string &&id, size_t attack, size_t health);

std::unique_ptr<Card> ConvertCardFrom(const Card& card,
                                      const FlatData::Card* deserialized);

void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                       const std::unique_ptr<BYTE[]>& buffer2,
                       std::size_t size);

void ExpectCardEqual(const Card& card1, const Card& card2);
}  // namespace TestUtils

#endif  // UNITTEST_TESTUTILS_H
