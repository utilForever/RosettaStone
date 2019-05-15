// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ---------------------------------------- MINION - HUNTER
// [EX1_543] King Krush - COST:9 [ATK:8/HP:8]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST(HunterExpert1Test, EX1_543_KingKrush)
{
    // Do nothing
}

// ------------------------------------------- SPELL - MAGE
// [CS2_028] Blizzard - COST:6
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Deal $2 damage to all enemy minions and <b>Freeze</b> them.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST(MageExpert1Test, CS2_028_Blizzard)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blizzard"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(opPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, AttackTask(card2, curPlayer.GetHero()));
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 0);
}

// ----------------------------------------- SPELL - PRIEST
// [CS1_129] Inner Fire - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Change a minion's Attack to be equal to its Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(Expert1CardsGen, CS1_129_InnerFire)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Inner Fire"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Divine Spirit"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Inner Fire"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Inner Fire"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curField.GetMinion(0)));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(),
              curField.GetMinion(0)->GetAttack());

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, curField.GetMinion(0)));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, curField.GetMinion(0)));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(),
              curField.GetMinion(0)->GetAttack());

    curField.GetMinion(0)->SetDamage(1);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curField.GetMinion(0)));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(),
              curField.GetMinion(0)->GetAttack());
}

// ------------------------------------------ SPELL - ROGUE
// [CS2_073] Cold Blood - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +2 Attack. <b>Combo:</b> +4 Attack instead.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(RogueExpert1Test, CS2_073_ColdBlood)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Cold Blood"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Cold Blood"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 7);
}

// ----------------------------------------- MINION - ROGUE
// [EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>
//        <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST(RogueExpert1Test, EX1_522_PatientAssassin)
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [CS2_038] Ancestral Spirit - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion "<b>Deathrattle:</b> Resummon this minion."
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(ShamanExpert1Test, CS2_038_AncestralSpirit)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ancestral Spirit"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 2);
}

// ----------------------------------------- SPELL - SHAMAN
// [CS2_053] Far Sight - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Draw a card. That card costs (3) less.
// --------------------------------------------------------
TEST(ShamanExpert1Test, CS2_053_FarSight)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curHand = curPlayer.GetHand();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Far Sight"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Entity* drawCard = curPlayer.GetHand().GetCard(curHand.GetNumOfCards() - 1);
    int cost = drawCard->card.gameTags[GameTag::COST] - 3;
    EXPECT_EQ(cost < 0 ? 0 : cost, drawCard->GetCost());
}

// ----------------------------------------- SPELL - SHAMAN
// [EX1_238] Lightning Bolt - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Deal $3 damage. <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST(ShamanExpert1Test, EX1_238_LightningBolt)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Lightning Bolt"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(curPlayer.GetRemainingMana(), 9);
    EXPECT_EQ(curPlayer.GetOverloadOwed(), 1);
    EXPECT_EQ(curPlayer.GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetRemainingMana(), 9);
    EXPECT_EQ(curPlayer.GetOverloadOwed(), 0);
    EXPECT_EQ(curPlayer.GetOverloadLocked(), 1);
}

// ---------------------------------------- MINION - SHAMAN
// [NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:5]
// - Race: Elemental, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - WINDFURY = 1
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST(ShamanExpert1Test, NEW1_010_AlAkirTheWindlord)
{
    // Do nothing
}

// --------------------------------------- MINION - WARLOCK
// [CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
// - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. At the end of your turn,
//       give another random friendly minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST(WarlockExpert1Test, CS2_059_BloodImp)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blood Imp"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    int totalHealth = curField.GetMinion(1)->GetHealth();
    totalHealth += curField.GetMinion(2)->GetHealth();
    EXPECT_EQ(totalHealth, 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    totalHealth = curField.GetMinion(1)->GetHealth();
    totalHealth += curField.GetMinion(2)->GetHealth();
    EXPECT_EQ(totalHealth, 4);
}

// --------------------------------------- MINION - NEUTRAL
// [CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS1_069_FenCreeper)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 3 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS2_117_EarthenRingFarseer)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);
    curPlayer.GetHero()->SetDamage(10);

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Earthen Ring Farseer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Earthen Ring Farseer"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    opField.GetMinion(0)->SetDamage(1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 23);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/2 Squire.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS2_151_SilverHandKnight)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Silver Hand Knight"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS2_161_RavenholdtAssassin)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
// - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS2_169_YoungDragonhawk)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(Expert1CardsGen, CS2_188_AbusiveSergeant)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Abusive Sergeant"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Abusive Sergeant"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 5);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
TEST(NeutralExpert1Test, CS2_231_Wisp)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_008_ArgentSquire)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_010_WorgenInfiltrator)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
// - Fac: neutral, Set: expert1, Rarity: legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_012_BloodmageThalnos)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Bloodmage Thalnos"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blizzard"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curPlayer.currentSpellPower, 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 0u);
    EXPECT_EQ(curPlayer.currentSpellPower, 0);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
// - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_017_JunglePanther)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_020_ScarletCrusader)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_021_ThrallmarFarseer)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
// - Race: Beast, Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_028_StranglethornTiger)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_032_Sunwalker)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_033_WindfuryHarpy)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_067_ArgentCommander)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_170_EmperorCobra)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_396_MogushanWarden)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_405_Shieldbearer)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_563] Malygos - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +5</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 5
// --------------------------------------------------------
TEST(NeutralExpert1Test, EX1_563_Malygos)
{
    // Do nothing
}