// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ---------------------------------------- MINION - PRIEST
// [CFM_605] Drakonid Operative - COST:5 [ATK:5/HP:6]
// - Race: Dragon, Set: GANGS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       <b>Discover</b> a copy of a card
//       in your opponent's deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CFM_605 : Drakonid Operative")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player2Deck[i + 2] = Cards::FindCardByName("Blizzard");
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
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Drakonid Operative"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Drakonid Operative"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        const bool checkName = card->name == "Wisp" ||
                               card->name == "Fireball" ||
                               card->name == "Blizzard";
        CHECK(checkName);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(opDeck.GetCount(), 26);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(!curPlayer->choice);
}

// --------------------------------------- MINION - WARLOCK
// [CFM_751] Abyssal Enforcer - COST:7 [ATK:6/HP:6]
// - Race: Demon, Set: GANGS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CFM_751 : Abyssal Enforcer")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abyssal Enforcer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [CFM_120] Mistress of Mixtures - COST:1 [ATK:2/HP:2]
// - Set: GANGS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Restore 4 Health to each hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CFM_120 : Mistress of Mixtures")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mistress of Mixtures"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 19);
}