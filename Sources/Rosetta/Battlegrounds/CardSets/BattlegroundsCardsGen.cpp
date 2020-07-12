// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>
#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Enchants/Effects.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchants.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::Battlegrounds
{
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
    // [CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Cat.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(SummonTask{ "CFM_315t", 1 });
    cards.emplace("CFM_315", CardDef{ power });

    // --------------------------------- MINION - BATTLEGROUNDS
    // [EX1_531] Scavenging Hyena - TIER:1 [ATK:2/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Common
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
    cards.emplace("EX1_531", CardDef{ power });

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

    // --------------------------------- MINION - BATTLEGROUNDS
    // [YOD_026] Fiendish Servant - TIER:1 [ATK:2/HP:1]
    // - Race: Demon, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give this minion's Attack
    //       to a random friendly minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        GetGameTagTask{ EntityType::SOURCE, GameTag::ATK });
    power.AddDeathrattleTask(RandomTask{ EntityType::MINIONS_NOSOURCE, 1 });
    power.AddDeathrattleTask(
        AddEnchantmentTask{ "YOD_026e", EntityType::STACK, true });
    cards.emplace("YOD_026", CardDef{ power });

    // ---------------------------- ENCHANTMENT - BATTLEGROUNDS
    // [YOD_026e] Servant's Sacrifice (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant{ Enchants::AddAttackScriptTag });
    cards.emplace("YOD_026e", CardDef(power));
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

void BattlegroundsCardsGen::AddMinionsNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------- MINION - BATTLEGROUNDS
    // [CFM_315t] Tabbycat (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs
    // --------------------------------------------------------
}

void BattlegroundsCardsGen::AddSpellsNonCollect(
    std::map<std::string, CardDef>& cards)
{
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

    AddMinionsNonCollect(cards);
    AddSpellsNonCollect(cards);
}
}  // namespace RosettaStone::Battlegrounds
