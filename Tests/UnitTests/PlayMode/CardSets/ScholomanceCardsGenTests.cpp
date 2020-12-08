// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ----------------------------------------- MINION - DRUID
// [SCH_242] Gibberling - COST:1 [ATK:1/HP:1]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Summon a Gibberling.
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SCH_242 : Gibberling")
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

// ------------------------------------------ SPELL - DRUID
// [SCH_333] Nature Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a spell. Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SCH_333 : Nature Studies")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nature Studies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfall"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::DRUID), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 4);

    const int oldCost = curHand[1]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 1));
    if (curHand[0]->GetCost() != 0)
    {
        CHECK_EQ(curHand[0]->GetCost(), oldCost + 1);
    }
}

// ------------------------------------------ SPELL - DRUID
// [SCH_427] Lightning Bloom - COST:0
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Gain 2 Mana Crystals this turn only.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
TEST_CASE("[Druid : Spell] - SCH_427 : Lightning Bloom")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(8);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bloom"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bloom"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonling Mechanic"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 2);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 2);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 2);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 2);
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 2);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [SCH_606] Partner Assignment - COST:1
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: Add a random 2-Cost and 3-Cost Beast to your hand.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SCH_606 : Partner Assignment")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(8);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Partner Assignment"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetCost(), 2);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::BEAST);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->GetCost(), 3);
    CHECK_EQ(curHand[1]->card->GetRace(), Race::BEAST);
}

// ------------------------------------------ SPELL - DRUID
// [SCH_612] Runic Carvings - COST:6
// - Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Choose One -</b> Summon four 2/2 Treant Totems; or
//       <b>Overload:</b> (2) to summon them with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// - OVERLOAD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SCH_612 : Runic Carvings")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Runic Carvings"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Runic Carvings"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bloom"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Treant Totem");
    CHECK_EQ(curField[0]->HasRush(), false);
    CHECK_EQ(curField[1]->card->name, "Treant Totem");
    CHECK_EQ(curField[1]->HasRush(), false);
    CHECK_EQ(curField[2]->card->name, "Treant Totem");
    CHECK_EQ(curField[2]->HasRush(), false);
    CHECK_EQ(curField[3]->card->name, "Treant Totem");
    CHECK_EQ(curField[3]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 4);
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[4]->card->name, "Treant Totem");
    CHECK_EQ(curField[4]->HasRush(), true);
    CHECK_EQ(curField[5]->card->name, "Treant Totem");
    CHECK_EQ(curField[5]->HasRush(), true);
    CHECK_EQ(curField[6]->card->name, "Treant Totem");
    CHECK_EQ(curField[6]->HasRush(), true);
}

// ----------------------------------------- MINION - DRUID
// [SCH_613] Groundskeeper - COST:4 [ATK:4/HP:5]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> If you're holding a
//       spell that costs (5) or more, restore 5 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_DRAG_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SCH_613 : Groundskeeper")
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

    auto curHero = curPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Groundskeeper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Groundskeeper"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodlust"));

    curHero->SetDamage(15);
    CHECK_EQ(curHero->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, curHero));
    CHECK_EQ(curHero->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetAttack(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, curHero));
    CHECK_EQ(curHero->GetHealth(), 20);
}

// ----------------------------------------- MINION - DRUID
// [SCH_616] Twilight Runner - COST:5 [ATK:5/HP:4]
// - Race: Beast, Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b> Whenever this attacks, draw 2 cards.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SCH_616 : Twilight Runner")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Runner"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 7);
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
TEST_CASE("[Hunter : Minion] - SCH_133 : Wolpertinger")
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

// ----------------------------------------- SPELL - HUNTER
// [SCH_300] Carrion Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a <b>Deathrattle</b> minion.
//       Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - SCH_300 : Carrion Studies")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carrion Studies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->HasGameTag(GameTag::DEATHRATTLE), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 0);

    const int oldCost = curHand[1]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    if (curHand[0]->GetCost() != 0)
    {
        CHECK_EQ(curHand[0]->GetCost(), oldCost + 1);
    }
}

// ---------------------------------------- MINION - HUNTER
// [SCH_340] Bloated Python - COST:3 [ATK:1/HP:2]
// - Race: Beast, Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 4/4 Hapless Handler.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - SCH_340 : Bloated Python")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloated Python"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Hapless Handler");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ------------------------------------------ MINION - MAGE
// [SCH_241] Firebrand - COST:3 [ATK:3/HP:4]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst</b>: Deal 4 damage randomly split
//       among all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - SCH_241 : Firebrand")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Firebrand"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    const bool check1 = opField.GetCount() == 1 && opField[0]->GetHealth() == 4;
    const bool check2 = opField.GetCount() == 2 && opField[1]->GetHealth() == 3;
    const bool check = check1 || check2;
    CHECK(check);
}

// ------------------------------------------ MINION - MAGE
// [SCH_243] Wyrm Weaver - COST:5 [ATK:3/HP:6]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Summon two 1/3 Mana Wyrms.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - SCH_243 : Wyrm Weaver")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wyrm Weaver"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->HasSpellburst(), false);
    CHECK_EQ(curField[0]->card->name, "Mana Wyrm");
    CHECK_EQ(curField[2]->card->name, "Mana Wyrm");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
}

// ------------------------------------------ MINION - MAGE
// [SCH_310] Lab Partner - COST:1 [ATK:1/HP:3]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - SCH_310 : Lab Partner")
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [SCH_712] Judicious Junior - COST:6 [ATK:4/HP:9]
// - Set: Scholomance, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - SCH_712 : Judicious Junior")
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
// [SCH_137] Frazzled Freshman - COST:1 [ATK:1/HP:4]
// - Set: SCHOLOMANCE, Rarity: Common
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

// ----------------------------------------- SPELL - PRIEST
// [SCH_233] Draconic Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a Dragon. Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - SCH_233 : Draconic Studies")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Draconic Studies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Savannah Highmane"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 8);
    CHECK_EQ(card3->GetCost(), 6);

    const int oldCost = curHand[2]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 8);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    if (curHand[1]->GetCost() != 0)
    {
        CHECK_EQ(curHand[1]->GetCost(), oldCost + 1);
    }
    CHECK_EQ(card3->GetCost(), 6);
}

// ----------------------------------------- MINION - ROGUE
// [SCH_234] Shifty Sophomore - COST:4 [ATK:4/HP:4]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Spellburst:</b> Add a
//       <b>Combo</b> card to your hand.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
// RefTag:
// - COMBO = 1
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

// ----------------------------------------- MINION - ROGUE
// [SCH_426] Infiltrator Lilian - COST:4 [ATK:4/HP:2]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Deathrattle:</b> Summon a
//       4/2 Forsaken Lilian that attacks a random enemy.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SCH_426 : Infiltrator Lilian")
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

    // Case when attack "Abomination"
    if (curField.GetCount() == 0)
    {
        CHECK_EQ(opField.GetCount(), 0);
        CHECK_EQ(curHero->GetHealth(), 26);
        CHECK_EQ(opHero->GetHealth(), 24);
    }
    // Case when attack opponent hero
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

// ----------------------------------------- WEAPON - ROGUE
// [SCH_622] Self-Sharpening Sword - COST:3
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
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
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> At the end of your opponent's turn,
//       add copies of the cards they played to your hand.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
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

// ---------------------------------------- SPELL - WARLOCK
// [SCH_158] Demonic Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a Demon. Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SCH_158 : Demonic Studies")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonic Studies"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Aranasi Broodmother"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Savannah Highmane"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DEMON);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 6);

    const int oldCost = curHand[2]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    if (curHand[1]->GetCost() != 0)
    {
        CHECK_EQ(curHand[1]->GetCost(), oldCost + 1);
    }
    CHECK_EQ(card3->GetCost(), 6);
}

// ---------------------------------------- SPELL - WARRIOR
// [SCH_237] Athletic Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a <b>Rush</b> minion.
//       Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - SCH_237 : Athletic Studies")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Athletic Studies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hippogryph"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Savannah Highmane"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->HasGameTag(GameTag::RUSH), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 6);

    const int oldCost = curHand[2]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    if (curHand[1]->GetCost() != 0)
    {
        CHECK_EQ(curHand[1]->GetCost(), oldCost + 1);
    }
    CHECK_EQ(card3->GetCost(), 6);
}

// ----------------------------------- MINION - DEMONHUNTER
// [SCH_705] Vilefiend Trainer - COST:4 [ATK:5/HP:4]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Summon two 1/1 Demons.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SCH_705 : Vilefiend Trainer")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Vilefiend Trainer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vilefiend Trainer"));
    [[maybe_unused]] const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vilefiend Trainer"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 0));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Snarling Vilefiend");
    CHECK_EQ(curField[1]->card->name, "Vilefiend Trainer");
    CHECK_EQ(curField[2]->card->name, "Snarling Vilefiend");
    CHECK_EQ(curField[3]->card->name, "Vilefiend Trainer");
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_143] Divine Rager - COST:4 [ATK:5/HP:1]
// - Race: Elemental, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_143 : Divine Rager")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_145] Desk Imp - COST:0 [ATK:1/HP:1]
// - Race: Demon, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_145 : Desk Imp")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_230] Onyx Magescribe - COST:6 [ATK:4/HP:9]
// - Race: Dragon, Set: SCHOLOMANCE, Rarity: Common
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

// --------------------------------------- WEAPON - NEUTRAL
// [SCH_259] Sphere of Sapience - COST:1
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: At the start of your turn, look at your top card.
//       You can put it on the bottom and lose 1 Durability.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Weapon] - SCH_259 : Sphere of Sapience")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto curHero = curPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sphere of Sapience"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, HeroPowerTask());
    CHECK(curPlayer->choice == nullptr);

    std::string topCardID = curDeck.GetTopCard()->card->id;

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_RESOURCE);

    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    CHECK_EQ(cards.size(), 2);
    CHECK_EQ(cards[0]->id, topCardID);
    CHECK_EQ(cards[1]->id, "SCH_259t");

    TestUtils::ChooseNthChoice(game, 1);
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero->weapon->GetDurability(), 4);
    CHECK_EQ(curHand.GetAll().back()->card->id, topCardID);

    std::string secondCardID = curDeck.GetNthTopCard(2)->card->id;
    topCardID = curDeck.GetTopCard()->card->id;

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_RESOURCE);

    CHECK(curPlayer->choice != nullptr);

    cards = TestUtils::GetChoiceCards(game);
    CHECK_EQ(cards.size(), 2);
    CHECK_EQ(cards[0]->id, topCardID);
    CHECK_EQ(cards[1]->id, "SCH_259t");

    TestUtils::ChooseNthChoice(game, 2);
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero->weapon->GetDurability(), 3);
    CHECK_EQ(curHand.GetAll().back()->card->id, secondCardID);
    CHECK_EQ(curDeck.GetNthTopCard(curDeck.GetCount())->card->id, topCardID);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_270] Primordial Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a <b>Spell Damage</b> minion.
//       Your next one costs (1) less.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - SCH_270 : Primordial Studies")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::ROGUE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Primordial Studies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Savannah Highmane"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->HasGameTag(GameTag::SPELLPOWER), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 6);

    const int oldCost = curHand[2]->GetCost();

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    if (curHand[1]->GetCost() != 0)
    {
        CHECK_EQ(curHand[1]->GetCost(), oldCost + 1);
    }
    CHECK_EQ(card3->GetCost(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_350] Wand Thief - COST:1 [ATK:1/HP:2]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> <b>Discover</b> a Mage spell.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_350 : Wand Thief")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wand Thief"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wand Thief"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice == nullptr);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->GetCardClass(), CardClass::MAGE);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_351] Jandice Barov - COST:5 [ATK:2/HP:1]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two random 5-Cost minions.
//       Secretly pick one that dies when it takes damage.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_351 : Jandice Barov")
{
    // Test case for 'Jandice Barov' (SCH_351)
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
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
        const auto card2 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
        const auto card3 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Jandice Barov"));
        const auto card4 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Jandice Barov"));

        game.Process(curPlayer, PlayCardTask::Minion(card1));
        game.Process(curPlayer, PlayCardTask::Minion(card2));
        game.Process(curPlayer, PlayCardTask::Minion(card3));
        CHECK(curPlayer->choice != nullptr);

        const auto& left = curField[2];
        const auto& right = curField[4];
        CHECK_NE(left->card->dbfID, right->card->dbfID);
        CHECK_EQ(left->card->GetCardType(), CardType::MINION);
        CHECK_EQ(left->card->GetCost(), 5);
        CHECK_EQ(right->card->GetCardType(), CardType::MINION);
        CHECK_EQ(right->card->GetCost(), 5);

        auto cards = TestUtils::GetChoiceCards(game);
        CHECK_EQ(cards.size(), 2);
        CHECK_EQ(cards[0]->dbfID, left->card->dbfID);
        CHECK_EQ(cards[1]->dbfID, right->card->dbfID);

        TestUtils::ChooseNthChoice(game, 2);
        CHECK_EQ(left->appliedEnchantments.size(), 0);
        CHECK_EQ(right->appliedEnchantments.size(), 1);
        CHECK_EQ(right->appliedEnchantments[0]->card->id, "SCH_351a");

        curPlayer->SetUsedMana(0);
        game.Process(curPlayer, PlayCardTask::Minion(card4));
        CHECK(curPlayer->choice == nullptr);
        CHECK_EQ(curField.IsFull(), true);
        CHECK_EQ(curField[5]->card->GetCardType(), CardType::MINION);
        CHECK_EQ(curField[5]->card->GetCost(), 5);
    }

    // Test case for 'This is an Illusion' (SCH_351a)
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
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
        const auto card2 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Abomination"));
        const auto card3 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Dalaran Crusader"));
        const auto card4 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
        const auto card5 =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));

        game.Process(curPlayer, PlayCardTask::Minion(card1));
        game.Process(curPlayer, PlayCardTask::Minion(card2));
        game.Process(curPlayer, PlayCardTask::Minion(card3));

        Generic::AddEnchantment(Cards::FindCardByID("SCH_351a"),
                                dynamic_cast<Playable*>(card1), card2);
        Generic::AddEnchantment(Cards::FindCardByID("SCH_351a"),
                                dynamic_cast<Playable*>(card1), card3);
        CHECK_EQ(card2->appliedEnchantments.size(), 1);
        CHECK_EQ(card3->appliedEnchantments.size(), 1);

        game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2));
        CHECK_EQ(card2->isDestroyed, true);
        CHECK_EQ(card3->isDestroyed, false);

        game.Process(curPlayer, PlayCardTask::SpellTarget(card5, card3));
        CHECK_EQ(card3->isDestroyed, true);
        CHECK_EQ(curField.GetCount(), 0);
    }
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_352] Potion of Illusion - COST:4
// - Set: SCHOLOMANCE, Rarity: Epic
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
    [[maybe_unused]] const auto card5 =
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_425] Doctor Krastinov - COST:5 [ATK:4/HP:4]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>
//       Whenever this attacks, give your weapon +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_425 : Doctor Krastinov")
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doctor Krastinov"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doctor Krastinov"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doctor Krastinov"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blazing Battlemage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opHero));
    CHECK_EQ(curHero->HasWeapon(), false);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, AttackTask(card2, opHero));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 2);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, AttackTask(card3, card4));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 3);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 4);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_509] Brain Freeze - COST:1
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Freeze</b> a minion.
//       <b>Combo:</b> Also deal 3 damage to it.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
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
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy a damaged minion.
//       <b>Combo:</b> Destroy any minion.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
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
// - Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a random minion with Cost
//       equal to your weapon's Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hooked Scimitar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetCost(), 0);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->GetCost(), 4);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_623] Cutting Class - COST:5
// - Set: SCHOLOMANCE, Rarity: Common
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
// - Race: Murloc, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Deathrattle:</b> Add a 4/3 Ghost
//       with <b>Rush</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_707 : Fishy Flyer")
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
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. <b>Deathrattle:</b> Add a 3/1 Ghost
//       with <b>Stealth</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_708 : Sneaky Delinquent")
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
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Deathrattle:</b> Add a 5/7 Ghost
//       with <b>Taunt</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_709 : Smug Senior")
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
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever your opponent casts a spell,
//       summon a 2/2 Skeleton with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_710 : Ogremancer")
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
// - Race: Dragon, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random 7-Cost minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_711 : Plagued Protodrake")
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_713] Cult Neophyte - COST:2 [ATK:3/HP:2]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your opponent's spells cost (1)
//       more next turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_713 : Cult Neophyte")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cult Neophyte"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 11);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_717] Keymaster Alabaster - COST:7 [ATK:6/HP:8]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever your opponent draws a card,
//       add a copy to your hand that costs (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[NEUTRAL : Minion] - SCH_717 : Keymaster Alabaster")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;
    config.fillCardIDs = { "CS2_124", "CS2_124", "CS2_124",
                           "CS2_124", "CS2_124", "CS2_124",
                           "CS2_124", "CS2_124", "CS2_124" };

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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Keymaster Alabaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(curHand[4]->card->id, opHand[5]->card->id);
    CHECK_EQ(curHand[5]->card->id, opHand[6]->card->id);
    CHECK_EQ(curHand[4]->GetCost(), 1);
    CHECK_EQ(curHand[5]->GetCost(), 1);
}