// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

    CHECK_EQ(curPlayer->GetHero()->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHero->weapon->IsImmune(), true);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->weapon->GetDurability(), 1);
    CHECK_EQ(opHero->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curHero->weapon->IsImmune(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

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
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 3);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->id, "DRG_255t2");
    CHECK_EQ(curField[1]->card->id, "DRG_255t2");
    CHECK_EQ(curField[2]->card->id, "DRG_255t2");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opPlayer->GetHero()->SetDamage(0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
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
    game.ProcessUntil(Step::MAIN_START);

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