// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [BT_127] Imprisoned Satyr - COST:3 [ATK:3/HP:3]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. When this awakens,
//       reduce the Cost of a random minion in your hand by (5).
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BT_127 : Imprisoned Satyr")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Imprisoned Satyr"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetCost(), 4);
}

// ------------------------------------------ SPELL - DRUID
// [BT_130] Overgrowth - COST:4
// - Faction: Neutral, Set: Core, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Gain two empty Mana Crystals.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BT_130 : Overgrowth")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Overgrowth"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Overgrowth"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);
}

// ----------------------------------------- MINION - DRUID
// [BT_131] Ysiel Windsinger - COST:9 [ATK:5/HP:5]
// - Set: BLACK_TEMPLE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your spells cost (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BT_131 : Ysiel Windsinger")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ysiel Windsinger"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(card2->GetCost(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
}

// ------------------------------------------ SPELL - DRUID
// [BT_132] Ironbark - COST:2
// - Set: BLACK_TEMPLE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a minion +1/+3 and <b>Taunt</b>.
//       Costs (0) if you have at least 7 Mana Crystals.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BT_132 : Ironbark")
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
    curPlayer->SetTotalMana(6);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironbark"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card1->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 12);
    CHECK_EQ(opField[0]->HasTaunt(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
    CHECK_EQ(opField[0]->GetAttack(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 15);
    CHECK_EQ(opField[0]->HasTaunt(), true);
}

// ----------------------------------------- MINION - DRUID
// [BT_133] Marsh Hydra - COST:7 [ATK:7/HP:7]
// - Race: Beast, Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b> After this attacks,
//       add a random 8-Cost minion to your hand.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BT_133 : Marsh Hydra")
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Marsh Hydra"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetCost(), 8);
}

// ------------------------------------------ SPELL - DRUID
// [BT_134] Bogbeam - COST:3
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
//       Costs (0) if you have at least 7 Mana Crystals.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BT_134 : Bogbeam")
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
    curPlayer->SetTotalMana(6);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bogbeam"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

// ----------------------------------------- MINION - DRUID
// [BT_136] Archspore Msshi'fn - COST:3 [ATK:3/HP:4]
// - Set: BLACK_TEMPLE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Shuffle
//       'Msshi'fn Prime' into your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BT_136 : Archspore Msshi'fn")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Archspore Msshi'fn"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Archspore Msshi'fn"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card5 = curHand[0];

    game.Process(curPlayer, PlayCardTask::Minion(card5, 1));
    CHECK_EQ(curField[0]->card->name, "Msshi'fn Prime");
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(curField[1]->card->name, "Fungal Guardian");
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 9);
    CHECK_EQ(curField[1]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card6 = curHand[0];

    game.Process(curPlayer, PlayCardTask::Minion(card6, 2));
    CHECK_EQ(curField[2]->card->name, "Msshi'fn Prime");
    CHECK_EQ(curField[2]->GetAttack(), 9);
    CHECK_EQ(curField[2]->GetHealth(), 9);
    CHECK_EQ(curField[3]->card->name, "Fungal Bruiser");
    CHECK_EQ(curField[3]->HasRush(), true);
    CHECK_EQ(curField[3]->GetAttack(), 9);
    CHECK_EQ(curField[3]->GetHealth(), 9);
}

// ---------------------------------------- MINION - HUNTER
// [BT_202] Helboar - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give a random Beast in your hand +1/+1.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - BT_202 : Helboar")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Helboar"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 1);
}

// ----------------------------------------- SPELL - HUNTER
// [BT_205] Scrap Shot - COST:4
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 3 damage. Give a random Beast in your hand +3/+3.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BT_205 : Scrap Shot")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scrap Shot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 1);
}

// ----------------------------------------- SPELL - HUNTER
// [BT_213] Scavenger's Ingenuity - COST:2
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: Draw a Beast. Give it +3/+3.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BT_213 : Scavenger's Ingenuity")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 1] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 2] = Cards::FindCardByName("Murloc Raider");
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
        curPlayer, Cards::FindCardByName("Scavenger's Ingenuity"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::BEAST);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 5);
}

// ------------------------------------------- SPELL - MAGE
// [BT_002] Incanter's Flow - COST:4
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Reduce the Cost of spells in your deck by (1).
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BT_002 : Incanter's Flow")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Blizzard");
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Incanter's Flow"));

    CHECK_EQ(curHand[0]->GetCost(), 6);
    CHECK_EQ(curHand[1]->GetCost(), 6);
    CHECK_EQ(curHand[2]->GetCost(), 6);
    CHECK_EQ(curHand[3]->GetCost(), 6);
    for (auto& card : curDeck.GetAll())
    {
        CHECK_EQ(card->GetCost(), 6);
    }

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand[0]->GetCost(), 6);
    CHECK_EQ(curHand[1]->GetCost(), 6);
    CHECK_EQ(curHand[2]->GetCost(), 6);
    CHECK_EQ(curHand[3]->GetCost(), 6);
    for (auto& card : curDeck.GetAll())
    {
        CHECK_EQ(card->GetCost(), 5);
    }
}

// ------------------------------------------- SPELL - MAGE
// [BT_003] Netherwind Portal - COST:3
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent casts a spell,
//       summon a random 4-Cost minion.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BT_003 : Netherwind Portal")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curSecret = *(curPlayer->GetSecretZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Onyxia"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Netherwind Portal"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.IsFull(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(card2->GetGameTag(GameTag::REVEALED), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(card2->GetGameTag(GameTag::REVEALED), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, curField[6]));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(card2->GetGameTag(GameTag::REVEALED), 1);
    CHECK_EQ(curField.IsFull(), true);
    CHECK_EQ(curField[6]->card->GetCost(), 4);
}

// ------------------------------------------ MINION - MAGE
// [BT_004] Imprisoned Observer - COST:3 [ATK:4/HP:5]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns.
//       When this awakens, deal 2 damage to all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - BT_004 : Imprisoned Observer")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Observer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 0);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 1);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// ------------------------------------------ MINION - MAGE
// [BT_014] Starscryer - COST:2 [ATK:3/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a spell.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - BT_014 : Starscryer")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 10; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wolfrider");
        config.player1Deck[i + 10] = Cards::FindCardByName("Starscryer");
        config.player1Deck[i + 20] = Cards::FindCardByName("Pyroblast");
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
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starscryer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Pyroblast");
}

// ------------------------------------------- SPELL - MAGE
// [BT_072] Deep Freeze - COST:8
// - Set: BLACK_TEMPLE, Rarity: Rare
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> an enemy. Summon two 3/6 Water Elementals.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BT_072 : Deep Freeze")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Deep Freeze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->card->name, "Water Elemental");
    CHECK_EQ(opField[1]->card->name, "Water Elemental");
}

// ------------------------------------------- SPELL - MAGE
// [BT_291] Apexis Blast - COST:5
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 5 damage. If your deck has no minions,
//       summon a random 5-Cost minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BT_291 : Apexis Blast")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wolfrider");
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
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Apexis Blast"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Apexis Blast"));

    opHero->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, opHero));
    CHECK_EQ(opHero->GetHealth(), 25);
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opHero->SetDamage(0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 25);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 5);
}

// --------------------------------------- MINION - PALADIN
// [BT_009] Imprisoned Sungill - COST:1 [ATK:2/HP:1]
// - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. When this awakens,
//       summon two 1/1 Murlocs.
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BT_009 : Imprisoned Sungill")
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
        curPlayer, Cards::FindCardByName("Imprisoned Sungill"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Sungill Streamrunner");
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[1]->IsUntouchable(), false);
    CHECK_EQ(curField[1]->CanAttack(), false);
    CHECK_EQ(curField[2]->card->name, "Sungill Streamrunner");
}

// ---------------------------------------- SPELL - PALADIN
// [BT_011] Libram of Justice - COST:5
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Equip a 1/4 weapon.
//       Change the Health of all enemy minions to 1.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BT_011 : Libram of Justice")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Libram of Justice"));

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- WEAPON - PALADIN
// [BT_018] Underlight Angling Rod - COST:3
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: After your Hero attacks,
//       add a random Murloc to your hand.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - BT_018 : Underlight Angling Rod")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Underlight Angling Rod"));

    auto& curHand = *(curPlayer->GetHandZone());

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::MURLOC);
}

// ---------------------------------------- SPELL - PALADIN
// [BT_024] Libram of Hope - COST:9
// - Set: BLACK_TEMPLE, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 8 Health. Summon an 8/8 Guardian
//       with <b>Taunt</b> and <b>Divine Shield</b>.
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BT_024 : Libram of Hope")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Libram of Hope"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Ancient Guardian");
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// ----------------------------------------- SPELL - PRIEST
// [BT_252] Renew - COST:1
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 3 Health. <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Preist : Spell] - BT_252 : Renew")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    curPlayer->GetHero()->SetDamage(5);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Renew"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Injured Blademaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::PRIEST), true);
    }
}

// ----------------------------------------- SPELL - PRIEST
// [BT_253] Psyche Split - COST:5
// - Set: BLACK_TEMPLE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Give a minion +1/+2. Summon a copy of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Preist : Spell] - BT_253 : Psyche Split")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Psyche Split"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ---------------------------------------- MINION - PRIEST
// [BT_256] Dragonmaw Overseer - COST:3 [ATK:2/HP:2]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another friendly minion +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Preist : Minion] - BT_256 : Dragonmaw Overseer")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonmaw Overseer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - PRIEST
// [BT_257] Apotheosis - COST:3
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a minion +2/+3 and <b>Lifesteal</b>.
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Preist : Spell] - BT_257 : Apotheosis")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Apotheosis"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->HasLifesteal(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ---------------------------------------- MINION - PRIEST
// [BT_258] Imprisoned Homunculus - COST:1 [ATK:2/HP:5]
// - Race: Demon, Set: Black Temple, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BT_258 : Imprisoned Homunculus")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Homunculus"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - PRIEST
// [BT_262] Dragonmaw Sentinel - COST:2 [ATK:1/HP:4]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       gain +1 Attack and <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BT_262 : Dragonmaw Sentinel")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonmaw Sentinel"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonmaw Sentinel"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->HasLifesteal(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->HasLifesteal(), false);
}

// ---------------------------------------- MINION - PRIEST
// [BT_341] Skeletal Dragon - COST:7 [ATK:4/HP:9]
// - Race: Dragon, Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b> At the end of your turn,
//       add a Dragon to your hand.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BT_341 : Skeletal Dragon")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skeletal Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::DRAGON);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[1]->card->GetRace(), Race::DRAGON);
}

// ---------------------------------------- SPELL - PALADIN
// [BT_292] Hand of A'dal - COST:2
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a minion +2/+1. Draw a card.
// --------------------------------------------------------
TEST_CASE("[Paladin : SPELL] - BT_292 : Hand of A'dal")
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hand of A'dal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ------------------------------------------ SPELL - ROGUE
// [BT_042] Bamboozle - COST:2
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When one of your minions is attacked,
//       transform it into a random one that costs (3) more.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BT_042 : Bamboozle")
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bamboozle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->card->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField[0]->card->GetCost(), 7);
}

// ----------------------------------------- MINION - ROGUE
// [BT_701] Spymistress - COST:1 [ATK:3/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BT_701 : Spymistress")
{
    // Do nothing
}

// ----------------------------------------- MINION - ROGUE
// [BT_703] Cursed Vagrant - COST:7 [ATK:7/HP:5]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 7/5 Shadow with <b>Stealth</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BT_703 : Cursed Vagrant")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cursed Vagrant"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Cursed Vagrant");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Cursed Shadow");
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[0]->HasStealth(), true);
}

// ------------------------------------------ SPELL - ROGUE
// [BT_707] Ambush - COST:2
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       summon a 2/3 Ambusher with <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BT_707 : Ambush")
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ambush"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Grommash Hellscream"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Broken Ambusher");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasPoisonous(), true);
}

// ------------------------------------------ SPELL - ROGUE
// [BT_709] Dirty Tricks - COST:2
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent casts a spell,
//       draw 2 cards.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BT_709 : Dirty Tricks")
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dirty Tricks"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 6);
}

// ----------------------------------------- MINION - ROGUE
// [BT_710] Greyheart Sage - COST:3 [ATK:3/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control
//       a <b>Stealthed</b> minion, draw 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BT_710 : Greyheart Sage")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Greyheart Sage"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Greyheart Sage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spymistress"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flare"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasStealth(), true);
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField[0]->HasStealth(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 7);
}

// ----------------------------------------- MINION - ROGUE
// [BT_711] Blackjack Stunner - COST:1 [ATK:1/HP:2]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       return a minion to its owner's hand. It costs (2) more.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BT_711 : Blackjack Stunner")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blackjack Stunner"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dirty Tricks"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetCost(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opHand[1]->GetCost(), 5);
}

// ----------------------------------------- SPELL - SHAMAN
// [BT_100] Serpentshrine Portal - COST:3
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 3 damage. Summon a random 3-Cost minion.
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - BT_100 : Serpentshrine Portal")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Serpentshrine Portal"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 3);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
}

// ---------------------------------------- WEAPON - SHAMAN
// [BT_102] Boggspine Knuckles - COST:5 [ATK:4/HP:0]
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: After your hero attacks, transform your minions
//       into random ones that cost (1) more.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - BT_102 : Boggspine Knuckles")
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
        curPlayer, Cards::FindCardByName("Boggspine Knuckles"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->card->GetCost(), 9);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->card->GetCost(), 10);
}

// ---------------------------------------- MINION - SHAMAN
// [BT_106] Bogstrok Clacker - COST:3 [ATK:3/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform adjacent minions
//       into random minions that cost (1) more.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BT_106 : Bogstrok Clacker")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bogstrok Clacker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField[0]->card->GetCost(), 4);
    CHECK_EQ(curField[2]->card->GetCost(), 5);
}

// ----------------------------------------- SPELL - SHAMAN
// [BT_110] Torrent - COST:4
// - Set: BLACK_TEMPLE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 8 damage to a minion.
//       Costs (3) less if you cast a spell last turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - BT_110 : Torrent")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Torrent"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card2->GetCost(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(card2->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 1);
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// ----------------------------------------- SPELL - SHAMAN
// [BT_113] Totemic Reflection - COST:3
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +2/+2.
//       If it's a Totem, summon a copy of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - BT_113 : Totemic Reflection")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Totemic Reflection"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Totemic Reflection"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mana Tide Totem"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dust Devil"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Mana Tide Totem");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField[0]->GetAttack(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[1]->GetAttack(), 5);
    CHECK_EQ(opField[1]->GetHealth(), 3);
}

// ---------------------------------------- MINION - SHAMAN
// [BT_114] Shattered Rumbler - COST:5 [ATK:5/HP:6]
// - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you cast a spell last turn,
//       deal 2 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BT_114 : Shattered Rumbler")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shattered Rumbler"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shattered Rumbler"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card4));
    CHECK_EQ(opField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// ---------------------------------------- MINION - SHAMAN
// [BT_115] Marshspawn - COST:3 [ATK:3/HP:4]
// - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you cast a spell last turn,
//       <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BT_115 : Marshspawn")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Marshspawn"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Marshspawn"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(!curPlayer->choice);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::SHAMAN), true);
    }
}

// ---------------------------------------- SPELL - WARLOCK
// [BT_199] Unstable Felbolt - COST:1
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 3 damage to an enemy minion
//       and a random friendly one.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BT_199 : Unstable Felbolt")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DEMONHUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Unstable Felbolt"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Doomsayer"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - WARLOCK
// [BT_301] Nightshade Matron - COST:4 [ATK:5/HP:5]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Battlecry:</b> Discard your highest Cost card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BT_301 : Nightshade Matron")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nightshade Matron"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Wolfrider");
}

// ---------------------------------------- SPELL - WARLOCK
// [BT_302] The Dark Portal - COST:4
// - Set: BLACK_TEMPLE, Rarity: Rare
// - Spell School: Fel
// --------------------------------------------------------
// Text: Draw a minion. If you have at least 8 cards in hand,
//       it costs (5) less.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BT_302 : The Dark Portal")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Dark Portal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Dark Portal"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(curHand.GetCount(), 8);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[7]->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[6]->GetCost(), 9);
}

// --------------------------------------- MINION - WARLOCK
// [BT_304] Enhanced Dreadlord - COST:8 [ATK:5/HP:7]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a 5/5
//       Dreadlord with <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BT_304 : Enhanced Dreadlord")
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
        curPlayer, Cards::FindCardByName("Enhanced Dreadlord"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Enhanced Dreadlord");
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Desperate Dreadlord");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[0]->HasLifesteal(), true);
}

// --------------------------------------- MINION - WARLOCK
// [BT_305] Imprisoned Scrap Imp - COST:2 [ATK:3/HP:3]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. When this awakens,
//       give all minions in your hand +2/+2.
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BT_305 : Imprisoned Scrap Imp")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Imprisoned Scrap Imp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 14);
}

// ---------------------------------------- SPELL - WARRIOR
// [BT_117] Bladestorm - COST:3
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 1 damage to all minions. Repeat until one dies.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BT_117 : Bladestorm")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladestorm"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Target Dummy"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dire Mole"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Dire Mole");
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [BT_120] Warmaul Challenger - COST:3 [ATK:1/HP:10]
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose an enemy minion.
//       Battle it to the death!
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BT_120 : Warmaul Challenger")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dire Mole"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Warmaul Challenger"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARRIOR
// [BT_121] Imprisoned Gan'arg - COST:1 [ATK:2/HP:2]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns.
//       When this awakens, equip a 3/2 Axe.
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BT_121 : Imprisoned Gan'arg")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Gan'arg"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// --------------------------------------- MINION - WARRIOR
// [BT_123] Kargath Bladefist - COST:4 [ATK:4/HP:4]
// - Set: BLACK_TEMPLE, Rarity: LEGENDARY
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Deathrattle:</b> Shuffle
//       'Kargath Prime' into your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BT_123 : Kargath Bladefist")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;
    config.doShuffle = false;

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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kargath Bladefist"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Reckless Rocketeer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    // Player1 summon 'Kargath Bladefist'
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // Player2 summon minions and attack player1's 'Kargath Bladefist'
    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card2, card1));

    // Player1's 'Kargath Prime' move to top of the deck
    auto curCards = curDeck.GetAll();
    auto iter = std::find_if(
        curCards.begin(), curCards.end(),
        [](const Playable* dc) { return (dc->card->name) == "Kargath Prime"; });
    CHECK(iter != curCards.end());
    const auto card5 = *iter;
    curDeck.Swap(card5, curDeck.GetTopCard());

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // Player1 summon 'Kargath Prime' and 'Kargath Prime' kill a minion
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, AttackTask(card5, card3));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 10);
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // 'Kargath Prime' kill a minion
    game.Process(curPlayer, AttackTask(card5, card4));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 20);
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // 'Kargath Prime' kill a hero
    opPlayer->GetHero()->SetBaseHealth(10);
    game.Process(curPlayer, AttackTask(card5, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 20);
}

// ---------------------------------------- SPELL - WARRIOR
// [BT_124] Corsair Cache - COST:2
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a weapon. Give it +1/+1.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BT_124 : Corsair Cache")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fiery War Axe");
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

    const auto card =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Corsair Cache"));

    game.Process(curPlayer, PlayCardTask::Spell(card));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[3])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[3])->GetDurability(), 2);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[4])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[4])->GetDurability(), 3);
}

// --------------------------------------- MINION - WARRIOR
// [BT_138] Bloodboil Brute - COST:7 [ATK:6/HP:8]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b> Costs (1) less for each damaged minion.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BT_138 : Bloodboil Brute")
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

    [[maybe_unused]] const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodboil Brute"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Sorcerer's Apprentice"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(opPlayer, HeroPowerTask(card3));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(card1->GetCost(), 5);
}

// ---------------------------------------- SPELL - WARRIOR
// [BT_233] Sword and Board - COST:1
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to a minion. Gain 2 Armor.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BT_233 : Sword and Board")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sword and Board"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 10);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_321] Netherwalker - COST:2 [ATK:2/HP:2]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a Demon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_321 : Netherwalker")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Netherwalker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DEMON);
    }
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_423] Ashtongue Battlelord - COST:4 [ATK:3/HP:5]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Lifesteal</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_423 : Ashtongue Battlelord")
{
    // Do nothing
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_429] Metamorphosis - COST:5
// - Set: BLACK_TEMPLE, Rarity: Legendary
// - Spell School: Fel
// --------------------------------------------------------
// Text: Swap your Hero Power to "Deal 4 damage."
//       After 2 uses, swap it back.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_429 : Metamorphosis")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Metamorphosis"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->id, "BT_429p");

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->id, "BT_429p2");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [BT_430] Warglaives of Azzinoth - COST:5
// - Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: After attacking a minion, your hero may attack again.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - BT_430 : Warglaives of Azzinoth")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Warglaives of Azzinoth"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->CanAttack(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->CanAttack(), false);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_480] Crimson Sigil Runner - COST:1 [ATK:1/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_480 : Crimson Sigil Runner")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crimson Sigil Runner"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crimson Sigil Runner"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_486] Pit Commander - COST:9 [ATK:7/HP:9]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b> At the end of your turn,
//       summon a Demon from your deck.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_486 : Pit Commander")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Disguised Wanderer");
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Commander"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetRace(), Race::DEMON);
    CHECK_EQ(curDeck.GetCount(), 25);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_491] Spectral Sight - COST:2
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: Draw a card.
//       <b>Outcast:</b> Draw another.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_491 : Spectral Sight")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spectral Sight"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spectral Sight"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_493] Priestess of Fury - COST:7 [ATK:6/HP:7]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 6 damage randomly split among all enemies.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_493 : Priestess of Fury")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Priestess of Fury"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const int totalHealth =
        opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 36);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_496] Furious Felfin - COST:2 [ATK:3/HP:2]
// - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your hero attacked this turn,
//       gain +1 Attack and <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_496 : Furious Felfin")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Furious Felfin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Furious Felfin"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_509] Fel Summoner - COST:6 [ATK:8/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random Demon from your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_509 : Fel Summoner")
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
    curPlayer->SetTotalMana(20);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fel Summoner"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Battlefiend"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ur'zul Horror"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Fel Summoner");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->IsRace(Race::DEMON), true);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_514] Immolation Aura - COST:2
// - Set: BLACK_TEMPLE, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 1 damage to all minions twice.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_514 : Immolation Aura")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Immolation Aura"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Hogsteed"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Commander"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_601] Skull of Gul'dan - COST:6
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: Draw 3 cards. <b>Outcast:</b> Reduce their Cost by (3).
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_601 : Skull of Gul'dan")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.doShuffle = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 1] = Cards::FindCardByName("Goldshire Footman");
        config.player1Deck[i + 2] = Cards::FindCardByName("Skull of Gul'dan");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skull of Gul'dan"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skull of Gul'dan"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[5]->GetCost(), 0);
    CHECK_EQ(curHand[6]->GetCost(), 3);
    CHECK_EQ(curHand[7]->GetCost(), 6);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(curHand[7]->GetCost(), 1);
    CHECK_EQ(curHand[8]->GetCost(), 6);
    CHECK_EQ(curHand[9]->GetCost(), 9);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_761] Coilfang Warlord - COST:8 [ATK:9/HP:5]
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Deathrattle:</b> Summon a
//       5/9 Warlord with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_761 : Coilfang Warlord")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coilfang Warlord"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Coilfang Warlord");
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Conchguard Warlord");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_934] Imprisoned Antaen - COST:5 [ATK:10/HP:6]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. When this awakens,
//       deal 10 damage randomly split among all enemies.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_934 : Imprisoned Antaen")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Antaen"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 0);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    int totalHealth =
        opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 42);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 1);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    totalHealth = opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 32);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_008] Rustsworn Initiate - COST:2 [ATK:2/HP:2]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 1/1 Impcaster with
//       <b>Spell Damage +1</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_008 : Rustsworn Initiate")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rustsworn Initiate"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Rustsworn Initiate");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->card->name, "Impcaster");
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetSpellPower(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_010] Felfin Navigator - COST:4 [ATK:4/HP:4]
// - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your other Murlocs +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_010 : Felfin Navigator")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felfin Navigator"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->GetAttack(), 4);
    CHECK_EQ(curField[3]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetAttack(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_155] Scrapyard Colossus - COST:10 [ATK:7/HP:7]
// - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a
//       7/7 Felcracked Colossus with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_155 : Scrapyard Colossus")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Scrapyard Colossus"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Scrapyard Colossus");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->card->name, "Felcracked Colossus");
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_156] Imprisoned Vilefiend - COST:2 [ATK:3/HP:5]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns. <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BT_156 : Imprisoned Vilefiend")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Vilefiend"));

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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_159] Terrorguard Escapee - COST:3 [ATK:3/HP:7]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon three 1/1 Huntresses
//       for your opponent.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_159 : Terrorguard Escapee")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Terrorguard Escapee"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->card->name, "Huntress");
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->card->name, "Huntress");
    CHECK_EQ(opField[2]->GetHealth(), 1);
    CHECK_EQ(opField[2]->GetAttack(), 1);
    CHECK_EQ(opField[2]->card->name, "Huntress");
}

// --------------------------------------- MINION - NEUTRAL
// [BT_160] Rustsworn Cultist - COST:4 [ATK:3/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your other minions
//       "<b>Deathrattle:</b> Summon a 1/1 Demon."
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_160 : Rustsworn Cultist")
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
        curPlayer, Cards::FindCardByName("Rustsworn Cultist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Rusted Devil");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_714] Frozen Shadoweaver - COST:3 [ATK:4/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Freeze</b> an enemy.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_714 : Frozen Shadoweaver")
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

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Frozen Shadoweaver"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fen Creeper"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->IsFrozen(), false);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[1]->IsFrozen(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->IsFrozen(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_715] Bonechewer Brawler - COST:2 [ATK:2/HP:3]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> Whenever this minion takes damage,
//       gain +2 Attack.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_715 : Bonechewer Brawler")
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

    const auto card = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bonechewer Brawler"));

    game.Process(curPlayer, PlayCardTask::Minion(card));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card));
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card));
    CHECK_EQ(curField[0]->GetAttack(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_716] Bonechewer Vanguard - COST:7 [ATK:4/HP:10]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> Whenever this minion takes damage,
//       gain +2 Attack.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_716 : Bonechewer Vanguard")
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

    const auto card = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bonechewer Vanguard"));

    game.Process(curPlayer, PlayCardTask::Minion(card));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card));
    CHECK_EQ(curField[0]->GetAttack(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_722] Guardian Augmerchant - COST:1 [ATK:2/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to a minion and
//       give it <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_722 : Guardian Augmerchant")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Guardian Augmerchant"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Guardian Augmerchant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Guardian Augmerchant");

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_723] Rocket Augmerchant - COST:1 [ATK:2/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to a minion and
//       give it <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_723 : Rocket Augmerchant")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rocket Augmerchant"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rocket Augmerchant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Rocket Augmerchant");

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_724] Ethereal Augmerchant - COST:1 [ATK:2/HP:1]
// - Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to a minion and
//       give it <b>Spell Damage +1</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_724 : Ethereal Augmerchant")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        curPlayer, Cards::FindCardByName("Ethereal Augmerchant"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ethereal Augmerchant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Ethereal Augmerchant");

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetSpellPower(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_726] Dragonmaw Sky Stalker - COST:6 [ATK:5/HP:6]
// - Race: Dragon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 3/4 Dragonrider.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BT_726 : Dragonmaw Sky Stalker")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonmaw Sky Stalker"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Dragonmaw Sky Stalker");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Dragonrider");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [BT_728] Disguised Wanderer - COST:4 [ATK:3/HP:3]
// - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 9/1 Inquisitor.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Netural : Minion] - BT_728 : Disguised Wanderer")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Disguised Wanderer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Rustsworn Inquisitor");
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}