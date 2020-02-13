// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Managers/TriggerEvent.hpp>

#include <algorithm>

namespace RosettaStone
{
void TriggerEvent::AddHandler(const TriggerEventHandler& handler)
{
    m_handlers.emplace_back(std::make_unique<TriggerEventHandler>(handler));
}

void TriggerEvent::RemoveHandler(const TriggerEventHandler& handler)
{
    m_handlers.erase(
        std::remove_if(
            m_handlers.begin(), m_handlers.end(),
            [&](const std::unique_ptr<TriggerEventHandler>& _handler) {
                return *_handler == handler;
            }),
        m_handlers.end());
}

void TriggerEvent::operator()(Entity* entity) const
{
    NotifyHandlers(entity);
}

TriggerEvent& TriggerEvent::operator+=(const TriggerEventHandler& handler)
{
    AddHandler(handler);

    return *this;
}

TriggerEvent& TriggerEvent::operator-=(const TriggerEventHandler& handler)
{
    RemoveHandler(handler);

    return *this;
}

void TriggerEvent::NotifyHandlers(Entity* entity) const
{
    for (auto& func : m_handlers)
    {
        if (func != nullptr)
        {
            (*func)(entity);
        }
    }
}
}  // namespace RosettaStone
