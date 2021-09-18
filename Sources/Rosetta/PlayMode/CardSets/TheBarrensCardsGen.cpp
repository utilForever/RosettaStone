// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Auras/SwitchingAura.hpp>
#include <Rosetta/PlayMode/CardSets/TheBarrensCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/ComplexTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Triggers/Triggers.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void TheBarrensCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TheBarrensCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TheBarrensCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [BAR_533] Thorngrowth Sentries - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 1/2 Turtles with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_533t", 2, SummonSide::SPELL));
    cards.emplace(
        "BAR_533",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_534] Pride's Fury - COST:4
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions +1/+3.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_534e", EntityType::MINIONS));
    cards.emplace("BAR_534", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [BAR_535] Thickhide Kodo - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<ArmorTask>(5));
    cards.emplace("BAR_535", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536] Living Seed (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast. Reduce its Cost by (1).
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536e", EntityType::STACK));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_536t")));
    cards.emplace("BAR_536", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [BAR_537] Razormane Battleguard - COST:2 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first <b>Taunt</b> minion you play each turn
    //       costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<SwitchingAura>(
        AuraType::HAND, SelfCondition::TauntMinionsPlayedThisTurn(0),
        TriggerType::PLAY_MINION, "BAR_537e"));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::HasTaunt());
    }
    cards.emplace("BAR_537", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [BAR_538] Druid of the Plains - COST:7 [ATK:7/HP:6]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Frenzy:</b> Transform into a 6/7 Kodo with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddFrenzyTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "BAR_538t"));
    cards.emplace("BAR_538", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_539] Celestial Alignment - COST:7
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Set each player to 0 Mana Crystals.
    //       Set the Cost of cards in all hands and decks to (1).
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SetManaCrystalTask>(0));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_539e", EntityType::HAND));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_539e", EntityType::DECK));
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BAR_539e", EntityType::ENEMY_HAND));
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BAR_539e", EntityType::ENEMY_DECK));
    cards.emplace("BAR_539", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [BAR_540] Plaguemaw the Rotting - COST:4 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a friendly minion with <b>Taunt</b> dies,
    //       summon a new copy of it without <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasTaunt())
    };
    power.GetTrigger()->tasks = {
        std::make_shared<SummonCopyTask>(EntityType::TARGET, false, true),
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 0)
    };
    cards.emplace("BAR_540", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_549] Mark of the Spikeshell - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       If it has <b>Taunt</b>, add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_549e", EntityType::TARGET));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasTaunt()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<CopyTask>(EntityType::TARGET,
                                                   ZoneType::HAND) }));
    cards.emplace(
        "BAR_549",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- MINION - DRUID
    // [BAR_720] Guff Runetotem - COST:3 [ATK:2/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a Nature spell,
    //       give another friendly minion +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell())
    };
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_720e", EntityType::MINIONS_NOSOURCE) };
    cards.emplace("BAR_720", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [WC_004] Fangbound Druid - COST:3 [ATK:4/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Reduce the Cost of a Beast
    //       in your hand by (2).
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<IncludeTask>(EntityType::HAND));
    power.AddDeathrattleTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("WC_004t", EntityType::STACK));
    cards.emplace("WC_004", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [WC_006] Lady Anacondra - COST:6 [ATK:3/HP:7]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Nature spells cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(AuraType::HAND, "WC_006e"));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell());
    }
    cards.emplace("WC_006", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [WC_036] Deviate Dreadfang - COST:8 [ATK:4/HP:9]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a Nature spell,
    //       summon a 4/2 Viper with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell())
    };
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "WC_036t1", SummonSide::SPELL) };
    cards.emplace("WC_036", CardDef(power));
}

void TheBarrensCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- MINION - DRUID
    // [BAR_533t] Thornguard Turtle - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_533t", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_534e] Overrun - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+3.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_534e"));
    cards.emplace("BAR_534e", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536t] Living Seed (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast. Reduce its Cost by (2).
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536te", EntityType::STACK));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_536t2")));
    cards.emplace("BAR_536t", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536t2] Living Seed (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast.
    //       Reduce its Cost by (3).
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536t2e", EntityType::STACK));
    cards.emplace("BAR_536t2", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_537e] Razorforced - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Each turn, your first <b> Taunt</b> minion costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("BAR_537e", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [BAR_538t] Druid of the Plains - COST:7 [ATK:6/HP:7]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_538t", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_539e] Vortexed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("BAR_539e", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_549e] Everbark - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_549e"));
    cards.emplace("BAR_549e", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_720e] Guff's Buff - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_720e"));
    cards.emplace("BAR_720e", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [WC_004t] Nightmare Trapped - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_004t", CardDef(power));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [WC_006e] Natural Empowerment - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_006e", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [WC_036t1] Deviate Viper - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("WC_036t1", CardDef(power));
}

void TheBarrensCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [BAR_030] Pack Kodo - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Beast,
    //       <b>Secret</b>, or weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BAR_031] Sunscale Raptor - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Shuffle a Sunscale Raptor into your deck
    //       with permanent +2/+1.
    // --------------------------------------------------------
    // RefTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_032] Piercing Shot - COST:4
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 6 damage to a minion.
    //       Excess damage hits the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<CustomTask>(
        []([[maybe_unused]] Player* player, Entity* source, Playable* target) {
            if (target == nullptr)
            {
                return;
            }

            const auto realSource = dynamic_cast<Playable*>(source);
            const auto realTarget = dynamic_cast<Character*>(target);

            const int targetHealth = realTarget->GetHealth();
            int realDamage = 6 + source->player->GetCurrentSpellPower();

            Generic::TakeDamageToCharacter(realSource, realTarget, realDamage,
                                           true);

            if (realTarget->isDestroyed)
            {
                const int remainDamage = realDamage - targetHealth;
                if (remainDamage > 0)
                {
                    Generic::TakeDamageToCharacter(realSource,
                                                   player->opponent->GetHero(),
                                                   remainDamage, false);
                }
            }
        }));
    cards.emplace(
        "BAR_032",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_033] Prospector's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       give all minions in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));
    power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<AddEnchantmentTask>("BAR_033e", EntityType::STACK)
    };
    cards.emplace("BAR_033", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_034] Tame Beast (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 2/2 Beast with <b>Rush</b>.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t3", SummonSide::SPELL));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_034t")));
    cards.emplace("BAR_034", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_035] Kolkar Pack Runner - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       summon a 1/1 Hyena with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_035t", SummonSide::RIGHT) };
    cards.emplace("BAR_035", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_037] Warsong Wrangler - COST:4 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Beast from your deck.
    //       Give all copies of it +2/+1 <i>(wherever they are)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BAR_038] Tavish Stormpike - COST:3 [ATK:2/HP:5]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a friendly Beast attacks,
    //       summon a Beast from your deck that costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BAR_551] Barak Kodobane - COST:5 [ATK:3/HP:5]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a 1, 2, and 3-Cost spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_801] Wound Prey - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage. Summon a 1/1 Hyena with <b>Rush</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    power.AddPowerTask(std::make_shared<SummonTask>("BAR_035t", 1));
    cards.emplace(
        "BAR_801",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ----------------------------------------- SPELL - HUNTER
    // [WC_007] Serpentbloom - COST:0
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a friendly Beast <b>Poisonous</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SetGameTagTask>(EntityType::TARGET,
                                                        GameTag::POISONOUS, 1));
    cards.emplace(
        "WC_007",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_TARGET_WITH_RACE, 20 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 } }));

    // ---------------------------------------- MINION - HUNTER
    // [WC_008] Sin'dorei Scentfinder - COST:4 [ATK:1/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Summon four 1/1 Hyenas with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddFrenzyTask(
        std::make_shared<SummonTask>("BAR_035t", 4, SummonSide::SPELL));
    cards.emplace("WC_008", CardDef(power));

    // ---------------------------------------- WEAPON - HUNTER
    // [WC_037] Venomstrike Bow - COST:4
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("WC_037", CardDef(power));
}

void TheBarrensCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BAR_033e] Prospector's Findings - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_033e"));
    cards.emplace("BAR_033e", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_034t] Tame Beast (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 4/4 Beast with <b>Rush</b>.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t4", SummonSide::SPELL));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_034t2")));
    cards.emplace("BAR_034t", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_034t2] Tame Beast (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 6/6 Beast with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t5", SummonSide::SPELL));
    cards.emplace("BAR_034t2", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t3] Tamed Crab - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t3", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t4] Tamed Scorpid - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t4", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t5] Tamed Thunder Lizard - COST:6 [ATK:6/HP:6]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t5", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [BAR_035t] Swift Hyena - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_035t", CardDef(power));

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BAR_037e] Centaur Call - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [WC_007e] Serpent's Bite - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [BAR_305] Flurry (Rank 1) - COST:0
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a random enemy minion.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    power.AddPowerTask(std::make_shared<SetGameTagTask>(EntityType::STACK,
                                                        GameTag::FROZEN, 1));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_305t")));
    cards.emplace(
        "BAR_305",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } }));

    // ------------------------------------------- SPELL - MAGE
    // [BAR_541] Runed Orb - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    power.AddPowerTask(std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace(
        "BAR_541",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------------- SPELL - MAGE
    // [BAR_542] Refreshing Spring Water - COST:5
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Refresh 2 Mana Crystals for each spell drawn.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_544] Reckless Apprentice - COST:4 [ATK:3/HP:5]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fire your Hero Power at all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_545] Arcane Luminary - COST:3 [ATK:4/HP:3]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Cards that didn't start in your deck cost (2) less,
    //       but not less than (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BAR_546] Wildfire - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Increase the damage of your Hero Power by 1.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_547] Mordresh Fire Eye - COST:10 [ATK:10/HP:10]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've dealt 10 damage with
    //       your Hero Power this game, deal 10 damage to
    //       all enemies.@ <i>({0} left!)</i>@ <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_748] Varden Dawngrasp - COST:4 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> all enemy minions.
    //       If any are already <b>Frozen</b>, deal 4 damage
    //       to them instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, [[maybe_unused]] Playable* target) {
            auto minions = player->opponent->GetFieldZone()->GetAll();
            for (auto& minion : minions)
            {
                if (minion->IsFrozen())
                {
                    Generic::TakeDamageToCharacter(
                        dynamic_cast<Playable*>(source), minion, 4, false);
                }
                else
                {
                    minion->SetGameTag(GameTag::FROZEN, 1);
                }
            }
        }));
    cards.emplace("BAR_748", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [BAR_812] Oasis Ally - COST:3
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion is attacked,
    //       summon a 3/6 Water Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsProposedDefender(CardType::MINION)),
                      std::make_shared<SelfCondition>(
                          SelfCondition::IsEventTargetFieldNotFull()) };
    power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("CS2_033", SummonSide::SPELL) });
    cards.emplace("BAR_812", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [BAR_888] Rimetongue - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a Frost spell,
    //       summon a 1/1 Elemental that <b><b>Freeze</b>s</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFrostSpell())
    };
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_888t", SummonSide::RIGHT) };
    cards.emplace("BAR_888", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [WC_041] Shattering Blast - COST:3
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Destroy all <b>Frozen</b> minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFrozen()) }));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("WC_041", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [WC_805] Frostweave Dungeoneer - COST:3 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell.
    //       If it's a Frost spell,
    //       summon two 1/1 Elementals that <b>Freeze</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DrawSpellTask>(1, SpellSchool::NONE, true));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsFrostSpell()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<SummonTask>("BAR_888t", SummonSide::LEFT),
            std::make_shared<SummonTask>("BAR_888t", SummonSide::RIGHT) }));
    cards.emplace("WC_805", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [WC_806] Floecaster - COST:6 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Costs (2) less for each <b>Frozen</b> enemy.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveCostEffect>([](Playable* playable) {
        auto minions = playable->player->opponent->GetFieldZone()->GetAll();
        int numFrozenEnemies = 0;

        for (auto& minion : minions)
        {
            if (minion->IsFrozen())
            {
                ++numFrozenEnemies;
            }
        }

        return 2 * numFrozenEnemies;
    }));
    cards.emplace("WC_806", CardDef(power));
}

void TheBarrensCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BAR_064e] Touch of Arcane - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b>
    //       for your next spell this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BAR_064e2] Touch of Arcane - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b>
    //       for your next spell this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BAR_305t] Flurry (Rank 2) - COST:0
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> two random enemy minions.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    power.AddPowerTask(std::make_shared<SetGameTagTask>(EntityType::STACK,
                                                        GameTag::FROZEN, 1));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_305t2")));
    cards.emplace(
        "BAR_305t",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } }));

    // ------------------------------------------- SPELL - MAGE
    // [BAR_305t2] Flurry (Rank 3) - COST:0
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> three random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 3));
    power.AddPowerTask(std::make_shared<SetGameTagTask>(EntityType::STACK,
                                                        GameTag::FROZEN, 1));
    cards.emplace(
        "BAR_305t2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } }));

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BAR_545e] Conjured Reduction - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less (but not less than 1).
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BAR_546e] Flame On! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Hero Power deals 1 more damage.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_888t] Frosted Elemental - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_888t", CardDef(power));
}

void TheBarrensCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_550] Galloping Savior - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays three
    //       cards in a turn, summon a 3/4 Steed with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::CardsPlayedThisTurn(3))
    };
    power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("BAR_550t", SummonSide::SPELL) });
    cards.emplace("BAR_550", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_871] Soldier's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       summon two 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));
    power.GetTrigger()->tasks = {
        std::make_shared<SummonTask>("CS2_101t", SummonSide::LEFT),
        std::make_shared<SummonTask>("CS2_101t", SummonSide::RIGHT)
    };
    cards.emplace("BAR_871", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_873] Knight of Anointment - COST:1 [ATK:1/HP:1]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Holy spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawSpellTask>(1, SpellSchool::HOLY));
    cards.emplace("BAR_873", CardDef(power));

    // --------------------------------------- WEAPON - PALADIN
    // [BAR_875] Sword of the Fallen - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       cast a <b>Secret</b> from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BAR_876] Northwatch Commander - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       draw a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawMinionTask>(1, false) }));
    cards.emplace("BAR_876", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_878] Veteran Warmedic - COST:4 [ATK:3/HP:5]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a Holy spell,
    //       summon a 2/2 Medic with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHolySpell())
    };
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_878t", SummonSide::SPELL) };
    cards.emplace("BAR_878", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_879] Cannonmaster Smythe - COST:5 [ATK:4/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform your <b>Secrets</b>
    //       into 3/3 Soldiers. They transform back when they die.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_880] Conviction (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a random friendly minion +3 Attack.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::MINIONS, 1));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_880e", EntityType::STACK));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_880t")));
    cards.emplace(
        "BAR_880",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_881] Invigorating Sermon - COST:4
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give +1/+1 to all minions in your hand, deck,
    //       and battlefield.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_HAND_DECK_FIELD));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_881e", EntityType::STACK));
    cards.emplace("BAR_881", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_902] Cariel Roame - COST:4 [ATK:4/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Divine Shield</b>
    //       Whenever this attacks, reduce the Cost of Holy spells
    //       in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_902e", EntityType::HAND, false, false,
        SelfCondition::IsHolySpell()) };
    cards.emplace("BAR_902", CardDef(power));

    // --------------------------------------- WEAPON - PALADIN
    // [WC_032] Seedcloud Buckler - COST:3
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your minions
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    power.AddDeathrattleTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("WC_032", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [WC_033] Judgment of Justice - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       set its Attack and Health to 1.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(
                      TaskList{ std::make_shared<SetGameTagTask>(
                                    EntityType::TARGET, GameTag::ATK, 1),
                                std::make_shared<SetGameTagTask>(
                                    EntityType::TARGET, GameTag::HEALTH, 1) }))
    };
    cards.emplace("WC_033", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [WC_034] Party Up! - COST:7
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon five 2/2 Adventurers with random bonus effects.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [BAR_550t] Holy Steed - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_550t", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [BAR_878t] Battlefield Medic - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BAR_878t", CardDef(power));

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_879e] Secrecy - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: It's a secret...
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BAR_879t] Northwatch Soldier - COST:3 [ATK:3/HP:3]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Transform back into a <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_880e] Blessed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_880e"));
    cards.emplace("BAR_880e", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_880t] Conviction (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give two random friendly minions +3 Attack.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::MINIONS, 2));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_880e", EntityType::STACK));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_880t2")));
    cards.emplace(
        "BAR_880t",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_880t2] Conviction (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give three random friendly minions +3 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::MINIONS, 3));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_880e", EntityType::STACK));
    cards.emplace(
        "BAR_880t2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_881e] Holy Might - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_881e"));
    cards.emplace("BAR_881e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_902e] Light's Strength - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BAR_902e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [WC_033e] Judged - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [BAR_307] Void Flayer - COST:4 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each spell in your hand,
    //       deal 1 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<CountTask>(EntityType::HAND_SPELL));
    power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1) }));
    cards.emplace("BAR_307", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_308] Power Word: Fortitude - COST:8
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +3/+5.
    //       Costs (1) less for each spell in your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_308e", EntityType::TARGET));
    power.AddAura(std::make_shared<AdaptiveCostEffect>([](Playable* playable) {
        int numSpellCard = 0;

        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardType() == CardType::SPELL)
            {
                if (handCard == playable)
                {
                    continue;
                }

                ++numSpellCard;
            }
        }

        return numSpellCard;
    }));
    cards.emplace(
        "BAR_308",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_309] Desperate Prayer - COST:0
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 5 Health to each hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::ENEMY_HERO, 5));
    cards.emplace("BAR_309", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [BAR_310] Lightshower Elemental - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Restore 8 Health
    //       to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 8));
    cards.emplace("BAR_310", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_311] Devouring Plague - COST:3
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 4 damage randomly split among all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        4, true));
    cards.emplace("BAR_311", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [BAR_312] Soothsayer's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       copy a spell from your opponent's deck to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BAR_313] Priest of An'she - COST:5 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> If you've restored
    //       Health this turn, gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HealthRestoredThisTurn()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BAR_313e", EntityType::SOURCE) }));
    cards.emplace("BAR_313", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314] Condemn (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_314t")));
    cards.emplace("BAR_314", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [BAR_315] Serena Bloodfeather - COST:2 [ATK:1/HP:1]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an enemy minion.
    //       Steal Attack and Health from it until this has more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BAR_735] Xyrella - COST:4 [ATK:4/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've restored Health this turn,
    //       deal that much damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [WC_013] Devout Dungeoneer - COST:3 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell.
    //       If it's a Holy spell, reduce its Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DrawSpellTask>(1, SpellSchool::NONE, true));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsHolySpell()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "WC_013e", EntityType::STACK) }));
    cards.emplace("WC_013", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [WC_014] Against All Odds - COST:5
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Destroy all odd-Attack minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [WC_803] Cleric of An'she - COST:1 [ATK:1/HP:2]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've restored Health this turn,
    //       <b>Discover</b> a spell from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BAR_313e] Sun's Strength - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_313e"));
    cards.emplace("BAR_313e", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314t] Condemn (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_314t2")));
    cards.emplace("BAR_314t", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314t2] Condemn (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 3, true));
    cards.emplace("BAR_314t2", CardDef(power));
}

void TheBarrensCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [BAR_316] Oil Rig Ambusher - COST:4 [ATK:4/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    //       If this entered your hand this turn, deal 4 instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BAR_317] Field Contact - COST:3 [ATK:3/HP:2]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a <b>Battlecry</b>
    //       or <b>Combo</b> card, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_318] Silverleaf Poison - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your weapon "After your hero attacks, draw a card."
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319] Wicked Stab (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BAR_320] Efficient Octo-bot - COST:2 [ATK:1/HP:4]
    // - Race: Mechanical, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Reduce the cost of cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_321] Paralytic Poison - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your weapon +1 Attack and "Your hero is
    //       <b>Immune</b> while attacking."
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [BAR_322] Swinetusk Shank - COST:3
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a Poison, gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_323] Yoink! - COST:1
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Hero Power and set its Cost to (0).
    //       Swap back after 2 uses.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BAR_324] Apothecary Helbrim - COST:4 [ATK:3/HP:2]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Add a random Poison to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BAR_552] Scabbs Cutterbutter - COST:4 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Combo:</b> The next two cards you play this turn
    //       cost (3) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [WC_015] Water Moccasin - COST:3 [ATK:2/HP:5]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Has <b>Poisonous</b> while you have no other minions.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [WC_016] Shroud of Concealment - COST:3
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw 2 minions.
    //       Any played this turn gain <b>Stealth</b> for 1 turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [WC_017] Savory Deviate Delight - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform a minion in both players' hands
    //       into a Pirate or <b>Stealth</b> minion.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319t] Wicked Stab (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage. <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319t2] Wicked Stab (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 6 damage.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BAR_321e] Paralytic Poison - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Immune</b> while attacking.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BAR_323e] Yoink! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BAR_552o] Cookin! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: The next two cards you play this turn costs (3) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [WC_016e] Cloaking - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Play this turn to gain <b>Stealth</b> for 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [WC_016e2] Cloaked - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [BAR_040] South Coast Chieftain - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control another Murloc,
    //       deal 2 damage.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BAR_041] Nofin Can Stop Us - COST:3
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    //       Give your Murlocs an extra +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_043] Tinyfin's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, draw a Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BAR_044] Chain Lightning (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion and a random adjacent one.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_045] Arid Stormer - COST:3 [ATK:2/HP:5]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       gain <b>Rush</b> and <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_048] Bru'kan - COST:4 [ATK:5/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Nature Spell Damage +3</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_750] Earth Revenant - COST:4 [ATK:2/HP:6]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_751] Spawnpool Forager - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Tinyfin.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_848] Lilypad Lurker - COST:5 [ATK:5/HP:6]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental
    //       last turn, transform an enemy minion into a
    //       0/1 Frog with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_860] Firemancer Flurgl - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a Murloc, deal 1 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [WC_005] Primal Dungeoneer - COST:3 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell.
    //       If it's a Nature spell, also draw an Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [WC_020] Perpetual Flame - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 3 damage to a random enemy minion.
    //       If it dies, recast this. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [WC_042] Wailing Vapor - COST:1 [ATK:1/HP:3]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play an Elemental, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [BAR_044t] Chain Lightning (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion and a random adjacent one.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BAR_044t2] Chain Lightning (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion and a random adjacent one.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BAR_536e] Living Seed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BAR_536e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BAR_536t2e] Living Seed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(3)));
    cards.emplace("BAR_536t2e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BAR_536te] Living Seed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("BAR_536te", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_751t] Diremuck Tinyfin - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: THE_BARRENS
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [WC_042e] Rising Gas - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_910] Grimoire of Sacrifice - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a friendly minion.
    //       Deal 2 damage to all enemy minions.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_911] Soul Rend - COST:4
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions.
    //       Destroy a card in your deck for each killed.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_912] Apothecary's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       summon a 1-Cost minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_913] Altar of Fire - COST:1
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Destroy the top 3 cards of each deck.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914] Imp Swarm (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon a 3/2 Imp.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_915] Kabal Outfitter - COST:3 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Give another random friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_916] Blood Shard Bristleback - COST:3 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>. <b>Battlecry:</b>
    //       If your deck contains 10 or fewer cards,
    //       deal 6 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_917] Barrens Scavenger - COST:6 [ATK:6/HP:6]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) while your deck has 10 or fewer cards.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_918] Tamsin Roame - COST:3 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you cast a Shadow spell that costs (1) or more,
    //       add a copy to your hand that costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_919] Neeru Fireblade - COST:5 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck is empty, open a portal
    //       that fills your board with 3/2 Imps each turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [WC_021] Unstable Shadow Blast - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 6 damage to a minion.
    //       Excess damage hits your hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [WC_022] Final Gasp - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion. If it dies,
    //       summon a 2/2 Adventurer with a random bonus effect.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [WC_023] Stealer of Souls - COST:4 [ATK:2/HP:6]
    // - Race: Demon, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you draw a card,
    //       change its Cost to Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914t] Imp Swarm (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon two 3/2 Imps.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914t2] Imp Swarm (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon three 3/2 Imps.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_914t3] Imp Familiar - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BAR_915e] Outfitted - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BAR_918e] Gathered Shadows - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BAR_919t] Burning Blade Portal - COST:11 [ATK:0/HP:1]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       fill your board with 3/2 Imps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [BAR_334] Overlord Saurfang - COST:7 [ATK:5/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Resurrect 2 friendly <b>Frenzy</b>
    //       minions. Deal 1 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BAR_840] Whirling Combatant - COST:4 [ATK:3/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry and Frenzy:</b>
    //       Deal 1 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - FRENZY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_841] Bulk Up - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a random <b>Taunt</b> minion in your hand +1/+1
    //       and copy it.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842] Conditioning (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +1/+1.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BAR_843] Warsong Envoy - COST:1 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Gain +1 Attack
    //       for each damaged character.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [BAR_844] Outrider's Axe - COST:4
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks and kills a minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_845] Rancor - COST:4
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    //       Gain 2 Armor for each destroyed.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BAR_846] Mor'shan Elite - COST:5 [ATK:4/HP:4]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> If your hero
    //       attacked this turn, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BAR_847] Rokara - COST:3 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After a friendly minion attacks and survives,
    //       give it +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BAR_896] Stonemaul Anchorman - COST:5 [ATK:4/HP:5]
    // - Race: Pirate, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Frenzy:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [WC_024] Man-at-Arms - COST:2 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a weapon equipped,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [WC_025] Whetstone Hatchet - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       give a minion in your hand +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [WC_026] Kresh, Lord of Turtling - COST:6 [ATK:3/HP:9]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Gain 8 Armor.
    //       <b>Deathrattle:</b> Equip a 2/5 Turtle Spike.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - FRENZY = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BAR_841e] Swoll - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842t] Conditioning (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +2/+2.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842t2] Conditioning (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BAR_896e] Incensed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [WC_024e] Armed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [WC_025e] Armed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [WC_026t] Turtle Spike - COST:4
    // - Set: THE_BARRENS
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_306] Sigil of Flame - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       deal 3 damage to all minions.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_325] Razorboar - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a <b>Deathrattle</b>
    //       minion that costs (3) or less from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_326] Razorfen Beastmaster - COST:3 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a <b>Deathrattle</b>
    //       minion that costs (4) or less from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_327] Vile Call - COST:3
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two 2/2 Demons with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_328] Vengeful Spirit - COST:4 [ATK:4/HP:4]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Draw 2 <b>Deathrattle</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_329] Death Speaker Blackthorn - COST:7 [ATK:3/HP:6]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 3 <b>Deathrattle</b>
    //       minions that cost (5) or less from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BAR_330] Tuskpiercer - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a <b>Deathrattle</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_333] Kurtrus Ashfallen - COST:4 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Attack the left and right-most
    //       enemy minions.
    //       <b>Outcast:</b> <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - OUTCAST = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_705] Sigil of Silence - COST:0
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       <b>Silence</b> all enemy minions.
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891] Fury (Rank 1) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [WC_003] Sigil of Summoning - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       summon two 2/2 Demons with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [WC_040] Taintheart Tormenter - COST:8 [ATK:8/HP:8]
    // - Race: Demon, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Your opponent's spells cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [WC_701] Felrattler - COST:3 [ATK:3/HP:2]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_327t] Ravenous Vilefiend - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e2] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e3] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891t] Fury (Rank 2) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +3 Attack this turn.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891t2] Fury (Rank 3) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [WC_003t] Wailing Demon - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [BAR_020] Razormane Raider - COST:5 [ATK:5/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Attack a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_021] Gold Road Grunt - COST:5 [ATK:3/HP:7]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Frenzy:</b> Gain Armor equal to the damage taken.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_022] Peon - COST:2 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Add a random spell from your class
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_024] Oasis Thrasher - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Deal 3 damage to the enemy Hero.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_025] Sunwell Initiate - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Gain <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_026] Death's Head Cultist - COST:3 [ATK:2/HP:4]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_027] Darkspear Berserker - COST:4 [ATK:5/HP:7]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_042] Primordial Protector - COST:8 [ATK:6/HP:6]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw your highest Cost spell.
    //       Summon a random minion with the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_060] Hog Rancher - COST:3 [ATK:3/HP:2]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 Hog with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_061] Ratchet Privateer - COST:3 [ATK:4/HP:3]
    // - Race: Pirate, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_062] Lushwater Murcenary - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Murloc, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_063] Lushwater Scout - COST:2 [ATK:1/HP:3]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a Murloc,
    //       give it +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_064] Talented Arcanist - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next spell this turn has
    //       <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_065] Venomous Scorpid - COST:3 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_069] Injured Marauder - COST:4 [ATK:5/HP:10]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 6 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_070] Gruntled Patron - COST:4 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Summon another Gruntled Patron.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_071] Taurajo Brave - COST:6 [ATK:4/HP:8]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_072] Burning Blade Acolyte - COST:5 [ATK:1/HP:1]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/8 Demonspawn
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_073] Barrens Blacksmith - COST:5 [ATK:3/HP:5]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Give your other minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_074] Far Watch Post - COST:2 [ATK:2/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't attack. After your opponent draws a card,
    //       it costs (1) more <i>(up to 10)</i>.  
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_075] Crossroads Watch Post - COST:4 [ATK:4/HP:6]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Can't attack. Whenever your opponent casts a spell,
    //       give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_076] Mor'shan Watch Post - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack. After your opponent plays a minion,
    //       summon a 2/2 Grunt.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_077] Kargal Battlescar - COST:7 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 5/5 Lookout for each
    //       Watch Post you've summoned this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_078] Blademaster Samuro - COST:4 [ATK:1/HP:6]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Frenzy:</b> Deal damage equal to this minion's
    //       Attack to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - FRENZY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_079] Kazakus, Golem Shaper - COST:4 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no 4-Cost cards,
    //       build a custom Golem.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_080] Shadow Hunter Vol'jin - COST:5 [ATK:3/HP:6]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion.
    //       Swap it with a random one in its owner's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_081] Southsea Scoundrel - COST:4 [ATK:5/HP:5]
    // - Race: Pirate, Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a card
    //       in your opponent's deck. They draw theirs as well.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_082] Barrens Trapper - COST:3 [ATK:2/HP:4]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Your <b>Deathrattle</b> cards cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_430] Horde Operative - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy your opponent's <b>Secrets</b>
    //       and put them into play.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_721] Mankrik - COST:3 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Help Mankrik find his wife!
    //       She was last seen somewhere in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_743] Toad of the Wilds - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you're holding a Nature spell,
    //       gain +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_744] Spirit Healer - COST:4 [ATK:3/HP:6]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a Holy spell,
    //       give a random friendly minion +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_745] Hecklefang Hyena - COST:2 [ATK:2/HP:4]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_854] Kindling Elemental - COST:1 [ATK:1/HP:2]
    // - Race: Elemental, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Elemental you play
    //       costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_890] Crossroads Gossiper - COST:3 [ATK:4/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly <b>Secret</b> is revealed, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_027] Devouring Ectoplasm - COST:3 [ATK:3/HP:2]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Adventurer
    //       with a random bonus effect.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_028] Meeting Stone - COST:1 [ATK:0/HP:2]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, add a 2/2 Adventurer
    //       with a random bonus effect to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_029] Selfless Sidekick - COST:7 [ATK:6/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a random weapon from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_030] Mutanus the Devourer - COST:7 [ATK:4/HP:4]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Eat a minion in your opponent's hand.
    //       Gain its stats.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_035] Archdruid Naralex - COST:3 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       While <b>Dormant</b>, add a Dream card to your hand
    //       at the end of your turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_041e] Mrrgrrrrgle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_041e2] MrrGRRRRgle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_045e] Storm Cloud - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Windfury</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_060t] Hog - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_061e] Privateering - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_062e] Bolstered - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_063e] Emboldened - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_072t] Demonspawn - COST:6 [ATK:5/HP:8]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_073e] Reforged - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_074e] Spotted! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_075e] Patrolling - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_076t] Watchful Grunt - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_077t] Lookout - COST:5 [ATK:5/HP:5]
    // - Set: THE_BARRENS
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_079_m1] Lesser Golem - COST:1 [ATK:1/HP:1]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_079_m2] Greater Golem - COST:5 [ATK:5/HP:5]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_079_m3] Superior Golem - COST:10 [ATK:10/HP:10]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t10] Wildvine - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t10b] Wildvine - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_079t10be] Wildpower - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_079t10ce] Wildpower - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_079t10e] Wildpower - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t11] Gromsblood - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t12] Icecap - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t12b] Icecap - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> two random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t12c] Icecap - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t13] Firebloom - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t13b] Firebloom - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to two random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t13c] Firebloom - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t14] Mageroyal - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t14b] Mageroyal - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t14c] Mageroyal - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Spell Damage +4</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t15] Kingsblood - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t15b] Kingsblood - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t15c] Kingsblood - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 4 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t4] Swifthistle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t5] Earthroot - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t6] Sungrass - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t7] Liferoot - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t8] Fadeleaf - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_079t9] Grave Moss - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_082e] Barrens Trapping - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_308e] Power Word: Fortitude - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3/+5.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BAR_308e"));
    cards.emplace("BAR_308e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_315e1] Flurry of Talons - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_315e2] Protective Feathers - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_315e3] Slashed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Stolen Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_315e4] Dazed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Stolen Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_318e] Silverleaf Poison - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: After your hero attacks, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_320e] Training - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_322e] Improvised Edge - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Durability.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_333e] Invigorated - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_552e] Cookin! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Your next two cards this turn costs (3) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_705e] Sigil - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Triggers at the start of your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_721t] Olgra, Mankrik's Wife - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 3/7 Mankrik, who immediately attacks
    //       the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_721t2] Mankrik, Consumed by Hatred - COST:5 [ATK:3/HP:10]
    // - Set: THE_BARRENS
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_743e] Toadin' Wild - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_744e] Lifted Spirits - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Health
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e2] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e3] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_847e] Battle Hardened - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_854e] Kindle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Your next Elemental costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_890e] Shameless - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_COIN1] The Coin - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BAR_COIN2] The Coin - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_013e] Ray of Light - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_013e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_023e] Stolen Soul - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs Health instead of Mana.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_030e] Devoured - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Increased Stats
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t] Deadly Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t2] Burly Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t3] Devout Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t4] Relentless Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t5] Arcane Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t6] Sneaky Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t7] Vital Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t8] Swift Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_035e] Dreaming - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 2 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_035e2] Asleep - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [WC_040e] Tormented - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode