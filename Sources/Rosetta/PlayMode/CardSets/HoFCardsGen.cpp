// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveEffect.hpp>
#include <Rosetta/PlayMode/CardSets/HoFCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawOpTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncPlayableTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathNumberIndexTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SilenceTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void HoFCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [EX1_161] Naturalize - COST:1
    // - Faction: Neutral, Set: HoF, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion. Your opponent draws 2 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cards.emplace(
        "EX1_161",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));
}

void HoFCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_031] Ice Lance - COST:1
    // - Faction: Neutral, Set: HoF, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a character. If it was already <b>Frozen</b>,
    //       deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<SetGameTagTask>(
                   EntityType::TARGET, GameTag::FROZEN, 1) }));
    cards.emplace(
        "CS2_031",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));
}

void HoFCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PALADIN
    // [EX1_349] Divine Favor - COST:3
    // - Faction: Neutral, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw cards until you have as many in hand
    //       as your opponent
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<FuncNumberTask>([](Playable* playable) {
        const int diffHands =
            playable->player->opponent->GetHandZone()->GetCount() -
            playable->player->GetHandZone()->GetCount();
        return diffHands > 0 ? diffHands : 0;
    }));
    power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("EX1_349", CardDef(power));
}

void HoFCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
    // - Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever a minion is healed, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("CS2_235", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_236] Divine Spirit - COST:2
    // - Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Double a minion's Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::HEALTH));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(EntityType::TARGET,
                                                        GameTag::DAMAGE, 0, 1));
    power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "CS2_236e", EntityType::TARGET, true));
    cards.emplace(
        "CS2_236",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [DS1_233] Mind Blast - COST:2
    // - Faction: Neutral, Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 5, true));
    cards.emplace("DS1_233", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
    // - Faction: Neutral, Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Double the damage and healing of your spells and Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::ADD, 1) }));
    cards.emplace("EX1_350", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
    // - Faction: Neutral, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your cards and powers that restore Health
    //       now deal damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::HEALING_DOES_DAMAGE,
                                             EffectOperator::SET, 1) }));
    cards.emplace("EX1_591", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_624] Holy Fire - COST:6
    // - Faction: Priest, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage. Restore 5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cards.emplace(
        "EX1_624",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));
}

void HoFCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS2_236e] Divine Spirit (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This minion has double Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Enchants::AddHealthScriptTag));
    cards.emplace("CS2_236e", CardDef(power));
}

void HoFCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_128] Conceal - COST:1
    // - Faction: Neutral, Set: HoF, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_128e", EntityType::MINIONS, false, false,
        SelfCondition::HasNotStealth()));
    cards.emplace("EX1_128", CardDef(power));

    // ------------------------------------------ SPELL - ROGUE
    // [NEW1_004] Vanish - COST:6
    // - Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::ALL_MINIONS));
    cards.emplace("NEW1_004", CardDef(power));
}

void HoFCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_128e] Conceal - COST:1
    // - Set: HoF
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::Stealth));
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { std::make_shared<RemoveEnchantmentTask>() };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_128e", CardDef(power));
}

void HoFCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
    // - Race: Demon, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>. <b>Battlecry:</b> Discard two random cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DiscardTask>(2));
    cards.emplace("EX1_310", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_316] Power Overwhelming - COST:1
    // - Faction: Neutral, Set: HoF, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a friendly minion +4/+4 until end of turn.
    //       Then, it dies. Horribly.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_316e", EntityType::TARGET));
    cards.emplace(
        "EX1_316",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 } }));
}

void HoFCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_316e] Power Overwhelming (*) - COST:0
    // - Faction: Neutral, Set: HoF
    // --------------------------------------------------------
    // Text: This minion has +4/+4, but will die a horrible death
    //       at the end of the turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_316e"));
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::TARGET) };
    cards.emplace("EX1_316e", CardDef(power));
}

void HoFCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
    // - Set: HoF, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_007", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
    // - Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Take control of a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    power.AddDeathrattleTask(std::make_shared<ControlTask>(EntityType::STACK));
    cards.emplace("EX1_016", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
    // - Faction: Horde, Set: HoF, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SilenceTask>(EntityType::TARGET));
    cards.emplace(
        "EX1_048",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(2));
    power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cards.emplace("EX1_050", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
    // - Race: Murloc, Faction: Neutral. Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>. Has +1 Attack for each other Murloc on the
    // battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [](Playable* playable) {
            int addAttackAmount = 0;
            const auto& myMinions = playable->player->GetFieldZone()->GetAll();
            const auto& opMinions =
                playable->player->opponent->GetFieldZone()->GetAll();

            for (const auto& minion : myMinions)
            {
                if (playable->GetZonePosition() == minion->GetZonePosition())
                {
                    continue;
                }

                if (minion->IsRace(Race::MURLOC))
                {
                    ++addAttackAmount;
                }
            }

            for (const auto& minion : opMinions)
            {
                if (minion->IsRace(Race::MURLOC))
                {
                    ++addAttackAmount;
                }
            }

            return addAttackAmount;
        }));
    cards.emplace("EX1_062", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 4 or
    //       more minions, take control of one at random.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            return playables.size() > 3 ? playables : std::vector<Playable*>{};
        }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldFull()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::STACK) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<ControlTask>(EntityType::STACK) }));
    cards.emplace("EX1_085", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveCostEffect>([](Playable* playable) {
        return playable->player->GetHandZone()->GetCount() - 1;
    }));
    cards.emplace("EX1_105", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_116] Leeroy Jenkins - COST:5 [ATK:6/HP:2]
    // - Faction: Alliance, Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>. <b>Battlecry:</b> Summon two 1/1 Whelps
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonOpTask>("EX1_116t") }, 2));
    cards.emplace("EX1_116", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
    // - Race: Dragon, Faction: Neutral, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_284", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_298] Ragnaros the Firelord - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't attack. At the end of your turn, deal 8 damage
    //       to a random enemy.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMIES),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 8)
    };
    cards.emplace("EX1_298", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage your hero has taken.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveCostEffect>([](Playable* playable) {
        return playable->player->GetHero()->GetDamage();
    }));
    cards.emplace("EX1_620", CardDef(power));
}

void HoFCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_027e] Yarrr! (*) - COST:0
    // - Set: HoF
    // --------------------------------------------------------
    // Text: Southsea Captain is granting +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("NEW1_027e"));
    cards.emplace("NEW1_027e", CardDef(power));
}

void HoFCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
