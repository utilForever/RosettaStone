// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>

#include <algorithm>

namespace RosettaStone::Generic
{
//! A list of play requirements that needs a target.
constexpr std::array<PlayReq, 8> NEEDS_TARGET_LIST = {
    PlayReq::REQ_TARGET_TO_PLAY,
    PlayReq::REQ_TARGET_IF_AVAILABLE,
    PlayReq::REQ_TARGET_FOR_COMBO,
    PlayReq::REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND,
    PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS,
    PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS,
    PlayReq::REQ_TARGET_IF_AVAILABLE_AND_ELEMENTAL_PLAYED_LAST_TURN,
    PlayReq::REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK
};

bool IsSourceNeedsTarget(Entity* source)
{
    for (auto& requirement : source->card.playRequirements)
    {
        auto iter = std::find(NEEDS_TARGET_LIST.begin(),
                              NEEDS_TARGET_LIST.end(), requirement.first);
        if (iter != NEEDS_TARGET_LIST.end())
        {
            return true;
        }
    }

    return false;
}

bool IsValidTarget(Entity* source, Entity* target)
{
    // Get valid play targets
    auto targetList = GetValidTargets(source);

    // Return if source needs a target, but target is null and list is empty
    if (IsSourceNeedsTarget(source) && target == nullptr && targetList.empty())
    {
        return false;
    }

    // Check source must require a target
    bool requiresTarget = false;
    for (auto& requirement : source->card.playRequirements)
    {
        if (requirement.first == PlayReq::REQ_TARGET_TO_PLAY)
        {
            requiresTarget = true;
            break;
        }
    }

    // Return if source must require a target, but target is null
    if (requiresTarget && target == nullptr)
    {
        return false;
    }

    // Return if target is exist, but not exist in target list
    if (target != nullptr && std::find(targetList.begin(), targetList.end(),
                                       target) == targetList.end())
    {
        return false;
    }

    return true;
}

std::vector<Character*> GetValidTargets(Entity* source)
{
    std::vector<Character*> ret;

    // If source don't need a target, return an empty vector
    if (!IsSourceNeedsTarget(source))
    {
        return ret;
    }

    auto game = source->GetOwner().GetGame();

    // Check play requirements for player's hero
    if (CheckRequirements(source, game->GetPlayer1().GetHero()))
    {
        ret.emplace_back(game->GetPlayer1().GetHero());
    }
    if (CheckRequirements(source, game->GetPlayer2().GetHero()))
    {
        ret.emplace_back(game->GetPlayer2().GetHero());
    }

    // Check play requirements for player's minions
    for (auto& minion : game->GetPlayer1().GetField().GetAllMinions())
    {
        if (CheckRequirements(source, minion))
        {
            ret.emplace_back(minion);
        }
    }
    for (auto& minion : game->GetPlayer2().GetField().GetAllMinions())
    {
        if (CheckRequirements(source, minion))
        {
            ret.emplace_back(minion);
        }
    }

    return ret;
}

bool CheckRequirements(Entity* source, Character* target)
{
    for (auto& requirement : source->card.playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_MINION_TARGET:
            {
                if (dynamic_cast<Minion*>(target) == nullptr)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_FRIENDLY_TARGET:
                if (&target->GetOwner() != &source->GetOwner())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_ENEMY_TARGET:
            {
                if (&target->GetOwner() == &source->GetOwner())
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_NONSELF_TARGET:
            {
                if (source == target)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_UNDAMAGED_TARGET:
            {
                if (target->GetDamage() > 0)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_TARGET_TO_PLAY:
            case PlayReq::REQ_TARGET_IF_AVAILABLE:
                break;
            default:
                break;
        }
    }

    return true;
}
}  // namespace RosettaStone::Generic
