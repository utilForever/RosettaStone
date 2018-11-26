// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_TASKS_HPP
#define UNIT_TESTS_TEST_TASKS_HPP

#include <hspp/Accounts/Player.hpp>
#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Tasks/MetaData.hpp>
#include <hspp/Tasks/Tasks.hpp>

#include <functional>

using namespace Hearthstonepp;

class TestTask : public ITask
{
 public:
    TestTask(TaskID id, std::function<MetaData(Player&)>&& impl);

    TaskID GetTaskID() const override;

 private:
    TaskID m_id;
    std::function<MetaData(Player&)> m_impl;

    MetaData Impl(Player& player) override;
};

#endif  // UNIT_TESTS_TEST_TASKS_HPP