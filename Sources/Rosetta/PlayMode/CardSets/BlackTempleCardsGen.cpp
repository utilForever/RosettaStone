// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void BlackTempleCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void BlackTempleCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [BT_429p] Demonic Blast - COST:1
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 4 damage. (Two uses left!)
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, false));
    cardDef.power.AddPowerTask(
        std::make_shared<ChangeHeroPowerTask>("BT_429p2"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_429p", cardDef);

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [BT_429p2] Demonic Blast - COST:1
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 4 damage. (Last use!)
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, false));
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](Playable* playable) {
            Player* player = playable->player;

            const int dbfID = player->GetGameTag(GameTag::HERO_POWER_OLD);
            const auto heroPowerCard = Cards::FindCardByDbfID(dbfID);

            const auto& changeHeroPowerTask =
                std::make_shared<ChangeHeroPowerTask>(heroPowerCard->id);
            changeHeroPowerTask->SetPlayer(player);
            changeHeroPowerTask->SetSource(playable);
            changeHeroPowerTask->SetTarget(nullptr);

            changeHeroPowerTask->Run();

            return 0;
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_429p2", cardDef);
}

void BlackTempleCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [BT_127] Imprisoned Satyr - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. When this awakens,
    //       reduce the Cost of a random minion in your hand by (5).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(TaskList{
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<AddEnchantmentTask>("BT_127e", EntityType::STACK) }) };
    cards.emplace("BT_127", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_128] Fungal Fortunes - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw 3 cards. Discard any minions drawn.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [BT_129] Germination - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a copy of a friendly minion.
    //       Give the copy <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [BT_130] Overgrowth - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Gain two empty Mana Crystals.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(2, false));
    cards.emplace("BT_130", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_131] Ysiel Windsinger - COST:9 [ATK:5/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your spells cost (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::SetCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cards.emplace("BT_131", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_132] Ironbark - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion +1/+3 and <b>Taunt</b>.
    //       Costs (0) if you have at least 7 Mana Crystals.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_132e", EntityType::TARGET));
    cardDef.power.AddAura(std::make_shared<AdaptiveCostEffect>(
        []([[maybe_unused]] Playable* playable) { return 0; },
        EffectOperator::SET, SelfCondition::HasAtLeastManaCrystal(7)));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_132", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_133] Marsh Hydra - COST:7 [ATK:7/HP:7]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b> After this attacks,
    //       add a random 8-Cost minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::COST, 8, RelaSign::EQ } }),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("BT_133", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_134] Bogbeam - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    //       Costs (0) if you have at least 7 Mana Crystals.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddAura(std::make_shared<AdaptiveCostEffect>(
        []([[maybe_unused]] Playable* playable) { return 0; },
        EffectOperator::SET, SelfCondition::HasAtLeastManaCrystal(7)));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_134", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_135] Glowfly Swarm - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a 2/2 Glowfly for each spell in your hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BT_136] Archspore Msshi'fn - COST:3 [ATK:3/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Shuffle
    //       'Msshi'fn Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "BT_136t", 1));
    cards.emplace("BT_136", cardDef);
}

void BlackTempleCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BT_127e] Imprisoned Satyr - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (5) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(5)));
    cards.emplace("BT_127e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BT_132e] Ironbark - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+3 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_132e"));
    cards.emplace("BT_132e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_135t] Glowfly - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: BLACK_TEMPLE
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BT_136t] Msshi'fn Prime - COST:10 [ATK:9/HP:9]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Choose One -</b> Summon a
    //       9/9 Fungal Giant with <b>Taunt</b>; or <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "BT_136ta", "BT_136tb" };
    cards.emplace("BT_136t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_136ta] Msshi'fn Pro'tec - COST:10
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Summon a 9/9 Guardian with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BT_136tt", 1));
    cards.emplace("BT_136ta", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [BT_136tb] Msshi'fn At'tac - COST:10
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Summon a 9/9 Bruiser with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BT_136tt2", 1));
    cards.emplace("BT_136tb", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_136tt] Fungal Guardian - COST:10 [ATK:9/HP:9]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_136tt", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_136tt2] Fungal Bruiser - COST:10 [ATK:9/HP:9]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_136tt2", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BT_136tt3] Fungal Gargantuan - COST:10 [ATK:9/HP:9]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_136tt3", cardDef);
}

void BlackTempleCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [BT_163] Nagrand Slam - COST:10
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon four 3/5 Clefthoofs that attack random enemies.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BT_201] Augmented Porcupine - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle</b>: Deal this minion's Attack damage
    //       randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BT_202] Helboar - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random Beast in your hand +1/+1.
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
                SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("BT_205e", EntityType::STACK));
    cards.emplace("BT_202", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [BT_203] Pack Tactics - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion is attacked,
    //       summon a 3/3 copy.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BT_205] Scrap Shot - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage. Give a random Beast in your hand +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_205e", EntityType::STACK));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_205", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BT_210] Zixor, Apex Predator - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Shuffle 'Zixor Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BT_211] Imprisoned Felmaw - COST:2 [ATK:5/HP:4]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       When this awakens, attack a random enemy.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BT_212] Mok'Nathal Lion - COST:4 [ATK:5/HP:2]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> Choose a friendly minion.
    //       Gain a copy of its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BT_213] Scavenger's Ingenuity - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a Beast. Give it +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawRaceMinionTask>(Race::BEAST, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_213e", EntityType::STACK));
    cards.emplace("BT_213", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [BT_214] Beastmaster Leoroxx - COST:8 [ATK:5/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 3 Beasts from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [BT_163t] Clefthoof - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: BLACK_TEMPLE
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BT_202e] Scent of Blood - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BT_203e] Packmate - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Attack and Health set to 3.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BT_210t] Zixor Prime - COST:8 [ATK:4/HP:4]
    // - Race: Beast, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Summon 3 copies of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [BT_002] Incanter's Flow - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Reduce the Cost of spells in your deck by (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_002e", EntityType::STACK));
    cards.emplace("BT_002", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [BT_003] Netherwind Portal - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       summon a random 4-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOpFieldNotFull())
    };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<RandomMinionTask>(
                      TagValues{ { GameTag::COST, 4, RelaSign::EQ } }),
                  std::make_shared<SummonStackTask>() });
    cards.emplace("BT_003", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [BT_004] Imprisoned Observer - COST:3 [ATK:4/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       When this awakens, deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(TaskList{
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2) }) };
    cards.emplace("BT_004", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [BT_006] Evocation - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Fill your hand with random Mage spells.
    //       At the end of your turn, discard them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BT_014] Starscryer - COST:2 [ATK:3/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawSpellTask>(1));
    cards.emplace("BT_014", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [BT_021] Font of Power - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Mage minion.
    //       If your deck has no minions, keep all 3.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BT_022] Apexis Smuggler - COST:2 [ATK:2/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a <b>Secret</b>, <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BT_028] Astromancer Solarian - COST:2 [ATK:3/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b> <b>Deathrattle:</b> Shuffle
    //       'Solarian Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BT_072] Deep Freeze - COST:8
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> an enemy. Summon two 3/6 Water Elementals.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("CS2_033", 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("BT_072", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [BT_291] Apexis Blast - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 5 damage. If your deck has no minions,
    //       summon a random 5-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::HasNoMinionsInDeck()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomMinionTask>(
                            TagValues{ { GameTag::COST, 5, RelaSign::EQ } }),
                        std::make_shared<SummonTask>() }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_291", cardDef);
}

void BlackTempleCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BT_002e] Incanter's Flow - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("BT_002e", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BT_006e] Evocation - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Discards at the end of your turn.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BT_028t] Solarian Prime - COST:7 [ATK:7/HP:7]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Battlecry:</b> Cast 5 random Mage spells
    //       (targets enemies if possible).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [BT_009] Imprisoned Sungill - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. When this awakens,
    //       summon two 1/1 Murlocs.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(TaskList{
        std::make_shared<SummonTask>("BT_009t", 1, SummonSide::LEFT),
        std::make_shared<SummonTask>("BT_009t", 1, SummonSide::RIGHT) }) };
    cards.emplace("BT_009", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [BT_011] Libram of Justice - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Equip a 1/4 weapon.
    //       Change the Health of all enemy minions to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("BT_011t"));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BT_011e", EntityType::ENEMY_MINIONS));
    cards.emplace("BT_011", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [BT_018] Underlight Angling Rod - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your Hero attacks,
    //       add a random Murloc to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::INVALID,
                                         Race::MURLOC),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("BT_018", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BT_019] Murgur Murgurgle - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> <b>Deathrattle:</b> Shuffle
    //       'Murgurgle Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BT_020] Aldor Attendant - COST:1 [ATK:1/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of your Librams
    //       by (1) this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BT_024] Libram of Hope - COST:9
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 8 Health. Summon an 8/8 Guardian
    //       with <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 8));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("BT_024t", 1, SummonSide::DEFAULT));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_024", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [BT_025] Libram of Wisdom - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +1/+1 and "<b>Deathrattle:</b>
    //       Add a 'Libram of Wisdom' spell to your hand."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BT_026] Aldor Truthseeker - COST:5 [ATK:4/HP:6]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> Reduce the Cost of
    //       your Librams by (2) this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BT_292] Hand of A'dal - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+1. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_292e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_292", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BT_334] Lady Liadrin - COST:7 [ATK:4/HP:6]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a copy of each spell you cast
    //       on friendly characters this game to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [BT_009t] Sungill Streamrunner - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_009t", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [BT_011t] Overdue Justice - COST:1
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_011t", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [BT_019t] Murgurgle Prime - COST:8 [ATK:6/HP:3]
    // - Race: Murloc, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Battlecry:</b> Summon 4 random Murlocs.
    //       Give them <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BT_024t] Ancient Guardian - COST:8 [ATK:8/HP:8]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_024t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BT_025e] Light's Wisdom - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1. <b>Deathrattle:</b> Add
    //       'Libram of Wisdom' to your hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BT_292e] Hand of A'dal - COST:0
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_292e"));
    cards.emplace("BT_292e", cardDef);
}

void BlackTempleCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [BT_197] Reliquary of Souls - COST:1 [ATK:1/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> <b>Deathrattle:</b> Shuffle
    //       'Reliquary Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BT_198] Soul Mirror - COST:7
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Summon copies of enemy minions.
    //       They attack their copies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ----------------------------------------- SPELL - PRIEST
    // [BT_252] Renew - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 3 Health. <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 3));
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_252", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BT_253] Psyche Split - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give a minion +1/+2. Summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_253e", EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_253", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [BT_254] Sethekk Veilweaver - COST:2 [ATK:2/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a spell on a minion,
    //       add a Priest spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BT_256] Dragonmaw Overseer - COST:3 [ATK:2/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another friendly minion +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<AddEnchantmentTask>("BT_256e", EntityType::STACK)
    };
    cards.emplace("BT_256", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [BT_257] Apotheosis - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+3 and <b>Lifesteal</b>.
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_257e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_257", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [BT_258] Imprisoned Homunculus - COST:1 [ATK:2/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(
        TaskList{}) };
    cards.emplace("BT_258", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [BT_262] Dragonmaw Sentinel - COST:2 [ATK:1/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BT_262e", EntityType::SOURCE) }));
    cards.emplace("BT_262", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [BT_341] Skeletal Dragon - COST:7 [ATK:4/HP:9]
    // - Race: Dragon, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the end of your turn,
    //       add a Dragon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::CARDRACE, static_cast<int>(Race::DRAGON),
                         RelaSign::EQ } }),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("BT_341", cardDef);
}

void BlackTempleCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [BT_197t] Reliquary Prime - COST:7 [ATK:6/HP:8]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Lifesteal</b>
    //       Only you can target this with spells and Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BT_253e] Twin Vision - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_253e"));
    cards.emplace("BT_253e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BT_256e] Booted - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Stats increased.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Effects::AttackHealthN(2)));
    cards.emplace("BT_256e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BT_257e] Apotheosis - COST:0
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: +2/+3 and <b>Lifesteal</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_257e"));
    cards.emplace("BT_257e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BT_262e] Nether Sight - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Lifesteal</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_262e"));
    cards.emplace("BT_262e", cardDef);
}

void BlackTempleCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [BT_042] Bamboozle - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       transform it into a random one that costs (3) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::MINION)) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<TransformMinionTask>(EntityType::EVENT_TARGET, 3) });
    cards.emplace("BT_042", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_188] Shadowjeweler Hanar - COST:2 [ATK:1/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a <b>Secret</b>, <b>Discover</b>
    //       a <b>Secret</b> from a different class.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BT_701] Spymistress - COST:1 [ATK:3/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_701", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_702] Ashtongue Slayer - COST:2 [ATK:3/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a <b>Stealthed</b> minion
    //       +3 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BT_703] Cursed Vagrant - COST:7 [ATK:7/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 7/5 Shadow with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_703t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_703", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BT_707] Ambush - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       summon a 2/3 Ambusher with <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("BT_707t", SummonSide::SPELL) });
    cards.emplace("BT_707", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [BT_709] Dirty Tricks - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<DrawTask>(2) });
    cards.emplace("BT_709", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_710] Greyheart Sage - COST:3 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control
    //       a <b>Stealthed</b> minion, draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingStealthedMinion()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(2) }));
    cards.emplace("BT_710", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_711] Blackjack Stunner - COST:1 [ATK:1/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       return a minion to its owner's hand. It costs (2) more.
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
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<AddAuraEffectTask>(
        Effects::AddCost(2), EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{
        { PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS, 1 }
    };
    cards.emplace("BT_711", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_713] Akama - COST:3 [ATK:3/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b> <b>Deathrattle:</b> Shuffle
    //       'Akama Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BT_212e] Stalking - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BT_702e] Guile of the Ashtongue - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +3 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BT_703t] Cursed Shadow - COST:7 [ATK:7/HP:5]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_703t", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_707t] Broken Ambusher - COST:2 [ATK:2/HP:3]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_707t", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [BT_713t] Akama Prime - COST:6 [ATK:6/HP:5]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Permanently <b>Stealthed</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [BT_100] Serpentshrine Portal - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage. Summon a random 3-Cost minion.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 3, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("BT_100", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [BT_101] Vivid Spores - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions
    //       "<b>Deathrattle:</b> Resummon this minion."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [BT_102] Boggspine Knuckles - COST:5 [ATK:4/HP:0]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero attacks, transform your minions
    //       into random ones that cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<TransformMinionTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("BT_102", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BT_106] Bogstrok Clacker - COST:3 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform adjacent minions
    //       into random minions that cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<TransformMinionTask>(EntityType::STACK, 1));
    cards.emplace("BT_106", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BT_109] Lady Vashj - COST:3 [ATK:4/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b> <b>Deathrattle:</b> Shuffle
    //       'Vashj Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BT_110] Torrent - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 8 damage to a minion.
    //       Costs (3) less if you cast a spell last turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 8, true));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (playable->player->GetNumSpellsCastLastTurn() > 0)
            {
                return 3;
            }

            return 0;
        }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_110", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [BT_113] Totemic Reflection - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       If it's a Totem, summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_113e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsRace(Race::TOTEM)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ConditionTask>(
                            EntityType::TARGET,
                            RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsFriendly()) }),
                        std::make_shared<FlagTask>(
                            true, TaskList{ std::make_shared<SummonCopyTask>(
                                      EntityType::TARGET, false, false,
                                      SummonSide::TARGET) }),
                        std::make_shared<FlagTask>(
                            false, TaskList{ std::make_shared<SummonCopyTask>(
                                       EntityType::TARGET, false, false,
                                       SummonSide::SPELL) }) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_113", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BT_114] Shattered Rumbler - COST:5 [ATK:5/HP:6]
    // - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you cast a spell last turn,
    //       deal 2 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsCastSpellLastTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(
                  EntityType::ALL_MINIONS_NOSOURCE, 2) }));
    cards.emplace("BT_114", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BT_115] Marshspawn - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you cast a spell last turn,
    //       <b>Discover</b> a spell.
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
                                SelfCondition::IsCastSpellLastTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DiscoverTask>(DiscoverType::SPELL) }));
    cards.emplace("BT_115", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BT_230] The Lurker Below - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to an enemy minion.
    //       If it dies, repeat on one of its neighbors.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BT_101e] Glowcapped - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BT_109t] Vashj Prime - COST:7 [ATK:5/HP:4]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b> <b>Battlecry:</b> Draw 3 spells.
    //       Reduce their Cost by (3).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BT_109te] Vashj Prime - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Cost (3) less.
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [BT_196] Keli'dan the Breaker - COST:6 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       If drawn this turn, instead destroy all minions
    //       except this one.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BT_199] Unstable Felbolt - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 3 damage to an enemy minion
    //       and a random friendly one.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldNotEmpty()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<IncludeTask>(EntityType::MINIONS),
                  std::make_shared<RandomTask>(EntityType::STACK, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 3, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("BT_199", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BT_300] Hand of Gul'dan - COST:6
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: When you play or discard this, draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BT_301] Nightshade Matron - COST:4 [ATK:5/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Discard your highest Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscardTask>(1, DiscardType::HIGHEST_COST));
    cards.emplace("BT_301", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BT_302] The Dark Portal - COST:4
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Draw a minion. If you have at least 8 cards in hand,
    //       it costs (5) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::HasAtLeastCardInHand(8)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BT_302e", EntityType::STACK) }));
    cards.emplace("BT_302", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [BT_304] Enhanced Dreadlord - COST:8 [ATK:5/HP:7]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a 5/5
    //       Dreadlord with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_304t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_304", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [BT_305] Imprisoned Scrap Imp - COST:2 [ATK:3/HP:3]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. When this awakens,
    //       give all minions in your hand +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(
        TaskList{ std::make_shared<AddEnchantmentTask>(
            "BT_305e", EntityType::HAND, false, false,
            SelfCondition::IsMinion()) }) };
    cards.emplace("BT_305", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [BT_306] Shadow Council - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Replace your hand with random Demons. Give them +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BT_307] Darkglare - COST:3 [ATK:3/HP:4]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero takes damage, refresh a Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BT_309] Kanrethad Ebonlocke - COST:2 [ATK:3/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Demons cost (1) less. <b>Deathrattle:</b> Shuffle
    //       'Kanrethad Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [BT_304t] Desperate Dreadlord - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_304t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BT_305e] Scrap Weapons - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_305e"));
    cards.emplace("BT_305e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BT_306e] Ritual Summons - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BT_309t] Kanrethad Prime - COST:8 [ATK:7/HP:6]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 3 friendly Demons
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [BT_117] Bladestorm - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions. Repeat until one dies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, [[maybe_unused]] Playable* target) {
            const auto& damageTask =
                std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true);
            const auto& condition =
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead());

            damageTask->SetPlayer(player);
            damageTask->SetSource(source);

            int repeatTime = 0;
            bool flag = true;

            // NOTE: Bladestorm can only repeat a maximum of 29 times. After
            // the 30th time (dealing 30 damage), it stops, regardless of
            // how much health the minion with the lowest one has.
            // References: https://hearthstone.gamepedia.com/Bladestorm
            while (flag && repeatTime < 30)
            {
                auto minions = IncludeTask::GetEntities(
                    EntityType::ALL_MINIONS, player, source, nullptr);
                if (minions.empty())
                {
                    break;
                }

                damageTask->Run();

                for (const auto& minion : minions)
                {
                    flag = flag && condition->Evaluate(minion);
                }

                ++repeatTime;
            }

            return TaskStatus::COMPLETE;
        }));
    cards.emplace("BT_117", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_120] Warmaul Challenger - COST:3 [ATK:1/HP:10]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an enemy minion.
    //       Battle it to the death!
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, Playable* target) {
            const auto& attackTask = std::make_shared<AttackTask>(
                EntityType::SOURCE, EntityType::TARGET, true);
            const auto& condition =
                std::make_shared<SelfCondition>(SelfCondition::IsDead());

            attackTask->SetPlayer(player);
            attackTask->SetSource(source);
            attackTask->SetTarget(target);

            while (true)
            {
                if (condition->Evaluate(dynamic_cast<Playable*>(source)) ||
                    condition->Evaluate(dynamic_cast<Playable*>(target)))
                {
                    break;
                }

                attackTask->Run();
            }

            return TaskStatus::COMPLETE;
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("BT_120", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_121] Imprisoned Gan'arg - COST:1 [ATK:2/HP:2]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       When this awakens, equip a 3/2 Axe.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(
        TaskList{ std::make_shared<WeaponTask>("CS2_106") }) };
    cards.emplace("BT_121", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_123] Kargath Bladefist - COST:4 [ATK:4/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: LEGENDARY
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Deathrattle:</b> Shuffle
    //       'Kargath Prime' into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "BT_123t"));
    cards.emplace("BT_123", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [BT_124] Corsair Cache - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a weapon. Give it +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawWeaponTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_124e", EntityType::STACK));
    cards.emplace("BT_124", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_138] Bloodboil Brute - COST:7 [ATK:6/HP:8]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> Costs (1) less for each damaged minion.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            FieldZone* curField = playable->player->GetFieldZone();
            FieldZone* opField = playable->player->opponent->GetFieldZone();
            int count = 0;

            for (const auto& minion : curField->GetAll())
            {
                if (minion->GetDamage() > 0)
                {
                    ++count;
                }
            }

            for (const auto& minion : opField->GetAll())
            {
                if (minion->GetDamage() > 0)
                {
                    ++count;
                }
            }

            return count;
        }));
    cards.emplace("BT_138", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_140] Bonechewer Raider - COST:3 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If there is a damaged minion,
    //       gain +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BT_233] Sword and Board - COST:1
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. Gain 2 Armor.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_233", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [BT_249] Scrap Golem - COST:5 [ATK:4/HP:5]
    // - Race: Mechanical, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle</b>: Gain Armor
    //       equal to this minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [BT_781] Bulwark of Azzinoth - COST:3
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your hero would take damage,
    //       this loses 1 Durability instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [BT_123t] Kargath Prime - COST:8 [ATK:10/HP:10]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Whenever this attacks
    //       and kills a minion, gain 10 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(
                    SelfCondition::IsDefenderDead()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsEventTargetIs(CardType::MINION)) }),
        std::make_shared<FlagTask>(true,
                                   TaskList{ std::make_shared<ArmorTask>(10) })
    };
    cards.emplace("BT_123t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BT_124e] Void Sharpened
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>(
            { Effects::AttackN(1), Effects::DurabilityN(1) })));
    cards.emplace("BT_124e", cardDef);
}

void BlackTempleCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_187] Kayn Sunfury - COST:4 [ATK:3/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b> All friendly attacks ignore <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_321] Netherwalker - COST:2 [ATK:2/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Demon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DEMON));
    cards.emplace("BT_321", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_423] Ashtongue Battlelord - COST:4 [ATK:3/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_423", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_429] Metamorphosis - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Swap your Hero Power to "Deal 4 damage."
    //       After 2 uses, swap it back.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            Player* player = playable->player;

            const int dbfID = player->GetHeroPower().card->dbfID;
            player->SetGameTag(GameTag::HERO_POWER_OLD, dbfID);

            return 0;
        }));
    cardDef.power.AddPowerTask(
        std::make_shared<ChangeHeroPowerTask>("BT_429p"));
    cards.emplace("BT_429", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BT_430] Warglaives of Azzinoth - COST:5
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After attacking a minion, your hero may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsEventTargetIs(CardType::MINION)) };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::HERO, GameTag::EXHAUSTED, 0) };
    cards.emplace("BT_430", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_480] Crimson Sigil Runner - COST:1 [ATK:1/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddOutcastTask(std::make_shared<DrawTask>(1));
    cards.emplace("BT_480", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_486] Pit Commander - COST:9 [ATK:7/HP:9]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the end of your turn,
    //       summon a Demon from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::SummonRaceMinionFromDeck(
        Race::DEMON) };
    cards.emplace("BT_486", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_491] Spectral Sight - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card.
    //       <b>Outcast:</b> Draw another.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.power.AddOutcastTask(std::make_shared<DrawTask>(1));
    cards.emplace("BT_491", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_493] Priestess of Fury - COST:7 [ATK:6/HP:7]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 6 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        6, false) };
    cards.emplace("BT_493", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_496] Furious Felfin - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero attacked this turn,
    //       gain +1 Attack and <b>Rush</b>.
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
                              SelfCondition::IsAttackThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "BT_496e", EntityType::SOURCE) }));
    cards.emplace("BT_496", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_509] Fel Summoner - COST:6 [ATK:8/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random Demon from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DEMON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("BT_509", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_514] Immolation Aura - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions twice.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConsecutiveDamageTask>(
        EntityType::ALL_MINIONS, std::vector<int>{ 1, 1 }, true));
    cards.emplace("BT_514", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_601] Skull of Gul'dan - COST:6
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 3 cards. <b>Outcast:</b> Reduce their Cost by (3).
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3, true));
    cardDef.power.AddOutcastTask(
        std::make_shared<AddEnchantmentTask>("BT_601e", EntityType::STACK));
    cards.emplace("BT_601", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_761] Coilfang Warlord - COST:8 [ATK:9/HP:5]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Deathrattle:</b> Summon a
    //       5/9 Warlord with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_761t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_761", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_934] Imprisoned Antaen - COST:5 [ATK:10/HP:6]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. When this awakens,
    //       deal 10 damage randomly split among all enemies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(
        TaskList{ std::make_shared<EnqueueTask>(
            TaskList{ std::make_shared<FilterStackTask>(
                          SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsNotDead()) }),
                      std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
                      std::make_shared<DamageTask>(EntityType::STACK, 1) },
            10, false) }) };
    cards.emplace("BT_934", cardDef);
}

void BlackTempleCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_512e3] Branded - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Takes 1 damage at the end of each turn.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_761t] Conchguard Warlord - COST:8 [ATK:5/HP:9]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_761t", cardDef);
}

void BlackTempleCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [BT_008] Rustsworn Initiate - COST:2 [ATK:2/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Impcaster with
    //       <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_008t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_008", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_010] Felfin Navigator - COST:4 [ATK:4/HP:4]
    // - Race: Murloc, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Murlocs +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_010e", EntityType::STACK));
    cards.emplace("BT_010", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_126] Teron Gorefiend - COST:3 [ATK:3/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other friendly minions.
    //       <b>Deathrattle:</b> Resummon them with +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_155] Scrapyard Colossus - COST:10 [ATK:7/HP:7]
    // - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a
    //       7/7 Felcracked Colossus with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_155t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_155", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_156] Imprisoned Vilefiend - COST:2 [ATK:3/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns. <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ProcessDormant(
        TaskList{}) };
    cards.emplace("BT_156", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_159] Terrorguard Escapee - COST:3 [ATK:3/HP:7]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon three 1/1 Huntresses
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonOpTask>("BT_159t", 3));
    cards.emplace("BT_159", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_160] Rustsworn Cultist - COST:4 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other minions
    //       "<b>Deathrattle:</b> Summon a 1/1 Demon."
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "BT_160e", EntityType::MINIONS_NOSOURCE));
    cards.emplace("BT_160", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_190] Replicat-o-tron - COST:4 [ATK:3/HP:3]
    // - Race: Mechanical, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       transform a neighbor into a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_255] Kael'thas Sunstrider - COST:6 [ATK:4/HP:7]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Every third spell you cast each turn costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_714] Frozen Shadoweaver - COST:3 [ATK:4/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> an enemy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("BT_714", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_715] Bonechewer Brawler - COST:2 [ATK:2/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> Whenever this minion takes damage,
    //       gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BT_715e", EntityType::SOURCE) };
    cards.emplace("BT_715", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_716] Bonechewer Vanguard - COST:7 [ATK:4/HP:10]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> Whenever this minion takes damage,
    //       gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BT_716e", EntityType::SOURCE) };
    cards.emplace("BT_716", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_717] Burrowing Scorpid - COST:4 [ATK:5/HP:2]
    // - Race: Beast, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    //       If that kills the target, gain <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_720] Ruststeed Raider - COST:5 [ATK:1/HP:8]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Rush</b>
    //       <b>Battlecry:</b> Gain +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_721] Blistering Rot - COST:3 [ATK:1/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a Rot with stats equal to this minion's.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_722] Guardian Augmerchant - COST:1 [ATK:2/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion and
    //       give it <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_722", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_723] Rocket Augmerchant - COST:1 [ATK:2/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion and
    //       give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<SetGameTagTask>(EntityType::TARGET, GameTag::RUSH, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_723", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_724] Ethereal Augmerchant - COST:1 [ATK:2/HP:1]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion and
    //       give it <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::SPELLPOWER, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BT_724", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_726] Dragonmaw Sky Stalker - COST:6 [ATK:5/HP:6]
    // - Race: Dragon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/4 Dragonrider.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_726t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_726", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_727] Soulbound Ashtongue - COST:1 [ATK:1/HP:4]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       also deal that amount to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_728] Disguised Wanderer - COST:4 [ATK:3/HP:3]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 9/1 Inquisitor.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_728t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_728", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_729] Waste Warden - COST:5 [ATK:3/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to a minion and
    //       all others of the same minion type.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_730] Overconfident Orc - COST:3 [ATK:1/HP:6]
    // - Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> While at full Health, this has +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_731] Infectious Sporeling - COST:1 [ATK:1/HP:2]
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this damages a minion,
    //       turn it into an Infectious Sporeling.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_732] Scavenging Shivarra - COST:6 [ATK:6/HP:3]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 6 damage randomly split
    //       among all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_733] Mo'arg Artificer - COST:2 [ATK:2/HP:5]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Epic
    // --------------------------------------------------------
    // Text: All minions take double damage from spells.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_734] Supreme Abyssal - COST:8 [ATK:12/HP:12]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't attack heroes.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_735] Al'ar - COST:5 [ATK:7/HP:3]
    // - Race: Elemental, Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle</b>: Summon a 0/3 Ashes of Al'ar
    //       that resurrects this minion on your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_737] Maiev Shadowsong - COST:4 [ATK:4/HP:3]
    // - Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion.
    //       It goes <b>Dormant</b> for 2 turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_850] Magtheridon - COST:4 [ATK:12/HP:12]
    // - Race: Demon, Set: BLACK_TEMPLE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Dormant</b>.
    //       <b>Battlecry:</b> Summon three 1/3 enemy Warders.
    //       When they die, destroy all minions and awaken.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [BT_008t] Impcaster - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_008t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_010e] Felfin Fueled - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_010e"));
    cards.emplace("BT_010e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_011e] Judgment of Justice - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetBaseHealth(1)));
    cards.emplace("BT_011e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_020e] Aldor Attendant - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_026e] Aldor Truthseeker - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_113e] Totemly Awesome - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_113e"));
    cards.emplace("BT_113e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_126e] Shadowy Construct - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Destroyed {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_126e2] Vengeful Spirit - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_129e] Mitosis - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_140e] Worg-mounted - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_155t] Felcracked Colossus - COST:7 [ATK:7/HP:7]
    // - Race: Elemental, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_155t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_159t] Huntress - COST:1 [ATK:1/HP:1]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_159t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_160e] Rustsworn Pact - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Demon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("BT_160t", SummonSide::DEATHRATTLE));
    cards.emplace("BT_160e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_160t] Rusted Devil - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_160t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_187e] Death's Dance - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Your attacks ignore <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_187e2] Death's Dance - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Kayn is letting this ignore <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_196e] Come Closer - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Drawn this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_205e] Scrapmetal Claws - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_205e"));
    cards.emplace("BT_205e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_213e] Pack Tactics - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_213e"));
    cards.emplace("BT_213e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_255e] Sunstrider - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_302e] Dark Portal - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (5) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(5)));
    cards.emplace("BT_302e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_309e] Black Harvest - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_496e] Finned and Furious - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_496e"));
    cards.emplace("BT_496e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_601e] Embrace Power - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(3)));
    cards.emplace("BT_601e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_711e] Stunned - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_715e] Brawling - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::AttackN(2)));
    cards.emplace("BT_715e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_716e] Victorious - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::AttackN(2)));
    cards.emplace("BT_716e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_720e] Ride Eternal - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_721t] Living Rot - COST:1 [ATK:1/HP:1]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_724e] Ethereal Augment - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_726t] Dragonrider - COST:3 [ATK:3/HP:4]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_726t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_728t] Rustsworn Inquisitor - COST:4 [ATK:9/HP:1]
    // - Race: Demon, Set: BLACK_TEMPLE
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_728t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BT_735t] Ashes of Al'ar - COST:1 [ATK:0/HP:3]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: At the start of your turn, transform this into Al'ar.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_737e] Imprisoned - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 2 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BT_850e] Imprisoned - COST:0
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken after 3 Warders die.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BT_850t] Hellfire Warder - COST:1 [ATK:1/HP:3]
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: (Magtheridon will destroy all minions and awaken
    //       after 3 Warders die.)
    // --------------------------------------------------------
}

void BlackTempleCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
