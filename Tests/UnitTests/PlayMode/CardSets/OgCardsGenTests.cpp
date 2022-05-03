//// Copyright (c) 2017-2021 Chris Ohk
//
//// We are making my contributions/submissions to this project solely in our
//// personal capacity and are not conveying any rights to any intellectual
//// property of any third parties.
//
//#include "doctest_proxy.hpp"
//
//#include <Utils/CardSetUtils.hpp>
//
//#include <Rosetta/PlayMode/Actions/Draw.hpp>
//#include <Rosetta/PlayMode/Cards/Cards.hpp>
//#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
//
//using namespace RosettaStone;
//using namespace PlayMode;
//using namespace PlayerTasks;
//using namespace SimpleTasks;
//
//// ------------------------------------------ SPELL - DRUID
//// [OG_047] Feral Rage - COST:3
//// - Set: Og, Rarity: Common
//// --------------------------------------------------------
//// Text: <b>Choose One -</b> Give your hero +4 Attack this turn;
////       or Gain 8 Armor.
//// --------------------------------------------------------
//// GameTag:
//// - CHOOSE_ONE = 1
//// --------------------------------------------------------
//TEST_CASE("[Druid : Spell] - OG_047 : Feral Rage")
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::DRUID;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
//    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
//    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [OG_273] Stand Against Darkness - COST:5
//// - Set: Og, Rarity: Common
//// --------------------------------------------------------
//// Text: Summon five 1/1 Silver Hand Recruits.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_NUM_MINION_SLOTS = 1
//// --------------------------------------------------------
//TEST_CASE("[Paladin : Spell] - OG_273 : Stand Against Darkness")
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::DRUID;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Stand Against Darkness"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Stand Against Darkness"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    CHECK_EQ(curField.GetCount(), 5);
//    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
//    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
//    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
//    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
//    CHECK_EQ(curField[4]->card->name, "Silver Hand Recruit");
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    CHECK_EQ(curField.GetCount(), 7);
//    CHECK_EQ(curField[5]->card->name, "Silver Hand Recruit");
//    CHECK_EQ(curField[6]->card->name, "Silver Hand Recruit");
//}
//
//// ----------------------------------------- MINION - ROGUE
//// [OG_070] Bladed Cultist - COST:1 [ATK:1/HP:2]
//// - Set: Og, Rarity: Common
//// --------------------------------------------------------
//// Text: <b>Combo:</b> Gain +1/+1.
//// --------------------------------------------------------
//// GameTag:
//// - COMBO = 1
//// --------------------------------------------------------
//TEST_CASE("[Rogue : Minion] - OG_070 : Bladed Cultist")
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::DRUID;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladed Cultist"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladed Cultist"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    CHECK_EQ(curField[0]->GetAttack(), 1);
//    CHECK_EQ(curField[0]->GetHealth(), 2);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    CHECK_EQ(curField[1]->GetAttack(), 2);
//    CHECK_EQ(curField[1]->GetHealth(), 3);
//}
//
//// --------------------------------------- MINION - WARLOCK
//// [OG_241] Possessed Villager - COST:1 [ATK:1/HP:1]
//// - Set: Og, Rarity: Common
//// --------------------------------------------------------
//// Text: <b>Deathrattle:</b> Summon a 1/1 Shadowbeast.
//// --------------------------------------------------------
//// GameTag:
//// - DEATHRATTLE = 1
//// --------------------------------------------------------
//TEST_CASE("[Warlock : Minion] - OG_241 : Possessed Villager")
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Possessed Villager"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    CHECK_EQ(curField[0]->card->name, "Possessed Villager");
//    CHECK_EQ(curField[0]->GetAttack(), 1);
//    CHECK_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    game.Process(opPlayer, HeroPowerTask(card1));
//    CHECK_EQ(curField[0]->card->name, "Shadowbeast");
//    CHECK_EQ(curField[0]->GetAttack(), 1);
//    CHECK_EQ(curField[0]->GetHealth(), 1);
//}