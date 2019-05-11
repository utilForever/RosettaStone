// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>

namespace RosettaStone
{
TaskMeta BasicPolicy::Next(const Game&)
{
    return TaskMeta(TaskMetaTrait{ TaskID::END_TURN });
}

TaskMeta BasicPolicy::Require(Player& player, TaskID id)
{
    if (const auto iter = m_require.find(id); iter != m_require.end())
    {
        return iter->second(*this, player);
    }
    return TaskMeta(TaskMetaTrait(id));
}

void BasicPolicy::Notify(const TaskMeta& meta)
{
    if (const auto iter = m_notify.find(meta.GetID()); iter != m_notify.end())
    {
        iter->second(*this, meta);
    }
}

TaskMeta BasicPolicy::RequireMulligan(Player&)
{
    return TaskMeta(TaskMetaTrait(), std::vector<std::size_t>());
}

TaskMeta BasicPolicy::RequirePlayCard(Player&)
{
    return TaskMeta(TaskMetaTrait(), SizedPtr<Entity*>());
}

TaskMeta BasicPolicy::RequireAttack(Player&)
{
    return TaskMeta(TaskMetaTrait(), SizedPtr<Entity*>());
}

TaskMeta BasicPolicy::RequireEndTurn(Player&)
{
    return TaskMeta(TaskMetaTrait(TaskID::END_TURN), SizedPtr<Entity*>());
}

void BasicPolicy::NotifyOverDraw(const TaskMeta& meta)
{
    (void)meta;
}
}  // namespace RosettaStone
