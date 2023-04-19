// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/TheBarrensCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
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
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_533t", 2, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BAR_533", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BAR_534] Pride's Fury - COST:4
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions +1/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_534e", EntityType::MINIONS));
    cards.emplace("BAR_534", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ArmorTask>(5));
    cards.emplace("BAR_535", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536] Living Seed (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast. Reduce its Cost by (1).
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536e", EntityType::STACK));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_536t")));
    cards.emplace("BAR_536", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BAR_537] Razormane Battleguard - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first <b>Taunt</b> minion you play each turn
    //       costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SwitchingAura>(
        AuraType::HAND, SelfCondition::TauntMinionsPlayedThisTurn(0),
        TriggerType::PLAY_MINION, "BAR_537e"));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::HasTaunt());
    }
    cards.emplace("BAR_537", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "BAR_538t"));
    cards.emplace("BAR_538", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BAR_539] Celestial Alignment - COST:8
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Set your Mana Crystals to 0.
    //       Set the cost of all cards in your hand and deck to (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetManaCrystalTask>(0));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_539e", EntityType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_539e", EntityType::DECK));
    cards.emplace("BAR_539", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasTaunt())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<SummonCopyTask>(EntityType::TARGET, false, true),
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 0)
    };
    cards.emplace("BAR_540", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_549e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasTaunt()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<CopyTask>(EntityType::TARGET,
                                                   ZoneType::HAND) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BAR_549", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_720e", EntityType::MINIONS_NOSOURCE) };
    cards.emplace("BAR_720", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("WC_004t", EntityType::STACK));
    cards.emplace("WC_004", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::HAND, "WC_006e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell());
    }
    cards.emplace("WC_006", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNatureSpell())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "WC_036t1", SummonSide::SPELL) };
    cards.emplace("WC_036", cardDef);
}

void TheBarrensCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [BAR_533t] Thornguard Turtle - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_533t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_534e] Overrun - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_534e"));
    cards.emplace("BAR_534e", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536t] Living Seed (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast. Reduce its Cost by (2).
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536te", EntityType::STACK));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_536t2")));
    cards.emplace("BAR_536t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BAR_536t2] Living Seed (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a Beast.
    //       Reduce its Cost by (3).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_536t2e", EntityType::STACK));
    cards.emplace("BAR_536t2", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_537e] Razorforced - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Each turn, your first <b> Taunt</b> minion costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("BAR_537e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BAR_538t] Druid of the Plains - COST:7 [ATK:6/HP:7]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_538t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_539e] Vortexed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("BAR_539e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_549e] Everbark - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_549e"));
    cards.emplace("BAR_549e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BAR_720e] Guff's Buff - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_720e"));
    cards.emplace("BAR_720e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [WC_004t] Nightmare Trapped - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_004t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [WC_006e] Natural Empowerment - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_006e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [WC_036t1] Deviate Viper - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_036t1", cardDef);
}

void TheBarrensCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](const Player* player, Entity* source, Playable* target) {
            if (!target)
            {
                return;
            }

            const auto realSource = dynamic_cast<Playable*>(source);
            const auto realTarget = dynamic_cast<Character*>(target);

            const int targetHealth = realTarget->GetHealth();
            const int realDamage = 6 + source->player->GetCurrentSpellPower();

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
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BAR_032", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<AddEnchantmentTask>("BAR_033e", EntityType::STACK)
    };
    cards.emplace("BAR_033", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t3", SummonSide::SPELL));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_034t")));
    cards.emplace("BAR_034", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_035t", SummonSide::RIGHT) };
    cards.emplace("BAR_035", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BAR_037] Warsong Wrangler - COST:4 [ATK:3/HP:4]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Beast from your deck.
    //       Give all copies of it +2/+1 <i>(wherever they are)</i>.
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BAR_035t", 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BAR_801", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::POISONOUS, 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_TARGET_WITH_RACE, 20 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("WC_007", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<SummonTask>("BAR_035t", 4, SummonSide::SPELL));
    cards.emplace("WC_008", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [WC_037] Venomstrike Bow - COST:4
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_037", cardDef);
}

void TheBarrensCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BAR_033e] Prospector's Findings - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_033e"));
    cards.emplace("BAR_033e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t4", SummonSide::SPELL));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_034t2")));
    cards.emplace("BAR_034t", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [BAR_034t2] Tame Beast (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 6/6 Beast with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_034t5", SummonSide::SPELL));
    cards.emplace("BAR_034t2", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t3] Tamed Crab - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t3", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t4] Tamed Scorpid - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t4", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BAR_034t5] Tamed Thunder Lizard - COST:6 [ATK:6/HP:6]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_034t5", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BAR_035t] Swift Hyena - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_035t", cardDef);

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
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_305t")));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("BAR_305", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BAR_541", cardDef);

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
    // [BAR_546] Wildfire - COST:1
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Increase the damage of your Hero Power by 1 this game.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BAR_547] Mordresh Fire Eye - COST:8 [ATK:8/HP:8]
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CustomTask>([](const Player* player, Entity* source,
                                        [[maybe_unused]] Playable* target) {
            const auto minions = player->opponent->GetFieldZone()->GetAll();

            for (auto& minion : minions)
            {
                if (minion->IsFrozen())
                {
                    Generic::TakeDamageToCharacter(
                        dynamic_cast<Playable*>(source), minion, 4, false);
                }
                else
                {
                    minion->Freeze();
                }
            }
        }));
    cards.emplace("BAR_748", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsProposedDefender(CardType::MINION)),
                      std::make_shared<SelfCondition>(
                          SelfCondition::IsEventTargetFieldNotFull()) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("CS2_033", SummonSide::SPELL) });
    cards.emplace("BAR_812", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFrostSpell())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_888t", SummonSide::RIGHT) };
    cards.emplace("BAR_888", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [WC_041] Shattering Blast - COST:3
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Destroy all <b>Frozen</b> minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("WC_041", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawSpellTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsFrostSpell()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<SummonTask>("BAR_888t", SummonSide::LEFT),
            std::make_shared<SummonTask>("BAR_888t", SummonSide::RIGHT) }));
    cards.emplace("WC_805", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [WC_806] Floecaster - COST:6 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Costs (2) less for each <b>Frozen</b> enemy.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            const auto minions =
                playable->player->opponent->GetFieldZone()->GetAll();
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
    cards.emplace("WC_806", cardDef);
}

void TheBarrensCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::SPELLPOWER, EffectOperator::ADD, 2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->removeTrigger = { TriggerType::TURN_END, nullptr };
    }
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("BAR_064e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_305t2")));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("BAR_305t", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 3));
    cardDef.power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("BAR_305t2", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_888t", cardDef);
}

void TheBarrensCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::CardsPlayedThisTurn(3))
    };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("BAR_550t", SummonSide::SPELL) });
    cards.emplace("BAR_550", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<SummonTask>("CS2_101t", SummonSide::LEFT),
        std::make_shared<SummonTask>("CS2_101t", SummonSide::RIGHT)
    };
    cards.emplace("BAR_871", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BAR_873] Knight of Anointment - COST:1 [ATK:1/HP:1]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Holy spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawSpellTask>(SpellSchool::HOLY, 1));
    cards.emplace("BAR_873", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { ComplexTask::CastSecretFromDeck() };
    cards.emplace("BAR_875", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawMinionTask>(1, false) }));
    cards.emplace("BAR_876", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHolySpell())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_878t", SummonSide::SPELL) };
    cards.emplace("BAR_878", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        ComplexTask::GiveBuffToRandomMinionInField("BAR_880e"));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_880t")));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BAR_880", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_881] Invigorating Sermon - COST:4
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give +1/+1 to all minions in your hand, deck,
    //       and battlefield.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_HAND_DECK_FIELD));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_881e", EntityType::STACK));
    cards.emplace("BAR_881", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_902e", EntityType::HAND, false, false,
        SelfCondition::IsHolySpell()) };
    cards.emplace("BAR_902", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddDeathrattleTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("WC_032", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
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
    cards.emplace("WC_033", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [WC_034] Party Up! - COST:7
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon five 2/2 Adventurers with random bonus effects.
    // --------------------------------------------------------
    // Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
    //            WC_034t5, WC_034t6, WC_034t7, WC_034t8
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>(5));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cardDef.property.entourages =
        Entourages{ "WC_034t",  "WC_034t2", "WC_034t3", "WC_034t4",
                    "WC_034t5", "WC_034t6", "WC_034t7", "WC_034t8" };
    cards.emplace("WC_034", cardDef);
}

void TheBarrensCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [BAR_550t] Holy Steed - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_550t", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BAR_878t] Battlefield Medic - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_878t", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_880e"));
    cards.emplace("BAR_880e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_880e", EntityType::STACK));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_880t2")));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BAR_880t", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [BAR_880t2] Conviction (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give three random friendly minions +3 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::MINIONS, 3));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_880e", EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BAR_880t2", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_881e] Holy Might - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_881e"));
    cards.emplace("BAR_881e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BAR_902e] Light's Strength - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BAR_902e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [WC_033e] Judged - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::HAND_SPELL));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1) }));
    cards.emplace("BAR_307", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_308e", EntityType::TARGET));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            int numSpellCard = 0;

            for (const auto& handCard :
                 playable->player->GetHandZone()->GetAll())
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
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BAR_308", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_309] Desperate Prayer - COST:0
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 5 Health to each hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::ENEMY_HERO, 5));
    cards.emplace("BAR_309", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 8));
    cards.emplace("BAR_310", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        4, true));
    cards.emplace("BAR_311", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HealthRestoredThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BAR_313e", EntityType::SOURCE) }));
    cards.emplace("BAR_313", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314] Condemn (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_314t")));
    cards.emplace("BAR_314", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HealthRestoredThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<FuncNumberTask>([](const Playable* playable) {
                return playable->player->GetAmountHealedThisTurn();
            }),
            std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS) }));
    cards.emplace("BAR_735", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawSpellTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsHolySpell()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "WC_013e", EntityType::STACK) }));
    cards.emplace("WC_013", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [WC_014] Against All Odds - COST:5
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Destroy all odd-Attack minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOddAttackMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("WC_014", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HealthRestoredThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(
                  DiscoverType::SPELL_FROM_DECK) }));
    cards.emplace("WC_803", cardDef);
}

void TheBarrensCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BAR_313e] Sun's Strength - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_313e"));
    cards.emplace("BAR_313e", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314t] Condemn (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_314t2")));
    cards.emplace("BAR_314t", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BAR_314t2] Condemn (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 3, true));
    cards.emplace("BAR_314t2", cardDef);
}

void TheBarrensCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsBattlecryCard()),
        std::make_shared<SelfCondition>(SelfCondition::IsComboCard())
    };
    cardDef.power.GetTrigger()->conditionLogic = MultiCondLogic::OR;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("BAR_317", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_318] Silverleaf Poison - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your weapon "After your hero attacks, draw a card."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_318e", EntityType::WEAPON));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } };
    cards.emplace("BAR_318", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319] Wicked Stab (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_319t")));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BAR_319", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BAR_320] Efficient Octo-bot - COST:3 [ATK:1/HP:4]
    // - Race: Mechanical, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Reduce the cost of cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<AddEnchantmentTask>("BAR_320e", EntityType::HAND));
    cards.emplace("BAR_320", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_321] Paralytic Poison - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your weapon +1 Attack and "Your hero is
    //       <b>Immune</b> while attacking."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_321e", EntityType::WEAPON));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } };
    cards.emplace("BAR_321", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [BAR_322] Swinetusk Shank - COST:3
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a Poison, gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsPoison())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_322e", EntityType::WEAPON) };
    cards.emplace("BAR_322", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddPoisonTask>(1));
    cardDef.power.AddDeathrattleTask(std::make_shared<AddPoisonTask>(1));
    cards.emplace("BAR_324", cardDef);

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
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319t] Wicked Stab (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage. <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_319t2")));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BAR_319t", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BAR_319t2] Wicked Stab (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 6, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BAR_319t2", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BAR_321e] Paralytic Poison - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Immune</b> while attacking.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DS1_188e", EntityType::HERO) };
    cards.emplace("BAR_321e", cardDef);

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
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_040] South Coast Chieftain - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control another Murloc,
    //       deal 2 damage.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::MINIONS_NOSOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("BAR_040", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [BAR_041] Nofin Can Stop Us - COST:3
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    //       Give your Murlocs an extra +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CustomTask>([](const Player* player, Entity* source,
                                        [[maybe_unused]] Playable* target) {
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (minion->card->GetRace() == Race::MURLOC)
                {
                    Generic::AddEnchantment(Cards::FindCardByID("BAR_041e2"),
                                            dynamic_cast<Playable*>(source),
                                            minion);
                }
                else
                {
                    Generic::AddEnchantment(Cards::FindCardByID("BAR_041e"),
                                            dynamic_cast<Playable*>(source),
                                            minion);
                }
            }
        }));
    cards.emplace("BAR_041", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_043] Tinyfin's Caravan - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, draw a Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawRaceMinionTask>(
        Race::MURLOC, 1, false) };
    cards.emplace("BAR_043", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsPlayElementalMinionLastTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BAR_045e", EntityType::SOURCE) }));
    cards.emplace("BAR_045", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_048] Bru'kan - COST:4 [ATK:5/HP:4]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Nature Spell Damage +3</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::SPELLPOWER_NATURE, 3));
    cards.emplace("BAR_048", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1));
    cards.emplace("BAR_750", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_751] Spawnpool Forager - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Tinyfin.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BAR_751t", SummonSide::DEATHRATTLE));
    cards.emplace("BAR_751", cardDef);

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
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_ELEMENTAL_PLAYED_LAST_TURN = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsPlayElementalMinionLastTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<TransformTask>(EntityType::TARGET,
                                                        "hexfrog") }));
    cardDef.property.playReqs = PlayReqs{
        { PlayReq::REQ_ENEMY_TARGET, 0 },
        { PlayReq::REQ_MINION_TARGET, 0 },
        { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_ELEMENTAL_PLAYED_LAST_TURN, 0 }
    };
    cards.emplace("BAR_848", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 1) };
    cards.emplace("BAR_860", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawSpellTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsNatureSpell()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawRaceMinionTask>(Race::ELEMENTAL, 1,
                                                             false) }));
    cards.emplace("WC_005", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [WC_020] Perpetual Flame - COST:2
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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::ELEMENTAL))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "WC_042e", EntityType::SOURCE) };
    cards.emplace("WC_042", cardDef);
}

void TheBarrensCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BAR_536e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BAR_536t2e] Living Seed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(3)));
    cards.emplace("BAR_536t2e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BAR_536te] Living Seed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("BAR_536te", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BAR_751t] Diremuck Tinyfin - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_751t", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [WC_042e] Rising Gas - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("WC_042e"));
    cards.emplace("WC_042e", cardDef);
}

void TheBarrensCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_910] Grimoire of Sacrifice - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a friendly minion.
    //       Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("BAR_910", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::SummonCostMinionFromDeck(
        1) };
    cards.emplace("BAR_912", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_913] Altar of Fire - COST:1
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Destroy the top 3 cards of each deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DestroyDeckCardTask>(3, false));
    cardDef.power.AddPowerTask(std::make_shared<DestroyDeckCardTask>(3, true));
    cards.emplace("BAR_913", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914] Imp Swarm (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon a 3/2 Imp.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_914t3", SummonSide::SPELL));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_914t")));
    cards.emplace("BAR_914", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_915e", EntityType::STACK));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("BAR_915e", EntityType::STACK));
    cards.emplace("BAR_915", cardDef);

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
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_MAXIMUM_CARDS_IN_DECK = 10
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::MaximumCardsInDeck(10)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 6) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MAXIMUM_CARDS_IN_DECK,
                    10 } };
    cards.emplace("BAR_916", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (playable->player->GetDeckZone()->GetCount() <= 10)
            {
                return playable->GetGameTag(GameTag::COST) - 1;
            }

            return 0;
        }));
    cards.emplace("BAR_917", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](const Player* player, Entity* source, Playable* target) {
            if (!target)
            {
                return;
            }

            const auto realSource = dynamic_cast<Playable*>(source);
            const auto realTarget = dynamic_cast<Character*>(target);

            const int targetHealth = realTarget->GetHealth();
            const int realDamage = 6 + source->player->GetCurrentSpellPower();

            Generic::TakeDamageToCharacter(realSource, realTarget, realDamage,
                                           true);

            if (realTarget->isDestroyed)
            {
                const int remainDamage = realDamage - targetHealth;

                if (remainDamage > 0)
                {
                    Generic::TakeDamageToCharacter(
                        realSource, player->GetHero(), remainDamage, false);
                }
            }
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("WC_021", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [WC_022] Final Gasp - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion. If it dies,
    //       summon a 2/2 Adventurer with a random bonus effect.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
    //            WC_034t5, WC_034t6, WC_034t7, WC_034t8
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomEntourageTask>(),
                        std::make_shared<SummonStackTask>() }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.entourages =
        Entourages{ "WC_034t",  "WC_034t2", "WC_034t3", "WC_034t4",
                    "WC_034t5", "WC_034t6", "WC_034t7", "WC_034t8" };
    cards.emplace("WC_022", cardDef);

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
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914t] Imp Swarm (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon two 3/2 Imps.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_914t3", 2, SummonSide::SPELL));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_914t2")));
    cards.emplace("BAR_914t", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BAR_914t2] Imp Swarm (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon three 3/2 Imps.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_914t3", 3, SummonSide::SPELL));
    cards.emplace("BAR_914t2", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [BAR_914t3] Imp Familiar - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_914t3", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BAR_915e] Outfitted - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_915e"));
    cards.emplace("BAR_915e", cardDef);

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
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDead()),
        std::make_shared<SelfCondition>(SelfCondition::HasFrenzy()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS_NOSOURCE, 1));
    cards.emplace("BAR_334", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS_NOSOURCE, 1));
    cardDef.power.AddFrenzyTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS_NOSOURCE, 1));
    cards.emplace("BAR_840", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::HasTaunt()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_841e", EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("BAR_841", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842] Conditioning (Rank 1) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +1/+1.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BAR_842e", EntityType::MINIONS_HAND));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_842t")));
    cards.emplace("BAR_842", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<IncludeTask>(EntityType::ALL));
    cardDef.power.AddFrenzyTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }));
    cardDef.power.AddFrenzyTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddFrenzyTask(std::make_shared<AddEnchantmentTask>(
        "BAR_896e", EntityType::SOURCE, true));
    cards.emplace("BAR_843", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [BAR_844] Outrider's Axe - COST:4
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks and kills a minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDefenderDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("BAR_844", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_845] Rancor - COST:4
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    //       Gain 2 Armor for each destroyed.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, Playable* target) {
            int count = 0;

            player->GetFieldZone()->ForEach([&](const Playable* minion) {
                if (minion->isDestroyed)
                {
                    ++count;
                }
            });

            player->opponent->GetFieldZone()->ForEach(
                [&](const Playable* minion) {
                    if (minion->isDestroyed)
                    {
                        ++count;
                    }
                });

            const auto& armorTask = std::make_shared<ArmorTask>(2 * count);
            armorTask->SetPlayer(player);
            armorTask->SetSource(source);
            armorTask->SetTarget(target);

            armorTask->Run();

            return TaskStatus::COMPLETE;
        }));
    cards.emplace("BAR_845", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsAttackThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<CopyTask>(EntityType::SOURCE,
                                                   ZoneType::PLAY) }));
    cards.emplace("BAR_846", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNotDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_847e", EntityType::EVENT_SOURCE) };
    cards.emplace("BAR_847", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BAR_896] Stonemaul Anchorman - COST:5 [ATK:4/HP:6]
    // - Race: Pirate, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Frenzy:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<DrawTask>(1));
    cards.emplace("BAR_896", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsWeaponEquipped()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "WC_024e", EntityType::SOURCE) }));
    cards.emplace("WC_024", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::GiveBuffToRandomMinionInHand("WC_025e")
    };
    cards.emplace("WC_025", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<ArmorTask>(8));
    cardDef.power.AddDeathrattleTask(std::make_shared<WeaponTask>("WC_026t"));
    cards.emplace("WC_026", cardDef);
}

void TheBarrensCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BAR_841e] Swoll - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_841e"));
    cards.emplace("BAR_841e", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842t] Conditioning (Rank 2) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +2/+2.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BAR_842e2", EntityType::MINIONS_HAND));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_842t2")));
    cards.emplace("BAR_842t", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [BAR_842t2] Conditioning (Rank 3) - COST:2
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give minions in your hand +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BAR_842e3", EntityType::MINIONS_HAND));
    cards.emplace("BAR_842t2", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BAR_896e] Incensed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("BAR_896e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [WC_024e] Armed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("WC_024e"));
    cards.emplace("WC_024e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [WC_025e] Armed - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("WC_025e"));
    cards.emplace("WC_025e", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [WC_026t] Turtle Spike - COST:4
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_026t", cardDef);
}

void TheBarrensCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_306] Sigil of Flame - COST:2
    // - Set: THE_BARRENS, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       deal 3 damage to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 3, true) };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("BAR_306", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsCost(3, RelaSign::LEQ)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("BAR_325", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsCost(4, RelaSign::LEQ)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("BAR_326", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_327] Vile Call - COST:3
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two 2/2 Demons with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_327t", 2, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BAR_327", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddOutcastTask(std::make_shared<DrawMinionTask>(
        DrawMinionType::DEATHRATTLE, 2, false));
    cards.emplace("BAR_328", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle()),
        std::make_shared<SelfCondition>(
            SelfCondition::IsCost(5, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 3));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("BAR_329", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BAR_330] Tuskpiercer - COST:1
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a <b>Deathrattle</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawMinionTask>(
        DrawMinionType::DEATHRATTLE, 1, false));
    cards.emplace("BAR_330", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS_LEFTMOST));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::ENEMY_MINIONS_RIGHTMOST, std::vector<EntityType>(), true));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::SOURCE, EntityType::STACK, true));
    cardDef.power.AddOutcastTask(
        std::make_shared<AddEnchantmentTask>("BAR_333e", EntityType::SOURCE));
    cards.emplace("BAR_333", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SilenceTask>(
        EntityType::ENEMY_MINIONS) };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("BAR_705", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891] Fury (Rank 1) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_891e", EntityType::HERO));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(5, "BAR_891t")));
    cards.emplace("BAR_891", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "WC_003t", 2, SummonSide::SPELL) };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("WC_003", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::ENEMY_HAND, "WC_040e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cards.emplace("WC_040", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1));
    cards.emplace("WC_701", cardDef);
}

void TheBarrensCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- MINION - DEMONHUNTER
    // [BAR_327t] Ravenous Vilefiend - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_327t", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_891e"));
    cards.emplace("BAR_891e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e2] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_891e2"));
    cards.emplace("BAR_891e2", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BAR_891e3] Fury - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_891e3"));
    cards.emplace("BAR_891e3", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891t] Fury (Rank 2) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +3 Attack this turn.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_891e2", EntityType::HERO));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::RankSpellTrigger(10, "BAR_891t2")));
    cards.emplace("BAR_891t", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BAR_891t2] Fury (Rank 3) - COST:1
    // - Set: THE_BARRENS, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_891e3", EntityType::HERO));
    cards.emplace("BAR_891t2", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [WC_003t] Wailing Demon - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_003t", cardDef);
}

void TheBarrensCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_020] Razormane Raider - COST:5 [ATK:5/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Attack a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<IncludeTask>(EntityType::ENEMIES));
    cardDef.power.AddFrenzyTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddFrenzyTask(
        std::make_shared<AttackTask>(EntityType::SOURCE, EntityType::STACK));
    cards.emplace("BAR_020", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            int damage = dynamic_cast<Minion*>(source)->GetDamage();

            const auto& armorTask = std::make_shared<ArmorTask>(damage);
            armorTask->SetPlayer(player);
            armorTask->SetSource(source);
            armorTask->SetTarget(target);

            armorTask->Run();
        }));

    cards.emplace("BAR_021", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<RandomSpellTask>(CardClass::PLAYER_CLASS, 1));
    cardDef.power.AddFrenzyTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("BAR_022", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_024] Oasis Thrasher - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Deal 3 damage to the enemy Hero.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cards.emplace("BAR_024", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("BAR_025", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::HERO, 4));
    cards.emplace("BAR_026", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_027] Darkspear Berserker - COST:4 [ATK:5/HP:7]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::HERO, 5));
    cards.emplace("BAR_027", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawSpellTask>(DrawSpellType::HIGHEST_COST, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::STACK, GameTag::COST));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomMinionNumberTask>(GameTag::COST));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("BAR_042", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_060t", 1, SummonSide::RIGHT));
    cards.emplace("BAR_060", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_061] Ratchet Privateer - COST:3 [ATK:4/HP:3]
    // - Race: Pirate, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_061e", EntityType::WEAPON));
    cards.emplace("BAR_061", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_062] Lushwater Murcenary - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Murloc, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::MINIONS_NOSOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BAR_062e", EntityType::SOURCE) }));
    cards.emplace("BAR_062", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_063e", EntityType::TARGET) };
    cards.emplace("BAR_063", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_064] Talented Arcanist - COST:2 [ATK:1/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next spell this turn has
    //       <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_064e", EntityType::SOURCE));
    cards.emplace("BAR_064", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("BAR_065", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::SOURCE, 6));
    cards.emplace("BAR_069", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_070] Gruntled Patron - COST:4 [ATK:3/HP:3]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Summon another Gruntled Patron.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<SummonTask>("BAR_070", 1, SummonSide::RIGHT));
    cards.emplace("BAR_070", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_071] Taurajo Brave - COST:6 [ATK:4/HP:8]
    // - Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cards.emplace("BAR_071", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BAR_072t", SummonSide::DEATHRATTLE));
    cards.emplace("BAR_072", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_073] Barrens Blacksmith - COST:5 [ATK:3/HP:5]
    // - Set: THE_BARRENS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Frenzy:</b> Give your other minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(std::make_shared<AddEnchantmentTask>(
        "BAR_073e", EntityType::MINIONS_NOSOURCE));
    cards.emplace("BAR_073", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_DRAW_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsCost(9, RelaSign::LEQ))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_074e", EntityType::TARGET) };
    cards.emplace("BAR_074", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_075e", EntityType::MINIONS) };
    cards.emplace("BAR_075", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BAR_076t", SummonSide::RIGHT) };
    cards.emplace("BAR_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_077] Kargal Battlescar - COST:7 [ATK:5/HP:5]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 5/5 Lookout for each
    //       Watch Post you've summoned this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetPlayerGameTagTask>(
        GameTag::NUM_WATCH_POSTS_SUMMONED_THIS_GAME));
    cardDef.power.AddPowerTask(std::make_shared<SummonNumberTask>(
        "BAR_077t", false, SummonSide::RIGHT));
    cards.emplace("BAR_077", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddFrenzyTask(
        std::make_shared<GetGameTagTask>(EntityType::SOURCE, GameTag::ATK));
    cardDef.power.AddFrenzyTask(
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("BAR_078", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle());
    }
    cards.emplace("BAR_082", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "BAR_721t"));
    cards.emplace("BAR_721", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsHoldingSpell(SpellSchool::NATURE)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BAR_743e", EntityType::SOURCE) }));
    cards.emplace("BAR_743", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHolySpell())
    };
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::GiveBuffToRandomMinionInField("BAR_744e");
    cards.emplace("BAR_744", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_745] Hecklefang Hyena - COST:2 [ATK:2/HP:4]
    // - Race: Beast, Set: THE_BARRENS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 3));
    cards.emplace("BAR_745", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BAR_854e", EntityType::SOURCE));
    cards.emplace("BAR_854", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::SECRET_REVEALED));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BAR_890e", EntityType::SOURCE) };
    cards.emplace("BAR_890", cardDef);

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
    // Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
    //            WC_034t5, WC_034t6, WC_034t7, WC_034t8
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>());
    cardDef.property.entourages =
        Entourages{ "WC_034t",  "WC_034t2", "WC_034t3", "WC_034t4",
                    "WC_034t5", "WC_034t6", "WC_034t7", "WC_034t8" };
    cards.emplace("WC_027", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomEntourageTask>(),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cardDef.property.entourages =
        Entourages{ "WC_034t",  "WC_034t2", "WC_034t3", "WC_034t4",
                    "WC_034t5", "WC_034t6", "WC_034t7", "WC_034t8" };
    cards.emplace("WC_028", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_029] Selfless Sidekick - COST:7 [ATK:6/HP:6]
    // - Set: THE_BARRENS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a random weapon from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::EquipWeaponFromDeck());
    cards.emplace("WC_029", cardDef);

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
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_041e] Mrrgrrrrgle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_041e"));
    cards.emplace("BAR_041e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_041e2] MrrGRRRRgle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_041e2"));
    cards.emplace("BAR_041e2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_045e] Storm Cloud - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Windfury</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_045e"));
    cards.emplace("BAR_045e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_060t] Hog - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_060t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_061e] Privateering - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_061e"));
    cards.emplace("BAR_061e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_062e] Bolstered - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_062e"));
    cards.emplace("BAR_062e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_063e] Emboldened - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_063e"));
    cards.emplace("BAR_063e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_072t] Demonspawn - COST:6 [ATK:5/HP:8]
    // - Race: Demon, Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_072t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_073e] Reforged - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_073e"));
    cards.emplace("BAR_073e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_074e] Spotted! - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AddCost(1)));
    cards.emplace("BAR_074e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_075e] Patrolling - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_075e"));
    cards.emplace("BAR_075e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_076t] Watchful Grunt - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_076t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_077t] Lookout - COST:5 [ATK:5/HP:5]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_077t", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_308e"));
    cards.emplace("BAR_308e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("BAR_318e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_320e] Training - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BAR_320e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_322e] Improvised Edge - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1 Durability.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::DurabilityN(1)));
    cards.emplace("BAR_322e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_333e] Invigorated - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_333e"));
    cards.emplace("BAR_333e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<SummonTask>("BAR_721t2", SummonSide::SPELL, true));
    cardDef.power.AddTopdeckTask(std::make_shared<AttackTask>(
        EntityType::STACK, EntityType::ENEMY_HERO, true));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BAR_721t2", SummonSide::SPELL, true));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::STACK, EntityType::ENEMY_HERO, true));
    cards.emplace("BAR_721t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BAR_721t2] Mankrik, Consumed by Hatred - COST:5 [ATK:3/HP:7]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BAR_721t2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_743e] Toadin' Wild - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_743e"));
    cards.emplace("BAR_743e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_744e] Lifted Spirits - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2 Health
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_744e"));
    cards.emplace("BAR_744e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_842e"));
    cards.emplace("BAR_842e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e2] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_842e2"));
    cards.emplace("BAR_842e2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_842e3] Gains - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_842e3"));
    cards.emplace("BAR_842e3", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_847e] Battle Hardened - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_847e"));
    cards.emplace("BAR_847e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_854e] Kindle - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: Your next Elemental costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::ELEMENTAL));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::ELEMENTAL)) };
    }
    cards.emplace("BAR_854e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BAR_890e] Shameless - COST:0
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BAR_890e"));
    cards.emplace("BAR_890e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("WC_013e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t2] Burly Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t2", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t3] Devout Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t3", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t4] Relentless Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t4", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t5] Arcane Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t5", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t6] Sneaky Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t6", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t7] Vital Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t7", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [WC_034t8] Swift Adventurer - COST:2 [ATK:2/HP:2]
    // - Set: THE_BARRENS
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("WC_034t8", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AddCost(2)));
    cards.emplace("WC_040e", cardDef);
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