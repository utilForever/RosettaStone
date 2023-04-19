// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/DragonsCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void DragonsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600] Galakrond, the Wretched - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 1 random Demon. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::DEMON));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.heroPowerDbfID = 55807;
    cards.emplace("DRG_600", cardDef);

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 2 random Demons. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(
                      CardType::MINION, CardClass::INVALID, Race::DEMON),
                  std::make_shared<SummonTask>() },
        2));
    cardDef.property.heroPowerDbfID = 55807;
    cards.emplace("DRG_600t2", cardDef);

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 4 random Demons.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(
                      CardType::MINION, CardClass::INVALID, Race::DEMON),
                  std::make_shared<SummonTask>() },
        4));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cardDef.property.heroPowerDbfID = 55807;
    cards.emplace("DRG_600t3", cardDef);

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610] Galakrond, the Nightmare - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 1 card. It costs (0).
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55806;
    cards.emplace("DRG_610", cardDef);

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 cards. They cost (0).
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55806;
    cards.emplace("DRG_610t2", cardDef);

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 4 cards. They cost (0).
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(4, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cardDef.property.heroPowerDbfID = 55806;
    cards.emplace("DRG_610t3", cardDef);

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620] Galakrond, the Tempest - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 2/2 Storms with <b>Rush</b>.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t4", 2));
    cardDef.property.heroPowerDbfID = 55808;
    cards.emplace("DRG_620", cardDef);

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 4/4 Storms with <b>Rush</b>.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t5", 2));
    cardDef.property.heroPowerDbfID = 55808;
    cards.emplace("DRG_620t2", cardDef);

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 8/8 Storms with <b>Rush</b>.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t6", 2));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cardDef.property.heroPowerDbfID = 55808;
    cards.emplace("DRG_620t3", cardDef);

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650] Galakrond, the Unbreakable - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 1 minion. Give it +4/+4.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e", EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55805;
    cards.emplace("DRG_650", cardDef);

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 minions. Give them +4/+4.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e2", EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55805;
    cards.emplace("DRG_650t2", cardDef);

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 4 minions. Give them +4/+4.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(4, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e3", EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cardDef.property.heroPowerDbfID = 55805;
    cards.emplace("DRG_650t3", cardDef);

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660] Galakrond, the Unspeakable - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 1 random enemy minion.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55810;
    cards.emplace("DRG_660", cardDef);

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 2 random enemy minions.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.property.heroPowerDbfID = 55810;
    cards.emplace("DRG_660t2", cardDef);

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 4 random enemy minions.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 4));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cardDef.property.heroPowerDbfID = 55810;
    cards.emplace("DRG_660t3", cardDef);
}

void DragonsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- HERO_POWER - WARRIOR
    // [DRG_238p] Galakrond's Might (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Give your hero +3 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_238t10e", EntityType::HERO));
    cards.emplace("DRG_238p", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [DRG_238p2] Galakrond's Guile (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DRG_238p2", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [DRG_238p3] Galakrond's Malice (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon two 1/1 Imps.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_238t12t2", 2));
    cards.emplace("DRG_238p3", cardDef);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [DRG_238p4] Galakrond's Fury (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 2/1 Elemental with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_238t14t3", 1));
    cards.emplace("DRG_238p4", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [DRG_238p5] Galakrond's Wit (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a random Priest minion to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::PRIEST));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("DRG_238p5", cardDef);
}

void DragonsCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [DRG_051] Strength in Numbers - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Spend 10 Mana on minions.
    //       <b>Reward:</b> Summon a minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 10
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::PLAY_MINION));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        ComplexTask::SummonMinionFromDeck(), ProgressType::SPEND_MANA) };
    cardDef.property.questProgressTotal = 10;
    cards.emplace("DRG_051", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_311] Treenforcements - COST:1
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give a minion +2 Health and
    //       <b>Taunt</b>; or Summon a 2/2 Treant.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "DRG_311a", "DRG_311b" };
    cards.emplace("DRG_311", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DRG_312] Shrubadier - COST:2 [ATK:1/HP:1]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Treant.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_311t", SummonSide::RIGHT));
    cards.emplace("DRG_312", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DRG_313] Emerald Explorer - COST:6 [ATK:4/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DRAGON));
    cards.emplace("DRG_313", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_314] Aeroponics - COST:5
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Costs (2) less for each Treant you control.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            const auto minions = playable->player->GetFieldZone()->GetAll();
            int numTreants = 0;

            for (auto& minion : minions)
            {
                if (minion->card->name == "Treant")
                {
                    ++numTreants;
                }
            }

            return 2 * numTreants;
        }));
    cards.emplace("DRG_314", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_315] Embiggen - COST:0
    // - Set: Dragons, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give all minions in your deck +2/+2.
    //       They cost (1) more <i>(up to 10)</i>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_315e", EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<CustomTask>([](const Player* player, Entity* source,
                                        [[maybe_unused]] Playable* target) {
            const auto deckCards = player->GetDeckZone()->GetAll();

            for (auto& deckCard : deckCards)
            {
                if (deckCard->card->GetCardType() != CardType::MINION)
                {
                    continue;
                }

                if (deckCard->GetCost() < 10)
                {
                    Generic::AddEnchantment(Cards::FindCardByID("DRG_315e2"),
                                            dynamic_cast<Playable*>(source),
                                            deckCard, 0, 0, 0);
                }
            }
        }));
    cards.emplace("DRG_315", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_317] Secure the Deck - COST:1
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Attack twice with your hero.
    //       <b>Reward:</b> Add 3 'Claw' spells to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 2
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{
            std::make_shared<AddCardTask>(EntityType::HAND, "CS2_005", 3) }) };
    cardDef.property.questProgressTotal = 2;
    cards.emplace("DRG_317", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_318] Breath of Dreams - COST:2
    // - Faction: Neutral, Set: Dragons, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a card. If you're holding a Dragon,
    //       gain an empty Mana Crystal.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ManaCrystalTask>(1, false) }));
    cards.emplace("DRG_318", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DRG_319] Goru the Mightree - COST:7 [ATK:5/HP:10]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> For the rest of
    //       the game, your Treants have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_319e4", EntityType::PLAYER));
    cards.emplace("DRG_319", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DRG_320] Ysera, Unleashed - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 7 Dream Portals into your deck.
    //       When drawn, summon a random Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "DRG_320t", 7));
    cards.emplace("DRG_320", cardDef);
}

void DragonsCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [DRG_311a] Spin 'em Up (*) - COST:0
    // - Set: Dragons
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a 2/2 Treant.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_311t", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("DRG_311a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_311b] Small Repairs (*) - COST:0
    // - Set: Dragons
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_311e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DRG_311b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DRG_311t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_311t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [DRG_315e] Embiggened (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_315e"));
    cards.emplace("DRG_315e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [DRG_315e2] Costly Embiggening (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AddCost(1)));
    cards.emplace("DRG_315e2", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DRG_320t] Dream Portal (*) - COST:9
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon a random Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(std::make_shared<RandomMinionTask>(TagValues{
        { GameTag::CARDRACE, static_cast<int>(Race::DRAGON), RelaSign::EQ } }));
    cardDef.power.AddTopdeckTask(std::make_shared<SummonTask>());
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(TagValues{
        { GameTag::CARDRACE, static_cast<int>(Race::DRAGON), RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("DRG_320t", cardDef);
}

void DragonsCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_006] Corrosive Breath - COST:2
    // - Set: Dragons, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion. If you're holding
    //       a Dragon, it also hits the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3,
                                                     true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_006", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [DRG_007] Stormhammer - COST:3 [ATK:3/HP:0]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Doesn't lose Durability while you control a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::DRAGON)),
        GameTag::IMMUNE));
    cards.emplace("DRG_007", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_010] Diving Gryphon - COST:3 [ATK:4/HP:1]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Battlecry:</b> Draw a
    //       <b>Rush</b> minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasRush()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>());
    cards.emplace("DRG_010", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_095] Veranus - COST:6 [ATK:7/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change the Health of all enemy minions to 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_095e", EntityType::ENEMY_MINIONS));
    cards.emplace("DRG_095", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_251] Clear the Way - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Summon 3 <b>Rush</b> minions.
    //       <b>Reward:</b> Summon a 4/4 Gryphon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 3
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasRush())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_251t", 1) }) };
    cardDef.property.questProgressTotal = 3;
    cards.emplace("DRG_251", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_252] Phase Stalker - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you use your Hero Power,
    //       cast a <b>Secret</b> from your deck.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::CastSecretFromDeck() };
    cards.emplace("DRG_252", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_253] Dwarven Sharpshooter - COST:1 [ATK:1/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Hero Power can target minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::CAN_TARGET_MINION_BY_HERO_POWER,
                              EffectOperator::SET, 1) }));
    cards.emplace("DRG_253", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_254] Primordial Explorer - COST:3 [ATK:2/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - POISONOUS = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DRAGON));
    cards.emplace("DRG_254", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_255] Toxic Reinforcements - COST:1
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Use your Hero Power three times.
    //       <b>Reward:</b> Summon three 2/1 Leper Gnomes.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 3
    // - QUEST_REWARD_DATABASE_ID = 41127
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_255t2", 3) }) };
    cardDef.property.questProgressTotal = 3;
    cards.emplace("DRG_255", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_256] Dragonbane - COST:4 [ATK:3/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you use your Hero Power,
    //       deal 5 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 5)
    };
    cards.emplace("DRG_256", cardDef);
}

void DragonsCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DRG_095e] Intimidated (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetBaseHealth(1)));
    cards.emplace("DRG_095e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DRG_251t] Gryphon (*) - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_251t", cardDef);
}

void DragonsCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [DRG_102] Azure Explorer - COST:4 [ATK:2/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DRAGON));
    cards.emplace("DRG_102", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_104] Chenvaala - COST:3 [ATK:2/HP:5]
    // - Race: Elemental, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast three spells in a turn,
    //       summon a 5/5 Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    const auto trigger1 = std::make_shared<Trigger>(TriggerType::CAST_SPELL);
    trigger1->triggerSource = TriggerSource::SPELLS;
    trigger1->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<MathAddTask>(1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::TAG_SCRIPT_DATA_NUM_1),
        std::make_shared<SetGameTagNumberTask>(EntityType::SOURCE,
                                               GameTag::CUSTOM_KEYWORD_EFFECT),
        std::make_shared<NumberConditionTask>(3, RelaSign::EQ),
        std::make_shared<FlagTask>(
            true,
            TaskList{
                std::make_shared<SummonTask>("DRG_104t2"),
                std::make_shared<SetGameTagTask>(
                    EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1, 0),
                std::make_shared<SetGameTagTask>(
                    EntityType::SOURCE, GameTag::CUSTOM_KEYWORD_EFFECT, 0) })
    };
    const auto trigger2 = std::make_shared<Trigger>(TriggerType::TURN_END);
    trigger2->tasks = {
        std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                         GameTag::TAG_SCRIPT_DATA_NUM_1, 0),
        std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                         GameTag::CUSTOM_KEYWORD_EFFECT, 0)
    };
    cardDef.power.AddTrigger(std::make_shared<MultiTrigger>(
        std::vector<std::shared_ptr<Trigger>>{ trigger1, trigger2 }));
    cards.emplace("DRG_104", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_106] Arcane Breath - COST:1
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. If you're holding a Dragon,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(DiscoverType::SPELL) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_106", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_107] Violet Spellwing - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add an 'Arcane Missiles' spell
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "EX1_277", 1));
    cards.emplace("DRG_107", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_109] Mana Giant - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each card you've played this
    //       game that didn't start in your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumCardsPlayedThisGameNotStartInDeck();
        }));
    cards.emplace("DRG_109", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_270] Malygos, Aspect of Magic - COST:5 [ATK:2/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> an upgraded Mage spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(std::vector<std::string>{
                  "DRG_270t1",
                  "DRG_270t2",
                  "DRG_270t4",
                  "DRG_270t5",
                  "DRG_270t6",
                  "DRG_270t7",
                  "DRG_270t8",
                  "DRG_270t9",
                  "DRG_270t11",
              }) }));
    cards.emplace("DRG_270", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_321] Rolling Fireball - COST:5
    // - Set: Dragons, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 8 damage to a minion. Any excess damage
    //       continues to the left or right.
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
        []([[maybe_unused]] Player* player, Entity* source, Playable* target) {
            if (!target)
            {
                return;
            }

            auto continueFunc = [](FieldZone* fieldZone, Playable* _source,
                                   Minion* minion, int remainDamage,
                                   bool isLeft) {
                while (true)
                {
                    const int targetHealth = minion->GetHealth();
                    minion->TakeDamage(_source, remainDamage);

                    if (!minion->isDestroyed)
                    {
                        break;
                    }

                    remainDamage = remainDamage - targetHealth;
                    if (remainDamage <= 0)
                    {
                        break;
                    }

                    const int targetPos = minion->GetZonePosition();

                    if (isLeft && targetPos > 0)
                    {
                        minion = (*fieldZone)[targetPos - 1];
                    }
                    else if (!isLeft && targetPos < fieldZone->GetCount() - 1)
                    {
                        minion = (*fieldZone)[targetPos + 1];
                    }
                    else
                    {
                        break;
                    }
                }
            };

            const auto realSource = dynamic_cast<Playable*>(source);
            const auto realTarget = dynamic_cast<Character*>(target);

            const int targetHealth = realTarget->GetHealth();
            const int realDamage = 8 + source->player->GetCurrentSpellPower();

            Generic::TakeDamageToCharacter(realSource, realTarget, realDamage,
                                           true);

            if (realTarget->isDestroyed)
            {
                const int remainDamage = realDamage - targetHealth;
                if (remainDamage > 0)
                {
                    FieldZone* fieldZone = realTarget->player->GetFieldZone();
                    Minion* left = nullptr;
                    Minion* right = nullptr;
                    const int targetPos = realTarget->GetZonePosition();
                    int count = 0;
                    bool includeLeft = false, includeRight = false;

                    if (targetPos > 0)
                    {
                        left = (*fieldZone)[targetPos - 1];

                        if (!left->IsUntouchable())
                        {
                            includeLeft = true;
                            ++count;
                        }

                        if (targetPos < fieldZone->GetCount() - 1)
                        {
                            right = (*fieldZone)[targetPos + 1];

                            if (!right->IsUntouchable())
                            {
                                includeRight = true;
                                ++count;
                            }
                        }
                    }
                    else if (fieldZone->GetCount() > 1)
                    {
                        right = (*fieldZone)[targetPos + 1];

                        if (!right->IsUntouchable())
                        {
                            includeRight = true;
                            ++count;
                        }
                    }

                    if (count == 2)
                    {
                        const auto direction = Random::get<int>(0, 1);
                        if (direction == 0)
                        {
                            continueFunc(fieldZone, realSource, left,
                                         remainDamage, true);
                        }
                        else
                        {
                            continueFunc(fieldZone, realSource, right,
                                         remainDamage, false);
                        }
                    }
                    else if (count == 1)
                    {
                        if (includeLeft)
                        {
                            continueFunc(fieldZone, realSource, left,
                                         remainDamage, true);
                        }
                        else if (includeRight)
                        {
                            continueFunc(fieldZone, realSource, right,
                                         remainDamage, false);
                        }
                    }
                }
            }
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_321", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_322] Dragoncaster - COST:6 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       your next spell this turn costs (0).
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
                  "DRG_322e", EntityType::PLAYER) }));
    cards.emplace("DRG_322", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_323] Learn Draconic - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Spend 8 Mana on spells.
    //       <b>Reward:</b> Summon a 6/6 Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 8
    // - QUEST_REWARD_DATABASE_ID = 55282
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_323t") },
        ProgressType::SPEND_MANA_ON_SPELLS) };
    cardDef.property.questProgressTotal = 8;
    cards.emplace("DRG_323", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_324] Elemental Allies - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Play an Elemental 2 turns in a row.
    //       <b>Reward:</b> Draw 3 spells from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 2
    // - QUEST_REWARD_DATABASE_ID = 395
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    const auto trigger3 = std::make_shared<Trigger>(TriggerType::PLAY_MINION);
    trigger3->conditions = SelfCondList{ std::make_shared<SelfCondition>(
        SelfCondition::IsRace(Race::ELEMENTAL)) };
    trigger3->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{
            std::make_shared<IncludeTask>(EntityType::DECK),
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }),
            std::make_shared<RandomTask>(EntityType::STACK, 3),
            std::make_shared<DrawStackTask>() },
        ProgressType::PLAY_ELEMENTAL_MINONS) };
    const auto trigger4 = std::make_shared<Trigger>(TriggerType::TURN_END);
    trigger4->conditions = SelfCondList{ std::make_shared<SelfCondition>(
        SelfCondition::IsNotPlayElementalMinionThisTurn()) };
    trigger4->tasks = { std::make_shared<IncludeTask>(EntityType::SOURCE),
                        std::make_shared<FuncPlayableTask>(
                            [=](const std::vector<Playable*>& playables) {
                                const auto spell =
                                    dynamic_cast<Spell*>(playables[0]);
                                spell->SetGameTag(GameTag::QUEST_PROGRESS, 0);
                                return std::vector<Playable*>{};
                            }) };
    cardDef.power.AddTrigger(std::make_shared<MultiTrigger>(
        std::vector<std::shared_ptr<Trigger>>{ trigger3, trigger4 }));
    cardDef.property.questProgressTotal = 2;
    cards.emplace("DRG_324", cardDef);
}

void DragonsCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [DRG_104t2] Snow Elemental (*) - COST:5 [ATK:5/HP:5]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_104t2", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t1] Malygos's Intellect (*) - COST:3
    // - Set: Dragons
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(4));
    cards.emplace("DRG_270t1", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t2] Malygos's Tome (*) - COST:1
    // - Set: Dragons
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Add 3 random Mage spells to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE),
            std::make_shared<AddStackToTask>(EntityType::HAND) },
        3));
    cards.emplace("DRG_270t2", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t4] Malygos's Explosion (*) - COST:2
    // - Set: Dragons
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cards.emplace("DRG_270t4", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t5] Malygos's Nova (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("DRG_270t5", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t6] Malygos's Polymorph (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Transform a minion into a 1/1 Sheep.
    // - Spell School: Arcane
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::TARGET, "DRG_270t6t"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_270t6", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_270t6t] Malygos's Sheep (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Dragons
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_270t6t", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t7] Malygos's Flamestrike (*) - COST:7
    // - Set: Dragons
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 8 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 8, true));
    cards.emplace("DRG_270t7", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t8] Malygos's Frostbolt (*) - COST:0
    // - Set: Dragons
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 3 damage to a character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DRG_270t8", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t9] Malygos's Fireball (*) - COST:4
    // - Set: Dragons
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 8 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 8, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DRG_270t9", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t11] Malygos's Missiles (*) - COST:1
    // - Set: Dragons
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 6 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        6, true));
    cards.emplace("DRG_270t11", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [DRG_322e] Draconic Magic (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
        aura->removeTrigger = { TriggerType::CAST_SPELL,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsSpell()) };
    }
    cards.emplace("DRG_322e", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [DRG_323t] Draconic Emissary (*) - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_323t", cardDef);
}

void DragonsCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_008] Righteous Cause - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Summon 5 minions.
    //       <b>Reward:</b> Give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 5
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<AddEnchantmentTask>(
            "DRG_008e", EntityType::MINIONS) }) };
    cardDef.property.questProgressTotal = 5;
    cards.emplace("DRG_008", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_225] Sky Claw - COST:3 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your other Mechs have +1 Attack.
    //       <b>Battlecry:</b> Summon two 1/1 Microcopters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "DRG_225e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MECHANICAL));
    }
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_225t", SummonSide::LEFT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_225t", SummonSide::RIGHT));
    cards.emplace("DRG_225", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_226] Amber Watcher - COST:5 [ATK:4/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 8 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 8));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("DRG_226", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_229] Bronze Explorer - COST:3 [ATK:3/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - LIFESTEAL = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DRAGON));
    cards.emplace("DRG_229", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_231] Lightforged Crusader - COST:7 [ATK:7/HP:7]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       add 5 random Paladin cards to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasNoNeutralCardsInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<EnqueueTask>(
            TaskList{ std::make_shared<RandomCardTask>(CardType::INVALID,
                                                       CardClass::PALADIN),
                      std::make_shared<AddStackToTask>(EntityType::HAND) },
            5) }));
    cards.emplace("DRG_231", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_232] Lightforged Zealot - COST:4 [ATK:4/HP:2]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       equip a 4/2 Truesilver Champion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasNoNeutralCardsInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<WeaponTask>("DRG_232t") }));
    cards.emplace("DRG_232", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_233] Sand Breath - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+2. Give it <b>Divine Shield</b>
    //       if you're holding a Dragon.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_233e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SetGameTagTask>(
                  EntityType::TARGET, GameTag::DIVINE_SHIELD, 1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_233", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_235] Dragonrider Talritha - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a Dragon in your hand +3/+3
    //       and this <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("DRG_235e", EntityType::STACK));
    cards.emplace("DRG_235", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_258] Sanctuary - COST:2
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Take no damage for a turn.
    //       <b>Reward:</b> Summon a 3/6 minion with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 1
    // - QUEST_REWARD_DATABASE_ID = 57723
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsMyHeroUndamagedEnemyTurn()) };
    cardDef.power.GetTrigger()->eitherTurn = true;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_258t") }) };
    cardDef.property.questProgressTotal = 1;
    cards.emplace("DRG_258", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_309] Nozdormu the Timeless - COST:4 [ATK:8/HP:8]
    // - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set each player to 10 Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ManaCrystalTask>(10, false, false));
    cardDef.power.AddPowerTask(
        std::make_shared<ManaCrystalTask>(10, false, true));
    cards.emplace("DRG_309", cardDef);
}

void DragonsCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [DRG_225t] Microcopter (*) - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_225t", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [DRG_232t] Truesilver Champion (*) - COST:4 [ATK:4/HP:0]
    // - Faction: Neutral, Set: Dragons, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::HERO, 2) };
    cards.emplace("DRG_232t", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [DRG_258t] Indomitable Champion (*) - COST:4 [ATK:3/HP:6]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_258t", cardDef);
}

void DragonsCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [DRG_090] Murozond the Infinite - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Play all cards
    //       your opponent played last turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<
                               CustomTask>([](Player* player,
                                              [[maybe_unused]] Entity* source,
                                              [[maybe_unused]] Playable*
                                                  target) {
        auto cardsOpPlayedLastTurn = player->opponent->cardsPlayedThisTurn;
        Random::shuffle(cardsOpPlayedLastTurn.begin(),
                        cardsOpPlayedLastTurn.end());

        for (const auto& card : cardsOpPlayedLastTurn)
        {
            auto validTargets = card->GetValidPlayTargets(player);
            if (card->mustHaveToTargetToPlay && validTargets.empty())
            {
                continue;
            }

            const auto targetIdx =
                Random::get<std::size_t>(0, validTargets.size() - 1);
            const auto randTarget =
                validTargets.empty() ? nullptr : validTargets[targetIdx];
            const auto chooseOneIdx = Random::get<int>(1, 2);

            Entity* entity = Entity::GetFromCard(player, card);

            switch (card->GetCardType())
            {
                case CardType::HERO:
                {
                    Generic::PlayHero(player, dynamic_cast<Hero*>(entity),
                                      randTarget, chooseOneIdx);
                    break;
                }
                case CardType::MINION:
                case CardType::LOCATION:
                {
                    if (player->GetFieldZone()->IsFull())
                    {
                        break;
                    }

                    Generic::Summon(dynamic_cast<Minion*>(entity), -1, player);

                    player->game->ProcessDestroyAndUpdateAura();
                    break;
                }
                case CardType::SPELL:
                {
                    Generic::CastSpell(player, dynamic_cast<Spell*>(entity),
                                       randTarget, chooseOneIdx);

                    while (player->choice)
                    {
                        const auto choiceIdx = Random::get<std::size_t>(
                            0, player->choice->choices.size());
                        Generic::ChoicePick(player,
                                            static_cast<int>(choiceIdx));
                    }

                    player->game->ProcessDestroyAndUpdateAura();
                    break;
                }
                case CardType::WEAPON:
                {
                    const auto weapon = dynamic_cast<Weapon*>(entity);

                    if (const auto aura = weapon->card->power.GetAura(); aura)
                    {
                        aura->Activate(weapon);
                    }

                    if (const auto trigger = weapon->card->power.GetTrigger();
                        trigger)
                    {
                        trigger->Activate(weapon);
                    }

                    player->GetHero()->AddWeapon(*weapon);
                    break;
                }
                case CardType::INVALID:
                case CardType::GAME:
                case CardType::PLAYER:
                case CardType::ENCHANTMENT:
                case CardType::ITEM:
                case CardType::TOKEN:
                case CardType::HERO_POWER:
                case CardType::BLANK:
                case CardType::GAME_MODE_BUTTON:
                case CardType::MOVE_MINION_HOVER_TARGET:
                case CardType::LETTUCE_ABILITY:
                case CardType::BATTLEGROUND_HERO_BUDDY:
                case CardType::BATTLEGROUND_QUEST_REWARD:
                    throw std::invalid_argument(
                        "Murozond the Infinite (DRG_090) - Invalid card type!");
            }
        }
    }));
    cards.emplace("DRG_090", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_246] Time Rip - COST:5
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_246", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DRG_300] Fate Weaver - COST:4 [ATK:3/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       reduce the Cost of cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasInvokedTwice()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DRG_300e", EntityType::HAND) }));
    cards.emplace("DRG_300", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_301] Whispers of EVIL - COST:0
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DRG_301", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_302] Grave Rune - COST:4
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Summon 2 copies of this."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_302e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_302", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DRG_303] Disciple of Galakrond - COST:1 [ATK:1/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_303", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DRG_304] Chronobreaker - COST:5 [ATK:4/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you're holding a Dragon,
    //       deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FlagTask>(true, TaskList{ std::make_shared<DamageTask>(
                                             EntityType::ENEMY_MINIONS, 3) }));
    cards.emplace("DRG_304", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DRG_306] Envoy of Lazul - COST:2 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards.
    //       Guess which one is in your opponent's hand
    //       to get a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, [[maybe_unused]] Playable* target) {
            // Envoy of Lazul attempts to show three cards: one card in the
            // opponent's hand, and two cards that are in the opponent's current
            // deck but not in the opponent's hand.
            const auto opHandCards = player->opponent->GetHandZone()->GetAll();

            // If the opponent has no cards in hand,
            // Envoy of Lazul's Battlecry does nothing.
            if (opHandCards.empty())
            {
                return;
            }

            std::vector<Card*> result;
            result.reserve(3);

            // For the one card in the opponent's hand:
            // The card being shown in the opponent's hand does not have
            // to be a card that started in the opponent's deck.
            const auto idx =
                Random::get<std::size_t>(0, opHandCards.size() - 1);
            result.emplace_back(opHandCards[idx]->card);

            // For the two cards not in the opponent's hand:
            std::vector<Card*> opDeckCards;

            for (const auto& deckCard :
                 player->opponent->GetDeckZone()->GetAll())
            {
                // Pass if it exists in hand zone
                bool existInHand = false;
                for (auto& handCard : opHandCards)
                {
                    if (handCard->card->id == deckCard->card->id)
                    {
                        existInHand = true;
                        break;
                    }
                }

                if (existInHand)
                {
                    continue;
                }

                // Pass if it exists in opponent deck cards
                bool existInDeck = false;
                for (const auto& opDeckCard : opDeckCards)
                {
                    if (opDeckCard->id == deckCard->card->id)
                    {
                        existInDeck = true;
                        break;
                    }
                }

                if (existInDeck)
                {
                    continue;
                }

                opDeckCards.emplace_back(deckCard->card);
            }

            // If the opponent's current deck is empty, two cards that had
            // started in the opponent's deck will be picked instead.
            // If the opponent's current deck has only one card left, the same
            // thing happens; two cards that had started in the opponent's deck
            // will be picked instead.
            if (opDeckCards.size() < 2)
            {
                const auto startDeck =
                    player->game->GetPlayerDeck(player->opponent->playerType);
                auto twoCards = ChooseNElements(startDeck, 2);
                result.emplace_back(twoCards[0]);
                result.emplace_back(twoCards[1]);
            }
            else
            {
                auto twoCards = ChooseNElements(opDeckCards, 2);
                result.emplace_back(twoCards[0]);
                result.emplace_back(twoCards[1]);
            }

            Random::shuffle(result.begin(), result.end());
            Generic::CreateChoiceCards(player, source, ChoiceType::GENERAL,
                                       ChoiceAction::ENVOY_OF_LAZUL, result);
        }));
    cards.emplace("DRG_306", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_307] Breath of the Infinite - COST:3
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    //       If you're holding a Dragon, only damage enemies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS,
                                                     2, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<DamageTask>(EntityType::ALL_MINIONS,
                                                      2, true) }));
    cards.emplace("DRG_307", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DRG_308] Mindflayer Kaahrj - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an enemy minion.
    //       <b>Deathrattle:</b> Summon a new copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::ENTITY_ID));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_308e", EntityType::SOURCE, false, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("DRG_308", cardDef);
}

void DragonsCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [DRG_300e] Draconic Fate (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("DRG_300e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [DRG_302e] Grave Rune (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon 2 copies of this.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<CopyTask>(EntityType::SOURCE, ZoneType::PLAY, 2));
    cards.emplace("DRG_302e", cardDef);
}

void DragonsCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [DRG_027] Umbral Skulker - COST:4 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       add 3 Coins to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasInvokedTwice()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddCardTask>(EntityType::HAND,
                                                      "GAME_005", 3) }));
    cards.emplace("DRG_027", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_028] Dragon's Hoard - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Legendary</b> minion
    //       from another class.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(
        CardType::MINION, CardClass::ANOTHER_CLASS, Race::INVALID,
        Rarity::LEGENDARY));
    cards.emplace("DRG_028", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_030] Praise Galakrond! - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1 Attack. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_030e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_030", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_031] Necrium Apothecary - COST:4 [ATK:2/HP:5]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Draw a <b>Deathrattle</b> minion
    //       from your deck and gain its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddComboTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle()) }));
    cardDef.power.AddComboTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddComboTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsStackNum(1, RelaSign::GEQ)) }));
    cardDef.power.AddComboTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomTask>(EntityType::STACK, 1),
                        std::make_shared<GetGameTagTask>(EntityType::STACK,
                                                         GameTag::ENTITY_ID),
                        std::make_shared<AddEnchantmentTask>(
                            "DRG_031e", EntityType::SOURCE, false, true),
                        std::make_shared<DrawStackTask>() }));
    cards.emplace("DRG_031", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_033] Candle Breath - COST:6
    // - Set: Dragons, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    //       Costs (3) less while you're holding a Dragon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            const auto hands = playable->player->GetHandZone()->GetAll();

            for (const auto& card : hands)
            {
                if (card->card->GetRace() == Race::DRAGON)
                {
                    return 3;
                }
            }

            return 0;
        }));
    cards.emplace("DRG_033", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_034] Stowaway - COST:5 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If there are cards in your deck
    //       that didn't start there, draw 2 of them.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsNotStartInDeck()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 2));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>());
    cards.emplace("DRG_034", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_035] Bloodsail Flybooter - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1/1 Pirates to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DRG_035t", 2));
    cards.emplace("DRG_035", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_036] Waxadred - COST:5 [ATK:7/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle a Candle into your deck
    //       that resummons Waxadred when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "DRG_036t", 1));
    cards.emplace("DRG_036", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_037] Flik Skyshiv - COST:6 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion and all copies
    //       of it <i>(wherever they are)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyAllTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_037", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_247] Seal Fate - COST:3
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to an undamaged character.
    //       <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_UNDAMAGED_TARGET, 0 } };
    cards.emplace("DRG_247", cardDef);
}

void DragonsCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_030e] Praise Galakrond! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_030e"));
    cards.emplace("DRG_030e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_031e] Necrium Infusion (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Copied Deathrattle from {0}.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ActivateCapturedDeathrattleTask>());
    cards.emplace("DRG_031e", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [DRG_035t] Sky Pirate (*) - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_035t", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_036t] Waxadred's Candle (*) - COST:5
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon Waxadred.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(std::make_shared<SummonTask>("DRG_036"));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_036"));
    cards.emplace("DRG_036t", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_074e] Camouflaged (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Stealth));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("DRG_074e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_610e] Galakrond's Wonder (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("DRG_610e", cardDef);
}

void DragonsCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_096] Bandersmosh - COST:5 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Each turn this is in your hand, transform it into a
    //       5/5 copy of a random <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsInZone(ZoneType::HAND)) }),
        std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<ChangeEntityTask>(
                                EntityType::SOURCE, CardType::MINION,
                                CardClass::INVALID, Race::INVALID,
                                Rarity::LEGENDARY, true),
                            std::make_shared<AddEnchantmentTask>(
                                "DRG_096e", EntityType::SOURCE),
                            std::make_shared<AddEnchantmentTask>(
                                "DRG_096e2", EntityType::SOURCE) })
    };
    cards.emplace("DRG_096", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_211] Squallhunter - COST:4 [ATK:5/HP:7]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b> <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // - OVERLOAD = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_211", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_215] Storm's Wrath - COST:1
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions +1/+1. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_215e", EntityType::MINIONS));
    cards.emplace("DRG_215", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_216] Surging Tempest - COST:1 [ATK:1/HP:3]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +1 Attack while you have <b>Overloaded</b>
    //       Mana Crystals.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            return (playable->player->GetOverloadLocked() > 0 ||
                    playable->player->GetOverloadOwed() > 0)
                       ? 1
                       : 0;
        }));
    cards.emplace("DRG_216", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_217] Dragon's Pack - COST:5
    // - Set: Dragons, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       If you've <b>Invoked</b> twice, give them +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_217t", 2, SummonSide::SPELL, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasInvokedTwice()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DRG_217e", EntityType::STACK) }));
    cards.emplace("DRG_217", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_218] Corrupt Elementalist - COST:5 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond twice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_218", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_219] Lightning Breath - COST:3
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. If you're holding
    //       a Dragon, also damage its neighbors.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<IncludeAdjacentTask>(EntityType::TARGET),
                  std::make_shared<DamageTask>(EntityType::STACK, 4, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_219", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_223] Cumulo-Maximus - COST:5 [ATK:5/HP:5]
    // - Race: Elemental, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have <b>Overloaded</b>
    //       Mana Crystals, deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsOverloaded()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 5) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("DRG_223", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224] Nithogg - COST:6 [ATK:5/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 0/3 Eggs.
    //       Next turn they hatch into 4/4 Drakes with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_224t", SummonSide::LEFT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_224t", SummonSide::RIGHT));
    cards.emplace("DRG_224", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_248] Invocation of Frost - COST:1
    // - Set: Dragons, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> an enemy. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("DRG_248", cardDef);
}

void DragonsCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_068e] Toasty (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Can't be <b>Frozen</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(GameTag::CANT_BE_FROZEN,
                                                       EffectOperator::SET, 1));
    cards.emplace("DRG_068e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_096e2] Smoshing (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: 5/5.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(
        EffectList{ Effects::SetAttack(5), Effects::SetBaseHealth(5) }));
    cards.emplace("DRG_096e2", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_216e] Surging (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_217t] Spirit Wolf (*) - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_217t", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224t] Storm Egg (*) - COST:1 [ATK:0/HP:3]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: At the start of your turn, transform into
    //       a 4/4 Storm Drake with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<TransformTask>(
        EntityType::SOURCE, "DRG_224t2") };
    cards.emplace("DRG_224t", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224t2] Storm Drake (*) - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_224t2", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_238t14t3] Windswept Elemental (*) - COST:2 [ATK:2/HP:1]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_238t14t3", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t4] Brewing Storm (*) - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t4", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t5] Living Storm (*) - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t5", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t6] Raging Storm (*) - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t6", cardDef);
}

void DragonsCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [DRG_201] Crazed Netherwing - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 3 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::ALL_NOSOURCE, 3) }));
    cards.emplace("DRG_201", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_202] Dragonblight Cultist - COST:3 [ATK:1/HP:1]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    //       Gain +1 Attack for each other friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_202e", EntityType::SOURCE, true));
    cards.emplace("DRG_202", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_203] Veiled Worshipper - COST:4 [ATK:5/HP:4]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasInvokedTwice()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(3) }));
    cards.emplace("DRG_203", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_204] Dark Skies - COST:3
    // - Faction: Neutral, Set: Dragons, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 1 damage to a random minion.
    //       Repeat for each card in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1, true) }));
    cards.emplace("DRG_204", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_205] Nether Breath - COST:2
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 2 damage. If you're holding a Dragon,
    //       deal 4 damage with <b>Lifesteal</b> instead.
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                                   GameTag::LIFESTEAL, 1),
                  std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("DRG_205", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_206] Rain of Fire - COST:1
    // - Set: Dragons, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 1 damage to all characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL, 1, true));
    cards.emplace("DRG_206", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_207] Abyssal Summoner - COST:6 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Demon with <b>Taunt</b>
    //       and stats equal to your hand size.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("DRG_207t", SummonSide::RIGHT, true));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            if (const auto minion = dynamic_cast<Minion*>(playables[0]))
            {
                const auto count = minion->player->GetHandZone()->GetCount();
                minion->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, count);

                minion->SetAttack(count);
                minion->SetBaseHealth(count);
                minion->SetCost(count);
            }

            return std::vector<Playable*>{};
        }));
    cards.emplace("DRG_207", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_208] Valdris Felgorge - COST:7 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Increase your maximum hand size
    //       to 12. Draw 4 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](const Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            player->GetHandZone()->Expand(12);
        }));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(4));
    cards.emplace("DRG_208", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_209] Zzeraku the Warped - COST:8 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your hero takes damage,
    //       summon a 6/6 Nether Drake.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "DRG_209t", 1) };
    cards.emplace("DRG_209", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_250] Fiendish Rites - COST:3
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Invoke</b> Galakrond.
    //       Give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_250e", EntityType::MINIONS));
    cards.emplace("DRG_250", cardDef);
}

void DragonsCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [DRG_202e] Power of the Cult (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("DRG_202e", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_207t] Abyssal Destroyer (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_207t", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_209t] Nether Drake (*) - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_209t", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DRG_238t12t2] Draconic Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_238t12t2", cardDef);
}

void DragonsCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [DRG_019] Scion of Ruin - COST:3 [ATK:3/HP:2]
    // - Race: Dragon, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> If you've
    //       <b>Invoked</b> twice, summon 2 copies of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasInvokedTwice()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<SummonCopyTask>(EntityType::SOURCE, false,
                                                   false, SummonSide::LEFT),
                  std::make_shared<SummonCopyTask>(
                      EntityType::SOURCE, false, false, SummonSide::RIGHT) }));
    cards.emplace("DRG_019", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DRG_020] EVIL Quartermaster - COST:3 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    //       Gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(3));
    cards.emplace("DRG_020", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [DRG_021] Ritual Chopper - COST:2 [ATK:1/HP:0]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_021", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_022] Ramming Speed - COST:3
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Force a minion to attack one of its neighbors.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::TARGET, EntityType::STACK, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_022", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DRG_023] Skybarge - COST:3 [ATK:2/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a Pirate,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::PIRATE))
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 2)
    };
    cards.emplace("DRG_023", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DRG_024] Sky Raider - COST:1 [ATK:1/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Pirate to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::PIRATE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("DRG_024", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [DRG_025] Ancharrr - COST:3 [ATK:2/HP:0]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks, draw a Pirate from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::DECK),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::PIRATE)) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DrawStackTask>()
    };
    cards.emplace("DRG_025", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DRG_026] Deathwing, Mad Aspect - COST:8 [ATK:12/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Attack ALL other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](const Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            auto enemyMinions = player->opponent->GetFieldZone()->GetAll();
            Random::shuffle(enemyMinions.begin(), enemyMinions.end());

            auto& curField = *(player->GetFieldZone());
            const auto deathwing =
                curField[player->GetFieldZone()->GetCount() - 1];

            for (const auto& minion : enemyMinions)
            {
                Generic::Attack(player, deathwing, minion, true);

                if (deathwing->isDestroyed)
                {
                    break;
                }
            }
        }));
    cards.emplace("DRG_026", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_249] Awaken! - COST:3
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Invoke</b> Galakrond. Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("DRG_249", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_500] Molten Breath - COST:4
    // - Set: Dragons, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    //       If you're holding a Dragon, gain 5 Armor.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ArmorTask>(5) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DRG_500", cardDef);
}

void DragonsCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DRG_238t10e] Galakrond's Might (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_238t10e"));
    cards.emplace("DRG_238t10e", cardDef);
}

void DragonsCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_049] Tasty Flyfish - COST:2 [ATK:2/HP:2]
    // - Race: Murloc, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a Dragon in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("DRG_049e", EntityType::STACK));
    cards.emplace("DRG_049", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_050] Devoted Maniac - COST:4 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - RUSH = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_050", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_054] Big Ol' Whelp - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("DRG_054", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_055] Hoard Pillager - COST:4 [ATK:4/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip one of your destroyed weapons.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDead()),
        std::make_shared<SelfCondition>(SelfCondition::IsWeapon()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY));
    cards.emplace("DRG_055", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_056] Parachute Brigand - COST:2 [ATK:2/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a Pirate,
    //       summon this minion from your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::PLAY_MINION));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::PIRATE))
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                                  SelfCondition::IsFieldNotFull()) }),
        std::make_shared<FlagTask>(
            true,
            TaskList{ std::make_shared<RemoveHandTask>(EntityType::SOURCE),
                      std::make_shared<SummonTask>() })
    };
    cards.emplace("DRG_056", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_057] Hot Air Balloon - COST:1 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn, gain +1 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DRG_057e", EntityType::SOURCE) };
    cards.emplace("DRG_057", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_058] Wing Commander - COST:4 [ATK:2/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack for each Dragon in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            int numDragon = 0;

            for (const auto& card : playable->player->GetHandZone()->GetAll())
            {
                if (card->card->GetRace() == Race::DRAGON)
                {
                    ++numDragon;
                }
            }

            return 2 * numDragon;
        }));
    cards.emplace("DRG_058", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_059] Goboglide Tech - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Mech,
    //       gain +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::MECHANICAL)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                            "DRG_059e", EntityType::SOURCE),
                        std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                                         GameTag::RUSH, 1) }));
    cards.emplace("DRG_059", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_060] Fire Hawk - COST:3 [ATK:1/HP:3]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack for each card
    //       in your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_HAND));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_060e", EntityType::SOURCE, true));
    cards.emplace("DRG_060", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_061] Gyrocopter - COST:6 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_061", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_062] Wyrmrest Purifier - COST:2 [ATK:3/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform all Neutral cards
    //       in your deck into random cards from your class.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const auto legendaryCards = RandomCardTask::GetCardList(
                player->GetHero(), CardType::INVALID, CardClass::PLAYER_CLASS);
            const auto deck = player->GetDeckZone();

            for (const auto& card : deck->GetAll())
            {
                if (card->card->GetCardClass() != CardClass::NEUTRAL)
                {
                    continue;
                }

                const auto idx =
                    Random::get<std::size_t>(0, legendaryCards.size() - 1);
                Generic::ChangeEntity(player, card, legendaryCards[idx], false);
            }
        }));
    cards.emplace("DRG_062", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_063] Dragonmaw Poacher - COST:4 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent controls a Dragon,
    //       gain +4/+4 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsOpControllingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DRG_063e", EntityType::SOURCE) }));
    cards.emplace("DRG_063", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_064] Zul'Drak Ritualist - COST:4 [ATK:3/HP:9]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Summon three
    //       random 1-Cost minions for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomMinionTask>(
                      TagValues{ { GameTag::COST, 1, RelaSign::EQ } }, 1, true),
                  std::make_shared<SummonOpTask>() },
        3));
    cards.emplace("DRG_064", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_065] Hippogryph - COST:4 [ATK:2/HP:6]
    // - Race: Beast, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_065", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_066] Evasive Chimaera - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_066", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_067] Troll Batrider - COST:4 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 3));
    cards.emplace("DRG_067", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_068] Living Dragonbreath - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions can't be <b>Frozen</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::PLAYER, "DRG_068e"));
    cards.emplace("DRG_068", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_069] Platebreaker - COST:5 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::ENEMY_HERO, GameTag::ARMOR, 0));
    cards.emplace("DRG_069", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_070] Dragon Breeder - COST:2 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Dragon.
    //       Add a copy of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 24
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::HAND));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 24 } };
    cards.emplace("DRG_070", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_071] Bad Luck Albatross - COST:3 [ATK:4/HP:3]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle two 1/1 Albatross
    //       into your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_DECK, "DRG_071t", 2));
    cards.emplace("DRG_071", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_072] Skyfin - COST:5 [ATK:3/HP:3]
    // - Race: Murloc, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       summon 2 random Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<EnqueueTask>(
            TaskList{ std::make_shared<RandomCardTask>(
                          CardType::MINION, CardClass::INVALID, Race::MURLOC),
                      std::make_shared<SummonTask>() },
            2) }));
    cards.emplace("DRG_072", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_073] Evasive Feywing - COST:4 [ATK:5/HP:4]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_073", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_074] Camouflaged Dirigible - COST:6 [ATK:6/HP:6]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Mechs
    //       <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsRace(Race::MECHANICAL)) }));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_074e", EntityType::STACK, false, false,
        SelfCondition::HasNotStealth()));
    cards.emplace("DRG_074", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_075] Cobalt Spellkin - COST:5 [ATK:3/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1-Cost spells from
    //       your class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomSpellTask>(
        CardClass::PLAYER_CLASS, GameTag::COST, 1, 2, RelaSign::EQ));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("DRG_075", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_076] Faceless Corruptor - COST:5 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> Transform
    //       one of your minions into a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TransformCopyTask>(true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("DRG_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_077] Utgarde Grapplesniper - COST:6 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Both players draw a card.
    //       If it's a Dragon, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonStackTask>(true) }));
    cardDef.power.AddPowerTask(std::make_shared<ClearStackTask>());
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonStackTask>(true) }));
    cards.emplace("DRG_077", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_078] Depth Charge - COST:1 [ATK:0/HP:5]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 5 damage to ALL minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 5) };
    cards.emplace("DRG_078", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_079] Evasive Wyrm - COST:6 [ATK:5/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>. <b>Rush</b>.
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - RUSH = 1
    // - 1211 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_079", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_081] Scalerider - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("DRG_081", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_082] Kobold Stickyfinger - COST:5 [ATK:4/HP:4]
    // - Race: Pirate, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Steal your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            if (player->opponent->GetHero()->HasWeapon())
            {
                player->GetHero()->AddWeapon(
                    *player->opponent->GetHero()->weapon);
                player->GetHero()->weapon->player = player;
                player->opponent->GetHero()->weapon = nullptr;
            }
        }));
    cards.emplace("DRG_082", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_084] Tentacled Menace - COST:5 [ATK:6/HP:5]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws a card.
    //       Swap their Costs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_084e", EntityType::STACK));
    cards.emplace("DRG_084", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_086] Chromatic Egg - COST:5 [ATK:0/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Secretly <b>Discover</b>
    //       a Dragon to hatch into. <b>Deathrattle:</b> Hatch!
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(
        CardType::MINION, CardClass::INVALID, Race::DRAGON, Rarity::INVALID,
        ChoiceAction::ENCHANTMENT));
    cardDef.power.AddAfterChooseTask(std::make_shared<AddEnchantmentTask>(
        "DRG_086e", EntityType::SOURCE, false, true));
    cards.emplace("DRG_086", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_088] Dread Raven - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Has +3 Attack for each other Dread Raven you control.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            int numDreadRaven = 0;

            for (const auto& card : playable->player->GetFieldZone()->GetAll())
            {
                if (card->card->id == "DRG_088")
                {
                    ++numDreadRaven;
                }
            }

            return 3 * (numDreadRaven - 1);
        }));
    cards.emplace("DRG_088", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_089] Dragonqueen Alexstrasza - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       add 2 other random Dragons to your hand. They cost (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNoDuplicateInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<RandomMinionTask>(
                TagValues{ { GameTag::CARDRACE, static_cast<int>(Race::DRAGON),
                             RelaSign::EQ } },
                2, false, true),
            std::make_shared<AddEnchantmentTask>("DRG_089e", EntityType::STACK),
            std::make_shared<AddStackToTask>(EntityType::HAND) }));
    cards.emplace("DRG_089", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_091] Shu'ma - COST:7 [ATK:1/HP:7]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       fill your board with 1/1 Tentacles.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_091t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("DRG_091t", SummonSide::LEFT) },
        3) };
    cards.emplace("DRG_091", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_092] Transmogrifier - COST:2 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you draw a card,
    //       transform it into a random <b>Legendary</b> minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DRAW_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ChangeEntityTask>(
        EntityType::TARGET, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY, true) };
    cards.emplace("DRG_092", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_099] Kronx Dragonhoof - COST:6 [ATK:6/HP:6]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw Galakrond.
    //       If you're already Galakrond, unleash a Devastation.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsGalakrondHero()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(
                  std::vector<std::string>{ "DRG_099t1", "DRG_099t2",
                                            "DRG_099t3", "DRG_099t4" },
                  ChoiceAction::CAST_SPELL, 4, false) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<IncludeTask>(EntityType::DECK),
                         std::make_shared<FilterStackTask>(
                             SelfCondList{ std::make_shared<SelfCondition>(
                                 SelfCondition::IsGalakrondHero()) }),
                         std::make_shared<RandomTask>(EntityType::STACK, 1),
                         std::make_shared<DrawStackTask>() }));
    cards.emplace("DRG_099", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_213] Twin Tyrant - COST:8 [ATK:4/HP:10]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to two random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 4));
    cards.emplace("DRG_213", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_239] Blazing Battlemage - COST:1 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_239", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_242] Shield of Galakrond - COST:5 [ATK:4/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_242", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_257] Frizz Kindleroost - COST:4 [ATK:5/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of Dragons
    //       in your deck by (2).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_257e3", EntityType::STACK));
    cards.emplace("DRG_257", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_310] Evasive Drakonid - COST:7 [ATK:7/HP:7]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_310", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_401] Grizzled Wizard - COST:2 [ATK:3/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap Hero Powers with your opponent
    //       until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SwapHeroPowerTask>());
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_401e", EntityType::PLAYER));
    cards.emplace("DRG_401", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_402] Sathrovarr - COST:9 [ATK:5/HP:5]
    // - Race: Demon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Add a copy of it to your hand, deck, and battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<SummonCopyTask>(
        EntityType::TARGET, false, false, SummonSide::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("DRG_402", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_403] Blowtorch Saboteur - COST:3 [ATK:3/HP:4]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's next
    //       Hero Power costs (3).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_403e", EntityType::ENEMY_PLAYER));
    cards.emplace("DRG_403", cardDef);
}

void DragonsCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_008e] Righteous Cause (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_008e"));
    cards.emplace("DRG_008e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_049e] Well Fed (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_049e"));
    cards.emplace("DRG_049e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_052] Draconic Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - MARK_OF_EVIL = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DRAGON));
    cards.emplace("DRG_052", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_057e] Up, Up, and Away! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::HealthN(1)));
    cards.emplace("DRG_057e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_058e] Commanding (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_058e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_059e] Gobogliding (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_059e"));
    cards.emplace("DRG_059e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_060e] Fired Up (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("DRG_060e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_063e] Poaching (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4 and <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_063e"));
    cards.emplace("DRG_063e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_071t] Albatross (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_071t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_084e] Tentacle Confusion (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Cost swapped by Tentacled Menace.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<SwapCostEnchant>());
    cards.emplace("DRG_084e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_086e] What's in the Egg? (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: It's a mystery...@{0} is inside!
    //       <i>(Only you can see this.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonCapturedMinionTask>());
    cards.emplace("DRG_086e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_088e] Conspiracy of Ravens (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3 Attack for each other Dread Raven.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_088e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_089e] A Queen's Discount (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("DRG_089e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_091t] Tentacle (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dragons
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_091t", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t1] Decimation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    //       Restore 5 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cards.emplace("DRG_099t1", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t2] Reanimation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Summon an 8/8 Dragon with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("DRG_099t2t"));
    cards.emplace("DRG_099t2", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t3] Domination (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Give your other minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "DRG_099t3e", EntityType::MINIONS_NOEVENTSOURCE));
    cards.emplace("DRG_099t3", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t4] Annihilation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 5 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS_NOEVENTSOURCE, 5, true));
    cards.emplace("DRG_099t4", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_096e] Smoshing (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Transforming into random <b>Legendary</b> minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(GameTag::SHIFTING_MINION,
                                                       EffectOperator::SET, 1));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                                  SelfCondition::IsInZone(ZoneType::HAND)) }),
        std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<ChangeEntityTask>(
                                EntityType::TARGET, CardType::MINION,
                                CardClass::INVALID, Race::INVALID,
                                Rarity::LEGENDARY, true),
                            std::make_shared<AddEnchantmentTask>(
                                "DRG_096e", EntityType::TARGET) })
    };
    cards.emplace("DRG_096e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_099t2t] Reanimated Dragon (*) - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_099t2t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_099t3e] Dominating (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_099t3e"));
    cards.emplace("DRG_099t3e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_215e] Storm's Wrath (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_215e"));
    cards.emplace("DRG_215e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_217e] Galakrond's Power (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_217e"));
    cards.emplace("DRG_217e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_225e] Mechanical Might (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack from Sky Claw.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_225e"));
    cards.emplace("DRG_225e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_233e] Sand Breath (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_233e"));
    cards.emplace("DRG_233e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_235d] Dragonrider Talritha Effect Dummy (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_235d", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_235e] Rider Talritha (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3/+3 and <b>Deathrattle:</b> Give a Dragon in your hand this
    // enchant.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_235e"));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("DRG_235e", EntityType::STACK));
    cards.emplace("DRG_235e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_250e] Fiendish Rites (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_250e"));
    cards.emplace("DRG_250e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_255t2] Leper Gnome (*) - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("DRG_255t2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_257e3] Ready to Hatch! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("DRG_257e3", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_308e] Shadowborn (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon {0}.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonCapturedMinionTask>());
    cards.emplace("DRG_308e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_311e] Spore Hardened (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_311e"));
    cards.emplace("DRG_311e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_319e4] Treant Powerup (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Your Treants have +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_AND_HAND, "DRG_319e5"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsTreant());
    }
    cards.emplace("DRG_319e4", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_319e5] Tree Power! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_319e5"));
    cards.emplace("DRG_319e5", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_401d] Grizzled Power Dummy (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Dummy Hook Up for DRG_401e
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // - 1200 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DRG_401d", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_401e] Grizzled Power (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Swap Hero Powers with your opponent next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<SwapHeroPowerTask>()
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("DRG_401e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_403e] Hot Hot Hot! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (3).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_HERO_POWER, EffectList{ Effects::SetCost(3) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->removeTrigger = { TriggerType::INSPIRE, nullptr };
    }
    cards.emplace("DRG_403e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e"));
    cards.emplace("DRG_650e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e2] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e2"));
    cards.emplace("DRG_650e2", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e3] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e3"));
    cards.emplace("DRG_650e3", cardDef);
}

void DragonsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
