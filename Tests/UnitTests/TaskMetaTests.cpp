#include "gtest/gtest.h"

#include <Tasks/TaskMeta.h>
#include <Tasks/TaskSerializer.h>

#include <Flatbuffers/generated/MetaData_generated.h>

#include <random>

using namespace Hearthstonepp;

void EmptyTraitTest(const TaskMeta& meta)
{
    EXPECT_EQ(meta.id, +TaskID::INVALID);
    EXPECT_EQ(meta.status, MetaData::INVALID);
    EXPECT_EQ(meta.userID, TaskMetaTrait::USER_INVALID);
}

void BufferEqualityTest(const std::unique_ptr<BYTE[]>& buffer1,
                        const std::unique_ptr<BYTE[]>& buffer2, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer1[i], buffer2[i]);
    }
}

size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<BYTE> data(0, 255);

    size_t size = data(gen);
    ptr = std::make_unique<BYTE[]>(size);
    for (size_t i = 0; i < size; ++i)
    {
        ptr[i] = data(gen);
    }

    return size;
}

TEST(TaskMeta, TraitConstructors)
{
    // Empty Trait Test
    TaskMetaTrait empty;
    EXPECT_EQ(empty.id, +TaskID::INVALID);
    EXPECT_EQ(empty.status, MetaData::INVALID);
    EXPECT_EQ(empty.userID, TaskMetaTrait::USER_INVALID);

    std::random_device rd;
    std::default_random_engine gen(rd());

    // TaskID Constructor
    TaskID randID = TaskID::_from_integral(gen() % TaskID::_size());
    TaskMetaTrait traitID(randID);
    EXPECT_EQ(traitID.id, randID);
    EXPECT_EQ(traitID.status, MetaData::INVALID);
    EXPECT_EQ(traitID.userID, TaskMetaTrait::USER_INVALID);

    int metaSize = static_cast<int>(MetaData::GAME_END);
    MetaData randMeta = static_cast<MetaData>(gen() % metaSize);

    // TaskID, Status Constructor
    TaskMetaTrait traitMeta(randID, randMeta);
    EXPECT_EQ(traitMeta.id, randID);
    EXPECT_EQ(traitMeta.status, randMeta);
    EXPECT_EQ(traitMeta.userID, TaskMetaTrait::USER_INVALID);

    // TaskID, Status, User Constructor
    BYTE randUser = gen() % 2;
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
    size_t zero = 0;

    // Empty Constructor
    TaskMeta meta;
    EmptyTraitTest(meta);
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetConstBuffer().get(), nullptr);

    std::unique_ptr<BYTE[]> buffer;
    size_t size = GenerateRandomBuffer(buffer);

    // Default Constructor
    TaskMeta task(TaskMetaTrait(), size, buffer.get());
    EXPECT_EQ(task.GetBufferSize(), size);
    EmptyTraitTest(task);
    BufferEqualityTest(task.GetConstBuffer(), buffer, size);

    // Move Constructor
    TaskMeta moved(TaskMetaTrait(), size, std::move(buffer));
    EXPECT_EQ(moved.GetBufferSize(), size);
    EmptyTraitTest(moved);
    BufferEqualityTest(moved.GetConstBuffer(), task.GetConstBuffer(), size);

    // Move Assignment
    meta = std::move(moved);
    EXPECT_EQ(meta.GetBufferSize(), size);
    EmptyTraitTest(meta);
    BufferEqualityTest(meta.GetConstBuffer(), task.GetConstBuffer(), size);
}

TEST(TaskMeta, UniquePtr)
{
    std::unique_ptr<BYTE[]> buffer;
    size_t size = GenerateRandomBuffer(buffer);
    TaskMeta meta(TaskMetaTrait(), size, buffer.get());

    // MoveBuffer
    std::unique_ptr<BYTE[]> moved = meta.MoveBuffer();
    EXPECT_EQ(meta.GetConstBuffer().get(), nullptr);
    BufferEqualityTest(buffer, moved, size);

    // reset
    meta = TaskMeta(TaskMetaTrait(), size, buffer.get());
    meta.reset();
    EXPECT_EQ(meta.GetConstBuffer().get(), nullptr);
}

TEST(TaskMeta, CopyFrom)
{
    std::unique_ptr<BYTE[]> buffer;
    size_t size = GenerateRandomBuffer(buffer);
    TaskMeta meta(TaskMetaTrait(), size, buffer.get());

    // CopyFrom
    TaskMeta copied = TaskMeta::CopyFrom(meta);
    EXPECT_EQ(meta.id, copied.id);
    EXPECT_EQ(meta.status, copied.status);
    EXPECT_EQ(meta.userID, copied.userID);
    EXPECT_EQ(meta.GetBufferSize(), copied.GetBufferSize());
    BufferEqualityTest(meta.GetConstBuffer(), copied.GetConstBuffer(), size);
}

TEST(TaskMeta, ConvertFrom)
{
    std::unique_ptr<BYTE[]> buffer;
    size_t size = GenerateRandomBuffer(buffer);

    flatbuffers::FlatBufferBuilder builder(512);
    auto trait = FlatData::TaskMetaTrait(static_cast<int>(TaskID::INVALID),
                                         static_cast<status_t>(MetaData::INVALID),
                                         TaskMeta::USER_INVALID);

    auto data = builder.CreateVector(buffer.get(), size);
    auto serialized = FlatData::CreateTaskMeta(builder, &trait, data);
    builder.Finish(serialized);

    auto deserialized = flatbuffers::GetRoot<FlatData::TaskMeta>(builder.GetBufferPointer());

    // ConvertFrom
    TaskMeta meta = TaskMeta::ConvertFrom(deserialized);
    EmptyTraitTest(meta);
    EXPECT_EQ(size, meta.GetBufferSize());
    BufferEqualityTest(meta.GetConstBuffer(), buffer, size);
}