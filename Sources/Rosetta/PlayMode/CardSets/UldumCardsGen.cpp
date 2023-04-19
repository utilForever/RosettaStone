// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/UldumCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void UldumCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void UldumCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- HERO_POWER - DRUID
    // [ULD_131p] Ossirian Tear (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b>
    //       Your <b>Choose One</b> cards have both effects combined.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::CHOOSE_BOTH, EffectOperator::SET, 1) }));
    cards.emplace("ULD_131p", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [ULD_140p] Tome of Origination (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card. It costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_140e", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ApplyEffectTask>(
        EntityType::STACK, EffectList{ Effects::SetCost(0) }));
    cards.emplace("ULD_140p", cardDef);

    // ------------------------------------ HERO_POWER - HUNTER
    // [ULD_155p] Pharaoh's Warmask (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Give your minions +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_155e", EntityType::MINIONS));
    cards.emplace("ULD_155p", cardDef);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [ULD_291p] Heart of Vir'naal (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Your <b>Battlecries</b> trigger twice this turn.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_291pe", EntityType::PLAYER));
    cards.emplace("ULD_291p", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [ULD_326p] Ancient Blades (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 3/2 Blade with
    //       <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("ULD_326t"));
    cards.emplace("ULD_326p", cardDef);

    // ----------------------------------- HERO_POWER - PALADIN
    // [ULD_431p] Emperor Wraps (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 2/2 copy of a friendly minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonCopyTask>(
        EntityType::TARGET, false, true, SummonSide::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_431e", EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ULD_431p", cardDef);

    // -------------------------------------- HERO_POWER - MAGE
    // [ULD_433p] Ascendant Scroll (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a random Mage spell to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_HAND_NOT_FULL = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_433e", EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_HAND_NOT_FULL, 0 } };
    cards.emplace("ULD_433p", cardDef);

    // ----------------------------------- HERO_POWER - WARRIOR
    // [ULD_711p3] Anraphet's Core (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 4/3 Golem.
    //       After your hero attacks, refresh this.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("ULD_711t"));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks =
        TaskList{ std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                                   GameTag::EXHAUSTED, 0) };
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ULD_711p3", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [ULD_724p] Obelisk's Eye (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 3 Health.
    //       If you target a minion, also give it +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 3));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "ULD_724e", EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("ULD_724p", cardDef);
}

void UldumCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [ULD_131] Untapped Potential - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> End 4 turns with any unspent Mana.
    //       <b>Reward:</b> Ossirian Tear.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 4
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53499
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsUnspentMana())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_131p") };
    cardDef.property.questProgressTotal = 4;
    cards.emplace("ULD_131", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_133] Crystal Merchant - COST:2 [ATK:1/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: If you have any unspent Mana at the end of your turn,
    //       draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsUnspentMana())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("ULD_133", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_134] BEEEES!!! - COST:3 [ATK:1/HP:4]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Summon four 1/1 Bees that attack it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ULD_134t", 4, SummonSide::SPELL, true));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::STACK, EntityType::TARGET, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ULD_134", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135] Hidden Oasis - COST:6
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One</b> - Summon a 6/6 Ancient with <b>Taunt</b>;
    //       or Restore 12 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "ULD_135a", "ULD_135b" };
    cards.emplace("ULD_135", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_136] Worthy Expedition - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Choose One</b> card.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::CHOOSE_ONE));
    cards.emplace("ULD_136", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_137] Garden Gnome - COST:4 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, summon two 2/2 Treants.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::Has5MoreCostSpellInHand()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonTask>(
                  "ULD_137t", 2, SummonSide::ALTERNATE_FRIENDLY) }));
    cards.emplace("ULD_137", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_138] Anubisath Defender - COST:5 [ATK:3/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Costs (0) if you've cast a spell that
    //       costs (5) or more this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveCostEffect>(
        [](Playable* playable) { return 0; }, EffectOperator::SET,
        SelfCondition::Cast5MoreCostSpellInThisTurn()));
    cards.emplace("ULD_138", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_139] Elise the Enlightened - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       duplicate your hand.
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
        true, TaskList{ std::make_shared<CustomTask>(
                  [](Player* player, [[maybe_unused]] Entity* source,
                     [[maybe_unused]] Playable* target) {
                      for (const auto& handCard :
                           player->GetHandZone()->GetAll())
                      {
                          if (player->GetHandZone()->IsFull())
                          {
                              break;
                          }

                          Generic::Copy(player, handCard, ZoneType::HAND);
                      }
                  }) }));
    cards.emplace("ULD_139", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_273] Overflow - COST:7
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Restore 5 Health to all characters. Draw 5 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::ALL, 5));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(5));
    cards.emplace("ULD_273", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_292] Oasis Surger - COST:5 [ATK:3/HP:3]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Choose One -</b> Gain +2/+2;
    //       or Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "ULD_292a", "ULD_292b" };
    cards.emplace("ULD_292", cardDef);
}

void UldumCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [ULD_134t] Bee (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_134t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135a] Befriend the Ancient (*) - COST:0
    // - Set: Uldum
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a 6/6 Ancient with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ULD_135at", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ULD_135a", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_135at] Vir'naal Ancient (*) - COST:6 [ATK:6/HP:6]
    // - Set: Uldum
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_135at", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135b] Drink the Water (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Restore 12 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 12));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("ULD_135b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ULD_137t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_137t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_292a] Focused Burst (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Gain +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_292ae", EntityType::SOURCE));
    cards.emplace("ULD_292a", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ULD_292ae] Focused (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_292ae"));
    cards.emplace("ULD_292ae", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ULD_292b] Divide and Conquer (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Summon a copy of this minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::SOURCE));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 2 } };
    cards.emplace("ULD_292b", cardDef);
}

void UldumCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [ULD_151] Ramkahen Wildtamer - COST:3 [ATK:4/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a random Beast in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::CopyCardInHand(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::BEAST)) }));
    cards.emplace("ULD_151", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_152] Pressure Plate - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFieldNotEmpty())
    };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
                  std::make_shared<DestroyTask>(EntityType::STACK) });
    cards.emplace("ULD_152", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ULD_154] Hyena Alpha - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsControllingSecret()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<SummonTask>("ULD_154t", SummonSide::LEFT),
            std::make_shared<SummonTask>("ULD_154t", SummonSide::RIGHT) }));
    cards.emplace("ULD_154", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_155] Unseal the Vault - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Summon 20 minions.
    //       <b>Reward:</b> Ramkahen Roar.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 20
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53925
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_155p") };
    cardDef.property.questProgressTotal = 20;
    cards.emplace("ULD_155", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156] Dinotamer Brann - COST:7 [ATK:2/HP:4]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       summon King Krush.
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
        true, TaskList{ std::make_shared<SummonTask>("ULD_156t3",
                                                     SummonSide::RIGHT) }));
    cards.emplace("ULD_156", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ULD_212] Wild Bloodstinger - COST:6 [ATK:6/HP:9]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a minion from
    //       your opponent's hand. Attack it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cardDef.power.AddPowerTask(std::make_shared<AttackTask>(
        EntityType::SOURCE, EntityType::STACK, true));
    cards.emplace("ULD_212", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ULD_410] Scarlet Webweaver - COST:6 [ATK:5/HP:5]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of a random Beast
    //       in your hand by (5).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_410e", EntityType::STACK));
    cards.emplace("ULD_410", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_429] Hunter's Pack - COST:3
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a random Hunter Beast, <b>Secret</b>,
    //       and weapon to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::HUNTER, Race::BEAST));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::HUNTER,
                                         GameTags{ { GameTag::SECRET, 1 } }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::WEAPON, CardClass::HUNTER));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("ULD_429", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [ULD_430] Desert Spear - COST:3 [ATK:1/HP:0]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       summon a 1/1 Locust with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "ULD_430t", SummonSide::SPELL) };
    cards.emplace("ULD_430", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_713] Swarm of Locusts - COST:6
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon seven 1/1 Locusts with <b>Rush</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("ULD_430t", 7));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ULD_713", cardDef);
}

void UldumCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [ULD_154t] Hyena (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_154t", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ULD_155e] Roar! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_155e"));
    cards.emplace("ULD_155e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156t3] King Krush (*) - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Faction: Neutral, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_156t3", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ULD_410e] Weaved (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (5) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(5)));
    cards.emplace("ULD_410e", cardDef);
}

void UldumCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [ULD_216] Puzzle Box of Yogg-Saron - COST:10
    // - Faction: Neutral, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Cast 10 random spells <i>(targets chosen randomly).</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<CastRandomSpellTask>() }, 10, true));
    cards.emplace("ULD_216", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_236] Tortollan Pilgrim - COST:8 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: <b>Discover</b> a spell
    //       in your deck and cast it with random targets.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::TORTOLLAN_PILGRIM));
    cards.emplace("ULD_236", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_238] Reno the Relicologist - COST:6 [ATK:4/HP:6]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       deal 10 damage randomly split among all enemy minions.
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
        TaskList{ std::make_shared<EnqueueTask>(
            TaskList{
                std::make_shared<FilterStackTask>(
                    SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsNotDead()) }),
                std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
                std::make_shared<DamageTask>(EntityType::STACK, 1) },
            10) }));
    cards.emplace("ULD_238", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [ULD_239] Flame Ward - COST:3
    // - Faction: Neutral, Set: Uldum, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After a minion attacks your hero,
    //       deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACKED));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 3, true) });
    cards.emplace("ULD_239", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_240] Arcane Flakmage - COST:2 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a <b>Secret</b>,
    //       deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSecret())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2),
    };
    cards.emplace("ULD_240", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_293] Cloud Prince - COST:5 [ATK:4/HP:4]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       deal 6 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 6));
    cardDef.property.playReqs = PlayReqs{
        { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS, 1 }
    };
    cards.emplace("ULD_293", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_329] Dune Sculptor - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, add a random Mage
    //       minion to your hand.
    // --------------------------------------------------------
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::MAGE),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("ULD_329", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [ULD_433] Raid the Sky Temple - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Cast 10 spells.
    //       <b>Reward: </b>Ascendant Scroll.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 10
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53946
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_433p") };
    cardDef.property.questProgressTotal = 10;
    cards.emplace("ULD_433", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [ULD_435] Naga Sand Witch - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change the Cost of spells
    //       in your hand to (5).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_435e", EntityType::STACK));
    cards.emplace("ULD_435", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [ULD_726] Ancient Mysteries - COST:2
    // - Set: Uldum, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw a <b>Secret</b> from your deck. It costs (0).
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1,
        SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsSecret()) },
        true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_726e", EntityType::STACK));
    cards.emplace("ULD_726", cardDef);
}

void UldumCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [ULD_435e] Sandwitched (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (5).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(5)));
    cards.emplace("ULD_435e", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [ULD_726e] Translated (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("ULD_726e", cardDef);
}

void UldumCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_143] Pharaoh's Blessing - COST:6
    // - Faction: Neutral, Set: Uldum, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +4/+4, <b>Divine Shield</b>,
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_143e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_143", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_145] Brazen Zealot - COST:1 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a minion, gain +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks =
        TaskList{ std::make_shared<AddEnchantmentTask>("ULD_145e",
                                                       EntityType::SOURCE) };
    cards.emplace("ULD_145", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_207] Ancestral Guardian - COST:4 [ATK:4/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_207", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_217] Micro Mummy - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Reborn</b> At the end of your turn, give
    //       another random friendly minion +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("ULD_217e", EntityType::STACK)
    };
    cards.emplace("ULD_217", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_431] Making Mummies - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play 5 <b>Reborn</b> minions.
    //       <b>Reward:</b> Emperor Wraps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53908
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasReborn())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_431p") };
    cardDef.property.questProgressTotal = 5;
    cards.emplace("ULD_431", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_438] Salhet's Pride - COST:3 [ATK:3/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw two 1-Health minions
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsCost(1)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 2));
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawStackTask>());
    cards.emplace("ULD_438", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_439] Sandwasp Queen - COST:2 [ATK:3/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 2/1 Sandwasps to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "ULD_439t", 2));
    cards.emplace("ULD_439", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_500] Sir Finley of the Sands - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       <b>Discover</b> an upgraded Hero Power.
    // --------------------------------------------------------
    // Entourage: HERO_01bp2, HERO_02bp2, HERO_03bp2, HERO_04bp2,
    //            HERO_05bp2, HERO_06bp2, HERO_07bp2, HERO_08bp2,
    //            HERO_09bp2, HERO_10bp2
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
                                SelfCondition::IsNoDuplicateInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(
                  DiscoverType::SIR_FINLEY_OF_THE_SANDS) }));
    cards.emplace("ULD_500", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_716] Tip the Scales - COST:8
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon 7 Murlocs from your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 7));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("ULD_716", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_728] Subdue - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_728e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_728", cardDef);
}

void UldumCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_143e] Pharaoh's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +4/+4, <b>Divine Shield</b>, and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_143e"));
    cards.emplace("ULD_143e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_145e] Zeal (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("ULD_145e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_431e] Emperor Wrapped (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetAttackHealth(2)));
    cards.emplace("ULD_431e", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ULD_439t] Sandwasp (*) - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_439t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_716e2] Watched (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------
}

void UldumCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [ULD_262] High Priest Amet - COST:4 [ATK:2/HP:7]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you summon a minion,
    //       set its Health equal to this minion's.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE, GameTag::HEALTH),
        std::make_shared<AddEnchantmentTask>("ULD_262e", EntityType::TARGET,
                                             true)
    };
    cards.emplace("ULD_262", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_265] Embalming Ritual - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion <b>Reborn</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::REBORN, 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_265", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ULD_266] Grandmummy - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> <b>Deathrattle:</b> Give a random
    //       friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("ULD_266e", EntityType::STACK));
    cards.emplace("ULD_266", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ULD_268] Psychopomp - COST:4 [ATK:3/HP:1]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random friendly minion
    //       that died this game. Give it <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::REBORN, 1));
    cards.emplace("ULD_268", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ULD_269] Wretched Reclaimer - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion,
    //       then return it to life with full Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_269", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ULD_270] Sandhoof Waterbearer - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, restore 5 Health
    //       to a damaged friendly character.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::FRIENDS),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<HealTask>(EntityType::STACK, 5)
    };
    cards.emplace("ULD_270", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_272] Holy Ripple - COST:2
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemies. Restore 1 Health
    //       to all friendly characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 1));
    cards.emplace("ULD_272", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_714] Penance - COST:2
    // - Set: Uldum, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> Deal 3 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_714", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_718] Plague of Death - COST:9
    // - Set: Uldum, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Silence</b> and destroy all minions.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS));
    cards.emplace("ULD_718", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_724] Activate the Obelisk - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Restore 15 Health.
    //       <b>Reward:</b> Obelisk's Eye.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 15
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54750
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_724p", ProgressType::RESTORE_HEALTH) };
    cardDef.property.questProgressTotal = 15;
    cards.emplace("ULD_724", cardDef);
}

void UldumCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_262e] Amet's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Health changed.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::SetHealthScriptTag));
    cards.emplace("ULD_262e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_266e] Grandmummy's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_266e"));
    cards.emplace("ULD_266e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_724e] Obelisk's Gaze (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Effects::AttackHealthN(3)));
    cards.emplace("ULD_724e", cardDef);
}

void UldumCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [ULD_186] Pharaoh Cat - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random <b>Reborn</b> minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::INVALID,
                                         GameTags{ { GameTag::REBORN, 1 } }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("ULD_186", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [ULD_231] Whirlkick Master - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a <b>Combo</b> card,
    //       add a random <b>Combo</b> card to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsComboCard())
    };
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::INVALID, CardClass::INVALID,
                                         GameTags{ { GameTag::COMBO, 1 } }),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("ULD_231", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [ULD_280] Sahket Sapper - COST:4 [ATK:4/HP:4]
    // - Race: Pirate, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random enemy minion
    //       to your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ReturnHandTask>(EntityType::STACK));
    cards.emplace("ULD_280", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_285] Hooked Scimitar - COST:3 [ATK:2/HP:0]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(std::make_shared<AddEnchantmentTask>(
        "ULD_285e", EntityType::SOURCE, true));
    cards.emplace("ULD_285", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_286] Shadow of Death - COST:4
    // - Set: Uldum, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Choose a minion. Shuffle 3 'Shadows' into your deck
    //       that summon a copy when drawn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, const Playable* target) {
            if (!target)
            {
                return;
            }

            std::map<GameTag, int> tags;
            tags.emplace(GameTag::TAG_SCRIPT_DATA_NUM_1, target->card->dbfID);

            for (int i = 0; i < 3; i++)
            {
                Playable* shadow =
                    Entity::GetFromCard(player, Cards::FindCardByID("ULD_286t"),
                                        tags, player->GetDeckZone());
                Generic::ShuffleIntoDeck(player, source, shadow);
            }
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_286", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [ULD_288] Anka, the Buried - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change each <b>Deathrattle</b>
    //       minion in your hand into a 1/1 that costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::HasDeathrattle()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_288e", EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<ApplyEffectTask>(
        EntityType::STACK, EffectList{ Effects::SetCost(1) }));
    cards.emplace("ULD_288", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_326] Bazaar Burglary - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Add 4 cards from other classes to your hand.
    //       <b>Reward: </b>Ancient Blades.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 4
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54312
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ADD_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsAnotherClassCard())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_326p") };
    cardDef.property.questProgressTotal = 4;
    cards.emplace("ULD_326", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [ULD_327] Bazaar Mugger - COST:5 [ATK:3/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Battlecry:</b> Add a random minion
    //       from another class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::ANOTHER_CLASS));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("ULD_327", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_328] Clever Disguise - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Add 2 random spells from another class to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(CardType::SPELL,
                                                   CardClass::ANOTHER_CLASS),
                  std::make_shared<AddStackToTask>(EntityType::HAND) },
        2));
    cards.emplace("ULD_328", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_715] Plague of Madness - COST:1
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Each player equips a 2/2 Knife with <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - 858 = 2451
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("ULD_715t"));
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("ULD_715t", true));
    cards.emplace("ULD_715", cardDef);
}

void UldumCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ULD_285e] Polished (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_285e"));
    cards.emplace("ULD_285e", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_286t] Shadow (*) - COST:4
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon a {0}.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<CustomTask>([](Player* player, const Entity* source,
                                        [[maybe_unused]] Playable* target) {
            const int dbfID =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1);
            Playable* minion =
                Entity::GetFromCard(player, Cards::FindCardByDbfID(dbfID));
            Generic::Summon(dynamic_cast<Minion*>(minion), -1, player);
        }));
    cardDef.power.AddPowerTask(
        std::make_shared<CustomTask>([](Player* player, const Entity* source,
                                        [[maybe_unused]] Playable* target) {
            const int dbfID =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1);
            Playable* minion =
                Entity::GetFromCard(player, Cards::FindCardByDbfID(dbfID));
            Generic::Summon(dynamic_cast<Minion*>(minion), -1, player);
        }));
    cards.emplace("ULD_286t", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ULD_288e] Buried (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Anka, the Buried made this 1/1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_288e"));
    cards.emplace("ULD_288e", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_326t] Mirage Blade (*) - COST:2 [ATK:3/HP:0]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DS1_188e", EntityType::HERO) };
    cards.emplace("ULD_326t", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_715t] Plagued Knife (*) - COST:1 [ATK:2/HP:0]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_715t", cardDef);
}

void UldumCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_158] Sandstorm Elemental - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1));
    cards.emplace("ULD_158", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_169] Mogu Fleshshaper - COST:9 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Costs (1) less for each minion
    //       on the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetFieldZone()->GetCount() +
                   playable->player->opponent->GetFieldZone()->GetCount();
        }));
    cards.emplace("ULD_169", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_170] Weaponized Wasp - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Lackey</b>,
    //       deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsControllingLackey()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 3) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("ULD_170", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_171] Totemic Surge - COST:0
    // - Set: Uldum, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your Totems +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::TOTEM)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_171e", EntityType::STACK));
    cards.emplace("ULD_171", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_172] Plague of Murlocs - COST:3
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Transform all minions into random Murlocs.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TransformMinionTask>(
        EntityType::ALL_MINIONS, Race::MURLOC));
    cards.emplace("ULD_172", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_173] Vessina - COST:4 [ATK:2/HP:6]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: While you're <b>Overloaded</b>,
    //       your other minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "ULD_173e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsOverloaded());
        aura->restless = true;
    }
    cards.emplace("ULD_173", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_181] Earthquake - COST:7
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions,
    //       then deal 2 damage to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConsecutiveDamageTask>(
        EntityType::ALL_MINIONS, std::vector<int>{ 5, 2 }, true));
    cards.emplace("ULD_181", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_276] EVIL Totem - COST:2 [ATK:0/HP:2]
    // - Race: Totem, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddLackeyTask>(1) };
    cards.emplace("ULD_276", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_291] Corrupt the Waters - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play 6 <b>Battlecry</b> cards.
    //       <b>Reward:</b> Heart of Vir'naal.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 6
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54370
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsBattlecryCard())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_291p") };
    cardDef.property.questProgressTotal = 6;
    cards.emplace("ULD_291", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [ULD_413] Splitting Axe - COST:4 [ATK:3/HP:0]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon copies of your Totems.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::TOTEM)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::STACK));
    cards.emplace("ULD_413", cardDef);
}

void UldumCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_171e] Big Surge (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_171e"));
    cards.emplace("ULD_171e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_173e] Vessina's Devotion (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Vessina is granting this minion +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(2)));
    cards.emplace("ULD_173e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_433e] Cheat Sheet (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("ULD_433e", cardDef);
}

void UldumCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_140] Supreme Archaeology - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Draw 20 cards.
    //       <b>Reward:</b> Tome of Origination.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 20
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53740
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DRAW_CARD));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<ChangeHeroPowerTask>("ULD_140p") }) };
    cardDef.property.questProgressTotal = 20;
    cards.emplace("ULD_140", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_160] Sinister Deal - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Lackey</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::LACKEY));
    cards.emplace("ULD_160", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_161] Neferset Thrasher - COST:3 [ATK:4/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this attacks, deal 3 damage to your hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::HERO, 3) };
    cards.emplace("ULD_161", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_162] EVIL Recruiter - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly <b>Lackey</b>
    //       to summon a 5/5 Demon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 1359 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_LACKEY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::ZONE_POSITION));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ULD_162t", SummonSide::NUMBER));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_LACKEY_TARGET, 0 } };
    cards.emplace("ULD_162", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_163] Expired Merchant - COST:2 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard your highest Cost card.
    //       <b>Deathrattle:</b> Add 2 copies of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscardTask>(1, DiscardType::HIGHEST_COST, true));
    cardDef.power.AddDeathrattleTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_ENT_1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<CopyTask>(EntityType::STACK_NUM0, ZoneType::HAND, 2));
    cards.emplace("ULD_163", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_165] Riftcleaver - COST:6 [ATK:7/HP:5]
    // - Race: Demon, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       Your hero takes damage equal to its Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::HEALTH));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::HERO));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_165", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_167] Diseased Vulture - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero takes damage on your turn,
    //       summon a random 3-Cost minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMyTurn())
    };
    cardDef.power.GetTrigger()->tasks =
        TaskList{ std::make_shared<RandomMinionTask>(
                      TagValues{ { GameTag::COST, 3, RelaSign::EQ } }),
                  std::make_shared<SummonStackTask>() };
    cards.emplace("ULD_167", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_168] Dark Pharaoh Tekahn - COST:5 [ATK:4/HP:4]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_168e", EntityType::PLAYER));
    cards.emplace("ULD_168", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_324] Impbalming - COST:4
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Destroy a minion. Shuffle 3 Worthless Imps into your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "ULD_324t", 3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_324", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_717] Plague of Flames - COST:1
    // - Set: Uldum, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Destroy all your minions.
    //       For each one, destroy a random enemy minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](const Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            player->game->taskStack.num[0] = player->GetFieldZone()->GetCount();
        }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
                  std::make_shared<DestroyTask>(EntityType::STACK) }));
    cards.emplace("ULD_717", cardDef);
}

void UldumCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_140e] Origination (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_140e"));
    cards.emplace("ULD_140e", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_162t] EVIL Demon (*) - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_162t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_163e] Expired Goods (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Discarded {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_AND_HAND, "ULD_168e3"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsLackey());
    }
    cards.emplace("ULD_168e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e2] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e3] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_168e3"));
    cards.emplace("ULD_168e3", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ULD_324t] Worthless Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_324t", cardDef);
}

void UldumCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [ULD_195] Frightened Flunky - COST:2 [ATK:2/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a <b>Taunt</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::TAUNT_MINION));
    cards.emplace("ULD_195", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [ULD_206] Restless Mummy - COST:4 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_206", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [ULD_253] Tomb Warden - COST:8 [ATK:3/HP:6]
    // - Race: Mechanical, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::SOURCE));
    cards.emplace("ULD_253", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_256] Into the Fray - COST:1
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give all <b>Taunt</b> minions in your hand +2/+2.
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
        std::make_shared<AddEnchantmentTask>("ULD_256e", EntityType::STACK));
    cards.emplace("ULD_256", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [ULD_258] Armagedillo - COST:6 [ATK:4/HP:7]
    // - Race: Beast, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the end of your turn,
    //       give all <b>Taunt</b> minions in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
            std::make_shared<SelfCondition>(SelfCondition::HasTaunt()) }),
        std::make_shared<AddEnchantmentTask>("ULD_258e", EntityType::STACK)
    };
    cards.emplace("ULD_258", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_707] Plague of Wrath - COST:5
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy all damaged minions.
    // --------------------------------------------------------
    // GameTag:
    // - 858 = 41425
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("ULD_707", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [ULD_708] Livewire Lance - COST:3 [ATK:2/HP:0]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your Hero attacks,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddLackeyTask>(1) };
    cards.emplace("ULD_708", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [ULD_709] Armored Goon - COST:6 [ATK:6/HP:7]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, gain 5 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(5) };
    cards.emplace("ULD_709", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_711] Hack the System - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Attack 5 times with your hero.
    //       <b>Reward:</b> Anraphet's Core.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54416
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "ULD_711p3") };
    cardDef.property.questProgressTotal = 5;
    cards.emplace("ULD_711", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [ULD_720] Bloodsworn Mercenary - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Choose a damaged friendly minion.
    //       Summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonCopyTask>(
        EntityType::TARGET, false, false, SummonSide::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_DAMAGED_TARGET, 0 } };
    cards.emplace("ULD_720", cardDef);
}

void UldumCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [ULD_711t] Stone Golem (*) - COST:3 [ATK:4/HP:3]
    // - Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_711t", cardDef);
}

void UldumCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_003] Zephrys the Great - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       wish for the perfect card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_157] Questing Explorer - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsControllingQuest()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cards.emplace("ULD_157", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_174] Serpent Egg - COST:2 [ATK:0/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/4 Sea Serpent.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("ULD_174t", SummonSide::DEATHRATTLE));
    cards.emplace("ULD_174", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_177] Octosari - COST:8 [ATK:8/HP:8]
    // - Race: Beast, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw 8 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(8));
    cards.emplace("ULD_177", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_178] Siamat - COST:7 [ATK:6/HP:6]
    // - Race: Elemental, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 2 of <b>Rush</b>,
    //       <b>Taunt</b>, <b>Divine Shield</b>, or
    //       <b>Windfury</b> <i>(your choice).</i>
    // --------------------------------------------------------
    // Entourage: ULD_178a2, ULD_178a, ULD_178a3, ULD_178a4
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SIAMAT, 4, 2));
    cardDef.power.AddAfterChooseTask(std::make_shared<CustomTask>(
        []([[maybe_unused]] Player* player, Entity* source,
           [[maybe_unused]] Playable* target) {
            const int dbfID1 =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1);
            Generic::AddEnchantment(Cards::FindCardByDbfID(dbfID1),
                                    dynamic_cast<Playable*>(source), source);

            const int dbfID2 =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2);
            Generic::AddEnchantment(Cards::FindCardByDbfID(dbfID2),
                                    dynamic_cast<Playable*>(source), source);
        }));
    cards.emplace("ULD_178", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_179] Phalanx Commander - COST:5 [ATK:4/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Your <b>Taunt</b> minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - TECH_LEVEL = 3
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::FIELD, "ULD_179e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::HasTaunt());
    }
    cards.emplace("ULD_179", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_180] Sunstruck Henchman - COST:4 [ATK:6/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       this has a 50% chance to fall asleep.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->percentage = 0.5f;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::EXHAUSTED, 1) };
    cards.emplace("ULD_180", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_182] Spitting Camel - COST:2 [ATK:2/HP:4]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 1 damage
    //       to another random friendly minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1)
    };
    cards.emplace("ULD_182", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_183] Anubisath Warbringer - COST:9 [ATK:9/HP:6]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all minions in your hand +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("ULD_183e", EntityType::STACK));
    cards.emplace("ULD_183", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_184] Kobold Sandtrooper - COST:2 [ATK:2/HP:1]
    // - Faction: Alliance, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cards.emplace("ULD_184", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_185] Temple Berserker - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b> Has +2 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::SELF, "ULD_185e"));
    cards.emplace("ULD_185", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_188] Golden Scarab - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Battlecry:</b> Discover</b> a 4-Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::FOUR_COST_CARD));
    cards.emplace("ULD_188", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_189] Faceless Lurker - COST:5 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Double this minion's Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::SOURCE, GameTag::HEALTH));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::SOURCE, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "ULD_189e", EntityType::SOURCE, true));
    cards.emplace("ULD_189", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_190] Pit Crocolisk - COST:8 [ATK:5/HP:6]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("ULD_190", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_191] Beaming Sidekick - COST:1 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_191e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_191", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_193] Living Monument - COST:10 [ATK:10/HP:10]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_193", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_194] Wasteland Scorpid - COST:7 [ATK:3/HP:9]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_194", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_196] Neferset Ritualist - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore adjacent minions
    //       to full Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<HealFullTask>(EntityType::STACK));
    cards.emplace("ULD_196", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_197] Quicksand Elemental - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all enemy minions -2 Attack
    //       this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "ULD_197e", EntityType::ENEMY_MINIONS));
    cards.emplace("ULD_197", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_198] Conjured Mirage - COST:4 [ATK:3/HP:10]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the start of your turn,
    //       shuffle this minion into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<MoveToDeckTask>(
        EntityType::SOURCE) };
    cards.emplace("ULD_198", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_205] Candletaker - COST:3 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_205", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_208] Khartut Defender - COST:6 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Reborn</b> <b>Deathrattle:</b>
    //       Restore 3 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::HERO, 3));
    cards.emplace("ULD_208", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_209] Vulpera Scoundrel - COST:3 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: <b>Discover</b> a spell or
    //       pick a mystery choice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::VULPERA_SCOUNDREL, 4));
    cards.emplace("ULD_209", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_214] Generous Mummy - COST:3 [ATK:5/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> Your opponent's cards cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_HAND, EffectList{ Effects::ReduceCost(1) }));
    cards.emplace("ULD_214", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_215] Wrapped Golem - COST:7 [ATK:7/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> At the end of your turn,
    //       summon a 1/1 Scarab with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "ULD_215t") };
    cards.emplace("ULD_215", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_229] Mischief Maker - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the top card of your deck
    //       with your opponent's.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SwapTopCardTask>());
    cards.emplace("ULD_229", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_250] Infested Goblin - COST:3 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Add two 1/1 Scarabs
    //       with <b>Taunt</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "ULD_215t", 2));
    cards.emplace("ULD_250", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_271] Injured Tol'vir - COST:2 [ATK:2/HP:6]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 3 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::SOURCE, 3));
    cards.emplace("ULD_271", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_274] Wasteland Assassin - COST:5 [ATK:4/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_274", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_275] Bone Wraith - COST:4 [ATK:2/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_275", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_282] Jar Dealer - COST:1 [ATK:1/HP:1]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random 1-Cost minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 1, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("ULD_282", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_289] Fishflinger - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Murloc
    //       to each player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::MURLOC));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::MURLOC, Rarity::INVALID,
        GameTags{}, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("ULD_289", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_290] History Buff - COST:3 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a minion,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<AddEnchantmentTask>("ULD_290e", EntityType::STACK)
    };
    cards.emplace("ULD_290", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_304] King Phaoris - COST:10 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each spell in your hand,
    //       summon a random minion of the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            std::vector<int> spellCosts;
            for (const auto& playable : player->GetHandZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::SPELL)
                {
                    spellCosts.emplace_back(playable->GetCost());
                }
            }

            const auto& task1 =
                std::make_shared<RandomMinionNumberTask>(GameTag::COST);
            const auto& task2 = std::make_shared<SummonStackTask>();

            for (const auto& cost : spellCosts)
            {
                player->game->taskStack.num[0] = cost;

                task1->SetPlayer(player);
                task1->SetSource(source);
                task1->SetTarget(target);
                task1->Run();

                task2->SetPlayer(player);
                task2->SetSource(source);
                task2->SetTarget(target);
                task2->Run();
            }
        }));
    cards.emplace("ULD_304", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_309] Dwarven Archaeologist - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you <b>Discover</b> a card,
    //       reduce its cost by (1).
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDiscoverCard())
    };
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "ULD_309e", EntityType::STACK_NUM0) };
    cards.emplace("ULD_309", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_450] Vilefiend - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_450", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_702] Mortuary Machine - COST:5 [ATK:8/HP:8]
    // - Race: Mechanical, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your opponent plays a minion,
    //       give it <b>Reborn</b>.
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::REBORN, 1) };
    cards.emplace("ULD_702", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_703] Desert Obelisk - COST:5 [ATK:0/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: If you control 3 of these at the end of your turn,
    //       deal 5 damage to a random enemy.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::ControlThisCard(3))
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 5)
    };
    cards.emplace("ULD_703", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_705] Mogu Cultist - COST:1 [ATK:1/HP:1]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your board is full of Mogu Cultists,
    //       sacrifice them all and summon Highkeeper Ra.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::ControlThisCard(7)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DestroyTask>(EntityType::MINIONS, true),
                  std::make_shared<SummonTask>("ULD_705t") }));
    cards.emplace("ULD_705", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_706] Blatant Decoy - COST:6 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Each player summons
    //       the lowest Cost minion from their hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsLowestCostMinion()) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_HAND));
    cardDef.power.AddDeathrattleTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsLowestCostMinion()) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("ULD_706", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_712] Bug Collector - COST:2 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Locust with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("ULD_430t"));
    cards.emplace("ULD_712", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_719] Desert Hare - COST:3 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Desert Hares.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ULD_719", SummonSide::LEFT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ULD_719", SummonSide::RIGHT));
    cards.emplace("ULD_719", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_721] Colossus of the Moon - COST:10 [ATK:10/HP:10]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_721", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_723] Murmy - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_723", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_727] Body Wrapper - COST:4 [ATK:4/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a friendly minion
    //       that died this game. Shuffle it into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::BODY_WRAPPER));
    cards.emplace("ULD_727", cardDef);
}

void UldumCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_174t] Sea Serpent (*) - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_174t", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a] Siamat's Wind (*) - COST:0
    // - Faction: Neutral, Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::Windfury));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_178a", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a2] Siamat's Shield (*) - COST:0
    // - Faction: Neutral, Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::DivineShield));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_178a2", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a3] Siamat's Heart (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::Taunt));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("ULD_178a3", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a4] Siamat's Speed (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::Rush));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ULD_178a4", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_179e] Commanded (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Phalanx Commander is granting this +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_179e"));
    cards.emplace("ULD_179e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_183e] Anubisath Power (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_183e"));
    cards.emplace("ULD_183e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_185e] Enraged (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_185e"));
    cards.emplace("ULD_185e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_189e] Bravery (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Doubled Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddHealthScriptTag));
    cards.emplace("ULD_189e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_191e] Assisting! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_191e"));
    cards.emplace("ULD_191e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_197e] Stuck! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: -2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_197e"));
    cards.emplace("ULD_197e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_209t] Mystery Choice! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Add a random spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_214e] Charity (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_215t] Scarab (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_215t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_217e] Microwrapped (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Attack increased.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("ULD_217e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_256e] Frayed (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2/+2 from Into the Fray.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_256e"));
    cards.emplace("ULD_256e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_258e] Tough (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats from Armagedillo.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(2)));
    cards.emplace("ULD_258e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_290e] Erudite (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats from History Buff.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(1)));
    cards.emplace("ULD_290e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_291pe] Heart of Vir'naal (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Battlecries</b> trigger twice this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::EXTRA_BATTLECRIES_BASE,
                                             EffectOperator::SET, 1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->removeTrigger = { TriggerType::TURN_END, nullptr };
    }
    cards.emplace("ULD_291pe", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_309e] Archaelogical Study (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("ULD_309e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_430t] Locust (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ULD_430t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_616] Titanic Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Health
    //       and <b>Taunt</b>.
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
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_616e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("ULD_616", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_616e] Hardened (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ULD_616e"));
    cards.emplace("ULD_616e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_705t] Highkeeper Ra (*) - COST:10 [ATK:20/HP:20]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 20 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 20) };
    cards.emplace("ULD_705t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_728e] Subdued (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetAttackHealth(1)));
    cards.emplace("ULD_728e", cardDef);
}

void UldumCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
