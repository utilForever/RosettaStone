//// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon
//
//// We are making my contributions/submissions to this project solely in our
//// personal capacity and are not conveying any rights to any intellectual
//// property of any third parties.
//
//#include <Utils/CardSetUtils.hpp>
//
//#include <Rosetta/Actions/Draw.hpp>
//#include <Rosetta/Cards/Cards.hpp>
//#include <Rosetta/Zones/DeckZone.hpp>
//#include <Rosetta/Zones/FieldZone.hpp>
//#include <Rosetta/Zones/HandZone.hpp>
//
//using namespace RosettaStone;
//using namespace PlayerTasks;
//using namespace SimpleTasks;
//
//// ------------------------------------ HERO_POWER - PRIEST
//// [CS1h_001] Lesser Heal (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Restore 2 Health.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS1h_001_LesserHeal)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 29);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
//
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ------------------------------------- HERO_POWER - DRUID
//// [CS2_017] Shapeshift (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> +1 Attack this turn. +1 Armor.
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_017_Shapeshift)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::PRIEST;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 0);
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 1);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 1);
//
//    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 1);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 0);
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 0);
//}
//
//// -------------------------------------- HERO_POWER - MAGE
//// [CS2_034] Fireblast (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Deal 1 damage.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_034_Fireblast)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PRIEST;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask(card1));
//
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//}
//
//// ------------------------------------ HERO_POWER - SHAMAN
//// [CS2_049] Totemic Call (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Summon a random Totem.
//// --------------------------------------------------------
//// Entourage: CS2_050, CS2_051, CS2_052, NEW1_009
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_NUM_MINION_SLOTS = 1
//// - REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 0
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_049_TotemicCall)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    game.Process(curPlayer, HeroPowerTask());
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask());
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask());
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask());
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask());
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask());
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask());
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask());
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curField.GetCount(), 4);
//    EXPECT_EQ(opField.GetCount(), 4);
//}
//
//// ----------------------------------- HERO_POWER - WARLOCK
//// [CS2_056] Life Tap (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Draw a card and take 2 damage.
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_056_LifeTap)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 4);
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
//}
//
//// ------------------------------------- HERO_POWER - ROGUE
//// [CS2_083b] Dagger Mastery (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Equip a 1/2 Dagger.
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_083b_DaggerMastery)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    EXPECT_EQ(curPlayer->GetHero()->HasWeapon(), false);
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(curPlayer->GetHero()->HasWeapon(), true);
//    EXPECT_EQ(curPlayer->GetWeapon().GetAttack(), 1);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 2);
//
//    game.Process(curPlayer,
//                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 1);
//}
//
//// ----------------------------------- HERO_POWER - PALADIN
//// [CS2_101] Reinforce (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Summon a 1/1 Silver Hand Recruit.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_NUM_MINION_SLOTS = 1
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_101_Reinforce)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//}
//
//// ----------------------------------- HERO_POWER - WARRIOR
//// [CS2_102] Armor Up! (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Gain 2 Armor.
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, CS2_102_ArmorUp)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 0);
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 2);
//}
//
//// ------------------------------------ HERO_POWER - HUNTER
//// [DS1h_292] Steady Shot (*) - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Hero Power</b> Deal 2 damage to the enemy hero.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_STEADY_SHOT = 0
//// - REQ_MINION_OR_ENEMY_HERO = 0
//// --------------------------------------------------------
//TEST(HeroPowersCoreTest, DS1h_292_SteadyShot)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_005] Claw - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your hero +2 Attack this turn. Gain 2 Armor.
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_005_Claw)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Claw"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 2);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 2);
//
//    game.Process(curPlayer,
//                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 2);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_007] Healing Touch - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Restore 8 Health.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_007_HealingTouch)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Healing Touch"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Healing Touch"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    curPlayer->GetHero()->SetDamage(15);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    opField[0]->SetDamage(6);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 23);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_008] Moonfire - COST:0
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_008_Moonfire)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));
//    const auto card5 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card6 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card6));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 29);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 29);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_009] Mark of the Wild - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion <b>Taunt</b> and +2/+2.<i>
////       (+2 Attack/+2 Health)</i>
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_009_MarkOfTheWild)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mark of the Wild"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
//    EXPECT_EQ(curField[0]->GetAttack(), 5);
//    EXPECT_EQ(curField[0]->GetHealth(), 3);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_011] Savage Roar - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your characters +2 Attack this turn.
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_011_SavageRoar)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Savage Roar"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetAttack(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 2);
//    EXPECT_EQ(curField[0]->GetAttack(), 5);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetAttack(), 1);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_012] Swipe - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 4 damage to an enemy and 1 damage to all other enemies.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_ENEMY_TARGET = 0
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_012_Swipe)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swipe"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swipe"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opField[1]->GetHealth(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 29);
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 25);
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [CS2_013] Wild Growth - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Gain an empty Mana Crystal.
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_013_WildGrowth)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(9);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wild Growth"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wild Growth"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetRemainingMana(), 6);
//    EXPECT_EQ(curPlayer->GetTotalMana(), 10);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetRemainingMana(), 3);
//    EXPECT_EQ(curPlayer->GetTotalMana(), 10);
//}
//
//// ----------------------------------------- MINION - DRUID
//// [CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
//// - Faction: neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(DruidCoreTest, CS2_232_IronbarkProtector)
//{
//    // Do nothing
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [EX1_169] Innervate - COST:0
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Gain 1 Mana Crystal this turn only.
//// --------------------------------------------------------
//TEST(DruidCoreTest, EX1_169_Innervate)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(9);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
//    const auto card3 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Dragonling Mechanic"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetRemainingMana(), 10);
//    EXPECT_EQ(curPlayer->GetTemporaryMana(), 1);
//    EXPECT_EQ(curPlayer->GetTotalMana(), 9);
//    EXPECT_EQ(curPlayer->GetUsedMana(), 0);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curPlayer->GetRemainingMana(), 6);
//    EXPECT_EQ(curPlayer->GetTemporaryMana(), 0);
//    EXPECT_EQ(curPlayer->GetTotalMana(), 9);
//    EXPECT_EQ(curPlayer->GetUsedMana(), 3);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetRemainingMana(), 10);
//    EXPECT_EQ(curPlayer->GetTemporaryMana(), 0);
//    EXPECT_EQ(curPlayer->GetTotalMana(), 10);
//    EXPECT_EQ(curPlayer->GetUsedMana(), 0);
//}
//
//// ------------------------------------------ SPELL - DRUID
//// [EX1_173] Starfire - COST:6
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 5 damage. Draw a card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(DruidCoreTest, EX1_173_Starfire)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfire"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [CS2_084] Hunter's Mark - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Change a minion's Health to 1.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(HunterCoreTest, CS2_084_HuntersMark)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hunter's Mark"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//}
//
//// ---------------------------------------- MINION - HUNTER
//// [CS2_237] Starving Buzzard - COST:5 [ATK:3/HP:2]
//// - Race: Beast, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Whenever you summon a Beast, draw a card.
//// --------------------------------------------------------
//TEST(HunterCoreTest, CS2_237_StarvingBuzzard)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starving Buzzard"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironfur Grizzly"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//}
//
//// ---------------------------------------- MINION - HUNTER
//// [DS1_070] Houndmaster - COST:4 [ATK:4/HP:3]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Give a friendly Beast +2/+2 and <b>Taunt</b>.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_FRIENDLY_TARGET = 0
//// - REQ_TARGET_WITH_RACE = 20
//// --------------------------------------------------------
//// RefTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_070_Houndmaster)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Houndmaster"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starving Buzzard"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField[1]->GetAttack(), 5);
//    EXPECT_EQ(curField[1]->GetHealth(), 4);
//    EXPECT_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 1);
//}
//
//// ---------------------------------------- MINION - HUNTER
//// [DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
//// - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your other Beasts have +1 Attack.
//// --------------------------------------------------------
//// GameTag:
//// - AURA = 1
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_175_TimberWolf)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Timber Wolf"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Timber Wolf"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starving Buzzard"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(curField[2]->GetAttack(), 4);
//    EXPECT_EQ(curField[2]->GetHealth(), 2);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//    EXPECT_EQ(curField[2]->GetAttack(), 5);
//    EXPECT_EQ(curField[2]->GetHealth(), 2);
//    EXPECT_EQ(curField[3]->GetAttack(), 2);
//    EXPECT_EQ(curField[3]->GetHealth(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//    game.Process(opPlayer, AttackTask(card5, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//    EXPECT_EQ(curField[2]->GetAttack(), 4);
//    EXPECT_EQ(curField[2]->GetHealth(), 2);
//}
//
//// ---------------------------------------- MINION - HUNTER
//// [DS1_178] Tundra Rhino - COST:5 [ATK:2/HP:5]
//// - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your Beasts have <b>Charge</b>.
//// --------------------------------------------------------
//// GameTag:
//// - AURA = 1
//// --------------------------------------------------------
//// RefTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_178_TundraRhino)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tundra Rhino"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Timber Wolf"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starving Buzzard"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 0);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
//    EXPECT_EQ(curField[1]->GetGameTag(GameTag::CHARGE), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
//    EXPECT_EQ(curField[1]->GetGameTag(GameTag::CHARGE), 1);
//    EXPECT_EQ(curField[2]->GetGameTag(GameTag::CHARGE), 1);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [DS1_183] Multi-Shot - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage to two random enemy minions.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_MINIMUM_ENEMY_MINIONS = 1
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_183_MultiShot)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Multi-Shot"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    int totalHealth = opField[0]->GetHealth();
//    EXPECT_EQ(totalHealth, 4);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    totalHealth += opField[1]->GetHealth();
//    EXPECT_EQ(totalHealth, 8);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    totalHealth += opField[2]->GetHealth();
//    EXPECT_EQ(totalHealth, 12);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//    EXPECT_EQ(opField.GetCount(), 3);
//    totalHealth = opField[0]->GetHealth();
//    totalHealth += opField[1]->GetHealth();
//    totalHealth += opField[2]->GetHealth();
//    EXPECT_EQ(totalHealth, 6);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [DS1_184] Tracking - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Look at the top 3 cards of your deck. Draw one and discard
//// the others.
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_184_Tracking)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tracking"));
//
//    EXPECT_EQ(curPlayer->GetDeckZone()->GetCount(), 5);
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_TRUE(curPlayer->choice.has_value());
//    EXPECT_EQ(curPlayer->choice.value().choices.size(), 3u);
//
//    game.Process(
//        curPlayer,
//        ChooseTask::Pick(curPlayer, curPlayer->choice.value().choices[0]));
//    EXPECT_EQ(curPlayer->GetDeckZone()->GetCount(), 2);
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [DS1_185] Arcane Shot - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(HunterCoreTest, DS1_185_ArcaneShot)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
//    const auto card5 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card6 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card6));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
//    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
//    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [EX1_539] Kill Command - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage. If you control a Beast,
////       deal 5 damage instead.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(HunterCoreTest, EX1_539_KillCommand)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kill Command"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kill Command"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironfur Grizzly"));
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 22);
//}
//
//// ----------------------------------------- SPELL - HUNTER
//// [NEW1_031] Animal Companion - COST:3
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Summon a random Beast Companion.
//// --------------------------------------------------------
//// Entourage: NEW1_032, NEW1_033, NEW1_034
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_NUM_MINION_SLOTS = 1
//// --------------------------------------------------------
//TEST(HunterCoreTest, NEW1_031_AnimalCompanion)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Animal Companion"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Animal Companion"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//
//    int isLeokk1 = (curField[0]->card->name == "Leokk") ? 1 : 0;
//    int isLeokk2 = (curField[1]->card->name == "Leokk") ? 1 : 0;
//
//    EXPECT_EQ(curField[0]->card->gameTags[GameTag::ATK] + isLeokk2,
//              curField[0]->GetAttack());
//    EXPECT_EQ(curField[1]->card->gameTags[GameTag::ATK] + isLeokk1,
//              curField[1]->GetAttack());
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_022] Polymorph - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Transform a minion
////       into a 1/1 Sheep.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_022_Polymorph)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Polymorph"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Polymorph"));
//    const auto card3 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetAttack(), 1);
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_023] Arcane Intellect - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Draw 2 cards.
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_023_ArcaneIntellect)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Intellect"));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_024] Frostbolt - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage to a character and <b>Freeze</b> it.
//// --------------------------------------------------------
//// GameTag:
//// - FREEZE = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_024_Frostbolt)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
//    const auto card5 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card6 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card6));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
//    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//    EXPECT_EQ(opPlayer->GetHero()->IsFrozen(), true);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//    EXPECT_EQ(curField[0]->IsFrozen(), true);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 27);
//    EXPECT_EQ(curPlayer->GetHero()->IsFrozen(), true);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_025] Arcane Explosion - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage to all enemy minions.
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_025_ArcaneExplosion)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Explosion"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Explosion"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//    EXPECT_EQ(opField.GetCount(), 3);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(opField.GetCount(), 0);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_026] Frost Nova - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Freeze</b> all enemy minions.
//// --------------------------------------------------------
//// GameTag:
//// - FREEZE = 1
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_026_FrostNova)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frost Nova"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//    EXPECT_EQ(opField[0]->IsFrozen(), true);
//    EXPECT_EQ(opField[1]->GetHealth(), 1);
//    EXPECT_EQ(opField[1]->IsFrozen(), true);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//    EXPECT_EQ(opPlayer->GetHero()->IsFrozen(), false);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_027] Mirror Image - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Summon two 0/2 minions with <b>Taunt</b>.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_NUM_MINION_SLOTS = 1
//// --------------------------------------------------------
//// RefTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_027_MirrorImage)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Image"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Image"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Image"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Image"));
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    EXPECT_EQ(curField.GetCount(), 0);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curField.GetCount(), 2);
//    EXPECT_EQ(curField[0]->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetHealth(), 2);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
//    EXPECT_EQ(curField[1]->GetAttack(), 0);
//    EXPECT_EQ(curField[1]->GetHealth(), 2);
//    EXPECT_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 1);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curField.GetCount(), 4);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card3));
//    EXPECT_EQ(curField.GetCount(), 6);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card4));
//    EXPECT_EQ(curField.GetCount(), 7);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_029] Fireball - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 6 damage.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_029_Fireball)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
//    const auto card5 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card6 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card6));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
//    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 24);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
//    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 24);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [CS2_032] Flamestrike - COST:7
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 4 damage to all enemy minions.
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_032_Flamestrike)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flamestrike"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//}
//
//// ------------------------------------------ MINION - MAGE
//// [CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
//// - Race: Elemental, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Freeze</b> any character damaged by this minion.
//// --------------------------------------------------------
//// GameTag:
//// - FREEZE = 1
//// --------------------------------------------------------
//TEST(MageCoreTest, CS2_033_WaterElemental)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Water Elemental"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, AttackTask(card1, card2));
//
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 2);
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//    EXPECT_EQ(curField[0]->IsFrozen(), false);
//    EXPECT_EQ(opField[0]->IsFrozen(), true);
//}
//
//// ------------------------------------------- SPELL - MAGE
//// [EX1_277] Arcane Missiles - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage randomly split among all enemies.
//// --------------------------------------------------------
//// GameTag:
//// - ImmuneToSpellpower = 1
//// --------------------------------------------------------
//TEST(MageCoreTest, EX1_277_ArcaneMissiles)
//{
//    GameConfig config;
//    config.player1Class = CardClass::MAGE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    int totalHealth = opPlayer->GetHero()->GetHealth();
//    totalHealth += opField[0]->GetHealth();
//    EXPECT_EQ(totalHealth, 37);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    totalHealth = opPlayer->GetHero()->GetHealth();
//    totalHealth += opField[0]->GetHealth();
//    EXPECT_EQ(totalHealth, 34);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    totalHealth = opPlayer->GetHero()->GetHealth();
//    totalHealth += opField[0]->GetHealth();
//    EXPECT_EQ(totalHealth, 31);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [CS2_087] Blessing of Might - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion +3 Attack.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_087_BlessingOfMight)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Blessing of Might"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//}
//
//// --------------------------------------- MINION - PALADIN
//// [CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Restore 6 Health to your hero.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_088_GuardianOfKings)
//{
//    GameConfig config;
//    config.player1Class = CardClass::DRUID;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    opPlayer->GetHero()->SetDamage(6);
//
//    const auto card1 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Guardian of Kings"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [CS2_089] Holy Light - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Restore 6 Health.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_089_HolyLight)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    curPlayer->GetHero()->SetDamage(15);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    opField[0]->SetDamage(6);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 21);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//}
//
//// --------------------------------------- WEAPON - PALADIN
//// [CS2_091] Light's Justice - COST:1 [ATK:1/HP:0]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// GameTag:
//// - DURABILITY = 4
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_091_LightsJustice)
//{
//    // Do nothing
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [CS2_092] Blessing of Kings - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_092_BlessingOfKings)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Blessing of Kings"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 7);
//    EXPECT_EQ(curField[0]->GetHealth(), 5);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [CS2_093] Consecration - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage to all enemies.
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_093_Consecration)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Consecration"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [CS2_094] Hammer of Wrath - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage. Draw a card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_094_HammerOfWrath)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hammer of Wrath"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 4);
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//}
//
//// --------------------------------------- WEAPON - PALADIN
//// [CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Whenever your hero attacks, restore 2 Health to it.
//// --------------------------------------------------------
//// GameTag:
//// - DURABILITY = 2
//// --------------------------------------------------------
//TEST(PaladinCoreTest, CS2_097_TruesilverChampion)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(4);
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Truesilver Champion"));
//
//    game.Process(curPlayer, PlayCardTask::Weapon(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 26);
//    EXPECT_EQ(curPlayer->GetWeapon().GetAttack(), 4);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 2);
//
//    game.Process(curPlayer,
//                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 26);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 1);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [EX1_360] Humility - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Change a minion's Attack to 1.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PaladinCoreTest, EX1_360_Humility)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Humility"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField[0]->GetAttack(), 6);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(opField[0]->GetAttack(), 1);
//}
//
//// ---------------------------------------- SPELL - PALADIN
//// [EX1_371] Hand of Protection - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion <b>Divine Shield</b>.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - DIVINE_SHIELD = 1
//// --------------------------------------------------------
//TEST(PaladinCoreTest, EX1_371_HandOfProtection)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Hand of Protection"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hammer of Wrath"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS1_112] Holy Nova - COST:5
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage to all enemies.
////       Restore 2 Health to all friendly characters.
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS1_112_HolyNova)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(4);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windfury Harpy"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Nova"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Argent Squire"));
//    const auto card5 = Generic::DrawCard(
//        opPlayer, Cards::FindCardByName("Worgen Infiltrator"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, AttackTask(card1, card4));
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card3));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//    EXPECT_EQ(curField[0]->GetHealth(), 5);
//    EXPECT_EQ(curField[1]->GetHealth(), 7);
//    EXPECT_EQ(opField.GetCount(), 0);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS1_113] Mind Control - COST:10
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Take control of an enemy minion.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_ENEMY_TARGET = 0
//// - REQ_NUM_MINION_SLOTS = 1
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS1_113_MindControl)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto& curField = *(curPlayer->GetFieldZone());
//    const auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windfury Harpy"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Control"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mind Control"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField.GetCount(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
//    EXPECT_EQ(curField.GetCount(), 2);
//    EXPECT_EQ(opField.GetCount(), 0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 8);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS1_130] Holy Smite - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS1_130_HolySmite)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
//    const auto card5 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card6 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card6));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
//    EXPECT_EQ(curField.GetCount(), 0);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS2_003] Mind Vision - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Put a copy of a random card in your opponent's hand into your hand.
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS2_003_MindVision)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curHand = *(curPlayer->GetHandZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Vision"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    const auto gainedCard = curHand[4];
//
//    bool flag = false;
//    for (auto& handCard : opPlayer->GetHandZone()->GetAll())
//    {
//        if (handCard->card->id == gainedCard->card->id)
//        {
//            flag = true;
//            break;
//        }
//    }
//
//    EXPECT_TRUE(flag);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS2_004] Power Word: Shield - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion +2 Health.
////       Draw a card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS2_004_PowerWordShield)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Power Word: Shield"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField[0]->GetHealth(), 9);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS2_234] Shadow Word: Pain - COST:2
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Destroy a minion with 3 or less Attack.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_TARGET_MAX_ATTACK = 3
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS2_234_ShadowWordPain)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Shadow Word: Pain"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(opField.GetCount(), 1);
//}
//
//// ---------------------------------------- MINION - PRIEST
//// [CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Whenever a minion is healed, draw a card.
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS2_235_NorthshireCleric)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(6);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Northshire Cleric"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(curPlayer,
//                 PlayCardTask::MinionTarget(card2, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 26);
//
//    curField[0]->SetDamage(2);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField[0]->GetHealth(), 3);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [CS2_236] Divine Spirit - COST:2
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Double a minion's Health.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(PriestCoreTest, CS2_236_DivineSpirit)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Divine Spirit"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, AttackTask(card3, card2));
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetHealth(), 8);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [EX1_192] Radiance - COST:1
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Restore 5 Health to your hero.
//// --------------------------------------------------------
//TEST(PriestCoreTest, EX1_192_Radiance)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(8);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Radiance"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Radiance"));
//
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 22);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 27);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ----------------------------------------- SPELL - PRIEST
//// [EX1_622] Shadow Word: Death - COST:3
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Destroy a minion with 5 or more Attack.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_TARGET_MIN_ATTACK = 5
//// --------------------------------------------------------
//TEST(PriestCoreTest, EX1_622_ShadowWordDeath)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Shadow Word: Death"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(opField.GetCount(), 1);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [CS2_072] Backstab - COST:0
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage to an undamaged minion.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_UNDAMAGED_TARGET = 0
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_072_Backstab)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [CS2_074] Deadly Poison - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your weapon +2 Attack.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_WEAPON_EQUIPPED = 0
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_074_DeadlyPoison)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Poison"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, HeroPowerTask());
//    EXPECT_EQ(curPlayer->GetWeapon().GetAttack(), 1);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 2);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetWeapon().GetAttack(), 3);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 2);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetWeapon().GetAttack(), 3);
//    EXPECT_EQ(curPlayer->GetWeapon().GetDurability(), 2);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [CS2_075] Sinister Strike - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage to the enemy hero.
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_075_SinisterStrike)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sinister Strike"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [CS2_076] Assassinate - COST:5
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Destroy an enemy minion.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_ENEMY_TARGET = 0
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_076_Assassinate)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Assassinate"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(opField.GetCount(), 0);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [CS2_077] Sprint - COST:7
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Draw 4 cards.
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_077_Sprint)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sprint"));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 8);
//}
//
//// ----------------------------------------- WEAPON - ROGUE
//// [CS2_080] Assassin's Blade - COST:5 [ATK:3/HP:0]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// GameTag:
//// - DURABILITY = 4
//// --------------------------------------------------------
//TEST(RogueCoreTest, CS2_080_AssassinsBlade)
//{
//    // Do nothing
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [EX1_129] Fan of Knives - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage to all enemy minions. Draw a card.
//// --------------------------------------------------------
//TEST(RogueCoreTest, EX1_129_FanOfKnives)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fan of Knives"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fan of Knives"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//
//    EXPECT_EQ(opField.GetCount(), 3);
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 7);
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 7);
//    EXPECT_EQ(opField.GetCount(), 0);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ----------------------------------------- MINION - ROGUE
//// [EX1_191] Plaguebringer - COST:4 [ATK:3/HP:3]
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Give a friendly minion <b>Poisonous</b>.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_MINION_TARGET = 0
//// - REQ_FRIENDLY_TARGET = 0
//// - REQ_TARGET_IF_AVAILABLE = 0
//// --------------------------------------------------------
//// RefTag:
//// - POISONOUS = 1
//// --------------------------------------------------------
//TEST(RogueCoreTest, EX1_191_Plaguebringer)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::ROGUE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Plaguebringer"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card3));
//
//    game.Process(opPlayer, AttackTask(card3, card1));
//    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
//    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 1);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [EX1_278] Shiv - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage. Draw a card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(RogueCoreTest, EX1_278_Shiv)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shiv"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shiv"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 8);
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curPlayer->currentSpellPower, 1);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 7);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//}
//
//// ------------------------------------------ SPELL - ROGUE
//// [EX1_581] Sap - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Return an enemy minion to your opponent's hand.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_ENEMY_TARGET = 0
//// --------------------------------------------------------
//TEST(RogueCoreTest, EX1_581_Sap)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sap"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blessing of Kings"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField.GetCount(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card4));
//    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetAttack(), 7);
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 7);
//    EXPECT_EQ(opField[0]->GetAttack(), 3);
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [CS2_037] Frost Shock - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage to an enemy character and <b>Freeze</b> it.
//// --------------------------------------------------------
//// GameTag:
//// - FREEZE = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_ENEMY_TARGET = 0
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_037_FrostShock)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frost Shock"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frost Shock"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//    EXPECT_EQ(opField[0]->IsFrozen(), true);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
//    EXPECT_EQ(opField.GetCount(), 1);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [CS2_039] Windfury - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a minion <b>Windfury</b>.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - WINDFURY = 1
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_039_Windfury)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windfury"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::WINDFURY), 0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 24);
//    EXPECT_EQ(curField[0]->IsExhausted(), true);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::WINDFURY), 1);
//    EXPECT_EQ(curField[0]->IsExhausted(), false);
//
//    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 18);
//    EXPECT_EQ(curField[0]->IsExhausted(), true);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [CS2_041] Ancestral Healing - COST:0
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Restore a minion
////       to full Health and
////       give it <b>Taunt</b>.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// Tag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_041_AncestralHealing)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::ROGUE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    const auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Ancestral Healing"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, AttackTask(card3, card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(opField.GetCount(), 0);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 2);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
//}
//
//// ---------------------------------------- MINION - SHAMAN
//// [CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
//// - Race: Elemental, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Deal 3 damage.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_042_FireElemental)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Elemental"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Elemental"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer,
//                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opField[0]));
//    EXPECT_EQ(opField[0]->GetHealth(), 4);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [CS2_045] Rockbiter Weapon - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a friendly character +3 Attack this turn.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_FRIENDLY_TARGET = 0
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_045_RockbiterWeapon)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rockbiter Weapon"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rockbiter Weapon"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 3);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [CS2_046] Bloodlust - COST:5
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your minions +3 Attack this turn.
//// --------------------------------------------------------
//TEST(ShamanCoreTest, CS2_046_Bloodlust)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodlust"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 9);
//    EXPECT_EQ(curField[1]->GetAttack(), 6);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [EX1_244] Totemic Might - COST:0
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your Totems +2 Health.
//// --------------------------------------------------------
//TEST(ShamanCoreTest, EX1_244_TotemicMight)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Totemic Might"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, HeroPowerTask());
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, HeroPowerTask());
//    int totem1Health = curField[0]->GetHealth();
//    int totem2Health = curField[1]->GetHealth();
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[2]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curField[0]->GetHealth(), totem1Health + 2);
//    EXPECT_EQ(curField[1]->GetHealth(), totem2Health + 2);
//    EXPECT_EQ(curField[2]->GetHealth(), 1);
//}
//
//// ----------------------------------------- SPELL - SHAMAN
//// [EX1_246] Hex - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(ShamanCoreTest, EX1_246_Hex)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hex"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hex"));
//    const auto card3 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetAttack(), 0);
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::TAUNT), 1);
//}
//
//// ---------------------------------------- MINION - SHAMAN
//// [EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:3]
//// - Race: Totem, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Adjacent minions have +2 Attack.
//// --------------------------------------------------------
//// GameTag:
//// - ADJACENT_BUFF = 1
//// - AURA = 1
//// --------------------------------------------------------
//TEST(ShamanCoreTest, EX1_565_FlametongueTotem)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = false;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Flametongue Totem"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Flametongue Totem"));
//    const auto card3 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Flametongue Totem"));
//    const auto card4 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Flametongue Totem"));
//    const auto card5 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card6 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
//    const auto card7 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card8 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 0);
//    EXPECT_EQ(curField[0]->GetHealth(), 3);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card5));
//    EXPECT_EQ(curField[1]->GetAttack(), 8);
//    EXPECT_EQ(curField[1]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[1]->GetAttack(), 10);
//    EXPECT_EQ(curField[1]->GetHealth(), 7);
//    EXPECT_EQ(curField[2]->GetAttack(), 0);
//    EXPECT_EQ(curField[2]->GetHealth(), 3);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card6));
//    EXPECT_EQ(curField[3]->GetAttack(), 3);
//    EXPECT_EQ(curField[3]->GetHealth(), 4);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[3]->GetAttack(), 5);
//    EXPECT_EQ(curField[3]->GetHealth(), 4);
//    EXPECT_EQ(curField[4]->GetAttack(), 0);
//    EXPECT_EQ(curField[4]->GetHealth(), 3);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card7));
//    EXPECT_EQ(curField[5]->GetAttack(), 5);
//    EXPECT_EQ(curField[5]->GetHealth(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(curField[5]->GetAttack(), 7);
//    EXPECT_EQ(curField[5]->GetHealth(), 1);
//    EXPECT_EQ(curField[6]->GetAttack(), 0);
//    EXPECT_EQ(curField[6]->GetHealth(), 3);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card8));
//    game.Process(opPlayer, AttackTask(card8, card7));
//
//    EXPECT_EQ(curField[4]->GetAttack(), 2);
//    EXPECT_EQ(curField[4]->GetHealth(), 3);
//    EXPECT_EQ(curField[5]->GetAttack(), 2);
//    EXPECT_EQ(curField[5]->GetHealth(), 3);
//}
//
//// ---------------------------------------- MINION - SHAMAN
//// [EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
//// - Faction: Neutral, Set: core, Rarity: free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Give a friendly minion <b>Windfury</b>.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_FRIENDLY_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - WINDFURY = 1
//// --------------------------------------------------------
//TEST(ShamanCoreTest, EX1_587_Windspeaker)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windspeaker"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::WINDFURY), 0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::WINDFURY), 0);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetGameTag(GameTag::WINDFURY), 0);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::WINDFURY), 1);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [CS2_057] Shadow Bolt - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 4 damage to a minion.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_057_ShadowBolt)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadow Bolt"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadow Bolt"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [CS2_061] Drain Life - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage. Restore 2 Health to your hero.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_061_DrainLife)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Drain Life"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    opPlayer->GetHero()->SetDamage(10);
//
//    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 5);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 22);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [CS2_062] Hellfire - COST:4
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 3 damage to all characters.
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_062_Hellfire)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hellfire"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField.GetCount(), 2);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//    EXPECT_EQ(opField.GetCount(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 27);
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetHealth(), 4);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [CS2_063] Corruption - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Choose an enemy minion. At the start of your turn, destroy it.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_ENEMY_TARGET = 0
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_063_Corruption)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Corruption"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(opField.GetCount(), 0);
//}
//
//// --------------------------------------- MINION - WARLOCK
//// [CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
//// - Race: Demon, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Deal 1 damage to all other characters.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_064_DreadInfernal)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dread Infernal"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 29);
//    EXPECT_EQ(curField[0]->GetHealth(), 6);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 29);
//}
//
//// --------------------------------------- MINION - WARLOCK
//// [CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
//// - Race: Demon, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(WarlockCoreTest, CS2_065_Voidwalker)
//{
//    // Do nothing
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [EX1_302] Mortal Coil - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage to a minion. If that kills it, draw a card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//TEST(WarlockCoreTest, EX1_302_MortalCoil)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField.GetCount(), 0);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_306] Felstalker - COST:2 [ATK:4/HP:3]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Discard a random card.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(WarlockCoreTest, EX1_306_Succubus)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felstalker"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 3);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 6);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [EX1_308] Soulfire - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 4 damage. Discard a random card.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// --------------------------------------------------------
//TEST(WarlockCoreTest, EX1_308_Soulfire)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 4);
//    EXPECT_EQ(opField.GetCount(), 0);
//
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
//
//    game.Process(curPlayer,
//                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 3);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 26);
//}
//
//// ---------------------------------------- SPELL - WARLOCK
//// [NEW1_003] Sacrificial Pact - COST:0
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Destroy a Demon. Restore 5 Health to your hero.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_TARGET_WITH_RACE = 15
//// --------------------------------------------------------
//TEST(WarlockCoreTest, NEW1_003_SacrificialPact)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(8);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sacrificial Pact"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 22);
//    EXPECT_EQ(curField.GetCount(), 2);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 27);
//    EXPECT_EQ(curField.GetCount(), 1);
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [CS2_103] Charge - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give a friendly minion <b>Charge</b>.
////       It can't attack heroes this turn.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_FRIENDLY_TARGET = 0
//// - REQ_MINION_TARGET = 0
//// --------------------------------------------------------
//// RefTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_103_Charge)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Charge"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 0);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CANNOT_ATTACK_HEROES), 0);
//
//    game.Process(curPlayer, AttackTask(card2, card3));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CANNOT_ATTACK_HEROES), 1);
//
//    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//
//    game.Process(curPlayer, AttackTask(card2, card3));
//    EXPECT_EQ(opField.GetCount(), 0);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
//    EXPECT_EQ(curField[0]->GetGameTag(GameTag::CANNOT_ATTACK_HEROES), 0);
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [CS2_105] Heroic Strike - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Give your hero +4 Attack this turn.
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_105_HeroicStrike)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heroic Strike"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heroic Strike"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 4);
//
//    game.Process(curPlayer,
//                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 26);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 0);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Weapon(card3));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 3);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 7);
//
//    game.Process(curPlayer,
//                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 19);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    EXPECT_EQ(curPlayer->GetHero()->GetAttack(), 3);
//}
//
//// --------------------------------------- WEAPON - WARRIOR
//// [CS2_106] Fiery War Axe - COST:3 [ATK:3/HP:0]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// GameTag:
//// - DURABILITY = 2
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_106_FieryWarAxe)
//{
//    // Do nothing
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [CS2_108] Execute - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Destroy a damaged enemy minion.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_TO_PLAY = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_ENEMY_TARGET = 0
//// - REQ_DAMAGED_TARGET = 0
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_108_Execute)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Execute"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField.GetCount(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, AttackTask(card2, card3));
//
//    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
//    EXPECT_EQ(opField.GetCount(), 0);
//}
//
//// --------------------------------------- WEAPON - WARRIOR
//// [CS2_112] Arcanite Reaper - COST:5 [ATK:5/HP:0]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// GameTag:
//// - DURABILITY = 2
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_112_ArcaniteReaper)
//{
//    // Do nothing
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [CS2_114] Cleave - COST:2
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 2 damage to two random enemy minions.
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_MINIMUM_ENEMY_MINIONS = 1
//// --------------------------------------------------------
//TEST(WarriorCoreTest, CS2_114_Cleave)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cleave"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cleave"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opField[1]->GetHealth(), 7);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card2));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
//    EXPECT_EQ(opField[0]->GetHealth(), 3);
//    EXPECT_EQ(opField[1]->GetHealth(), 5);
//}
//
//// --------------------------------------- MINION - WARRIOR
//// [EX1_084] Warsong Commander - COST:3 [ATK:2/HP:3]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your <b>Charge</b> minions have +1 Attack.
//// --------------------------------------------------------
//// GameTag:
//// - AURA = 1
//// --------------------------------------------------------
//// RefTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(WarriorCoreTest, EX1_084_WarsongCommander)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card4 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Warsong Commander"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//    EXPECT_EQ(curField[1]->GetAttack(), 1);
//    EXPECT_EQ(curField[2]->GetAttack(), 3);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//    EXPECT_EQ(curField[1]->GetAttack(), 2);
//    EXPECT_EQ(curField[2]->GetAttack(), 4);
//    EXPECT_EQ(curField[3]->GetAttack(), 2);
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [EX1_400] Whirlwind - COST:1
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Deal 1 damage to all minions.
//// --------------------------------------------------------
//TEST(WarriorCoreTest, EX1_400_Whirlwind)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlwind"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//    EXPECT_EQ(opField[1]->GetHealth(), 1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
//    EXPECT_EQ(curField.GetCount(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 6);
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 30);
//    EXPECT_EQ(opField.GetCount(), 1);
//    EXPECT_EQ(opField[0]->GetHealth(), 6);
//}
//
//// ---------------------------------------- SPELL - WARRIOR
//// [EX1_606] Shield Block - COST:3
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Gain 5 Armor.
////       Draw a card.
//// --------------------------------------------------------
//TEST(WarriorCoreTest, EX1_606_ShieldBlock)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetArmor(3);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Block"));
//
//    game.Process(curPlayer, PlayCardTask::Spell(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//    EXPECT_EQ(curPlayer->GetHero()->GetArmor(), 8);
//}
//
//// --------------------------------------- MINION - WARRIOR
//// [NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(WarriorCoreTest, NEW1_011_KorkronElite)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS1_042_GoldshireFootman)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
//// - Race: Elemental, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_118_MagmaRager)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
//// - Race: Beast, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_119_OasisSnapjaw)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
//// - Race: Beast, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_120_RiverCrocolisk)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_121_FrostwolfGrunt)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_122] Raid Leader - COST:3 [ATK:2/HP:2]
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your other minions have +1 Attack.
//// --------------------------------------------------------
//// GameTag:
//// - AURA = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_122_RaidLeader)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Raid Leader"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    game.Process(opPlayer, AttackTask(card3, card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_124_Wolfrider)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
//// - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_125_IronfurGrizzly)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
//// - Race: Beast, Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_127_SilverbackPatriarch)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_131_StormwindKnight)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Deal 1 damage.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_NONSELF_TARGET = 0
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_141_IronforgeRifleman)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Ironforge Rifleman"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Spell Damage +1</b>
//// --------------------------------------------------------
//// GameTag:
//// - SPELLPOWER = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_142_KoboldGeomancer)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Draw a card.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_147_GnomishInventor)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gnomish Inventor"));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Deal 2 damage.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_NONSELF_TARGET = 0
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_150_StormpikeCommando)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::HUNTER;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Stormpike Commando"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Stormpike Commando"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//
//    game.Process(curPlayer,
//                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 28);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 7);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 5);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_155] Archmage - COST:6 [ATK:4/HP:7]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Spell Damage +1</b>
//// --------------------------------------------------------
//// GameTag:
//// - SPELLPOWER = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_155_Archmage)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_162_LordOfTheArena)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
//// - Race: Murloc, Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_168_MurlocRaider)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
//// - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_171_StonetuskBoar)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
//// - Race: Beast, Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_172_BloodfenRaptor)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
//// - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_173_BluegillWarrior)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_179_SenjinShieldmasta)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_182_ChillwindYeti)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_186] War Golem - COST:7 [ATK:7/HP:7]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_186_WarGolem)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Taunt</b>
//// --------------------------------------------------------
//// GameTag:
//// - TAUNT = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_187_BootyBayBodyguard)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Deal 1 damage.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_NONSELF_TARGET = 0
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_189_ElvenArcher)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elven Archer"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(opField[0]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Summon a 1/1 Boar.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_196_RazorfenHunter)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razorfen Hunter"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//    EXPECT_EQ(curField[0]->GetHealth(), 3);
//    EXPECT_EQ(curField[1]->GetAttack(), 1);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Spell Damage +1</b>
//// --------------------------------------------------------
//// GameTag:
//// - SPELLPOWER = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_197_OgreMagi)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
//// - Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_200_BoulderfistOgre)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
//// - Race: Beast, Set: Core, Rarity: Free
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_201_CoreHound)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Charge</b>
//// --------------------------------------------------------
//// GameTag:
//// - CHARGE = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_213_RecklessRocketeer)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_222] Stormwind Champion - COST:7 [ATK:6/HP:6]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your other minions have +1/+1.
//// --------------------------------------------------------
//// GameTag:
//// - AURA = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_222_StormwindChampion)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Stormwind Champion"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card4 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//    EXPECT_EQ(curField[0]->GetHealth(), 7);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 7);
//    EXPECT_EQ(curField[0]->GetHealth(), 8);
//    EXPECT_EQ(curField[1]->GetAttack(), 6);
//    EXPECT_EQ(curField[1]->GetHealth(), 6);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    opField[0]->SetAttack(7);
//    game.Process(opPlayer, AttackTask(card3, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 7);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card4));
//    opField[0]->SetAttack(6);
//    game.Process(opPlayer, AttackTask(card4, card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 6);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Gain +1/+1 for each other friendly minion on the
//// battlefield.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, CS2_226_FrostwolfWarlord)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Frostwolf Warlord"));
//    const auto card2 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Frostwolf Warlord"));
//    const auto card3 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Frostwolf Warlord"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 4);
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[1]->GetAttack(), 5);
//    EXPECT_EQ(curField[1]->GetHealth(), 5);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[2]->GetAttack(), 6);
//    EXPECT_EQ(curField[2]->GetHealth(), 6);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [DS1_055] Darkscale Healer - COST:5 [ATK:4/HP:5]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Restore 2 Health to all friendly characters.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, DS1_055_DarkscaleHealer)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PRIEST;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darkscale Healer"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Squire"));
//    const auto card4 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    game.Process(curPlayer, PlayCardTask::Minion(card4));
//    curField[0]->SetDamage(5);
//    curField[2]->SetDamage(1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//    EXPECT_EQ(curField[2]->GetHealth(), 2);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
//// - Faction: Horde, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Restore 2 Health.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_011_VoodooDoctor)
//{
//    GameConfig config;
//    config.player1Class = CardClass::PALADIN;
//    config.player2Class = CardClass::WARRIOR;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//    curPlayer->GetHero()->SetDamage(6);
//
//    auto& opField = *(opPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
//    const auto card3 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card3));
//    opField[0]->SetDamage(1);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer,
//                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
//    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 26);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
//    EXPECT_EQ(opField[0]->GetHealth(), 2);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Draw a card.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_015_NoviceEngineer)
//{
//    GameConfig config;
//    config.player1Class = CardClass::ROGUE;
//    config.player2Class = CardClass::SHAMAN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Novice Engineer"));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//// PlayReq:
//// - REQ_TARGET_IF_AVAILABLE = 0
//// - REQ_MINION_TARGET = 0
//// - REQ_FRIENDLY_TARGET = 0
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_019_ShatteredSunCleric)
//{
//    GameConfig config;
//    config.player1Class = CardClass::HUNTER;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Shattered Sun Cleric"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironfur Grizzly"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 3);
//    EXPECT_EQ(curField[0]->GetHealth(), 3);
//
//    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 4);
//    EXPECT_EQ(curField[0]->GetHealth(), 4);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_025_DragonlingMechanic)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Dragonling Mechanic"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField.GetCount(), 2);
//    EXPECT_EQ(curField[1]->GetAttack(), 2);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
//// - Faction: Alliance, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Destroy your opponent's weapon.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_066_AcidicSwampOoze)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::ROGUE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
//    const auto card2 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
//
//    game.Process(curPlayer, PlayCardTask::Weapon(card1));
//    EXPECT_EQ(curPlayer->GetHero()->HasWeapon(), true);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curPlayer->GetHero()->HasWeapon(), false);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:7]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Whenever this minion takes damage, gain +3 Attack.
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_399_GurubashiBerserker)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARLOCK;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Gurubashi Berserker"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 5);
//
//    game.Process(opPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, HeroPowerTask(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 8);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
//// - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_506_MurlocTidehunter)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::WARLOCK;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 = Generic::DrawCard(
//        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField.GetCount(), 2);
//    EXPECT_EQ(curField[1]->GetAttack(), 1);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
//// - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: Your other Murlocs have +1 Attack.
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_508_GrimscaleOracle)
//{
//    GameConfig config;
//    config.player1Class = CardClass::SHAMAN;
//    config.player2Class = CardClass::MAGE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    auto& curField = *(curPlayer->GetFieldZone());
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grimscale Oracle"));
//    const auto card2 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grimscale Oracle"));
//    const auto card3 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
//    const auto card4 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
//    const auto card5 =
//        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card3));
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card4));
//    EXPECT_EQ(curField[2]->GetAttack(), 3);
//    EXPECT_EQ(curField[2]->GetHealth(), 1);
//
//    game.Process(curPlayer, PlayCardTask::Minion(card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 2);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//    EXPECT_EQ(curField[2]->GetAttack(), 4);
//    EXPECT_EQ(curField[2]->GetHealth(), 1);
//    EXPECT_EQ(curField[3]->GetAttack(), 2);
//    EXPECT_EQ(curField[3]->GetHealth(), 1);
//
//    game.Process(curPlayer, EndTurnTask());
//    game.ProcessUntil(Step::MAIN_START);
//
//    game.Process(opPlayer, PlayCardTask::Minion(card5));
//    game.Process(opPlayer, AttackTask(card5, card2));
//    EXPECT_EQ(curField[0]->GetAttack(), 1);
//    EXPECT_EQ(curField[0]->GetHealth(), 1);
//    EXPECT_EQ(curField[1]->GetAttack(), 3);
//    EXPECT_EQ(curField[1]->GetHealth(), 1);
//    EXPECT_EQ(curField[2]->GetAttack(), 3);
//    EXPECT_EQ(curField[2]->GetHealth(), 1);
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Spell Damage +1</b>
//// --------------------------------------------------------
//// GameTag:
//// - SPELLPOWER = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_582_DalaranMage)
//{
//    // Do nothing
//}
//
//// --------------------------------------- MINION - NEUTRAL
//// [EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
//// - Faction: Neutral, Set: Core, Rarity: Free
//// --------------------------------------------------------
//// Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
//// --------------------------------------------------------
//// GameTag:
//// - BATTLECRY = 1
//// --------------------------------------------------------
//TEST(NeutralCoreTest, EX1_593_Nightblade)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::PALADIN;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.Start();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player* curPlayer = game.GetCurrentPlayer();
//    Player* opPlayer = game.GetOpponentPlayer();
//    curPlayer->SetTotalMana(10);
//    curPlayer->SetUsedMana(0);
//    opPlayer->SetTotalMana(10);
//    opPlayer->SetUsedMana(0);
//
//    const auto card1 =
//        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nightblade"));
//
//    game.Process(curPlayer, PlayCardTask::Minion(card1));
//    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 27);
//}