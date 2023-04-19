// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [LOE_050] Mounted Raptor - COST:3 [ATK:3/HP:2]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random 1-Cost minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - LOE_050 : Mounted Raptor")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mounted Raptor"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 1);
}

// ----------------------------------------- MINION - DRUID
// [LOE_051] Jungle Moonkin - COST:4 [ATK:4/HP:4]
// - Race: Beast, Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Both players have <b>Spell Damage +2</b>.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 2
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - LOE_051 : Jungle Moonkin")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jungle Moonkin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 2);
    CHECK_EQ(opPlayer->GetCurrentSpellPower(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
}

// ------------------------------------------ SPELL - DRUID
// [LOE_115] Raven Idol - COST:1
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b>
//       <b>Discover</b> a minion; or <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - CHOOSE_ONE = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - LOE_115 : Raven Idol")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Raven Idol"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Raven Idol"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
}

// ---------------------------------------- MINION - HUNTER
// [LOE_020] Desert Camel - COST:3 [ATK:2/HP:4]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Put a 1-Cost minion from each deck
//       into the battlefield.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - LOE_020 : Desert Camel")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player2Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player2Deck[i + 2] = Cards::FindCardByName("Wisp");
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
    auto& opDeck = *(opPlayer->GetDeckZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desert Camel"));

    CHECK_EQ(curDeck.GetCount(), 26);
    CHECK_EQ(opDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 25);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Worgen Infiltrator");
    CHECK_EQ(opDeck.GetCount(), 25);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Worgen Infiltrator");
}

// ----------------------------------------- SPELL - HUNTER
// [LOE_021] Dart Trap - COST:2
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After an opposing Hero Power is used,
//       deal 5 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - LOE_021 : Dart Trap")
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dart Trap"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, HeroPowerTask());

    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ((card2->isDestroyed || opPlayer->GetHero()->GetHealth() == 27),
             true);
}

// ----------------------------------------- SPELL - HUNTER
// [LOE_105] Explorer's Hat - COST:2
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +1/+1 and "<b>Deathrattle:</b>
//       Add an Explorer's Hat to your hand."
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - LOE_105 : Explorer's Hat")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explorer's Hat"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Explorer's Hat");
}

// ------------------------------------------- SPELL - MAGE
// [LOE_002] Forgotten Torch - COST:3
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage. Shuffle a 'Roaring Torch'
//       into your deck that deals 6 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - LOE_002 : Forgotten Torch")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Forgotten Torch"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curDeck[0]->card->name, "Roaring Torch");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[0], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 6);
}

// ------------------------------------------ MINION - MAGE
// [LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:3]
// - Set: LoE Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - LOE_003 : Ethereal Conjurer")
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
        curPlayer, Cards::FindCardByName("Ethereal Conjurer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::MAGE), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// ------------------------------------------ MINION - MAGE
// [LOE_119] Animated Armor - COST:4 [ATK:4/HP:4]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Your hero can only take 1 damage at a time.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - LOE_119 : Animated Armor")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Animated Armor"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - PALADIN
// [LOE_017] Keeper of Uldaman - COST:4 [ATK:3/HP:4]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Set a minion's Attack and Health to 3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - LOE_017 : Keeper of Uldaman")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Keeper of Uldaman"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// ---------------------------------------- SPELL - PALADIN
// [LOE_026] Anyfin Can Happen - COST:10
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Summon 7 Murlocs that died this game.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - LOE_026 : Anyfin Can Happen")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Anyfin Can Happen"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desk Imp"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Snowflipper Penguin"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Target Dummy"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK(curField[0]->IsRace(Race::MURLOC));
    CHECK(curField[1]->IsRace(Race::MURLOC));
}

// ---------------------------------------- SPELL - PALADIN
// [LOE_027] Sacred Trial - COST:1
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent has at least
//       3 minions and plays another, destroy it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - LOE_027 : Sacred Trial")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sacred Trial"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 3);
}

// ---------------------------------------- MINION - PRIEST
// [LOE_006] Museum Curator - COST:2 [ATK:1/HP:2]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a <b>Deathrattle</b> card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - LOE_006 : Museum Curator")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Museum Curator"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->HasGameTag(GameTag::DEATHRATTLE), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [LOE_104] Entomb - COST:6
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: Choose an enemy minion. Shuffle it into your deck.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - LOE_104 : Entomb")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Entomb"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curDeck[0]->card->name, "Malygos");
}

// ----------------------------------------- SPELL - PRIEST
// [LOE_111] Excavated Evil - COST:5
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 3 damage to all minions.
//       Shuffle this card into your opponent's deck.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - LOE_111 : Excavated Evil")
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

    auto& opDeck = *(opPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Excavated Evil"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Upgradeable Framebot"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(opDeck.GetCount(), 1);
    CHECK_EQ(opDeck[0]->card->name, "Excavated Evil");
}

// ----------------------------------------- MINION - ROGUE
// [LOE_010] Pit Snake - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - LOE_010 : Pit Snake")
{
    // Do nothing
}

// ----------------------------------------- MINION - ROGUE
// [LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a Coin to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - LOE_012 : Tomb Pillager")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tomb Pillager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "The Coin");
}

// ----------------------------------------- MINION - ROGUE
// [LOE_019] Unearthed Raptor - COST:3 [ATK:3/HP:4]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly minion.
//       Gain a copy of its <b>Deathrattle</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_DEATHRATTLE = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - LOE_019 : Unearthed Raptor")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Unearthed Raptor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[1]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - SHAMAN
// [LOE_016] Rumbling Elemental - COST:4 [ATK:2/HP:6]
// - Race: Elemental, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: After you play a <b>Battlecry</b> minion,
//       deal 2 damage to a random enemy.
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - LOE_016 : Rumbling Elemental")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rumbling Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Fly"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - SHAMAN
// [LOE_018] Tunnel Trogg - COST:1 [ATK:1/HP:3]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you <b>Overload</b>,
//       gain +1 Attack per locked Mana Crystal.
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - LOE_018 : Tunnel Trogg")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tunnel Trogg"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Fly"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dust Devil"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [LOE_113] Everyfin is Awesome - COST:7
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Give your minions +2/+2.
//       Costs (1) less for each Murloc you control.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - LOE_113 : Everyfin is Awesome")
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
        curPlayer, Cards::FindCardByName("Everyfin is Awesome"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Fly"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));

    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ---------------------------------------- SPELL - WARLOCK
// [LOE_007] Curse of Rafaam - COST:2
// - Set: LoE, Rarity: common
// --------------------------------------------------------
// Text: Give your opponent a 'Cursed!' card.
//       While they hold it, they take 2 damage on their turn.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - LOE_007 : Curse of Rafaam")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Curse of Rafaam"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opHand.GetCount(), 6);
    CHECK_EQ(opHand[5]->card->name, "Cursed!");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, PlayCardTask::Spell(opHand[5]));
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - WARLOCK
// [LOE_023] Dark Peddler - COST:2 [ATK:2/HP:2]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a 1-Cost card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - LOE_023 : Dark Peddler")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dark Peddler"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCost(), 1);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// --------------------------------------- MINION - WARLOCK
// [LOE_116] Reliquary Seeker - COST:1 [ATK:1/HP:1]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have 6 other minions,
//       gain +4/+4.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - LOE_116 : Reliquary Seeker")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reliquary Seeker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reliquary Seeker"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[6]->GetAttack(), 5);
    CHECK_EQ(curField[6]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [LOE_009] Obsidian Destroyer - COST:7 [ATK:7/HP:7]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn,
//       summon a 1/1 Scarab with <b>Taunt</b>.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - LOE_009 : Obsidian Destroyer")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Obsidian Destroyer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Scarab");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// --------------------------------------- MINION - WARRIOR
// [LOE_022] Fierce Monkey - COST:3 [ATK:3/HP:4]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - LOE_022 : Fierce Monkey")
{
    // Do nothing
}

// --------------------------------------- WEAPON - WARRIOR
// [LOE_118] Cursed Blade - COST:1 [ATK:2/HP:0]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Double all damage dealt to your hero.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - LOE_118 : Cursed Blade")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cursed Blade"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 14);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_011] Reno Jackson - COST:6 [ATK:4/HP:6]
// - Set: LoE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       fully heal your hero.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_011 : Reno Jackson")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 6; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
    curPlayer->GetHero()->SetDamage(20);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reno Jackson"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reno Jackson"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_029] Jeweled Scarab - COST:2 [ATK:1/HP:1]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a 3-Cost card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_029 : Jeweled Scarab")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jeweled Scarab"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCost(), 3);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_038] Naga Sea Witch - COST:8 [ATK:5/HP:5]
// - Set: LoE, Rarity: Epic
// --------------------------------------------------------
// Text: Your cards cost (5).
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_038 : Naga Sea Witch")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naga Sea Witch"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 9);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_039] Gorillabot A-3 - COST:3 [ATK:3/HP:4]
// - Race: Mechanical, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control another Mech,
//       <b>Discover</b> a Mech.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_039 : Gorillabot A-3")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gorillabot A-3"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gorillabot A-3"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(!curPlayer->choice);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::MECHANICAL);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_046] Huge Toad - COST:2 [ATK:3/HP:2]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 1 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_046 : Huge Toad")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Huge Toad"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Shieldbearer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth(), 34);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth(), 33);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_047] Tomb Spider - COST:4 [ATK:3/HP:3]
// - Race: Beast, Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a Beast.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_047 : Tomb Spider")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tomb Spider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::BEAST);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_053] Djinni of Zephyrs - COST:5 [ATK:4/HP:6]
// - Race: Elemental, Set: LoE, Rarity: Epic
// --------------------------------------------------------
// Text: After you cast a spell on another friendly minion,
//       cast a copy of it on this one.
// --------------------------------------------------------
// GameTag:
// - 1059 = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_053 : Djinni of Zephyrs")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Djinni of Zephyrs"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_061] Anubisath Sentinel - COST:5 [ATK:4/HP:4]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give a random friendly minion +3/+3.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_061 : Anubisath Sentinel")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Anubisath Sentinel"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_073] Fossilized Devilsaur - COST:8 [ATK:8/HP:8]
// - Set: LoE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a Beast,
//       gain <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_073 : Fossilized Devilsaur")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fossilized Devilsaur"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fossilized Devilsaur"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dire Wolf Alpha"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_076] Sir Finley Mrrgglton - COST:1 [ATK:1/HP:3]
// - Race: Murloc, Set: LoE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a new basic Hero Power.
// --------------------------------------------------------
// Entourage: HERO_01bp, HERO_02bp, HERO_03bp, HERO_04bp,
//            HERO_05bp, HERO_06bp, HERO_07bp, HERO_08bp,
//            HERO_09bp, HERO_10bp
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_076 : Sir Finley Mrrgglton")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sir Finley Mrrgglton"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::HERO_POWER);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_077] Brann Bronzebeard - COST:3 [ATK:2/HP:4]
// - Set: LoE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your <b>Battlecries</b> trigger twice.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_077 : Brann Bronzebeard")
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
    opPlayer->GetHero()->SetDamage(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Brann Bronzebeard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elven Archer"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razorfen Hunter"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abusive Sergeant"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->ExtraBattlecry(), true);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[2]->card->name, "Razorfen Hunter");
    CHECK_EQ(curField[3]->card->name, "Boar");
    CHECK_EQ(curField[4]->card->name, "Boar");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(curPlayer->ExtraBattlecry(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_079] Elise Starseeker - COST:4 [ATK:3/HP:5]
// - Set: LoE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle the
//       'Map to the Golden Monkey' into your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_079 : Elise Starseeker")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Bloodfen Raptor");
    config.player1Deck[1] = Cards::FindCardByName("Young Dragonhawk");
    config.player1Deck[2] = Cards::FindCardByName("Faerie Dragon");

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(0);

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elise Starseeker"));

    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curDeck.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curHand[3]->card->name, "Map to the Golden Monkey");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[3]));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curHand[3]->card->name, "Golden Monkey");
    CHECK_EQ(curDeck.GetCount(), 0);

    Card* wispCard = Cards::FindCardByName("Wisp");
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[3]));
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[2]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[2]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[0]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[1]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[2]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[2]->card->GetRarity(), Rarity::LEGENDARY);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_086] Summoning Stone - COST:5 [ATK:0/HP:6]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       summon a random minion of the same Cost.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_086 : Summoning Stone")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Summoning Stone"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->GetCost(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_089] Wobbling Runts - COST:6 [ATK:2/HP:6]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon three 2/2 Runts.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_089 : Wobbling Runts")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wobbling Runts"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Grumbly Runt");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Wily Runt");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Rascally Runt");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_092] Arch-Thief Rafaam - COST:9 [ATK:7/HP:8]
// - Set: LoE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a powerful Artifact.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_092 : Arch-Thief Rafaam")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arch-Thief Rafaam"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    CHECK_EQ(cards[0]->name, "Lantern of Power");
    CHECK_EQ(cards[1]->name, "Mirror of Doom");
    CHECK_EQ(cards[2]->name, "Timepiece of Horror");

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    SUBCASE("Arch-Thief Rafaam - LOEA16_3")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("LOEA16_3"));

        game.Process(curPlayer, PlayCardTask::SpellTarget(card, card1));
        CHECK_EQ(curField[0]->GetAttack(), 17);
        CHECK_EQ(curField[0]->GetHealth(), 18);
    }

    SUBCASE("Arch-Thief Rafaam - LOEA16_4")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("LOEA16_4"));

        game.Process(curPlayer, PlayCardTask::Spell(card));
        CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    }

    SUBCASE("Arch-Thief Rafaam - LOEA16_5")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("LOEA16_5"));

        game.Process(curPlayer, PlayCardTask::Spell(card));
        CHECK_EQ(curField.GetCount(), 7);
        CHECK_EQ(curField[1]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[1]->GetAttack(), 3);
        CHECK_EQ(curField[1]->GetHealth(), 3);
        CHECK_EQ(curField[2]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[2]->GetAttack(), 3);
        CHECK_EQ(curField[2]->GetHealth(), 3);
        CHECK_EQ(curField[3]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[3]->GetAttack(), 3);
        CHECK_EQ(curField[3]->GetHealth(), 3);
        CHECK_EQ(curField[4]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[4]->GetAttack(), 3);
        CHECK_EQ(curField[4]->GetHealth(), 3);
        CHECK_EQ(curField[5]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[5]->GetAttack(), 3);
        CHECK_EQ(curField[5]->GetHealth(), 3);
        CHECK_EQ(curField[6]->card->name, "Mummy Zombie");
        CHECK_EQ(curField[6]->GetAttack(), 3);
        CHECK_EQ(curField[6]->GetHealth(), 3);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_107] Eerie Statue - COST:4 [ATK:7/HP:7]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack unless it's the only minion
//       in the battlefield.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_107 : Eerie Statue")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eerie Statue"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [LOE_110] Ancient Shade - COST:4 [ATK:7/HP:4]
// - Set: LoE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle an 'Ancient Curse'
//       into your deck that deals 7 damage to you when drawn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOE_110 : Ancient Shade")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Shade"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opDeck.GetCount(), 1);
    CHECK_EQ(opDeck[0]->card->name, "Ancient Curse");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1]
// - Race: Murloc, Set: LoE, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOEA10_3 : Murloc Tinyfin")
{
    // Do nothing
}