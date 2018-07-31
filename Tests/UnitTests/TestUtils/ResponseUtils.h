#ifndef UNIT_TEST_RESPONSE_UTILS
#define UNIT_TEST_RESPONSE_UTILS

#include <Managers/GameAgent.h>
#include <Tasks/TaskMeta.h>

#include <future>
#include <vector>

using namespace Hearthstonepp;

namespace TestUtils
{
// AutoResponder for GameAgent
// Response stated data to RequireTasks of GameAgent asynchronously
class AutoResponder
{
 public:
    AutoResponder(GameAgent& agent);

    std::future<TaskMeta> Mulligan(const BYTE* index, size_t size);
    std::future<TaskMeta> PlayCard(size_t cardIndex);
    std::future<TaskMeta> PlayMinion(size_t position);
    std::future<TaskMeta> PlaySpell(TargetType targetType,
                                    size_t targetPosition);
    std::future<TaskMeta> Target(size_t src, size_t dst);

    // Consists of PlayCard and PlayMinion
    auto AutoMinion(size_t cardIndex, size_t position)
        -> std::future<std::tuple<TaskMeta, TaskMeta>>;
    // Consists of PlayCard and PlaySpell
    auto AutoSpell(size_t cardIndex, TargetType targetType,
                   size_t targetPosition)
        -> std::future<std::tuple<TaskMeta, TaskMeta>>;

 private:
    GameAgent& m_agent;
};
}  // namespace TestUtils

#endif
