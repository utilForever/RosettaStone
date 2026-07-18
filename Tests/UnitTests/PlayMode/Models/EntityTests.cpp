// Copyright (c) 2017-2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

#include <stdexcept>
#include <utility>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Entity] - GetFromCard rejects invalid card type")
{
    Player player;
    Card invalidCard;

    invalidCard.gameTags.emplace(GameTag::CARDTYPE,
                                 std::to_underlying(CardType::INVALID));
    CHECK_THROWS_AS(Entity::GetFromCard(&player, &invalidCard),
                    std::invalid_argument);
}
