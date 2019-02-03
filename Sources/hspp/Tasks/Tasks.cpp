// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp
{
ITask::ITask(Entity* source, Entity* target)
    : m_source(source), m_target(target)
{
    // Do nothing
}

void ITask::SetTarget(Entity* target)
{
    m_target = target;
}

MetaData ITask::Run(Player& player)
{
    return Impl(player);
}
}  // namespace Hearthstonepp
