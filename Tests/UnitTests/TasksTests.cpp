#include "gtest/gtest.h"

#include <Tasks/BasicTask.h>
#include <Tasks/Tasks.h>

#include <random>

using namespace Hearthstonepp;

TEST(Tasks, Constructors)
{
    // Empty Constructor
    Task empty;
    EXPECT_EQ(empty.GetTaskID(), +TaskID::INVALID);

    std::random_device rd;
    std::default_random_engine gen(rd());

	int taskSize = static_cast<int>(TaskID::_size() - 1);
    std::uniform_int_distribution<int> dis(0, taskSize);
    TaskID rand = TaskID::_from_integral(dis(gen));
    Task::lambda_t lambda = BasicTask::RawPlayerSetting;

    // Default Constructor
    Task task(rand, lambda);
    EXPECT_EQ(task.GetTaskID(), rand);

    // Copy Constructor
    Task copied(task);
    EXPECT_EQ(copied.GetTaskID(), rand);

    // Move Constructor, noexcept
    Task moved(std::move(task));
    EXPECT_EQ(moved.GetTaskID(), rand);

    rand = TaskID::_from_integral(dis(gen));
    lambda = BasicTask::RawPlayerSetting;

    Task task2(rand, lambda);

    // Copy Assignment
    copied = task2;
    EXPECT_EQ(copied.GetTaskID(), task2.GetTaskID());

    // Move Assignment
    moved = std::move(task2);
    EXPECT_EQ(moved.GetTaskID(), task2.GetTaskID());
}