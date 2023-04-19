// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [DMF_057] Lunar Eclipse - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
//       Your next spell this turn costs (2) less.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DMF_057 : Lunar Eclipse")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lunar Eclipse"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(card2->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 4);
}

// ------------------------------------------ SPELL - DRUID
// [DMF_058] Solar Eclipse - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Your next spell this turn casts twice.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DMF_058 : Solar Eclipse")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Solar Eclipse"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Forest's Aid"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->id, "DAL_256ts");
    CHECK_EQ(curHand[1]->card->id, "DAL_256ts");
}

// ----------------------------------------- MINION - DRUID
// [DMF_059] Fizzy Elemental - COST:9 [ATK:10/HP:10]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DMF_059 : Fizzy Elemental")
{
    // Do nothing
}

// ----------------------------------------- MINION - DRUID
// [DMF_060] Umbral Owl - COST:7 [ATK:4/HP:4]
// - Race: Beast, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>
//       Costs (1) less for each spell
//       you've cast this game.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DMF_060 : Umbral Owl")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Umbral Owl"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));

    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card1->GetCost(), 5);
}

// ----------------------------------------- MINION - DRUID
// [DMF_061] Faire Arborist - COST:3 [ATK:2/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One - </b>Draw a card;
//       or Summon a 2/2 Treant.
//       <b>Corrupt:</b> Do both.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DMF_061 : Faire Arborist")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faire Arborist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faire Arborist"));
    [[maybe_unused]] auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faire Arborist"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curHand.GetCount(), 9);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Treant");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curHand[4]->card->id, "DMF_061");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[4]->card->id, "DMF_061t");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[4]->card->name, "Treant");
}

// ------------------------------------------ SPELL - DRUID
// [DMF_730] Moontouched Amulet - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Give your hero +4 Attack this turn.
//       <b>Corrupt:</b> And gain 6 Armor.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DMF_730 : Moontouched Amulet")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& curHero = *(curPlayer->GetHero());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moontouched Amulet"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero.GetAttack(), 4);
    CHECK_EQ(curHero.GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_730");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_730t");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHero.GetAttack(), 4);
    CHECK_EQ(curHero.GetArmor(), 6);
}

// ------------------------------------------ SPELL - DRUID
// [DMF_732] Cenarion Ward - COST:8
// - Set: DARKMOON_FAIRE, Rarity: Epic
// - Spell School: Nature
// --------------------------------------------------------
// Text: Gain 8 Armor. Summon a random 8-Cost minion.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DMF_732 : Cenarion Ward")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cenarion Ward"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 8);
}

// ----------------------------------------- MINION - DRUID
// [DMF_733] Kiri, Chosen of Elune - COST:4 [ATK:2/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a Solar Eclipse and
//       Lunar Eclipse to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DMF_733 : Kiri, Chosen of Elune")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kiri, Chosen of Elune"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Solar Eclipse");
    CHECK_EQ(curHand[1]->card->name, "Lunar Eclipse");
}

// ----------------------------------------- MINION - DRUID
// [YOP_025] Dreaming Drake - COST:3 [ATK:3/HP:4]
// - Race: Dragon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> Gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - YOP_025 : Dreaming Drake")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreaming Drake"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreaming Drake"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "YOP_025");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "YOP_025t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [YOP_026] Arbor Up - COST:5
// - Set: DARKMOON_FAIRE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon two 2/2 Treants. Give your minions +2/+1.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - YOP_026 : Arbor Up")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arbor Up"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Treant");
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->card->name, "Treant");
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// ---------------------------------------- MINION - HUNTER
// [DMF_083] Dancing Cobra - COST:2 [ATK:1/HP:5]
// - Race: Beast, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Corrupt:</b> Gain <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DMF_083 : Dancing Cobra")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dancing Cobra"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dancing Cobra"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_083");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_083t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasPoisonous(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [DMF_084] Jewel of N'Zoth - COST:8
// - Set: DARKMOON_FAIRE, Rarity: Epic
// --------------------------------------------------------
// Text: Summon three friendly <b>Deathrattle</b> minions
//       that died this game.
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// - REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DMF_084 : Jewel of N'Zoth")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jewel of N'Zoth"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kobold Sandtrooper"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 2);

    // NOTE: dbfID of the card 'Leper Gnome' is 658
    //       dbfID of the card 'Kobold Sandtrooper' is 54259
    const int dbfTotal = curField[0]->card->dbfID + curField[1]->card->dbfID;
    CHECK_EQ(dbfTotal, 54917);
}

// ---------------------------------------- MINION - HUNTER
// [DMF_085] Darkmoon Tonk - COST:7 [ATK:8/HP:5]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Fire four missiles
//       at random enemies that deal 2 damage each.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DMF_085 : Darkmoon Tonk")
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

    const auto& opHero = *(opPlayer->GetHero());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darkmoon Tonk"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opHero.GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(opHero.GetHealth(), 22);
}

// ---------------------------------------- WEAPON - HUNTER
// [DMF_088] Rinling's Rifle - COST:4
// - Set: DARKMOON_FAIRE, Rarity: Legendary
// --------------------------------------------------------
// Text: After your hero attacks,
//       <b>Discover</b> a <b>Secret</b> and cast it.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - DMF_088 : Rinling's Rifle")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rinling's Rifle"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->IsSecret(), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetSecretZone()->GetCount(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [DMF_122] Mystery Winner - COST:1 [ATK:1/HP:1]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a <b>Secret.</b>
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DMF_122 : Mystery Winner")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mystery Winner"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->IsSecret(), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsSecret(), true);
}

// ------------------------------------------ MINION - MAGE
// [DMF_100] Confection Cyclone - COST:2 [ATK:3/HP:2]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add two 1/2 Sugar Elementals
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DMF_100 : Confection Cyclone")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Confection Cyclone"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Sugar Elemental");
    CHECK_EQ(curHand[1]->card->name, "Sugar Elemental");
}

// ------------------------------------------ MINION - MAGE
// [DMF_101] Firework Elemental - COST:5 [ATK:3/HP:5]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to a minion.
//       <b>Corrupt:</b> Deal 12 instead.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DMF_101 : Firework Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Firework Elemental"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Firework Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card5));
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_101");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_101t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[0], card5));
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------ MINION - MAGE
// [DMF_102] Game Master - COST:2 [ATK:2/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: The first <b>Secret</b> you play each turn costs (1).
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DMF_102 : Game Master")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Game Master"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Counterspell"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Barrier"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->GetCost(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [DMF_103] Mask of C'Thun - COST:7
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 10 damage randomly split among all enemies.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DMF_103 : Mask of C'Thun")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mask of C'Thun"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    const int totalHealth =
        opField[0]->GetHealth() + opPlayer->GetHero()->GetHealth();
    CHECK_EQ(totalHealth, 32);
}

// ------------------------------------------- SPELL - MAGE
// [YOP_019] Conjure Mana Biscuit - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Add a Biscuit to your hand that
//       refreshes 2 Mana Crystals.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - YOP_019 : Conjure Mana Biscuit")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

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
        curPlayer, Cards::FindCardByName("Conjure Mana Biscuit"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conjure Mana Biscuit"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[2]->card->name, "Mana Biscuit");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[2]->card->name, "Mana Biscuit");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 5);
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[1]));
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curPlayer->GetRemainingMana(), 3);
}

// ------------------------------------------ MINION - MAGE
// [YOP_020] Glacier Racer - COST:1 [ATK:1/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spellburst</b>: Deal 3 damage
//       to all <b>Frozen</b> enemies.
// --------------------------------------------------------
// GameTag:
// - SPELLBURST = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - YOP_020 : Glacier Racer")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Glacier Racer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 6);
}

// --------------------------------------- MINION - PALADIN
// [DMF_064] Carousel Gryphon - COST:5 [ATK:5/HP:5]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Corrupt:</b> Gain +3/+3 and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_064 : Carousel Gryphon")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carousel Gryphon"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carousel Gryphon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[0]->HasTaunt(), false);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_064");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_064t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
}

// --------------------------------------- MINION - PALADIN
// [DMF_194] Redscale Dragontamer - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a Dragon.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_194 : Redscale Dragontamer")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Shotbot");
        config.player1Deck[i + 2] = Cards::FindCardByName("Murmy");
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
        curPlayer, Cards::FindCardByName("Redscale Dragontamer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(card1->isDestroyed, true);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Faerie Dragon");
}

// --------------------------------------- MINION - PALADIN
// [DMF_235] Balloon Merchant - COST:4 [ATK:3/HP:5]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your Silver Hand Recruits
//       +1 Attack and <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_235 : Balloon Merchant")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Balloon Merchant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->HasDivineShield(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
}

// --------------------------------------- MINION - PALADIN
// [DMF_237] Carnival Barker - COST:3 [ATK:3/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you summon a 1-Health minion, give it +1/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_237 : Carnival Barker")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Carnival Barker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shotbot"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
}

// --------------------------------------- WEAPON - PALADIN
// [DMF_238] Hammer of the Naaru - COST:6
// - Set: DARKMOON_FAIRE, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 6/6 Holy Elemental
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - DMF_238 : Hammer of the Naaru")
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
        curPlayer, Cards::FindCardByName("Hammer of the Naaru"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Holy Elemental");
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - PALADIN
// [DMF_241] High Exarch Yrel - COST:8 [ATK:7/HP:5]
// - Set: DARKMOON_FAIRE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no Neutral cards,
//       gain <b>Rush</b>, <b>Lifesteal</b>, <b>Taunt</b>,
//       and <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// - LIFESTEAL = 1
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DMF_241 : High Exarch Yrel")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (std::size_t i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Leper Gnome");
        config.player2Deck[i] = Cards::FindCardByName("Leper Gnome");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("High Exarch Yrel"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("High Exarch Yrel"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), false);
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[0]->HasTaunt(), false);
    CHECK_EQ(curField[0]->HasDivineShield(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[1]->HasLifesteal(), true);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [DMF_244] Day at the Faire - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Summon 3 Silver Hand Recruits.
//       <b>Corrupt:</b> Summon 5.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DMF_244 : Day at the Faire")
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Day at the Faire"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Day at the Faire"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Explosion"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_244");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_244t");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[4]->card->name, "Silver Hand Recruit");
}

// --------------------------------------- MINION - PALADIN
// [YOP_010] Imprisoned Celestial - COST:3 [ATK:4/HP:5]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns.
//       <b>Spellburst</b>: Give your minions
//       <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - SPELLBURST = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - YOP_010 : Imprisoned Celestial")
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
        curPlayer, Cards::FindCardByName("Imprisoned Celestial"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 0);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasSpellburst(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 1);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->HasSpellburst(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(curField[0]->HasSpellburst(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->HasSpellburst(), false);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
}

// --------------------------------------- WEAPON - PALADIN
// [YOP_011] Libram of Judgment - COST:7
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Corrupt:</b> Gain <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - YOP_011 : Libram of Judgment")
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

    auto& curHero = *(curPlayer->GetHero());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Libram of Judgment"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Libram of Judgment"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shotbot"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHero.HasWeapon(), true);
    CHECK_EQ(curHero.weapon->GetAttack(), 5);
    CHECK_EQ(curHero.weapon->GetDurability(), 3);
    CHECK_EQ(curHero.HasLifesteal(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand[0]->card->id, "YOP_011");

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand[0]->card->id, "YOP_011t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Weapon(curHand[0]));
    CHECK_EQ(curHero.HasWeapon(), true);
    CHECK_EQ(curHero.weapon->GetAttack(), 5);
    CHECK_EQ(curHero.weapon->GetDurability(), 3);
    CHECK_EQ(curHero.HasLifesteal(), true);
}

// ---------------------------------------- MINION - PRIEST
// [DMF_184] Fairground Fool - COST:3 [ATK:4/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> Gain +4 Health.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DMF_184 : Fairground Fool")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fairground Fool"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fairground Fool"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_184");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_184t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 7);
}

// ----------------------------------------- SPELL - PRIEST
// [DMF_186] Auspicious Spirits - COST:4
// - Set: DARKMOON_FAIRE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Summon a random 4-Cost minion.
//       <b>Corrupt:</b> Summon a 7-Cost minion instead.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DMF_186 : Auspicious Spirits")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Auspicious Spirits"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Auspicious Spirits"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Plague of Death"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->card->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_186");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_186a");

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curField[0]->card->GetCost(), 7);
}

// ----------------------------------------- MINION - ROGUE
// [DMF_514] Ticket Master - COST:3 [ATK:4/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle 3 Tickets into your deck.
//       When drawn, summon a 3/3 Plush Bear.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DMF_514 : Ticket Master")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ticket Master"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Plush Bear");
    CHECK_EQ(curField[2]->card->name, "Plush Bear");
    CHECK_EQ(curField[3]->card->name, "Plush Bear");
}

// ------------------------------------------ SPELL - ROGUE
// [DMF_515] Swindle - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Draw a spell.
//       <b>Combo:</b> And a minion.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DMF_515 : Swindle")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Shiv");
        config.player1Deck[i + 2] = Cards::FindCardByName("Assassin's Blade");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swindle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swindle"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[6]->card->GetCardType(), CardType::MINION);
}

// ----------------------------------------- MINION - ROGUE
// [DMF_517] Sweet Tooth - COST:2 [ATK:3/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Corrupt:</b> Gain +2 Attack and <b>Stealth</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DMF_517 : Sweet Tooth")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sweet Tooth"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sweet Tooth"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasStealth(), false);
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_517");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_517a");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasStealth(), true);
    CHECK_EQ(curField[1]->GetAttack(), 5);
}

// ----------------------------------------- MINION - ROGUE
// [YOP_016] Sparkjoy Cheat - COST:3 [ATK:3/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a <b>Secret</b>,
//       cast it and draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - YOP_016 : Sparkjoy Cheat")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sparkjoy Cheat"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sparkjoy Cheat"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ambush"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(curSecret[0]->card->name, "Ambush");

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curSecret.GetCount(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_700] Revolve - COST:1
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Transform all minions into random ones with the same Cost.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_700 : Revolve")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Revolve"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cagematch Custodian"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->card->GetCost(), 3);
    CHECK_EQ(curField[1]->card->GetCost(), 0);
    CHECK_EQ(curField[2]->card->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[0]->card->GetCost(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->card->GetCost(), 3);
    CHECK_EQ(curField[1]->card->GetCost(), 0);
    CHECK_EQ(curField[2]->card->GetCost(), 2);
    CHECK_EQ(opField[0]->card->GetCost(), 9);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_701] Dunk Tank - COST:4
// - Set: DARKMOON_FAIRE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 4 damage.
//       <b>Corrupt:</b> Then deal 2 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_701 : Dunk Tank")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dunk Tank"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dunk Tank"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deep Freeze"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_701");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_701t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card5));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_702] Stormstrike - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
//       Give your hero +3 Attack this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_702 : Stormstrike")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormstrike"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earth Elemental"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ---------------------------------------- MINION - SHAMAN
// [DMF_703] Pit Master - COST:3 [ATK:1/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 3/2 Duelist.
//       <b>Corrupt:</b> Summon two.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DMF_703 : Pit Master")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Master"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Master"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Pit Master");
    CHECK_EQ(curField[1]->card->name, "Duelist");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_703");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_703t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[2]->card->name, "Duelist");
    CHECK_EQ(curField[3]->card->name, "Pit Master");
    CHECK_EQ(curField[4]->card->name, "Duelist");
}

// ---------------------------------------- MINION - SHAMAN
// [DMF_704] Cagematch Custodian - COST:2 [ATK:2/HP:2]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DMF_704 : Cagematch Custodian")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Stormforged Axe");
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
        curPlayer, Cards::FindCardByName("Cagematch Custodian"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Stormforged Axe");
}

// ---------------------------------------- WEAPON - SHAMAN
// [DMF_705] Whack-A-Gnoll Hammer - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks,
//       give a random friendly minion +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - DMF_705 : Whack-A-Gnoll Hammer")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Whack-A-Gnoll Hammer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ----------------------------------------- SPELL - SHAMAN
// [DMF_706] Deathmatch Pavilion - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Epic
// --------------------------------------------------------
// Text: Summon a 3/2 Duelist.
//       If your hero attacked this turn, summon another.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DMF_706 : Deathmatch Pavilion")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deathmatch Pavilion"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deathmatch Pavilion"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stormforged Axe"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Pavilion Duelist");

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Pavilion Duelist");
    CHECK_EQ(curField[2]->card->name, "Pavilion Duelist");
}

// ---------------------------------------- MINION - SHAMAN
// [YOP_022] Mistrunner - COST:5 [ATK:4/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +3/+3.
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - OVERLOAD = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - YOP_022 : Mistrunner")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mistrunner"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mistrunner"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 2);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
}

// ----------------------------------------- SPELL - SHAMAN
// [YOP_023] Landslide - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions.
//       If you're <b>Overloaded</b>, deal 1 damage again.
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - YOP_023 : Landslide")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Landslide"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Landslide"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mistrunner"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Onyxia"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card4, card3));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [DMF_110] Fire Breather - COST:4 [ATK:4/HP:3]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 2 damage to all minions except Demons.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_110 : Fire Breather")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Breather"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Servant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Evasive Feywing"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Midway Maniac"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Southsea Captain"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Crabrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 3);
    CHECK_EQ(opField[2]->GetHealth(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - WARLOCK
// [DMF_111] Man'ari Mosher - COST:3 [ATK:3/HP:4]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly Demon +3 Attack
//       and <b>Lifesteal</b> this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 15
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_111 : Man'ari Mosher")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Man'ari Mosher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Midway Maniac"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasLifesteal(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasLifesteal(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->HasLifesteal(), true);

    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
    CHECK_EQ(opField[0]->GetHealth(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->HasLifesteal(), false);
}

// --------------------------------------- MINION - WARLOCK
// [DMF_114] Midway Maniac - COST:2 [ATK:1/HP:5]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_114 : Midway Maniac")
{
    // Do nothing
}

// --------------------------------------- MINION - WARLOCK
// [DMF_115] Revenant Rascal - COST:3 [ATK:3/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a Mana Crystal for both players.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_115 : Revenant Rascal")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Revenant Rascal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Revenant Rascal"));

    CHECK_EQ(curPlayer->GetTotalMana(), 10);
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(opPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(opPlayer->GetTotalMana(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(opPlayer->GetTotalMana(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetTotalMana(), 9);
    CHECK_EQ(opPlayer->GetRemainingMana(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
}

// --------------------------------------- MINION - WARLOCK
// [DMF_533] Ring Matron - COST:6 [ATK:6/HP:4]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Summon two 3/2 Imps.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DMF_533 : Ring Matron")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ring Matron"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Fiery Imp");
    CHECK_EQ(curField[1]->card->name, "Fiery Imp");
}

// ---------------------------------------- SPELL - WARLOCK
// [YOP_033] Backfire - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: Draw 3 cards. Deal 3 damage to your hero.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - YOP_033 : Backfire")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backfire"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curHand.GetCount(), 7);
}

// --------------------------------------- MINION - WARRIOR
// [DMF_521] Sword Eater - COST:4 [ATK:2/HP:5]
// - Race: Pirate, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Equip a 3/2 Sword.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_521 : Sword Eater")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sword Eater"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// ---------------------------------------- SPELL - WARRIOR
// [DMF_522] Minefield - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 5 damage randomly split among all minions.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DMF_522 : Minefield")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Minefield"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    const int totalHealth = curField[0]->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 9);
}

// --------------------------------------- MINION - WARRIOR
// [DMF_523] Bumper Car - COST:2 [ATK:1/HP:3]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Deathrattle:</b> Add two 1/1 Riders
//       with <b>Rush</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_523 : Bumper Car")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bumper Car"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Darkmoon Rider");
    CHECK_EQ(curField[1]->card->name, "Darkmoon Rider");
}

// ---------------------------------------- SPELL - WARRIOR
// [DMF_526] Stage Dive - COST:1
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a <b>Rush</b> minion.
//       <b>Corrupt:</b> Give it +2/+1.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DMF_526 : Stage Dive")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Shotbot");
        config.player1Deck[i + 2] = Cards::FindCardByName("Burly Shovelfist");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stage Dive"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stage Dive"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heroic Strike"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[7]->card->name, "Burly Shovelfist");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[7])->GetAttack(), 9);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[7])->GetHealth(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand[4]->card->id, "DMF_526");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[4]->card->id, "DMF_526a");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Burly Shovelfist");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetAttack(), 11);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->GetHealth(), 10);
}

// --------------------------------------- MINION - WARRIOR
// [DMF_531] Stage Hand - COST:2 [ATK:3/HP:2]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random minion in your hand +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_531 : Stage Hand")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stage Hand"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    const int totalAttack = dynamic_cast<Minion*>(card2)->GetAttack() +
                            dynamic_cast<Minion*>(card3)->GetAttack();
    const int totalHealth = dynamic_cast<Minion*>(card2)->GetHealth() +
                            dynamic_cast<Minion*>(card3)->GetHealth();
    CHECK_EQ(totalAttack, 7);
    CHECK_EQ(totalHealth, 4);
}

// --------------------------------------- MINION - WARRIOR
// [YOP_014] Ironclad - COST:3 [ATK:2/HP:4]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your hero has Armor, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - YOP_014 : Ironclad")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironclad"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironclad"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [DMF_219] Relentless Pursuit - COST:3
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +4 Attack and <b>Immune</b> this turn.
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - DMF_219 : Relentless Pursuit")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& curHero = *(curPlayer->GetHero());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Relentless Pursuit"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero.GetAttack(), 4);
    CHECK_EQ(curHero.IsImmune(), true);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curHero.GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero.GetAttack(), 0);
    CHECK_EQ(curHero.IsImmune(), false);
}

// ----------------------------------- MINION - DEMONHUNTER
// [DMF_223] Renowned Performer - COST:4 [ATK:3/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Deathrattle:</b> Summon two 1/1 Assistants
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - DMF_223 : Renowned Performer")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Renowned Performer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Performer's Assistant");
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Performer's Assistant");
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [DMF_227] Dreadlord's Bite - COST:3 [ATK:3/HP:0]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - DMF_227 : Dreadlord's Bite")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dreadlord's Bite"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ----------------------------------- MINION - DEMONHUNTER
// [DMF_247] Insatiable Felhound - COST:3 [ATK:2/HP:5]
// - Race: Demon, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> Gain +1/+1 and <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - DMF_247 : Insatiable Felhound")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Insatiable Felhound"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Insatiable Felhound"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "DMF_247");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_247t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->HasLifesteal(), true);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_044] Rock Rager - COST:2 [ATK:5/HP:1]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_044 : Rock Rager")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_065] Banana Vendor - COST:3 [ATK:2/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add 2 Bananas to each player's hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_065 : Banana Vendor")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Banana Vendor"));

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Bananas");
    CHECK_EQ(curHand[1]->card->name, "Bananas");
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[1]->card->name, "Bananas");
    CHECK_EQ(opHand[2]->card->name, "Bananas");
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_066] Knife Vendor - COST:4 [ATK:3/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage to each hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_066 : Knife Vendor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Knife Vendor"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_067] Prize Vendor - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Both players draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_067 : Prize Vendor")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Prize Vendor"));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_073] Darkmoon Dirigible - COST:3 [ATK:3/HP:2]
// - Race: Mechanical, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Corrupt:</b> Gain <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_073 : Darkmoon Dirigible")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkmoon Dirigible"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkmoon Dirigible"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_073");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_073t");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_078] Strongman - COST:7 [ATK:6/HP:6]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Corrupt:</b> This costs (0).
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_078 : Strongman")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Strongman"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deep Freeze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_078");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_078t");
    CHECK_EQ(curHand[0]->GetCost(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_080] Fleethoof Pearltusk - COST:5 [ATK:4/HP:4]
// - Race: Beast, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Corrupt:</b> Gain +4/+4.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_080 : Fleethoof Pearltusk")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fleethoof Pearltusk"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fleethoof Pearltusk"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_080");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_080t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetAttack(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_091] Wriggling Horror - COST:2 [ATK:2/HP:1]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_091 : Wriggling Horror")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wriggling Horror"));
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
// [DMF_174] Circus Medic - COST:4 [ATK:3/HP:4]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 4 Health.
//       <b>Corrupt:</b> Deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_174 : Circus Medic")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Medic"));
    [[maybe_unused]] auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Medic"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    opHero->SetDamage(15);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 19);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curHand[0]->card->id, "DMF_174");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "DMF_174t");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opHero->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::MinionTarget(curHand[0], opHero));
    CHECK_EQ(opHero->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_189] Costumed Entertainer - COST:2 [ATK:1/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random minion in your hand +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DMF_189 : Costumed Entertainer")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Costumed Entertainer"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    const int totalAttack = dynamic_cast<Minion*>(card2)->GetAttack() +
                            dynamic_cast<Minion*>(card3)->GetAttack();
    const int totalHealth = dynamic_cast<Minion*>(card2)->GetHealth() +
                            dynamic_cast<Minion*>(card3)->GetHealth();
    CHECK_EQ(totalAttack, 8);
    CHECK_EQ(totalHealth, 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_190] Fantastic Firebird - COST:4 [ATK:3/HP:5]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_190 : Fantastic Firebird")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_191] Showstopper - COST:2 [ATK:3/HP:2]
// - Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> <b>Silence</b> all minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_191 : Showstopper")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Showstopper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Power Infusion"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[1]->GetSpellPower(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card7, card5));
    CHECK_EQ(opField[0]->GetAttack(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(opField[1]->GetSpellPower(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetSpellPower(), 0);
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DMF_532] Circus Amalgam - COST:4 [ATK:4/HP:5]
// - Race: All, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <i>This has all minion types.</i>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DMF_532 : Circus Amalgam")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Circus Amalgam"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fresh Scent"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);
}

// ---------------------------------------- SPELL - NEUTRAL
// [YOP_015] Nitroboost Poison - COST:2
// - Set: DARKMOON_FAIRE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a minion +2 Attack.
//       <b>Corrupt:</b> And your weapon.
// --------------------------------------------------------
// GameTag:
// - CORRUPT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Spell] - YOP_015 : Nitroboost Poison")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHero = *(curPlayer->GetHero());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nitroboost Poison"));
    [[maybe_unused]] auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nitroboost Poison"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fan of Knives"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sinister Strike"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHero.weapon->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card5));
    CHECK_EQ(curHero.weapon->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curHand[0]->card->id, "YOP_015");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->id, "YOP_015t");

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card5));
    CHECK_EQ(curHero.weapon->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [YOP_021] Imprisoned Phoenix - COST:2 [ATK:2/HP:3]
// - Race: Elemental, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns.
//       <b>Spell Damage +2</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOP_021 : Imprisoned Phoenix")
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
        curPlayer, Cards::FindCardByName("Imprisoned Phoenix"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 0);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 1);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 16);
}

// --------------------------------------- MINION - NEUTRAL
// [YOP_031] Crabrider - COST:2 [ATK:1/HP:4]
// - Race: Murloc, Set: DARKMOON_FAIRE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOP_031 : Crabrider")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [YOP_032] Armor Vendor - COST:1 [ATK:1/HP:3]
// - Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give 4 Armor to each hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOP_032 : Armor Vendor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Armor Vendor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [YOP_034] Runaway Blackwing - COST:9 [ATK:9/HP:9]
// - Race: Dragon, Set: DARKMOON_FAIRE, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 9 damage to a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOP_034 : Runaway Blackwing")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Runaway Blackwing"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[0]->GetHealth(), 3);
}