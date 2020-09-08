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

// --------------------------------------- MINION - HUNTER
// [SCH_133] Wolpertinger - COST:1 [ATK:1/HP:1]
// - Set: Scholomance, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a copy of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[HUNTER : Minion] - SCH_133 : Wolpertinger")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::HUNTER;
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
    const auto card =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolpertinger"));

    game.Process(curPlayer, PlayCardTask::Minion(card));

    CHECK_EQ("Wolpertinger", curField[0]->card->name);
    CHECK_EQ("Wolpertinger", curField[1]->card->name);
}

// ---------------------------------------- MINION - PRIEST
// [SCH_137] Frazzled Freshman - COST:1 [ATK:1/HP:4]
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_230] Onyx Magescribe - COST:6 [ATK:4/HP:9]
//  - Race: Dragon, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Add 2 random spells
//       from your class to your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_230 : Onyx Magescribe")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Onyx Magescribe"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Explosion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->name, "Onyx Magescribe");
    CHECK_EQ(curField[0]->HasSpellburst(), true);
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::MAGE);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::MAGE);
}

// ----------------------------------------- MINION - ROGUE
// [SCH_234] Shifty Sophomore - COST:4 [ATK:4/HP:4]
//  - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Spellburst:</b> Add a
//       <b>Combo</b> card to your hand.
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shifty Sophomore"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));

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

// ----------------------------------------- MINION - DRUID
// [SCH_242] Gibberling - COST:1 [ATK:1/HP:1]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Summon a Gibberling.
// --------------------------------------------------------
TEST_CASE("[DRUID : MINION] - SCH_242 : Gibberling")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gibberling"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Savage Roar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->HasSpellburst(), true);
    CHECK_EQ(curField[1]->card->name, "Wisp");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(curField[1]->card->name, "Gibberling");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasSpellburst(), true);
    CHECK_EQ(curField[2]->card->name, "Wisp");
}

// ----------------------------------------- MINION - ROGUE
// [SCH_426] Infiltrator Lilian - COST:4 [ATK:4/HP:2]
//  - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Deathrattle:</b> Summon a
//       4/2 Forsaken Lilian that attacks a random enemy.
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
        auto curHero = curPlayer->GetHero();
        auto opHero = opPlayer->GetHero();

        const auto card1 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Infiltrator Lilian"));
        const auto card2 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Consecration"));
        const auto card3 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
        const auto card4 =
            Generic::DrawCard(opPlayer, Cards::FindCardByName("Abomination"));
        const auto card5 =
            Generic::DrawCard(opPlayer, Cards::FindCardByName("Abomination"));

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        game.Process(opPlayer, PlayCardTask::Minion(card4));
        game.Process(opPlayer, PlayCardTask::Minion(card5));

        game.Process(opPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        game.Process(curPlayer, PlayCardTask::Minion(card1));
        game.Process(curPlayer, PlayCardTask::Spell(card2));
        game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));

        // case when attack "Abomination"
        if (curField.GetCount() == 0)
        {
            CHECK_EQ(opField.GetCount(), 0);
            CHECK_EQ(curHero->GetHealth(), 26);
            CHECK_EQ(opHero->GetHealth(), 24);
        }
        // case when attack opponent hero
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

// ----------------------------------------- WEAPON - ROGUE
// [SCH_622] Self-Sharpening Sword - COST:3
//  - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
//  - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SCH_622 : Self-Sharpening Sword")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Self-Sharpening Sword"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Poison"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHero->GetAttack(), 1);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->GetAttack(), 2);
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHero->GetAttack(), 4);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->GetAttack(), 5);
    CHECK_EQ(opHero->GetHealth(), 25);
}

// ------------------------------------------ SPELL - ROGUE
// [SCH_706] Plagiarize - COST:2
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> At the end of your opponent's turn,
//       add copies of the cards they played to your hand.
// --------------------------------------------------------
// GameTag:
//  - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - SCH_706 : Plagiarize")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plagiarize"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    game.Process(opPlayer, PlayCardTask::Spell(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Arcane Missiles");
    CHECK_EQ(curHand[1]->card->name, "Blizzard");
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

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_352] Potion of Illusion - COST:4
//  - Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: Add 1/1 copies of your minions to your hand.
//       They cost (1).
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - SCH_352 : Potion of Illusion")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blazing Battlemage"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Defias Ringleader"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Edwin VanCleef"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Potion of Illusion"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Edwin VanCleef"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blazing Battlemage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 1);  // The Coin
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(opField.GetCount(), 1);

    const auto CheckMinion = [](Playable* card, bool isChanged) {
        const auto minion = dynamic_cast<Minion*>(card);
        CHECK_EQ(minion->GetCost() == 1, isChanged);
        CHECK_EQ(minion->GetAttack() == 1, isChanged);
        CHECK_EQ(minion->GetHealth() == 1, isChanged);
    };
    CheckMinion(curHand[0], false);
    CheckMinion(curHand[1], true);
    CheckMinion(curHand[2], true);
    CheckMinion(curHand[3], true);
    CheckMinion(curHand[4], true);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_509] Brain Freeze - COST:1
//  - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Freeze</b> a minion.
//       <b>Combo:</b> Also deal 3 damage to it.
// --------------------------------------------------------
// GameTag:
//  - COMBO = 1
// --------------------------------------------------------
// RefTag:
//  - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - SCH_509 : Brain Freeze")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Brain Freeze"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Brain Freeze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironfur Grizzly"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ironfur Grizzly"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->IsFrozen(), true);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_521] Coerce - COST:3
//  - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy a damaged minion.
//       <b>Combo:</b> Destroy any minion.
// --------------------------------------------------------
// GameTag:
//  - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_DAMAGED_TARGET_UNLESS_COMBO = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - SCH_521 : Coerce")
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lake Thresher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lake Thresher"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Coerce"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Coerce"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opHand.GetCount(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opHand.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_522] Steeldancer - COST:4 [ATK:4/HP:4]
//  - Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a random minion with Cost
//       equal to your weapon's Attack.
// --------------------------------------------------------
// GameTag:
//  - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_522 : Steeldancer")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Steeldancer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Steeldancer"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Steeldancer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hooked Scimitar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetCost(), 0);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->GetCost(), 1);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Weapon(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[5]->GetCost(), 4);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_623] Cutting Class - COST:5
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Draw 2 cards. Costs (1) less per Attack of your weapon.
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - SCH_623 : Cutting Class")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cutting Class"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cutting Class"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hooked Scimitar"));

    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(card1->GetCost(), 4);
    CHECK_EQ(card2->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    CHECK_EQ(card2->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_707] Fishy Flyer - COST:4 [ATK:4/HP:3]
//  - Race: Murloc, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Deathrattle:</b> Add a 4/3 Ghost
//       with <b>Rush</b> to your hand.
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
// [SCH_708] Sneaky Delinquent - COST:2 [ATK:3/HP:1]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. <b>Deathrattle:</b> Add a 3/1 Ghost
//       with <b>Stealth</b> to your hand.
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
// [SCH_709] Smug Senior - COST:6 [ATK:5/HP:7]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Deathrattle:</b> Add a 5/7 Ghost
//       with <b>Taunt</b> to your hand.
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
// [SCH_710] Ogremancer - COST:5 [ATK:3/HP:7]
//  - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever your opponent casts a spell,
//       summon a 2/2 Skeleton with <b>Taunt</b>.
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
// [SCH_711] Plagued Protodrake - COST:8 [ATK:8/HP:8]
//  - Race: Dragon, Set: SCHOLOMANCE, Rarity: Common
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
