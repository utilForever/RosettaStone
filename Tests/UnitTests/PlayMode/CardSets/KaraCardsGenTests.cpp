// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [KAR_065] Menagerie Warden - COST:5 [ATK:4/HP:4]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly Beast.
//       Summon a copy of it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_WITH_RACE = 20
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - KAR_065 : Menagerie Warden")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Menagerie Warden"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Bloodfen Raptor");
    CHECK_EQ(curField[1]->card->name, "Faerie Dragon");
    CHECK_EQ(curField[2]->card->name, "Menagerie Warden");
    CHECK_EQ(curField[3]->card->name, "Bloodfen Raptor");
}

// ------------------------------------------ SPELL - DRUID
// [KAR_075] Moonglade Portal - COST:6
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: Restore 6 Health. Summon a random 6-Cost minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - KAR_075 : Moonglade Portal")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonglade Portal"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 6);
}

// ----------------------------------------- MINION - DRUID
// [KAR_300] Enchanted Raven - COST:1 [ATK:2/HP:2]
// - Race: Beast, Set: Kara, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - KAR_300 : Enchanted Raven")
{
    // Do nothing
}

// ----------------------------------------- SPELL - HUNTER
// [KAR_004] Cat Trick - COST:2
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent casts a spell,
//       summon a 4/2 Panther with <b>Stealth</b>.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - KAR_004 : Cat Trick")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cat Trick"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Intellect"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Cat in a Hat");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasStealth(), true);
}

// ---------------------------------------- MINION - HUNTER
// [KAR_005] Kindly Grandmother - COST:2 [ATK:1/HP:1]
// - Race: Beast, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 3/2 Big Bad Wolf.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - KAR_005 : Kindly Grandmother")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kindly Grandmother"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Big Bad Wolf");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ---------------------------------------- MINION - HUNTER
// [KAR_006] Cloaked Huntress - COST:3 [ATK:3/HP:4]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Your <b>Secrets</b> cost (0).
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - KAR_006 : Cloaked Huntress")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cloaked Huntress"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snake Trap"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(card2->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 2);
}

// ------------------------------------------ MINION - MAGE
// [KAR_009] Babbling Book - COST:1 [ATK:1/HP:1]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Mage spell to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - KAR_009 : Babbling Book")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Babbling Book"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
    CHECK(curHand[0]->card->IsCardClass(CardClass::MAGE));
}

// ------------------------------------------- SPELL - MAGE
// [KAR_076] Firelands Portal - COST:7
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Deal 5 damage. Summon a random 5-Cost minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - KAR_076 : Firelands Portal")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Firelands Portal"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 5);
}

// ------------------------------------------ MINION - MAGE
// [KAR_092] Medivh's Valet - COST:2 [ATK:2/HP:3]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       deal 3 damage.
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
TEST_CASE("[Mage : Minion] - KAR_092 : Medivh's Valet")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Medivh's Valet"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Medivh's Valet"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Ward"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - PALADIN
// [KAR_010] Nightbane Templar - COST:3 [ATK:2/HP:3]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       summon two 1/1 Whelps.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - KAR_010 : Nightbane Templar")
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
        curPlayer, Cards::FindCardByName("Nightbane Templar"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nightbane Templar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Whelp");
    CHECK_EQ(curField[2]->card->name, "Whelp");

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 5);
}

// --------------------------------------- MINION - PALADIN
// [KAR_057] Ivory Knight - COST:6 [ATK:4/HP:4]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a spell.
//       Restore Health to your hero equal to its Cost.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - KAR_057 : Ivory Knight")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ivory Knight"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::PALADIN), true);
    }

    const int cost = cards[0]->GetCost();

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20 + cost);
}

// ---------------------------------------- SPELL - PALADIN
// [KAR_077] Silvermoon Portal - COST:4
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +2/+2.
//       Summon a random 2-Cost minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - KAR_077 : Silvermoon Portal")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Silvermoon Portal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->card->GetCost(), 2);
}

// ----------------------------------------- SPELL - PRIEST
// [KAR_013] Purify - COST:2
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Silence</b> a friendly minion. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - KAR_013 : Purify")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Purify"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(curHand.GetCount(), 5);
}

// ---------------------------------------- MINION - PRIEST
// [KAR_035] Priest of the Feast - COST:4 [ATK:3/HP:6]
// - Faction: Neutral, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       restore 3 Health to your hero.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - KAR_035 : Priest of the Feast")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Priest of the Feast"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Circle of Healing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
}

// ---------------------------------------- MINION - PRIEST
// [KAR_204] Onyx Bishop - COST:5 [ATK:3/HP:4]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a friendly minion
//       that died this game.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - KAR_204 : Onyx Bishop")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Onyx Bishop"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Stonetusk Boar");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ----------------------------------------- MINION - ROGUE
// [KAR_069] Swashburglar - COST:1 [ATK:1/HP:1]
// - Race: Pirate, Faction: Neutral, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random card
//       from another class to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - KAR_069 : Swashburglar")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swashburglar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK(curHand[0]->card->IsCardClass(CardClass::HUNTER));
}

// ----------------------------------------- MINION - ROGUE
// [KAR_070] Ethereal Peddler - COST:5 [ATK:5/HP:6]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding any non-Rogue
//       class cards, reduce their Cost by (2).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - KAR_070 : Ethereal Peddler")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ethereal Peddler"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Assassinate"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 2);
}

// ----------------------------------------- MINION - ROGUE
// [KAR_094] Deadly Fork - COST:3 [ATK:3/HP:2]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a 3/2 weapon to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - KAR_094 : Deadly Fork")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Fork"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Sharp Fork");
}

// ---------------------------------------- MINION - SHAMAN
// [KAR_021] Wicked Witchdoctor - COST:4 [ATK:3/HP:4]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       summon a random basic Totem.
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - KAR_021 : Wicked Witchdoctor")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wicked Witchdoctor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Totemic Might"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);

    const bool isBasicTotem =
        curField[1]->card->dbfID == 537 || curField[1]->card->dbfID == 850 ||
        curField[1]->card->dbfID == 62320 || curField[1]->card->dbfID == 764;
    CHECK(isBasicTotem);
}

// ---------------------------------------- WEAPON - SHAMAN
// [KAR_063] Spirit Claws - COST:2 [ATK:1/HP:0]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Has +2 Attack while you have <b>Spell Damage</b>.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - KAR_063 : Spirit Claws")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spirit Claws"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [KAR_073] Maelstrom Portal - COST:2
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions.
//       Summon a random 1-Cost minion.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - KAR_073 : Maelstrom Portal")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Maelstrom Portal"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ---------------------------------------- SPELL - WARLOCK
// [KAR_025] Kara Kazham! - COST:5
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Summon a 1/1 Candle, 2/2 Broom, and 3/3 Teapot.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - KAR_025 : Kara Kazham!")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kara Kazham!"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Candle");
    CHECK_EQ(curField[1]->card->name, "Broom");
    CHECK_EQ(curField[2]->card->name, "Teapot");
}

// --------------------------------------- MINION - WARLOCK
// [KAR_089] Malchezaar's Imp - COST:1 [ATK:1/HP:3]
// - Race: Demon, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you discard a card, draw a card.
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - KAR_089 : Malchezaar's Imp")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malchezaar's Imp"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 4);
}

// --------------------------------------- MINION - WARLOCK
// [KAR_205] Silverware Golem - COST:3 [ATK:3/HP:3]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: If you discard this minion, summon it.
// --------------------------------------------------------
// GameTag:
// - InvisibleDeathrattle = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - KAR_205 : Silverware Golem")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto& curField = *(curPlayer->GetFieldZone());

    [[maybe_unused]] const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Silverware Golem"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Silverware Golem");
}

// ---------------------------------------- SPELL - WARRIOR
// [KAR_026] Protect the King! - COST:3
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: For each enemy minion,
//       summon a 1/1 Pawn with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - KAR_026 : Protect the King!")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Protect the King!"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Kara Kazham!"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Pawn");
    CHECK_EQ(curField[1]->card->name, "Pawn");
    CHECK_EQ(curField[2]->card->name, "Pawn");
}

// --------------------------------------- WEAPON - WARRIOR
// [KAR_028] Fool's Bane - COST:5 [ATK:3/HP:0]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Unlimited attacks each turn. Can't attack heroes.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 4
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - KAR_028 : Fool's Bane")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fool's Bane"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sleepy Dragon"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);
    CHECK_EQ(curPlayer->GetHero()->IsExhausted(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);
    CHECK_EQ(curPlayer->GetHero()->IsExhausted(), false);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
    CHECK_EQ(curPlayer->GetHero()->IsExhausted(), false);
}

// ---------------------------------------- SPELL - WARRIOR
// [KAR_091] Ironforge Portal - COST:5
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: Gain 4 Armor. Summon a random 4-Cost minion.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - KAR_091 : Ironforge Portal")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironforge Portal"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_011] Pompous Thespian - COST:2 [ATK:3/HP:2]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_011 : Pompous Thespian")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_029] Runic Egg - COST:1 [ATK:0/HP:2]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_029 : Runic Egg")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Runic Egg"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_030a] Pantry Spider - COST:3 [ATK:1/HP:3]
// - Race: Beast, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/3 Spider.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_030a : Pantry Spider")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pantry Spider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Cellar Spider");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_033] Book Wyrm - COST:6 [ATK:3/HP:6]
// - Race: Dragon, Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       destroy an enemy minion with 3 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NONSELF_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_MAX_ATTACK = 3
// - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_033 : Book Wyrm")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Book Wyrm"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Book Wyrm"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ethereal Peddler"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card5));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(opField.GetCount(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_036] Arcane Anomaly - COST:1 [ATK:2/HP:1]
// - Race: Elemental, Faction: Neutral, Set: Kara, Rarity: common
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       give this minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Netural : Minion] - KAR_036 : Arcane Anomaly")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Anomaly"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_037] Avian Watcher - COST:5 [ATK:3/HP:6]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       gain +1/+1 and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Netural : Minion] - KAR_037 : Avian Watcher")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Avian Watcher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Avian Watcher"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_041] Moat Lurker - COST:6 [ATK:3/HP:3]
// - Set: Kara, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a minion.
//       <b>Deathrattle:</b> Resummon it.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Netural : Minion] - KAR_041 : Moat Lurker")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moat Lurker"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Holy Smite"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_044] Moroes - COST:3 [ATK:1/HP:1]
// - Set: Kara, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       At the end of your turn, summon a 1/1 Steward.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Netural : Minion] - KAR_044 : Moroes")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moroes"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Steward");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_061] The Curator - COST:7 [ATK:4/HP:6]
// - Race: Mechanical, Set: Kara, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> Draw a Beast,
//       Dragon, and Murloc from your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_061 : The Curator")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 5)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Murloc Tinyfin");
        config.player1Deck[i + 2] = Cards::FindCardByName("Faerie Dragon");
        config.player1Deck[i + 3] = Cards::FindCardByName("Voidwalker");
        config.player1Deck[i + 4] = Cards::FindCardByName("Bloodsail Raider");
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Curator"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 23);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::BEAST);
    CHECK_EQ(curHand[5]->card->GetRace(), Race::DRAGON);
    CHECK_EQ(curHand[6]->card->GetRace(), Race::MURLOC);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_062] Netherspite Historian - COST:2 [ATK:1/HP:3]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_062 : Netherspite Historian")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Netherspite Historian"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Netherspite Historian"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_095] Zoobot - COST:3 [ATK:3/HP:3]
// - Race: Mechanical, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random friendly Beast,
//       Dragon, and Murloc +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_095 : Zoobot")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Zoobot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodsail Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 3);
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_096] Prince Malchezaar - COST:5 [ATK:5/HP:6]
// - Race: Demon, Set: Kara, Rarity: Legendary
// --------------------------------------------------------
// Text: When the game starts,
//       add 5 extra <b>Legendary</b> minions to your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_096 : Prince Malchezaar")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Prince Malchezaar");

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

    CHECK_EQ(curDeck.GetCount(), 4);
    CHECK_EQ(curHand.GetCount(), 2);

    for (auto& deckCard : curDeck.GetAll())
    {
        CHECK_EQ(deckCard->card->GetCardType(), CardType::MINION);
        CHECK_EQ(deckCard->card->GetRarity(), Rarity::LEGENDARY);
    }

    for (auto& handCard : curHand.GetAll())
    {
        CHECK_EQ(handCard->card->GetCardType(), CardType::MINION);
        CHECK_EQ(handCard->card->GetRarity(), Rarity::LEGENDARY);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_097] Medivh, the Guardian - COST:8 [ATK:7/HP:7]
// - Set: Kara, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b>
//       Equip Atiesh, Greatstaff of the Guardian.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_097 : Medivh, the Guardian")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Medivh, the Guardian"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetCost(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_114] Barnes - COST:4 [ATK:3/HP:4]
// - Set: Kara, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 copy of
//       a random minion in your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_114 : Barnes")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::HUNTER;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Barnes"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Malygos");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_702] Menagerie Magician - COST:5 [ATK:4/HP:4]
// - Faction: Neutral, Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a random friendly Beast,
//       Dragon, and Murloc +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_702 : Menagerie Magician")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Menagerie Magician"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodsail Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_710] Arcanosmith - COST:4 [ATK:3/HP:2]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 0/5 minion with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_710 : Arcanosmith")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcanosmith"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Animated Shield");
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_711] Arcane Giant - COST:12 [ATK:8/HP:8]
// - Set: Kara, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each spell you've cast this game.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_711 : Arcane Giant")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));

    CHECK_EQ(card1->GetCost(), 12);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card1->GetCost(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [KAR_712] Violet Illusionist - COST:3 [ATK:4/HP:3]
// - Set: Kara, Rarity: Common
// --------------------------------------------------------
// Text: During your turn, your hero is <b>Immune</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - KAR_712 : Violet Illusionist")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Violet Illusionist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Medivh, the Guardian"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
}
