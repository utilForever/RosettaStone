// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>
#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Enchants/Effects.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchants.hpp>

namespace RosettaStone::Battlegrounds
{
using PlayReqs = std::map<PlayReq, int>;

void BattlegroundsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier1Minions(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BG_CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Cat.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(SummonTask{ "BG_CFM_315t", 1 });
    cards.emplace("BG_CFM_315", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BG_EX1_531] Scavenging Hyena - TIER:1 [ATK:2/HP:2]
    // - Race: Beast, Set: Expert1
    // --------------------------------------------------------
    // Text: Whenever a friendly Beast dies, gain +2/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger{ TriggerType::DEATH });
    power.GetTrigger().value().SetTriggerSource(TriggerSource::FRIENDLY);
    power.GetTrigger().value().SetTasks(std::vector<TaskType>{
        AddEnchantmentTask{ "EX1_531e", EntityType::SOURCE } });
    power.GetTrigger().value().SetCondition(
        SelfCondition{ SelfCondition::IsRace(Race::BEAST) });
    cards.emplace("BG_EX1_531", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [YOD_026] Fiendish Servant - TIER:1 [ATK:2/HP:1]
    // - Race: Demon, Set: YoD
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give this minion's Attack
    //       to a random friendly minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        GetGameTagTask{ EntityType::SOURCE, GameTag::ATK });
    power.AddDeathrattleTask(RandomTask{ EntityType::MINIONS, 1 });
    power.AddDeathrattleTask(
        AddEnchantmentTask{ "Yod_026e", EntityType::STACK, true });
    cards.emplace("YOD_026", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [LOOT_013] Vulgar Homunculus - TIER:1 [ATK:2/HP:4]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 2 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(DamageHeroTask{ 2 });
    cards.emplace("LOOT_013", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_004] Wrath Weaver - TIER:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Battlegrounds
    // --------------------------------------------------------
    // Text: After you play a Demon, deal 1 damage to your hero
    //       and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger{ TriggerType::AFTER_PLAY_MINION });
    power.GetTrigger().value().SetTriggerSource(
        TriggerSource::MINIONS_EXCEPT_SELF);
    power.GetTrigger().value().SetTasks(std::vector<TaskType>{
        DamageHeroTask{ 1 },
        AddEnchantmentTask{ "BGS_004e", EntityType::SOURCE } });
    power.GetTrigger().value().SetCondition(
        SelfCondition{ SelfCondition::IsRace(Race::DEMON) });
    cards.emplace("BGS_004", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_039] Dragonspawn Lieutenant - TIER:1 [ATK:2/HP:2]
    // - Race: Dragon, Set: Battlegrounds
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("BGS_039", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_019] Red Whelp - TIER:1 [ATK:1/HP:2]
    // - Race: Dragon, Set: Battlegrounds
    // --------------------------------------------------------
    // Text: <b>Start of Combat:</b> Deal 1 damage per friendly
    //       Dragon to one random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddStartCombatTask(CountTask{
        EntityType::MINIONS_NOSOURCE, 0,
        std::vector<SelfCondition>{ SelfCondition::IsRace(Race::DRAGON) } });
    power.AddStartCombatTask(RepeatNumberStartTask{ 2 });
    power.AddStartCombatTask(RandomTask{ EntityType::ENEMY_MINIONS, 1 });
    power.AddStartCombatTask(DamageTask{ EntityType::STACK, 1 });
    power.AddStartCombatTask(RepeatNumberEndTask{});
    cards.emplace("BGS_019", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BOT_445] Mecharoo - TIER:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Boomsday
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Jo-E Bot.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        SummonTask{ "BOT_445t", 1, SummonSide::DEATHRATTLE });
    cards.emplace("BOT_445", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [GVG_103] Micro Machine - TIER:1 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Gvg
    // --------------------------------------------------------
    // Text: At the start of each turn, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger{ TriggerType::TURN_START });
    power.GetTrigger().value().SetTasks(std::vector<TaskType>{
        AddEnchantmentTask{ "GVG_076a", EntityType::SOURCE } });
    cards.emplace("GVG_103", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [EX1_509] Murloc Tidecaller - TIER:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: Expert1
    // --------------------------------------------------------
    // Text: Whenever you summon a Murloc, gain +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger{ TriggerType::SUMMON });
    power.GetTrigger().value().SetTriggerSource(TriggerSource::FRIENDLY);
    power.GetTrigger().value().SetTasks(std::vector<TaskType>{
        AddEnchantmentTask{ "EX1_509e", EntityType::SOURCE } });
    power.GetTrigger().value().SetCondition(
        SelfCondition{ SelfCondition::IsRace(Race::MURLOC) });
    cards.emplace("EX1_509", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [EX1_506] Murloc Tidehunter - TIER:1 [ATK:2/HP:1]
    // - Race: Murloc, Set: Core
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(SummonTask{ "EX1_506a", 1, SummonSide::RIGHT });
    cards.emplace("EX1_506", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [UNG_073] Rockpool Hunter - TIER:1 [ATK:2/HP:3]
    // - Race: Murloc, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Murloc +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 14
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(
        AddEnchantmentTask{ "UNG_073e", EntityType::TARGET });
    cards.emplace(
        "UNG_073",
        CardDef{ power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                  { PlayReq::REQ_MINION_TARGET, 0 },
                                  { PlayReq::REQ_TARGET_WITH_RACE, 14 },
                                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } } });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_055] Deck Swabbie - TIER:1 [ATK:2/HP:2]
    // - Race: Pirate, Set: Battlegrounds
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the cost of upgrading
    //       Bob's Tavern by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(ReduceTavernCostTask{ TavernButton::UPGRADE, 1 });
    cards.emplace("BGS_055", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_061] Scallywag - TIER:1 [ATK:3/HP:1]
    // - Race: Pirate, Set: Battlegrounds
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Pirate.
    //       It attacks immediately.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        SummonTask{ "BGS_061t", 1, SummonSide::DEATHRATTLE, true });
    power.AddDeathrattleTask(AttackTask{ EntityType::STACK });
    cards.emplace("BGS_061", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [ICC_038] Righteous Protector - TIER:1 [ATK:1/HP:1]
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("ICC_038", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [OG_221] Selfless Hero - TIER:1 [ATK:2/HP:1]
    // - Set: Og
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(IncludeTask{ EntityType::MINIONS });
    power.AddDeathrattleTask(RandomTask{ EntityType::STACK, 1 });
    power.AddDeathrattleTask(
        SetGameTagTask{ EntityType::STACK, GameTag::DIVINE_SHIELD, 1 });
    cards.emplace("OG_221", CardDef{ power });
}

void BattlegroundsCardsGen::AddTier2Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier3Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier4Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier5Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier6Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTokenMinions(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BG_CFM_315t] Tabbycat (*) - TIER:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("BG_CFM_315t", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BOT_445t] Jo-E Bot (*) - TIER:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Boomsday
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("BOT_445t", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [EX1_506a] Murloc Scout (*) - TIER:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Core
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("EX1_506a", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [BGS_061t] Sky Pirate (*) - TIER:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Battlegrounds
    // --------------------------------------------------------
    power.ClearData();
    cards.emplace("BGS_061t", CardDef{ power });
}

void BattlegroundsCardsGen::AddEnchantments(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [EX1_531e] Well Fed (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack and Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{
        std::vector<Effect>{ Effects::AttackN(2), Effects::HealthN(1) } });
    cards.emplace("EX1_531e", CardDef{ power });

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [Yod_026e] Servant's Sacrifice (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{ Enchants::AddAttackScriptTag });
    cards.emplace("Yod_026e", CardDef(power));

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [BGS_004e] Wrath Woven (*) - COST:0
    // - Set: Battlegrounds
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{
        std::vector<Effect>{ Effects::AttackN(2), Effects::HealthN(2) } });
    cards.emplace("BGS_004e", CardDef{ power });

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [GVG_076a] Pistons (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{ std::vector<Effect>{ Effects::AttackN(1) } });
    cards.emplace("GVG_076a", CardDef{ power });

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [EX1_509e] Blarghghl (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{ std::vector<Effect>{ Effects::AttackN(1) } });
    cards.emplace("EX1_509e", CardDef{ power });

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [UNG_073e] Trained (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("UNG_073e"));
    cards.emplace("UNG_073e", CardDef{ power });
}

void BattlegroundsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddTier1Minions(cards);
    AddTier2Minions(cards);
    AddTier3Minions(cards);
    AddTier4Minions(cards);
    AddTier5Minions(cards);
    AddTier6Minions(cards);

    AddTokenMinions(cards);
    AddEnchantments(cards);
}
}  // namespace RosettaStone::Battlegrounds
