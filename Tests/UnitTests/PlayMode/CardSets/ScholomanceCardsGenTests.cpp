// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [SCH_242] Gibberling - COST:2 [ATK:1/HP:1]
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
// - Spell School: Nature
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
    CHECK(curPlayer->choice);

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
    if (curHand[0]->GetCost() != 0 &&
        curHand[0]->card->name != "Moontouched Amulet")
    {
        CHECK_EQ(curHand[0]->GetCost(), oldCost + 1);
    }
}

// ------------------------------------------ SPELL - DRUID
// [SCH_427] Lightning Bloom - COST:0
// - Set: SCHOLOMANCE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Refresh 2 Mana Crystals.
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
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 4);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 2);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 4);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
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
// - Spell School: Nature
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
// [SCH_614] Forest Warden Omu - COST:6 [ATK:5/HP:4]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Refresh your Mana Crystals.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SCH_614 : Forest Warden Omu")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Forest Warden Omu"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
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

    const auto& curHand = *(curPlayer->GetHandZone());

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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolpertinger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    CHECK_EQ(curField[0]->card->name, "Wolpertinger");
    CHECK_EQ(curField[1]->card->name, "Wolpertinger");
}

// ---------------------------------------- MINION - HUNTER
// [SCH_239] Krolusk Barkstripper - COST:4 [ATK:3/HP:5]
// - Race: Beast, Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Destroy a random enemy minion.
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - SCH_239 : Krolusk Barkstripper")
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

    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Krolusk Barkstripper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Trap"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 2);
}

// ---------------------------------------- MINION - HUNTER
// [SCH_244] Teacher's Pet - COST:5 [ATK:4/HP:5]
// - Race: Beast, Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Summon a random 3-Cost Beast.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - SCH_244 : Teacher's Pet")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Teacher's Pet"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 3);
    CHECK_EQ(curField[0]->card->GetRace(), Race::BEAST);
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
    CHECK(curPlayer->choice);

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

// ----------------------------------------- SPELL - HUNTER
// [SCH_617] Adorable Infestation - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +1/+1. Summon a 1/1 Cub.
//       Add a Cub to your hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - SCH_617 : Adorable Infestation")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Adorable Infestation"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Marsuul Cub");
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Marsuul Cub");
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
// [SCH_243] Wyrm Weaver - COST:4 [ATK:3/HP:5]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Summon two 1/2 Mana Wyrms.
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

// ---------------------------------------- SPELL - PALADIN
// [SCH_247] First Day of School - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Add 2 random 1-Cost minions to your hand.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - SCH_247 : First Day of School")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("First Day of School"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetCost(), 1);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->GetCost(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [SCH_524] Shield of Honor - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a damaged minion +3 Attack and <b>Divine Shield</b>.
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_DAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - SCH_524 : Shield of Honor")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield of Honor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// --------------------------------------- MINION - PALADIN
// [SCH_526] Lord Barov - COST:3 [ATK:3/HP:2]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Set the Health of all other minions to 1.
//       <b>Deathrattle:</b> Deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - SCH_526 : Lord Barov")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lord Barov"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - PALADIN
// [SCH_532] Goody Two-Shields - COST:3 [ATK:4/HP:2]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Spellburst:</b> Gain <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - SCH_532 : Goody Two-Shields")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goody Two-Shields"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Redemption"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasSpellburst(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [SCH_533] Commencement - COST:7
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: Summon a minion from your deck.
//       Give it <b>Taunt</b> and <b>Divine Shield</b>.
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - SCH_533 : Commencement")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Commencement"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
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
    CHECK(curPlayer->choice);

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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Infiltrator Lilian"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));

    const int totalHealth =
        opField[0]->GetHealth() + opPlayer->GetHero()->GetHealth();
    CHECK_EQ(totalHealth, 38);
}

// ----------------------------------------- MINION - ROGUE
// [SCH_519] Vulpera Toxinblade - COST:3 [ATK:3/HP:3]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Your weapon has +2 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SCH_519 : Vulpera Toxinblade")
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
        curPlayer, Cards::FindCardByName("Vulpera Toxinblade"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Self-Sharpening Sword"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero->GetAttack(), 0);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curHero->GetAttack(), 3);

    game.Process(curPlayer, AttackTask(curHero, opHero));
    CHECK_EQ(curHero->GetAttack(), 4);
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curHero->GetAttack(), 1);
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
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plagiarize"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret.GetCount(), 1);

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

    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Arcane Missiles");
    CHECK_EQ(curHand[1]->card->name, "Blizzard");
}

// --------------------------------------- MINION - WARLOCK
// [SCH_147] Boneweb Egg - COST:2 [ATK:0/HP:2]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon two 2/1 Spiders.
//       If you discard this, trigger its <b>Deathrattle</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - InvisibleDeathrattle = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SCH_147 : Boneweb Egg")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boneweb Egg"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boneweb Egg"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->card->name, "Boneweb Spider");
    CHECK_EQ(curField[1]->card->name, "Boneweb Spider");
    CHECK_EQ(curField[2]->card->name, "Boneweb Spider");
    CHECK_EQ(curField[3]->card->name, "Boneweb Spider");
}

// ---------------------------------------- SPELL - WARLOCK
// [SCH_158] Demonic Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// - Spell School: Shadow
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
    CHECK(curPlayer->choice);

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

// ---------------------------------------- SPELL - WARLOCK
// [SCH_307] School Spirits - COST:3
// - Set: SCHOLOMANCE, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 2 damage to all minions.
//       Shuffle 2 Soul Fragments into your deck.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SCH_307 : School Spirits")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("School Spirits"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 13);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

// --------------------------------------- MINION - WARLOCK
// [SCH_343] Void Drinker - COST:5 [ATK:4/HP:5]
// - Race: Demon, Set: SCHOLOMANCE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Battlecry:</b> Destroy
//       a Soul Fragment in your deck to gain +3/+3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SCH_343 : Void Drinker")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("School Spirits"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Void Drinker"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Void Drinker"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// --------------------------------------- MINION - WARLOCK
// [SCH_517] Shadowlight Scholar - COST:3 [ATK:3/HP:4]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a Soul Fragment in your deck
//       to deal 3 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SCH_517 : Shadowlight Scholar")
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("School Spirits"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowlight Scholar"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowlight Scholar"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 2);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 12);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 12);
}

// --------------------------------------- MINION - WARLOCK
// [SCH_700] Spirit Jailer - COST:1 [ATK:1/HP:3]
// - Race: Demon, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle 2 Soul Fragments into your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SCH_700 : Spirit Jailer")
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spirit Jailer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curDeck[0]->card->name, "Soul Fragment");
    CHECK_EQ(curDeck[1]->card->name, "Soul Fragment");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
    CHECK_EQ(curDeck.GetCount(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [SCH_701] Soul Shear - COST:2
// - Set: SCHOLOMANCE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
//       Shuffle 2 Soul Fragments into your deck.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SCH_701 : Soul Shear")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soul Shear"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(opField[0]->GetHealth(), 8);
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curDeck[0]->card->name, "Soul Fragment");
    CHECK_EQ(curDeck[1]->card->name, "Soul Fragment");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 13);
    CHECK_EQ(curDeck.GetCount(), 0);
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
    CHECK(curPlayer->choice);

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

// ---------------------------------------- SPELL - WARRIOR
// [SCH_525] In Formation! - COST:2
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Add 2 random <b>Taunt</b> minions to your hand.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - SCH_525 : In Formation!")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("In Formation!"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->HasGameTag(GameTag::TAUNT), true);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->HasGameTag(GameTag::TAUNT), true);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [SCH_252] Marrowslicer - COST:4
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle 2 Soul Fragments into your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - SCH_252 : Marrowslicer")
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Marrowslicer"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 4);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curDeck[0]->card->name, "Soul Fragment");
    CHECK_EQ(curDeck[1]->card->name, "Soul Fragment");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
    CHECK_EQ(curDeck.GetCount(), 0);
}

// ----------------------------------- MINION - DEMONHUNTER
// [SCH_355] Shardshatter Mystic - COST:3 [ATK:3/HP:2]
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a Soul Fragment
//       in your deck to deal 3 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SCH_355 : Shardshatter Mystic")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spirit Jailer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shardshatter Mystic"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shardshatter Mystic"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [SCH_422] Double Jump - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: Draw an <b>Outcast</b> card from your deck.
// --------------------------------------------------------
// RefTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - SCH_422 : Double Jump")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = (i < 5)
                                    ? Cards::FindCardByName("Eye Beam")
                                    : Cards::FindCardByName("Faerie Dragon");
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Double Jump"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Double Jump"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 25);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Eye Beam");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curDeck.GetCount(), 25);
    CHECK_EQ(curHand.GetCount(), 5);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [SCH_600] Demon Companion - COST:1
// - Set: SCHOLOMANCE, Rarity: Rare
// --------------------------------------------------------
// Text: Summon a random Demon Companion.
// --------------------------------------------------------
// Entourage: SCH_600t1, SCH_600t2, SCH_600t3
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - SCH_600 : Demon Companion")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demon Companion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);

    const bool isReffuh = curField[1]->card->id == "SCH_600t1";
    const bool isShima = curField[1]->card->id == "SCH_600t2";
    const bool isKolek = curField[1]->card->id == "SCH_600t3";
    const bool isDemon = isReffuh || isShima || isKolek;
    CHECK(isDemon);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[1]));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    SUBCASE("Reffuh - SCH_600t1")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("SCH_600t1"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 2);
        CHECK_EQ(curField[1]->GetHealth(), 1);
        CHECK_EQ(curField[1]->HasCharge(), true);
    }

    SUBCASE("Shima - SCH_600t2")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("SCH_600t2"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 2);
        CHECK_EQ(curField[1]->GetHealth(), 2);
        CHECK_EQ(curField[1]->HasTaunt(), true);
    }

    SUBCASE("Kolek - SCH_600t3")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("SCH_600t3"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 1);
        CHECK_EQ(curField[1]->GetHealth(), 2);
        CHECK_EQ(curField[0]->GetAttack(), 4);
    }
}

// ----------------------------------- MINION - DEMONHUNTER
// [SCH_704] Soulshard Lapidary - COST:5 [ATK:5/HP:5]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a Soul Fragment in your deck
//       to give your hero +5 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SCH_704 : Soulshard Lapidary")
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spirit Jailer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soulshard Lapidary"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soulshard Lapidary"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
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
// [SCH_160] Wandmaker - COST:2 [ATK:2/HP:2]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a 1-Cost spell
//       from your class to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_160 : Wandmaker")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wandmaker"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wandmaker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsCardClass(CardClass::WARRIOR), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opHand.GetCount(), 2);
    CHECK_EQ(opHand[1]->card->IsCardClass(CardClass::MAGE), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_162] Vectus - COST:5 [ATK:4/HP:4]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Whelps.
//       Each gains a <b>Deathrattle</b> from your minions
//       that died this game.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_162 : Vectus")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kobold Sandtrooper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlwind"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vectus"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlwind"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);
    CHECK_EQ(curField[2]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 10);
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
// Text: <b>Spellburst:</b> Gain +2 Attack.
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_232] Crimson Hothead - COST:4 [ATK:3/HP:6]
// - Race: Dragon, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Gain +1 Attack and <b>Taunt</b>.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_232 : Crimson Hothead")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crimson Hothead"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->HasTaunt(), false);
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasSpellburst(), false);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasSpellburst(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_245] Steward of Scrolls - COST:5 [ATK:4/HP:4]
// - Race: Elemental, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_245 : Steward of Scrolls")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Steward of Scrolls"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
    }

    TestUtils::ChooseNthChoice(game, 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_248] Pen Flinger - COST:1 [ATK:1/HP:1]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to a minion.
//       <b>Spellburst:</b> Return this to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_248 : Pen Flinger")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pen Flinger"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Redemption"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Equality"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card4));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(opField[0]->GetHealth(), 11);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[6]->card->name, "Pen Flinger");

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[6], card4));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Pen Flinger");
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[5], card4));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opField.GetCount(), 0);
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
    CHECK(!curPlayer->choice);

    std::string topCardID = curDeck.GetTopCard()->card->id;

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_RESOURCE);

    CHECK(curPlayer->choice);

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

    CHECK(curPlayer->choice);

    cards = TestUtils::GetChoiceCards(game);
    CHECK_EQ(cards.size(), 2);
    CHECK_EQ(cards[0]->id, topCardID);
    CHECK_EQ(cards[1]->id, "SCH_259t");

    TestUtils::ChooseNthChoice(game, 2);
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero->weapon->GetDurability(), 3);
    CHECK_EQ(curHand.GetAll().back()->card->id, secondCardID);
    CHECK_EQ(curDeck.GetBottomCard()->card->id, topCardID);
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_270] Primordial Studies - COST:1
// - Set: SCHOLOMANCE, Rarity: Common
// - Spell School: Arcane
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
    CHECK(curPlayer->choice);

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
// [SCH_273] Ras Frostwhisper - COST:5 [ATK:3/HP:6]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn, deal 1 damage
//       to all enemies (improved by <b>Spell Damage</b>).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_273 : Ras Frostwhisper")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ras Frostwhisper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ogre Magi"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_283] Manafeeder Panthara - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've used your Hero Power
//       this turn, draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_283 : Manafeeder Panthara")
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
        curPlayer, Cards::FindCardByName("Manafeeder Panthara"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Manafeeder Panthara"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_311] Animated Broomstick - COST:1 [ATK:1/HP:1]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Battlecry:</b> Give your other minions <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_311 : Animated Broomstick")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Animated Broomstick"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_312] Tour Guide - COST:1 [ATK:1/HP:1]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your next Hero Power costs (0).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_312 : Tour Guide")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tour Guide"));

    CHECK_EQ(curPlayer->GetHero()->heroPower->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->GetCost(), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->heroPower->GetCost(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [SCH_313] Wretched Tutor - COST:4 [ATK:2/HP:5]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spellburst:</b> Deal 2 damage to all other minions.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_313 : Wretched Tutor")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wretched Tutor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windfury Harpy"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 10);
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
    CHECK(!curPlayer->choice);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);

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
        CHECK(curPlayer->choice);

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
        CHECK(!curPlayer->choice);
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
// - Spell School: Arcane
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_428] Lorekeeper Polkelt - COST:4 [ATK:4/HP:5]
// - Set: SCHOLOMANCE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Reorder your deck from the highest
//       Cost card to the lowest Cost card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_428 : Lorekeeper Polkelt")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    const std::string INNKEEPER_EXPERT_WARLOCK =
        "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
    const auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

    for (size_t j = 0; j < deck.size(); ++j)
    {
        config.player1Deck[j] = Cards::FindCardByID(deck[j]);
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

    const auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lorekeeper Polkelt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 26);

    for (int count = 1; count < curDeck.GetCount(); ++count)
    {
        CHECK(curDeck.GetNthTopCard(count)->GetCost() >=
              curDeck.GetNthTopCard(count + 1)->GetCost());
    }
}

// ---------------------------------------- SPELL - NEUTRAL
// [SCH_509] Brain Freeze - COST:1
// - Set: SCHOLOMANCE, Rarity: Rare
// - Spell School: Frost
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

// --------------------------------------- MINION - NEUTRAL
// [SCH_530] Sorcerous Substitute - COST:6 [ATK:6/HP:6]
// - Set: SCHOLOMANCE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have <b>Spell Damage</b>,
//       summon a copy of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SCH_530 : Sorcerous Substitute")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sorcerous Substitute"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sorcerous Substitute"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[2]->card->name, "Sorcerous Substitute");
    CHECK_EQ(curField[3]->card->name, "Sorcerous Substitute");
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