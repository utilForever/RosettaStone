// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Commons/Utils.hpp>

#include <random>

TEST(SizedPtr, Constructor)
{
    SizedPtr<int> defaultCtor;
    EXPECT_EQ(defaultCtor.size(), 0);
    EXPECT_EQ(defaultCtor.get(), nullptr);

    constexpr std::size_t size = 255;

    SizedPtr<int> ptr1(size);
    EXPECT_EQ(ptr1.size(), size);
    EXPECT_NE(ptr1.get(), nullptr);

    int* ptr = new int[size];
    SizedPtr<int> ptr2(ptr, size);
    EXPECT_EQ(ptr2.size(), size);
    EXPECT_EQ(ptr2.get(), ptr);

    std::random_device rd;
    std::default_random_engine gen(rd());

    SizedPtr<int> sizedPtr(gen() % 1024 + 1);
    for (std::size_t i = 0; i < sizedPtr.size(); ++i)
    {
        sizedPtr[i] = gen() % 255;
    }

    // Copy constructor
    SizedPtr<int> copied(sizedPtr);
    EXPECT_EQ(sizedPtr, copied);

    // Move constructor
    SizedPtr<int> moved(std::move(copied));
    EXPECT_EQ(sizedPtr, moved);

    // Copy assignment
    copied = sizedPtr;
    EXPECT_EQ(sizedPtr, copied);

    // Move assignment
    moved = std::move(copied);
    EXPECT_EQ(sizedPtr, moved);
}

TEST(SizedPtr, Reset)
{
    SizedPtr<int> sizedPtr = TestUtils::GenerateRandomBuffer();
    EXPECT_NE(sizedPtr.size(), 0);
    EXPECT_NE(sizedPtr, nullptr);

    sizedPtr.reset();
    EXPECT_EQ(sizedPtr.size(), 0);
    EXPECT_EQ(sizedPtr, nullptr);

    constexpr std::size_t size = 10;

    int* ptr = new int[size];
    sizedPtr.reset(ptr, size);
    EXPECT_EQ(sizedPtr.size(), size);
    EXPECT_EQ(sizedPtr.get(), ptr);
}

TEST(SizedPtr, Operator)
{
    SizedPtr<int> sizedPtr = TestUtils::GenerateRandomBuffer();
    EXPECT_EQ(*sizedPtr, sizedPtr[0]);

    *sizedPtr = 10;
    EXPECT_EQ(*sizedPtr, 10);
    EXPECT_EQ(sizedPtr[0], 10);

    sizedPtr[sizedPtr.size() - 1] = 20;
    EXPECT_EQ(sizedPtr[sizedPtr.size() - 1], 20);

    EXPECT_TRUE(static_cast<bool>(sizedPtr));

    sizedPtr.reset();
    EXPECT_FALSE(static_cast<bool>(sizedPtr));
}

TEST(SizedPtr, Iterator)
{
    SizedPtr<int> sizedPtr = TestUtils::GenerateRandomBuffer();

    std::size_t idx = 0;
    for (int elem : sizedPtr)
    {
        EXPECT_EQ(elem, sizedPtr[idx++]);
    }

    idx = 0;
    for (auto iter = sizedPtr.cbegin(); iter != sizedPtr.cend(); ++iter)
    {
        EXPECT_EQ(*iter, sizedPtr[idx++]);
    }
}