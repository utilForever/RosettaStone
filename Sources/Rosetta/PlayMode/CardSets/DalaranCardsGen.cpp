// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/DalaranCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void DalaranCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void DalaranCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void DalaranCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [DAL_256] The Forest's Aid - COST:8
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Summon five 2/2 Treants.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 52821
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DAL_256t2", 5, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_256", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350] Crystal Power - COST:1
    // - Faction: Neutral, Set: Dalaran, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 2 damage to a minion;
    //       or Restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "DAL_350a", "DAL_350b" };
    cards.emplace("DAL_350", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_351] Blessing of the Ancients - COST:3
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54128
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_351e", EntityType::MINIONS));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_351", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_352] Crystalsong Portal - COST:2
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Druid minion.
    //       If your hand has no minions, keep all 3.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasMinionInHand()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(CardType::MINION,
                                                       CardClass::DRUID) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<DiscoverTask>(
                   CardType::MINION, CardClass::DRUID, Race::INVALID,
                   Rarity::INVALID, ChoiceAction::HAND, 1, true) }));
    cards.emplace("DAL_352", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_354] Acornbearer - COST:1 [ATK:2/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 1/1 Squirrels to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DAL_354t", 2));
    cards.emplace("DAL_354", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_355] Lifeweaver - COST:3 [ATK:2/HP:5]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you restore Health,
    //       add a random Druid spell to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::GIVE_HEAL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::DRUID),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("DAL_355", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_357] Lucentbark - COST:8 [ATK:4/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Go dormant.
    //       Restore 5 Health to awaken this minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("DAL_357t", SummonSide::DEATHRATTLE));
    cards.emplace("DAL_357", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_732] Keeper Stalladris - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a <b>Choose One</b> spell,
    //       add copies of both choices to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsChooseOneCard())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           const Playable* target) {
            const std::shared_ptr<IEffect> costEffect =
                Cost::Effect(EffectOperator::SET, target->card->GetCost());

            for (auto& chooseCardID : target->card->chooseCardIDs)
            {
                const auto chooseCard = Entity::GetFromCard(
                    player, Cards::FindCardByID(chooseCardID), std::nullopt,
                    player->GetSetasideZone());
                const auto copy =
                    Generic::Copy(player, chooseCard, ZoneType::HAND);
                costEffect->ApplyTo(copy);
            }
        }) };
    cards.emplace("DAL_732", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_733] Dreamway Guardians - COST:2
    // - Faction: Neutral, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/2 Dryads with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DAL_733t", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_733", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_799] Crystal Stag - COST:5 [ATK:4/HP:4]
    // - Race: Beast, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> If you've restored
    //       5 Health this game, summon a copy of this.
    //       @ <i>({0} left!)</i>@ <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // - PLAYER_TAG_THRESHOLD_TAG_ID = 958
    // - PLAYER_TAG_THRESHOLD_VALUE = 5
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::CheckThreshold(RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonCopyTask>(
                  EntityType::SOURCE, false, false, SummonSide::RIGHT) }));
    cards.emplace("DAL_799", cardDef);
}

void DalaranCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [DAL_256t2] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_256t2", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_256ts] The Forest's Aid (*) - COST:8
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon five 2/2 Treants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DAL_256t2", 5, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_256ts", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350a] Piercing Thorns (*) - COST:1
    // - Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_350a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350b] Healing Blossom (*) - COST:1
    // - Faction: Neutral, Set: Dalaran,
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_350b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DAL_351ts] Blessing of the Ancients (*) - COST:3
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_351e", EntityType::MINIONS));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_351ts", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_354t] Squirrel (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_354t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_357t] Spirit of Lucentbark (*) - COST:11 [ATK:0/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: When you restore 5 Health, awaken this minion.
    //       <i>(@ left!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 5
    // - HIDE_STATS = 1
    // - UNTOUCHABLE = 1
    // - SCORE_VALUE_1 = 5
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsEventSourceFriendly())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetEventNumberTask>(),
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_2, 0, 1),
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::ADD),
        std::make_shared<NumberConditionTask>(5, RelaSign::GEQ),
        std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<ChangeEntityTask>("DAL_357") }),
        std::make_shared<FlagTask>(
            false, TaskList{ std::make_shared<SetGameTagNumberTask>(
                       EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_2) })
    };
    cards.emplace("DAL_357t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DAL_733t] Crystal Dryad (*) - COST:1 [ATK:1/HP:2]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_733t", cardDef);
}

void DalaranCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_371] Marked Shot - COST:4
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_371", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_372] Arcane Fletcher - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a 1-Cost minion,
    //       draw a spell from your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsCost(1))
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::DECK),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DrawStackTask>()
    };
    cards.emplace("DAL_372", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_373] Rapid Fire - COST:2
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54143
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_373", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_376] Oblivitron - COST:6 [ATK:3/HP:4]
    // - Race: Mechanical, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a Mech from your hand
    //       and trigger its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MECHANICAL)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ActivateDeathrattleTask>(EntityType::STACK));
    cards.emplace("DAL_376", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_377] Nine Lives - COST:3
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly <b>Deathrattle</b> minion that
    //       died this game. Also trigger its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DEATHRATTLE_MINION_DIED));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<ActivateDeathrattleTask>(EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME,
                    0 } };
    cards.emplace("DAL_377", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_378] Unleash the Beast - COST:6
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Summon a 5/5 Wyvern with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54145
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DAL_378t1"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_378", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_379] Vereesa Windrunner - COST:7 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip Thori'dal, the Stars' Fury.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DAL_379t"));
    cards.emplace("DAL_379", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_587] Shimmerfly - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran, Rarity: rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Hunter spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::HUNTER));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("DAL_587", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_589] Hunting Party - COST:5
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Copy all Beasts in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("DAL_589", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_604] Ursatron - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a Mech from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DrawRaceMinionTask>(Race::MECHANICAL, 1, false));
    cards.emplace("DAL_604", cardDef);
}

void DalaranCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_373ts] Rapid Fire (*) - COST:2
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_373ts", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DAL_378t1] Wyvern (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_378t1", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_378ts] Unleash the Beast (*) - COST:6
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 5/5 Wyvern with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_ATTACK = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DAL_378t1"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_378ts", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DAL_379e] Stars' Fury (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(GameTag::SPELLPOWER, EffectOperator::ADD, 2));
    cardDef.power.GetEnchant()->isOneTurnEffect = true;
    cards.emplace("DAL_379e", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [DAL_379t] Thori'dal, the Stars' Fury (*) - COST:3 [ATK:2/HP:0]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       gain <b>Spell Damage +2</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DAL_379e", EntityType::HERO) };
    cards.emplace("DAL_379t", cardDef);
}

void DalaranCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [DAL_163] Messenger Raven - COST:3 [ATK:3/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Mage minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(CardType::MINION, CardClass::MAGE));
    cards.emplace("DAL_163", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DAL_177] Conjurer's Calling - COST:3
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Destroy a minion.
    //       Summon 2 minions of the same Cost to replace it.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 52637
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::COST));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<ConditionTask>(
                      EntityType::TARGET,
                      SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsFriendly()) }),
                  std::make_shared<FlagTask>(
                      true, TaskList{ std::make_shared<RandomMinionNumberTask>(
                                          GameTag::COST),
                                      std::make_shared<SummonTask>() }),
                  std::make_shared<FlagTask>(
                      false, TaskList{ std::make_shared<RandomMinionNumberTask>(
                                           GameTag::COST, true),
                                       std::make_shared<SummonOpTask>() }) },
        2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_177", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DAL_182] Magic Dart Frog - COST:2 [ATK:1/HP:3]
    // - Race: Beast, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to a random enemy minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1)
    };
    cards.emplace("DAL_182", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DAL_575] Khadgar - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your cards that summon minions summon twice as many.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::FRIENDLY_EVENT_SOURCE;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>([=](const Playable* playable) -> bool {
            return playable->game->currentEventData->eventSource != playable &&
                   playable->GetGameTag(GameTag::COPIED_BY_KHADGAR) != 1;
        })
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CustomTask>(
        [](const Player* player, Entity* source, const Playable* target) {
            if (target->player->GetFieldZone()->IsFull())
            {
                return;
            }

            std::map<GameTag, int> gameTags;
            gameTags.emplace(GameTag::COPIED_BY_KHADGAR, 1);

            const auto entity = Entity::GetFromCard(
                target->player, target->card, gameTags, player->GetFieldZone());
            Generic::Summon(dynamic_cast<Minion*>(entity),
                            target->GetZonePosition() + 1, source);
        }) };
    cards.emplace("DAL_575", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DAL_576] Kirin Tor Tricaster - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +3</b> Your spells cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 3
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::HAND, "DAL_576e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cards.emplace("DAL_576", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DAL_577] Ray of Frost - COST:1
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> <b>Freeze</b> a minion.
    //       If it's already <b>Frozen</b>, deal 2 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54193
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_577", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DAL_578] Power of Creation - COST:8
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 6-Cost minion. Summon two copies of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SIX_COST_MINION_SUMMON));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_578", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DAL_603] Mana Cyclone - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each spell you've cast this turn,
    //       add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            int count = 0;

            for (const auto& card : playable->player->cardsPlayedThisTurn)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    ++count;
                }
            }

            return count;
        }));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE),
        std::make_shared<AddStackToTask>(EntityType::HAND) }));
    cards.emplace("DAL_603", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DAL_608] Magic Trick - COST:1
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell that costs (3) or less.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL_THREE_COST_OR_LESS));
    cards.emplace("DAL_608", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DAL_609] Kalecgos - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your first spell each turn costs (0).
    //       <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - AURA = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SwitchingAura>(
        AuraType::HAND, SelfCondition::SpellsCastThisTurn(0),
        TriggerType::CAST_SPELL, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("DAL_609", cardDef);
}

void DalaranCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [DAL_177ts] Conjurer's Calling (*) - COST:3
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Destroy a minion.
    //       Summon 2 minions of the same Cost to replace it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::COST));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<ConditionTask>(
                      EntityType::TARGET,
                      SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsFriendly()) }),
                  std::make_shared<FlagTask>(
                      true, TaskList{ std::make_shared<RandomMinionNumberTask>(
                                          GameTag::COST),
                                      std::make_shared<SummonTask>() }),
                  std::make_shared<FlagTask>(
                      false, TaskList{ std::make_shared<RandomMinionNumberTask>(
                                           GameTag::COST, true),
                                       std::make_shared<SummonOpTask>() }) },
        2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_177ts", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DAL_577ts] Ray of Frost (*) - COST:1
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion.
    //       If it's already <b>Frozen</b>, deal 2 damage to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_577ts", cardDef);
}

void DalaranCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_141] Desperate Measures - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Cast a random Paladin <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54129
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const auto activeSecrets = player->GetSecretZone()->GetAll();

            auto allCards =
                player->game->GetFormatType() == FormatType::STANDARD
                    ? Cards::GetAllStandardCards()
                    : Cards::GetAllWildCards();

            std::vector<Card*> secrets;
            for (auto& card : allCards)
            {
                if (card->GetCardClass() == CardClass::PALADIN &&
                    card->IsSecret())
                {
                    bool isExist = false;
                    for (auto& secret : activeSecrets)
                    {
                        if (card->id == secret->card->id)
                        {
                            isExist = true;
                            break;
                        }
                    }

                    if (!isExist)
                    {
                        secrets.emplace_back(card);
                    }
                }
            }

            const auto idx = Random::get<std::size_t>(0, secrets.size() - 1);
            Playable* playable = Entity::GetFromCard(player, secrets.at(idx));
            Generic::CastSpell(player, dynamic_cast<Spell*>(playable), nullptr,
                               0);
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_SECRET_ZONE_CAP_FOR_NON_SECRET, 0 } };
    cards.emplace("DAL_141", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DAL_146] Bronze Herald - COST:3 [ATK:3/HP:2]
    // - Race: Dragon, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 4/4 Dragons to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DAL_146t", 2));
    cards.emplace("DAL_146", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DAL_147] Dragon Speaker - COST:5 [ATK:3/HP:5]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all Dragons in your hand +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_147e", EntityType::STACK));
    cards.emplace("DAL_147", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_568] Lightforged Blessing - COST:2
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give a friendly minion <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54189
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_568e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_568", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_570] Never Surrender! - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       give your minions +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<AddEnchantmentTask>("DAL_570e",
                                                       EntityType::MINIONS) });
    cards.emplace("DAL_570", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [DAL_571] Mysterious Blade - COST:2 [ATK:2/HP:0]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a
    //       <b>Secret</b>, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
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
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DAL_571e", EntityType::SOURCE) }));
    cards.emplace("DAL_571", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DAL_573] Commander Rhyssa - COST:3 [ATK:4/HP:3]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your <b>Secrets</b> trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::EXTRA_TRIGGER_SECRET,
                                             EffectOperator::SET, 1) }));
    cards.emplace("DAL_573", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DAL_581] Nozari - COST:10 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore both heroes to full Health.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealFullTask>(EntityType::HEROES));
    cards.emplace("DAL_581", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_727] Call to Adventure - COST:3
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw the lowest Cost minion from your deck. Give it +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawMinionTask>(DrawMinionType::LOWEST_COST, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_727e", EntityType::STACK));
    cards.emplace("DAL_727", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_731] Duel! - COST:5
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a minion from each player's deck. They fight!
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ENTITY_ID));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ENTITY_ID, 0, 1));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::STACK_NUM0, EntityType::STACK_NUM1));
    cards.emplace("DAL_731", cardDef);
}

void DalaranCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_141ts] Desperate Measures (*) - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Cast a random Paladin <b>Secret</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const auto activeSecrets = player->GetSecretZone()->GetAll();

            auto allCards =
                player->game->GetFormatType() == FormatType::STANDARD
                    ? Cards::GetAllStandardCards()
                    : Cards::GetAllWildCards();

            std::vector<Card*> secrets;
            for (auto& card : allCards)
            {
                if (card->GetCardClass() == CardClass::PALADIN &&
                    card->IsSecret())
                {
                    bool isExist = false;

                    for (const auto& secret : activeSecrets)
                    {
                        if (card->id == secret->card->id)
                        {
                            isExist = true;
                            break;
                        }
                    }

                    if (!isExist)
                    {
                        secrets.emplace_back(card);
                    }
                }
            }

            const auto idx = Random::get<std::size_t>(0, secrets.size() - 1);
            Playable* playable = Entity::GetFromCard(player, secrets.at(idx));
            Generic::CastSpell(player, dynamic_cast<Spell*>(playable), nullptr,
                               0);
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_SECRET_ZONE_CAP_FOR_NON_SECRET, 0 } };
    cards.emplace("DAL_141ts", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DAL_146t] Bronze Dragon (*) - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_146t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DAL_568e] Lightforged Blessing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_568e"));
    cards.emplace("DAL_568e", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_568ts] Lightforged Blessing (*) - COST:2
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a friendly minion <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_568e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_568ts", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DAL_571e] Mysterious (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_571e"));
    cards.emplace("DAL_571e", cardDef);
}

void DalaranCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_011] Lazul's Scheme - COST:0
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Reduce the Attack of an enemy minion by
    //       @ until your next turn. <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DAL_011e", EntityType::TARGET, true));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1)
    };
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("DAL_011", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_030] Shadowy Figure - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 2/2 copy of
    //       a friendly <b>Deathrattle</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformCopyTask>(false, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_030e", EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_DEATHRATTLE, 0 } };
    cards.emplace("DAL_030", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_039] Convincing Infiltrator - COST:5 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cards.emplace("DAL_039", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_040] Hench-Clan Shadequill - COST:4 [ATK:4/HP:7]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 5 Health to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::ENEMY_HERO, 5));
    cards.emplace("DAL_040", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_065] Unsleeping Soul - COST:4
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Silence</b> a friendly minion, then summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_065", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_413] EVIL Conscripter - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DAL_413", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_721] Catrina Muerte - COST:8 [ATK:6/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a friendly minion
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY)
    };
    cards.emplace("DAL_721", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_723] Forbidden Words - COST:0
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Spend all your Mana. Destroy a minion with that
    //       much Attack or less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetPlayerManaTask>());
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::ATK, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<NumberConditionTask>(RelaSign::GEQ));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) }));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            playables[0]->player->SetUsedMana(
                playables[0]->player->GetTotalMana() +
                playables[0]->player->GetTemporaryMana() -
                playables[0]->player->GetOverloadLocked());

            return std::vector<Playable*>{};
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_723", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_724] Mass Resurrection - COST:9
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Summon 3 friendly minions that died this game.
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
        std::make_shared<RandomTask>(EntityType::STACK, 3));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 },
                  { PlayReq::REQ_FRIENDLY_MINION_DIED_THIS_GAME, 0 } };
    cards.emplace("DAL_724", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DAL_729] Madame Lazul - COST:3 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a
    //       copy of a card in your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::MADAME_LAZUL));
    cards.emplace("DAL_729", cardDef);
}

void DalaranCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [DAL_030e] Shade (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_030e"));
    cards.emplace("DAL_030e", cardDef);
}

void DalaranCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_010] Togwaggle's Scheme - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a minion. Shuffle @ (copy, copies) of it into your deck.
    //       <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::DECK) }));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1)
    };
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_010", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366] Unidentified Contract - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Gains a bonus effect in your hand.
    // --------------------------------------------------------
    // Entourage: DAL_366t1, DAL_366t2, DAL_366t3, DAL_366t4
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ZONE));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ChangeUnidentifiedTask>()
    };
    cardDef.property.entourages =
        Entourages{ "DAL_366t1", "DAL_366t2", "DAL_366t3", "DAL_366t4" };
    cards.emplace("DAL_366", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DAL_415] EVIL Miscreant - COST:3 [ATK:1/HP:5]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Add two random <b>Lackeys</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(std::make_shared<AddLackeyTask>(2));
    cards.emplace("DAL_415", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DAL_416] Hench-Clan Burglar - COST:4 [ATK:4/HP:4]
    // - Race: Pirate, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell
    //       from another class.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(
        CardType::SPELL, CardClass::ANOTHER_CLASS));
    cards.emplace("DAL_416", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DAL_417] Heistbaron Togwaggle - COST:6 [ATK:5/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Lackey</b>,
    //       choose a fantastic treasure.
    // --------------------------------------------------------
    // Entourage: LOOT_998h, LOOT_998j, LOOT_998l, LOOT_998k
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - MULTIPLY_BUFF_VALUE = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsControllingLackey()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(
                  DiscoverType::HEISTBARON_TOGWAGGLE, 4) }));
    cards.emplace("DAL_417", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DAL_714] Underbelly Fence - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a card from
    //       another class, gain +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHoldingAnotherClassCard()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                            "DAL_714e", EntityType::SOURCE),
                        std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                                         GameTag::RUSH, 1) }));
    cards.emplace("DAL_714", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_716] Vendetta - COST:4
    // - Faction: Neutral, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. Costs (0) if you're
    //       holding a card from another class.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddAura(std::make_shared<AdaptiveCostEffect>(
        [](Playable* playable) { return 0; }, EffectOperator::SET,
        SelfCondition::IsHoldingAnotherClassCard()));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_716", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DAL_719] Tak Nozwhisker - COST:7 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you shuffle a card into your deck,
    //       add a copy to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::SHUFFLE_INTO_DECK));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CopyTask>(
        EntityType::TARGET, ZoneType::HAND) };
    cards.emplace("DAL_719", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [DAL_720] Waggle Pick - COST:4 [ATK:4/HP:0]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random friendly
    //       minion to your hand. It costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::MINIONS, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ReturnHandTask>(EntityType::STACK));
    cardDef.power.AddDeathrattleTask(std::make_shared<ApplyEffectTask>(
        EntityType::STACK, EffectList{ Effects::ReduceCost(2) }));
    cards.emplace("DAL_720", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_728] Daring Escape - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Return all friendly minions to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::MINIONS));
    cards.emplace("DAL_728", cardDef);
}

void DalaranCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t1] Assassin's Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Summon a 1/2 Patient Assassin.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("EX1_522"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_366t1", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t2] Recruitment Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::HAND));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_366t2", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t3] Lucrative Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Add 2 Coins to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005", 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_366t3", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t4] Turncoat Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. It deals its damage to adjacent minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_366t4", cardDef);
}

void DalaranCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_009] Hagatha's Scheme - COST:5
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal @ damage to all minions.
    //       <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::ALL_MINIONS, true));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1)
    };
    cards.emplace("DAL_009", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_047] Walking Fountain - COST:8 [ATK:4/HP:8]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>, <b>Rush</b>, <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_047", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_049] Underbelly Angler - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a Murloc, add a random Murloc to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::INVALID,
                                         Race::MURLOC),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("DAL_049", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_052] Muckmorpher - COST:5 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 4/4 copy of
    //       a different minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::SOURCE, EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_052e", EntityType::SOURCE));
    cards.emplace("DAL_052", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_071] Mutate - COST:0
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform a friendly minion into a random one
    //       that costs (1) more.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformMinionTask>(EntityType::TARGET, 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_071", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_431] Swampqueen Hagatha - COST:7 [ATK:5/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 5/5 Horror to your hand.
    //       Teach it two Shaman spells.
    // --------------------------------------------------------
    // Entourage: DAL_431t
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SWAMPQUEEN_HAGATHA, 3, 2));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<CustomTask>([](Player* player, const Entity* source,
                                        [[maybe_unused]] Playable* target) {
            if (source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2) > 0)
            {
                std::map<GameTag, int> tags;
                tags.emplace(
                    GameTag::TAG_SCRIPT_DATA_ENT_1,
                    source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
                tags.emplace(
                    GameTag::TAG_SCRIPT_DATA_ENT_2,
                    source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

                Playable* horror =
                    Entity::GetFromCard(player, Cards::FindCardByID("DAL_431t"),
                                        tags, player->GetHandZone());
                Generic::AddCardToHand(player, horror);
            }
        }));
    cards.emplace("DAL_431", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_432] Witch's Brew - COST:2
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Restore 4 Health. Repeatable this turn.
    // --------------------------------------------------------
    // GameTag:
    // - NON_KEYWORD_ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 4));
    cardDef.power.AddPowerTask(ComplexTask::RepeatableThisTurn());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_432", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_433] Sludge Slurper - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DAL_433", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_710] Soul of the Murloc - COST:2
    // - Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b> Summon a 1/1 Murloc."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_710e", EntityType::MINIONS));
    cards.emplace("DAL_710", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_726] Scargil - COST:4 [ATK:4/HP:4]
    // - Race: Murloc, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Murlocs cost (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::HAND, "DAL_726e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("DAL_726", cardDef);
}

void DalaranCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_431t] Drustvar Horror (*) - COST:5 [ATK:5/HP:5]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast {0} and {1}.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, const Entity* source, Playable* target) {
            const int dbfID1 =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1);
            Playable* playable1 =
                Entity::GetFromCard(player, Cards::FindCardByDbfID(dbfID1));
            Generic::CastSpell(player, dynamic_cast<Spell*>(playable1),
                               dynamic_cast<Character*>(target), 0);

            const int dbfID2 =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2);
            Playable* playable2 =
                Entity::GetFromCard(player, Cards::FindCardByDbfID(dbfID2));
            Generic::CastSpell(player, dynamic_cast<Spell*>(playable2),
                               dynamic_cast<Character*>(target), 0);
        }));
    cards.emplace("DAL_431t", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DAL_710e] Soul of the Murloc (*) - COST:0
    // - Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Murloc.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_506a", SummonSide::DEATHRATTLE));
    cards.emplace("DAL_710e", cardDef);
}

void DalaranCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_007] Rafaam's Scheme - COST:3
    // - Set: Dalaran, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Summon @ 1/1 (Imp, Imps). <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonNumberTask>("DAL_751t", false));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1)
    };
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_007", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_173] Darkest Hour - COST:6
    // - Set: Dalaran, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy all friendly minions.
    //       For each one, summon a random minion from your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK, true));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<IncludeTask>(EntityType::DECK),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<SummonStackTask>(true) }));
    cards.emplace("DAL_173", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_185] Aranasi Broodmother - COST:6 [ATK:4/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> When you draw this,
    //       restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TOPDECK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<HealTask>(EntityType::HERO, 4));
    cards.emplace("DAL_185", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_422] Arch-Villain Rafaam - COST:7 [ATK:7/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Replace your hand
    //       and deck with <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::DECK, std::vector<EntityType>(), true));
    cardDef.power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::STACK, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY));
    cards.emplace("DAL_422", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_561] Jumbo Imp - COST:10 [ATK:8/HP:8]
    // - Race: Demon, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less whenever a friendly Demon dies
    //       while this is in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DAL_561e", EntityType::SOURCE) };
    cards.emplace("DAL_561", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_563] Eager Underling - COST:4 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give two random friendly minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::MINIONS, 2));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("DAL_563e", EntityType::STACK));
    cards.emplace("DAL_563", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_602] Plot Twist - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Shuffle your hand into your deck. Draw that many cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<MoveToDeckTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("DAL_602", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_605] Impferno - COST:3
    // - Set: Dalaran, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Give your Demons +1 Attack.
    //       Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_605e", EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cards.emplace("DAL_605", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_606] EVIL Genius - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion
    //       to add 2 random <b>Lackeys</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasTarget()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET),
                        std::make_shared<AddLackeyTask>(2) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_606", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DAL_607] Fel Lord Betrug - COST:8 [ATK:5/HP:7]
    // - Race: Demon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you draw a minion, summon a copy
    //       with <b>Rush</b> that dies at end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DRAW_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY, 1, true),
        std::make_shared<AddEnchantmentTask>("DAL_607e", EntityType::STACK)
    };
    cards.emplace("DAL_607", cardDef);
}

void DalaranCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [DAL_605e] Imptastic (*) - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_605e"));
    cards.emplace("DAL_605e", cardDef);
}

void DalaranCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_008] Dr. Boom's Scheme - COST:4
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain @ Armor. <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(0, false, true));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1)
    };
    cards.emplace("DAL_008", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_059] Dimensional Ripper - COST:10
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 2 copies of a minion in your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DAL_059", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DAL_060] Clockwork Goblin - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a Bomb into your opponent's deck.
    //       When drawn, it explodes for 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_DECK, "BOT_511t"));
    cards.emplace("DAL_060", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_062] Sweeping Strikes - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion "Also damages minions next to whomever this attacks."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_062e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_062", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [DAL_063] Wrenchcalibur - COST:4 [ATK:3/HP:0]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero attacks, shuffle a Bomb
    //       into your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddCardTask>(
        EntityType::ENEMY_DECK, "BOT_511t") };
    cards.emplace("DAL_063", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DAL_064] Blastmaster Boom - COST:7 [ATK:7/HP:7]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Boom Bots
    //       for each Bomb in your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsCardID("BOT_511t")) }));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<NumberConditionTask>(4, RelaSign::GEQ));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<FuncNumberTask>(
                  []([[maybe_unused]] Playable* playable) { return 3; }) }));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(
        TaskList{ std::make_shared<SummonTask>(
            "GVG_110t", 2, SummonSide::ALTERNATE_FRIENDLY) }));
    cards.emplace("DAL_064", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DAL_070] The Boom Reaver - COST:10 [ATK:7/HP:9]
    // - Race: Mechanical, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of a minion in your deck.
    //       Give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_070e", EntityType::STACK));
    cards.emplace("DAL_070", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DAL_759] Vicious Scraphound - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion deals damage, gain that much Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::DEAL_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetEventNumberTask>(),
        std::make_shared<ArmorTask>(0, false, true)
    };
    cards.emplace("DAL_759", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_769] Improve Morale - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion.
    //       If it survives, add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNotDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddLackeyTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_769", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DAL_770] Omega Devastator - COST:4 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       deal 10 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsManaCrystalFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 10) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DAL_770", cardDef);
}

void DalaranCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_062e] Sweeping Strikes (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Damages minions adjacent to defender.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::ENCHANTMENT_TARGET;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsEventTargetIs(CardType::MINION)) };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeAdjacentTask>(EntityType::EVENT_TARGET),
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK),
        std::make_shared<DamageNumberTask>(EntityType::STACK)
    };
    cards.emplace("DAL_062e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_070e] Reaving (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Has <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_070e"));
    cards.emplace("DAL_070e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_742e] Whirling (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Mega-Windfury</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(GameTag::MEGA_WINDFURY,
                                                       EffectOperator::SET, 1));
    cards.emplace("DAL_742e", cardDef);
}

void DalaranCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_058] Hecklebot - COST:4 [ATK:3/HP:8]
    // - Race: Mechanical, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Your opponent
    //       summons a minion from their deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("DAL_058", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_077] Toxfin - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Murloc <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 14
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_077e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 14 } };
    cards.emplace("DAL_077", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_078] Traveling Healer - COST:4 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("DAL_078", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_081] Spellward Jeweler - COST:3 [ATK:3/HP:4]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your hero can't be targeted by
    //       spells or Hero Powers until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_081e", EntityType::HERO));
    cards.emplace("DAL_081", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_085] Dalaran Crusader - COST:5 [ATK:5/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_085", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_086] Sunreaver Spy - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1.
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
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DAL_086e", EntityType::SOURCE) }));
    cards.emplace("DAL_086", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_087] Hench-Clan Hag - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Amalgams
    //       with all minion types.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>(
        "DAL_087t", 2, SummonSide::ALTERNATE_FRIENDLY));
    cards.emplace("DAL_087", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_088] Safeguard - COST:6 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a 0/5
    //       Vault Safe with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("DAL_088t2", SummonSide::DEATHRATTLE));
    cards.emplace("DAL_088", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_089] Spellbook Binder - COST:2 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have <b>Spell Damage</b>,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasPlayerSpellPower()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cards.emplace("DAL_089", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_090] Hench-Clan Sneak - COST:3 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_090", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_092] Arcane Servant - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_092", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_095] Violet Spellsword - COST:4 [ATK:1/HP:6]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack
    //       for each spell in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DAL_095e", EntityType::SOURCE, true));
    cards.emplace("DAL_095", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_096] Violet Warden - COST:6 [ATK:4/HP:7]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_096", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_400] EVIL Cable Rat - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DAL_400", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_434] Arcane Watcher - COST:3 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack unless you have <b>Spell Damage</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(
            SelfCondition::HasNotSpellDamageOnHero()),
        GameTag::CANT_ATTACK));
    cards.emplace("DAL_434", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_538] Unseen Saboteur - COST:6 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent casts a random spell
    //       from their hand <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<PlayTask>(PlayType::SPELL, true));
    cards.emplace("DAL_538", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_539] Sunreaver Warmage - COST:5 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_DRAG_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::Has5MoreCostSpellInHand()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_DRAG_TO_PLAY, 0 } };
    cards.emplace("DAL_539", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_544] Potion Vendor - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 2));
    cards.emplace("DAL_544", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_546] Barista Lynchen - COST:5 [ATK:4/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a copy of each of your other
    //       <b>Battlecry</b> minions to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsBattlecryCard()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("DAL_546", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_548] Azerite Elemental - COST:5 [ATK:2/HP:7]
    // - Race: Elemental, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, gain <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DAL_548e", EntityType::SOURCE) };
    cards.emplace("DAL_548", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_550] Underbelly Ooze - COST:7 [ATK:3/HP:5]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion survives damage, summon a copy of it.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNotDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CopyTask>(
        EntityType::SOURCE, ZoneType::PLAY) };
    cards.emplace("DAL_550", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_551] Proud Defender - COST:4 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +2 Attack while you have no other minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            return playable->player->GetFieldZone()->GetCount() == 1 ? 2 : 0;
        }));
    cards.emplace("DAL_551", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_553] Big Bad Archmage - COST:10 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a random
    //       6-Cost minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::COST, 6, RelaSign::EQ } }),
        std::make_shared<SummonTask>()
    };
    cards.emplace("DAL_553", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_554] Chef Nomi - COST:7 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck is empty,
    //       summon six 6/6 Greasefire Elementals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDeckEmpty()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonTask>(
                  "DAL_554t", 6, SummonSide::ALTERNATE_FRIENDLY) }));
    cards.emplace("DAL_554", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_558] Archmage Vargoth - COST:4 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, cast a spell
    //       you've cast this turn <i>(targets are random)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            std::vector<Card*> spellsPlayedThisTurn;

            for (auto& card : player->cardsPlayedThisTurn)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    spellsPlayedThisTurn.emplace_back(card);
                }
            }

            if (spellsPlayedThisTurn.empty())
            {
                return;
            }

            auto idx =
                Random::get<std::size_t>(0, spellsPlayedThisTurn.size() - 1);
            Card* randSpellCard = spellsPlayedThisTurn[idx];

            if (!randSpellCard->IsPlayableByCardReq(player) ||
                (randSpellCard->IsSecret() &&
                 player->GetSecretZone()->IsFull()) ||
                (randSpellCard->IsQuest() && player->GetSecretZone()->quest))
            {
                return;
            }

            Character* randTarget;
            const std::vector<Character*> validTargets =
                randSpellCard->GetValidPlayTargets(player);

            if (validTargets.empty())
            {
                randTarget = nullptr;
            }
            else
            {
                idx = Random::get<std::size_t>(0, validTargets.size() - 1);
                randTarget = validTargets[idx];
            }

            if (randSpellCard->mustHaveToTargetToPlay && !randTarget)
            {
                return;
            }

            Spell* spellToCast = dynamic_cast<Spell*>(
                Entity::GetFromCard(player, randSpellCard));
            const int randChooseOne = Random::get<int>(1, 2);

            Generic::CastSpell(player, spellToCast, randTarget, randChooseOne);

            while (player->choice)
            {
                idx = Random::get<std::size_t>(
                    0, player->choice->choices.size() - 1);
                Generic::ChoicePick(player, static_cast<int>(idx));
            }
        }) };
    cards.emplace("DAL_558", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_560] Heroic Innkeeper - COST:8 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt.</b> <b>Battlecry:</b> Gain +2/+2
    //       for each other friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            return 2 * (playable->player->GetFieldZone()->GetCount() - 1);
        }));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DAL_560e2", EntityType::SOURCE, true));
    cards.emplace("DAL_560", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_565] Portal Overfiend - COST:6 [ATK:5/HP:6]
    // - Race: Demon, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
    //       When drawn, summon a 2/2 Demon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "DAL_582t", 3));
    cards.emplace("DAL_565", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_566] Eccentric Scribe - COST:6 [ATK:6/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon four 1/1 Vengeful Scrolls.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("DAL_566t", 4, SummonSide::DEATHRATTLE));
    cards.emplace("DAL_566", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_582] Portal Keeper - COST:4 [ATK:5/HP:2]
    // - Race: Demon, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
    //       When drawn, summon a 2/2 Demon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "DAL_582t", 3));
    cards.emplace("DAL_582", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_592] Batterhead - COST:8 [ATK:3/HP:12]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After this attacks and kills a minion,
    //       it may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDefenderDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
                                              EntityType::SOURCE,
                                              GameTag::EXHAUSTED, 0),
                                          std::make_shared<SummonTask>() };
    cards.emplace("DAL_592", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_735] Dalaran Librarian - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> adjacent minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::STACK));
    cards.emplace("DAL_735", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_736] Archivist Elysiana - COST:8 [ATK:7/HP:7]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> 5 cards.
    //       Replace your deck with 2 copies of each.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(
        CardType::INVALID, CardClass::INVALID, Race::INVALID, Rarity::INVALID,
        ChoiceAction::STACK, 5));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<MoveToSetasideTask>(EntityType::DECK));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::DECK, 2));
    cards.emplace("DAL_736", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_742] Whirlwind Tempest - COST:8 [ATK:6/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your minions with <b>Windfury</b> have <b>Mega-Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - MEGA_WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::PLAYER, "DAL_742e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::HasWindfury());
    }
    cards.emplace("DAL_742", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_743] Hench-Clan Hogsteed - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Deathrattle:</b> Summon a 1/1 Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("DAL_743t", SummonSide::DEATHRATTLE));
    cards.emplace("DAL_743", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_744] Faceless Rager - COST:3 [ATK:5/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a friendly minion's Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::HEALTH));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DAL_744e", EntityType::SOURCE, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_744", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_747] Flight Master - COST:3 [ATK:3/HP:4]
    // - Faction: Alliance, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Gryphon for each player.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DAL_747t"));
    cardDef.power.AddPowerTask(std::make_shared<SummonOpTask>("DAL_747t"));
    cards.emplace("DAL_747", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_748] Mana Reservoir - COST:2 [ATK:0/HP:6]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_748", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_749] Recurring Villain - COST:5 [ATK:3/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If this minion has 4 or more Attack,
    //       resummon it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 4, RelaSign::GEQ)) }));
    cardDef.power.AddDeathrattleTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonTask>(
                  "DAL_749", 1, SummonSide::DEATHRATTLE) }));
    cards.emplace("DAL_749", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_751] Mad Summoner - COST:6 [ATK:4/HP:4]
    // - Race: Demon, Faction: Alliance, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fill each player's board with 1/1 Imps.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(ZoneType::PLAY, true, false));
    cardDef.power.AddPowerTask(std::make_shared<SummonNumberTask>(
        "DAL_751t", false, SummonSide::ALTERNATE_FRIENDLY));
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(ZoneType::PLAY, true, true));
    cardDef.power.AddPowerTask(std::make_shared<SummonNumberTask>(
        "DAL_751t", true, SummonSide::ALTERNATE_ENEMY));
    cards.emplace("DAL_751", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_752] Jepetto Joybuzz - COST:8 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 minions from your deck.
    //       Set their Attack, Health, and Cost to 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_752e", EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_752e2", EntityType::STACK));
    cards.emplace("DAL_752", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_760] Burly Shovelfist - COST:9 [ATK:9/HP:9]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_760", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_771] Soldier of Fortune - COST:4 [ATK:5/HP:6]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion attacks, give your opponent a Coin.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddCardTask>(
        EntityType::ENEMY_HAND, "GAME_005") };
    cards.emplace("DAL_771", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_773] Magic Carpet - COST:3 [ATK:1/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a 1-Cost minion,
    //       give it +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(SelfCondition::IsTagValue(
            GameTag::TAG_LAST_KNOWN_COST_IN_HAND, 1)) };
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DAL_773e", EntityType::TARGET) };
    cards.emplace("DAL_773", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_774] Exotic Mountseller - COST:7 [ATK:5/HP:8]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, summon a random 3-Cost Beast.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::COST, 3, RelaSign::EQ },
                       { GameTag::CARDRACE, static_cast<int>(Race::BEAST),
                         RelaSign::EQ } }),
        std::make_shared<SummonTask>()
    };
    cards.emplace("DAL_774", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_775] Tunnel Blaster - COST:7 [ATK:3/HP:7]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Deal 3 damage
    //       to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 3));
    cards.emplace("DAL_775", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_800] Zayle, Shadow Cloak - COST:2 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: You start the game with one of Zayle's EVIL Decks!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_800", cardDef);
}

void DalaranCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_011e] Lazul's Curse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Reduced Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Atk::Effect(EffectOperator::SUB, 0)));
    cardDef.power.GetEnchant()->useScriptTag = true;
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("DAL_011e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_052e] Muckmorphing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_052e"));
    cards.emplace("DAL_052e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_077e] Toxic Fin (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_077e"));
    cards.emplace("DAL_077e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_081e] Sparkly (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero cards.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(
        Effects::CantBeTargetedBySpellsAndHeroPowers()));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("DAL_081e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_086e] Stolen Secrets (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_086e"));
    cards.emplace("DAL_086e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_087t] Amalgam (*) - COST:1 [ATK:1/HP:1]
    // - Race: All, Set: Dalaran
    // --------------------------------------------------------
    // Text: <i>This is an Elemental, Mech, Demon, Murloc, Dragon,
    //       Beast, Pirate and Totem.</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_087t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_088t2] Vault Safe (*) - COST:2 [ATK:0/HP:5]
    // - Race: Mechanical, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_088t2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_095e] Pizzazz (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("DAL_095e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_147e] Dragon Shout (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_147e"));
    cards.emplace("DAL_147e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_351e] Ancient Blessings (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_351e"));
    cards.emplace("DAL_351e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_548e] Arcane Expansion (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased <b>Spell Damage</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(EffectList{ std::make_shared<Effect>(
            GameTag::SPELLPOWER, EffectOperator::ADD, 2) }));
    cards.emplace("DAL_548e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_554t] Greasefire Elemental (*) - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_554t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_566t] Vengeful Scroll (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_566t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_560e2] Protect the Brews! (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("DAL_560e2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_561e] Imp-onomical (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(EffectList{ Effects::ReduceCost(1) }));
    cards.emplace("DAL_561e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_563e] Power of EVIL (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_563e"));
    cards.emplace("DAL_563e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_570e] Never Surrender! (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_570e"));
    cards.emplace("DAL_570e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_576e] Kirin Tor's Curse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AddCost(1)));
    cards.emplace("DAL_576e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DAL_582t] Felhound Portal (*) - COST:2
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 2/2 Felhound with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(std::make_shared<SummonTask>("DAL_582t2"));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DAL_582t2"));
    cards.emplace("DAL_582t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_582t2] Felhound (*) - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_582t2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_589e] Hunting Party (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_607e] Fleeting Fel (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Dies at end of turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Rush));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<DestroyTask>(EntityType::TARGET),
    };
    cards.emplace("DAL_607e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_613] Faceless Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 2, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("DAL_613", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_614] Kobold Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DAL_614", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_615] Witchy Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform a friendly minion into one
    //       that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformMinionTask>(EntityType::TARGET, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_615", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_714e] Street Smarts (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_714e"));
    cards.emplace("DAL_714e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_726e] Scargil's Blessing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("DAL_726e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_727e] Heroic (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_727e"));
    cards.emplace("DAL_727e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_739] Goblin Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1 Attack
    //       and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DAL_739e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DAL_739", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_739e] Short Fuse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_739e"));
    cards.emplace("DAL_739e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_741] Ethereal Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("DAL_741", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_743t] Hench-Clan Squire (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_743t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_744e] Familiar Faces (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Copied health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::SetHealthScriptTag));
    cards.emplace("DAL_744e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_747t] Gryphon (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Faction: Alliance, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_747t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_751t] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DAL_751t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_752e] Toy-sized (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Jepetto Joybuzz made this 1/1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_752e"));
    cards.emplace("DAL_752e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_752e2] On Sale (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("DAL_752e2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_773e] Flying High (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DAL_773e"));
    cards.emplace("DAL_773e", cardDef);
}

void DalaranCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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