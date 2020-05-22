// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Card.hpp>

namespace RosettaStone::Battlegrounds
{
CardType Card::GetCardType() const
{
    return static_cast<CardType>(gameTags.at(GameTag::CARDTYPE));
}

int Card::GetTier() const
{
    if (gameTags.find(GameTag::TECH_LEVEL) == gameTags.end())
    {
        return 0;
    }

    return gameTags.at(GameTag::TECH_LEVEL);
}
}  // namespace RosettaStone::Battlegrounds
