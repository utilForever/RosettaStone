// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_TASKS_HPP
#define UNIT_TESTS_TEST_TASKS_HPP

#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <Rosetta/Tasks/TaskStatus.hpp>

#include <functional>

using namespace RosettaStone;

class TestTask : public ITask
{
 public:
    TestTask(TaskID id, std::function<TaskStatus(Player&)>&& impl);

    TaskID GetTaskID() const override;

 private:
    TaskID m_id;
    std::function<TaskStatus(Player&)> m_impl;

    TaskStatus Impl(Player& player) override;
};

#endif  // UNIT_TESTS_TEST_TASKS_HPP