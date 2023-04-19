// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [UNG_108] Earthen Scales - COST:2
// - Faction: Neutral, Set: Ungoro, Rarity: Rare
// --------------------------------------------------------
// Text: Give a friendly minion +1/+1,
//       then gain Armor equal to its Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - UNG_108 : Earthen Scales")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earthen Scales"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);
}

// ----------------------------------------- MINION - DRUID
// [UNG_852] Tyrantus - COST:10 [ATK:12/HP:12]
// - Race: Beast, Set: Ungoro, Rarity: Legendary
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Druid] - UNG_852 : Tyrantus")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tyrantus"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);
    CHECK_EQ(opPlayer->GetHero()->heroPower->IsExhausted(), false);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);
    CHECK_EQ(opHand.GetCount(), 7);
}

// ---------------------------------------- MINION - HUNTER
// [UNG_912] Jeweled Macaw - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Beast to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - UNG_912 : Jeweled Macaw")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jeweled Macaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::BEAST);
}
// ---------------------------------------- MINION - HUNTER
// [UNG_914] Raptor Hatchling - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: Ungoro, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle a 4/3 Raptor
//       into your deck.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - UNG_914 : Raptor Hatchling")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Raptor Hatchling"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curDeck[0]->card->name, "Raptor Patriarch");
}


// ------------------------------------------ MINION - MAGE
// [UNG_020] Arcanologist - COST:2 [ATK:2/HP:3]
// - Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a <b>Secret</b> from your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - UNG_020 : Arcanologist")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Young Dragonhawk");
        config.player1Deck[i + 2] = Cards::FindCardByName("Ice Barrier");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcanologist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsSecret(), true);
}

// ---------------------------------------- MINION - PRIEST
// [UNG_034] Radiant Elemental - COST:2 [ATK:2/HP:3]
// - Race: Elemental, Faction: Neutral, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: Your spells cost (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - UNG_034 : Radiant Elemental")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Radiant Elemental"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Radiant Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
}

// ---------------------------------------- MINION - PRIEST
// [UNG_963] Lyra the Sunshard - COST:5 [ATK:3/HP:5]
// - Race: Elemental, Set: Ungoro, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       add a random Priest spell to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - UNG_963 : Lyra the Sunshard")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lyra the Sunshard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::PRIEST);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
}

// ----------------------------------------- MINION - ROGUE
// [UNG_058] Razorpetal Lasher - COST:2 [ATK:2/HP:2]
// - Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a Razorpetal to your hand
//       that deals 1 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - UNG_058 : Razorpetal Lasher")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razorpetal Lasher"));
    
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Razorpetal");
}

// ------------------------------------------ SPELL - ROGUE
// [UNG_057] Razorpetal Volley - COST:2
// - Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: Add two Razorpetals to_your hand that deal 1 damage.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - UNG_057 : Razorpetal Volley")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Razorpetal Volley"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Razorpetal");
    CHECK_EQ(curHand[5]->card->name, "Razorpetal");

    game.Process(curPlayer,
        PlayCardTask::SpellTarget(curHand[4], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
}

// ----------------------------------------- SPELL - SHAMAN
// [UNG_817] Tidal Surge - COST:3
// - Faction: Neutral, Set: Ungoro, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 4 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - UNG_817 : Tidal Surge")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tidal Surge"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [UNG_833] Lakkari Felhound - COST:4 [ATK:3/HP:8]
// - Race: Demon, Faction: Neutral, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Discard your two lowest-Cost cards.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - UNG_833 : Lakkari Felhound")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lakkari Felhound"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    [[maybe_unused]] const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Pyroblast");
    CHECK_EQ(curHand[1]->card->name, "Malygos");
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_083] Devilsaur Egg - COST:3 [ATK:0/HP:3]
// - Set: Ungoro, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 5/5 Devilsaur.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_083 : Devilsaur Egg")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Devilsaur Egg"));
    const auto card2 = 
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->name, "Devilsaur Egg");
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Devilsaur");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_806] Ultrasaur - COST:10 [ATK:7/HP:14]
// - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_806 : Ultrasaur")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_809] Fire Fly - COST:1 [ATK:1/HP:2]
// - Race: Elemental, Faction: Alliance, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry</b>: Add a 1/2 Elemental to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_809 : Fire Fly")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Fly"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Flame Elemental");
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_813] Stormwatcher - COST:7 [ATK:4/HP:8]
// - Race: Elemental, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_813 : Stormwatcher")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_844] Humongous Razorleaf - COST:3 [ATK:4/HP:8]
// - Faction: Alliance, Set: Ungoro, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_844 : Humongous Razorleaf")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_848] Primordial Drake - COST:8 [ATK:4/HP:8]
// - Race: Dragon, Set: Ungoro, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 2 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_848 : Primordial Drake")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Primordial Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(opField[0]->GetHealth(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [UNG_928] Tar Creeper - COST:3 [ATK:1/HP:5]
// - Race: Elemental, Set: Ungoro, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Has +2 Attack during your opponent's turn.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - UNG_928 : Tar Creeper")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tar Creeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}