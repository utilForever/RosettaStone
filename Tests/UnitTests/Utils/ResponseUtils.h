// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_RESPONSE_UTILS_H
#define UNIT_TESTS_RESPONSE_UTILS_H

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/TaskMeta.h>

#include <future>

using namespace Hearthstonepp;

namespace TestUtils
{
// Auto responder for GameAgent
// Response stated data to RequireTasks of GameAgent asynchronously
class AutoResponder
{
 public:
    AutoResponder(GameAgent& agent);

    std::future<TaskMeta> Mulligan(const BYTE* index, size_t size);
    std::future<TaskMeta> PlayCard(size_t cardIndex);
    std::future<TaskMeta> PlayMinion(size_t position);
    std::future<TaskMeta> PlaySpell(EntityType type, size_t targetPosition);
    std::future<TaskMeta> Target(size_t src, size_t dst);

    // Consists of PlayCard and PlayMinion
    auto AutoMinion(size_t cardIndex, size_t position)
        -> std::future<std::tuple<TaskMeta, TaskMeta>>;
    // Consists of PlayCard and PlaySpell
    auto AutoSpell(size_t cardIndex, EntityType type, size_t targetPosition)
        -> std::future<std::tuple<TaskMeta, TaskMeta>>;

 private:
    GameAgent& m_agent;
};
}  // namespace TestUtils

#endif  // UNIT_TESTS_RESPONSE_UTILS_H
