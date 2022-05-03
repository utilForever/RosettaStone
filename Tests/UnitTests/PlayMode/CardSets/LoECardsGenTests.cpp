//// Copyright (c) 2017-2021 Chris Ohk
//
//// We are making my contributions/submissions to this project solely in our
//// personal capacity and are not conveying any rights to any intellectual
//// property of any third parties.
//
//#include "doctest_proxy.hpp"
//
//#include <Utils/CardSetUtils.hpp>
//#include <Utils/TestUtils.hpp>
//
//#include <Rosetta/PlayMode/Actions/Draw.hpp>
//#include <Rosetta/PlayMode/Cards/Cards.hpp>
//#include <Rosetta/PlayMode/Zones/HandZone.hpp>
//
//using namespace RosettaStone;
//using namespace PlayMode;
//using namespace PlayerTasks;
//using namespace SimpleTasks;
//
//// ------------------------------------------ MINION - MAGE
//// [LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:3]
//// - Set: LoE Rarity: Common
//// --------------------------------------------------------
//// Text: <b>Battlecry: Discover</b> a spell.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// - DISCOVER = 1
//// - USE_DISCOVER_VISUALS = 1
//// --------------------------------------------------------
//TEST_CASE("[Mage : Minion] - LOE_003 : Ethereal Conjurer")
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = false;
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
//    auto& curHand = *(curPlayer->GetHandZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Ethereal Conjurer"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    CHECK(curPlayer->choice != nullptr);
//    CHECK_EQ(curPlayer->choice->choices.size(), 3);
//
//    auto cards = TestUtils::GetChoiceCards(game);
//    for (auto& card : cards)
//    {
//        CHECK_EQ(card->GetCardType(), CardType::SPELL);
//        CHECK_EQ(card->IsCardClass(CardClass::MAGE), true);
//    }
//
//    TestUtils::ChooseNthChoice(game, 1);
//    CHECK_EQ(curHand.GetCount(), 1);
//}
//
//// ----------------------------------------- MINION - ROGUE
//// [LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
//// - Set: LoE, Rarity: Common
//// --------------------------------------------------------
//// Text: <b>Deathrattle:</b> Add a Coin to your hand.
//// --------------------------------------------------------
//// GameTag:
//// - DEATHRATTLE = 1
//// --------------------------------------------------------
//TEST_CASE("[Rogue : Minion] - LOE_012 : Tomb Pillager")
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = false;
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
//    auto& curHand = *(curPlayer->GetHandZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tomb Pillager"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    CHECK_EQ(curHand.GetCount(), 0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_ACTION);
//
//    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
//    CHECK_EQ(curHand.GetCount(), 1);
//    CHECK_EQ(curHand[0]->card->name, "The Coin");
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1]
//// - Race: Murloc, Set: LoE, Rarity: Common
//// --------------------------------------------------------
//TEST_CASE("[Neutral : Minion] - LOEA10_3 : Murloc Tinyfin")
//{
//    // Do nothing
//}