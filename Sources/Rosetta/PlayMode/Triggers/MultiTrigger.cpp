// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Triggers/MultiTrigger.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
MultiTrigger::MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers)
    : Trigger(TriggerType::MULTI_TRIGGER), m_triggers(std::move(triggers))
{
    // Do nothing
}

MultiTrigger::MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers,
                           const MultiTrigger& prototype, Entity& owner)
    : Trigger(prototype, owner), m_triggers(std::move(triggers))
{
    // Do nothing
}

std::shared_ptr<Trigger> MultiTrigger::Activate(Playable* source,
                                                TriggerActivation activation,
                                                bool cloning, bool isMulti)
{
    std::vector<std::shared_ptr<Trigger>> triggers;
    triggers.reserve(m_triggers.size());

    bool flag = false;

    for (const auto& trigger : m_triggers)
    {
        if (auto trig = trigger->Activate(source, activation, cloning, true);
            trig)
        {
            triggers.emplace_back(trig);
            flag = true;
        }
    }

    if (!flag)
    {
        return nullptr;
    }

    auto instance = std::make_shared<MultiTrigger>(triggers, *this, *source);

    if (!isMulti)
    {
        source->activatedTrigger = instance;
    }

    return instance;
}

void MultiTrigger::Remove()
{
    for (const auto& trigger : m_triggers)
    {
        trigger->Remove();
    }

    if (!isMultiTrigger)
    {
        m_owner->activatedTrigger = nullptr;
    }
}
}  // namespace RosettaStone::PlayMode
