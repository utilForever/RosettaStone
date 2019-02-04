// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Commons/Utils.hpp>
#include <hspp/Policy/IoPolicy.hpp>

namespace Hearthstonepp
{
IoPolicy::IoPolicy(std::ostream& out, std::istream& in) : m_out(out), m_in(in)
{
    // Do Nothing
}

TaskMeta IoPolicy::RequireMulligan(Player& player)
{
    TaskMetaTrait trait(TaskID::MULLIGAN, TaskStatus::MULLIGAN_SUCCESS,
                        player.GetID());

    return TaskMeta(trait, Box<size_t>(3));
}

TaskMeta IoPolicy::RequirePlaySpell(Player& player)
{
    (void)player;
    (void)m_out;
    (void)m_in;
    return TaskMeta();
}

TaskMeta IoPolicy::RequirePlayCard(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta IoPolicy::RequirePlayMinion(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta IoPolicy::RequireCombat(Player& player)
{
    (void)player;
    return TaskMeta();
}

void IoPolicy::NotifyOverDraw(const TaskMeta& meta)
{
    (void)meta;
}
}  // namespace Hearthstonepp