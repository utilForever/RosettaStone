// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [EX1_161] Naturalize - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a minion. Your opponent draws 2 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_161 : Naturalize")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Naturalize"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount + 2);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// ------------------------------------------- SPELL - MAGE
// [CS2_031] Ice Lance - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: <b>Freeze</b> a character. If it was already <b>Frozen</b>,
//       deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CS2_031 : Ice Lance")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card7));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(curField[0]->GetDamage(), 0);
    CHECK_EQ(curField[1]->GetDamage(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card6));
    CHECK_EQ(curField[0]->GetDamage(), 4);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card7));
    CHECK_EQ(card7->isDestroyed, true);
}

// ----------------------------------------- SPELL - PALADIN
// [EX1_349] Divine Favor - COST:3
// - Faction: Neutral, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: Draw cards until you have as many in hand
//       as your opponent
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_349 : Divine Favor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Divine Favor"));

    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(),
             opPlayer->GetHandZone()->GetCount());
}

// ---------------------------------------- MINION - PRIEST
// [CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
// - Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Whenever a minion is healed, draw a card.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CS2_235 : Northshire Cleric")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    curPlayer->GetHero()->SetDamage(6);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northshire Cleric"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);

    curField[0]->SetDamage(2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - PRIEST
// [CS2_236] Divine Spirit - COST:2
// - Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Double a minion's Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CS2_236 : Divine Spirit")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Divine Spirit"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);
}

// ----------------------------------------- SPELL - PRIEST
// [DS1_233] Mind Blast - COST:2
// - Faction: Neutral, Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Deal 5 damage to the enemy hero.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DS1_233 : Mind Blast")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
// - Faction: Neutral, Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: Double the damage and healing of your spells and Hero Power.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_350 : Prophet Velen")
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
    curPlayer->GetHero()->SetDamage(10);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Prophet Velen"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Prophet Velen"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Prophet Velen"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card5, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 2);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
// - Faction: Neutral, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: Your cards and powers that restore Health
//       now deal damage instead.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_591 : Auchenai Soulpriest")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Auchenai Soulpriest"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Circle of Healing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_624] Holy Fire - COST:6
// - Faction: Priest, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 5 damage. Restore 5 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_624 : Holy Fire")
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
    curPlayer->GetHero()->SetDamage(8);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Fire"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_625] Shadowform - COST:3
// - Faction: Priest, Set: HoF, Rarity: Epic
// --------------------------------------------------------
// Text: Your Hero Power becomes 'Deal 2 damage'.
//       If already in Shadowform: 3 damage.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_625 : Shadowform")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    Hero* opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Shatter");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 19);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Shatter");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 19);
}

// ------------------------------------------ SPELL - ROGUE
// [EX1_128] Conceal - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions <b>Stealth</b> until your next turn.
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_128 : Conceal")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Conceal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Patient Assassin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(curPlayer, AttackTask(card3, opPlayer->GetHero()));

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 0);
}

// ------------------------------------------ SPELL - ROGUE
// [NEW1_004] Vanish - COST:6
// - Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Return all minions to their owner's hand.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - NEW1_004 : Vanish")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vanish"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
// - Race: Demon, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>. <b>Battlecry:</b> Discard two random cards.
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_310 : Doomguard")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomguard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 2);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_316] Power Overwhelming - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Give a friendly minion +4/+4 until end of turn.
//       Then, it dies. Horribly.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_316 : Power Overwhelming")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Power Overwhelming"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goldshire Footman"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("King Mukla"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    game.Process(curPlayer, AttackTask(card2, card3));

    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
// - Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, draw a card.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_007 : Acolyte of Pain")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Acolyte of Pain"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
// - Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Take control of a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_016 : Sylvanas Windrunner")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Sylvanas Windrunner"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
// - Faction: Horde, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Silence</b> a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_048 : Spellbreaker")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbreaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbreaker"));
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
// [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
// - Faction: Neutral, Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_050 : Coldlight Oracle")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    const auto card =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coldlight Oracle"));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
// - Race: Murloc, Faction: Neutral. Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>. Has +1 Attack for each other Murloc on the battlefield.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_062 : Old Murk-Eye")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Old Murk-Eye"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
// - Faction: Alliance, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your opponent has 4 or
//       more minions, take control of one at random.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_085 : Mind Control Tech")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Control Tech"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card9 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mind Control Tech"));
    const auto card10 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card11 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card9));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card10));
    game.Process(opPlayer, PlayCardTask::Minion(card11));
    CHECK_EQ(opField.GetCount(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));
    game.Process(curPlayer, PlayCardTask::Minion(card8));
    CHECK_EQ(curField.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
// - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other card in your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_105 : Mountain Giant")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sap"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Assassinate"));

    CHECK_EQ(card1->GetCost(), 9);
    CHECK_EQ(card2->GetCost(), 9);
    CHECK_EQ(card3->GetCost(), 9);
    CHECK_EQ(card4->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 10);
    CHECK_EQ(card3->GetCost(), 10);
    CHECK_EQ(card4->GetCost(), 10);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 11);
    CHECK_EQ(card4->GetCost(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(card1->GetCost(), 10);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card2));
    CHECK_EQ(card2->GetCost(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_116] Leeroy Jenkins - COST:5 [ATK:6/HP:2]
// - Faction: Alliance, Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>. <b>Battlecry:</b> Summon two 1/1 Whelps
//       for your opponent.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_116 : Leeroy Jenkins")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leeroy Jenkins"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
// - Race: Dragon, Faction: Neutral, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_284 : Azure Drake")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azure Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Archmage"));

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));

    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
// - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each damage your hero has taken.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_620 : Molten Giant")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Molten Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));

    CHECK_EQ(card1->GetCost(), 20);

    game.Process(curPlayer, PlayCardTask(card2));
    game.Process(curPlayer, PlayCardTask(card3));
    game.Process(curPlayer, PlayCardTask(card4));
    game.Process(curPlayer, PlayCardTask(card5));

    CHECK_EQ(card1->GetCost(), 8);

    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card9 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));

    game.Process(curPlayer, PlayCardTask(card6));
    game.Process(curPlayer, PlayCardTask(card7));
    game.Process(curPlayer, PlayCardTask(card8));
    game.Process(curPlayer, PlayCardTask(card9));

    CHECK_EQ(card1->GetCost(), 0);
}
