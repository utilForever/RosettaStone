// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Triggers/MultiTrigger.hpp>

#include <utility>

namespace RosettaStone
{
MultiTrigger::MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers)
    : Trigger(TriggerType::MULTI_TRIGGER), m_triggers(std::move(triggers))
{
    // Do nothing
}
}  // namespace RosettaStone
