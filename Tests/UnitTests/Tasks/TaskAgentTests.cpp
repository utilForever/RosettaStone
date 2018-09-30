#include "gtest/gtest.h"
#include <Utils/TestTasks.h>
#include <Utils/TestUtils.h>

#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/TaskMeta.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

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

TEST(TaskAgent, RunSingleTask)
{
    TaskAgent agent;

    TestTask task(TaskID::COMBAT, [](Player& p1, Player& p2) -> MetaData {
        p1.id = 100;
        p2.id = 200;

        return MetaData::COMBAT;
    });

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    // with Notifying
    TaskMeta read;
    agent.Run(read, player1, player2, task);

    TaskMeta ret;
    agent.Read(ret);

    EXPECT_EQ(read, ret);

    EXPECT_EQ(player1.id, 100);
    EXPECT_EQ(player2.id, 200);

    EXPECT_EQ(read.id, +TaskID::COMBAT);
    EXPECT_EQ(read.status, MetaData::COMBAT);

    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(read);
    EXPECT_EQ(status->currentPlayer(), 100);
    EXPECT_EQ(status->opponentPlayer(), 200);

    // without Notifying
    TaskMeta read2;
    agent.Run(read2, player2, player1, task, false);

    EXPECT_EQ(read.id, read2.id);
    EXPECT_EQ(read.status, read2.status);

    EXPECT_EQ(player2.id, 100);
    EXPECT_EQ(player1.id, 200);
}

TEST(TaskAgent, RunMultiTasks)
{
    TestTask task1(TaskID::SWAP, [](Player& p1, Player&) -> MetaData {
        p1.id = 100;
        return MetaData::SWAP;
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
    agent.RunMulti(ret, player1, player2, task1, task2);

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(ret, read);
    EXPECT_EQ(ret.id, +TaskID::TASK_VECTOR);

    EXPECT_EQ(player1.id, 100);
    EXPECT_EQ(player2.id, 200);

    const auto& buffer = ret.GetBuffer();
    auto taskTuple =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

    auto taskVector = taskTuple->vector();
    TaskMeta received1 = TaskMeta::ConvertFrom(taskVector->Get(0));
    TaskMeta received2 = TaskMeta::ConvertFrom(taskVector->Get(1));

    EXPECT_EQ(received1.id, +TaskID::SWAP);
    EXPECT_EQ(received1.status, MetaData::SWAP);

    EXPECT_EQ(received2.id, +TaskID::COMBAT);
    EXPECT_EQ(received2.status, MetaData::COMBAT);

    auto status1 = TaskMeta::ConvertTo<FlatData::GameStatus>(received1);
    auto status2 = TaskMeta::ConvertTo<FlatData::GameStatus>(received2);

    EXPECT_EQ(status1->currentPlayer(), 100);
    EXPECT_EQ(status1->opponentPlayer(), Player::USER_INVALID);

    EXPECT_EQ(status2->currentPlayer(), 100);
    EXPECT_EQ(status2->opponentPlayer(), 200);
}

TEST(TaskAgent, RunMultiTaskWithBrief)
{
    std::vector<TestTask> tasks;
    std::vector<TaskMetaTrait> traits;

    auto generate = [](const TaskMetaTrait& trait) -> TestTask {
        return TestTask(trait.id,
                        [status = trait.status, userID = trait.userID](
                            Player& p, Player&) -> MetaData {
                            p.id = userID;
                            return status;
                        });
    };

    auto check = [&traits](const TaskMeta& meta) {
        auto metas = TaskMeta::ConvertTo<FlatData::TaskMetaVector>(meta);
        auto vec = metas->vector();

        constexpr size_t size = 5;
        EXPECT_EQ(vec->Length(), size);

        for (size_t i = 0; i < 5; ++i)
        {
            auto idx = static_cast<flatbuffers::uoffset_t>(i);

            TaskMeta converted = TaskMeta::ConvertFrom(vec->Get(idx));
            EXPECT_EQ(converted.id, traits[i].id);
            EXPECT_EQ(converted.userID, traits[i].userID);

            if (converted.status == MetaData::BRIEF_EXPIRED)
            {
                EXPECT_EQ(traits[i].status == MetaData::BRIEF ||
                              traits[i].status == MetaData::BRIEF_EXPIRED,
                          true);
            }
            else
            {
                EXPECT_EQ(converted.status, traits[i].status);

                auto status =
                    TaskMeta::ConvertTo<FlatData::GameStatus>(converted);
                EXPECT_EQ(status->currentPlayer(), traits[i].userID);
            }
        }
    };

    traits.reserve(5);
    for (size_t i = 0; i < 5; ++i)
    {
        traits.emplace_back(TestUtils::GenerateRandomTrait());
        if (traits[i].id == +TaskID::BRIEF)
        {
            traits[i].id = TaskID::INVALID;
        }

        tasks.emplace_back(generate(traits[i]));
    }

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    TaskAgent agent;

    // without TaskID::Brief
    TaskMeta ret;
    agent.RunMulti(ret, player1, player2, tasks[0], tasks[1], tasks[2],
                   tasks[3], tasks[4]);

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(ret, read);
    check(ret);

    // with TaskID::Brief
    traits[2] = TaskMetaTrait(TaskID::BRIEF, MetaData::BRIEF, 100);
    tasks[2] = generate(traits[2]);

    std::future<TaskMeta> res = std::async(std::launch::async, [&] {
        TaskMeta ret;
        agent.RunMulti(ret, player1, player2, tasks[0], tasks[1], tasks[2],
                       tasks[3], tasks[4]);
        return ret;
    });

    agent.Read(read);
    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(read);

    EXPECT_EQ(read.id, +TaskID::BRIEF);
    EXPECT_EQ(read.status, MetaData::BRIEF);
    EXPECT_EQ(read.userID, 100);

    EXPECT_EQ(status->currentPlayer(), 100);

    agent.Read(read);
    check(read);
    check(res.get());
}
