// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.h>
#include "gtest/gtest.h"

#include <hspp/Tasks/TaskMeta.h>
#include <hspp/Tasks/TaskSerializer.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

#include <random>

using namespace Hearthstonepp;
using namespace TestUtils;

TEST(TaskMeta, TraitConstructors)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    const int sizeTaskID = static_cast<int>(TaskID::_size());
    const int sizeMetaData = static_cast<int>(MetaData::GAME_END);

    const TaskID randID = TaskID::_from_integral(gen() % sizeTaskID);
    const auto randMeta = static_cast<MetaData>(gen() % sizeMetaData);
    const BYTE randUser = gen() % 2;

    // Empty Trait Test
    TaskMetaTrait empty;
    EXPECT_EQ(empty.id, +TaskID::INVALID);
    EXPECT_EQ(empty.status, MetaData::INVALID);
    EXPECT_EQ(empty.userID, TaskMetaTrait::USER_INVALID);

    // TaskID Constructor
    TaskMetaTrait traitID(randID);
    EXPECT_EQ(traitID.id, randID);
    EXPECT_EQ(traitID.status, MetaData::INVALID);
    EXPECT_EQ(traitID.userID, TaskMetaTrait::USER_INVALID);

    // TaskID, Status Constructor
    TaskMetaTrait traitMeta(randID, randMeta);
    EXPECT_EQ(traitMeta.id, randID);
    EXPECT_EQ(traitMeta.status, randMeta);
    EXPECT_EQ(traitMeta.userID, TaskMetaTrait::USER_INVALID);

    // TaskID, Status, User Constructor
    TaskMetaTrait traitUser(randID, randMeta, randUser);
    EXPECT_EQ(traitUser.id, randID);
    EXPECT_EQ(traitUser.status, randMeta);
    EXPECT_EQ(traitUser.userID, randUser);

    // Copy Assignment
    TaskMetaTrait copied(traitUser);
    EXPECT_EQ(copied.id, traitUser.id);
    EXPECT_EQ(copied.status, traitUser.status);
    EXPECT_EQ(copied.userID, traitUser.userID);
}

TEST(TaskMeta, Constructors)
{
    constexpr size_t zero = 0;
    std::unique_ptr<BYTE[]> buffer;
    const size_t size = GenerateRandomBuffer(buffer);
    TaskMetaTrait trait = GenerateRandomTrait();

    // Empty Constructor
    TaskMeta meta;
    EXPECT_EQ(meta.id, +TaskID::INVALID);
    EXPECT_EQ(meta.status, MetaData::INVALID);
    EXPECT_EQ(meta.userID, TaskMeta::USER_INVALID);
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetBuffer().get(), static_cast<BYTE*>(nullptr));

    // Default Constructor
    TaskMeta task(trait, size, buffer.get());
    EXPECT_EQ(trait, task);
    EXPECT_EQ(task.GetBufferSize(), size);
    ExpectBufferEqual(task.GetBuffer(), buffer, size);

    // Move Buffer
    TaskMeta moveBuffer(trait, size, std::move(buffer));
    EXPECT_EQ(trait, moveBuffer);
    EXPECT_EQ(moveBuffer.GetBufferSize(), size);
    ExpectBufferEqual(moveBuffer.GetBuffer(), task.GetBuffer(), size);

    // Move Constructor
    TaskMeta moved(std::move(moveBuffer));
    EXPECT_EQ(trait, moved);
    EXPECT_EQ(moved.GetBufferSize(), size);
    ExpectBufferEqual(moved.GetBuffer(), task.GetBuffer(), size);

    // Move Assignment
    meta = std::move(moved);
    EXPECT_EQ(trait, meta);
    EXPECT_EQ(meta.GetBufferSize(), size);
    ExpectBufferEqual(meta.GetBuffer(), task.GetBuffer(), size);
}

TEST(TaskMeta, UniquePtr)
{
    constexpr size_t zero = 0;
    std::unique_ptr<BYTE[]> buffer;
    const size_t size = GenerateRandomBuffer(buffer);

    const TaskMetaTrait trait = GenerateRandomTrait();
    TaskMeta meta(trait, size, buffer.get());

    // MoveBuffer
    const std::unique_ptr<BYTE[]> moved = meta.MoveBuffer();
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetBuffer().get(), static_cast<BYTE*>(nullptr));
    ExpectBufferEqual(buffer, moved, size);

    // reset
    meta = TaskMeta(trait, size, buffer.get());
    meta.Reset();
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetBuffer().get(), static_cast<BYTE*>(nullptr));
}

TEST(TaskMeta, CopyFrom)
{
    // CopyFrom
    TaskMeta meta = GenerateRandomTaskMeta();
    const TaskMeta copied = TaskMeta::CopyFrom(meta);
    EXPECT_EQ(meta, copied);
}

TEST(TaskMeta, ConvertFrom)
{
    TaskMeta meta = GenerateRandomTaskMeta();
    const auto& buffer = meta.GetBuffer();
    const size_t size = meta.GetBufferSize();

    flatbuffers::FlatBufferBuilder builder(512);
    auto trait = FlatData::TaskMetaTrait(static_cast<int>(meta.id),
                                         static_cast<status_t>(meta.status),
                                         meta.userID);

    const auto data = builder.CreateVector(buffer.get(), size);
    const auto serialized = FlatData::CreateTaskMeta(builder, &trait, data);
    builder.Finish(serialized);

    const auto deserialized =
        flatbuffers::GetRoot<FlatData::TaskMeta>(builder.GetBufferPointer());

    // ConvertFrom
    const TaskMeta converted = TaskMeta::ConvertFrom(deserialized);
    EXPECT_EQ(meta, converted);
}

TEST(TaskMeta, ConvertTo)
{
    TaskMeta meta = Serializer::CreateRequire(TaskID::MULLIGAN, 0);
    const auto require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(meta);

    EXPECT_EQ(meta.userID, 0);
    EXPECT_EQ(TaskID::MULLIGAN, require->required());
}
