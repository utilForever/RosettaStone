// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Tasks/TaskMeta.hpp>

#include <random>

using namespace Hearthstonepp;
using namespace TestUtils;

TEST(TaskMeta, TraitConstructors)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    const int sizeTaskID = static_cast<int>(TaskID::_size());
    const int sizeTaskStatus = static_cast<int>(TaskStatus::GAME_END);

    const TaskID randID = TaskID::_from_integral(gen() % sizeTaskID);
    const auto randMeta = static_cast<TaskStatus>(gen() % sizeTaskStatus);
    const BYTE randUser = gen() % 2;

    // Empty Trait Test
    TaskMetaTrait empty;
    EXPECT_EQ(empty.GetID(), +TaskID::INVALID);
    EXPECT_EQ(empty.GetStatus(), TaskStatus::INVALID);
    EXPECT_EQ(empty.GetUserID(), TaskMetaTrait::USER_INVALID);

    // TaskID Constructor
    TaskMetaTrait traitID(randID);
    EXPECT_EQ(traitID.GetID(), randID);
    EXPECT_EQ(traitID.GetStatus(), TaskStatus::INVALID);
    EXPECT_EQ(traitID.GetUserID(), TaskMetaTrait::USER_INVALID);

    // TaskID, Status Constructor
    TaskMetaTrait traitMeta(randID, randMeta);
    EXPECT_EQ(traitMeta.GetID(), randID);
    EXPECT_EQ(traitMeta.GetStatus(), randMeta);
    EXPECT_EQ(traitMeta.GetUserID(), TaskMetaTrait::USER_INVALID);

    // TaskID, Status, User Constructor
    TaskMetaTrait traitUser(randID, randMeta, randUser);
    EXPECT_EQ(traitUser.GetID(), randID);
    EXPECT_EQ(traitUser.GetStatus(), randMeta);
    EXPECT_EQ(traitUser.GetUserID(), randUser);

    // Copy Assignment
    TaskMetaTrait copied(traitUser);
    EXPECT_EQ(copied.GetID(), traitUser.GetID());
    EXPECT_EQ(copied.GetStatus(), traitUser.GetStatus());
    EXPECT_EQ(copied.GetUserID(), traitUser.GetUserID());
}

TEST(TaskMeta, Constructors)
{
    TaskMetaTrait trait = GenerateRandomTrait();
    SizedPtr<int> buffer = GenerateRandomBuffer();

    // Empty Constructor
    TaskMeta meta;
    EXPECT_EQ(meta.GetID(), +TaskID::INVALID);
    EXPECT_EQ(meta.GetStatus(), TaskStatus::INVALID);
    EXPECT_EQ(meta.GetUserID(), TaskMeta::USER_INVALID);
    EXPECT_FALSE(meta.HasObjects());

    // Default Constructor
    TaskMeta task(trait, buffer);
    EXPECT_EQ(trait, task);
    EXPECT_TRUE(task.HasObjects());
    EXPECT_EQ(task.GetObject<SizedPtr<int>>(), buffer);

    // Copy Constructor
    TaskMeta copied(task);
    EXPECT_EQ(trait, copied);
    EXPECT_TRUE(copied.HasObjects());
    EXPECT_EQ(copied.GetObject<SizedPtr<int>>(), buffer);

    // Copy Assignment
    meta = copied;
    EXPECT_EQ(trait, meta);
    EXPECT_TRUE(meta.HasObjects());
    EXPECT_EQ(meta.GetObject<SizedPtr<int>>(), buffer);

    // Move Constructor
    TaskMeta moved(std::move(task));
    EXPECT_EQ(trait, moved);
    EXPECT_TRUE(moved.HasObjects());
    EXPECT_EQ(moved.GetObject<SizedPtr<int>>(), buffer);

    // Move Assignment
    meta = std::move(moved);
    EXPECT_EQ(trait, meta);
    EXPECT_TRUE(meta.HasObjects());
    EXPECT_EQ(meta.GetObject<SizedPtr<int>>(), buffer);
}

TEST(TaskMeta, Object)
{
    TaskMeta empty;
    EXPECT_FALSE(empty.HasObjects());

    TaskMeta meta = GenerateRandomTaskMeta();
    EXPECT_TRUE(meta.HasObjects());

    meta.GetObject<SizedPtr<int>>()[0] = 1024;
    EXPECT_EQ(meta.GetObject<SizedPtr<int>>()[0], 1024);

    SizedPtr<int> sizedPtr = meta.MoveObject<SizedPtr<int>>();
    EXPECT_TRUE(meta.HasObjects());
    EXPECT_EQ(meta.GetObject<SizedPtr<int>>(), nullptr);

    meta.Reset();
    EXPECT_FALSE(meta.HasObjects());
}