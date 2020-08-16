// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ----------------------------------------- HERO - WARLOCK
// [DRG_600] Galakrond, the Wretched - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 1 random Demon. <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55807
// - 676 = 1
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero] - DRG_600 : Galakrond, the Wretched")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Galakrond, the Wretched"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetRace(), Race::DEMON);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Draconic Imp");
    CHECK_EQ(curField[2]->card->name, "Draconic Imp");
}

// ----------------------------------------- HERO - WARLOCK
// [DRG_600t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 2 random Demons. <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55807
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero] - DRG_600t2 : Galakrond, the Apocalypse")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_600t2"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curField[1]->card->GetRace(), Race::DEMON);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[2]->card->name, "Draconic Imp");
    CHECK_EQ(curField[3]->card->name, "Draconic Imp");
}

// ----------------------------------------- HERO - WARLOCK
// [DRG_600t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 4 random Demons.
//       Equip a 5/2 Claw.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55807
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero] - DRG_600t3 : Galakrond, Azeroth's End")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_600t3"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curField[1]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curField[2]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curField[3]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[4]->card->name, "Draconic Imp");
    CHECK_EQ(curField[5]->card->name, "Draconic Imp");
}

// ------------------------------------------- HERO - ROGUE
// [DRG_610] Galakrond, the Nightmare - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 1 card. It costs (1).
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55806
// - 676 = 1
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Hero] - DRG_610 : Galakrond, the Nightmare")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Galakrond, the Nightmare"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[3]->GetCost(), 4);
    CHECK_EQ(curHand[4]->GetCost(), 1);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->IsLackey(), true);
}

// ------------------------------------------- HERO - ROGUE
// [DRG_610t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 2 cards. They cost (1).
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55806
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Hero] - DRG_610t2 : Galakrond, the Apocalypse")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_610t2"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[3]->GetCost(), 4);
    CHECK_EQ(curHand[4]->GetCost(), 1);
    CHECK_EQ(curHand[5]->GetCost(), 1);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[6])->IsLackey(), true);
}

// ------------------------------------------- HERO - ROGUE
// [DRG_610t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 4 cards. They cost (1).
//       Equip a 5/2 Claw.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55806
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Hero] - DRG_610t3 : Galakrond, Azeroth's End")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_610t3"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[3]->GetCost(), 4);
    CHECK_EQ(curHand[4]->GetCost(), 1);
    CHECK_EQ(curHand[5]->GetCost(), 1);
    CHECK_EQ(curHand[6]->GetCost(), 1);
    CHECK_EQ(curHand[7]->GetCost(), 1);
    CHECK_EQ(curPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 9);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[8])->IsLackey(), true);
}

// ------------------------------------------ HERO - SHAMAN
// [DRG_620] Galakrond, the Tempest - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 2/2 Storms with <b>Rush</b>.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55808
// - 676 = 1
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Hero] - DRG_620 : Galakrond, the Tempest")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Galakrond, the Tempest"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Brewing Storm");
    CHECK_EQ(curField[0]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[1]->card->name, "Brewing Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasRush(), true);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// ------------------------------------------ HERO - SHAMAN
// [DRG_620t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 4/4 Storms with <b>Rush</b>.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55808
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Hero] - DRG_620t2 : Galakrond, the Apocalypse")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_620t2"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Living Storm");
    CHECK_EQ(curField[0]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[1]->card->name, "Living Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->HasRush(), true);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// ------------------------------------------ HERO - SHAMAN
// [DRG_620t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 8/8 Storms with <b>Rush</b>.
//       Equip a 5/2 Claw.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55808
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Hero] - DRG_620t3 : Galakrond, Azeroth's End")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_620t3"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Raging Storm");
    CHECK_EQ(curField[0]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[1]->card->name, "Raging Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// ----------------------------------------- HERO - WARRIOR
// [DRG_650] Galakrond, the Unbreakable - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 1 minion. Give it +4/+4.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55805
// - 676 = 1
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Hero] - DRG_650 : Galakrond, the Unbreakable")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Galakrond, the Unbreakable"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 5);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->CanAttack(), true);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ----------------------------------------- HERO - WARRIOR
// [DRG_650t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 2 minions. Give them +4/+4.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55805
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Hero] - DRG_650t2 : Galakrond, the Apocalypse")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_650t2"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetHealth(), 5);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->CanAttack(), true);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ----------------------------------------- HERO - WARRIOR
// [DRG_650t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 4 minions. Give them +4/+4.
//       Equip a 5/2 Claw.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55805
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Hero] - DRG_650t3 : Galakrond, Azeroth's End")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DRG_650t3"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[6])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[6])->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[7])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[7])->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->CanAttack(), true);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);
}

// ------------------------------------------ HERO - PRIEST
// [DRG_660] Galakrond, the Unspeakable - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy 1 random enemy minion.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55810
// - 676 = 1
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Hero] - DRG_660 : Galakrond, the Unspeakable")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
    opPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Galakrond, the Unspeakable"));

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opHand[6]->card->GetCardClass(), CardClass::PRIEST);
}

// ------------------------------------------ HERO - PRIEST
// [DRG_660t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy 2 random enemy minions.
//       <i>(@)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_2 = 2
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55810
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Hero] - DRG_660t2 : Galakrond, the Apocalypse")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
    opPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DRG_660t2"));

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opHand[6]->card->GetCardClass(), CardClass::PRIEST);
}

// ------------------------------------------ HERO - PRIEST
// [DRG_660t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy 4 random enemy minions.
//       Equip a 5/2 Claw.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - ARMOR = 5
// - HERO_POWER = 55810
// - GALAKROND_HERO_CARD = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Hero] - DRG_660t3 : Galakrond, Azeroth's End")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
    opPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DRG_660t3"));

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(opPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(opPlayer->GetWeapon().GetDurability(), 2);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opHand[6]->card->GetCardClass(), CardClass::PRIEST);
}

// ------------------------------------------ SPELL - DRUID
// [DRG_051] Strength in Numbers - COST:1
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Spend 10 Mana on minions.
//       <b>Reward:</b> Summon a minion from your deck.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 10
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_051 : Strength in Numbers")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Strength in Numbers"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(quest->GetQuestProgress(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(quest->GetQuestProgress(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(quest->GetQuestProgress(), 12);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 24);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Wisp");
}

// ------------------------------------------ SPELL - DRUID
// [DRG_311] Treenforcements - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give a minion +2 Health and
//       <b>Taunt</b>; or Summon a 2/2 Treant.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_311 : Treenforcements")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Treenforcements"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Treenforcements"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, curField[0], 2));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// ----------------------------------------- MINION - DRUID
// [DRG_312] Shrubadier - COST:2 [ATK:1/HP:1]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/2 Treant.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DRG_312 : Shrubadier")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shrubadier"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shrubadier"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Treant");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Shrubadier");
    CHECK_EQ(curField[1]->card->name, "Shrubadier");
    CHECK_EQ(curField[2]->card->name, "Treant");
    CHECK_EQ(curField[3]->card->name, "Treant");
}

// ----------------------------------------- MINION - DRUID
// [DRG_313] Emerald Explorer - COST:6 [ATK:4/HP:8]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DRG_313 : Emerald Explorer")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Emerald Explorer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }
}

// ------------------------------------------ SPELL - DRUID
// [DRG_314] Aeroponics - COST:5
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Draw 2 cards.
//       Costs (2) less for each Treant you control.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_314 : Aeroponics")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Aeroponics"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shrubadier"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shrubadier"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shrubadier"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card1->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(card1->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, curField[1]));
    CHECK_EQ(card1->GetCost(), 1);
}

// ------------------------------------------ SPELL - DRUID
// [DRG_315] Embiggen - COST:0
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Give all minions in your deck +2/+2.
//       They cost (1) more <i>(up to 10)</i>.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_315 : Embiggen")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Embiggen"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Embiggen"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetCost(), 9);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetCost(), 9);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetCost(), 9);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetCost(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 14);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetCost(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetAttack(), 8);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetHealth(), 16);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetCost(), 10);
}

// ------------------------------------------ SPELL - DRUID
// [DRG_317] Secure the Deck - COST:1
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Attack twice with your hero.
//       <b>Reward:</b> Add 3 'Claw' spells to your hand.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 2
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_317 : Secure the Deck")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Secure the Deck"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 2);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(quest->GetQuestProgress(), 2);
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[0]->card->name, "Claw");
    CHECK_EQ(curHand[1]->card->name, "Claw");
    CHECK_EQ(curHand[2]->card->name, "Claw");
}

// ------------------------------------------ SPELL - DRUID
// [DRG_318] Breath of Dreams - COST:2
// - Faction: Neutral, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a card. If you're holding a Dragon,
//       gain an empty Mana Crystal.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DRG_318 : Breath of Dreams")
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
    curPlayer->SetTotalMana(3);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Breath of Dreams"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Breath of Dreams"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curPlayer->GetTotalMana(), 4);
    CHECK_EQ(curPlayer->GetUsedMana(), 3);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 6);

    curPlayer->SetTotalMana(3);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curPlayer->GetTotalMana(), 3);
    CHECK_EQ(curPlayer->GetUsedMana(), 2);
}

// ----------------------------------------- MINION - DRUID
// [DRG_319] Goru the Mightree - COST:7 [ATK:5/HP:10]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> For the rest of
//       the game, your Treants have +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DRG_319 : Goru the Mightree")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID("DAL_256t2");
        config.player2Deck[i] = Cards::FindCardByID("DAL_256t2");
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goru the Mightree"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goru the Mightree"));

    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetHealth(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetHealth(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[3]->GetAttack(), 4);
    CHECK_EQ(curField[3]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[3])->GetHealth(), 4);
}

// ----------------------------------------- MINION - DRUID
// [DRG_320] Ysera, Unleashed - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle 7 Dream Portals into your deck.
//       When drawn, summon a random Dragon.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DRG_320 : Ysera, Unleashed")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ysera, Unleashed"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curDeck.GetCount(), 7);
    for (int i = 0; i < 7; ++i)
    {
        CHECK_EQ(curDeck[i]->card->name, "Dream Portal");
    }

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 7);
    for (int i = 0; i < 7; ++i)
    {
        CHECK_EQ(curField[i]->card->GetRace(), Race::DRAGON);
    }
}

// ----------------------------------------- SPELL - HUNTER
// [DRG_006] Corrosive Breath - COST:2
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage to a minion. If you're holding
//       a Dragon, it also hits the enemy hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DRG_006 : Corrosive Breath")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Corrosive Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Corrosive Breath"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// ---------------------------------------- WEAPON - HUNTER
// [DRG_007] Stormhammer - COST:3 [ATK:3/HP:0]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Doesn't lose Durability while you control a Dragon.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - DRG_007 : Stormhammer")
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormhammer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Brightwing"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHero->weapon->GetAttack(), 3);
    CHECK_EQ(curHero->weapon->GetDurability(), 2);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->weapon->GetDurability(), 1);
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHero->weapon->IsImmune(), true);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->weapon->GetDurability(), 1);
    CHECK_EQ(opHero->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curHero->weapon->IsImmune(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->weapon, nullptr);
    CHECK_EQ(opHero->GetHealth(), 21);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_010] Diving Gryphon - COST:3 [ATK:4/HP:1]
// - Race: Beast, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Battlecry:</b> Draw a
//       <b>Rush</b> minion from your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_010 : Diving Gryphon")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Restless Mummy");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Diving Gryphon"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Diving Gryphon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Restless Mummy");

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 5);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_095] Veranus - COST:6 [ATK:7/HP:6]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Change the Health of all enemy minions to 1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_095 : Veranus")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Wyrm"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Water Elemental"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Veranus"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Phase Stalker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - HUNTER
// [DRG_251] Clear the Way - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Summon 3 <b>Rush</b> minions.
//       <b>Reward:</b> Summon a 4/4 Gryphon with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 3
// - SIDEQUEST = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DRG_251 : Clear the Way")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Clear the Way"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Hogsteed"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Hogsteed"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Hogsteed"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(quest->GetQuestProgress(), 3);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->card->name, "Gryphon");
    CHECK_EQ(curField[3]->GetAttack(), 4);
    CHECK_EQ(curField[3]->GetHealth(), 4);
    CHECK_EQ(curField[3]->HasRush(), true);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_252] Phase Stalker - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: After you use your Hero Power,
//       cast a <b>Secret</b> from your deck.
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_252 : Phase Stalker")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 7; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Snake Trap");
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Phase Stalker"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(curSecret[0]->card->name, "Snake Trap");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 1);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curSecret.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curSecret.GetCount(), 0);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_253] Dwarven Sharpshooter - COST:1 [ATK:1/HP:3]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Your Hero Power can target minions.
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_253 : Dwarven Sharpshooter")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dwarven Sharpshooter"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_254] Primordial Explorer - COST:3 [ATK:2/HP:3]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Poisonous</b>
//       <b>Battlecry:</b> <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - POISONOUS = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_254 : Primordial Explorer")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Primordial Explorer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }
}

// ----------------------------------------- SPELL - HUNTER
// [DRG_255] Toxic Reinforcements - COST:1
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Use your Hero Power three times.
//       <b>Reward:</b> Summon three 1/1 Leper Gnomes.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 3
// - QUEST_REWARD_DATABASE_ID = 41127
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DRG_255 : Toxic Reinforcements")
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
        curPlayer, Cards::FindCardByName("Toxic Reinforcements"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 3);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 3);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->id, "DRG_255t2");
    CHECK_EQ(curField[1]->card->id, "DRG_255t2");
    CHECK_EQ(curField[2]->card->id, "DRG_255t2");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - HUNTER
// [DRG_256] Dragonbane - COST:4 [ATK:3/HP:5]
// - Race: Mechanical, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: After you use your Hero Power,
//       deal 5 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DRG_256 : Dragonbane")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dragonbane"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, HeroPowerTask());
    const bool check = (curPlayer->GetHero()->GetHealth() == 23 &&
                        curField[0]->GetHealth() == 12) ||
                       (curPlayer->GetHero()->GetHealth() == 28 &&
                        curField[0]->GetHealth() == 7);
    CHECK_EQ(check, true);
}

// ------------------------------------------ MINION - MAGE
// [DRG_102] Azure Explorer - COST:4 [ATK:2/HP:3]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +2</b>
//       <b>Battlecry:</b> <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 2
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_102 : Azure Explorer")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azure Explorer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }
}

// ------------------------------------------ MINION - MAGE
// [DRG_104] Chenvaala - COST:3 [ATK:2/HP:5]
// - Race: Elemental, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: After you cast three spells in a turn,
//       summon a 5/5 Elemental.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_104 : Chenvaala")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chenvaala"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 0);

    game.Process(opPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 0);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Snow Elemental");
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 0);
}

// ------------------------------------------- SPELL - MAGE
// [DRG_106] Arcane Breath - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to a minion. If you're holding a Dragon,
//       <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DRG_106 : Arcane Breath")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Breath"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opField[0]->GetHealth(), 10);
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::MAGE));
    }

    Generic::ChoicePick(curPlayer, 27);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetHealth(), 8);
    CHECK(curPlayer->choice == nullptr);
}

// ------------------------------------------ MINION - MAGE
// [DRG_107] Violet Spellwing - COST:1 [ATK:1/HP:1]
// - Race: Elemental, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add an 'Arcane Missiles' spell
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_107 : Violet Spellwing")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Violet Spellwing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Arcane Missiles");
}

// ------------------------------------------ MINION - MAGE
// [DRG_109] Mana Giant - COST:8 [ATK:8/HP:8]
// - Race: Elemental, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each card you've played this
//       game that didn't start in your deck.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_109 : Mana Giant")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Missiles"));

    CHECK_EQ(card1->GetCost(), 8);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 3);
}

// ------------------------------------------ MINION - MAGE
// [DRG_270] Malygos, Aspect of Magic - COST:5 [ATK:2/HP:8]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       <b>Discover</b> an upgraded Mage spell.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_270 : Malygos, Aspect of Magic")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos, Aspect of Magic"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos, Aspect of Magic"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->GetCardClass(), CardClass::MAGE);
    }

    Generic::ChoicePick(curPlayer, 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice == nullptr);
}

// ------------------------------------------- SPELL - MAGE
// [DRG_321] Rolling Fireball - COST:5
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 8 damage to a minion. Any excess damage
//       continues to the left or right.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DRG_321 : Rolling Fireball")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rolling Fireball"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Archmage"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    opPlayer->SetUsedMana(0);
    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    const bool check1 =
        opField.GetCount() == 4 && opField[0]->card->name == "Oasis Snapjaw" &&
        opField[0]->GetHealth() == 5 && opField[1]->card->name == "Wisp" &&
        opField[2]->card->name == "Wisp" &&
        opField[3]->card->name == "Wolfrider";
    const bool check2 =
        opField.GetCount() == 2 && opField[0]->card->name == "Oasis Snapjaw" &&
        opField[0]->GetHealth() == 7 && opField[1]->card->name == "Wolfrider";
    const bool check = check1 || check2;
    CHECK_EQ(check, true);
}

// ------------------------------------------ MINION - MAGE
// [DRG_322] Dragoncaster - COST:7 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       your next spell this turn costs (0).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DRG_322 : Dragoncaster")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragoncaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragoncaster"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragoncaster"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card5->GetCost(), 4);
    CHECK_EQ(card6->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card5->GetCost(), 0);
    CHECK_EQ(card6->GetCost(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(card6->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card6->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card6->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card6->GetCost(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card6->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card6->GetCost(), 4);
}

// ------------------------------------------- SPELL - MAGE
// [DRG_323] Learn Draconic - COST:1
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Spend 8 Mana on spells.
//       <b>Reward:</b> Summon a 6/6 Dragon.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 8
// - QUEST_REWARD_DATABASE_ID = 55282
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DRG_323 : Learn Draconic")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Learn Draconic"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 8);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(quest->GetQuestProgress(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Draconic Emissary");
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->card->GetRace(), Race::DRAGON);
}

// ------------------------------------------- SPELL - MAGE
// [DRG_324] Elemental Allies - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Play an Elemental 2 turns in a row.
//       <b>Reward:</b> Draw 3 spells from your deck.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 2
// - QUEST_REWARD_DATABASE_ID = 395
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DRG_324 : Elemental Allies")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player2Deck[i] = Cards::FindCardByName("Fireball");
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elemental Allies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 23);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 8);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(quest->GetQuestProgress(), 2);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 20);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 10);
}

// ---------------------------------------- SPELL - PALADIN
// [DRG_008] Righteous Cause - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Summon 5 minions.
//       <b>Reward:</b> Give your minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 5
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DRG_008 : Righteous Cause")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Righteous Cause"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(quest->GetQuestProgress(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(quest->GetQuestProgress(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(quest->GetQuestProgress(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(quest->GetQuestProgress(), 4);
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(quest->GetQuestProgress(), 5);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 2);
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
}

// --------------------------------------- MINION - PALADIN
// [DRG_225] Sky Claw - COST:3 [ATK:1/HP:2]
// - Race: Mechanical, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Your other Mechs have +1 Attack.
//       <b>Battlecry:</b> Summon two 1/1 Microcopters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_225 : Sky Claw")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sky Claw"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sky Claw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Microcopter");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Sky Claw");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Microcopter");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[0]->card->name, "Microcopter");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Sky Claw");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Microcopter");
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Microcopter");
    CHECK_EQ(curField[3]->GetAttack(), 3);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[4]->card->name, "Sky Claw");
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);
    CHECK_EQ(curField[5]->card->name, "Microcopter");
    CHECK_EQ(curField[5]->GetAttack(), 3);
    CHECK_EQ(curField[5]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Microcopter");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Sky Claw");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Microcopter");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Microcopter");
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[4]->card->name, "Microcopter");
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 1);
}

// --------------------------------------- MINION - PALADIN
// [DRG_226] Amber Watcher - COST:5 [ATK:4/HP:6]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 8 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_226 : Amber Watcher")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    opField[0]->SetDamage(6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);
}

// --------------------------------------- MINION - PALADIN
// [DRG_229] Bronze Explorer - COST:3 [ATK:2/HP:3]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       <b>Battlecry:</b> <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - LIFESTEAL = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_229 : Bronze Explorer")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Explorer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }
}

// --------------------------------------- MINION - PALADIN
// [DRG_231] Lightforged Crusader - COST:7 [ATK:7/HP:7]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no Neutral cards,
//       add 5 random Paladin cards to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_231 : Lightforged Crusader")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (std::size_t i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = Cards::FindCardByName("Leper Gnome");
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
        curPlayer, Cards::FindCardByName("Lightforged Crusader"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightforged Crusader"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 10);
    for (std::size_t i = 5; i < 10; ++i)
    {
        CHECK_EQ(curHand[i]->card->GetCardClass(), CardClass::PALADIN);
    }
}

// --------------------------------------- MINION - PALADIN
// [DRG_232] Lightforged Zealot - COST:4 [ATK:4/HP:2]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no Neutral cards,
//       equip a 4/2 Truesilver Champion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_232 : Lightforged Zealot")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (std::size_t i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = Cards::FindCardByName("Leper Gnome");
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightforged Zealot"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightforged Zealot"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 4);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// ---------------------------------------- SPELL - PALADIN
// [DRG_233] Sand Breath - COST:1
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +1/+2. Give it <b>Divine Shield</b>
//       if you're holding a Dragon.
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DRG_233 : Sand Breath")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sand Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sand Breath"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 12);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 14);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
}

// --------------------------------------- MINION - PALADIN
// [DRG_235] Dragonrider Talritha - COST:3 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give a Dragon in your hand +3/+3
//       and this <b>Deathrattle</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_235 : Dragonrider Talritha")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonrider Talritha"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    auto minion2 = dynamic_cast<Minion*>(card2);
    auto minion3 = dynamic_cast<Minion*>(card3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(minion2->GetAttack(), 4);
    CHECK_EQ(minion2->GetHealth(), 6);
    CHECK_EQ(minion3->GetAttack(), 4);
    CHECK_EQ(minion3->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    bool check1 = (minion2->GetAttack() == 7 && minion2->GetHealth() == 9 &&
                   minion2->HasDeathrattle() == true &&
                   minion3->GetAttack() == 4 && minion3->GetHealth() == 6);
    bool check2 = (minion2->GetAttack() == 4 && minion2->GetHealth() == 6 &&
                   minion3->GetAttack() == 7 && minion3->GetHealth() == 9 &&
                   minion3->HasDeathrattle() == true);
    bool check = check1 || check2;
    CHECK_EQ(check, true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    if (check1)
    {
        game.Process(curPlayer,
                     PlayCardTask::MinionTarget(card2, curPlayer->GetHero()));
    }
    else
    {
        game.Process(curPlayer,
                     PlayCardTask::MinionTarget(card3, curPlayer->GetHero()));
    }
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, curField[0]));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 7);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 9);
    CHECK_EQ(curHand[0]->HasDeathrattle(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [DRG_258] Sanctuary - COST:2
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Take no damage for a turn.
//       <b>Reward:</b> Summon a 3/6 minion with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 1
// - QUEST_REWARD_DATABASE_ID = 57723
// - SIDEQUEST = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DRG_258 : Sanctuary")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sanctuary"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Indomitable Champion");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - PALADIN
// [DRG_309] Nozdormu the Timeless - COST:4 [ATK:8/HP:8]
// - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Set each player to 10 Mana Crystals.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DRG_309 : Nozdormu the Timeless")
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
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(5);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nozdormu the Timeless"));

    CHECK_EQ(curPlayer->GetTotalMana(), 4);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
    CHECK_EQ(opPlayer->GetTotalMana(), 5);
    CHECK_EQ(opPlayer->GetUsedMana(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetTotalMana(), 10);
    CHECK_EQ(curPlayer->GetUsedMana(), 10);
    CHECK_EQ(opPlayer->GetTotalMana(), 10);
    CHECK_EQ(opPlayer->GetUsedMana(), 5);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_090] Murozond the Infinite - COST:8 [ATK:8/HP:8]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Play all cards your opponent
//       played last turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_090 : Murozond the Infinite")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Block"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murozond the Infinite"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(opPlayer->GetHero()->weapon->card->name, "Fiery War Axe");
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[1]->card->name, "Wolfrider");
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);
}

// ----------------------------------------- SPELL - PRIEST
// [DRG_246] Time Rip - COST:5
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy a minion. <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DRG_246 : Time Rip")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player2Deck[0] =
        Cards::FindCardByName("Galakrond, the Unspeakable");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Whispers of EVIL"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[2]->card->GetCardClass(), CardClass::PRIEST);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_300] Fate Weaver - COST:4 [ATK:3/HP:6]
// - Race: Dragon, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
//       reduce the Cost of cards in your hand by (1).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// --------------------------------------------------------
// RefTag:
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_300 : Fate Weaver")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fate Weaver"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fate Weaver"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 4);
    CHECK_EQ(card5->GetCost(), 9);

    curPlayer->IncreaseInvoke();
    curPlayer->IncreaseInvoke();

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 3);
    CHECK_EQ(card5->GetCost(), 8);
}

// ----------------------------------------- SPELL - PRIEST
// [DRG_301] Whispers of EVIL - COST:0
// - Faction: Neutral, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Add a <b>Lackey</b> to your hand.
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DRG_301 : Whispers of EVIL")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whispers of EVIL"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsLackey(), true);
}

// ----------------------------------------- SPELL - PRIEST
// [DRG_302] Grave Rune - COST:4
// - Faction: Neutral, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion "<b>Deathrattle:</b> Summon 2 copies of this."
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DRG_302 : Grave Rune")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grave Rune"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(curField[1]->card->name, "Wolfrider");
    CHECK_EQ(curField[1]->HasDeathrattle(), false);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_303] Disciple of Galakrond - COST:1 [ATK:1/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DRG_303 : Disciple of Galakrond")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] =
        Cards::FindCardByName("Galakrond, the Unspeakable");

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
        curPlayer, Cards::FindCardByName("Disciple of Galakrond"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Disciple of Galakrond"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Disciple of Galakrond"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Disciple of Galakrond"));

    CHECK_EQ(curPlayer->GetInvoke(), 0);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetInvoke(), 2);
    CHECK_EQ(curHand[0]->card->id, "DRG_660t2");
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetInvoke(), 3);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curPlayer->GetInvoke(), 4);
    CHECK_EQ(curHand[0]->card->id, "DRG_660t3");
    CHECK_EQ(curHand.GetCount(), 5);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_304] Chronobreaker - COST:5 [ATK:4/HP:5]
// - Race: Dragon, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> If you're holding a Dragon,
//       deal 3 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_304 : Chronobreaker")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chronobreaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chronobreaker"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card9 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));

    opPlayer->SetUsedMana(0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card8, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card7));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card9, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Malygos");
    CHECK_EQ(curField[1]->GetHealth(), 12);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(opField[1]->card->name, "Wisp");
    CHECK_EQ(opField[1]->GetHealth(), 1);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_306] Envoy of Lazul - COST:2 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Look at 3 cards.
//       Guess which one is in your opponent's hand
//       to get a copy of it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_306 : Envoy of Lazul")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 10; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
    }
    for (int i = 10; i < 20; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
    }
    for (int i = 20; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Blizzard");
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

    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Envoy of Lazul"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK(opPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    Generic::ChoicePick(opPlayer, 36);

    const bool check =
        ((opHand.GetCount() == 1) ||
         (opHand.GetCount() == 2 && opHand[1]->card->name == "Wisp"));
    CHECK_EQ(check, true);
}

// ----------------------------------------- SPELL - PRIEST
// [DRG_307] Breath of the Infinite - COST:3
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to all minions.
//       If you're holding a Dragon, only damage enemies.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_307 : Breath of the Infinite")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Breath of the Infinite"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Breath of the Infinite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opField[0]->GetHealth(), 10);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Malygos");
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// ---------------------------------------- MINION - PRIEST
// [DRG_308] Mindflayer Kaahrj - COST:3 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose an enemy minion.
//       <b>Deathrattle:</b> Summon a new copy of it.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DRG_308 : Mindflayer Kaahrj")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mindflayer Kaahrj"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(opField[0]->HasDeathrattle(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 12);
}

// ----------------------------------------- MINION - ROGUE
// [DRG_027] Umbral Skulker - COST:4 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
//       add 3 Coins to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// --------------------------------------------------------
// RefTag:
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_027 : Umbral Skulker")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Umbral Skulker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Umbral Skulker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    curPlayer->IncreaseInvoke();
    curPlayer->IncreaseInvoke();

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[0]->card->name, "The Coin");
    CHECK_EQ(curHand[1]->card->name, "The Coin");
    CHECK_EQ(curHand[2]->card->name, "The Coin");
}

// ------------------------------------------ SPELL - ROGUE
// [DRG_028] Dragon's Hoard - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Discover</b> a <b>Legendary</b> minion
//       from another class.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DRG_028 : Dragon's Hoard")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon's Hoard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRarity(), Rarity::LEGENDARY);

        bool check = (card->GetCardClass() !=
                      curPlayer->GetHero()->card->GetCardClass()) &&
                     (card->GetCardClass() != CardClass::NEUTRAL);
        CHECK_EQ(check, true);
    }
}

// ------------------------------------------ SPELL - ROGUE
// [DRG_030] Praise Galakrond! - COST:1
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +1 Attack. <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DRG_030 : Praise Galakrond!")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Nightmare");

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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Praise Galakrond!"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->IsLackey(), true);
}

// ----------------------------------------- MINION - ROGUE
// [DRG_031] Necrium Apothecary - COST:5 [ATK:2/HP:5]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Combo:</b> Draw a <b>Deathrattle</b> minion
//       from your deck and gain its <b>Deathrattle</b>.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_031 : Necrium Apothecary")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (std::size_t i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = Cards::FindCardByName("Leper Gnome");
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Necrium Apothecary"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Necrium Apothecary"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Necrium Apothecary"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curField[0]->HasDeathrattle(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Leper Gnome");
    CHECK_EQ(curField[1]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[5]));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curField[2]->HasDeathrattle(), false);
}

// ------------------------------------------ SPELL - ROGUE
// [DRG_033] Candle Breath - COST:6
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Draw 3 cards.
//       Costs (3) less while you're holding a Dragon.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DRG_033 : Candle Breath")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Candle Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);
}

// ----------------------------------------- MINION - ROGUE
// [DRG_034] Stowaway - COST:5 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If there are cards in your deck
//       that didn't start there, draw 2 of them.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_034 : Stowaway")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stowaway"));

    game.Process(curPlayer, AddCardTask(EntityType::DECK, "EX1_537", 3));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Explosive Shot");
    CHECK_EQ(curHand[5]->card->name, "Explosive Shot");
}

// ----------------------------------------- MINION - ROGUE
// [DRG_035] Bloodsail Flybooter - COST:1 [ATK:1/HP:1]
// - Race: Pirate, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add two 1/1 Pirates to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_035 : Bloodsail Flybooter")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodsail Flybooter"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Sky Pirate");
    CHECK_EQ(curHand[5]->card->name, "Sky Pirate");
}

// ----------------------------------------- MINION - ROGUE
// [DRG_036] Waxadred - COST:5 [ATK:7/HP:5]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle a Candle into your deck
//       that resummons Waxadred when drawn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_036 : Waxadred")
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Waxadred"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curDeck[0]->card->name, "Waxadred's Candle");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Waxadred");
}

// ----------------------------------------- MINION - ROGUE
// [DRG_037] Flik Skyshiv - COST:6 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a minion and all copies
//       of it <i>(wherever they are)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DRG_037 : Flik Skyshiv")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& opField = *(opPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flik Skyshiv"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opDeck.GetCount(), 25);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 1);
    CHECK_EQ(opDeck.GetCount(), 0);
}

// ------------------------------------------ SPELL - ROGUE
// [DRG_247] Seal Fate - COST:3
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 3 damage to an undamaged character.
//       <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_UNDAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DRG_247 : Seal Fate")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Nightmare");

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Seal Fate"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Seal Fate"));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->IsLackey(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curHand.GetCount(), 3);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_096] Bandersmosh - COST:5 [ATK:5/HP:5]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: Each turn this is in your hand, transform it into a
//       5/5 copy of a random <b>Legendary</b> minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_096 : Bandersmosh")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bandersmosh"));

    CHECK_EQ(card1->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 5);
    CHECK_EQ(card1->GetGameTag(GameTag::HEALTH), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand[4]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::ATK), 5);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::HEALTH), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand[4]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::ATK), 5);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::HEALTH), 5);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_211] Squallhunter - COST:4 [ATK:5/HP:7]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +2</b> <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 2
// - OVERLOAD = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_211 : Squallhunter")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [DRG_215] Storm's Wrath - COST:1
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Give your minions +1/+1. <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DRG_215 : Storm's Wrath")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Storm's Wrath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_216] Surging Tempest - COST:1 [ATK:1/HP:3]
// - Race: Elemental, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Has +1 Attack while you have <b>Overloaded</b>
//       Mana Crystals.
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_216 : Surging Tempest")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Surging Tempest"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [DRG_217] Dragon's Pack - COST:5
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
//       If you've <b>Invoked</b> twice, give them +2/+2.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DRG_217 : Dragon's Pack")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon's Pack"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon's Pack"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Spirit Wolf");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->card->name, "Spirit Wolf");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    curPlayer->IncreaseInvoke();
    curPlayer->IncreaseInvoke();

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[2]->card->name, "Spirit Wolf");
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[3]->card->name, "Spirit Wolf");
    CHECK_EQ(curField[3]->GetAttack(), 4);
    CHECK_EQ(curField[3]->GetHealth(), 5);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_218] Corrupt Elementalist - COST:6 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond twice.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_218 : Corrupt Elementalist")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Tempest");

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
        curPlayer, Cards::FindCardByName("Corrupt Elementalist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetInvoke(), 2);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
}

// ----------------------------------------- SPELL - SHAMAN
// [DRG_219] Lightning Breath - COST:3
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 4 damage to a minion. If you're holding
//       a Dragon, also damage its neighbors.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DRG_219 : Lightning Breath")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Breath"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Breath"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    curPlayer->SetUsedMana(0);
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    curPlayer->SetUsedMana(0);
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 12);
    CHECK_EQ(curField[1]->GetHealth(), 12);
    CHECK_EQ(curField[2]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[2]->GetHealth(), 8);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card3));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[2]->GetHealth(), 4);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_223] Cumulo-Maximus - COST:5 [ATK:5/HP:5]
// - Race: Elemental, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have <b>Overloaded</b>
//       Mana Crystals, deal 5 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_223 : Cumulo-Maximus")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cumulo-Maximus"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cumulo-Maximus"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cumulo-Maximus"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, opHero));
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, opHero));
    CHECK_EQ(opHero->GetHealth(), 17);
}

// ---------------------------------------- MINION - SHAMAN
// [DRG_224] Nithogg - COST:6 [ATK:5/HP:5]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 0/3 Eggs.
//       Next turn they hatch into 4/4 Drakes with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_224 : Nithogg")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nithogg"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Storm Egg");
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[2]->card->name, "Storm Egg");
    CHECK_EQ(curField[2]->GetAttack(), 0);
    CHECK_EQ(curField[2]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Storm Drake");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[2]->card->name, "Storm Drake");
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// ----------------------------------------- SPELL - SHAMAN
// [DRG_248] Invocation of Frost - COST:2
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Freeze</b> an enemy. <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DRG_248 : Corrupt Elementalist")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Tempest");

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
        curPlayer, Cards::FindCardByName("Invocation of Frost"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetInvoke(), 0);
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Windswept Elemental");
}

// --------------------------------------- MINION - WARLOCK
// [DRG_201] Crazed Netherwing - COST:5 [ATK:5/HP:5]
// - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       deal 3 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DRG_201 : Crazed Netherwing")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crazed Netherwing"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crazed Netherwing"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero->GetHealth(), 27);
    CHECK_EQ(opHero->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHero->GetHealth(), 27);
    CHECK_EQ(opHero->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARLOCK
// [DRG_202] Dragonblight Cultist - COST:3 [ATK:1/HP:1]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
//       Gain +1 Attack for each other friendly minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DRG_202 : Dragonblight Cultist")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Wretched");

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
        curPlayer, Cards::FindCardByName("Dragonblight Cultist"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonblight Cultist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[3]->GetAttack(), 6);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARLOCK
// [DRG_203] Veiled Worshipper - COST:4 [ATK:5/HP:4]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
//       draw 3 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// --------------------------------------------------------
// RefTag:
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DRG_203 : Veiled Worshipper")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Veiled Worshipper"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Veiled Worshipper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    curPlayer->IncreaseInvoke();
    curPlayer->IncreaseInvoke();

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 7);
}

// ---------------------------------------- SPELL - WARLOCK
// [DRG_204] Dark Skies - COST:3
// - Faction: Neutral, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 1 damage to a random minion.
//       Repeat for each card in your hand.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DRG_204 : Dark Skies")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dark Skies"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetHealth() + opField[0]->GetHealth(), 13);
}

// ---------------------------------------- SPELL - WARLOCK
// [DRG_205] Nether Breath - COST:2
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage. If you're holding a Dragon,
//       deal 4 damage with <b>Lifesteal</b> instead.
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DRG_205 : Nether Breath")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    curHero->SetDamage(20);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nether Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nether Breath"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crazed Netherwing"));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, opHero));
    CHECK_EQ(curHero->GetHealth(), 14);
    CHECK_EQ(opHero->GetHealth(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(curHero->GetHealth(), 14);
    CHECK_EQ(opHero->GetHealth(), 24);
}

// ---------------------------------------- SPELL - WARLOCK
// [DRG_206] Rain of Fire - COST:1
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage to all characters.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DRG_206 : Rain of Fire")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rain of Fire"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero->GetHealth(), 24);
    CHECK_EQ(opHero->GetHealth(), 24);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// --------------------------------------- MINION - WARLOCK
// [DRG_207] Abyssal Summoner - COST:6 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a Demon with <b>Taunt</b>
//       and stats equal to your hand size.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DRG_207 : Abyssal Summoner")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abyssal Summoner"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Spellbreaker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->GetCost(), 6);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetCost(), 4);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, curField[1]));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetCost(), 4);
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// --------------------------------------- MINION - WARLOCK
// [DRG_208] Valdris Felgorge - COST:7 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Increase your maximum hand size
//       to 12. Draw 4 cards.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DRG_208 : Valdris Felgorge")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Valdris Felgorge"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(curHand.GetCount(), 8);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 12);
}

// --------------------------------------- MINION - WARLOCK
// [DRG_209] Zzeraku the Warped - COST:8 [ATK:4/HP:12]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever your hero takes damage,
//       summon a 6/6 Nether Drake.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DRG_209 : Zzeraku the Warped")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Zzeraku the Warped"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Nether Drake");
    CHECK_EQ(curField[1]->card->GetRace(), Race::DRAGON);
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 6);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, curPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Nether Drake");
    CHECK_EQ(curField[2]->card->GetRace(), Race::DRAGON);
    CHECK_EQ(curField[2]->GetAttack(), 6);
    CHECK_EQ(curField[2]->GetHealth(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [DRG_250] Fiendish Rites - COST:4
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Invoke</b> Galakrond.
//       Give your minions +1 Attack.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DRG_250 : Fiendish Rites")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Galakrond, the Wretched");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Rites"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Draconic Imp");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Draconic Imp");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [DRG_019] Scion of Ruin - COST:4 [ATK:3/HP:2]
// - Race: Dragon, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Battlecry:</b> If you've
//       <b>Invoked</b> twice, summon 2 copies of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DRG_019 : Scion of Ruin")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scion of Ruin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scion of Ruin"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    curPlayer->IncreaseInvoke();
    curPlayer->IncreaseInvoke();

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Scion of Ruin");
    CHECK_EQ(curField[3]->card->name, "Scion of Ruin");
}

// --------------------------------------- MINION - WARRIOR
// [DRG_020] EVIL Quartermaster - COST:3 [ATK:2/HP:3]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
//       Gain 3 Armor.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DRG_020 : EVIL Quartermaster")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("EVIL Quartermaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsLackey(), true);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
}

// --------------------------------------- WEAPON - WARRIOR
// [DRG_021] Ritual Chopper - COST:2 [ATK:1/HP:0]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - BATTLECRY = 1
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - DRG_021 : Ritual Chopper")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] =
        Cards::FindCardByName("Galakrond, the Unbreakable");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ritual Chopper"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [DRG_022] Ramming Speed - COST:3
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Force a minion to attack one of its neighbors.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DRG_022 : Ramming Speed")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ramming Speed"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [DRG_023] Skybarge - COST:3 [ATK:2/HP:5]
// - Race: Mechanical, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: After you summon a Pirate,
//       deal 2 damage to a random enemy.
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DRG_023 : Skybarge")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
        curPlayer, Cards::FindCardByName("Cabal Shadow Priest"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Skybarge"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Southsea Deckhand"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Southsea Deckhand"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    bool check31 = curField[0]->GetHealth() == 3 &&
                   curPlayer->GetHero()->GetHealth() == 30;
    bool check32 = curField[0]->GetHealth() == 5 &&
                   curPlayer->GetHero()->GetHealth() == 28;
    bool check3 = (check31 || check32);
    CHECK(check3);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    bool check41 = curField[0]->GetHealth() == 1 &&
                   curPlayer->GetHero()->GetHealth() == 30;
    bool check42 = curField[0]->GetHealth() == 3 &&
                   curPlayer->GetHero()->GetHealth() == 28;
    bool check43 = curField[0]->GetHealth() == 5 &&
                   curPlayer->GetHero()->GetHealth() == 26;
    bool check4 = (check41 || check42 || check43);
    CHECK(check4);
}

// --------------------------------------- MINION - WARRIOR
// [DRG_024] Sky Raider - COST:1 [ATK:1/HP:2]
// - Race: Pirate, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Pirate to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DRG_024 : Sky Raider")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sky Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::PIRATE);
}

// --------------------------------------- WEAPON - WARRIOR
// [DRG_025] Ancharrr - COST:3 [ATK:2/HP:0]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: After your hero attacks, draw a Pirate from your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - DRG_025 : Ancharrr")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        if (i % 2 == 0)
        {
            config.player1Deck[i] = Cards::FindCardByName("Wisp");
        }
        else
        {
            config.player1Deck[i] = Cards::FindCardByName("Southsea Deckhand");
        }
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancharrr"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Southsea Deckhand");
    CHECK_EQ(curHand[4]->card->GetRace(), Race::PIRATE);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [DRG_026] Deathwing, Mad Aspect - COST:8 [ATK:12/HP:12]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Attack ALL other minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DRG_026 : Deathwing, Mad Aspect")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Deathwing, Mad Aspect"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    curPlayer->SetUsedMana(0);
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- SPELL - WARRIOR
// [DRG_249] Awaken! - COST:3
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Invoke</b> Galakrond. Deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DRG_249 : Awaken!")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player2Deck[0] =
        Cards::FindCardByName("Galakrond, the Unbreakable");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Awaken!"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opPlayer->GetInvoke(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetAttack(), 3);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetAttack(), 0);
}

// ---------------------------------------- SPELL - WARRIOR
// [DRG_500] Molten Breath - COST:4
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 5 damage to a minion.
//       If you're holding a Dragon, gain 5 Armor.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DRG_500 : Molten Breath")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Molten Breath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Molten Breath"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_049] Tasty Flyfish - COST:2 [ATK:2/HP:2]
// - Race: Murloc, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give a Dragon in your hand +2/+2.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_049 : Tasty Flyfish")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tasty Flyfish"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    auto minion = dynamic_cast<Minion*>(card2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(minion->GetAttack(), 4);
    CHECK_EQ(minion->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(minion->GetAttack(), 6);
    CHECK_EQ(minion->GetHealth(), 14);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_050] Devoted Maniac - COST:4 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - 676 = 1
// - RUSH = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_050 : Devoted Maniac")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] =
        Cards::FindCardByName("Galakrond, the Unspeakable");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Devoted Maniac"));

    CHECK_EQ(curPlayer->GetInvoke(), 0);
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curHand.GetCount(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_054] Big Ol' Whelp - COST:5 [ATK:5/HP:5]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_054 : Big Ol' Whelp")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Big Ol' Whelp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_055] Hoard Pillager - COST:4 [ATK:4/HP:2]
// - Race: Pirate, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip one of your destroyed weapons.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_055 : Hoard Pillager")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto curHero = curPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hoard Pillager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gorehowl"));

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curHero->HasWeapon(), true);

    game.Process(curPlayer, AttackTask(curHero, opPlayer->GetHero()));
    CHECK_EQ(curHero->HasWeapon(), false);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero->HasWeapon(), true);

    game.Process(curPlayer, AttackTask(curHero, opPlayer->GetHero()));
    CHECK_EQ(curHero->HasWeapon(), false);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 16);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_056] Parachute Brigand - COST:2 [ATK:2/HP:2]
// - Race: Pirate, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: After you play a Pirate,
//       summon this minion from your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_056 : Parachute Brigand")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Southsea Deckhand"));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Parachute Brigand"));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Parachute Brigand"));
    const auto card8 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Parachute Brigand"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Parachute Brigand");
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[5]->card->name, "Parachute Brigand");
    CHECK_EQ(curField[6]->card->name, "Parachute Brigand");
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_057] Hot Air Balloon - COST:1 [ATK:1/HP:2]
// - Race: Mechanical, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: At the start of your turn, gain +1 Health.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_057 : Hot Air Balloon")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hot Air Balloon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_058] Wing Commander - COST:4 [ATK:2/HP:5]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Has +2 Attack for each Dragon in your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_058 : Wing Commander")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wing Commander"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_059] Goboglide Tech - COST:3 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a Mech,
//       gain +1/+1 and <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_059 : Goboglide Tech")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Goboglide Tech"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Goboglide Tech"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hot Air Balloon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_060] Fire Hawk - COST:3 [ATK:1/HP:3]
// - Race: Elemental, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1 Attack for each card
//       in your opponent's hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_060 : Fire Hawk")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Hawk"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Hawk"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_061] Gyrocopter - COST:6 [ATK:4/HP:5]
// - Race: Mechanical, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_061 : Gyrocopter")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_062] Wyrmrest Purifier - COST:2 [ATK:3/HP:2]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform all Neutral cards
//       in your deck into random cards from your class.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_062 : Wyrmrest Purifier")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Fireball");
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wyrmrest Purifier"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    for (auto& card : curPlayer->GetDeckZone()->GetAll())
    {
        CHECK_EQ(card->card->GetCardClass(), CardClass::MAGE);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_063] Dragonmaw Poacher - COST:4 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your opponent controls a Dragon,
//       gain +4/+4 and <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_063 : Dragonmaw Poacher")
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
        curPlayer, Cards::FindCardByName("Dragonmaw Poacher"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonmaw Poacher"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_064] Zul'Drak Ritualist - COST:4 [ATK:3/HP:9]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> Summon three
//       random 1-Cost minions for your opponent.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_064 : Zul'Drak Ritualist")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Zul'Drak Ritualist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->card->GetCost(), 1);
    CHECK_EQ(opField[1]->card->GetCost(), 1);
    CHECK_EQ(opField[2]->card->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_065] Hippogryph - COST:4 [ATK:2/HP:6]
// - Race: Beast, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_065 : Hippogryph")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_066] Evasive Chimaera - COST:2 [ATK:2/HP:1]
// - Race: Beast, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Poisonous</b>
//       Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_066 : Evasive Chimaera")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Chimaera"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_067] Troll Batrider - COST:4 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_067 : Troll Batrider")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Troll Batrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Troll Batrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    const bool check =
        (curField[0]->GetHealth() == 6 && curField[1]->GetHealth() == 12) ||
        (curField[0]->GetHealth() == 9 && curField[1]->GetHealth() == 9);
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_068] Living Dragonbreath - COST:3 [ATK:3/HP:4]
// - Race: Elemental, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Your minions can't be <b>Frozen</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_068 : Living Dragonbreath")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Living Dragonbreath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormwind Knight"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormwind Knight"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Water Elemental"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField[0]->IsFrozen(), true);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->IsFrozen(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, AttackTask(card3, card6));
    CHECK_EQ(curField[2]->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField[0]->IsFrozen(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_069] Platebreaker - COST:5 [ATK:5/HP:5]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your opponent's Armor.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_069 : Platebreaker")
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

    auto curHero = curPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Block"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Platebreaker"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero->GetArmor(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero->GetArmor(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHero->GetArmor(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_070] Dragon Breeder - COST:2 [ATK:2/HP:3]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly Dragon.
//       Add a copy of it to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_RACE = 24
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_070 : Dragon Breeder")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon Breeder"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_NE(curHand[0]->card->name, "Bronze Herald");

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Bronze Herald");
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_071] Bad Luck Albatross - COST:3 [ATK:4/HP:3]
// - Race: Beast, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle two 1/1 Albatross
//       into your opponent's deck.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_071 : Bad Luck Albatross")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bad Luck Albatross"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opDeck.GetCount(), 2);
    CHECK_EQ(opDeck[0]->card->name, "Albatross");
    CHECK_EQ(opDeck[1]->card->name, "Albatross");
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_072] Skyfin - COST:5 [ATK:3/HP:3]
// - Race: Murloc, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       summon 2 random Murlocs.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_072 : Skyfin")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skyfin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skyfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->GetRace(), Race::MURLOC);
    CHECK_EQ(curField[2]->card->GetRace(), Race::MURLOC);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_073] Evasive Feywing - COST:4 [ATK:5/HP:4]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_073 : Evasive Feywing")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Feywing"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_074] Camouflaged Dirigible - COST:6 [ATK:6/HP:6]
// - Race: Mechanical, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your other Mechs
//       <b>Stealth</b> until your next turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_074 : Camouflaged Dirigible")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Camouflaged Dirigible"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Worgen Infiltrator"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hot Air Balloon"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gyrocopter"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curField[1]->HasStealth(), true);
    CHECK_EQ(curField[2]->HasStealth(), true);
    CHECK_EQ(curField[3]->HasStealth(), false);

    game.Process(curPlayer, AttackTask(card4, card5));

    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curField[1]->HasStealth(), true);
    CHECK_EQ(curField[2]->HasStealth(), false);
    CHECK_EQ(curField[3]->HasStealth(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curField[1]->HasStealth(), true);
    CHECK_EQ(curField[2]->HasStealth(), false);
    CHECK_EQ(curField[3]->HasStealth(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curField[1]->HasStealth(), false);
    CHECK_EQ(curField[2]->HasStealth(), false);
    CHECK_EQ(curField[3]->HasStealth(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_075] Cobalt Spellkin - COST:5 [ATK:3/HP:5]
// - Race: Dragon, Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add two 1-Cost spells from
//       your class to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_075 : Cobalt Spellkin")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cobalt Spellkin"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::ROGUE);
    CHECK_EQ(curHand[0]->card->GetCost(), 1);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::ROGUE);
    CHECK_EQ(curHand[1]->card->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_076] Faceless Corruptor - COST:5 [ATK:4/HP:4]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Battlecry:</b> Transform
//       one of your minions into a copy of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_076 : Faceless Corruptor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Faceless Corruptor"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->card->name, "Faceless Corruptor");
    CHECK_EQ(opField[1]->card->name, "Faceless Corruptor");

    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_077] Utgarde Grapplesniper - COST:6 [ATK:5/HP:5]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Both players draw a card.
//       If it's a Dragon, summon it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_077 : Utgarde Grapplesniper")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Utgarde Grapplesniper"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Utgarde Grapplesniper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Fireball");
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Fireball");
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[2]->card->name, "Malygos");
    CHECK_EQ(opHand.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_078] Depth Charge - COST:1 [ATK:0/HP:5]
// - Set: Dragons, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       deal 5 damage to ALL minions.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_078 : Depth Charge")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Depth Charge"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(opField[0]->GetHealth(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_079] Evasive Wyrm - COST:6 [ATK:5/HP:3]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>. <b>Rush</b>.
//       Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// - RUSH = 1
// - 1211 = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_079 : Evasive Wyrm")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Wyrm"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_081] Scalerider - COST:3 [ATK:3/HP:3]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_081 : Scalerider")
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

    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scalerider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scalerider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_082] Kobold Stickyfinger - COST:5 [ATK:4/HP:4]
// - Race: Pirate, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Steal your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_082 : Kobold Stickyfinger")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Kobold Stickyfinger"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_084] Tentacled Menace - COST:5 [ATK:6/HP:5]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws a card.
//       Swap their Costs.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_084 : Tentacled Menace")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tentacled Menace"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->GetCost(), 9);
    CHECK_EQ(opHand.GetCount(), 6);
    CHECK_EQ(opHand[5]->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(opHand[5]));
    CHECK_EQ(opPlayer->GetRemainingMana(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[4], opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_086] Chromatic Egg - COST:5 [ATK:0/HP:3]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Secretly <b>Discover</b>
//       a Dragon to hatch into. <b>Deathrattle:</b> Hatch!
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_086 : Chromatic Egg")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chromatic Egg"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }

    Generic::ChoicePick(curPlayer, 27);
    auto minion = game.entityList[27];

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, minion->card->name);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_088] Dread Raven - COST:3 [ATK:3/HP:4]
// - Race: Beast, Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Has +3 Attack for each other Dread Raven you control.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_088 : Dread Raven")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dread Raven"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dread Raven"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dread Raven"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetAttack(), 9);
    CHECK_EQ(curField[2]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetAttack(), 9);
    CHECK_EQ(curField[2]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_089] Dragonqueen Alexstrasza - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       add 2 other random Dragons to your hand. They cost (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_089 : Dragonqueen Alexstrasza")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 6; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
        curPlayer, Cards::FindCardByName("Dragonqueen Alexstrasza"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonqueen Alexstrasza"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_NE(curHand[5]->card->name, "Dragonqueen Alexstrasza");
    CHECK_EQ(curHand[5]->card->GetRace(), Race::DRAGON);
    CHECK_EQ(curHand[5]->GetCost(), 1);
    CHECK_NE(curHand[6]->card->name, "Dragonqueen Alexstrasza");
    CHECK_EQ(curHand[6]->card->GetRace(), Race::DRAGON);
    CHECK_EQ(curHand[6]->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_091] Shu'ma - COST:7 [ATK:1/HP:7]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       fill your board with 1/1 Tentacles.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_091 : Shu'ma")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shu'ma"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->card->name, "Tentacle");
    CHECK_EQ(curField[1]->card->name, "Tentacle");
    CHECK_EQ(curField[2]->card->name, "Tentacle");
    CHECK_EQ(curField[3]->card->name, "Shu'ma");
    CHECK_EQ(curField[4]->card->name, "Tentacle");
    CHECK_EQ(curField[5]->card->name, "Tentacle");
    CHECK_EQ(curField[6]->card->name, "Tentacle");

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->card->name, "Tentacle");
    CHECK_EQ(curField[1]->card->name, "Tentacle");
    CHECK_EQ(curField[2]->card->name, "Shu'ma");
    CHECK_EQ(curField[3]->card->name, "Tentacle");
    CHECK_EQ(curField[4]->card->name, "Tentacle");
    CHECK_EQ(curField[5]->card->name, "Tentacle");
    CHECK_EQ(curField[6]->card->name, "Malygos");
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_092] Transmogrifier - COST:2 [ATK:2/HP:3]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: Whenever you draw a card,
//       transform it into a random <b>Legendary</b> minion.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_092 : Transmogrifier")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Transmogrifier"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[4]->card->GetRarity(), Rarity::LEGENDARY);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[5]->card->GetRarity(), Rarity::LEGENDARY);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_099] Kronx Dragonhoof - COST:6 [ATK:6/HP:6]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw Galakrond.
//       If you're already Galakrond, unleash a Devastation.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - 676 = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DRG_099 : Kronx Dragonhoof")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] =
            Cards::FindCardByName("Galakrond, the Unspeakable");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
    curPlayer->GetHero()->SetDamage(15);
    opPlayer->GetHero()->SetDamage(15);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kronx Dragonhoof"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kronx Dragonhoof"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kronx Dragonhoof"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kronx Dragonhoof"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kronx Dragonhoof"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice == nullptr);
    CHECK_EQ(curHand.GetCount(), 9);
    CHECK_EQ(curHand[8]->card->name, "Galakrond, the Unspeakable");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(opHand[0]));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curPlayer->GetHero()->card->IsGalakrond(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(opHand[0]));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 71);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 10);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 76);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->GetAttack(), 8);
    CHECK_EQ(curField[3]->GetHealth(), 8);
    CHECK_EQ(curField[3]->HasTaunt(), true);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 82);
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[2]->GetAttack(), 8);
    CHECK_EQ(curField[2]->GetHealth(), 8);
    CHECK_EQ(curField[3]->GetAttack(), 10);
    CHECK_EQ(curField[3]->GetHealth(), 10);
    CHECK_EQ(curField[4]->GetAttack(), 6);
    CHECK_EQ(curField[4]->GetHealth(), 6);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 87);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 3);
    CHECK_EQ(curField[3]->GetHealth(), 5);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_213] Twin Tyrant - COST:8 [ATK:4/HP:10]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage to two random enemy minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_213 : Twin Tyrant")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twin Tyrant"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twin Tyrant"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_239] Blazing Battlemage - COST:1 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_239 : Blazing Battlemage")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_242] Shield of Galakrond - COST:5 [ATK:4/HP:5]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// - 676 = 1
// - EMPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_242 : Shield of Galakrond")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] =
        Cards::FindCardByName("Galakrond, the Unspeakable");

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
        curPlayer, Cards::FindCardByName("Shield of Galakrond"));

    CHECK_EQ(curPlayer->GetInvoke(), 0);
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetInvoke(), 1);
    CHECK_EQ(curHand.GetCount(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_257] Frizz Kindleroost - COST:4 [ATK:5/HP:4]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Reduce the Cost of Dragons
//       in your deck by (2).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_257 : Frizz Kindleroost")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frizz Kindleroost"));

    CHECK_EQ(curHand[0]->GetCost(), 9);
    CHECK_EQ(curHand[1]->GetCost(), 9);
    CHECK_EQ(curHand[2]->GetCost(), 9);
    CHECK_EQ(curHand[3]->GetCost(), 9);
    for (auto& card : curDeck.GetAll())
    {
        CHECK_EQ(card->GetCost(), 9);
    }

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand[0]->GetCost(), 9);
    CHECK_EQ(curHand[1]->GetCost(), 9);
    CHECK_EQ(curHand[2]->GetCost(), 9);
    CHECK_EQ(curHand[3]->GetCost(), 9);
    for (auto& card : curDeck.GetAll())
    {
        CHECK_EQ(card->GetCost(), 7);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_310] Evasive Drakonid - COST:7 [ATK:7/HP:7]
// - Race: Dragon, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_310 : Evasive Drakonid")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Drakonid"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_401] Grizzled Wizard - COST:2 [ATK:3/HP:2]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Swap Hero Powers with your opponent
//       until your next turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_401 : Grizzled Wizard")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto curHero = curPlayer->GetHero();
    auto curHand = curPlayer->GetHandZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grizzled Wizard"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero->GetHealth(), 28);
    CHECK_EQ(curHand->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero->GetHealth(), 28);
    CHECK_EQ(curHero->GetArmor(), 2);
    CHECK_EQ(curHand->GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero->GetHealth(), 28);
    CHECK_EQ(curHero->GetArmor(), 0);
    CHECK_EQ(curHand->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_402] Sathrovarr - COST:9 [ATK:5/HP:5]
// - Race: Demon, Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly minion.
//       Add a copy of it to your hand, deck, and battlefield.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_402 : Sathrovarr")
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
    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sathrovarr"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Stonetusk Boar");
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curDeck[0]->card->name, "Stonetusk Boar");
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Stonetusk Boar");
    CHECK_EQ(curField[1]->card->name, "Stonetusk Boar");
    CHECK_EQ(curField[2]->card->name, "Sathrovarr");
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_403] Blowtorch Saboteur - COST:3 [ATK:3/HP:4]
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your opponent's next
//       Hero Power costs (3).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_403 : Blowtorch Saboteur")
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

    auto opHero = opPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blowtorch Saboteur"));

    CHECK_EQ(opHero->heroPower->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opHero->heroPower->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opHero->heroPower->GetCost(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opHero->heroPower->GetCost(), 3);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opHero->heroPower->GetCost(), 2);
}