#include "TestTasks.h"
#include "TestUtils/TestUtils.h"
#include "gtest/gtest.h"

#include <Enums/CardEnums.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/TaskMeta.h>

#include <future>

using namespace Hearthstonepp;

TEST(TaskAgent, NotifyAndRead)
{
    TaskAgent agent;

    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
    TaskMeta copied = TaskMeta::CopyFrom(meta);

    agent.Notify(std::move(meta));

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(copied, read);
}

TEST(TaskAgent, NotifyAndReadSide)
{
    TaskAgent agent;

    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
    TaskMeta copied = TaskMeta::CopyFrom(meta);

    agent.Notify(std::move(meta), true);

    TaskMeta read;
    agent.Read(read, true);

    EXPECT_EQ(copied, read);
}

TEST(TaskAgent, AddTaskAndRun)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    TestTask task1(TaskID::INVALID, [](Player& p1, Player&) -> MetaData {
        p1.id = 100;
        return MetaData::INVALID;
    });

    TestTask task2(TaskID::COMBAT, [](Player&, Player& p2) -> MetaData {
        p2.id = 200;
        return MetaData::COMBAT;
    });

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    TaskAgent agent;

    TaskMeta ret;
    agent.Run(ret, player1, player2, task1, task2);

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(ret, read);
    EXPECT_EQ(ret.id, +TaskID::TASK_VECTOR);

    EXPECT_EQ(player1.id, 100);
    EXPECT_EQ(player2.id, 200);

    const auto& buffer = ret.GetConstBuffer();
    auto taskTuple =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

    auto taskVector = taskTuple->vector();
    TaskMeta received1 = TaskMeta::ConvertFrom(taskVector->Get(0));
    TaskMeta received2 = TaskMeta::ConvertFrom(taskVector->Get(1));

    EXPECT_EQ(received1.id, +TaskID::INVALID);
    EXPECT_EQ(received2.id, +TaskID::COMBAT);

    auto status1 = TaskMeta::ConvertTo<FlatData::GameStatus>(received1);
    auto status2 = TaskMeta::ConvertTo<FlatData::GameStatus>(received2);

    EXPECT_EQ(status1->currentPlayer(), 100);
    EXPECT_EQ(status1->opponentPlayer(), Player::USER_INVALID);

    EXPECT_EQ(status2->currentPlayer(), 100);
    EXPECT_EQ(status2->opponentPlayer(), 200);
}

// TEST(TaskAgent, RunSingleTask)
//{
//    TaskAgent agent;
//
//    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
//    Task task(TaskID::INVALID, [&meta](Player& p1, Player& p2) -> TaskMeta {
//        p1.id = 100;
//        p2.id = 200;
//
//        return TaskMeta::CopyFrom(meta);
//    });
//
//    Deck deck;
//    Account account;
//    Player player1(&account, &deck);
//    Player player2(&account, &deck);
//
//    // with Notifying
//    TaskMeta read;
//    agent.Run(task, read, player1, player2);
//
//    TaskMeta ret;
//    agent.Read(ret);
//
//    EXPECT_EQ(meta, ret);
//    EXPECT_EQ(meta, read);
//
//    EXPECT_EQ(player1.id, 100);
//    EXPECT_EQ(player2.id, 200);
//
//    // without Notifying
//    TaskMeta read2;
//    agent.Run(task, read2, player2, player1, false);
//
//    EXPECT_EQ(meta, read2);
//    EXPECT_EQ(player2.id, 100);
//    EXPECT_EQ(player1.id, 200);
//}
//
// TEST(TaskAgent, RunMultiTask)
//{
//    auto generate = [](BYTE userID, const TaskMeta& meta) {
//        return [userID, &meta](Player& p, Player&) {
//            p.id = userID;
//            return TaskMeta::CopyFrom(meta);
//        };
//    };
//
//    auto metaEqual = [](const TaskMeta& meta, const auto& metas, size_t init,
//                        size_t size) {
//        const auto& buffer = meta.GetConstBuffer();
//        auto taskTuple =
//            flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());
//
//        auto vector = taskTuple->vector();
//        EXPECT_EQ(vector->Length(), size);
//
//        for (size_t i = 0; i < size; ++i)
//        {
//            auto idx = static_cast<flatbuffers::uoffset_t>(i);
//            TaskMeta converted = TaskMeta::ConvertFrom(vector->Get(idx));
//
//            EXPECT_EQ(metas[init + i], converted);
//        }
//    };
//
//    std::vector<Task> tasks;
//    std::vector<TaskMeta> metas;
//
//    metas.reserve(5);
//    for (BYTE i = 0; i < 5; ++i)
//    {
//        metas.emplace_back(TestUtils::GenerateRandomTaskMeta());
//        tasks.emplace_back(TaskID::INVALID, generate(i, metas[i]));
//    }
//
//    Deck deck;
//    Account account;
//    Player player1(&account, &deck);
//    Player player2(&account, &deck);
//
//    TaskAgent agent;
//
//    // without TaskID::Brief
//    TaskMeta ret;
//    agent.Run(tasks, ret, player1, player2);
//
//    TaskMeta read;
//    agent.Read(read);
//
//    EXPECT_EQ(ret, read);
//    metaEqual(ret, metas, 0, 5);
//
//    BYTE lastUserID = 4;
//    EXPECT_EQ(player1.id, lastUserID);
//
//    // with TaskID::Brief
//    tasks[2] = Task(TaskID::BRIEF, generate(2, metas[2]));
//    std::future<TaskMeta> res = std::async(std::launch::async, [&] {
//        TaskMeta ret;
//        agent.Run(tasks, ret, player1, player2);
//
//        return ret;
//    });
//
//    agent.Read(read);
//    metaEqual(read, metas, 0, 3);
//
//    agent.Read(read);
//    metaEqual(read, metas, 3, 2);
//
//    res.wait();
//    metaEqual(res.get(), metas, 0, 5);
//}
//
// TEST(TaskAgent, Clear)
//{
//    Task task(TaskID::INVALID, [](Player&, Player&) { return TaskMeta(); });
//
//    TaskAgent agent;
//    agent.Add(task);
//    agent.Clear();
//
//    Deck deck;
//    Account account;
//    Player player1(&account, &deck);
//    Player player2(&account, &deck);
//
//    TaskMeta meta;
//    agent.Run(meta, player1, player2);
//
//    const auto& buffer = meta.GetConstBuffer();
//    auto taskVector =
//        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());
//
//    size_t zero = 0;
//    size_t size = taskVector->vector()->Length();
//    EXPECT_EQ(size, zero);
//}
