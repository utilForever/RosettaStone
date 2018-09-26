#include "gtest/gtest.h"

#include <Utils/TestUtils.h>

#include <Tasks/TaskMeta.h>
#include <Tasks/TaskSerializer.h>

#include <Flatbuffers/generated/FlatData_generated.h>

#include <random>

using namespace Hearthstonepp;

TEST(TaskMeta, TraitConstructors)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    int sizeTaskID = static_cast<int>(TaskID::_size());
    int sizeMetaData = static_cast<int>(MetaData::GAME_END);

    TaskID randID = TaskID::_from_integral(gen() % sizeTaskID);
    MetaData randMeta = static_cast<MetaData>(gen() % sizeMetaData);
    BYTE randUser = gen() % 2;

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
    size_t size = TestUtils::GenerateRandomBuffer(buffer);
    TaskMetaTrait trait = TestUtils::GenerateRandomTrait();

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
    TestUtils::ExpectBufferEqual(task.GetBuffer(), buffer, size);

    // Move Buffer
    TaskMeta moveBuffer(trait, size, std::move(buffer));
    EXPECT_EQ(trait, moveBuffer);
    EXPECT_EQ(moveBuffer.GetBufferSize(), size);
    TestUtils::ExpectBufferEqual(moveBuffer.GetBuffer(), task.GetBuffer(),
                                 size);

    // Move Constructor
    TaskMeta moved(std::move(moveBuffer));
    EXPECT_EQ(trait, moved);
    EXPECT_EQ(moved.GetBufferSize(), size);
    TestUtils::ExpectBufferEqual(moved.GetBuffer(), task.GetBuffer(), size);

    // Move Assignment
    meta = std::move(moved);
    EXPECT_EQ(trait, meta);
    EXPECT_EQ(meta.GetBufferSize(), size);
    TestUtils::ExpectBufferEqual(meta.GetBuffer(), task.GetBuffer(),
                                 size);
}

TEST(TaskMeta, UniquePtr)
{
    constexpr size_t zero = 0;
    std::unique_ptr<BYTE[]> buffer;
    size_t size = TestUtils::GenerateRandomBuffer(buffer);

    TaskMetaTrait trait = TestUtils::GenerateRandomTrait();
    TaskMeta meta(trait, size, buffer.get());

    // MoveBuffer
    std::unique_ptr<BYTE[]> moved = meta.MoveBuffer();
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetBuffer().get(), static_cast<BYTE*>(nullptr));
    TestUtils::ExpectBufferEqual(buffer, moved, size);

    // reset
    meta = TaskMeta(trait, size, buffer.get());
    meta.Reset();
    EXPECT_EQ(meta.GetBufferSize(), zero);
    EXPECT_EQ(meta.GetBuffer().get(), static_cast<BYTE*>(nullptr));
}

TEST(TaskMeta, CopyFrom)
{
    // CopyFrom
    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
    TaskMeta copied = TaskMeta::CopyFrom(meta);
    EXPECT_EQ(meta, copied);
}

TEST(TaskMeta, ConvertFrom)
{
    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
    const auto& buffer = meta.GetBuffer();
    size_t size = meta.GetBufferSize();

    flatbuffers::FlatBufferBuilder builder(512);
    auto trait = FlatData::TaskMetaTrait(static_cast<int>(meta.id),
                                         static_cast<status_t>(meta.status),
                                         meta.userID);

    auto data = builder.CreateVector(buffer.get(), size);
    auto serialized = FlatData::CreateTaskMeta(builder, &trait, data);
    builder.Finish(serialized);

    auto deserialized =
        flatbuffers::GetRoot<FlatData::TaskMeta>(builder.GetBufferPointer());

    // ConvertFrom
    TaskMeta converted = TaskMeta::ConvertFrom(deserialized);
    EXPECT_EQ(meta, converted);
}

TEST(TaskMeta, ConvertTo)
{
    TaskMeta meta = Serializer::CreateRequire(TaskID::MULLIGAN, 0);
    auto require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(meta);

    EXPECT_EQ(meta.userID, 0);
    EXPECT_EQ(TaskID::MULLIGAN, require->required());
}
