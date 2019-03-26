// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_UTILS_HPP
#define UNIT_TESTS_TEST_UTILS_HPP

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Tasks/TaskMeta.hpp>

using namespace RosettaStone;

namespace TestUtils
{
SizedPtr<int> GenerateRandomBuffer(std::size_t maximumSize = 255);

TaskMetaTrait GenerateRandomTrait();

TaskMeta GenerateRandomTaskMeta();

Card GenerateMinionCard(std::string&& id, std::size_t attack, int health);

void PlayMinionCard(Player& player, Card& card);

void ExpectCardEqual(const Card& card1, const Card& card2);
}  // namespace TestUtils

#endif  // UNIT_TESTS_TEST_UTILS_HPP
