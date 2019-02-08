// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Targeting.hpp>
#include <hspp/Models/Game.hpp>

namespace Hearthstonepp
{
bool Targeting::IsValidTarget(Card* card, Entity* target)
{
    for (auto& requirement : card->playRequirements)
    {
        switch (requirement.first)
        {
            case +PlayReq::REQ_ENEMY_TARGET:
            {
                if (dynamic_cast<Character*>(target)->GetOwner() !=
                    target->GetGame()->GetCurrentPlayer())
                {
                    return false;
                }
            }
            case +PlayReq::REQ_MINION_TARGET:
            {
                if (dynamic_cast<Minion*>(target) == nullptr)
                {
                    return false;
                }
            }
            default:
                break;
        }
    }

    return true;
}
}  // namespace Hearthstonepp