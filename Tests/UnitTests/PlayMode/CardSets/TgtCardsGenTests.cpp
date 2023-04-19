// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [AT_037] Living Roots - COST:1
// - Set: Tgt, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 2 damage;
//       or Summon two 1/1 Saplings.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - AT_037 : Living Roots")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero(), 1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Sapling");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Sapling");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ----------------------------------------- SPELL - HUNTER
// [AT_061] Lock and Load - COST:2
// - Set: Tgt, Rarity: Epic
// --------------------------------------------------------
// Text: Each time you cast a spell this turn,
//       add a random Hunter card to your hand.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - AT_061 : Lock and Load")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lock and Load"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Timber Wolf"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK(curHand[1]->card->IsCardClass(CardClass::HUNTER));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 1);
}

// ------------------------------------------ MINION - MAGE
// [AT_003] Fallen Hero - COST:2 [ATK:3/HP:2]
// - Set: Tgt, Rarity: Rare
// --------------------------------------------------------
// Text: Your Hero Power deals 1 extra damage.
// --------------------------------------------------------
// GameTag:
// - HEROPOWER_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - AT_003 : Fallen Hero")
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

    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fallen Hero"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 26);
}

// ------------------------------------------ MINION - MAGE
// [AT_008] Coldarra Drake - COST:6 [ATK:6/HP:6]
// - Race: Dragon, Set: Tgt, Rarity: Epic
// --------------------------------------------------------
// Text: You can use your Hero Power any number of times.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - AT_008 : Coldarra Drake")
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

    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coldarra Drake"));

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 28);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);
}

// --------------------------------------- MINION - PALADIN
// [AT_075] Warhorse Trainer - COST:3 [ATK:2/HP:4]
// - Set: Tgt, Rarity: Common
// --------------------------------------------------------
// Text: Your Silver Hand Recruits have +2 Attack and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - AT_075 : Warhorse Trainer")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Warhorse Trainer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// ----------------------------------------- SPELL - PRIEST
// [AT_055] Flash Heal - COST:1
// - Set: Tgt, Rarity: Common
// --------------------------------------------------------
// Text: Restore 5 Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - AT_055 : Flash Heal")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));

    CHECK_EQ(curHero->GetHealth(), 20);
    CHECK_EQ(opHero->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curHero));
    CHECK_EQ(curHero->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 25);
}

//----------------------------------------- MINION - ROGUE
// [AT_029] Buccaneer - COST:1 [ATK:2/HP:1]
// - Race: Pirate, Set: Tgt, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you equip a weapon, give it +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - AT_029 : Buccaneer")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Buccaneer"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
}

// ---------------------------------------- MINION - SHAMAN
// [AT_047] Draenei Totemcarver - COST:4 [ATK:4/HP:5]
// - Set: Tgt, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1/+1 for each friendly Totem.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - AT_047 : Draenei Totemcarver")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Draenei Totemcarver"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Draenei Totemcarver"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 6);
}

// --------------------------------------- MINION - WARLOCK
// [AT_021] Tiny Knight of Evil - COST:2 [ATK:3/HP:2]
// - Race: Demon, Set: Tgt, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you discard a card, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - AT_021 : Tiny Knight of Evil")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tiny Knight of Evil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[0], opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ---------------------------------------- SPELL - WARRIOR
// [AT_064] Bash - COST:2
// - Set: Tgt, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage.
//       Gain 3 Armor.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - AT_064 : Bash")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bash"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [AT_092] Ice Rager - COST:3 [ATK:5/HP:2]
// - Race: Elemental, Set: Tgt, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - AT_092 : Ice Rager")
{
    // Do nothing
}