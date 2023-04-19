// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Managers/TriggerEvent.hpp>

#include <algorithm>

namespace RosettaStone::PlayMode
{
void TriggerEvent::AddHandler(const TriggerEventHandler& handler)
{
    m_handlers.emplace_back(std::make_unique<TriggerEventHandler>(handler));
}

void TriggerEvent::RemoveHandler(const TriggerEventHandler& handler)
{
    if (m_isNotifying)
    {
        for (auto& _handler : m_handlers)
        {
            if (*_handler == handler)
            {
                _handler->toBeRemoved = true;
                break;
            }
        }
    }
    else
    {
        m_handlers.erase(
            std::remove_if(
                m_handlers.begin(), m_handlers.end(),
                [&](const std::unique_ptr<TriggerEventHandler>& _handler) {
                    return *_handler == handler;
                }),
            m_handlers.end());
    }
}

void TriggerEvent::operator()(Entity* entity)
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

void TriggerEvent::NotifyHandlers(Entity* entity)
{
    m_isNotifying = true;

    for (auto& func : m_handlers)
    {
        if (func)
        {
            (*func)(entity);
        }
    }

    m_handlers.erase(
        std::remove_if(
            m_handlers.begin(), m_handlers.end(),
            [&](const std::unique_ptr<TriggerEventHandler>& handler) {
                return handler->toBeRemoved;
            }),
        m_handlers.end());

    m_isNotifying = false;
}
}  // namespace RosettaStone::PlayMode
