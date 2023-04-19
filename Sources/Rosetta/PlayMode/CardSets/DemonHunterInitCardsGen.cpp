// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void DemonHunterInitCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_173] Command the Illidari - COST:5
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon six 1/1 Illidari with <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BT_036t", 6));
    cards.emplace("BT_173", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175] Twin Slice - COST:1
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    //       Add 'Second Slice' to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "BT_175t", 1));
    cards.emplace("BT_175", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BT_271] Flamereaper - COST:7 [ATK:4/HP:0]
    // - Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever
    //       your hero attacks.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            const auto target = dynamic_cast<Minion*>(
                playable->game->currentEventData->eventTarget);
            if (!target)
            {
                return 0;
            }

            auto& taskStack = playable->game->taskStack;
            for (auto& minion : target->GetAdjacentMinions())
            {
                taskStack.playables.emplace_back(minion);
            }

            return playable->player->GetHero()->GetAttack();
        }),
        std::make_shared<DamageNumberTask>(EntityType::STACK)
    };
    cards.emplace("BT_271", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_351] Battlefiend - COST:1 [ATK:1/HP:2]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BT_351e", EntityType::SOURCE) };
    cards.emplace("BT_351", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_354] Blade Dance - COST:3
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 3));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("BT_354", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_355] Wrathscale Naga - COST:3 [ATK:3/HP:2]
    // - Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: After a friendly minion dies,
    //       deal 3 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 3)
    };
    cards.emplace("BT_355", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_407] Ur'zul Horror - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a 2/1 Lost Soul to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "BT_407t"));
    cards.emplace("BT_407", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_416] Raging Felscreamer - COST:4 [ATK:4/HP:4]
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Demon you play costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_416e", EntityType::SOURCE));
    cards.emplace("BT_416", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_427] Feast of Souls - COST:1
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw a card for each friendly minion that died this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const int num = player->GetNumFriendlyMinionsDiedThisTurn();

            for (int i = 0; i < num; ++i)
            {
                Generic::Draw(player, nullptr);
            }
        }));
    cards.emplace("BT_427", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_481] Nethrandamus - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: Demon Hunter Initiate, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two random 0-Cost minions.
    //       <i>(Upgrades each time a friendly minion dies!)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomMinionNumberTask>(GameTag::COST));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>(SummonSide::LEFT));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomMinionNumberTask>(GameTag::COST));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>(SummonSide::RIGHT));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1),
    };
    cards.emplace("BT_481", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_487] Hulking Overfiend - COST:8 [ATK:5/HP:10]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After this attacks and kills a minion,
    //       it may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDefenderDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::EXHAUSTED, 0) };
    cards.emplace("BT_487", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_488] Soul Split - COST:4
    // - Set: Demon Hunter Initiate, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Choose a friendly Demon. Summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 15 } };
    cards.emplace("BT_488", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_490] Consume Magic - COST:1
    // - Set: Demon Hunter Initiate, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Silence</b> an enemy minion.
    //       <b>Outcast:</b> Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.power.AddOutcastTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("BT_490", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_510] Wrathspike Brute - COST:5 [ATK:2/HP:6]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b> After this is attacked,
    //       deal 1 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACKED));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 1, false) };
    cards.emplace("BT_510", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_752] Blur - COST:0
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Your hero can't take damage this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_752e", EntityType::HERO));
    cards.emplace("BT_752", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_753] Mana Burn - COST:1
    // - Set: Demon Hunter Initiate, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Your opponent has 2 fewer Mana Crystals next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_753e", EntityType::PLAYER));
    cards.emplace("BT_753", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_801] Eye Beam - COST:3
    // - Set: Demon Hunter Initiate, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>. Deal 3 damage to a minion.
    //       <b>Outcast:</b> This costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - OUTCAST = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (playable->GetZonePosition() == 0 ||
                playable->GetZonePosition() ==
                    playable->player->GetHandZone()->GetCount() - 1)
            {
                return playable->GetGameTag(GameTag::COST) - 1;
            }

            return 0;
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_801", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_814] Illidari Felblade - COST:4 [ATK:5/HP:3]
    // - Race: Demon, Set: Demon Hunter Initiate, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Outcast:</b> Gain <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddOutcastTask(
        std::make_shared<AddEnchantmentTask>("BT_814e", EntityType::SOURCE));
    cards.emplace("BT_814", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BT_922] Umberwing - COST:2 [ATK:1/HP:0]
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Felwings.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BT_922t", 2));
    cards.emplace("BT_922", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_937] Altruis the Outcast - COST:4 [ATK:4/HP:2]
    // - Set: Demon Hunter Initiate, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play the left- or right-most card in your hand,
    //       deal 1 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsLeftOrRightMostCardInHand()) };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 1) };
    cards.emplace("BT_937", cardDef);
}

void DemonHunterInitCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_175e] Twin Slice (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_175e"));
    cards.emplace("BT_175e", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175t] Second Slice - COST:1
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    cards.emplace("BT_175t", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_351e] Felheartened - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("BT_351e", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_407t] Lost Soul (*) - COST:1 [ATK:2/HP:1]
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_407t", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_416e] Felscream (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Your next Demon costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::DEMON)) };
    }
    cards.emplace("BT_416e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_752e] Blur (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_752e"));
    cards.emplace("BT_752e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_753e] Mana Burned (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Start with 2 fewer Mana Crystals this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::RESOURCES_USED,
                                             EffectOperator::ADD, 2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->removeTrigger = { TriggerType::TURN_END,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsEnemyTurn()) };
    }
    cards.emplace("BT_753e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_814e] Nimble (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_814e"));
    cards.emplace("BT_814e", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_922t] Felwing (*) - COST:1 [ATK:1/HP:1]
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_922t", cardDef);
}

void DemonHunterInitCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
