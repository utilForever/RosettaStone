// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <RosettaTorch/TorchPolicy.hpp>

namespace RosettaTorch
{
TorchPolicy::TorchPolicy(std::shared_ptr<ModuleBase> module) : m_module(module)
{
    // Do nothing
}

TaskMeta TorchPolicy::RequireMulligan(Player& player)
{
    TaskMetaTrait trait(TaskID::MULLIGAN, TaskStatus::COMPLETE,
                        player.GetID());

    return TaskMeta(trait, SizedPtr<std::size_t>());
}

TaskMeta TorchPolicy::RequirePlayCard(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta TorchPolicy::RequireAttack(Player& player)
{
    (void)player;
    return TaskMeta();
}

void TorchPolicy::NotifyOverDraw(const TaskMeta& meta)
{
    (void)meta;
}
}  // namespace HSppTorch