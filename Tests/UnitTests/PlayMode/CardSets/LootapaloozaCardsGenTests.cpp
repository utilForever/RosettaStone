// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ---------------------------------------- WEAPON - HUNTER
// [LOOT_222] Candleshot - COST:1 [ATK:1/HP:0]
// - Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Immune</b> while attacking.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - LOOT_222 : Candleshot")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Candleshot"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 1);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);
}

// ------------------------------------------- SPELL - MAGE
// [LOOT_101] Explosive Runes - COST:3
// - Faction: Neutral, Set: Lootapalooza, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       deal 6 damage to it and any excess to their hero.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - LOOT_101 : Explosive Runes")
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
    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Runes"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Runes"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_124] Lone Champion - COST:3 [ATK:2/HP:4]
// - Set: Lootapalooza, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control no other minions,
//       gain <b>Taunt</b> and <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_124 : Lone Champion")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_125] Stoneskin Basilisk - COST:3 [ATK:1/HP:1]
// - Race: Beast, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_125 : Stoneskin Basilisk")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_137] Sleepy Dragon - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_137 : Sleepy Dragon")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_413] Plated Beetle - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Gain 3 Armor.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_413 : Plated Beetle")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plated Beetle"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_516] Zola the Gorgon - COST:3 [ATK:2/HP:2]
// - Set: Lootapalooza, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly minion.
//       Add a Golden copy of it to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_516 : Zola the Gorgon")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Zola the Gorgon"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Wisp");
    CHECK_EQ(curHand[0]->IsGoldenCard(), true);
}