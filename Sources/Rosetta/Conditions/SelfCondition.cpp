// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Games/Game.hpp>
#include <utility>

namespace RosettaStone
{
SelfCondition::SelfCondition(std::function<bool(Entity*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsControllingRace(Race race)
{
    return SelfCondition([=](Entity* entity) -> bool {
        for (auto& minion : entity->GetOwner().GetField().GetAllMinions())
        {
            if (minion->card.GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

bool SelfCondition::Evaluate(Entity* entity) const
{
    return m_func(entity);
}
}  // namespace RosettaStone
