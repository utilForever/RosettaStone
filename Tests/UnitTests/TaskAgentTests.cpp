#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Enums/Enums.h>
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
    TaskMeta meta1 = TestUtils::GenerateRandomTaskMeta();
    TaskMeta meta2 = TestUtils::GenerateRandomTaskMeta();

    Task task1(TaskID::INVALID, [&meta1](Player& p1, Player&) -> TaskMeta {
        p1.id = 100;
        return TaskMeta::CopyFrom(meta1);
    });
    Task task2(TaskID::INVALID, [&meta2](Player&, Player& p2) -> TaskMeta {
        p2.id = 200;
        return TaskMeta::CopyFrom(meta2);
    });

    TaskAgent agent;
    agent.Add(task1);
    agent.Add(task2);

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    TaskMeta ret;
    agent.Run(ret, player1, player2);

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(ret, read);
    EXPECT_EQ(ret.id, +TaskID::TASK_TUPLE);

    EXPECT_EQ(player1.id, 100);
    EXPECT_EQ(player2.id, 200);

    const auto& buffer = ret.GetConstBuffer();
    auto taskTuple =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

    auto taskVector = taskTuple->vector();
    TaskMeta received1 = TaskMeta::ConvertFrom(taskVector->Get(0));
    TaskMeta received2 = TaskMeta::ConvertFrom(taskVector->Get(1));

    EXPECT_EQ(meta1, received1);
    EXPECT_EQ(meta2, received2);
}

TEST(TaskAgent, RunSingleTask)
{
    TaskAgent agent;

    TaskMeta meta = TestUtils::GenerateRandomTaskMeta();
    Task task(TaskID::INVALID, [=, &meta](Player& p1, Player& p2) -> TaskMeta {
        p1.id = 100;
        p2.id = 200;

        return TaskMeta::CopyFrom(meta);
    });

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    // with Notifying
    TaskMeta read;
    agent.Run(task, read, player1, player2);

    TaskMeta ret;
    agent.Read(ret);

    EXPECT_EQ(meta, ret);
    EXPECT_EQ(meta, read);

    EXPECT_EQ(player1.id, 100);
    EXPECT_EQ(player2.id, 200);

    // without Notifying
    TaskMeta read2;
    agent.Run(task, read2, player2, player1, false);

    EXPECT_EQ(meta, read2);
    EXPECT_EQ(player2.id, 100);
    EXPECT_EQ(player1.id, 200);
}

TEST(TaskAgent, RunMultiTask)
{
    auto generate = [](BYTE userID, const TaskMeta& meta) {
        return [userID, &meta](Player& p, Player&) {
            p.id = userID;
            return TaskMeta::CopyFrom(meta);
        };
    };

	auto metaEqual = [](const TaskMeta& meta, const auto& metas, size_t init,
                        size_t size) {
        const auto& buffer = meta.GetConstBuffer();
        auto taskTuple =
            flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

        auto vector = taskTuple->vector();
        EXPECT_EQ(vector->Length(), size);

        for (size_t i = 0; i < size; ++i)
        {
            auto idx = static_cast<flatbuffers::uoffset_t>(i);
            TaskMeta converted = TaskMeta::ConvertFrom(vector->Get(idx));

            EXPECT_EQ(metas[init + i], converted);
        }
    };

    std::vector<Task> tasks;
    std::vector<TaskMeta> metas;

    metas.reserve(5);
    for (BYTE i = 0; i < 5; ++i)
    {
        metas.emplace_back(TestUtils::GenerateRandomTaskMeta());
        tasks.emplace_back(TaskID::INVALID, generate(i, metas[i]));
    }

    Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

    TaskAgent agent;

    // without TaskID::Brief
    TaskMeta ret;
    agent.Run(tasks, ret, player1, player2);

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(ret, read);
    metaEqual(ret, metas, 0, 5);

    BYTE lastUserID = 4;
    EXPECT_EQ(player1.id, lastUserID);

	// with TaskID::Brief
    tasks[2] = Task(TaskID::BRIEF, generate(2, metas[2]));
    std::future<TaskMeta> res = std::async(std::launch::async, [&] {
        TaskMeta ret;
		agent.Run(tasks, ret, player1, player2); 

		return ret;
	});
	
	agent.Read(read);
    metaEqual(read, metas, 0, 3);

	agent.Read(read);
    metaEqual(read, metas, 3, 2);

	res.wait();
    metaEqual(res.get(), metas, 0, 5);
}

TEST(TaskAgent, Clear)
{
    Task task(TaskID::INVALID, [](Player&, Player&) { return TaskMeta(); });

	TaskAgent agent;
    agent.Add(task);
	agent.Clear();

	Deck deck;
    Account account;
    Player player1(&account, &deck);
    Player player2(&account, &deck);

	TaskMeta meta;
    agent.Run(meta, player1, player2);

	const auto& buffer = meta.GetConstBuffer();
    auto taskVector =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

	size_t size = taskVector->vector()->Length();
	EXPECT_EQ(size, 0);
}

