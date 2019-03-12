// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Commons/Utils.hpp>
#include <hspp/Policies/TorchPolicy.hpp>

namespace Hearthstonepp
{
TaskMeta TorchPolicy::RequireMulligan(Player& player)
{
    TaskMetaTrait trait(TaskID::MULLIGAN, TaskStatus::MULLIGAN_SUCCESS,
                        player.GetID());

    return TaskMeta(trait, SizedPtr<std::size_t>());
}

TaskMeta TorchPolicy::RequirePlaySpell(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta TorchPolicy::RequirePlayCard(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta TorchPolicy::RequirePlayMinion(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta TorchPolicy::RequireCombat(Player& player)
{
    (void)player;
    return TaskMeta();
}

void TorchPolicy::NotifyOverDraw(const TaskMeta& meta)
{
    (void)meta;
}
}  // namespace Hearthstonepp