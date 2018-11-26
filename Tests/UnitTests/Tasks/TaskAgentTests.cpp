// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestTasks.h>
#include <Utils/TestUtils.h>
#include "gtest/gtest.h"

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/TaskMeta.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

#include <future>

using namespace Hearthstonepp;
using namespace TestUtils;

TEST(TaskAgent, NotifyAndRead)
{
    TaskAgent agent;

    TaskMeta meta = GenerateRandomTaskMeta();
    TaskMeta copied = TaskMeta::CopyFrom(meta);

    agent.Notify(std::move(meta));

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(copied, read);
}

TEST(TaskAgent, NotifyAndReadSide)
{
    TaskAgent agent;

    TaskMeta meta = GenerateRandomTaskMeta();
    TaskMeta copied = TaskMeta::CopyFrom(meta);

    agent.Notify(std::move(meta), true);

    TaskMeta read;
    agent.Read(read, true);

    EXPECT_EQ(copied, read);
}

TEST(TaskAgent, RunSingleTask)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    TestTask task(TaskID::COMBAT, [](Player& p) -> MetaData {
        p.SetID(100);
        p.GetOpponent().SetID(200);

        return MetaData::COMBAT;
    });

    // with Notifying
    TaskMeta read;
    taskAgent.Run(read, agent.GetPlayer1(), task);

    TaskMeta ret;
    taskAgent.Read(ret);

    EXPECT_EQ(read, ret);

    EXPECT_EQ(agent.GetPlayer1().GetID(), 100);
    EXPECT_EQ(agent.GetPlayer2().GetID(), 200);

    EXPECT_EQ(read.GetID(), +TaskID::COMBAT);
    EXPECT_EQ(read.GetStatus(), MetaData::COMBAT);

    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(read);
    EXPECT_EQ(status->currentPlayer(), 100);
    EXPECT_EQ(status->opponentPlayer(), 200);

    // without Notifying
    TaskMeta read2;
    taskAgent.Run(read2, agent.GetPlayer2(), task, false);

    EXPECT_EQ(read.GetID(), read2.GetID());
    EXPECT_EQ(read.GetStatus(), read2.GetStatus());

    EXPECT_EQ(agent.GetPlayer1().GetID(), 200);
    EXPECT_EQ(agent.GetPlayer2().GetID(), 100);
}

TEST(TaskAgent, RunMultiTasks)
{
    TestTask task1(TaskID::SWAP, [](Player& p) -> MetaData {
        p.SetID(100);
        return MetaData::SWAP;
    });

    TestTask task2(TaskID::COMBAT, [](Player& p) -> MetaData {
        p.GetOpponent().SetID(200);
        return MetaData::COMBAT;
    });

    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    TaskMeta ret;
    taskAgent.RunMulti(ret, agent.GetPlayer1(), task1, task2);

    TaskMeta read;
    taskAgent.Read(read);

    EXPECT_EQ(ret, read);
    EXPECT_EQ(ret.GetID(), +TaskID::TASK_VECTOR);

    EXPECT_EQ(agent.GetPlayer1().GetID(), 100);
    EXPECT_EQ(agent.GetPlayer2().GetID(), 200);

    const auto& buffer = ret.GetBuffer();
    const auto taskTuple =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

    const auto taskVector = taskTuple->vector();
    TaskMeta received1 = TaskMeta::ConvertFrom(taskVector->Get(0));
    TaskMeta received2 = TaskMeta::ConvertFrom(taskVector->Get(1));

    EXPECT_EQ(received1.GetID(), +TaskID::SWAP);
    EXPECT_EQ(received1.GetStatus(), MetaData::SWAP);

    EXPECT_EQ(received2.GetID(), +TaskID::COMBAT);
    EXPECT_EQ(received2.GetStatus(), MetaData::COMBAT);

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

    const auto generate = [](const TaskMetaTrait& trait) -> TestTask {
        return TestTask(trait.GetID(),
                        [status = trait.GetStatus(),
                         userID = trait.GetUserID()](Player& p) -> MetaData {
                            p.SetID(userID);
                            return status;
                        });
    };

    const auto check = [&traits](const TaskMeta& meta) {
        const auto metas = TaskMeta::ConvertTo<FlatData::TaskMetaVector>(meta);
        auto vec = metas->vector();

        constexpr size_t size = 5;
        EXPECT_EQ(vec->Length(), size);

        for (size_t i = 0; i < 5; ++i)
        {
            const auto idx = static_cast<flatbuffers::uoffset_t>(i);

            TaskMeta converted = TaskMeta::ConvertFrom(vec->Get(idx));
            EXPECT_EQ(converted.GetID(), traits[i].GetID());
            EXPECT_EQ(converted.GetUserID(), traits[i].GetUserID());

            if (converted.GetStatus() == MetaData::BRIEF_EXPIRED)
            {
                EXPECT_EQ(traits[i].GetStatus() == MetaData::BRIEF ||
                              traits[i].GetStatus() == MetaData::BRIEF_EXPIRED,
                          true);
            }
            else
            {
                EXPECT_EQ(converted.GetStatus(), traits[i].GetStatus());

                auto status =
                    TaskMeta::ConvertTo<FlatData::GameStatus>(converted);
                EXPECT_EQ(status->currentPlayer(), traits[i].GetUserID());
            }
        }
    };

    traits.reserve(5);
    for (size_t i = 0; i < 5; ++i)
    {
        traits.emplace_back(GenerateRandomTrait());
        if (traits[i].GetID() == +TaskID::BRIEF)
        {
            traits[i].SetID(TaskID::INVALID);
        }

        tasks.emplace_back(generate(traits[i]));
    }

    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    // without TaskID::Brief
    TaskMeta ret;
    taskAgent.RunMulti(ret, agent.GetPlayer1(), tasks[0], tasks[1], tasks[2],
                       tasks[3], tasks[4]);

    TaskMeta read;
    taskAgent.Read(read);

    EXPECT_EQ(ret, read);
    check(ret);

    // with TaskID::Brief
    traits[2] = TaskMetaTrait(TaskID::BRIEF, MetaData::BRIEF, 100);
    tasks[2] = generate(traits[2]);

    std::future<TaskMeta> res = std::async(std::launch::async, [&] {
        TaskMeta meta;
        taskAgent.RunMulti(meta, agent.GetPlayer1(), tasks[0], tasks[1],
                           tasks[2], tasks[3], tasks[4]);
        return meta;
    });

    taskAgent.Read(read);
    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(read);

    EXPECT_EQ(read.GetID(), +TaskID::BRIEF);
    EXPECT_EQ(read.GetStatus(), MetaData::BRIEF);
    EXPECT_EQ(read.GetUserID(), 100);

    EXPECT_EQ(status->currentPlayer(), 100);

    taskAgent.Read(read);
    check(read);
    check(res.get());
}
