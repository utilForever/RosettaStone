// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ---------------------------------------- MINION - HUNTER
// [GIL_650] Houndmaster Shaw - COST:4 [ATK:3/HP:6]
// - Set: Gilneas, Rarity: Legendary
// --------------------------------------------------------
// Text: Your other minions have <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - GIL_650 : Houndmaster Shaw")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Houndmaster Shaw"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bluegill Warrior"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->HasRush(), false);
}

// ----------------------------------------- SPELL - HUNTER
// [GIL_828] Dire Frenzy - COST:4
// - Set: Gilneas, Rarity: Common
// --------------------------------------------------------
// Text: Give a Beast +3/+3.
//       Shuffle 3 copies into your deck with +3/+3.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_WITH_RACE = 20
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - GIL_828 : Dire Frenzy")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dire Frenzy"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bluegill Warrior"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curDeck.GetCount(), 3);
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Bloodfen Raptor");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 5);
}

// ------------------------------------------- SPELL - MAGE
// [GIL_801] Snap Freeze - COST:2
// - Set: Gilneas, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> a minion.
//       If it's already <b>Frozen</b>, destroy it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - GIL_801 : Snap Freeze")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snap Freeze"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snap Freeze"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->IsFrozen(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- MINION - ROGUE
// [GIL_598] Tess Greymane - COST:7 [ATK:6/HP:6]
// - Set: Gilneas, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Replay every card
//       from another class you've played this game
//       <i>(targets chosen randomly)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - GIL_598 : Tess Greymane")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tess Greymane"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Righteous Protector"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twisting Nether"));

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
}

// ---------------------------------------- SPELL - WARLOCK
// [GIL_191] Fiendish Circle - COST:3
// - Set: Gilneas, Rarity: Common
// --------------------------------------------------------
// Text: Summon four 1/1 Imps.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - GIL_191 : Fiendish Circle")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Imp");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[6]->card->name, "Imp");
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [GIL_547] Darius Crowley - COST:5 [ATK:4/HP:5]
// - Set: Gilneas, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>
//       After this attacks and kills a minion, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - GIL_547 : Darius Crowley")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darius Crowley"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Violet Teacher"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [GIL_124] Mossy Horror - COST:6 [ATK:2/HP:7]
// - Set: Gilneas, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy all other minions
//       with 2 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GIL_124 : Mossy Horror")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mossy Horror"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Wolfrider");
}

// --------------------------------------- MINION - NEUTRAL
// [GIL_622] Lifedrinker - COST:4 [ATK:3/HP:3]
// - Race: Beast, Set: Gilneas, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to the enemy hero.
//       Restore 3 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GIL_622 : Lifedrinker")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lifedrinker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);
}