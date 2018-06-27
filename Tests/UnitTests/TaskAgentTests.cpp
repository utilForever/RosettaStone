#include "gtest/gtest.h"
#include "Generator.h"

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

    std::async(std::launch::async, [&agent, &meta] {
        agent.Notify(std::move(meta));
    });

    TaskMeta read;
    agent.Read(read);

    EXPECT_EQ(copied, read);
}

TEST(TaskAgent, AddTaskAndRun)
{
//    TaskMeta meta1 = GenerateRandomTaskMeta();
//    TaskMeta meta2 = GenerateRandomTaskMeta();
//
//    TaskAgent agent;
//    agent.Add(meta1);
//    agent.Add(meta2);
}

TEST(TaskAgent, RunSingleTask)
{
}

TEST(TaskAgent, RunMultiTask)
{
}

TEST(TaskAgent, Clear)
{
}