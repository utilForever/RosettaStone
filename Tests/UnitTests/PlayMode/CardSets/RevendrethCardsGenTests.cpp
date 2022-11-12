// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [REV_307] Natural Causes - COST:2
// - Set: REVENDRETH, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 2 damage. Summon a 2/2 Treant.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - REV_307 : Natural Causes")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Natural Causes"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [REV_313] Planted Evidence - COST:1
// - Set: REVENDRETH, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Discover</b> a spell.
//       It costs (2) less this turn.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - REV_313 : Planted Evidence")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Planted Evidence"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::DRUID));
    }

    TestUtils::ChooseNthChoice(game, 1);

    auto calculateCostDiff = [](int cost) -> int {
        if (cost == 0)
        {
            return 0;
        }

        if (cost == 1)
        {
            return 1;
        }

        return 2;
    };

    const int costDiff = calculateCostDiff(curHand[0]->card->GetCost());
    CHECK_EQ(curHand[0]->card->GetCost() - curHand[0]->GetCost(), costDiff);
}

// ----------------------------------------- MINION - DRUID
// [REV_318] Widowbloom Seedsman - COST:4 [ATK:3/HP:2]
// - Set: REVENDRETH, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a Nature spell.
//       Gain an empty Mana Crystal.
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - REV_318 : Widowbloom Seedsman")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Lightning Bolt");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Blizzard");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Widowbloom Seedsman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetSpellSchool(), SpellSchool::NATURE);
    CHECK_EQ(curPlayer->GetTotalMana(), 5);
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);
}

// ----------------------------------------- MINION - DRUID
// [REV_319] Sesselie of the Fae Court - COST:8 [ATK:8/HP:8]
// - Set: REVENDRETH, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle</b>: Draw a minion.
//       Reduce its Cost by (8).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - REV_319 : Sesselie of the Fae Court")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 1] = Cards::FindCardByName("Chaos Nova");
        config.player1Deck[i + 2] = Cards::FindCardByName("Fireball");
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
        curPlayer, Cards::FindCardByName("Sesselie of the Fae Court"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Malygos");
    CHECK_EQ(curHand[4]->GetCost(), 1);
}

// ------------------------------------------ SPELL - DRUID
// [REV_336] Plot of Sin - COST:3
// - Set: REVENDRETH, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon two 2/2 Treants.
//       <b>Infuse (5):</b> Two 5/5 Ancients instead.
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - REV_336 : Plot of Sin")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plot of Sin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plot of Sin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Treant");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(card2->HasInfuse(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Ancient");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->card->name, "Ancient");
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [REV_350] Frenzied Fangs - COST:2
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: Summon two 2/1 Bats.
//       <b>Infuse (3):</b> Give them +1/+2.
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - REV_350 : Frenzied Fangs")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frenzied Fangs"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frenzied Fangs"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Thirsty Bat");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Thirsty Bat");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(card2->HasInfuse(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Thirsty Bat");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->card->name, "Thirsty Bat");
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ---------------------------------------- MINION - HUNTER
// [REV_352] Stonebound Gargon - COST:4 [ATK:3/HP:5]
// - Race: Beast, Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Infuse (3):</b> Also damages the minions
//       next to whomever this attacks.
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - REV_352 : Stonebound Gargon")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonebound Gargon"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonebound Gargon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flamestrike"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(card2->HasInfuse(), true);

    game.Process(curPlayer, AttackTask(card1, card6));
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card8));
    CHECK_EQ(curHand[0]->IsInfused(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, AttackTask(curField[0], card6));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [REV_353] Huntsman Altimor - COST:7 [ATK:5/HP:4]
// - Set: REVENDRETH, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a Gargon Companion.
//       <b>Infuse (4):</b> Summon another.
//       <b>Infuse (4):</b> And another!
// --------------------------------------------------------
// Entourage: REV_353t3, REV_353t4, REV_353t5
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - INFUSE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - REV_353 : Huntsman Altimor")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Huntsman Altimor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Huntsman Altimor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Huntsman Altimor"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twisting Nether"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twisting Nether"));

    auto isGargonCompanion = [](const Playable* playable) -> bool {
        return playable->card->id == "REV_353t3" ||
               playable->card->id == "REV_353t4" ||
               playable->card->id == "REV_353t5";
    };

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK(isGargonCompanion(curField[1]));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(card2->HasInfuse(), true);
    CHECK_EQ(card3->HasInfuse(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(curHand[0]->HasInfuse(), true);
    CHECK_EQ(curHand[1]->IsInfused(), true);
    CHECK_EQ(curHand[1]->HasInfuse(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK(isGargonCompanion(curField[1]));
    CHECK(isGargonCompanion(curField[2]));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card8));
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(curHand[0]->HasInfuse(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK(isGargonCompanion(curField[1]));
    CHECK(isGargonCompanion(curField[2]));
    CHECK(isGargonCompanion(curField[3]));
}

// ---------------------------------------- MINION - HUNTER
// [REV_356] Batty Guest - COST:1 [ATK:1/HP:1]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 2/1 Bat.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - REV_356 : Batty Guest")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Batty Guest"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Thirsty Bat");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_012] Bog Beast - COST:6 [ATK:3/HP:6]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Summon a 2/4 Muckmare
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_012 : Bog Beast")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bog Beast"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Muckmare");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_013] Stoneborn Accuser - COST:5 [ATK:5/HP:5]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Infuse (5):</b>
//       Gain "<b>Battlecry:</b> Deal 5 damage."
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_013 : Stoneborn Accuser")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stoneborn Accuser"));
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(card1->HasInfuse(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[4]->IsInfused(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(curHand[4], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_019] Famished Fool - COST:5 [ATK:3/HP:5]
// - Set: REVENDRETH, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a card.
//       <b>Infuse (4):</b> Draw 3 instead.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - INFUSE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_019 : Famished Fool")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Famished Fool"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Famished Fool"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flamestrike"));

    CHECK_EQ(curHand.GetCount(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(card1->HasInfuse(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[4]->IsInfused(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 9);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_251] Sinrunner - COST:5 [ATK:6/HP:5]
// - Race: Beast, Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Destroy a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_251 : Sinrunner")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sinrunner"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_308] Maze Guide - COST:2 [ATK:1/HP:1]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry</b>: Summon a random 2-Cost minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_308 : Maze Guide")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Maze Guide"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetCost(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_338] Dredger Staff - COST:1 [ATK:1/HP:2]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give minions in your hand +1 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_338 : Dredger Staff")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dredger Staff"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_956] Priest of the Deceased - COST:2 [ATK:2/HP:3]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Infuse (3):</b> Gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_956 : Priest of the Deceased")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Priest of the Deceased"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(card1->HasInfuse(), true);
    CHECK_EQ(dynamic_cast<Minion*>(card1)->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card1)->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_957] Murlocula - COST:4 [ATK:3/HP:4]
// - Race: Murloc, Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       <b>Infuse (4):</b> This costs (0).
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_957 : Murlocula")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murlocula"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(card1->HasInfuse(), true);
    CHECK_EQ(card1->GetCost(), 4);
    CHECK_EQ(card1->HasLifesteal(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(curHand[0]->GetCost(), 0);
    CHECK_EQ(curHand[0]->HasLifesteal(), true);
}