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

// ------------------------------------------ MINION - MAGE
// [TSC_029] Gaia, the Techtonic - COST:8 [ATK:5/HP:7]
// - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Colossal +2</b>
//       After a friendly Mech attacks,
//       deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - COLOSSAL = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - TSC_029 : Gaia, the Techtonic")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Gaia, the Techtonic"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, AttackTask(curField[0], card2));
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(curPlayer, AttackTask(curField[1], card2));
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ------------------------------------------ MINION - MAGE
// [TSC_054] Mecha-Shark - COST:3 [ATK:4/HP:3]
// - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: After you summon a Mech,
//       deal 3 damage randomly split among all enemies.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - TSC_054 : Mecha-Shark")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mecha-Shark"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naval Mine"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    const int totalHealth =
        opPlayer->GetHero()->GetHealth() + opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 39);
}

// ------------------------------------------- SPELL - MAGE
// [TSC_055] Seafloor Gateway - COST:3
// - Set: THE_SUNKEN_CITY, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a Mech.
//       Reduce the Cost of Mechs in your hand by (1).
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - TSC_055 : Seafloor Gateway")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Naval Mine");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Seafloor Gateway"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naval Mine"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 9);
    CHECK_EQ(curHand[6]->card->name, "Naval Mine");
    CHECK_EQ(curHand[6]->GetCost(), 1);
}

// ------------------------------------------ MINION - MAGE
// [TSC_776] Azsharan Sweeper - COST:3 [ATK:3/HP:4]
// - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b>
//       Put a 'Sunken Sweeper' on the bottom of your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - TSC_776 : Azsharan Sweeper")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Naval Mine");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azsharan Sweeper"));
    // Sunken Sweeper (TSC_776t)
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("TSC_776t"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 27);
    CHECK_EQ(curDeck.GetBottomCard()->card->name, "Sunken Sweeper");

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::MECHANICAL);
    CHECK_EQ(curHand[5]->card->GetRace(), Race::MECHANICAL);
    CHECK_EQ(curHand[6]->card->GetRace(), Race::MECHANICAL);
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

// ---------------------------------------- SPELL - PALADIN
// [TSC_076] Immortalized in Stone - COST:7
// - Set: THE_SUNKEN_CITY, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Summon a 1/2, 2/4 and 4/8 Elemental with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - TSC_076 : Immortalized in Stone")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = true;
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
        curPlayer, Cards::FindCardByName("Immortalized in Stone"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 8);
    CHECK_EQ(curField[2]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - ROGUE
// [TSC_916] Gone Fishin' - COST:1
// - Set: THE_SUNKEN_CITY, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Dredge</b>.
//       <b>Combo:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// - DREDGE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - TSC_916 : Gone Fishin'")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::HUNTER;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gone Fishin'"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gone Fishin'"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto firstChoice = game.entityList[curPlayer->choice->choices[0]];
    auto secondChoice = game.entityList[curPlayer->choice->choices[1]];
    auto thirdChoice = game.entityList[curPlayer->choice->choices[2]];
    CHECK_EQ(firstChoice->card->name, "Pyroblast");
    CHECK_EQ(secondChoice->card->name, "Wisp");
    CHECK_EQ(thirdChoice->card->name, "Frostbolt");

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetTopCard()->card->name, "Pyroblast");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    firstChoice = game.entityList[curPlayer->choice->choices[0]];
    secondChoice = game.entityList[curPlayer->choice->choices[1]];
    thirdChoice = game.entityList[curPlayer->choice->choices[2]];
    CHECK_EQ(firstChoice->card->name, "Wisp");
    CHECK_EQ(secondChoice->card->name, "Frostbolt");
    CHECK_EQ(thirdChoice->card->name, "Malygos");

    TestUtils::ChooseNthChoice(game, 3);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Malygos");
    CHECK_EQ(curDeck.GetTopCard()->card->name, "Pyroblast");
}

// ------------------------------------------ SPELL - ROGUE
// [TSC_932] Blood in the Water - COST:6
// - Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage to an enemy.
//       Summon a 5/5 Shark with <b>Rush</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_ENEMY_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - TSC_932 : Blood in the Water")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blood in the Water"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Tiger Shark");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[0]->HasRush(), true);
}

// ----------------------------------------- MINION - ROGUE
// [TSC_963] Filletfighter - COST:1 [ATK:3/HP:1]
// - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - TSC_963 : Filletfighter")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Filletfighter"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [TSC_941] Guard the City - COST:2
// - Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: Gain 3 Armor.
//       Summon a 2/3 Naga with <b>Taunt</b>.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - TSC_941 : Guard the City")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Guard the City"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Naga Centaur");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasTaunt(), true);
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
// [TSC_001] Naval Mine - COST:2 [ATK:0/HP:2]
// - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 4 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_001 : Naval Mine")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naval Mine"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [TSC_002] Pufferfist - COST:3 [ATK:3/HP:3]
// - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: After your hero attacks, deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_002 : Pufferfist")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pufferfist"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opField[0]->GetHealth(), 11);
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
// [TSC_053] Rainbow Glowscale - COST:2 [ATK:2/HP:3]
// - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_053 : Rainbow Glowscale")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [TSC_065] Helmet Hermit - COST:1 [ATK:4/HP:3]
// - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_065 : Helmet Hermit")
{
    // Do nothing
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

// --------------------------------------- MINION - NEUTRAL
// [TSC_938] Treasure Guard - COST:3 [ATK:1/HP:5]
// - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - TSC_938 : Treasure Guard")
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

    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Treasure Guard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 5);
}