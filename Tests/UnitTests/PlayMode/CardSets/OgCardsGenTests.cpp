// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [OG_044] Fandral Staghelm - COST:4 [ATK:3/HP:5]
// - Set: Og, Rarity: Legendary
// --------------------------------------------------------
// Text: Your <b>Choose One</b> cards and powers
//       have both effects combined.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - OG_044 : Fandral Staghelmh")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fandral Staghelm"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Claw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 6);
    CHECK_EQ(curField[3]->HasRush(), true);
    CHECK_EQ(curField[3]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [OG_047] Feral Rage - COST:3
// - Set: Og, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your hero +4 Attack this turn;
//       or Gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - OG_047 : Feral Rage")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// --------------------------------------- MINION - PALADIN
// [OG_229] Ragnaros, Lightlord - COST:8 [ATK:8/HP:8]
// - Race: Elemental, Set: Og, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       restore 8 Health to a damaged friendly character.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - OG_229 : Ragnaros, Lightlord")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ragnaros, Lightlord"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    int totalHealth =
        curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 42);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 32);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 40);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    const bool checkHealth = totalHealth == 32 || totalHealth == 38;
    CHECK(checkHealth);
}

// ---------------------------------------- SPELL - PALADIN
// [OG_273] Stand Against Darkness - COST:4
// - Set: Og, Rarity: Common
// --------------------------------------------------------
// Text: Summon five 1/1 Silver Hand Recruits.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - OG_273 : Stand Against Darkness")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stand Against Darkness"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stand Against Darkness"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[4]->card->name, "Silver Hand Recruit");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[5]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[6]->card->name, "Silver Hand Recruit");
}

// ----------------------------------------- MINION - ROGUE
// [OG_070] Bladed Cultist - COST:1 [ATK:1/HP:2]
// - Set: Og, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - OG_070 : Bladed Cultist")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladed Cultist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladed Cultist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [OG_109] Darkshire Librarian - COST:2 [ATK:3/HP:2]
// - Set: Og, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Discard a random card.
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - OG_109 : Darkshire Librarian")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 4);
}

// --------------------------------------- MINION - WARLOCK
// [OG_241] Possessed Villager - COST:1 [ATK:1/HP:1]
// - Set: Og, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 1/1 Shadowbeast.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - OG_241 : Possessed Villager")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Possessed Villager"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->name, "Possessed Villager");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->card->name, "Shadowbeast");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [OG_218] Bloodhoof Brave - COST:4 [ATK:2/HP:6]
// - Set: Og, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Has +3 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - OG_218 : Bloodhoof Brave")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodhoof Brave"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}