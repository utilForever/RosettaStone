// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/PriorityQueue.hpp>
#include <Rosetta/Common/Utils.hpp>

#include <array>

TEST_CASE("[Utils] - ChooseNElements (std::array)")
{
    std::array<int*, 5> intVec{};
    intVec[0] = new int(10);
    intVec[1] = new int(20);
    intVec[2] = new int(30);
    intVec[3] = new int(40);
    intVec[4] = new int(50);

    std::vector<int*> result = ChooseNElements(intVec, 2);
    CHECK_EQ(result.size(), 2);
    CHECK_NE(*result[0], *result[1]);

    for (auto& elem : intVec)
    {
        delete elem;
    }
}

TEST_CASE("[Utils] - ChooseNElements (std::vector)")
{
    std::vector<int*> intVec;
    intVec.emplace_back(new int(10));
    intVec.emplace_back(new int(20));
    intVec.emplace_back(new int(30));
    intVec.emplace_back(new int(40));
    intVec.emplace_back(new int(50));

    std::vector<int*> result = ChooseNElements(intVec, 2);
    CHECK_EQ(result.size(), 2);
    CHECK_NE(*result[0], *result[1]);

    for (auto& elem : intVec)
    {
        delete elem;
    }
}

TEST_CASE("[Utils] - SplitSpring")
{
    const std::string str = "1 2 3";
    const std::vector<std::string> tokens = SplitString(str, " ");
    CHECK_EQ(tokens.size(), 3);
    CHECK_EQ(tokens[0], "1");
    CHECK_EQ(tokens[1], "2");
    CHECK_EQ(tokens[2], "3");
}

TEST_CASE("[PriorityQueue] - Pop empty queue throws")
{
    RosettaStone::PriorityQueue<int> queue;

    CHECK(queue.IsEmpty());
    CHECK_THROWS(queue.Pop());
}

TEST_CASE("[PriorityQueue] - Copy assignment preserves count")
{
    RosettaStone::PriorityQueue<int> source;
    source.Push(10, 2);
    source.Push(20, 1);

    RosettaStone::PriorityQueue<int> target;
    target.Push(30, 3);
    target = source;

    CHECK_EQ(target.GetCount(), 2u);
    CHECK_EQ(target.Pop(), 20);
    CHECK_EQ(target.Pop(), 10);
    CHECK(target.IsEmpty());
}

TEST_CASE("[PriorityQueue] - Move assignment transfers nodes")
{
    RosettaStone::PriorityQueue<int> source;
    source.Push(10, 2);
    source.Push(20, 1);

    RosettaStone::PriorityQueue<int> target;
    target.Push(30, 3);
    target = static_cast<RosettaStone::PriorityQueue<int>&&>(source);

    CHECK_EQ(target.GetCount(), 2u);
    CHECK_EQ(target.Pop(), 20);
    CHECK_EQ(target.Pop(), 10);
    CHECK(target.IsEmpty());
    CHECK(source.IsEmpty());
}

TEST_CASE("[PriorityQueue] - Move constructor transfers nodes")
{
    RosettaStone::PriorityQueue<int> source;
    source.Push(10, 2);
    source.Push(20, 1);

    RosettaStone::PriorityQueue<int> target(
        static_cast<RosettaStone::PriorityQueue<int>&&>(source));

    CHECK_EQ(target.GetCount(), 2u);
    CHECK_EQ(target.Pop(), 20);
    CHECK_EQ(target.Pop(), 10);
    CHECK(target.IsEmpty());
    CHECK(source.IsEmpty());
}
