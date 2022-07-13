// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- MINION - DRUID
// [TSC_026] Colaque - COST:7 [ATK:6/HP:5]
// - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Colossal +1</b>
//       <b>Immune</b> while you control Colaque's Shell.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - COLOSSAL = 1
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - TSC_026 : Colaque")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Colaque"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->IsImmune(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, curField[1]));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
    CHECK_EQ(curField[0]->IsImmune(), false);
}

// ------------------------------------------ SPELL - DRUID
// [TSC_650] Flipper Friends - COST:5
// - Set: THE_SUNKEN_CITY, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One</b> -
//       Summon a 6/6 Orca with <b>Taunt</b>;
//       or six 1/1 Otters with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - TSC_650 : Flipper Friends")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flipper Friends"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flipper Friends"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Orca");
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[1]->card->name, "Otter");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[2]->card->name, "Otter");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->HasRush(), true);
    CHECK_EQ(curField[3]->card->name, "Otter");
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[3]->HasRush(), true);
    CHECK_EQ(curField[4]->card->name, "Otter");
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[4]->HasRush(), true);
    CHECK_EQ(curField[5]->card->name, "Otter");
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
    CHECK_EQ(curField[5]->HasRush(), true);
    CHECK_EQ(curField[6]->card->name, "Otter");
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);
    CHECK_EQ(curField[6]->HasRush(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [TSC_072] Conch's Call - COST:3
// - Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: Draw a Naga and a spell.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - TSC_072 : Conch's Call")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Rainbow Glowscale");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Conch's Call"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Rainbow Glowscale");
    CHECK_EQ(curHand[5]->card->name, "Fireball");
}

// ----------------------------------------- SPELL - HUNTER
// [TSC_947] Naga's Pride - COST:3
// - Set: THE_SUNKEN_CITY, Rarity: Rare
// --------------------------------------------------------
// Text: Summon two 2/2 Lionfish.
//       If you played a Naga while holding this,
//       give them +1/+1.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - TSC_947 : Naga's Pride")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naga's Pride"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naga's Pride"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rainbow Glowscale"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Lionfish");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Lionfish");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[3]->card->name, "Lionfish");
    CHECK_EQ(curField[3]->GetAttack(), 3);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(curField[4]->card->name, "Lionfish");
    CHECK_EQ(curField[4]->GetAttack(), 3);
    CHECK_EQ(curField[4]->GetHealth(), 3);
}

// --------------------------------------- MINION - PALADIN
// [TSC_030] The Leviathan - COST:7 [ATK:4/HP:5]
// - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Colossal +1</b>
//       <b>Rush</b>, <b>Divine Shield</b>
//       After this attacks, <b>Dredge</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - COLOSSAL = 1
// - DIVINE_SHIELD = 1
// - DREDGE = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - TSC_030 : The Leviathan")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 5)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Frostbolt");
        config.player1Deck[i + 3] = Cards::FindCardByName("Wisp");
        config.player1Deck[i + 4] = Cards::FindCardByName("Pyroblast");
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
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Leviathan"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 8);
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto firstChoice = game.entityList[curPlayer->choice->choices[0]];
    auto secondChoice = game.entityList[curPlayer->choice->choices[1]];
    auto thirdChoice = game.entityList[curPlayer->choice->choices[2]];
    CHECK_EQ(firstChoice->card->name, "Pyroblast");
    CHECK_EQ(secondChoice->card->name, "Wisp");
    CHECK_EQ(thirdChoice->card->name, "Frostbolt");

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curDeck.GetTopCard()->card->name, "Pyroblast");

    game.Process(curPlayer, AttackTask(curField[1], card2));
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Pyroblast");
}

// ------------------------------------ SPELL - DEMONHUNTER
// [TSC_058] Predation - COST:3
// - Set: THE_SUNKEN_CITY, Rarity: Rare
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 3 damage.
//       Costs (0) if you played a Naga while holding this.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - TSC_058 : Predation")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DEMONHUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Predation"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Predation"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rainbow Glowscale"));

    CHECK_EQ(card1->GetCost(), 3);
    CHECK_EQ(card2->GetCost(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(card2->GetCost(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);
}

// --------------------------------------- MINION - NEUTRAL
// [TSC_017] Baba Naga - COST:4 [ATK:4/HP:4]
// - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've cast
//       a spell while holding this, deal 3 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_017 : Baba Naga")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Baba Naga"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Baba Naga"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
}

// --------------------------------------- MINION - NEUTRAL
// [TSC_909] Tuskarrrr Trawler - COST:2 [ATK:2/HP:3]
// - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Dredge</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DREDGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_909 : Tuskarrrr Trawler")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 5)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Frostbolt");
        config.player1Deck[i + 3] = Cards::FindCardByName("Wisp");
        config.player1Deck[i + 4] = Cards::FindCardByName("Pyroblast");
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tuskarrrr Trawler"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto firstChoice = game.entityList[curPlayer->choice->choices[0]];
    auto secondChoice = game.entityList[curPlayer->choice->choices[1]];
    auto thirdChoice = game.entityList[curPlayer->choice->choices[2]];
    CHECK_EQ(firstChoice->card->name, "Pyroblast");
    CHECK_EQ(secondChoice->card->name, "Wisp");
    CHECK_EQ(thirdChoice->card->name, "Frostbolt");

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curDeck.GetTopCard()->card->name, "Pyroblast");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Pyroblast");
}