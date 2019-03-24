// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>

namespace RosettaStone::Generic
{
bool IsValidTarget(Entity* source, Entity* target)
{
    for (auto& requirement : source->card.playRequirements)
    {
        switch (requirement.first)
        {
            case +PlayReq::REQ_MINION_TARGET:
            {
                if (dynamic_cast<Minion*>(target) == nullptr)
                {
                    return false;
                }
                break;
            }
            case +PlayReq::REQ_ENEMY_TARGET:
            {
                if (&target->GetOwner() == &source->GetOwner())
                {
                    return false;
                }
                break;
            }
            case +PlayReq::REQ_TARGET_TO_PLAY:
            {
                if (dynamic_cast<Character*>(target) == nullptr)
                {
                    return false;
                }
                break;
            }
            default:
                break;
        }
    }

    return true;
}
}  // namespace RosettaStone::Generic
