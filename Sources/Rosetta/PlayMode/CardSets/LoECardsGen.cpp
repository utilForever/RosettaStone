// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/LoECardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void LoECardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void LoECardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void LoECardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [LOE_050] Mounted Raptor - COST:3 [ATK:3/HP:2]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random 1-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 1, RelaSign::EQ } }));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>());
    cards.emplace("LOE_050", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [LOE_051] Jungle Moonkin - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Both players have <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER,
                                             EffectOperator::ADD, 2) }));
    cards.emplace("LOE_051", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [LOE_115] Raven Idol - COST:1
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>
    //       <b>Discover</b> a minion; or <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - CHOOSE_ONE = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "LOE_115a", "LOE_115b" };
    cards.emplace("LOE_115", cardDef);
}

void LoECardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [LOE_115a] Break Free (*) - COST:1
    // - Set: LoE
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::MINION));
    cards.emplace("LOE_115a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [LOE_115b] Awakened (*) - COST:1
    // - Set: LoE
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("LOE_115b", cardDef);
}

void LoECardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [LOE_020] Desert Camel - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Put a 1-Cost minion from each deck
    //       into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::SummonCostMinionFromDeck(1));
    cardDef.power.AddPowerTask(ComplexTask::SummonCostOpMinionFromDeck(1));
    cards.emplace("LOE_020", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [LOE_021] Dart Trap - COST:2
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After an opposing Hero Power is used,
    //       deal 5 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->eitherTurn = true;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        ComplexTask::DamageRandomTargets(EntityType::ENEMIES, 1, 5, true));
    cards.emplace("LOE_021", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [LOE_105] Explorer's Hat - COST:2
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +1/+1 and "<b>Deathrattle:</b>
    //       Add an Explorer's Hat to your hand."
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
        std::make_shared<AddEnchantmentTask>("LOE_105e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("LOE_105", cardDef);
}

void LoECardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [LOE_105e] Explorer's Hat (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: +1/+1. <b>Deathrattle:</b>
    //       Add an Explorer's Hat to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOE_105e"));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "LOE_105"));
    cards.emplace("LOE_105e", cardDef);
}

void LoECardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [LOE_002] Forgotten Torch - COST:3
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage. Shuffle a 'Roaring Torch'
    //       into your deck that deals 6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "LOE_002t"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("LOE_002", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:3]
    // - Set: LoE Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("LOE_003", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [LOE_119] Animated Armor - COST:4 [ATK:4/HP:4]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your hero can only take 1 damage at a time.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::TAKE_ONE_DAMAGE_AT_A_TIME,
                                             EffectOperator::SET, 1) }));
    cards.emplace("LOE_119", cardDef);
}

void LoECardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [LOE_002t] Roaring Torch (*) - COST:3
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Deal 6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 6, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("LOE_002t", cardDef);
}

void LoECardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [LOE_017] Keeper of Uldaman - COST:4 [ATK:3/HP:4]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set a minion's Attack and Health to 3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("LOE_017e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("LOE_017", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [LOE_026] Anyfin Can Happen - COST:10
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 7 Murlocs that died this game.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::GRAVEYARD));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 7));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::STACK));
    cards.emplace("LOE_026", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [LOE_027] Sacred Trial - COST:1
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent has at least
    //       3 minions and plays another, destroy it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(4, RelaSign::GEQ)) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) });
    cards.emplace("LOE_027", cardDef);
}

void LoECardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [LOE_017e] Watched (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetAttackHealth(3)));
    cards.emplace("LOE_017e", cardDef);
}

void LoECardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [LOE_006] Museum Curator - COST:2 [ATK:1/HP:2]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a <b>Deathrattle</b> card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DEATHRATTLE_MINION));
    cards.emplace("LOE_006", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [LOE_104] Entomb - COST:6
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose an enemy minion. Shuffle it into your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<MoveToDeckTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("LOE_104", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [LOE_111] Excavated Evil - COST:5
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to all minions.
    //       Shuffle this card into your opponent's deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_DECK, "LOE_111"));
    cards.emplace("LOE_111", cardDef);
}

void LoECardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void LoECardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [LOE_010] Pit Snake - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_010", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005"));
    cards.emplace("LOE_012", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [LOE_019] Unearthed Raptor - COST:3 [ATK:3/HP:4]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Gain a copy of its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::ENTITY_ID));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "LOE_019e", EntityType::SOURCE, false, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_DEATHRATTLE, 0 } };
    cards.emplace("LOE_019", cardDef);
}

void LoECardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [LOE_019e] Unearthed Raptor (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Copied Deathrattle from {0}.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ActivateCapturedDeathrattleTask>());
    cards.emplace("LOE_019e", cardDef);
}

void LoECardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [LOE_016] Rumbling Elemental - COST:4 [ATK:2/HP:6]
    // - Race: Elemental, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a <b>Battlecry</b> minion,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsBattlecryCard())
    };
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::DamageRandomTargets(EntityType::ENEMIES, 1, 2);
    cards.emplace("LOE_016", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [LOE_018] Tunnel Trogg - COST:1 [ATK:1/HP:3]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you <b>Overload</b>,
    //       gain +1 Attack per locked Mana Crystal.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOverloadCard())
    };
    cardDef.power.GetTrigger()->tasks =
        TaskList{ std::make_shared<GetGameTagTask>(EntityType::TARGET,
                                                   GameTag::OVERLOAD),
                  std::make_shared<AddEnchantmentTask>(
                      "LOE_018e", EntityType::SOURCE, true) };
    cards.emplace("LOE_018", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [LOE_113] Everyfin is Awesome - COST:7
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions +2/+2.
    //       Costs (1) less for each Murloc you control.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("LOE_113e", EntityType::MINIONS));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            const auto minions = playable->player->GetFieldZone()->GetAll();
            int numMurlocs = 0;

            for (auto& minion : minions)
            {
                if (minion->IsRace(Race::MURLOC))
                {
                    ++numMurlocs;
                }
            }

            return numMurlocs;
        }));
    cards.emplace("LOE_113", cardDef);
}

void LoECardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [LOE_018e] Trogg No Stupid (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("LOE_018e", cardDef);
}

void LoECardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [LOE_007] Curse of Rafaam - COST:2
    // - Set: LoE, Rarity: common
    // --------------------------------------------------------
    // Text: Give your opponent a 'Cursed!' card.
    //       While they hold it, they take 2 damage on their turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_HAND, "LOE_007t"));
    cards.emplace("LOE_007", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [LOE_023] Dark Peddler - COST:2 [ATK:2/HP:2]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a 1-Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::ONE_COST_CARD));
    cards.emplace("LOE_023", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [LOE_116] Reliquary Seeker - COST:1 [ATK:1/HP:1]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 6 other minions,
    //       gain +4/+4.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "LOE_009e", EntityType::SOURCE) }));
    cards.emplace("LOE_116", cardDef);
}

void LoECardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [LOE_009e] Sinister Power (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOE_009e"));
    cards.emplace("LOE_009e", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [LOE_007t] Cursed! (*) - COST:2
    // - Set: LoE
    // --------------------------------------------------------
    // Text: While this is in your hand,
    //       take 2 damage at the start of your turn.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - EVIL_GLOW = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->tasks =
        TaskList{ std::make_shared<DamageTask>(EntityType::HERO, 2) };
    cards.emplace("LOE_007t", cardDef);
}

void LoECardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [LOE_009] Obsidian Destroyer - COST:7 [ATK:7/HP:7]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a 1/1 Scarab with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "LOE_009t", SummonSide::RIGHT) };
    cards.emplace("LOE_009", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [LOE_022] Fierce Monkey - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_022", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [LOE_118] Cursed Blade - COST:1 [ATK:2/HP:0]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Double all damage dealt to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::TAKE_DAMAGE_DOUBLE,
                                             EffectOperator::SET, 1) }));
    cards.emplace("LOE_118", cardDef);
}

void LoECardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [LOE_009t] Scarab (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: LoE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_009t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [LOE_118e] Cursed Blade (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Double all damage dealt to your hero.
    // --------------------------------------------------------
}

void LoECardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_011] Reno Jackson - COST:6 [ATK:4/HP:6]
    // - Set: LoE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       fully heal your hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNoDuplicateInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<HealFullTask>(EntityType::HERO) }));
    cards.emplace("LOE_011", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_029] Jeweled Scarab - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a 3-Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::THREE_COST_CARD));
    cards.emplace("LOE_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_038] Naga Sea Witch - COST:8 [ATK:5/HP:5]
    // - Set: LoE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your cards cost (5).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::SetCost(5) }));
    cards.emplace("LOE_038", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_039] Gorillabot A-3 - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control another Mech,
    //       <b>Discover</b> a Mech.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::MINIONS_NOSOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::MECHANICAL)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DiscoverTask>(DiscoverType::MECHANICAL) }));
    cards.emplace("LOE_039", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_046] Huge Toad - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1));
    cards.emplace("LOE_046", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_047] Tomb Spider - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a Beast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::BEAST));
    cards.emplace("LOE_047", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_053] Djinni of Zephyrs - COST:5 [ATK:4/HP:6]
    // - Race: Elemental, Set: LoE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a spell on another friendly minion,
    //       cast a copy of it on this one.
    // --------------------------------------------------------
    // GameTag:
    // - 1059 = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::SPELLS_CASTED_ON_ANOTHER_FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CastCopyTask>(
        EntityType::EVENT_SOURCE) };
    cards.emplace("LOE_053", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_061] Anubisath Sentinel - COST:5 [ATK:4/HP:4]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        ComplexTask::GiveBuffToRandomMinionInField("LOE_061e"));
    cards.emplace("LOE_061", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_073] Fossilized Devilsaur - COST:8 [ATK:8/HP:8]
    // - Set: LoE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Beast,
    //       gain <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::MINIONS,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "LOE_073e", EntityType::SOURCE) }));
    cards.emplace("LOE_073", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_076] Sir Finley Mrrgglton - COST:1 [ATK:1/HP:3]
    // - Race: Murloc, Set: LoE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a new basic Hero Power.
    // --------------------------------------------------------
    // Entourage: HERO_01bp, HERO_02bp, HERO_03bp, HERO_04bp,
    //            HERO_05bp, HERO_06bp, HERO_07bp, HERO_08bp,
    //            HERO_09bp, HERO_10bp
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::HERO_POWER));
    cards.emplace("LOE_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_077] Brann Bronzebeard - COST:3 [ATK:2/HP:4]
    // - Set: LoE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your <b>Battlecries</b> trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::EXTRA_BATTLECRIES_BASE,
                                             EffectOperator::SET, 1) }));
    cards.emplace("LOE_077", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_079] Elise Starseeker - COST:4 [ATK:3/HP:5]
    // - Set: LoE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle the
    //       'Map to the Golden Monkey' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "LOE_019t", 1));
    cards.emplace("LOE_079", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_086] Summoning Stone - COST:5 [ATK:0/HP:6]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a random minion of the same Cost.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::EVENT_SOURCE,
                                         GameTag::COST),
        std::make_shared<RandomMinionNumberTask>(GameTag::COST),
        std::make_shared<SummonTask>()
    };
    cards.emplace("LOE_086", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_089] Wobbling Runts - COST:6 [ATK:2/HP:6]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon three 2/2 Runts.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("LOE_089t", SummonSide::DEATHRATTLE));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("LOE_089t2", SummonSide::DEATHRATTLE));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("LOE_089t3", SummonSide::DEATHRATTLE));
    cards.emplace("LOE_089", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_092] Arch-Thief Rafaam - COST:9 [ATK:7/HP:8]
    // - Set: LoE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a powerful Artifact.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(
        DiscoverType::ARCH_THIEF_RAFAAM, 3, 1, false));
    cards.emplace("LOE_092", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_107] Eerie Statue - COST:4 [ATK:7/HP:7]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack unless it's the only minion
    //       in the battlefield.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(2, RelaSign::GEQ)),
        GameTag::CANT_ATTACK));
    cards.emplace("LOE_107", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_110] Ancient Shade - COST:4 [ATK:7/HP:4]
    // - Set: LoE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle an 'Ancient Curse'
    //       into your deck that deals 7 damage to you when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_DECK, "LOE_110t"));
    cards.emplace("LOE_110", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1]
    // - Race: Murloc, Set: LoE, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOEA10_3", cardDef);
}

void LoECardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOE_008] Eye of Hakkar (*) - COST:1
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Take a secret from your opponent's deck and
    //       put it into the battlefield.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOE_008H] Eye of Hakkar (*) - COST:1
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Take a secret from your opponent's deck and
    //       put it into the battlefield.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_016t] Rock (*) - COST:1 [ATK:0/HP:6]
    // - Set: LoE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOE_019t] Map to the Golden Monkey (*) - COST:2
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Shuffle the Golden Monkey into your deck. Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "LOE_019t2", 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("LOE_019t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_019t2] Golden Monkey (*) - COST:4 [ATK:6/HP:6]
    // - Set: LoE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Replace your hand and deck
    //       with <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::HAND, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY));
    cardDef.power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::DECK, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY));
    cards.emplace("LOE_019t2", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_024t] Rolling Boulder (*) - COST:4 [ATK:0/HP:4]
    // - Set: LoE
    // --------------------------------------------------------
    // Text: At the end of your turn, destroy the minion to the left.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_030e] Hollow (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Stats copied.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_038e] Seawitching (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Costs (5).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_061e] Power of the Titans (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOE_061e"));
    cards.emplace("LOE_061e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_073e] Fossilized (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Has <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOE_073e"));
    cards.emplace("LOE_073e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_077e] Bronzebeard Battlecry (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Your <b>Battlecries</b> trigger twice.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_089t] Rascally Runt (*) - COST:2 [ATK:2/HP:2]
    // - Set: LoE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_089t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_089t2] Wily Runt (*) - COST:2 [ATK:2/HP:2]
    // - Set: LoE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_089t2", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOE_089t3] Grumbly Runt (*) - COST:2 [ATK:2/HP:2]
    // - Set: LoE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOE_089t3", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOE_110t] Ancient Curse (*) - COST:4
    // - Set: LoE
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       You take 7 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<DamageTask>(EntityType::HERO, 7));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 7));
    cards.emplace("LOE_110t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOE_113e] Mrglllraawrrrglrur! (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOE_113e"));
    cards.emplace("LOE_113e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOEA16_3] Lantern of Power (*) - COST:10
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Give a minion +10/+10.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("LOEA16_3e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("LOEA16_3", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOEA16_3e] Lantern of Power (*) - COST:0
    // - Set: LoE
    // --------------------------------------------------------
    // Text: +10/+10.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOEA16_3e"));
    cards.emplace("LOEA16_3e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOEA16_4] Timepiece of Horror (*) - COST:10
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Deal 10 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        10, true));
    cards.emplace("LOEA16_4", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOEA16_5] Mirror of Doom (*) - COST:10
    // - Set: LoE
    // --------------------------------------------------------
    // Text: Fill your board with 3/3 Mummy Zombies.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("LOEA16_5t", 7, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("LOEA16_5", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOEA16_5t] Mummy Zombie (*) - COST:3 [ATK:3/HP:3]
    // - Set: LoE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOEA16_5t", cardDef);
}

void LoECardsGen::AddAll(std::map<std::string, CardDef>& cards)
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