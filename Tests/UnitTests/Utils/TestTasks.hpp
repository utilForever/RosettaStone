// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_TASKS_HPP
#define UNIT_TESTS_TEST_TASKS_HPP

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Tasks/TaskStatus.hpp>
#include <hspp/Tasks/Tasks.hpp>

#include <functional>

using namespace Hearthstonepp;

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