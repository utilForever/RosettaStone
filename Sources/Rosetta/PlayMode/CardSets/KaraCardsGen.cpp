// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/KaraCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void KaraCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [KAR_065] Menagerie Warden - COST:5 [ATK:4/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Beast.
    //       Summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 20 } };
    cards.emplace("KAR_065", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [KAR_075] Moonglade Portal - COST:6
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: Restore 6 Health. Summon a random 6-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 6));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 6, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("KAR_075", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [KAR_300] Enchanted Raven - COST:1 [ATK:2/HP:2]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_300", cardDef);
}

void KaraCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [KAR_004] Cat Trick - COST:2
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       summon a 4/2 Panther with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("KAR_004a", SummonSide::SPELL) });
    cards.emplace("KAR_004", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [KAR_005] Kindly Grandmother - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/2 Big Bad Wolf.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("KAR_005a", SummonSide::DEATHRATTLE));
    cards.emplace("KAR_005", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [KAR_006] Cloaked Huntress - COST:3 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Your <b>Secrets</b> cost (0).
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSecret());
    }
    cards.emplace("KAR_006", cardDef);
}

void KaraCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [KAR_004a] Cat in a Hat (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: Kara
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_004a", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [KAR_005a] Big Bad Wolf (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_005a", cardDef);
}

void KaraCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [KAR_009] Babbling Book - COST:1 [ATK:1/HP:1]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("KAR_009", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [KAR_076] Firelands Portal - COST:7
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 5 damage. Summon a random 5-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 5, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("KAR_076", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [KAR_092] Medivh's Valet - COST:2 [ATK:2/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       deal 3 damage.
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
        std::make_shared<DamageTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs = PlayReqs{
        { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS, 1 }
    };
    cards.emplace("KAR_092", cardDef);
}

void KaraCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [KAR_010] Nightbane Templar - COST:3 [ATK:2/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       summon two 1/1 Whelps.
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
        TaskList{
            std::make_shared<SummonTask>("KAR_010a", SummonSide::LEFT),
            std::make_shared<SummonTask>("KAR_010a", SummonSide::RIGHT) }));
    cards.emplace("KAR_010", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [KAR_057] Ivory Knight - COST:6 [ATK:4/HP:4]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    //       Restore Health to your hero equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::COST));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<HealNumberTask>(EntityType::HERO));
    cards.emplace("KAR_057", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [KAR_077] Silvermoon Portal - COST:4
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("KAR_077e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 2, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("KAR_077", cardDef);
}

void KaraCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [KAR_010a] Whelp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Dragon, Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_010a", cardDef);
}

void KaraCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [KAR_013] Purify - COST:2
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a friendly minion. Draw a card.
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
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("KAR_013", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [KAR_035] Priest of the Feast - COST:4 [ATK:3/HP:6]
    // - Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       restore 3 Health to your hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::HERO, 3) };
    cards.emplace("KAR_035", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [KAR_204] Onyx Bishop - COST:5 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a friendly minion
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::PLAY, 1));
    cards.emplace("KAR_204", cardDef);
}

void KaraCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [KAR_069] Swashburglar - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random card
    //       from another class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(EntityType::ENEMY_HERO));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("KAR_069", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [KAR_070] Ethereal Peddler - COST:5 [ATK:5/HP:6]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding any non-Rogue
    //       class cards, reduce their Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsHoldingAnyNonClassCard(CardClass::ROGUE)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<IncludeTask>(EntityType::HAND),
                  std::make_shared<FilterStackTask>(
                      SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsNotCardClass(CardClass::ROGUE)) }),
                  std::make_shared<AddAuraEffectTask>(Effects::ReduceCost(2),
                                                      EntityType::STACK) }));
    cards.emplace("KAR_070", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [KAR_094] Deadly Fork - COST:3 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a 3/2 weapon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "KAR_094a"));
    cards.emplace("KAR_094", cardDef);
}

void KaraCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- WEAPON - ROGUE
    // [KAR_094a] Sharp Fork (*) - COST:3 [ATK:3/HP:0]
    // - Set: Kara
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_094a", cardDef);
}

void KaraCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [KAR_021] Wicked Witchdoctor - COST:4 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a random basic Totem.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::SummonRandomBasicTotem()
    };
    cards.emplace("KAR_021", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [KAR_063] Spirit Claws - COST:2 [ATK:1/HP:0]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have <b>Spell Damage</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            if (playable->player->GetCurrentSpellPower() > 0)
            {
                return 2;
            }

            return 0;
        }));
    cards.emplace("KAR_063", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [KAR_073] Maelstrom Portal - COST:2
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    //       Summon a random 1-Cost minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 1, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("KAR_073", cardDef);
}

void KaraCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [KAR_025] Kara Kazham! - COST:5
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon a 1/1 Candle, 2/2 Broom, and 3/3 Teapot.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("KAR_025a", SummonSide::SPELL));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("KAR_025b", SummonSide::SPELL));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("KAR_025c", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("KAR_025", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [KAR_089] Malchezaar's Imp - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you discard a card, draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DISCARD));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("KAR_089", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [KAR_205] Silverware Golem - COST:3 [ATK:3/HP:3]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you discard this minion, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DISCARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "KAR_205") };
    cards.emplace("KAR_205", cardDef);
}

void KaraCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [KAR_025a] Candle (*) - COST:1 [ATK:1/HP:1]
    // - Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_025a", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [KAR_025b] Broom (*) - COST:2 [ATK:2/HP:2]
    // - Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_025b", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [KAR_025c] Teapot (*) - COST:3 [ATK:3/HP:3]
    // - Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_025c", cardDef);
}

void KaraCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [KAR_026] Protect the King! - COST:3
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: For each enemy minion,
    //       summon a 1/1 Pawn with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<SummonTask>("KAR_026t", SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 0 } };
    cards.emplace("KAR_026", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [KAR_028] Fool's Bane - COST:5 [ATK:3/HP:0]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Unlimited attacks each turn. Can't attack heroes.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HERO,
        EffectList{ std::make_shared<Effect>(GameTag::CANNOT_ATTACK_HEROES,
                                             EffectOperator::SET, 1) }));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::HERO, GameTag::EXHAUSTED, 0) };
    cards.emplace("KAR_028", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [KAR_091] Ironforge Portal - COST:5
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 4 Armor. Summon a random 4-Cost minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 4, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("KAR_091", cardDef);
}

void KaraCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [KAR_026t] Pawn (*) - COST:1 [ATK:1/HP:1]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_026t", cardDef);
}

void KaraCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_011] Pompous Thespian - COST:2 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_011", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_029] Runic Egg - COST:1 [ATK:0/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("KAR_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_030a] Pantry Spider - COST:3 [ATK:1/HP:3]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/3 Spider.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("KAR_030"));
    cards.emplace("KAR_030a", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_033] Book Wyrm - COST:6 [ATK:3/HP:6]
    // - Race: Dragon, Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy an enemy minion with 3 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NONSELF_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MAX_ATTACK = 3
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NONSELF_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_MAX_ATTACK, 3 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND, 0 } };
    cards.emplace("KAR_033", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_036] Arcane Anomaly - COST:1 [ATK:2/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Kara, Rarity: common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       give this minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "KAR_036e", EntityType::SOURCE) };
    cards.emplace("KAR_036", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_037] Avian Watcher - COST:5 [ATK:3/HP:6]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "KAR_037t", EntityType::SOURCE) }));
    cards.emplace("KAR_037", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_041] Moat Lurker - COST:6 [ATK:3/HP:3]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       <b>Deathrattle:</b> Resummon it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::ENTITY_ID));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagNumberTask>(
        EntityType::SOURCE, GameTag::MOAT_LURKER_MINION));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::SOURCE));
    cardDef.power.AddDeathrattleTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            const int entityID =
                playables[0]->GetGameTag(GameTag::MOAT_LURKER_MINION);
            if (entityID == 0)
            {
                return std::vector<Playable*>{};
            }

            const Playable* target = playables[0]->game->entityList[entityID];
            if (target->player->GetFieldZone()->IsFull())
            {
                return std::vector<Playable*>{};
            }

            Entity* entity =
                Entity::GetFromCard(target->player, target->card, std::nullopt,
                                    target->player->GetFieldZone());
            Generic::Summon(dynamic_cast<Minion*>(entity), -1, target->player);

            return std::vector<Playable*>{};
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("KAR_041", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_044] Moroes - COST:3 [ATK:1/HP:1]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       At the end of your turn, summon a 1/1 Steward.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "KAR_044a", SummonSide::RIGHT) };
    cards.emplace("KAR_044", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_061] The Curator - COST:7 [ATK:4/HP:6]
    // - Race: Mechanical, Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Draw a Beast,
    //       Dragon, and Murloc from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::MURLOC)) }));
    cards.emplace("KAR_061", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_062] Netherspite Historian - COST:2 [ATK:1/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DiscoverTask>(DiscoverType::DRAGON) }));
    cards.emplace("KAR_062", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_095] Zoobot - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly Beast,
    //       Dragon, and Murloc +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_095e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_095e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_095e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::MURLOC)) }));
    cards.emplace("KAR_095", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_096] Prince Malchezaar - COST:5 [ATK:5/HP:6]
    // - Race: Demon, Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: When the game starts,
    //       add 5 extra <b>Legendary</b> minions to your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::GAME_START));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::DECK;
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cardDef.power.GetTrigger()->tasks = TaskList{
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::RARITY, static_cast<int>(Rarity::LEGENDARY),
                         RelaSign::EQ } },
            5),
        std::make_shared<AddStackToTask>(EntityType::DECK)
    };
    cards.emplace("KAR_096", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_097] Medivh, the Guardian - COST:8 [ATK:7/HP:7]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Equip Atiesh, Greatstaff of the Guardian.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("KAR_097t"));
    cards.emplace("KAR_097", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_114] Barnes - COST:4 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 copy of
    //       a random minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldNotFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<IncludeTask>(EntityType::DECK),
                        std::make_shared<FilterStackTask>(
                            SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsMinion()) }),
                        std::make_shared<RandomTask>(EntityType::STACK, 1),
                        std::make_shared<CopyTask>(EntityType::STACK,
                                                   ZoneType::PLAY, 1, true),
                        std::make_shared<AddEnchantmentTask>(
                            "KAR_114e", EntityType::STACK) }));
    cards.emplace("KAR_114", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_702] Menagerie Magician - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly Beast,
    //       Dragon, and Murloc +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_702e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_702e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(ComplexTask::GiveBuffToRandomMinionInField(
        "KAR_702e", SelfCondList{ std::make_shared<SelfCondition>(
                        SelfCondition::IsRace(Race::MURLOC)) }));
    cards.emplace("KAR_702", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_710] Arcanosmith - COST:4 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 0/5 minion with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("KAR_710m"));
    cards.emplace("KAR_710", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_711] Arcane Giant - COST:12 [ATK:8/HP:8]
    // - Set: Kara, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each spell you've cast this game.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetNumSpellsPlayedThisGame();
        }));
    cards.emplace("KAR_711", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_712] Violet Illusionist - COST:3 [ATK:4/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: During your turn, your hero is <b>Immune</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::HERO, EffectList{ Effects::Immune }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMyTurn());
        aura->restless = true;
    }
    cards.emplace("KAR_712", cardDef);
}

void KaraCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_030] Cellar Spider (*) - COST:3 [ATK:1/HP:3]
    // - Race: Beast, Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_030", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_036e] Eating (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(EffectList{ Effects::HealthN(1) }));
    cards.emplace("KAR_036e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_037t] Secrets of Karazhan (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("KAR_037t"));
    cards.emplace("KAR_037t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_041e] Moat Lurker (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Destroyed {0}.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_044a] Steward (*) - COST:1 [ATK:1/HP:1]
    // - Faction: neutral, Set: Kara
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_044a", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_077e] Silver Might (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("KAR_077e"));
    cards.emplace("KAR_077e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_095e] Well Fed (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("KAR_095e"));
    cards.emplace("KAR_095e", cardDef);

    // --------------------------------------- WEAPON - NEUTRAL
    // [KAR_097t] Atiesh (*) - COST:3 [ATK:1/HP:0]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       summon a random minion of that Cost.
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::TARGET,
                                         GameTag::TAG_LAST_KNOWN_COST_IN_HAND),
        std::make_shared<RandomMinionNumberTask>(GameTag::COST),
        std::make_shared<SummonTask>(),
        std::make_shared<DamageWeaponTask>(false)
    };
    cards.emplace("KAR_097t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_114e] Incredible Impression (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Attack and Health set to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetAttackHealth(1)));
    cards.emplace("KAR_114e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_702e] A Simple Trick (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("KAR_702e"));
    cards.emplace("KAR_702e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_710m] Animated Shield (*) - COST:2 [ATK:0/HP:5]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_710m", cardDef);
}

void KaraCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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