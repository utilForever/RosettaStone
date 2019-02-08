// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_UTILS_HPP
#define UNIT_TESTS_TEST_UTILS_HPP

#include <hspp/Cards/Card.hpp>
#include <hspp/Commons/Utils.hpp>
#include <hspp/Tasks/TaskMeta.hpp>

using namespace Hearthstonepp;

namespace TestUtils
{
SizedPtr<int> GenerateRandomBuffer(size_t maximumSize = 255);

TaskMetaTrait GenerateRandomTrait();

TaskMeta GenerateRandomTaskMeta();

Card GenerateMinionCard(std::string&& id, size_t attack, size_t health);

void PlayMinionCard(Player& player, Card& card);

void ExpectCardEqual(const Card& card1, const Card& card2);
}  // namespace TestUtils

#endif  // UNIT_TESTS_TEST_UTILS_HPP
