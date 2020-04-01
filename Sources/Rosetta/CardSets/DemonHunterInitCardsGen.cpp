// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

namespace RosettaStone
{
using PlayReqs = std::map<PlayReq, int>;

void DemonHunterInitCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_173] Command the Illidari - COST:5
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon six 1/1 Illidari with <b>Rush</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("BT_036t", 6));
    cards.emplace("BT_173", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175] Twin Slice - COST:0
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +1 Attack this turn.
    //       Add 'Second Slice' to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "BT_175t", 1));
    cards.emplace("BT_175", CardDef(power));

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BT_271] Flamereaper - COST:7 [ATK:4/HP:0]
    // - Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever your hero attacks.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { std::make_shared<FuncNumberTask>(
        [](Playable* playable) {
            const auto target = dynamic_cast<Minion*>(
                playable->game->currentEventData->eventTarget);
            if (target == nullptr)
            {
                return;
            }

            for (auto& minion : target->GetAdjacentMinions())
            {
                minion->TakeDamage(playable,
                                   playable->player->GetHero()->GetAttack());
            }
        }) };
    cards.emplace("BT_271", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_351] Battlefiend (*) - COST:1 [ATK:2/HP:2]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BT_351e", EntityType::SOURCE) };
    cards.emplace("BT_351", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_354] Blade Dance - COST:2
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal damage equal to your hero's Attack
    //       to 3 random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 3));
    power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ATK));
    power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK, true));
    cards.emplace(
        "BT_354",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } }));
}

void DemonHunterInitCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_175e] Twin Slice (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BT_175e"));
    cards.emplace("BT_175e", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175t] Second Slice - COST:0
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +1 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    cards.emplace("BT_175t", CardDef(power));

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_351e] Felheartened - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("BT_351e", CardDef(power));
}

void DemonHunterInitCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);
}
}  // namespace RosettaStone
