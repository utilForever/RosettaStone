// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CustomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathAddTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomMinionNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

namespace RosettaStone
{
using PlayReqs = std::map<PlayReq, int>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

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

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_355] Wrathscale Naga (*) - COST:3 [ATK:3/HP:1]
    // - Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: After a friendly minion dies,
    //       deal 3 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 3)
    };
    cards.emplace("BT_355", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_407] Ur'zul Horror (*) - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a 2/1 Lost Soul to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "BT_407t"));
    cards.emplace("BT_407", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_416] Raging Felscreamer (*) - COST:4 [ATK:4/HP:4]
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Demon you play costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_416e", EntityType::SOURCE));
    cards.emplace("BT_416", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_427] Feast of Souls - COST:2
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card for each friendly minion that died this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const int num = player->GetNumFriendlyMinionsDiedThisTurn();

            for (int i = 0; i < num; ++i)
            {
                Generic::Draw(player, nullptr);
            }
        }));
    cards.emplace("BT_427", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_481] Nethrandamus (*) - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: Demon Hunter Initiate, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two random 0-Cost minions.
    //       <i>(Upgrades each time a friendly minion dies!)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    power.AddPowerTask(std::make_shared<RandomMinionNumberTask>(GameTag::COST));
    power.AddPowerTask(std::make_shared<SummonTask>(SummonSide::LEFT));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    power.AddPowerTask(std::make_shared<RandomMinionNumberTask>(GameTag::COST));
    power.AddPowerTask(std::make_shared<SummonTask>(SummonSide::RIGHT));
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1),
    };
    cards.emplace("BT_481", CardDef(power));
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

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_407t] Lost Soul (*) - COST:1 [ATK:2/HP:1]
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("BT_407t", CardDef(power));

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_416e] Felscream (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Your next Demon costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(AuraType::HAND,
                                         EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::DEMON)) };
    }
    cards.emplace("BT_416e", CardDef(power));
}

void DemonHunterInitCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);
}
}  // namespace RosettaStone
