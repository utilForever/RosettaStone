// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

using namespace RosettaStone;
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
// Text: <b>Battlecry:</b> Draw 1 card. It costs (0).
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
        config.player1Deck[i] = *Cards::FindCardByName("Fireball");
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
    CHECK_EQ(curHand[4]->GetCost(), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->IsLackey(), true);
}

// ------------------------------------------- HERO - ROGUE
// [DRG_610t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 2 cards. They cost (0).
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
        config.player1Deck[i] = *Cards::FindCardByName("Fireball");
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
    CHECK_EQ(curHand[4]->GetCost(), 0);
    CHECK_EQ(curHand[5]->GetCost(), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[6])->IsLackey(), true);
}

// ------------------------------------------- HERO - ROGUE
// [DRG_610t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
// - Set: Dragons, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 4 cards. They cost (0).
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
        config.player1Deck[i] = *Cards::FindCardByName("Fireball");
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
    CHECK_EQ(curHand[4]->GetCost(), 0);
    CHECK_EQ(curHand[5]->GetCost(), 0);
    CHECK_EQ(curHand[6]->GetCost(), 0);
    CHECK_EQ(curHand[7]->GetCost(), 0);
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
    CHECK_EQ(curField[0]->IsRush(), true);
    CHECK_EQ(curField[1]->card->name, "Brewing Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->IsRush(), true);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->IsRush(), true);
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
    CHECK_EQ(curField[0]->IsRush(), true);
    CHECK_EQ(curField[1]->card->name, "Living Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->IsRush(), true);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->IsRush(), true);
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
    CHECK_EQ(curField[0]->IsRush(), true);
    CHECK_EQ(curField[1]->card->name, "Raging Storm");
    CHECK_EQ(curField[1]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[1]->IsRush(), true);
    CHECK_EQ(curPlayer->GetWeapon().card->name, "Dragon Claw");
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[2]->card->name, "Windswept Elemental");
    CHECK_EQ(curField[2]->card->GetRace(), Race::ELEMENTAL);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->IsRush(), true);
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
        config.player2Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
        config.player2Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
        config.player2Deck[i] = *Cards::FindCardByName("Wisp");
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
        config.player1Deck[i] = *Cards::FindCardByName("Wisp");
        config.player2Deck[i] = *Cards::FindCardByName("Wisp");
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
    CHECK_EQ(curPlayer->choice.has_value(), true);
    CHECK_EQ(curPlayer->choice.value().choices.size(), 3);

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
        config.player1Deck[i] = *Cards::FindCardByName("Restless Mummy");
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
    CHECK_EQ(curField[3]->IsRush(), true);
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
        config.player1Deck[i] = *Cards::FindCardByName("Snake Trap");
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
    CHECK_EQ(curPlayer->choice.has_value(), true);
    CHECK_EQ(curPlayer->choice.value().choices.size(), 3);

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
    CHECK_EQ(curPlayer->choice.has_value(), true);
    CHECK_EQ(curPlayer->choice.value().choices.size(), 3);

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
    CHECK_EQ(curPlayer->choice.has_value(), true);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->GetCardClass(), CardClass::MAGE);
    }

    Generic::ChoicePick(curPlayer, 27);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetHealth(), 8);
    CHECK_EQ(curPlayer->choice.has_value(), false);
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
    CHECK_EQ(curPlayer->choice.has_value(), true);

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
    CHECK_EQ(curPlayer->choice.has_value(), false);
}

// ------------------------------------------ MINION - MAGE
// [DRG_322] Dragoncaster - COST:6 [ATK:4/HP:4]
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
        config.player1Deck[i] = *Cards::FindCardByName("Fireball");
        config.player2Deck[i] = *Cards::FindCardByName("Fireball");
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
    CHECK_EQ(curPlayer->choice.has_value(), true);
    CHECK_EQ(curPlayer->choice.value().choices.size(), 3);

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
        config.player1Deck[i] = *Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = *Cards::FindCardByName("Leper Gnome");
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
        config.player1Deck[i] = *Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = *Cards::FindCardByName("Leper Gnome");
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
        *Cards::FindCardByName("Galakrond, the Unspeakable");

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
        *Cards::FindCardByName("Galakrond, the Unspeakable");

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
    CHECK_EQ(curPlayer->choice.has_value(), true);

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

    config.player1Deck[0] = *Cards::FindCardByName("Galakrond, the Nightmare");

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
        config.player1Deck[i] = *Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = *Cards::FindCardByName("Leper Gnome");
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

    config.player1Deck[0] = *Cards::FindCardByName("Galakrond, the Nightmare");

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

    config.player1Deck[0] = *Cards::FindCardByName("Galakrond, the Tempest");

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
    CHECK_EQ(curField[0]->IsRush(), true);
    CHECK_EQ(curField[2]->card->name, "Storm Drake");
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[2]->IsRush(), true);
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

    config.player1Deck[0] = *Cards::FindCardByName("Galakrond, the Tempest");

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
        *Cards::FindCardByName("Galakrond, the Unbreakable");

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
            config.player1Deck[i] = *Cards::FindCardByName("Wisp");
        }
        else
        {
            config.player1Deck[i] = *Cards::FindCardByName("Southsea Deckhand");
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
        *Cards::FindCardByName("Galakrond, the Unbreakable");

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
// [DRG_239] Blazing Battlemage - COST:1 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_239 : Blazing Battlemage")
{
    // Do nothing
}