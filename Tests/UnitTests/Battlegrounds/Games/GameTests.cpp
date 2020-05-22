// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

TEST_CASE("[Game] - Basic")
{
    Game game;
    game.Start();

    CHECK_EQ(game.GetGameState().phase, Phase::SELECT_HERO);

    for (auto& player : game.GetGameState().players)
    {
        for (const auto& hero : player.heroChoices)
        {
            auto heroCard = Cards::FindCardByDbfID(hero);
            CHECK_EQ(heroCard.GetCardType(), CardType::HERO);
            CHECK_EQ(heroCard.isCurHero, true);
        }

        player.SelectHero(1);
    }

    CHECK_EQ(game.GetGameState().phase, Phase::RECRUIT);
}