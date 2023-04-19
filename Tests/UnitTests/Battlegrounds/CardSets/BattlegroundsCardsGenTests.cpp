// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

// --------------------------------- MINION - BATTLEGROUNDS
// [BG_CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
// - Race: Beast, Set: Gangs, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Cat.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BG_CFM_315 : Alleycat")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByName("Alleycat"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

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

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

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

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

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

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    CHECK_EQ(player1.hero.health, 60);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hero.health, 58);
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

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    CHECK_EQ(player1.hero.health, 60);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hero.health, 60);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 1);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 3);

    player1.hand.Add(minion2);
    player1.PlayCard(0, 1);
    CHECK_EQ(player1.hero.health, 57);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 3);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 5);
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

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.hand.Add(minion3);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion4);
    player2.PlayCard(0, 0);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer2Field()[0].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetHealth(), 1);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BOT_445] Mecharoo - TIER:1 [ATK:1/HP:1]
// - Race: Mechanical, Set: Boomsday
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 1/1 Jo-E Bot.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BOT_445 : Mecharoo")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("BOT_445"));
    Minion minion2(Cards::FindCardByID("BOT_445"));
    Minion minion3(Cards::FindCardByID("BOT_445"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion3);
    player2.PlayCard(0, 0);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetName(), "Mecharoo");
    CHECK_EQ(battle.GetPlayer1Field()[1].GetName(), "Mecharoo");
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetName(), "Mecharoo");

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetName(), "Jo-E Bot");
    CHECK_EQ(battle.GetPlayer1Field()[1].GetName(), "Mecharoo");
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetName(), "Jo-E Bot");
}

// --------------------------------- MINION - BATTLEGROUNDS
// [GVG_103] Micro Machine - TIER:1 [ATK:1/HP:2]
// - Race: Mechanical, Set: Gvg
// --------------------------------------------------------
// Text: At the start of each turn, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - GVG_103 : Micro Machine")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("GVG_103"));
    Minion minion2(Cards::FindCardByID("GVG_103"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion2);
    player2.PlayCard(0, 0);

    player1.recruitField[0].SetHealth(10);
    player2.recruitField[0].SetHealth(10);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 1);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetAttack(), 1);

    auto& p1Field = const_cast<FieldZone&>(battle.GetPlayer1Field());
    auto& p2Field = const_cast<FieldZone&>(battle.GetPlayer2Field());

    p1Field.ForEachAlive([&](MinionData& owner) {
        p1Field.ForEachAlive([&](MinionData& minion) {
            {
                owner.value().ActivateTrigger(TriggerType::TURN_START,
                                              minion.value());
            };
        });
    });

    p2Field.ForEachAlive([&](MinionData& owner) {
        p2Field.ForEachAlive([&](MinionData& minion) {
            {
                owner.value().ActivateTrigger(TriggerType::TURN_START,
                                              minion.value());
            };
        });
    });

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 2);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetAttack(), 2);

    p1Field.ForEachAlive([&](MinionData& owner) {
        p1Field.ForEachAlive([&](MinionData& minion) {
            {
                owner.value().ActivateTrigger(TriggerType::TURN_START,
                                              minion.value());
            };
        });
    });

    p2Field.ForEachAlive([&](MinionData& owner) {
        p2Field.ForEachAlive([&](MinionData& minion) {
            {
                owner.value().ActivateTrigger(TriggerType::TURN_START,
                                              minion.value());
            };
        });
    });

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].GetAttack(), 3);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetAttack(), 3);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [EX1_509] Murloc Tidecaller - TIER:1 [ATK:1/HP:2]
// - Race: Murloc, Set: Expert1
// --------------------------------------------------------
// Text: Whenever you summon a Murloc, gain +1 Attack.
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - EX1_509 : Murloc Tidecaller")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("EX1_509"));
    Minion minion2(Cards::FindCardByID("EX1_509"));
    Minion minion3(Cards::FindCardByID("BGS_039"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.PlayCard(0, 0);
    CHECK_EQ(player1.recruitField.GetCount(), 1);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 1);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 2);

    player1.hand.Add(minion2);
    player1.PlayCard(0, 1);
    CHECK_EQ(player1.recruitField.GetCount(), 2);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 2);
    CHECK_EQ(player1.recruitField[1].GetAttack(), 1);
    CHECK_EQ(player1.recruitField[1].GetHealth(), 2);

    player1.hand.Add(minion3);
    player1.PlayCard(0, 2);
    CHECK_EQ(player1.recruitField.GetCount(), 3);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 2);
    CHECK_EQ(player1.recruitField[1].GetAttack(), 1);
    CHECK_EQ(player1.recruitField[1].GetHealth(), 2);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [EX1_506] Murloc Tidehunter - TIER:1 [ATK:2/HP:1]
// - Race: Murloc, Set: Core
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - EX1_506 : Murloc Tidehunter")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("EX1_506"));
    Minion minion2(Cards::FindCardByID("EX1_506"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    CHECK_EQ(player1.hand.GetCount(), 2);
    CHECK_EQ(player1.recruitField.GetCount(), 0);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.recruitField.GetCount(), 2);
    CHECK_EQ(player1.recruitField[0].GetName(), "Murloc Tidehunter");
    CHECK_EQ(player1.recruitField[1].GetName(), "Murloc Scout");

    player1.PlayCard(0, 1);
    CHECK_EQ(player1.hand.GetCount(), 0);
    CHECK_EQ(player1.recruitField.GetCount(), 4);
    CHECK_EQ(player1.recruitField[0].GetName(), "Murloc Tidehunter");
    CHECK_EQ(player1.recruitField[1].GetName(), "Murloc Tidehunter");
    CHECK_EQ(player1.recruitField[2].GetName(), "Murloc Scout");
    CHECK_EQ(player1.recruitField[3].GetName(), "Murloc Scout");
}

// --------------------------------- MINION - BATTLEGROUNDS
// [UNG_073] Rockpool Hunter - TIER:1 [ATK:2/HP:3]
// - Race: Murloc, Set: Ungoro
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly Murloc +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_WITH_RACE = 14
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - UNG_073 : Rockpool Hunter")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("UNG_073"));
    Minion minion2(Cards::FindCardByID("BGS_039"));
    Minion minion3(Cards::FindCardByID("UNG_073"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.hand.Add(minion3);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 3);

    player1.PlayCard(0, 1);
    CHECK_EQ(player1.recruitField[1].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[1].GetHealth(), 3);

    player1.PlayCard(0, 0, 1);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.recruitField.GetCount(), 2);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 3);
    CHECK_EQ(player1.recruitField[1].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[1].GetHealth(), 3);

    player1.PlayCard(0, 0, 0);
    CHECK_EQ(player1.hand.GetCount(), 0);
    CHECK_EQ(player1.recruitField.GetCount(), 3);
    CHECK_EQ(player1.recruitField[0].GetAttack(), 3);
    CHECK_EQ(player1.recruitField[0].GetHealth(), 4);
    CHECK_EQ(player1.recruitField[1].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[1].GetHealth(), 3);
    CHECK_EQ(player1.recruitField[2].GetAttack(), 2);
    CHECK_EQ(player1.recruitField[2].GetHealth(), 3);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BGS_055] Deck Swabbie - TIER:1 [ATK:2/HP:2]
// - Race: Pirate, Set: Battlegrounds
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Reduce the cost of upgrading
//       Bob's Tavern by (1).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BGS_055 : Deck Swabbie")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("BGS_055"));
    Minion minion2(Cards::FindCardByID("BGS_055"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.GetGameState().nextPhase = Phase::RECRUIT;
    GameManager::ProcessNextPhase(game, game.GetGameState().nextPhase);

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);

    CHECK_EQ(player1.currentTier, 1);
    CHECK_EQ(player1.coinToUpgradeTavern, 5);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.coinToUpgradeTavern, 4);

    player1.PlayCard(0, 1);
    CHECK_EQ(player1.coinToUpgradeTavern, 3);

    player1.remainCoin = 10;

    player1.UpgradeTavern();
    CHECK_EQ(player1.currentTier, 2);
    CHECK_EQ(player1.coinToUpgradeTavern, 7);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [BGS_061] Scallywag - TIER:1 [ATK:3/HP:1]
// - Race: Pirate, Set: Battlegrounds
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 1/1 Pirate.
//       It attacks immediately.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - BGS_061 : Scallywag")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("BGS_061"));
    Minion minion2(Cards::FindCardByID("BGS_061"));
    Minion minion3(Cards::FindCardByID("LOOT_013"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 0);

    player2.hand.Add(minion3);
    player2.PlayCard(0, 0);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    player1.getBattleCallback = [&]() -> Battle& { return battle; };
    player2.getBattleCallback = [&]() -> Battle& { return battle; };

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field()[0].GetHealth(), 4);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 0);
}

// --------------------------------- MINION - BATTLEGROUNDS
// [ICC_038] Righteous Protector - TIER:1 [ATK:1/HP:1]
// - Set: Icecrown
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - ICC_038 : Righteous Protector")
{
    // Do nothing
}

// --------------------------------- MINION - BATTLEGROUNDS
// [OG_221] Selfless Hero - TIER:1 [ATK:2/HP:1]
// - Set: Og
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give a random friendly minion
//       <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - OG_221 : Selfless Hero")
{
    Game game;
    game.Start();

    Player& player1 = game.GetGameState().players[0];
    Player& player2 = game.GetGameState().players[1];

    Minion minion1(Cards::FindCardByID("OG_221"));
    Minion minion2(Cards::FindCardByID("BGS_061"));
    Minion minion3(Cards::FindCardByID("LOOT_013"));

    player1.hero.Initialize(Cards::FindCardByDbfID(59397));
    player2.hero.Initialize(Cards::FindCardByDbfID(59397));

    game.SetPlayerPair(0, 1);

    player1.hand.Add(minion1);
    player1.hand.Add(minion2);
    player1.PlayCard(0, 0);
    player1.PlayCard(0, 1);

    player2.hand.Add(minion3);
    player2.PlayCard(0, 0);

    player1.isInCombat = true;
    player2.isInCombat = true;

    Battle battle(player1, player2);
    battle.Initialize();

    player1.getBattleCallback = [&]() -> Battle& { return battle; };
    player2.getBattleCallback = [&]() -> Battle& { return battle; };

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 2);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[1].HasDivineShield(), false);

    battle.Attack();

    CHECK_EQ(battle.GetPlayer1Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer2Field().GetCount(), 1);
    CHECK_EQ(battle.GetPlayer1Field()[0].HasDivineShield(), true);
}