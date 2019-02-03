// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Policy/BasicPolicy.hpp>

namespace Hearthstonepp
{
TaskMeta BasicPolicy::Next(const Game& game)
{
    (void)game;
    return TaskMeta();
}

TaskMeta BasicPolicy::Require(Player& player, TaskID id)
{
    if (auto iter = m_require.find(id); iter != m_require.end())
    {
        return iter->second(*this, player);
    }
    return TaskMeta(id);
}

void BasicPolicy::Notify(const TaskMeta& meta)
{
    if (auto iter = m_notify.find(meta.GetID()); iter != m_notify.end())
    {
        return iter->second(*this, meta);
    }
}
}  // namespace Hearthstonepp