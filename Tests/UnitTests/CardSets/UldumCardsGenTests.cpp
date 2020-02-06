// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ----------------------------------------- MINION - DRUID
// [ULD_133] Crystal Merchant - COST:2 [ATK:1/HP:4]
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: If you have any unspent Mana at the end of your turn,
//       draw a card.
// --------------------------------------------------------
TEST(DruidUldumTest, ULD_133_CrystalMerchant)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Merchant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curHand.GetCount(), 5);
    EXPECT_EQ(opHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curHand.GetCount(), 6);
    EXPECT_EQ(opHand.GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curHand.GetCount(), 7);
    EXPECT_EQ(opHand.GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetRemainingMana(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curHand.GetCount(), 6);
    EXPECT_EQ(opHand.GetCount(), 7);
}

// ----------------------------------------- SPELL - HUNTER
// [ULD_152] Pressure Plate - COST:2
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent casts a spell,
//       destroy a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST(HunterUldumTest, ULD_152_PressurePlate)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pressure Plate"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    EXPECT_EQ(curSecret.GetCount(), 1);
    EXPECT_EQ(card1->GetGameTag(GameTag::REVEALED), 0);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    EXPECT_EQ(opField.GetCount(), 1);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    EXPECT_EQ(curSecret.GetCount(), 0);
    EXPECT_EQ(card1->GetGameTag(GameTag::REVEALED), 1);
    EXPECT_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARRIOR
// [ULD_206] Restless Mummy - COST:4 [ATK:3/HP:2]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - REBORN = 1
// --------------------------------------------------------
TEST(WarriorUldumTest, ULD_206_RestlessMummy)
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [ULD_207] Ancestral Guardian - COST:4 [ATK:4/HP:2]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b> <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - REBORN = 1
// --------------------------------------------------------
TEST(PaladinUldumTest, ULD_207_AncestralGuardian)
{
    // Do nothing
}

// ---------------------------------------- SPELL - PALADIN
// [ULD_431] Making Mummies - COST:1
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Quest:</b> Play 5 <b>Reborn</b> minions.
//       <b>Reward:</b> Emperor Wraps.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - QUEST = 1
// - QUEST_PROGRESS_TOTAL = 5
// - 676 = 1
// - 839 = 1
// - QUEST_REWARD_DATABASE_ID = 53908
// --------------------------------------------------------
// RefTag:
// - REBORN = 1
// --------------------------------------------------------
TEST(PaladinUldumTest, ULD_431_MakingMummies)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto curHero = curPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Making Mummies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_TRUE(curSecret->quest != nullptr);
    EXPECT_EQ(quest->GetQuestProgress(), 0);
    EXPECT_EQ(quest->GetQuestProgressTotal(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    EXPECT_EQ(quest->GetQuestProgress(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    EXPECT_EQ(quest->GetQuestProgress(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    EXPECT_TRUE(curSecret->quest == nullptr);
    EXPECT_EQ(quest->GetQuestProgress(), 5);
    EXPECT_EQ(curHero->heroPower->card->id, "ULD_431p");

    game.Process(curPlayer, HeroPowerTask(card2));
    EXPECT_EQ(curField.GetCount(), 6);
    EXPECT_EQ(curField[0]->GetAttack(), 1);
    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(curField[0]->HasReborn(), true);
    EXPECT_EQ(curField[1]->GetAttack(), 2);
    EXPECT_EQ(curField[1]->GetHealth(), 2);
    EXPECT_EQ(curField[1]->HasReborn(), true);
    EXPECT_EQ(curField[2]->GetAttack(), 1);
    EXPECT_EQ(curField[2]->GetHealth(), 1);
    EXPECT_EQ(curField[2]->HasReborn(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_174] Serpent Egg - COST:2 [ATK:0/HP:3]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 3/4 Sea Serpent.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_174_SerpentEgg)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Serpent Egg"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    EXPECT_EQ(curField.GetCount(), 1);
    EXPECT_EQ(curField[0]->card->name, "Sea Serpent");
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_182] Spitting Camel - COST:2 [ATK:2/HP:4]
// - Race: Beast, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn, deal 1 damage
//       to another random friendly minion.
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_182_SpittingCamel)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spitting Camel"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(curField[1]->GetHealth(), 5);
    EXPECT_EQ(curField[2]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curField[0]->GetHealth(), 4);
    EXPECT_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curField[0]->GetHealth(), 4);
    EXPECT_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);
    EXPECT_EQ(curField[0]->GetHealth(), 4);
    EXPECT_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_184] Kobold Sandtrooper - COST:2 [ATK:2/HP:1]
// - Faction: Alliance, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 3 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_184_KoboldSandtrooper)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kobold Sandtrooper"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_191] Beaming Sidekick - COST:1 [ATK:1/HP:2]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_191_BeamingSidekick)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, nullptr));
    EXPECT_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    EXPECT_EQ(curField[0]->GetHealth(), 4);
    EXPECT_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card2));
    EXPECT_EQ(curField[0]->GetHealth(), 4);
    EXPECT_EQ(curField[1]->GetHealth(), 4);
    EXPECT_EQ(curField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_193] Living Monument - COST:10 [ATK:10/HP:10]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_193_LivingMonument)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Monument"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_194] Wasteland Scorpid - COST:7 [ATK:3/HP:9]
// - Race: Beast, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_194_WastelandScorpid)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_205] Candletaker - COST:3 [ATK:3/HP:2]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - REBORN = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_205_Candletaker)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_271] Injured Tol'vir - COST:2 [ATK:2/HP:6]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 3 damage to this minion.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_271_InjuredTolvir)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Injured Tol'vir"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField[0]->GetDamage(), 3);
}

// ------------------------------------------ SPELL - DRUID
// [ULD_273] Overflow - COST:7
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Restore 5 Health to all characters. Draw 5 cards.
// --------------------------------------------------------
TEST(DruidUldumTest, ULD_273_Overflow)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = config.player2Deck[i] =
            *Cards::FindCardByName("Magma Rager");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Injured Tol'vir"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Injured Tol'vir"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Overflow"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    EXPECT_EQ(curField[0]->GetHealth(), 3);
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    EXPECT_EQ(opField[0]->GetHealth(), 3);
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    EXPECT_EQ(curField[0]->GetHealth(), 6);
    EXPECT_EQ(opField[0]->GetHealth(), 6);
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 29);
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 29);
    EXPECT_EQ(curHand.GetCount(), 10);
    EXPECT_EQ(opHand.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_289] Fishflinger - COST:2 [ATK:3/HP:2]
// - Race: Murloc, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Murloc
//       to each player's hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_289_Fishflinger)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fishflinger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curHand.GetCount(), 5);
    EXPECT_EQ(opHand.GetCount(), 6);
    EXPECT_EQ(curHand[4]->card->GetRace(), Race::MURLOC);
    EXPECT_EQ(opHand[5]->card->GetRace(), Race::MURLOC);
}

// ---------------------------------------- WEAPON - HUNTER
// [ULD_430] Desert Spear - COST:3 [ATK:1/HP:0]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: After your hero attacks,
//       summon a 1/1 Locust with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST(HunterUldumTest, ULD_430_DesertSpear)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desert Spear"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    EXPECT_EQ(curField.GetCount(), 1);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    EXPECT_EQ(curField.GetCount(), 2);
    EXPECT_EQ(opField.GetCount(), 0);
    EXPECT_EQ(curField[1]->card->name, "Locust");
    EXPECT_EQ(curField[1]->GetAttack(), 1);
    EXPECT_EQ(curField[1]->GetHealth(), 1);
    EXPECT_EQ(curField[1]->IsRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Weapon(card3));
    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 27);
    EXPECT_EQ(curField.GetCount(), 2);
    EXPECT_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_274] Wasteland Assassin - COST:5 [ATK:4/HP:2]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - REBORN = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_274_WastelandAssassin)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_275] Bone Wraith - COST:4 [ATK:2/HP:5]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - REBORN = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_275_BoneWraith)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_450] Vilefiend - COST:2 [ATK:2/HP:2]
// - Race: Demon, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_450_Vilefiend)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vilefiend"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightwarden"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 24);
    EXPECT_EQ(curField[1]->GetAttack(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 26);
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
    EXPECT_EQ(curField[1]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
    EXPECT_EQ(curField[1]->GetAttack(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
    EXPECT_EQ(curField[1]->GetAttack(), 7);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 26);
    EXPECT_EQ(curField[1]->GetAttack(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_712] Bug Collector - COST:2 [ATK:2/HP:1]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Locust with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_712_BugCollector)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bug Collector"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bug Collector"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField.GetCount(), 2);
    EXPECT_EQ(curField[1]->card->name, "Locust");
    EXPECT_EQ(curField[1]->GetAttack(), 1);
    EXPECT_EQ(curField[1]->GetHealth(), 1);
    EXPECT_EQ(curField[1]->GetGameTag(GameTag::RUSH), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(opField.GetCount(), 2);
    EXPECT_EQ(opField[1]->card->name, "Locust");
    EXPECT_EQ(opField[1]->GetAttack(), 1);
    EXPECT_EQ(opField[1]->GetHealth(), 1);
    EXPECT_EQ(opField[1]->GetGameTag(GameTag::RUSH), 1);

    game.Process(opPlayer, AttackTask(opField[1], curField[1]));
    EXPECT_EQ(curField.GetCount(), 1);
    EXPECT_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_721] Colossus of the Moon - COST:10 [ATK:10/HP:10]
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Divine Shield</b> <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DIVINE_SHIELD = 1
// - REBORN = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_721_ColossusOfTheMoon)
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_723] Murmy - COST:1 [ATK:1/HP:1]
// - Race: Murloc, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - REBORN = 1
// --------------------------------------------------------
TEST(NeutralUldumTest, ULD_723_Murmy)
{
    // Do nothing
}
