// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/Auras/AdaptiveEffect.hpp>
#include <Rosetta/CardSets/HoFCardsGen.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawOpTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
using TaskList = std::vector<std::shared_ptr<ITask>>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;

void HoFCardsGen::AddHeroes(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddHeroPowers(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddDruid(PowersType& powers, PlayReqsType& playReqs,
                           EntouragesType& entourages)
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
    powers.emplace("EX1_161", power);
    playReqs.emplace("EX1_161", PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } });
}

void HoFCardsGen::AddDruidNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                     EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddHunter(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddHunterNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddMage(PowersType& powers, PlayReqsType& playReqs,
                          EntouragesType& entourages)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_031] Ice Lance - COST:1
    // - Faction: Neutral, Set: HoF, Rarity: Common
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
    powers.emplace("CS2_031", power);
    playReqs.emplace("CS2_031", PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } });
}

void HoFCardsGen::AddMageNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                    EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddPaladin(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
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
        for (auto handNum =
                 playable->player->opponent->GetHandZone()->GetCount() -
                 playable->player->GetHandZone()->GetCount();
             handNum > 0; --handNum)
        {
            Generic::Draw(playable->player);
        }
    }));
    powers.emplace("EX1_349", power);
}

void HoFCardsGen::AddPaladinNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddPriest(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [DS1_233] Mind Blast - COST:2
    // - Faction: Neutral, Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 5, true));
    powers.emplace("DS1_233", power);
}

void HoFCardsGen::AddPriestNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddRogue(PowersType& powers, PlayReqsType& playReqs,
                           EntouragesType& entourages)
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
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_128e", EntityType::MINIONS));
    powers.emplace("EX1_128", power);

    // ------------------------------------------ SPELL - ROGUE
    // [NEW1_004] Vanish - COST:6
    // - Set: HoF, Rarity: Free
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::ALL_MINIONS));
    powers.emplace("NEW1_004", power);
}

void HoFCardsGen::AddRogueNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                     EntouragesType& entourages)
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
    powers.emplace("EX1_128e", power);
}

void HoFCardsGen::AddShaman(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddShamanNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddWarlock(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
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
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::HAND, 2));
    power.AddPowerTask(std::make_shared<DiscardTask>(EntityType::STACK));
    powers.emplace("EX1_310", power);

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
    powers.emplace("EX1_316", power);
    playReqs.emplace("EX1_316",
                     PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                               { PlayReq::REQ_MINION_TARGET, 0 },
                               { PlayReq::REQ_FRIENDLY_TARGET, 0 } });
}

void HoFCardsGen::AddWarlockNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
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
    powers.emplace("EX1_316e", power);
}

void HoFCardsGen::AddWarrior(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddWarriorNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
    (void)powers;
}

void HoFCardsGen::AddNeutral(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
    Power power;

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
    powers.emplace("EX1_016", power);

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
    powers.emplace("EX1_050", power);

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
    power.AddAura(new AdaptiveEffect(
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
    powers.emplace("EX1_062", power);

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
    powers.emplace("EX1_284", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: HoF, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage your hero has taken.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new AdaptiveCostEffect([](Playable* playable) {
        return playable->player->GetHero()->GetDamage();
    }));
    powers.emplace("EX1_620", power);
}

void HoFCardsGen::AddNeutralNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
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
    powers.emplace("NEW1_027e", power);
}

void HoFCardsGen::AddAll(PowersType& powers, PlayReqsType& playReqs,
                         EntouragesType& entourages)
{
    AddHeroes(powers, playReqs, entourages);
    AddHeroPowers(powers, playReqs, entourages);

    AddDruid(powers, playReqs, entourages);
    AddDruidNonCollect(powers, playReqs, entourages);

    AddHunter(powers, playReqs, entourages);
    AddHunterNonCollect(powers, playReqs, entourages);

    AddMage(powers, playReqs, entourages);
    AddMageNonCollect(powers, playReqs, entourages);

    AddPaladin(powers, playReqs, entourages);
    AddPaladinNonCollect(powers, playReqs, entourages);

    AddPriest(powers, playReqs, entourages);
    AddPriestNonCollect(powers, playReqs, entourages);

    AddRogue(powers, playReqs, entourages);
    AddRogueNonCollect(powers, playReqs, entourages);

    AddShaman(powers, playReqs, entourages);
    AddShamanNonCollect(powers, playReqs, entourages);

    AddWarlock(powers, playReqs, entourages);
    AddWarlockNonCollect(powers, playReqs, entourages);

    AddWarrior(powers, playReqs, entourages);
    AddWarriorNonCollect(powers, playReqs, entourages);

    AddNeutral(powers, playReqs, entourages);
    AddNeutralNonCollect(powers, playReqs, entourages);
}
}  // namespace RosettaStone
