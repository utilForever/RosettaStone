// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Policies/IoPolicy.hpp>

namespace RosettaStone
{
IoPolicy::IoPolicy(std::ostream& out, std::istream& in) : m_out(out), m_in(in)
{
    // Do nothing
}

TaskMeta IoPolicy::RequireMulligan(Player& player)
{
    const TaskMetaTrait trait(TaskID::MULLIGAN, TaskStatus::COMPLETE, player.GetID());

    return TaskMeta(trait, SizedPtr<std::size_t>(3));
}

TaskMeta IoPolicy::RequirePlayCard(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta IoPolicy::RequireAttack(Player& player)
{
    (void)player;
    return TaskMeta();
}

void IoPolicy::NotifyOverDraw(const TaskMeta& meta)
{
    (void)m_in;
    (void)m_out;
    (void)meta;
}
}  // namespace RosettaStone
