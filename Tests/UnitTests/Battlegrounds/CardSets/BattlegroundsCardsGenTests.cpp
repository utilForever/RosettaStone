// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

// --------------------------------- MINION - BATTLEGROUNDS
// [CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
// - Race: Beast, Set: Gangs, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Cat.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - CFM_315 : Alleycat")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByName("Alleycat"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    player1.hand.Add(minion1);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.recruitField.GetCount(), 0);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hand.GetCount(), 0);
    CHECK_EQ(player1.recruitField.GetCount(), 2);
    CHECK_EQ(player1.recruitField[0].GetName(), "Alleycat");
    CHECK_EQ(player1.recruitField[1].GetName(), "Tabbycat");
}

// --------------------------------- MINION - BATTLEGROUNDS
// [EX1_531] Scavenging Hyena - TIER:1 [ATK:2/HP:2]
// - Race: Beast, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a friendly Beast dies, gain +2/+1.
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - EX1_531 : Scavenging Hyena")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByName("Scavenging Hyena"));
    Minion minion2(Cards::FindCardByName("Scavenging Hyena"));
    Minion minion3(Cards::FindCardByName("Scavenging Hyena"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion3);
    player2.PlayCard(0, 0);

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetHealth(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[1].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[1].GetHealth(), 2);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 4);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetHealth(), 3);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [YOD_026] Fiendish Servant - TIER:1 [ATK:2/HP:1]
// - Race: Demon, Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give this minion's Attack
//       to a random friendly minion.
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - YOD_026 : Fiendish Servant")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("YOD_026"));
    Minion minion2(Cards::FindCardByID("YOD_026"));
    Minion minion3(Cards::FindCardByID("YOD_026"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion3);
    player2.PlayCard(0, 0);

    player1.recruitField[0].SetAttack(10);

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 10);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetHealth(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[1].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[1].GetHealth(), 1);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 12);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetHealth(), 1);
}