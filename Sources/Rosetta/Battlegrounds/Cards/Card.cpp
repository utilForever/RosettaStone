// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Card.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <algorithm>

namespace RosettaStone::Battlegrounds
{
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

bool Card::IsTier1MinionInPool() const
{
    if (std::find(TIER1_MINIONS.begin(), TIER1_MINIONS.end(), dbfID) !=
        TIER1_MINIONS.end())
    {
        return true;
    }

    return false;
}

bool Card::IsTier2MinionInPool() const
{
    if (std::find(TIER2_MINIONS.begin(), TIER2_MINIONS.end(), dbfID) !=
        TIER2_MINIONS.end())
    {
        return true;
    }

    return false;
}

bool Card::IsTier3MinionInPool() const
{
    if (std::find(TIER3_MINIONS.begin(), TIER3_MINIONS.end(), dbfID) !=
        TIER3_MINIONS.end())
    {
        return true;
    }

    return false;
}

bool Card::IsTier4MinionInPool() const
{
    if (std::find(TIER4_MINIONS.begin(), TIER4_MINIONS.end(), dbfID) !=
        TIER4_MINIONS.end())
    {
        return true;
    }

    return false;
}

bool Card::IsTier5MinionInPool() const
{
    if (std::find(TIER5_MINIONS.begin(), TIER5_MINIONS.end(), dbfID) !=
        TIER5_MINIONS.end())
    {
        return true;
    }

    return false;
}

bool Card::IsTier6MinionInPool() const
{
    if (std::find(TIER6_MINIONS.begin(), TIER6_MINIONS.end(), dbfID) !=
        TIER6_MINIONS.end())
    {
        return true;
    }

    return false;
}
}  // namespace RosettaStone::Battlegrounds
