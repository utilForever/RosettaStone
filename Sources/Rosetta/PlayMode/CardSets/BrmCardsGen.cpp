// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/BrmCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void BrmCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- HERO - NEUTRAL
    // [BRM_027h] Ragnaros the Firelord (*) - COST:0 [ATK:0/HP:8]
    // - Set: Brm
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 2319
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BRM_027h", cardDef);
}

void BrmCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [BRM_027p] DIE, INSECT! (*) - COST:2
    // - Set: Brm
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 8 damage to a random enemy.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        ComplexTask::DamageRandomTargets(EntityType::ENEMIES, 1, 8));
    cards.emplace("BRM_027p", cardDef);

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [BRM_027pH] DIE, INSECTS! (*) - COST:2
    // - Set: Brm
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 8 damage to a random enemy. TWICE.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ ComplexTask::DamageRandomTargets(EntityType::ENEMIES, 1, 8) },
        2));
    cards.emplace("BRM_027pH", cardDef);
}

void BrmCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [BRM_009] Volcanic Lumberer - COST:9 [ATK:7/HP:8]
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each minion that died this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumFriendlyMinionsDiedThisTurn();
        }));
    cards.emplace("BRM_009", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BRM_010] Druid of the Flame - COST:3 [ATK:2/HP:2]
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 5/2 minion;
    //       or a 2/5 minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "OG_044b"));
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "BRM_010a", "BRM_010b" };
    cards.emplace("BRM_010", cardDef);
}

void BrmCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [BRM_010a] Firecat Form (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Transform into a 5/2 minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "BRM_010t"));
    cards.emplace("BRM_010a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BRM_010b] Fire Hawk Form (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Transform into a 2/5 minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "BRM_010t2"));
    cards.emplace("BRM_010b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BRM_010t] Druid of the Flame (*) - COST:3 [ATK:5/HP:2]
    // - Race: Beast, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BRM_010t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BRM_010t2] Druid of the Flame (*) - COST:3 [ATK:2/HP:5]
    // - Race: Beast, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BRM_010t2", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [OG_044b] Druid of the Flame (*) - COST:3 [ATK:5/HP:5]
    // - Race: Beast, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("OG_044b", cardDef);
}

void BrmCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [BRM_013] Quick Shot - COST:2
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       If your hand is empty, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHandEmpty()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BRM_013", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BRM_014] Core Rager - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hand is empty, gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHandEmpty()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BRM_014e", EntityType::SOURCE) }));
    cards.emplace("BRM_014", cardDef);
}

void BrmCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BRM_014e] Power Rager (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: +3/+3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BRM_014e"));
    cards.emplace("BRM_014e", cardDef);
}

void BrmCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [BRM_002] Flamewaker - COST:3 [ATK:2/HP:4]
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       deal 2 damage randomly split among all enemies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        ComplexTask::DamageRandomTargets(EntityType::ENEMIES, 1, 1), 2) };
    cards.emplace("BRM_002", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [BRM_003] Dragon's Breath - COST:5
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage. Costs (1) less for each minion
    //       that died this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumFriendlyMinionsDiedThisTurn();
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BRM_003", cardDef);
}

void BrmCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BrmCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [BRM_001] Solemn Vigil - COST:5
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Costs (1) less for each minion that died this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumFriendlyMinionsDiedThisTurn();
        }));
    cards.emplace("BRM_001", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BRM_018] Dragon Consort - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set:Bbrm, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Dragon
    //       you play costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BRM_018e", EntityType::SOURCE));
    cards.emplace("BRM_018", cardDef);
}

void BrmCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BRM_018e] Unchained! (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Your next Dragon costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DRAGON));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::DRAGON)) };
    }
    cards.emplace("BRM_018e", cardDef);
}

void BrmCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [BRM_004] Twilight Whelp - COST:1 [ATK:2/HP:1]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BRM_004e", EntityType::SOURCE) }));
    cards.emplace("BRM_004", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BRM_017] Resurrect - COST:2
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a random friendly minion that died this game.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 0 },
                  { PlayReq::REQ_FRIENDLY_MINION_DIED_THIS_GAME, 0 } };
    cards.emplace("BRM_017", cardDef);
}

void BrmCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BrmCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [BRM_007] Gang Up - COST:2
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       Shuffle 3 copies of it into your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::DECK, 3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BRM_007", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BRM_008] Dark Iron Skulker - COST:5 [ATK:4/HP:3]
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage
    //       to all undamaged enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsUndamaged()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2));
    cards.emplace("BRM_008", cardDef);
}

void BrmCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BrmCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [BRM_011] Lava Shock - COST:2
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       Unlock your <b>Overloaded</b> Mana Crystals.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<SetPlayerGameTagTask>(GameTag::OVERLOAD_LOCKED, 0));
    cardDef.power.AddPowerTask(
        std::make_shared<SetPlayerGameTagTask>(GameTag::OVERLOAD_OWED, 0));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BRM_011", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BRM_012] Fireguard Destroyer - COST:4 [ATK:3/HP:6]
    // - Race: Elemental, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 1-4 Attack.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - BATTLECRY = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<MathRandTask>(1, 4));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BRM_012e", EntityType::SOURCE, true));
    cards.emplace("BRM_012", cardDef);
}

void BrmCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BrmCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [BRM_005] Demonwrath - COST:3
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions except Demons.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsNotRace(Race::DEMON)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cards.emplace("BRM_005", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [BRM_006] Imp Gang Boss - COST:3 [ATK:2/HP:4]
    // - Race: Demon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, summon a 1/1 Imp.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BRM_006t", SummonSide::RIGHT) };
    cards.emplace("BRM_006", cardDef);
}

void BrmCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [BRM_006t] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Brm
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BRM_006t", cardDef);
}

void BrmCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [BRM_015] Revenge - COST:2
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    //       If you have 12 or less Health,
    //       deal 3 damage instead.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHealth(12, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 3,
                                                     true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<DamageTask>(EntityType::ALL_MINIONS,
                                                      1, true) }));
    cards.emplace("BRM_015", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BRM_016] Axe Flinger - COST:4 [ATK:2/HP:5]
    // - Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMY_HERO, 2) };
    cards.emplace("BRM_016", cardDef);
}

void BrmCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BrmCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_019] Grim Patron - COST:5 [ATK:3/HP:3]
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion survives damage,
    //       summon another Grim Patron.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNotDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BRM_019", SummonSide::RIGHT) };
    cards.emplace("BRM_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_020] Dragonkin Sorcerer - COST:4 [ATK:3/HP:5]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever <b>you</b> target this minion with a spell,
    //       gain +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::SPELLS_CASTED_ON_THIS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BRM_020e", EntityType::SOURCE) };
    cards.emplace("BRM_020", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_022] Dragon Egg - COST:1 [ATK:0/HP:2]
    // - Set: Brm, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       summon a 2/1 Whelp.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BRM_022t", SummonSide::RIGHT) };
    cards.emplace("BRM_022", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_024] Drakonid Crusher - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 15 or
    //       less Health, gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHealth(15, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BRM_024e", EntityType::SOURCE) }));
    cards.emplace("BRM_024", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_025] Volcanic Drake - COST:6 [ATK:6/HP:4]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: Costs (1) less for each minion that died this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumFriendlyMinionsDiedThisTurn();
        }));
    cards.emplace("BRM_025", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_026] Hungry Dragon - COST:4 [ATK:5/HP:6]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 1-Cost minion
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 1, RelaSign::EQ } }, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<SummonOpTask>());
    cards.emplace("BRM_026", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_027] Majordomo Executus - COST:9 [ATK:9/HP:7]
    // - Set: Brm, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Replace your hero
    //       with Ragnaros, the Firelord.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ReplaceHeroTask>("BRM_027h", "BRM_027p"));
    cards.emplace("BRM_027", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_028] Emperor Thaurissan - COST:6 [ATK:5/HP:5]
    // - Set: Brm, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       reduce the Cost of cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BRM_028e", EntityType::HAND) };
    cards.emplace("BRM_028", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_029] Rend Blackhand - COST:7 [ATK:8/HP:4]
    // - Set: Brm, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy a <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // - REQ_LEGENDARY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND, 0 },
                  { PlayReq::REQ_LEGENDARY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BRM_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_030] Nefarian - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: Brm, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 2 random spells to your hand
    //       <i>(from your opponent's class)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(CardType::SPELL,
                                                   CardClass::OPPONENT_CLASS),
                  std::make_shared<AddStackToTask>(EntityType::HAND) },
        2));
    cards.emplace("BRM_030", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_031] Chromaggus - COST:8 [ATK:6/HP:8]
    // - Race: Dragon, Set: Brm, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you draw a card,
    //       put another copy into your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DRAW_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CopyTask>(
        EntityType::TARGET, ZoneType::HAND) };
    cards.emplace("BRM_031", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_033] Blackwing Technician - COST:3 [ATK:2/HP:4]
    // - Faction: Neutral, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BRM_033e", EntityType::SOURCE) }));
    cards.emplace("BRM_033", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_034] Blackwing Corruptor - COST:5 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND, 0 } };
    cards.emplace("BRM_034", cardDef);
}

void BrmCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_004e] Twilight Endurance (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::HealthN(2)));
    cards.emplace("BRM_004e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_004t] Whelp (*) - COST:1 [ATK:1/HP:1]
    // - Set: Brm
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_012e] On Fire! (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("BRM_012e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_020e] Draconic Power (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(1)));
    cards.emplace("BRM_020e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BRM_022t] Black Whelp (*) - COST:1 [ATK:2/HP:1]
    // - Race: Dragon, Set: Brm, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BRM_022t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_024e] Large Talons (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BRM_024e"));
    cards.emplace("BRM_024e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_028e] Imperial Favor (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BRM_028e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [BRM_030t] Tail Swipe (*) - COST:4
    // - Set: Brm
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BRM_033e] Dragon Blood (*) - COST:0
    // - Set: Brm
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BRM_033e"));
    cards.emplace("BRM_033e", cardDef);
}

void BrmCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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