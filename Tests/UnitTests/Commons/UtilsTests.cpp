// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.
#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Commons/Utils.hpp>

#include <random>

TEST(Box, Constructor)
{
    Box<int> defaultCtor;
    EXPECT_EQ(defaultCtor.size(), 0);
    EXPECT_EQ(defaultCtor.get(), nullptr);

    constexpr size_t size = 255;

    Box<int> box1(size);
    EXPECT_EQ(box1.size(), size);
    EXPECT_NE(box1.get(), nullptr);

    int* ptr = new int[size];
    Box<int> box2(ptr, size);
    EXPECT_EQ(box2.size(), size);
    EXPECT_EQ(box2.get(), ptr);

    std::random_device rd;
    std::default_random_engine gen(rd());

    Box<int> box(gen() % 1024);
    for (size_t i = 0; i < box.size(); ++i)
    {
        box[i] = gen() % 255;
    }

    // Copy constructor
    Box<int> copied(box);
    EXPECT_EQ(box, copied);

    // Move constructor
    Box<int> moved(std::move(copied));
    EXPECT_EQ(box, moved);

    // Copy assignment
    copied = box;
    EXPECT_EQ(box, copied);

    // Move assignment
    moved = std::move(copied);
    EXPECT_EQ(box, moved);
}

TEST(Box, Reset)
{
    Box<int> box = TestUtils::GenerateRandomBuffer();
    EXPECT_NE(box.size(), 0);
    EXPECT_NE(box, nullptr);

    box.reset();
    EXPECT_EQ(box.size(), 0);
    EXPECT_EQ(box, nullptr);

    constexpr size_t size = 10;

    int* ptr = new int[size];
    box.reset(ptr, size);
    EXPECT_EQ(box.size(), size);
    EXPECT_EQ(box.get(), ptr);
}

TEST(Box, Operator)
{
    Box<int> box = TestUtils::GenerateRandomBuffer();
    EXPECT_EQ(*box, box[0]);

    *box = 10;
    EXPECT_EQ(*box, 10);
    EXPECT_EQ(box[0], 10);

    box[box.size() - 1] = 20;
    EXPECT_EQ(box[box.size() - 1], 20);

    EXPECT_TRUE(static_cast<bool>(box));
    
    box.reset();
    EXPECT_FALSE(static_cast<bool>(box));
}

TEST(Box, Iterator)
{
    Box<int> box = TestUtils::GenerateRandomBuffer();

    size_t idx = 0;
    for (int elem : box)
    {
        EXPECT_EQ(elem, box[idx++]);
    }

    idx = 0;
    for (auto iter = box.cbegin(); iter != box.cend(); ++iter)
    {
        EXPECT_EQ(*iter, box[idx++]);
    }
}