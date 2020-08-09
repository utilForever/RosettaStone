// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [ULD_131] Untapped Potential - COST:1
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Quest:</b> End 4 turns with any unspent Mana.
//       <b>Reward:</b> Ossirian Tear.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - QUEST = 1
// - QUEST_PROGRESS_TOTAL = 4
// - 676 = 1
// - 839 = 1
// - QUEST_REWARD_DATABASE_ID = 53499
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - ULD_131 : Untapped Potential")
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
    curPlayer->SetTotalMana(1);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Untapped Potential"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Claw"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfall"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(quest->GetQuestProgress(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK(curSecret->quest == nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 4);
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->id, "ULD_131p");

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasCharge(), true);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card4));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ----------------------------------------- MINION - DRUID
// [ULD_133] Crystal Merchant - COST:2 [ATK:1/HP:4]
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: If you have any unspent Mana at the end of your turn,
//       draw a card.
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - ULD_133 : Crystal Merchant")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Merchant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(opHand.GetCount(), 7);
}

// ------------------------------------------ SPELL - DRUID
// [ULD_134] BEEEES!!! - COST:3 [ATK:1/HP:4]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: Choose a minion. Summon four 1/1 Bees that attack it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - ULD_134 : BEEEES!!!")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostwolf Grunt"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("BEEEES!!!"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Bee");
}

// ------------------------------------------ SPELL - DRUID
// [ULD_135] Hidden Oasis - COST:6
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Choose One</b> - Summon a 6/6 Ancient with <b>Taunt</b>;
//       or Restore 12 Health.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - ULD_135 : Hidden Oasis")
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
    curPlayer->GetHero()->SetDamage(15);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hidden Oasis"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hidden Oasis"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero(), 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Vir'naal Ancient");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero(), 2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
}

// ------------------------------------------ SPELL - DRUID
// [ULD_136] Worthy Expedition - COST:1
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> a <b>Choose One</b> card.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - ULD_136 : Worthy Expedition")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Worthy Expedition"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->HasGameTag(GameTag::CHOOSE_ONE), true);
    }
}

// ----------------------------------------- MINION - DRUID
// [ULD_137] Garden Gnome - COST:4 [ATK:2/HP:3]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a spell that
//       costs (5) or more, summon two 2/2 Treants.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - ULD_137 : Garden Gnome")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Garden Gnome"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Garden Gnome"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[1]->card->name, "Garden Gnome");
    CHECK_EQ(curField[2]->card->name, "Treant");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->card->name, "Garden Gnome");
}

// ----------------------------------------- MINION - DRUID
// [ULD_138] Anubisath Defender - COST:5 [ATK:3/HP:5]
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>. Costs (0) if you've cast a spell that
//       costs (5) or more this turn.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - ULD_138 : Anubisath Defender")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Anubisath Defender"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfire"));

    CHECK_EQ(card1->GetCost(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(card1->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 5);
}

// ----------------------------------------- MINION - DRUID
// [ULD_139] Elise the Enlightened - COST:5 [ATK:5/HP:5]
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       duplicate your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - ULD_139 : Elise the Enlightened")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Elise the Enlightened"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
    [[maybe_unused]] const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wrath"));
    [[maybe_unused]] const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Acornbearer"));
    [[maybe_unused]] const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbark Protector"));

    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(curHand[6]->card->name, "Wisp");
    CHECK_EQ(curHand[7]->card->name, "Wolfrider");
    CHECK_EQ(curHand[8]->card->name, "Moonfire");
    CHECK_EQ(curHand[9]->card->name, "Wrath");
}

// ---------------------------------------- SPELL - PALADIN
// [ULD_143] Pharaoh's Blessing - COST:6
// - Faction: Neutral, Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +4/+4, <b>Divine Shield</b>,
//       and <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[PALADIN : Spell] - ULD_143 : Pharaoh's Blessing")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pharaoh's Blessing"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    auto& curField = *(curPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 1);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ------------------------------------------ SPELL - DRUID
// [ULD_273] Overflow - COST:7
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Restore 5 Health to all characters. Draw 5 cards.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - ULD_273 : Overflow")
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
            Cards::FindCardByName("Magma Rager");
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
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(opHand.GetCount(), 6);
}

// ----------------------------------------- MINION - DRUID
// [ULD_292] Oasis Surger - COST:5 [ATK:3/HP:3]
// - Race: Elemental, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Choose One -</b> Gain +2/+2;
//       or Summon a copy of this minion.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - ULD_292 : Oasis Surger")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Surger"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Surger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// ---------------------------------------- MINION - HUNTER
// [ULD_151] Ramkahen Wildtamer - COST:3 [ATK:4/HP:3]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Copy a random Beast in your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ULD_151 : Ramkahen Wildtamer")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ramkahen Wildtamer"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Young Dragonhawk"));

    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    const bool check = curHand[3]->card->name == "River Crocolisk" ||
                       curHand[3]->card->name == "Young Dragonhawk";
    CHECK_EQ(check, true);
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
TEST_CASE("[Hunter : Spell] - ULD_152 : Pressure Plate")
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

    auto& curSecret = *(curPlayer->GetSecretZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pressure Plate"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(card1->GetGameTag(GameTag::REVEALED), 0);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(card1->GetGameTag(GameTag::REVEALED), 1);
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- MINION - HUNTER
// [ULD_154] Hyena Alpha - COST:4 [ATK:3/HP:3]
// - Race: Beast, Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       summon two 2/2 Hyenas.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ULD_154 : Hyena Alpha")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Redemption"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Redemption"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hyena Alpha"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hyena Alpha"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opPlayer->GetSecretZone()->GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 4);
    CHECK_EQ(opField[0]->card->name, "Hyena Alpha");
    CHECK_EQ(opField[2]->card->name, "Hyena Alpha");
    CHECK_EQ(opField[1]->GetAttack(), 2);
    CHECK_EQ(opField[1]->GetHealth(), 2);
    CHECK_EQ(opField[1]->card->name, "Hyena");
    CHECK_EQ(opField[3]->GetAttack(), 2);
    CHECK_EQ(opField[3]->GetHealth(), 2);
    CHECK_EQ(opField[3]->card->name, "Hyena");
}

// ----------------------------------------- SPELL - HUNTER
// [ULD_155] Unseal the Vault - COST:1
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Quest:</b> Summon 20 minions.
//       <b>Reward:</b> Ramkahen Roar.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - QUEST = 1
// - QUEST_PROGRESS_TOTAL = 20
// - 676 = 1
// - 839 = 1
// - QUEST_REWARD_DATABASE_ID = 53925
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - ULD_155 : Unseal the Vault")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.doShuffle = false;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Unseal the Vault"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetSecretZone()->quest->card->name, "Unseal the Vault");

    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            game.Process(curPlayer,
                         PlayCardTask::Minion(Generic::DrawCard(
                             curPlayer, Cards::FindCardByName("Wisp"))));
        }
        CHECK_EQ(card1->GetGameTag(GameTag::QUEST_PROGRESS), i * 5);
        CHECK_EQ(curField.GetCount(), 5);

        game.Process(curPlayer,
                     PlayCardTask::Spell(Generic::DrawCard(
                         curPlayer, Cards::FindCardByName("Twisting Nether"))));
        CHECK_EQ(curField.GetCount(), 0);

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        game.Process(opPlayer, PlayCardTask::Minion(Generic::DrawCard(
                                   opPlayer, Cards::FindCardByName("Wisp"))));
        CHECK_EQ(card1->GetGameTag(GameTag::QUEST_PROGRESS), i * 5);

        game.Process(opPlayer,
                     PlayCardTask::Spell(Generic::DrawCard(
                         opPlayer, Cards::FindCardByName("Twisting Nether"))));
        CHECK_EQ(opField.GetCount(), 0);

        game.Process(opPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);
    }
    CHECK_EQ(curPlayer->GetHeroPower().card->name, "Pharaoh's Warmask");

    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [ULD_156] Dinotamer Brann - COST:7 [ATK:2/HP:4]
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       summon King Krush.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ULD_156 : Dinotamer Brann")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 6; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dinotamer Brann"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dinotamer Brann"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 0));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Dinotamer Brann");
    CHECK_EQ(curField[1]->card->name, "King Krush");
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[1]->HasCharge(), true);
    CHECK_EQ(curField[2]->card->name, "Dinotamer Brann");
}

// ---------------------------------------- MINION - HUNTER
// [ULD_212] Wild Bloodstinger - COST:6 [ATK:6/HP:9]
// - Race: Beast, Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a minion from
//       your opponent's hand. Attack it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ULD_212 : Wild Bloodstinger")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 6; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wild Bloodstinger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// ---------------------------------------- MINION - HUNTER
// [ULD_410] Scarlet Webweaver - COST:6 [ATK:5/HP:5]
// - Race: Beast, Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Reduce the Cost of a random Beast
//       in your hand by (5).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ULD_410 : Scarlet Webweaver")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Scarlet Webweaver"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("King Krush"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 9);
}

// ----------------------------------------- SPELL - HUNTER
// [ULD_429] Hunter's Pack - COST:3
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: Add a random Hunter Beast, <b>Secret</b>,
//       and weapon to your hand.
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - ULD_429 : Hunter's Pack")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hunter's Pack"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::HUNTER);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::BEAST);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::HUNTER);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[1]->card->IsSecret(), true);
    CHECK_EQ(curHand[2]->card->GetCardClass(), CardClass::HUNTER);
    CHECK_EQ(curHand[2]->card->GetCardType(), CardType::WEAPON);
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
TEST_CASE("[Hunter : Weapon] - ULD_430 : Desert Spear")
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
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curField[1]->card->name, "Locust");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->IsRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card3));
    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- SPELL - HUNTER
// [ULD_713] Swarm of Locusts - COST:6
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Summon seven 1/1 Locusts with <b>Rush</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - ULD_713 : Swarm of Locusts")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swarm of Locusts"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    for (int i = 0; i < 7; ++i)
    {
        CHECK_EQ(curField[i]->card->name, "Locust");
        CHECK_EQ(curField[i]->GetAttack(), 1);
        CHECK_EQ(curField[i]->GetHealth(), 1);
        CHECK_EQ(curField[i]->IsRush(), true);
    }
}

// ------------------------------------------- SPELL - MAGE
// [ULD_216] Puzzle Box of Yogg-Saron - COST:10
// - Faction: Neutral, Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: Cast 10 random spells <i>(targets chosen randomly).</i>
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - ULD_216 : Puzzle Box of Yogg-Saron")
{
    for (int i = 0; i < 100; ++i)
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

        const auto card1 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Puzzle Box of Yogg-Saron"));

        game.Process(curPlayer, PlayCardTask::Spell(card1));
        CHECK_EQ(curPlayer->GetGameTag(GameTag::CAST_RANDOM_SPELLS), 0);
        CHECK_EQ(curPlayer->GetNumSpellsPlayedThisTurn(), 1);
    }
}

// ------------------------------------------ MINION - MAGE
// [ULD_236] Tortollan Pilgrim - COST:8 [ATK:5/HP:5]
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry</b>: <b>Discover</b> a copy of
//       a spell in your deck and cast it with random targets.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - ULD_236 : Tortollan Pilgrim")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 1] = Cards::FindCardByName("Frostbolt");
        config.player1Deck[i + 2] = Cards::FindCardByName("Pyroblast");
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
    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tortollan Pilgrim"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    std::string_view cardName = cards[0]->name;

    const bool check1 = cards[0]->name == "Fireball" ||
                        cards[0]->name == "Frostbolt" ||
                        cards[0]->name == "Pyroblast";
    const bool check2 = cards[1]->name == "Fireball" ||
                        cards[1]->name == "Frostbolt" ||
                        cards[1]->name == "Pyroblast";
    const bool check3 = cards[2]->name == "Fireball" ||
                        cards[2]->name == "Frostbolt" ||
                        cards[2]->name == "Pyroblast";
    const bool check4 = (cards[0]->dbfID != cards[1]->dbfID) &&
                        (cards[0]->dbfID != cards[2]->dbfID) &&
                        (cards[1]->dbfID != cards[2]->dbfID);
    const bool check = check1 && check2 && check3 && check4;
    CHECK_EQ(check, true);

    curHero->SetDamage(0);
    opHero->SetDamage(0);

    TestUtils::ChooseNthChoice(game, 1);
    if (cardName == "Fireball")
    {
        const bool check11 = curHero->GetHealth() == 24 &&
                             curField.GetCount() == 1 &&
                             opHero->GetHealth() == 30;
        const bool check12 = curHero->GetHealth() == 30 &&
                             curField.GetCount() == 0 &&
                             opHero->GetHealth() == 30;
        const bool check13 = curHero->GetHealth() == 30 &&
                             curField.GetCount() == 1 &&
                             opHero->GetHealth() == 24;
        const bool check14 = check11 || check12 || check13;
        CHECK_EQ(check14, true);
    }
    else if (cardName == "Frostbolt")
    {
        const bool check21 =
            curHero->GetHealth() == 27 && curHero->IsFrozen() == true &&
            curField[0]->GetHealth() == 5 && opHero->GetHealth() == 30;
        const bool check22 =
            curHero->GetHealth() == 30 && curField[0]->GetHealth() == 2 &&
            curField[0]->IsFrozen() == true && opHero->GetHealth() == 30;
        const bool check23 =
            curHero->GetHealth() == 30 && curField[0]->GetHealth() == 5 &&
            opHero->GetHealth() == 27 && opHero->IsFrozen() == true;
        const bool check24 = check21 || check22 || check23;
        CHECK_EQ(check24, true);
    }
    else
    {
        const bool check31 = curHero->GetHealth() == 20 &&
                             curField.GetCount() == 1 &&
                             opHero->GetHealth() == 30;
        const bool check32 = curHero->GetHealth() == 30 &&
                             curField.GetCount() == 0 &&
                             opHero->GetHealth() == 30;
        const bool check33 = curHero->GetHealth() == 30 &&
                             curField.GetCount() == 1 &&
                             opHero->GetHealth() == 20;
        const bool check34 = check31 || check32 || check33;
        CHECK_EQ(check34, true);
    }
}

// ------------------------------------------ MINION - MAGE
// [ULD_238] Reno the Relicologist - COST:6 [ATK:4/HP:6]
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       deal 10 damage randomly split among all enemy minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - ULD_238 : Reno the Relicologist")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 7; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Malygos");
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Reno the Relicologist"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Reno the Relicologist"));

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[0]->GetHealth(), 12);
    CHECK_EQ(curField[1]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    const int totalHealth = curField[0]->GetHealth() + curField[1]->GetHealth();
    CHECK_EQ(totalHealth, 14);
}

// ------------------------------------------- SPELL - MAGE
// [ULD_239] Flame Ward - COST:3
// - Faction: Neutral, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After a minion attacks your hero,
//       deal 3 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - ULD_239 : Flame Ward")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curSecret = *(curPlayer->GetSecretZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Ward"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(card1->GetGameTag(GameTag::REVEALED), 0);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, AttackTask(card4, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(card1->GetGameTag(GameTag::REVEALED), 1);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ------------------------------------------ MINION - MAGE
// [ULD_240] Arcane Flakmage - COST:2 [ATK:3/HP:2]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: After you play a <b>Secret</b>,
//       deal 2 damage to all enemy minions.
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - ULD_240 : Arcane Flakmage")
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
    auto& opSecret = *(opPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Flakmage"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flame Ward"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opSecret.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(opSecret.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ------------------------------------------ MINION - MAGE
// [ULD_293] Cloud Prince - COST:5 [ATK:4/HP:4]
// - Race: Elemental, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       deal 6 damage.
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
TEST_CASE("[Mage : Minion] - ULD_293 : Cloud Prince")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cloud Prince"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cloud Prince"));
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
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
}

// ---------------------------------------- SPELL - WARLOCK
// [ULD_324] Impbalming - COST:4
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy a minion. Shuffle 3 Worthless Imps into your deck.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[WARLOCK : SPELL] - ULD_324 : Impbalming")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Impbalming"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 3);
    CHECK_EQ(curDeck[0]->card->name, "Worthless Imp");
}

// ----------------------------------------- MINION - ROGUE
// [ULD_327] Bazaar Mugger - COST:5 [ATK:3/HP:5]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Battlecry:</b> Add a random minion
//       from another class to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - ULD_327 : Bazaar Mugger")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bazaar Mugger"));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_NE(curHand[0]->card->GetCardClass(), CardClass::ROGUE);
}

// ------------------------------------------ MINION - MAGE
// [ULD_329] Dune Sculptor - COST:3 [ATK:3/HP:3]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a spell, add a random Mage
//       minion to your hand.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - ULD_329 : Dune Sculptor")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dune Sculptor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::MAGE);
}

// ------------------------------------------- SPELL - MAGE
// [ULD_433] Raid the Sky Temple - COST:1
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Quest:</b> Cast 10 spells.
//       <b>Reward: </b>Ascendant Scroll.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - QUEST = 1
// - QUEST_PROGRESS_TOTAL = 10
// - 676 = 1
// - 839 = 1
// - QUEST_REWARD_DATABASE_ID = 53946
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - ULD_433 : Raid the Sky Temple")
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

    auto curHero = curPlayer->GetHero();
    auto& curHand = *(curPlayer->GetHandZone());
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Raid the Sky Temple"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(quest->GetQuestProgress(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(quest->GetQuestProgress(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(quest->GetQuestProgress(), 5);

    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card9 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card10 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card11 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));

    game.Process(curPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(quest->GetQuestProgress(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card8));
    CHECK_EQ(quest->GetQuestProgress(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card9));
    CHECK_EQ(quest->GetQuestProgress(), 8);

    game.Process(curPlayer, PlayCardTask::Spell(card10));
    CHECK_EQ(quest->GetQuestProgress(), 9);

    game.Process(curPlayer, PlayCardTask::Spell(card11));
    CHECK(curSecret->quest == nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 10);
    CHECK_EQ(curHero->heroPower->card->id, "ULD_433p");
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curHand.GetCount(), 1);
    const int originalCost = curHand[0]->card->GetCost();
    const int reducedCost = curHand[0]->GetCost();
    CHECK_LE(originalCost - reducedCost, 2);
}

// ------------------------------------------ MINION - MAGE
// [ULD_435] Naga Sand Witch - COST:5 [ATK:5/HP:5]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Change the Cost of spells
//       in your hand to (5).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - ULD_435 : Naga Sand Witch")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Naga Sand Witch"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));

    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 5);
    CHECK_EQ(card4->GetCost(), 5);
}

// ------------------------------------------- SPELL - MAGE
// [ULD_726] Ancient Mysteries - COST:2
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: Draw a <b>Secret</b> from your deck. It costs (0).
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - ULD_726 : Ancient Mysteries")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 2)
    {
        config.player1Deck[i] = Cards::FindCardByName("Flame Ward");
        config.player1Deck[i + 1] = Cards::FindCardByName("Wisp");
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ancient Mysteries"));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsSecret(), true);
    CHECK_EQ(curHand[4]->GetCost(), 0);
    CHECK_EQ(curDeck.GetCount(), 25);
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
TEST_CASE("[Paladin : Minion] - ULD_207 : Ancestral Guardian")
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
TEST_CASE("[Paladin : Spell] - ULD_431 : Making Mummies")
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
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(quest->GetQuestProgress(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(quest->GetQuestProgress(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK(curSecret->quest == nullptr);
    CHECK_EQ(quest->GetQuestProgress(), 5);
    CHECK_EQ(curHero->heroPower->card->id, "ULD_431p");

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasReborn(), true);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasReborn(), true);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->HasReborn(), true);
}

// ---------------------------------------- MINION - PRIEST
// [ULD_269] Wretched Reclaimer - COST:3 [ATK:3/HP:3]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a friendly minion,
//       then return it to life with full Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - ULD_269 : Wretched Reclaimer")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
        curPlayer, Cards::FindCardByName("Injured Blademaster"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shattered Sun Cleric"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wretched Reclaimer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Serpent Egg"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wretched Reclaimer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->card->name, "Injured Blademaster");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Injured Blademaster");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card5, card4));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[3]->card->name, "Serpent Egg");
    CHECK_EQ(curField[4]->card->name, "Sea Serpent");
    CHECK_EQ(curField[4]->GetAttack(), 3);
    CHECK_EQ(curField[4]->GetHealth(), 4);
}

// ---------------------------------------- MINION - PRIEST
// [ULD_270] Sandhoof Waterbearer - COST:5 [ATK:5/HP:5]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn, restore 5 Health
//       to a damaged friendly character.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - ULD_270 : Sandhoof Waterbearer")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    curPlayer->GetHero()->SetDamage(5);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sandhoof Waterbearer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ----------------------------------------- SPELL - PRIEST
// [ULD_272] Holy Ripple - COST:2
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 1 damage to all enemies. Restore 1 Health
//       to all friendly characters.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - ULD_272 : Holy Ripple")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    curPlayer->GetHero()->SetDamage(1);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Ripple"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Injured Blademaster"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Servant"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ----------------------------------------- SPELL - PRIEST
// [ULD_714] Penance - COST:2
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b> Deal 3 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - ULD_714 : Penance")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    curPlayer->GetHero()->SetDamage(3);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Penance"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomsayer"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curField[0]));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ----------------------------------------- SPELL - PRIEST
// [ULD_718] Plague of Death - COST:9
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Silence</b> and destroy all minions.
// --------------------------------------------------------
// GameTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - ULD_718 : Plague of Death")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague of Death"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Serpent Egg"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Serpent Egg"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- MINION - ROGUE
// [ULD_186] Pharaoh Cat - COST:1 [ATK:1/HP:2]
// - Race: Beast, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random <b>Reborn</b> minion
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - REBORN = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - ULD_186 : Pharaoh Cat")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pharaoh Cat"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->HasGameTag(GameTag::REBORN), true);
}

// ----------------------------------------- MINION - ROGUE
// [ULD_231] Whirlkick Master - COST:2 [ATK:1/HP:2]
// - Set: Uldum, Rarity: Epic
// --------------------------------------------------------
// Text: Whenever you play a <b>Combo</b> card,
//       add a random <b>Combo</b> card to your hand.
// --------------------------------------------------------
// RefTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - ULD_231 : Whirlkick Master")
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlkick Master"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlkick Master"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eviscerate"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eviscerate"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Eviscerate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card5, card2));
    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    
    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, curPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(opHand.GetCount(), 1);     // The Coin

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 3);
    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[0]->card->HasGameTag(GameTag::COMBO), true);
    CHECK_EQ(curHand[1]->card->HasGameTag(GameTag::COMBO), true);
    CHECK_EQ(curHand[2]->card->HasGameTag(GameTag::COMBO), true);
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
TEST_CASE("[Warrior : Minion] - ULD_206 : Restless Mummy")
{
    // Do nothing
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
TEST_CASE("[Neutral : Minion] - ULD_174 : Serpent Egg")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Serpent Egg"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Sea Serpent");
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_177] Octosari - COST:8 [ATK:8/HP:8]
// - Race: Beast, Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw 8 cards.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_177 : Octosari")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Octosari"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, AttackTask(card2, card1));
    game.Process(opPlayer, AttackTask(card3, card1));
    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 9);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_182] Spitting Camel - COST:2 [ATK:2/HP:4]
// - Race: Beast, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn, deal 1 damage
//       to another random friendly minion.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_182 : Spitting Camel")
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
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth() + curField[2]->GetHealth(), 8);
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
TEST_CASE("[Neutral : Minion] - ULD_184 : Kobold Sandtrooper")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kobold Sandtrooper"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_190] Pit Crocolisk - COST:8 [ATK:5/HP:6]
// - Race: Beast, Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 5 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_190 : Pit Crocolisk")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Crocolisk"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
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
TEST_CASE("[Neutral : Minion] - ULD_191 : Beaming Sidekick")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, nullptr));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 2);
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
TEST_CASE("[Neutral : Minion] - ULD_193 : Living Monument")
{
    // Do noting
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
TEST_CASE("[Neutral : Minion] - ULD_194 : Wasteland Scorpid")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_197] Quicksand Elemental - COST:2 [ATK:3/HP:2]
// - Race: Elemental, Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give all enemy minions -2 Attack
//       this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_197 : Quicksand Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Infested Goblin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jar Dealer"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Quicksand Elemental"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Walking Fountain"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetAttack(), 0);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card4, curField[0]));
    CHECK_EQ(opField[1]->GetHealth(), 8);
    game.Process(opPlayer, AttackTask(card4, curField[1]));
    CHECK_EQ(opField[1]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_198] Conjured Mirage - COST:4 [ATK:3/HP:10]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> At the start of your turn,
//       shuffle this minion into your deck.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_198 : Conjured Mirage")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Conjured Mirage"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Walking Fountain"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 0);
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
TEST_CASE("[Neutral : Minion] - ULD_205 : Candletaker")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_208] Khartut Defender - COST:6 [ATK:3/HP:4]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>, <b>Reborn</b> <b>Deathrattle:</b>
//       Restore 3 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// - REBORN = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_208 : Khartut Defender")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    curPlayer->GetHero()->SetDamage(6);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Khartut Defender"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Walking Fountain"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasReborn(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasReborn(), false);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);

    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_250] Infested Goblin - COST:3 [ATK:2/HP:3]
// - Set: Uldum, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Add two 1/1 Scarabs
//       with <b>Taunt</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_250 : Infested Goblin")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Infested Goblin"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Scarab");
    CHECK_EQ(curHand[5]->card->name, "Scarab");
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
TEST_CASE("[Neutral : Minion] - ULD_271 : Injured Tol'vir")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Injured Tol'vir"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetDamage(), 3);
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
TEST_CASE("[Neutral : Minion] - ULD_274 : Wasteland Assassin")
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
TEST_CASE("[Neutral : Minion] - ULD_275 : Bone Wraith")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [ULD_282] Jar Dealer - COST:1 [ATK:1/HP:1]
// - Set: Uldum, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a random 1-Cost minion
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - ULD_282 : Jar Dealer")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jar Dealer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetCost(), 1);
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
TEST_CASE("[Neutral : Minion] - ULD_289 : Fishflinger")
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fishflinger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::MURLOC);
    CHECK_EQ(opHand[5]->card->GetRace(), Race::MURLOC);
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
TEST_CASE("[Neutral : Minion] - ULD_450 : Vilefiend")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vilefiend"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightwarden"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curField[1]->GetAttack(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField[1]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField[1]->GetAttack(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[1]->GetAttack(), 7);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curField[1]->GetAttack(), 7);
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
TEST_CASE("[Neutral : Minion] - ULD_712 : Bug Collector")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bug Collector"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bug Collector"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Locust");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::RUSH), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[1]->card->name, "Locust");
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetGameTag(GameTag::RUSH), 1);

    game.Process(opPlayer, AttackTask(opField[1], curField[1]));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
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
TEST_CASE("[Neutral : Minion] - ULD_721 : Colossus of the Moon")
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
TEST_CASE("[Neutral : Minion] - ULD_723 : Murmy")
{
    // Do nothing
}
