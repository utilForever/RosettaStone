// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

TEST_CASE("[Battle] - Player 1 win (Player 1 has a minion only)")
{
    Player player1, player2;

    Minion minion1(Cards::FindCardByDbfID(49169));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));
    player1.recruitFieldZone.Add(minion1);
    player1.currentTier = 4;

    Battle battle(player1, player2);
    battle.Run();

    CHECK_EQ(battle.IsDone(), true);
    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 0);

    CHECK_EQ(battle.GetResult(), BattleResult::PLAYER1_WIN);
    CHECK_EQ(player1.hero.health, 40);
    CHECK_EQ(player2.hero.health, 32);
}

TEST_CASE("[Battle] - Draw (0 attack minions only)")
{
    Player player1, player2;

    Minion minion1(Cards::FindCardByDbfID(49169));
    Minion minion2(Cards::FindCardByDbfID(49169));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));
    player1.recruitFieldZone.Add(minion1);
    player2.recruitFieldZone.Add(minion2);

    Battle battle(player1, player2);
    battle.Run();

    CHECK_EQ(battle.IsDone(), true);
    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);

    CHECK_EQ(battle.GetResult(), BattleResult::DRAW);
    CHECK_EQ(player1.hero.health, 40);
    CHECK_EQ(player2.hero.health, 40);
}