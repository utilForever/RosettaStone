// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [BRM_009] Volcanic Lumberer - COST:9 [ATK:7/HP:8]
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Costs (1) less for each minion that died this turn.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BRM_009 : Volcanic Lumberer")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Volcanic Lumberer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 9);

    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(card1->GetCost(), 8);

    game.Process(curPlayer, AttackTask(card3, card5));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 9);
}

// ----------------------------------------- MINION - DRUID
// [BRM_010] Druid of the Flame - COST:3 [ATK:2/HP:2]
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Transform into a 5/2 minion;
//       or a 2/5 minion.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BRM_010 : Druid of the Flame")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Flame"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Flame"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [BRM_013] Quick Shot - COST:2
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage.
//       If your hand is empty, draw a card.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BRM_013 : Quick Shot")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Quick Shot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Quick Shot"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
}

// --------------------------------------- MINION - WARLOCK
// [BRM_006] Imp Gang Boss - COST:3 [ATK:2/HP:4]
// - Race: Demon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, summon a 1/1 Imp.
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BRM_006 : Imp Gang Boss")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Imp Gang Boss"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Imp");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [BRM_014] Core Rager - COST:4 [ATK:4/HP:4]
// - Race: Beast, Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your hand is empty, gain +3/+3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - BRM_014 : Core Rager")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Core Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Core Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 7);
}

// ------------------------------------------ MINION - MAGE
// [BRM_002] Flamewaker - COST:3 [ATK:2/HP:4]
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a spell,
//       deal 2 damage randomly split among all enemies.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - BRM_002 : Flamewaker")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flamewaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Intellect"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));

    const int totalHealth =
        opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 40);
}

// ------------------------------------------- SPELL - MAGE
// [BRM_003] Dragon's Breath - COST:5
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Deal 4 damage. Costs (1) less for each minion
//       that died this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BRM_003 : Dragon's Breath")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon's Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(card1->GetCost(), 4);

    game.Process(curPlayer, AttackTask(card3, card5));
    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
}

// ---------------------------------------- SPELL - PALADIN
// [BRM_001] Solemn Vigil - COST:5
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Draw 2 cards.
//       Costs (1) less for each minion that died this turn.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BRM_001 : Solemn Vigil")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Solemn Vigil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(card1->GetCost(), 4);

    game.Process(curPlayer, AttackTask(card3, card5));
    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
}

// --------------------------------------- MINION - PALADIN
// [BRM_018] Dragon Consort - COST:5 [ATK:5/HP:5]
// - Race: Dragon, Set:Bbrm, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next Dragon
//       you play costs (2) less.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BRM_018 : Dragon Consort")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon Consort"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azure Drake"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Whelp"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Glaivebound Adept"));

    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card4->GetCost(), 5);
}

// ---------------------------------------- MINION - PRIEST
// [BRM_004] Twilight Whelp - COST:1 [ATK:2/HP:1]
// - Race: Dragon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       gain +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BRM_004 : Twilight Whelp")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Whelp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Whelp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [BRM_017] Resurrect - COST:2
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: Summon a random friendly minion that died this game.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - BRM_017 : Resurrect")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Resurrect"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Injured Blademaster"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 7);
}

// ------------------------------------------ SPELL - ROGUE
// [BRM_007] Gang Up - COST:2
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Choose a minion.
//       Shuffle 3 copies of it into your deck.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BRM_007 : Gang Up")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gang Up"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Injured Blademaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curDeck.GetCount(), 3);
    CHECK_EQ(curDeck[0]->card->name, "Injured Blademaster");
    CHECK_EQ(curDeck[1]->card->name, "Injured Blademaster");
    CHECK_EQ(curDeck[2]->card->name, "Injured Blademaster");
}

// ----------------------------------------- MINION - ROGUE
// [BRM_008] Dark Iron Skulker - COST:5 [ATK:4/HP:3]
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 2 damage
//       to all undamaged enemy minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BRM_007 : Gang Up")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dark Iron Skulker"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Injured Blademaster"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Azure Drake"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [BRM_011] Lava Shock - COST:2
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage.
//       Unlock your <b>Overloaded</b> Mana Crystals.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - BRM_011 : Lava Shock")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lava Shock"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lava Shock"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Spirit"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Spirit"));

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
}

// ---------------------------------------- MINION - SHAMAN
// [BRM_012] Fireguard Destroyer - COST:4 [ATK:3/HP:6]
// - Race: Elemental, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain 1-4 Attack.
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - BATTLECRY = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BRM_012 : Fireguard Destroyer")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireguard Destroyer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_GE(curField[0]->GetAttack(), 4);
    CHECK_LE(curField[0]->GetAttack(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
}

// ---------------------------------------- SPELL - WARLOCK
// [BRM_005] Demonwrath - COST:3
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to all minions except Demons.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BRM_005 : Demonwrath")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonwrath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Servant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Feywing"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Midway Maniac"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Southsea Captain"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Crabrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 3);
    CHECK_EQ(opField[2]->GetHealth(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - WARLOCK
// [BRM_006] Imp Gang Boss - COST:3 [ATK:2/HP:4]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, summon a 1/1 Imp.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BRM_006 : Imp Gang Boss")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Imp Gang Boss"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Imp");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [BRM_015] Revenge - COST:2
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 1 damage to all minions.
//       If you have 12 or less Health,
//       deal 3 damage instead.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BRM_015 : Revenge")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Revenge"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Revenge"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sleepy Dragon"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sleepy Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 11);
    CHECK_EQ(opField[0]->GetHealth(), 11);

    curPlayer->GetHero()->SetDamage(18);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(opField[0]->GetHealth(), 8);
}

// --------------------------------------- MINION - WARRIOR
// [BRM_016] Axe Flinger - COST:4 [ATK:2/HP:5]
// - Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage,
//       deal 2 damage to the enemy hero.
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BRM_016 : Axe Flinger")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Axe Flinger"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sleepy Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_019] Grim Patron - COST:5 [ATK:3/HP:3]
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: After this minion survives damage,
//       summon another Grim Patron.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_019 : Grim Patron")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grim Patron"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_020] Dragonkin Sorcerer - COST:4 [ATK:3/HP:5]
// - Race: Dragon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Whenever <b>you</b> target this minion with a spell,
//       gain +1/+1.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_020 : Dragonkin Sorcerer")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonkin Sorcerer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blessing of Kings"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blessing of Kings"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_022] Dragon Egg - COST:1 [ATK:0/HP:2]
// - Set: Brm, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever this minion takes damage,
//       summon a 2/1 Whelp.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_022 : Dragon Egg")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon Egg"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Black Whelp");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_024] Drakonid Crusher - COST:6 [ATK:6/HP:6]
// - Race: Dragon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your opponent has 15 or
//       less Health, gain +3/+3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_024 : Drakonid Crusher")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::SHAMAN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Drakonid Crusher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Drakonid Crusher"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    curPlayer->GetHero()->SetDamage(15);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 9);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_025] Volcanic Drake - COST:6 [ATK:6/HP:4]
// - Race: Dragon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: Costs (1) less for each minion that died this turn.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_025 : Volcanic Drake")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Volcanic Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer, AttackTask(card3, card5));
    CHECK_EQ(card1->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_026] Hungry Dragon - COST:4 [ATK:5/HP:6]
// - Race: Dragon, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a random 1-Cost minion
//       for your opponent.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_026 : Hungry Dragon")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hungry Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_027] Majordomo Executus - COST:9 [ATK:9/HP:7]
// - Set: Brm, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Replace your hero
//       with Ragnaros, the Firelord.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_027 : Majordomo Executus")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Majordomo Executus"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->card->name, "Ragnaros the Firelord");
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 8);
    CHECK_EQ(curPlayer->GetHeroPower().card->name, "DIE, INSECT!");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_028] Emperor Thaurissan - COST:6 [ATK:5/HP:5]
// - Set: Brm, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       reduce the Cost of cards in your hand by (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_028 : Emperor Thaurissan")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Emperor Thaurissan"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Worgen Infiltrator"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_029] Rend Blackhand - COST:7 [ATK:8/HP:4]
// - Set: Brm, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       destroy a <b>Legendary</b> minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
// - REQ_LEGENDARY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_029 : Rend Blackhand")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rend Blackhand"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card4));
    CHECK_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_030] Nefarian - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: Brm, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add 2 random spells to your hand
//       <i>(from your opponent's class)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_030 : Nefarian")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nefarian"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::WARRIOR);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::WARRIOR);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_031] Chromaggus - COST:8 [ATK:6/HP:8]
// - Race: Dragon, Set: Brm, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you draw a card,
//       put another copy into your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_031 : Chromaggus")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Flamestrike");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chromaggus"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Flamestrike");
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_033] Blackwing Technician - COST:3 [ATK:2/HP:4]
// - Faction: Neutral, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_033 : Blackwing Technician")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blackwing Technician"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blackwing Technician"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Whelp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [BRM_034] Blackwing Corruptor - COST:5 [ATK:5/HP:4]
// - Faction: Neutral, Set: Brm, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       deal 3 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BRM_034 : Blackwing Corruptor")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blackwing Corruptor"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(opField[0]->GetHealth(), 9);
}