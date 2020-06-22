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

TEST_CASE("[Battle] - Player 2 win (Each player has a minion)")
{
    Player player1, player2;

    Minion minion1(Cards::FindCardByDbfID(42467));
    Minion minion2(Cards::FindCardByDbfID(60628));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));
    player1.recruitFieldZone.Add(minion1);
    player2.recruitFieldZone.Add(minion2);
    player2.currentTier = 3;

    Battle battle(player1, player2);
    battle.Run();

    CHECK_EQ(battle.IsDone(), true);
    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 0);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);

    auto& p2Field = battle.GetPlayer2Field();
    CHECK_EQ(p2Field[0].GetHealth(), 1);

    CHECK_EQ(battle.GetResult(), BattleResult::PLAYER2_WIN);
    CHECK_EQ(player1.hero.health, 36);
    CHECK_EQ(player2.hero.health, 40);
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

TEST_CASE("[Battle] - Next Attacker")
{
    Player player1, player2;

    Minion minion1(Cards::FindCardByDbfID(1915));
    Minion minion2(Cards::FindCardByDbfID(1915));
    Minion minion3(Cards::FindCardByDbfID(1915));
    Minion minion4(Cards::FindCardByDbfID(1915));
    Minion minion5(Cards::FindCardByDbfID(1915));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));
    player1.recruitFieldZone.Add(minion1);
    player1.recruitFieldZone.Add(minion2);
    player1.recruitFieldZone.Add(minion3);
    player2.recruitFieldZone.Add(minion4);
    player2.recruitFieldZone.Add(minion5);

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 0);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 0);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 1);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 0);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 1);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 1);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 2);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 1);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 2);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 0);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 0);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 0);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1NextAttacker(), 0);
    CHECK_EQ(battle.GetPlayer2NextAttacker(), 1);
}