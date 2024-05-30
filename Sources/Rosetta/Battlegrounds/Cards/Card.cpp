// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Card.hpp>
#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/Common/Enums/TargetingEnums.hpp>

#include <algorithm>

namespace RosettaStone::Battlegrounds
{
void Card::Initialize()
{
    bool needsTarget = false;
    CharacterType characterType = CharacterType::CHARACTERS;
    FriendlyType friendlyType = FriendlyType::ALL;

    for (auto& requirement : playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_TARGET_IF_AVAILABLE:
                needsTarget = true;
                break;
            case PlayReq::REQ_MINION_TARGET:
                characterType = CharacterType::MINIONS;
                break;
            case PlayReq::REQ_FRIENDLY_TARGET:
                friendlyType = FriendlyType::FRIENDLY;
                break;
            case PlayReq::REQ_TARGET_WITH_RACE:
            {
                const Race race = static_cast<Race>(requirement.second);
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqTargetWithRace(race));
            }
            break;
            default:
                continue;
        }
    }

    if (needsTarget)
    {
        switch (characterType)
        {
            case CharacterType::MINIONS:
                switch (friendlyType)
                {
                    case FriendlyType::FRIENDLY:
                        targetingType = TargetingType::FRIENDLY_MINIONS;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

CardSet Card::GetCardSet() const
{
    return static_cast<CardSet>(gameTags.at(GameTag::CARD_SET));
}

CardType Card::GetCardType() const
{
    return static_cast<CardType>(gameTags.at(GameTag::CARDTYPE));
}

Race Card::GetRace() const
{
    if (gameTags.find(GameTag::CARDRACE) == gameTags.end())
    {
        return Race::INVALID;
    }

    return static_cast<Race>(gameTags.at(GameTag::CARDRACE));
}

int Card::GetAttack() const
{
    if (gameTags.find(GameTag::ATK) == gameTags.end())
    {
        return 0;
    }

    return gameTags.at(GameTag::ATK);
}

int Card::GetHealth() const
{
    if (gameTags.find(GameTag::HEALTH) == gameTags.end())
    {
        return 0;
    }

    return gameTags.at(GameTag::HEALTH);
}

int Card::GetTier() const
{
    if (gameTags.find(GameTag::TECH_LEVEL) == gameTags.end())
    {
        return 0;
    }

    return gameTags.at(GameTag::TECH_LEVEL);
}

bool Card::IsPlayableByCardReq([[maybe_unused]] Player& player) const
{
    //for (const auto& playReq : playRequirements)
    //{
    //    switch (playReq.first)
    //    {
    //        default:
    //            break;
    //    }
    //}

    return true;
}

bool Card::TargetingRequirements(Minion& target) const
{
    if (!targetingPredicate.empty())
    {
        for (const auto& predicate : targetingPredicate)
        {
            if (!predicate(target))
            {
                return false;
            }
        }
    }

    return true;
}
}  // namespace RosettaStone::Battlegrounds
