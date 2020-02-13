// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Managers/TriggerEventHandler.hpp>

#include <utility>

namespace RosettaStone
{
TriggerEventHandler::TriggerEventHandler() : id(0)
{
    // Do nothing
}

TriggerEventHandler::TriggerEventHandler(Func func)
    : id(++counter), m_func(std::move(func))
{
    // Do nothing
}

TriggerEventHandler& TriggerEventHandler::operator=(
    const TriggerEventHandler& handler)
{
    if (&handler == this)
    {
        return *this;
    }

    if (m_func == nullptr)
    {
        m_func = handler.m_func;
        id = ++counter;
    }

    return *this;
}

void TriggerEventHandler::operator()(Entity* entity) const
{
    m_func(entity);
}

bool TriggerEventHandler::operator==(const TriggerEventHandler& handler) const
{
    return id == handler.id;
}

bool TriggerEventHandler::operator!=(std::nullptr_t) const
{
    return m_func != nullptr;
}
}  // namespace RosettaStone
