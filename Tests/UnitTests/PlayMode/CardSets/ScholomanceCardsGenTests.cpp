// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// --------------------------------------- MINION - PALADIN
// [SCH_712] Judicious Junior - COST:6 [ATK:4/HP:9]
// - Set: Scholomance, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[PALADIN : Minion] - SCH_712 : Judicious Junior")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
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
    curPlayer->GetHero()->SetDamage(10);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Judicious Junior"));
    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);

    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
}

// ---------------------------------------- MINION - PRIEST
// [SCH_137] Frazzled Freshman - COST: 1 [ATK: 1/HP: 4]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - SCH_137 : Frazzled Freshman")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frazzled Freshman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ----------------------------------------- MINION - ROGUE
// [SCH_234] Shifty Sophomore - COST: 4 [ATK: 4/HP: 4]
//  - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       <b>Spellburst:</b> Add a <b>Combo</b> card to your hand.
// --------------------------------------------------------
// GameTag:
//  - STEALTH = 1
// --------------------------------------------------------
// RefTag:
//  - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SCH_234 : Shifty Sophomore")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(curPlayer, Cards::FindCardByName("Shifty Sophomore"));
    const auto card2 = Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card3 = Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curField[0]->HasSpellburst(), false);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->HasCombo(), true);
    CHECK_EQ(curField[0]->HasSpellburst(), false);
}

// ----------------------------------------- MINION - ROGUE
// [SCH_426] Infiltrator Lilian - COST: 4 [ATK: 4/HP: 2]
//  - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       <b>Deathrattle:</b> Summon a 4/2
//       Forsaken Lilian that attacks
//       a random enemy.
// --------------------------------------------------------
// GameTag:
//  - ELITE = 1
//  - DEATHRATTLE = 1
//  - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SCH_426 : Infiltrator Lilian")
{
    for (int i = 0; i < 10; ++i)
    {
        GameConfig config;
        config.player1Class = CardClass::ROGUE;
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
        curPlayer->GetHero()->SetHealth(30);
        opPlayer->SetTotalMana(10);
        opPlayer->SetUsedMana(0);
        opPlayer->GetHero()->SetHealth(30);

        auto& curField = *(curPlayer->GetFieldZone());
        auto& opField = *(opPlayer->GetFieldZone());
        auto curHero = curPlayer->GetHero();
        auto opHero = opPlayer->GetHero();

        const auto card1 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Infiltrator Lilian"));
        const auto card2 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Consecration"));
        const auto card3 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
        const auto card4 =
            Entity::GetFromCard(opPlayer, Cards::FindCardByName("Abomination"));
        const auto card5 =
            Entity::GetFromCard(opPlayer, Cards::FindCardByName("Abomination"));

        opField.Add(card4);
        opField.Add(card5);

        game.Process(curPlayer, PlayCardTask::Minion(card1));
        game.Process(curPlayer, PlayCardTask::Spell(card2));

        game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));

        // case when attack Abomination
        if (curField.GetCount() == 0)
        {
            CHECK_EQ(opField.GetCount(), 0);
            CHECK_EQ(curHero->GetHealth(), 26);
            CHECK_EQ(opHero->GetHealth(), 24);
        }
        // case when attack OpHero
        else if (curField.GetCount() == 1)
        {
            CHECK_EQ(opField.GetCount(), 2);
            CHECK_EQ(curHero->GetHealth(), 30);
            CHECK_EQ(opHero->GetHealth(), 24);
        }
        else
        {
            CHECK(false);
        }
    }
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_231] Intrepid Initiate - COST:1 [ATK:1/HP:2]
// - Set: Scholomance, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Gain +2 Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_231 : Intrepid Initiate")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        curPlayer, Cards::FindCardByName("Intrepid Initiate"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->HasSpellburst(), false);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->HasSpellburst(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_707] Fishy Flyer - COST: 4 [ATK: 4/HP: 3]
//  - Race: MURLOC, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Deathrattle:</b> Add a 4/3 Ghost with <b>Rush</b>
// to your hand.
// --------------------------------------------------------
// GameTag:
//  - DEATHRATTLE = 1
//  - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_707 : Fishy Flyer")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fishy Flyer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Assassinate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Spectral Flyer");
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_708] Sneaky Delinquent - COST: 2 [ATK: 3/HP: 1]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. <b>Deathrattle:</b> Add a 3/1 Ghost with
// <b>Stealth</b> to your hand.
// --------------------------------------------------------
// GameTag:
//  - DEATHRATTLE = 1
//  - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_708 : Sneaky Delinquent")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sneaky Delinquent"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Holy Nova"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Spectral Delinquent");
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_709] Smug Senior - COST: 6 [ATK: 5/HP: 7]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Deathrattle:</b> Add a 5/7 Ghost with <b>Taunt</b>
// to your hand.
// --------------------------------------------------------
// GameTag:
//  - DEATHRATTLE = 1
//  - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_709 : Smug Senior")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Smug Senior"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Assassinate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Spectral Senior");
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_710] Ogremancer - COST: 5 [ATK: 3/HP: 7]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever your opponent
//       casts a spell, summon a 2/2
//       Skeleton with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
//  - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
//  - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_710 : Ogremancer")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ogremancer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frost Nova"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Risen Skeleton");

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Risen Skeleton");
    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(curField[2]->IsFrozen(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_711] Plagued Protodrake - COST: 8 [ATK: 8/HP: 8]
//  - Race: DRAGON, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random 7-Cost minion.
// --------------------------------------------------------
// GameTag:
//  - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_711 : Plagued Protodrake")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Plagued Protodrake"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Assassinate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetCost(), 7);
}
