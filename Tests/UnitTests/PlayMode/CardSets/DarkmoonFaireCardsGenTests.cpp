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

// ----------------------------------------- MINION - DRUID
// [DMF_059] Fizzy Elemental - COST:9 [ATK:10/HP:10]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DMF_059 : Fizzy Elemental")
{
    // Do nothing
}

// ------------------------------------------ SPELL - DRUID
// [DMF_730] Moontouched Amulet - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Give your hero +4 Attack this turn.
//       <b>Corrupt:</b> And gain 6 Armor.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DMF_730 : Moontouched Amulet")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& curHero = *(curPlayer->GetHero());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero.GetAttack(), 4);
    CHECK_EQ(curHero.GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_730");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_730t");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHero.GetAttack(), 4);
    CHECK_EQ(curHero.GetArmor(), 6);
}

// ---------------------------------------- MINION - HUNTER
// [DMF_083] Dancing Cobra - COST:2 [ATK:1/HP:5]
// - Race: Beast, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Corrupt:</b> Gain <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DMF_083 : Dancing Cobra")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dancing Cobra"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dancing Cobra"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_083");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_083t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasPoisonous(), true);
}

// ---------------------------------------- MINION - HUNTER
// [DMF_085] Darkmoon Tonk - COST:7 [ATK:8/HP:5]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Fire four missiles
//       at random enemies that deal 2 damage each.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DMF_085 : Darkmoon Tonk")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& opHero = *(opPlayer->GetHero());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darkmoon Tonk"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opHero.GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(opHero.GetHealth(), 22);
}

// ------------------------------------------ MINION - MAGE
// [DMF_101] Firework Elemental - COST:5 [ATK:3/HP:5]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to a minion.
//       <b>Corrupt:</b> Deal 12 instead.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DMF_101 : Firework Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Firework Elemental"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Firework Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card5));
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_101");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_101t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[0], card5));
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - PALADIN
// [DMF_064] Carousel Gryphon - COST:5 [ATK:5/HP:5]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Corrupt:</b> Gain +3/+3 and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_064 : Carousel Gryphon")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carousel Gryphon"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carousel Gryphon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[0]->HasTaunt(), false);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_064");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_064t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
}

// --------------------------------------- MINION - PALADIN
// [DMF_194] Redscale Dragontamer - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a Dragon.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_194 : Redscale Dragontamer")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Shotbot");
        config.player1Deck[i + 2] = Cards::FindCardByName("Murmy");
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Redscale Dragontamer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(card1->isDestroyed, true);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Faerie Dragon");
}

// --------------------------------------- WEAPON - PALADIN
// [DMF_238] Hammer of the Naaru - COST:6
// - Set: DARKMOON_FAIRE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 6/6 Holy Elemental
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - DMF_238 : Hammer of the Naaru")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        curPlayer, Cards::FindCardByName("Hammer of the Naaru"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Holy Elemental");
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [DMF_244] Day at the Faire - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Summon 3 Silver Hand Recruits.
//       <b>Corrupt:</b> Summon 5.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DMF_244 : Day at the Faire")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Day at the Faire"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Day at the Faire"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Explosion"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_244");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_244t");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[4]->card->name, "Silver Hand Recruit");
}

// ---------------------------------------- MINION - PRIEST
// [DMF_184] Fairground Fool - COST:3 [ATK:4/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> Gain +4 Health.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DMF_184 : Fairground Fool")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fairground Fool"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fairground Fool"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_184");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_184t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 7);
}

// ------------------------------------------ SPELL - ROGUE
// [DMF_515] Swindle - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Draw a spell.
//       <b>Combo:</b> And a minion.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DMF_515 : Swindle")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Shiv");
        config.player1Deck[i + 2] = Cards::FindCardByName("Assassin's Blade");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swindle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swindle"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[6]->card->GetCardType(), CardType::MINION);
}

// ----------------------------------------- MINION - ROGUE
// [DMF_517] Sweet Tooth - COST:2 [ATK:3/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Corrupt:</b> Gain +2 Attack and <b>Stealth</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DMF_517 : Sweet Tooth")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sweet Tooth"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sweet Tooth"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasStealth(), false);
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_517");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_517a");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasStealth(), true);
    CHECK_EQ(curField[1]->GetAttack(), 5);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_701] Dunk Tank - COST:4
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 4 damage.
//       <b>Corrupt:</b> Then deal 2 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_701 : Dunk Tank")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dunk Tank"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dunk Tank"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deep Freeze"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_701");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_701t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card5));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_702] Stormstrike - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
//       Give your hero +3 Attack this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_702 : Stormstrike")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormstrike"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earth Elemental"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ---------------------------------------- MINION - SHAMAN
// [DMF_703] Pit Master - COST:3 [ATK:1/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 3/2 Duelist.
//       <b>Corrupt:</b> Summon two.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DMF_703 : Pit Master")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Master"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Master"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Pit Master");
    CHECK_EQ(curField[1]->card->name, "Duelist");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_703");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_703t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[2]->card->name, "Duelist");
    CHECK_EQ(curField[3]->card->name, "Pit Master");
    CHECK_EQ(curField[4]->card->name, "Duelist");
}

// ---------------------------------------- MINION - SHAMAN
// [DMF_704] Cagematch Custodian - COST:2 [ATK:2/HP:2]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DMF_704 : Cagematch Custodian")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Stormforged Axe");
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

    const auto card = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cagematch Custodian"));

    game.Process(curPlayer, PlayCardTask::Spell(card));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Stormforged Axe");
}

// --------------------------------------- MINION - WARLOCK
// [DMF_114] Midway Maniac - COST:2 [ATK:1/HP:5]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_114 : Midway Maniac")
{
    // Do nothing
}

// --------------------------------------- MINION - WARRIOR
// [DMF_531] Stage Hand - COST:2 [ATK:3/HP:2]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random minion in your hand +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_531 : Stage Hand")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stage Hand"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    const int totalAttack = dynamic_cast<Minion*>(card2)->GetAttack() +
                            dynamic_cast<Minion*>(card3)->GetAttack();
    const int totalHealth = dynamic_cast<Minion*>(card2)->GetHealth() +
                            dynamic_cast<Minion*>(card3)->GetHealth();
    CHECK_EQ(totalAttack, 7);
    CHECK_EQ(totalHealth, 4);
}

// ----------------------------------- MINION - DEMONHUNTER
// [DMF_223] Renowned Performer - COST:4 [ATK:3/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Deathrattle:</b> Summon two 1/1 Assistants
//       with <b>Taunt</b>.  
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - DMF_223 : Renowned Performer")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Renowned Performer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Performer's Assistant");
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Performer's Assistant");
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [DMF_227] Dreadlord's Bite - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - DMF_227 : Dreadlord's Bite")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ----------------------------------- MINION - DEMONHUNTER
// [DMF_247] Insatiable Felhound - COST:3 [ATK:2/HP:5]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> Gain +1/+1 and <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - DMF_247 : Insatiable Felhound")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Insatiable Felhound"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Insatiable Felhound"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_247");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_247t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->HasLifesteal(), true);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_044] Rock Rager - COST:2 [ATK:5/HP:1]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_044 : Rock Rager")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_065] Banana Vendor - COST:3 [ATK:2/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add 2 Bananas to each player's hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_065 : Banana Vendor")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Banana Vendor"));

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Bananas");
    CHECK_EQ(curHand[1]->card->name, "Bananas");
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[1]->card->name, "Bananas");
    CHECK_EQ(opHand[2]->card->name, "Bananas");
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_066] Knife Vendor - COST:4 [ATK:3/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage to each hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_066 : Knife Vendor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Knife Vendor"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_067] Prize Vendor - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Both players draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_067 : Prize Vendor")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Prize Vendor"));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_073] Darkmoon Dirigible - COST:3 [ATK:3/HP:2]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Corrupt:</b> Gain <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_073 : Darkmoon Dirigible")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkmoon Dirigible"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkmoon Dirigible"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_073");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_073t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_078] Strongman - COST:7 [ATK:6/HP:6]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> This costs (0).
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_078 : Strongman")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Strongman"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deep Freeze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_078");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_078t");
    CHECK_EQ(curHand[0]->GetCost(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_080] Fleethoof Pearltusk - COST:5 [ATK:4/HP:4]
// - Race: Beast, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Corrupt:</b> Gain +4/+4.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_080 : Fleethoof Pearltusk")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fleethoof Pearltusk"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fleethoof Pearltusk"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_080");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_080t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetAttack(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_091] Wriggling Horror - COST:2 [ATK:2/HP:1]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_091 : Wriggling Horror")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wriggling Horror"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_174] Circus Medic - COST:4 [ATK:3/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 4 Health.
//       <b>Corrupt:</b> Deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_174 : Circus Medic")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Medic"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Medic"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    opHero->SetDamage(15);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 19);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_174");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_174t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opHero->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[0], opHero));
    CHECK_EQ(opHero->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_189] Costumed Entertainer - COST:2 [ATK:1/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random minion in your hand +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_189 : Costumed Entertainer")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Costumed Entertainer"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    const int totalAttack = dynamic_cast<Minion*>(card2)->GetAttack() +
                            dynamic_cast<Minion*>(card3)->GetAttack();
    const int totalHealth = dynamic_cast<Minion*>(card2)->GetHealth() +
                            dynamic_cast<Minion*>(card3)->GetHealth();
    CHECK_EQ(totalAttack, 8);
    CHECK_EQ(totalHealth, 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_190] Fantastic Firebird - COST:4 [ATK:3/HP:5]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_190 : Fantastic Firebird")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_191] Showstopper - COST:2 [ATK:3/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> <b>Silence</b> all minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_191 : Showstopper")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Showstopper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Power Infusion"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[1]->GetSpellPower(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card7, card5));
    CHECK_EQ(opField[0]->GetAttack(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(opField[1]->GetSpellPower(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetSpellPower(), 0);
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_532] Circus Amalgam - COST:4 [ATK:4/HP:5]
// - Race: All, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <i>This has all minion types.</i>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_532 : Circus Amalgam")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Amalgam"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fresh Scent"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);
}