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

    player1.isInCombat = true;
    player2.isInCombat = true;

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

    player1.isInCombat = true;
    player2.isInCombat = true;

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

// --------------------------------- MINION - BATTLEGROUNDS
// [LOOT_013] Vulgar Homunculus - TIER:1 [ATK:2/HP:4]
// - Race: Demon, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 2 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - LOOT_013 : Vulgar Homunculus")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("LOOT_013"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    CHECK_EQ(player1.hero.health, 40);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hero.health, 38);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BGS_004] Wrath Weaver - TIER:1 [ATK:1/HP:1]
// - Race: Demon, Set: Battlegrounds, Rarity: Common
// --------------------------------------------------------
// Text: After you play a Demon, deal 1 damage to your hero
//       and gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BGS_004 : Wrath Weaver")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("BGS_004"));
    Minion minion2(Cards::FindCardByID("LOOT_013"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    CHECK_EQ(player1.hero.health, 40);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hero.health, 40);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 1);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 1);

    player1.hand.Add(minion2);
    player1.PlayCard(0, 1);
    CHECK_EQ(player1.hero.health, 37);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 3);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 3);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BGS_039] Dragonspawn Lieutenant - TIER:1 [ATK:2/HP:2]
// - Race: Dragon, Set: Battlegrounds, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BGS_039 : Dragonspawn Lieutenant")
{
    // Do nothing
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BGS_019] Red Whelp - TIER:1 [ATK:1/HP:2]
// - Race: Dragon, Set: Battlegrounds
// --------------------------------------------------------
// Text: <b>Start of Combat:</b> Deal 1 damage per friendly
//       Dragon to one random enemy minion.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BGS_019 : Red Whelp")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("BGS_019"));
    Minion minion2(Cards::FindCardByID("BGS_039"));
    Minion minion3(Cards::FindCardByID("BGS_039"));
    Minion minion4(Cards::FindCardByID("BGS_039"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.hand.Add(minion3);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion4);
    player2.PlayCard(0, 0);

    game.SetPlayerPair(0, 1);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer2Field()[0].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetHealth(), 1);
}