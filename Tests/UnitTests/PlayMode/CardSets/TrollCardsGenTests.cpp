// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [TRL_243] Pounce - COST:0
// - Set: Troll, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn.turn
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - TRL_243 : Pounce")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ---------------------------------------- WEAPON - HUNTER
// [TRL_111] Headhunter's Hatchet - COST:2 [ATK:2/HP:0]
// - Set: Troll, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a Beast,
//       gain +1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - TRL_111 : Headhunter's Hatchet")
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

    auto& curHero = *(curPlayer->GetHero());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Headhunter's Hatchet"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Headhunter's Hatchet"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK(curHero.HasWeapon());
    CHECK_EQ(curHero.weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK(curHero.HasWeapon());
    CHECK_EQ(curHero.weapon->GetDurability(), 3);
}

// ---------------------------------------- MINION - HUNTER
// [TRL_348] Springpaw - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: Troll, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Battlecry:</b> Add a 1/1 Lynx
//       with <b>Rush</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - TRL_348 : Springpaw")
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Springpaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Lynx");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ------------------------------------------ MINION - MAGE
// [TRL_315] Pyromaniac - COST:3 [ATK:3/HP:4]
// - Set: Troll, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever your Hero Power kills a minion, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - TRL_315 : Pyromaniac")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyromaniac"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Goldshire Footman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 7);
}

// ---------------------------------------- SPELL - PALADIN
// [TRL_307] Flash of Light - COST:2
// - Set: Troll, Rarity: Common
// --------------------------------------------------------
// Text: Restore 4 Health. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - TRL_307 : Flash of Light")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash of Light"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curHand.GetCount(), 6);
}

// ---------------------------------------- MINION - SHAMAN
// [TRL_345] Krag'wa, the Frog - COST:6 [ATK:4/HP:6]
// - Race: Beast, Set: Troll, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Return all spells you played
//       last turn to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - TRL_345 : Krag'wa, the Frog")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Krag'wa, the Frog"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Krag'wa, the Frog"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomhammer"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[2]->card->name, "Fireball");

    curPlayer->SetUsedMana(0);
    game.Process(curPlayer, PlayCardTask::Weapon(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 1);
}

// --------------------------------------- MINION - WARLOCK
// [TRL_252] High Priestess Jeklik - COST:4 [ATK:3/HP:5]
// - Set: Troll, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b>, <b>Lifesteal</b>
//       When you discard this,
//       add 2 copies of it to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// - InvisibleDeathrattle = 1
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - TRL_252 : High Priestess Jeklik")
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

    [[maybe_unused]] const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("High Priestess Jeklik"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));

    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "High Priestess Jeklik");
    CHECK_EQ(curHand[1]->card->name, "High Priestess Jeklik");
}