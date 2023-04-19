// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ---------------------------------------- MINION - HUNTER
// [ICC_419] Bearshark - COST:3 [ATK:4/HP:3]
// - Race: Beast, Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ICC_419 : Bearshark")
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - ICC_038 : Righteous Protector")
{
    // Do nothing
}

// ----------------------------------------- MINION - ROGUE
// [ICC_809] Plague Scientist - COST:3 [ATK:2/HP:3]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Give a friendly minion <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - ICC_809 : Plague Scientist")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->HasPoisonous(), true);
    CHECK_EQ(curField[1]->HasPoisonous(), false);
}

// ---------------------------------------- SPELL - WARLOCK
// [ICC_055] Drain Soul - COST:2
// - Set: Icecrown, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 3 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - ICC_055 : Drain Soul")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Drain Soul"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sen'jin Shieldmasta"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [ICC_026] Grim Necromancer - COST:4 [ATK:2/HP:4]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Skeletons.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ICC_026 : Grim Necromancer")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grim Necromancer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Skeleton");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Grim Necromancer");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->card->name, "Skeleton");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [ICC_029] Cobalt Scalebane - COST:5 [ATK:5/HP:5]
// - Race: Dragon, Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +3 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ICC_029 : Cobalt Scalebane")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cobalt Scalebane"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}