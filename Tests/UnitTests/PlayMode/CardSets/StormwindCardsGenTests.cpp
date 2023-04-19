// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [SW_419] Oracle of Elune - COST:3 [ATK:2/HP:4]
// - Set: STORMWIND, Rarity: Epic
// --------------------------------------------------------
// Text: After you play a minion that costs (2) or less,
//       summon a copy of it.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SW_419 : Oracle of Elune")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oracle of Elune"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[2]->card->name, "Wisp");
    CHECK_EQ(curField[3]->card->name, "Wisp");
}

// ------------------------------------------ SPELL - DRUID
// [SW_422] Sow the Soil - COST:1
// - Set: STORMWIND, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One</b> - Give your minions +1 Attack;
//       or Summon a 2/2 Treant.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_422 : Sow the Soil")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sow the Soil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sow the Soil"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [SW_428] Lost in the Park - COST:1
// - Set: STORMWIND, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Questline:</b> Gain 4 Attack with your hero.
//       <b>Reward:</b> Gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_428 : Lost in the Park")
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

    auto& curHand = *(curPlayer->GetHandZone());
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lost in the Park"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curSecret->quest);
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 1));
    CHECK(curSecret->quest);
    CHECK_EQ(curSecret->quest->card->name, "Defend the Squirrels");
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3, 1));
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 9);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK(curSecret->quest);
    CHECK_EQ(curSecret->quest->card->name, "Feral Friendsy");
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 6);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 11);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);
    CHECK_EQ(curHand.GetCount(), 7);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card4, 1));
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 15);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);

    game.Process(curPlayer, PlayCardTask::Spell(card6));
    CHECK(!curSecret->quest);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 17);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Guff the Tough");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[5]));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 25);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 19);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 19);
}

// ------------------------------------------ SPELL - DRUID
// [SW_429] Best in Shell - COST:6
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       Summon two 2/7 Turtles with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - TRADEABLE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_429 : Best in Shell")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Best in Shell"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Goldshell Turtle");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Goldshell Turtle");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ----------------------------------------- MINION - DRUID
// [SW_431] Park Panther - COST:4 [ATK:4/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>. Whenever this attacks,
//       give your hero +3 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SW_431 : Park Panther")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Park Panther"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [SW_432] Kodo Mount - COST:4
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +4/+2 and <b>Rush</b>.
//       When it dies, summon a Kodo.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_432 : Kodo Mount")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kodo Mount"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Guff's Kodo");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasRush(), true);
}

// ----------------------------------------- MINION - DRUID
// [SW_436] Wickerclaw - COST:2 [ATK:1/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: After your hero gains Attack,
//       this minion gains +2 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SW_436 : Wickerclaw")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wickerclaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 5);
}

// ------------------------------------------ SPELL - DRUID
// [SW_437] Composting - COST:2
// - Set: STORMWIND, Rarity: Epic
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your minions "<b>Deathrattle:</b> Draw a card."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - SW_437 : Composting")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Composting"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(curField[1]->HasDeathrattle(), false);
    CHECK_EQ(curField[2]->HasDeathrattle(), false);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);
    CHECK_EQ(curField[1]->HasDeathrattle(), true);
    CHECK_EQ(curField[2]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curField.GetCount(), 1);
}

// ----------------------------------------- MINION - DRUID
// [SW_439] Vibrant Squirrel - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle 4 Acorns into your deck.
//       When drawn, summon a 2/1 Squirrel.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_439 : Vibrant Squirrel")
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vibrant Squirrel"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 1);
}

// ----------------------------------------- MINION - DRUID
// [DED_001] Druid of the Reef - COST:1 [ATK:1/HP:1]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One - </b>Transform into
//       a 3/1 Shark with <b>Rush</b>; or
//       a 1/3 Turtle with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DED_001 : Druid of the Reef")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Reef"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Reef"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField[0]->card->name, "Druid of the Reef");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField[1]->card->name, "Druid of the Reef");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [SW_321] Aimed Shot - COST:3
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage.
//       Your next Hero Power deals 2 more damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - SW_321 : Aimed Shot")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Aimed Shot"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetHero()->GetHeroPowerDamage(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHeroPowerDamage(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(curPlayer->GetHero()->GetHeroPowerDamage(), 0);
}

// ---------------------------------------- MINION - HUNTER
// [SW_455] Rodent Nest - COST:4 [ATK:2/HP:2]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon five 1/1 Rats.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - SW_455 : Rodent Nest")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rodent Nest"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Rat");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Rat");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Rat");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Rat");
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[4]->card->name, "Rat");
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [SW_107] Fire Sale - COST:4
// - Set: STORMWIND, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       Deal 3 damage to all minions.
// --------------------------------------------------------
// RefTag:
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - SW_107 : Fire Sale")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Sale"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ------------------------------------------- SPELL - MAGE
// [SW_108] First Flame - COST:1
// - Set: STORMWIND, Rarity: Rare
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       Add a Second Flame to your hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - SW_108 : First Flame")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("First Flame"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Second Flame");
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card2));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [SW_046] City Tax - COST:2
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Lifesteal</b>. Deal 1 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - SW_046 : City Tax")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("City Tax"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[1]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 17);
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(opField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - PALADIN
// [SW_305] First Blade of Wrynn - COST:4 [ATK:3/HP:5]
// - Set: STORMWIND, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Battlecry:</b> Gain <b>Rush</b>
//       if this has at least 4 Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - SW_305 : First Blade of Wrynn")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("First Blade of Wrynn"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("First Blade of Wrynn"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Alliance Bannerman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->HasDivineShield(), true);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// --------------------------------------- MINION - PALADIN
// [SW_315] Alliance Bannerman - COST:3 [ATK:2/HP:1]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a minion.
//       Give minions in your hand +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - SW_315 : Alliance Bannerman")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("City Tax");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Noble Mount");
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
        curPlayer, Cards::FindCardByName("Alliance Bannerman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 13);
}

// ---------------------------------------- SPELL - PALADIN
// [SW_316] Noble Mount - COST:2
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +1/+1 and <b>Divine Shield</b>.
//       When it dies, summon a Warhorse.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - SW_316 : Noble Mount")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Mount"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField[0]->HasDivineShield(), false);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Cariel's Warhorse");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// ----------------------------------------- SPELL - PRIEST
// [SW_441] Shard of the Naaru - COST:1
// - Set: STORMWIND, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Silence</b> all enemy minions.
// --------------------------------------------------------
// GameTag:
// - TRADEABLE = 1
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - SW_441 : Shard of the Naaru")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
        curPlayer, Cards::FindCardByName("Shard of the Naaru"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(card2->HasDeathrattle(), true);
    CHECK_EQ(card3->HasDeathrattle(), false);
}

// ----------------------------------------- SPELL - PRIEST
// [SW_442] Void Shard - COST:4
// - Set: STORMWIND, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 4 damage.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - SW_442 : Void Shard")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Void Shard"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 16);
}

// ----------------------------------------- SPELL - PRIEST
// [SW_443] Elekk Mount - COST:7
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +4/+7 and <b>Taunt</b>.
//       When it dies, summon an Elekk.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - SW_443 : Elekk Mount")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elekk Mount"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Xyrella's Elekk");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// ---------------------------------------- MINION - PRIEST
// [SW_445] Psyfiend - COST:3 [ATK:3/HP:4]
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a Shadow spell,
//       deal 2 damage to each Hero.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - SW_445 : Psyfiend")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Psyfiend"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - PRIEST
// [DED_513] Defias Leper - COST:2 [ATK:3/HP:2]
// - Race: Pirate, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Shadow spell,
//       deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_DRAG_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - SW_445 : Psyfiend")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Defias Leper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Defias Leper"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ------------------------------------------ SPELL - ROGUE
// [SW_311] Garrote - COST:2
// - Set: STORMWIND, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 2 damage to the enemy hero.
//       Shuffle 2 Bleeds into your deck that
//       deal 2 more when drawn.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - SW_311 : Garrote")
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Garrote"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 18);
    CHECK_EQ(curDeck.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 13);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 7);
}

// ------------------------------------------ SPELL - ROGUE
// [SW_412] SI:7 Extortion - COST:1
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       Deal 3 damage to an undamaged character.
// --------------------------------------------------------
// GameTag:
// - TRADEABLE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_UNDAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - SW_412 : SI:7 Extortion")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Extortion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Extortion"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// ----------------------------------------- MINION - ROGUE
// [SW_413] SI:7 Operative - COST:3 [ATK:2/HP:4]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       After this attacks a minion, gain <b>Stealth</b>.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SW_413 : SI:7 Operative")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Operative"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasStealth(), false);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curField[0]->HasStealth(), true);
}

// ----------------------------------------- MINION - ROGUE
// [SW_434] Loan Shark - COST:3 [ATK:3/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your opponent a Coin.
//       <b>Deathrattle:</b> You get two.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - SW_434 : Loan Shark")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loan Shark"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[2]->card->name, "The Coin");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "The Coin");
    CHECK_EQ(curHand[1]->card->name, "The Coin");
}

// ---------------------------------------- MINION - SHAMAN
// [SW_033] Canal Slogger - COST:4 [ATK:6/HP:4]
// - Race: Elemental, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>, <b>Lifesteal</b>
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// - OVERLOAD = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - SW_033 : Canal Slogger")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [SW_095] Investment Opportunity - COST:1
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: Draw an <b>Overload</b> card.
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - SW_095 : Investment Opportunity")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Feral Spirit");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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
        curPlayer, Cards::FindCardByName("Investment Opportunity"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->HasOverload(), true);
}

// ---------------------------------------- MINION - SHAMAN
// [DED_522] Cookie the Cook - COST:3 [ATK:2/HP:3]
// - Race: Murloc, Set: STORMWIND, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       <b>Deathrattle:</b> Equip a 2/3 Stirring Rod
//       with <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DED_522 : Cookie the Cook")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cookie the Cook"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->HasLifesteal(), true);
}

// --------------------------------------- MINION - WARLOCK
// [SW_084] Bloodbound Imp - COST:2 [ATK:2/HP:5]
// - Race: Demon, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this attacks, deal 2 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SW_084 : Bloodbound Imp")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodbound Imp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - WARLOCK
// [SW_086] Shady Bartender - COST:5 [ATK:4/HP:4]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Battlecry:</b> Give your Demons +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SW_086 : Shady Bartender")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shady Bartender"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desk Imp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ---------------------------------------- SPELL - WARLOCK
// [SW_088] Demonic Assault - COST:4
// - Set: STORMWIND, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 3 damage.
//       Summon two 1/3 Voidwalkers with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SW_088 : Demonic Assault")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonic Assault"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Voidwalker");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Voidwalker");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ---------------------------------------- SPELL - WARLOCK
// [SW_090] Touch of the Nathrezim - COST:1
// - Set: STORMWIND, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it dies, restore 3 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - SW_090 : Touch of the Nathrezim")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Touch of the Nathrezim"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Touch of the Nathrezim"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 18);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 18);
}

// --------------------------------------- MINION - WARLOCK
// [SW_092] Anetheron - COST:6 [ATK:8/HP:6]
// - Race: Demon, Set: STORMWIND, Rarity: Legendary
// --------------------------------------------------------
// Text: Costs (1) if your hand is full.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - SW_092 : Anetheron")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Anetheron"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(card1->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [SW_021] Cowardly Grunt - COST:6 [ATK:6/HP:2]
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a minion from your deck.
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - SW_021 : Cowardly Grunt")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fiery War Axe");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cowardly Grunt"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Wisp");
}

// ---------------------------------------- SPELL - WARRIOR
// [SW_027] Shiver Their Timbers! - COST:1
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If you control a Pirate, deal 5 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - SW_027 : Shiver Their Timbers!")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shiver Their Timbers!"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shiver Their Timbers!"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Harbor Scamp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [SW_029] Harbor Scamp - COST:2 [ATK:2/HP:2]
// - Race: Pirate, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a Pirate.
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - SW_029 : Harbor Scamp")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Stonemaul Anchorman");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Harbor Scamp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::PIRATE);
}

// --------------------------------------- MINION - WARRIOR
// [SW_030] Cargo Guard - COST:3 [ATK:2/HP:4]
// - Race: Pirate, Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn, gain 3 Armor.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - SW_030 : Cargo Guard")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cargo Guard"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);
}

// --------------------------------------- MINION - WARRIOR
// [SW_093] Stormwind Freebooter - COST:3 [ATK:3/HP:4]
// - Race: Pirate, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your hero +2 Attack this turn.
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - SW_093 : Stormwind Freebooter")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stormwind Freebooter"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ---------------------------------------- SPELL - WARRIOR
// [SW_094] Heavy Plate - COST:3
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       Gain 8 Armor.
// --------------------------------------------------------
// RefTag:
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - SW_094 : Heavy Plate")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heavy Plate"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
}

// ---------------------------------------- SPELL - WARRIOR
// [DED_518] Man the Cannons - COST:2
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage to a minion and 1 damage to all other minions.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DED_518 : Man the Cannons")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Man the Cannons"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[1]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 2);
    CHECK_EQ(opField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - WARRIOR
// [DED_519] Defias Cannoneer - COST:3 [ATK:3/HP:3]
// - Race: Pirate, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: After your hero attacks,
//       deal 2 damage to a random enemy twice.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DED_519 : Defias Cannoneer")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Defias Cannoneer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);
}

// ----------------------------------- MINION - DEMONHUNTER
// [SW_037] Irebound Brute - COST:7 [ATK:6/HP:7]
// - Race: Demon, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Costs (1) less for each card drawn this turn.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SW_037 : Irebound Brute")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Irebound Brute"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Strike"));

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);
}

// ----------------------------------- MINION - DEMONHUNTER
// [SW_043] Felgorger - COST:4 [ATK:4/HP:3]
// - Race: Demon, Set: STORMWIND, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a Fel spell.
//       Reduce its Cost by (2).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SW_043 : Felgorger")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Feral Spirit");
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felgorger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetSpellSchool(), SpellSchool::FEL);
    CHECK_EQ(curHand[4]->GetCost(), 3);
}

// ----------------------------------- MINION - DEMONHUNTER
// [SW_451] Metamorfin - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> If you've cast a Fel spell
//       this turn, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - SW_451 : Metamorfin")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Metamorfin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Metamorfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Leech"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [SW_452] Chaos Leech - COST:3
// - Set: STORMWIND, Rarity: Rare
// - Spell School: Fel
// --------------------------------------------------------
// Text: <b>Lifesteal</b>. Deal 3 damage to a minion.
//       <b>Outcast:</b> Deal 5 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - SW_452 : Chaos Leech")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Leech"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Leech"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Leech"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_006] Stubborn Suspect - COST:4 [ATK:3/HP:3]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random 3-Cost minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_006 : Stubborn Suspect")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stubborn Suspect"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_054] Stormwind Guard - COST:5 [ATK:4/HP:5]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Give adjacent minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_054 : Stormwind Guard")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormwind Guard"));
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
// [SW_055] Impatient Shopkeep - COST:3 [ATK:3/HP:3]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_055 : Impatient Shopkeep")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [SW_061] Guild Trader - COST:4 [ATK:3/HP:4]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Spell Damage +2</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_061 : Guild Trader")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [SW_063] Battleground Battlemaster - COST:6 [ATK:5/HP:5]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: Adjacent minions have <b>Windfury</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_063 : Battleground Battlemaster")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Battleground Battlemaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasWindfury(), false);
    CHECK_EQ(curField[1]->HasWindfury(), false);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[1]->HasWindfury(), false);
    CHECK_EQ(curField[2]->HasWindfury(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField[0]->HasWindfury(), false);
    CHECK_EQ(curField[1]->HasWindfury(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_066] Royal Librarian - COST:4 [ATK:3/HP:4]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Battlecry:</b> <b>Silence</b> a minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TRADEABLE = 1
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_066 : Royal Librarian")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Royal Librarian"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Royal Librarian"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_067] Stockades Guard - COST:1 [ATK:1/HP:3]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_067 : Stockades Guard")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stockades Guard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_068] Mo'arg Forgefiend - COST:8 [ATK:8/HP:8]
// - Race: Demon, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_068 : Mo'arg Forgefiend")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mo'arg Forgefiend"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_070] Mailbox Dancer - COST:2 [ATK:3/HP:2]
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a Coin to your hand.
//       <b>Deathrattle:</b> Give your opponent one.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_070 : Mailbox Dancer")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mailbox Dancer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "The Coin");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opHand.GetCount(), 2);
    CHECK_EQ(opHand[0]->card->name, "The Coin");
    CHECK_EQ(opHand[1]->card->name, "The Coin");
}

// --------------------------------------- MINION - NEUTRAL
// [SW_071] Lion's Guard - COST:5 [ATK:4/HP:6]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have 15 or less Health,
//       gain +2/+4 and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_071 : Lion's Guard")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lion's Guard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lion's Guard"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    curPlayer->GetHero()->SetDamage(15);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 10);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_072] Rustrot Viper - COST:3 [ATK:3/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Battlecry:</b> Destroy your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_072 : Rustrot Viper")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Rustrot Viper"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_076] City Architect - COST:6 [ATK:4/HP:4]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 0/5 Castle Walls
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_076 : City Architect")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("City Architect"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Castle Wall");
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "City Architect");
    CHECK_EQ(curField[2]->card->name, "Castle Wall");
    CHECK_EQ(curField[2]->GetAttack(), 0);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[2]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_080] Cornelius Roame - COST:6 [ATK:4/HP:5]
// - Set: STORMWIND, Rarity: Legendary
// --------------------------------------------------------
// Text: At the start and end of each player's turn,
//       draw a card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_080 : Cornelius Roame")
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cornelius Roame"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(opHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 9);
    CHECK_EQ(opHand.GetCount(), 6);
}