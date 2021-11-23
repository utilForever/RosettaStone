// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/VanillaCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;

void VanillaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void VanillaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_CS2_102_H3] Armor Up! - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_CS2_102_H3", CardDef(power));

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_EX1_tk33] INFERNO! - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 6/6 Infernal.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("VAN_EX1_tk34"));
    cards.emplace(
        "VAN_EX1_tk33",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_HERO_01bp] Armor Up! - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_HERO_01bp", CardDef(power));

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_HERO_01bp2] Tank Up! - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 4 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cards.emplace("VAN_HERO_01bp2", CardDef(power));

    // ------------------------------------ HERO_POWER - SHAMAN
    // [VAN_HERO_02bp] Totemic Call - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a random Totem.
    // --------------------------------------------------------
    // Entourage: VAN_CS2_050, VAN_CS2_051, VAN_CS2_052, VAN_NEW1_009
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<FuncNumberTask>([](Playable* playable) {
        auto minions = playable->player->GetFieldZone()->GetAll();
        std::vector<Card*> totemCards;
        totemCards.reserve(4);

        for (const auto& id : playable->card->entourages)
        {
            bool exist = false;
            for (const auto& minion : minions)
            {
                if (id == minion->card->id)
                {
                    exist = true;
                    break;
                }
            }

            if (!exist)
            {
                totemCards.emplace_back(Cards::FindCardByID(id));
            }
        }

        if (totemCards.empty())
        {
            return 0;
        }

        const auto idx = Random::get<std::size_t>(0, totemCards.size() - 1);
        Playable* totem =
            Entity::GetFromCard(playable->player, totemCards[idx]);
        playable->player->GetFieldZone()->Add(dynamic_cast<Minion*>(totem));

        return 0;
    }));
    cards.emplace(
        "VAN_HERO_02bp",
        CardDef(power,
                PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 },
                          { PlayReq::REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY, 0 } },
                ChooseCardIDs{},
                Entourages{ "VAN_CS2_050", "VAN_CS2_051", "VAN_CS2_052",
                            "VAN_NEW1_009" }));

    // ------------------------------------ HERO_POWER - SHAMAN
    // [VAN_HERO_02bp2] Totemic Slam - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a Totem of your choice.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::BASIC_TOTEM_CLASSIC, 4));
    cards.emplace(
        "VAN_HERO_02bp2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ------------------------------------- HERO_POWER - ROGUE
    // [VAN_HERO_03bp] Dagger Mastery - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 1/2 Dagger.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<WeaponTask>("VAN_CS2_082"));
    cards.emplace("VAN_HERO_03bp", CardDef(power));

    // ------------------------------------- HERO_POWER - ROGUE
    // [VAN_HERO_03bp2] Poisoned Daggers - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 2/2 Weapon.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<WeaponTask>("AT_132_ROGUEt"));
    cards.emplace("VAN_HERO_03bp2", CardDef(power));

    // ----------------------------------- HERO_POWER - PALADIN
    // [VAN_HERO_04bp] Reinforce - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_101t", SummonSide::DEFAULT));
    cards.emplace(
        "VAN_HERO_04bp",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ----------------------------------- HERO_POWER - PALADIN
    // [VAN_HERO_04bp2] The Silver Hand - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon two 1/1 Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_101t", 2, SummonSide::DEFAULT));
    cards.emplace(
        "VAN_HERO_04bp2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ------------------------------------ HERO_POWER - HUNTER
    // [VAN_HERO_05bp] Steady Shot - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_STEADY_SHOT = 0
    // - REQ_MINION_OR_ENEMY_HERO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, false));
    cards.emplace(
        "VAN_HERO_05bp",
        CardDef(power, PlayReqs{ { PlayReq::REQ_STEADY_SHOT, 0 },
                                 { PlayReq::REQ_MINION_OR_ENEMY_HERO, 0 } }));

    // ------------------------------------ HERO_POWER - HUNTER
    // [VAN_HERO_05bp2] Ballista Shot - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_STEADY_SHOT = 0
    // - REQ_MINION_OR_ENEMY_HERO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, false));
    cards.emplace(
        "VAN_HERO_05bp2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_STEADY_SHOT, 0 },
                                 { PlayReq::REQ_MINION_OR_ENEMY_HERO, 0 } }));

    // ------------------------------------- HERO_POWER - DRUID
    // [VAN_HERO_06bp] Shapeshift - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn. +1 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_017o", EntityType::HERO));
    power.AddPowerTask(std::make_shared<ArmorTask>(1));
    cards.emplace("VAN_HERO_06bp", CardDef(power));

    // ------------------------------------- HERO_POWER - DRUID
    // [VAN_HERO_06bp2] Dire Shapeshift - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn. +2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>("AT_132_DRUIDe",
                                                            EntityType::HERO));
    power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_HERO_06bp2", CardDef(power));

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_HERO_07bp] Life Tap - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card and take 2 damage.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 2, false));
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_HERO_07bp", CardDef(power));

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_HERO_07bp2] Soul Tap - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_HERO_07bp2", CardDef(power));

    // -------------------------------------- HERO_POWER - MAGE
    // [VAN_HERO_08bp] Fireblast - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, false));
    cards.emplace(
        "VAN_HERO_08bp",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // -------------------------------------- HERO_POWER - MAGE
    // [VAN_HERO_08bp2] Fireblast Rank 2 - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, false));
    cards.emplace(
        "VAN_HERO_08bp2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------ HERO_POWER - PRIEST
    // [VAN_HERO_09bp] Lesser Heal - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 2 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 2));
    cards.emplace(
        "VAN_HERO_09bp",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------ HERO_POWER - PRIEST
    // [VAN_HERO_09bp2] Heal - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 4 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 4));
    cards.emplace(
        "VAN_HERO_09bp2",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [VAN_HERO_10bp] Demon Claws - COST:1
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>("VAN_HERO_10bpe",
                                                            EntityType::HERO));
    cards.emplace("VAN_HERO_10bp", CardDef(power));

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [VAN_HERO_10bp2] Demon's Bite - COST:1
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>("VAN_HERO_10pe2",
                                                            EntityType::HERO));
    cards.emplace("VAN_HERO_10bp2", CardDef(power));
}

void VanillaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_005] Claw - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Gain 2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(2));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_005o", EntityType::HERO));
    cards.emplace("VAN_CS2_005", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_007] Healing Touch - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore 8 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 8));
    cards.emplace(
        "VAN_CS2_007",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_008] Moonfire - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cards.emplace(
        "VAN_CS2_008",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_009] Mark of the Wild - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Taunt</b> and +2/+2.<i>
    //       (+2 Attack/+2 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_CS2_009e", EntityType::TARGET));
    cards.emplace(
        "VAN_CS2_009",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_011] Savage Roar - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your characters +2 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_011o", EntityType::FRIENDS));
    cards.emplace("VAN_CS2_011", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_012] Swipe - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage to an enemy and 1 damage
    //       to all other enemies.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES_NOTARGET, 1, true));
    cards.emplace("VAN_CS2_012",
                  CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                           { PlayReq::REQ_ENEMY_TARGET, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_013] Wild Growth - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ManaCrystalTask>(1, false));
    cards.emplace("VAN_CS2_013", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [VAN_CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_232", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_154] Wrath - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 3 damage to a minion;
    //       or 1 damage and draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_154",
                  CardDef(power,
                          PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                    { PlayReq::REQ_MINION_TARGET, 0 } },
                          ChooseCardIDs{ "VAN_EX1_154a", "VAN_EX1_154b" }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_155] Mark of Nature - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give a minion +4 Attack;
    //       or +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_155",
                  CardDef(power,
                          PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                    { PlayReq::REQ_MINION_TARGET, 0 } },
                          ChooseCardIDs{ "VAN_EX1_155a", "VAN_EX1_155b" }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_158] Soul of the Forest - COST:4
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions
    //       "<b>Deathrattle:</b> Summon a 2/2 Treant."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_EX1_158e", EntityType::MINIONS));
    cards.emplace("VAN_EX1_158", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_160] Power of the Wild - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your minions +1/+1;
    //       or Summon a 3/2 Panther.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_161] Naturalize - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion. Your opponent draws 2 cards.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_164] Nourish - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Gain 2 Mana Crystals;
    //       or Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_165] Druid of the Claw - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> <b>Charge</b>;
    //       or +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_166] Keeper of the Grove - COST:4 [ATK:2/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 2 damage;
    //       or <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_169] Innervate - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals this turn only.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_173] Starfire - COST:6
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 5 damage. Draw a card.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_178] Ancient of War - COST:7 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> +5 Attack;
    //       or +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_570] Bite - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn. Gain 4 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_571] Force of Nature - COST:6
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon three 2/2 Treants with <b>Charge</b>
    //       that die at the end of the turn.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_573] Cenarius - COST:9 [ATK:5/HP:8]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your other minions +2/+2;
    //       or Summon two 2/2 Treants with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_578] Savagery - COST:1
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal damage equal to your hero's Attack to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_007] Starfall - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 5 damage to a minion;
    //       or 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_NEW1_008] Ancient of Lore - COST:7 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Draw 2 cards;
    //       or Restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [VAN_CS2_009e] Mark of the Wild - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("VAN_CS2_009e"));
    cards.emplace("VAN_CS2_009e", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_154a] Solar Wrath - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cards.emplace(
        "VAN_EX1_154a",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_154b] Nature's Wrath - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace(
        "VAN_EX1_154b",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_155a] Tiger's Fury - COST:3
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155ae", EntityType::TARGET));
    cards.emplace(
        "VAN_EX1_155a",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_155b] Thick Hide - COST:3
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155be", EntityType::TARGET));
    cards.emplace(
        "VAN_EX1_155b",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------ ENCHANTMENT - DRUID
    // [VAN_EX1_158e] Soul of the Forest - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Treant.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_158t", SummonSide::DEFAULT));
    cards.emplace("VAN_EX1_158e", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_160a] Summon a Panther - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Summon a 3/2 Panther.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_160b] Leader of the Pack - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_164a] Rampant Growth - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_164b] Enrich - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_165a] Cat Form - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_165b] Bear Form - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_165t1] Druid of the Claw - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_165t2] Druid of the Claw - COST:5 [ATK:4/HP:6]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_166a] Moonfire - COST:4
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_166b] Dispel - COST:4
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_178a] Rooted - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_178b] Uproot - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_573a] Demigod's Favor - COST:9
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Give your other minions +2/+2.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_573b] Shan'do's Lesson - COST:9
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants with <b>Taunt</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_tk9] Treant - COST:1 [ATK:2/HP:2]
    // - Set: VANILLA
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_tk9b] Treant - COST:1 [ATK:2/HP:2]
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_007a] Stellar Drift - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_007b] Starlord - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_008a] Ancient Teachings - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_008b] Ancient Secrets - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [VAN_CS2_084] Hunter's Mark - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Health to 1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_CS2_237] Starving Buzzard - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever you summon a Beast, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_DS1_070] Houndmaster - COST:4 [ATK:4/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast +2/+2
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other Beasts have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_DS1_178] Tundra Rhino - COST:5 [ATK:2/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your Beasts have <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_183] Multi-Shot - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to two random enemy minions.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_184] Tracking - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Look at the top 3 cards of your deck.
    //       Draw one and discard the others.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_185] Arcane Shot - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [VAN_DS1_188] Gladiator's Longbow - COST:7
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_531] Scavenging Hyena - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly Beast dies, gain +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_533] Misdirection - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks your hero,
    //       instead it attacks another random character.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [VAN_EX1_536] Eaglehorn Bow - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a <b>Secret</b> is revealed,
    //       gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_537] Explosive Shot - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion and 2 damage
    //       to adjacent ones.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_538] Unleash the Hounds - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: For each enemy minion,
    //       summon a 1/1 Hound with <b>Charge</b>.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_539] Kill Command - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage. If you control a Beast,
    //       deal 5 damage instead.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_543] King Krush - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_544] Flare - COST:1
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: All minions lose <b>Stealth</b>.
    //       Destroy all enemy <b>Secrets</b>. Draw a card.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_549] Bestial Wrath - COST:1
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a Beast +2 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_554] Snake Trap - COST:2
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon three 1/1 Snakes.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_609] Snipe - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       deal 4 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_610] Explosive Trap - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       deal 2 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_611] Freezing Trap - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       return it to its owner's hand. It costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_617] Deadly Shot - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_NEW1_031] Animal Companion - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon a random Beast Companion.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_554t] Snake - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_032] Misha - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_033] Leokk - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_034] Huffer - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_022] Polymorph - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion into a 1/1 Sheep.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_023] Arcane Intellect - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_024] Frostbolt - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to a character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_025] Arcane Explosion - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_026] Frost Nova - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_027] Mirror Image - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon two 0/2 minions with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_028] Blizzard - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions
    //       and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_029] Fireball - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 6 damage.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_031] Ice Lance - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a character.
    //       If it was already <b>Frozen</b>,
    //       deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_032] Flamestrike - COST:7
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage to all enemy minions.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_EX1_274] Ethereal Arcanist - COST:4 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you control a <b>Secret</b> at the end of your turn,
    //       gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_275] Cone of Cold - COST:4
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion and the minions next to it,
    //       and deal 1 damage to them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_277] Arcane Missiles - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage randomly split
    //       among all enemy characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_279] Pyroblast - COST:10
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 10 damage.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_287] Counterspell - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       <b>Counter</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_289] Ice Barrier - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> As soon as your hero is attacked,
    //       gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_294] Mirror Entity - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent plays a minion,
    //       summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_295] Ice Block - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero takes fatal damage,
    //       prevent it and become <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_EX1_559] Archmage Antonidas - COST:7 [ATK:5/HP:7]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       add a 'Fireball' spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_594] Vaporize - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a minion attacks your hero,
    //       destroy it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_EX1_608] Sorcerer's Apprentice - COST:2 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your spells cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_EX1_612] Kirin Tor Mage - COST:3 [ATK:4/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next <b>Secret</b>
    //       you play this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_NEW1_012] Mana Wyrm - COST:1 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [VAN_tt_010] Spellbender - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy casts a spell on a minion,
    //       summon a 1/3 as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [VAN_CS2_mirror] Mirror Image - COST:0 [ATK:0/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [VAN_tt_010a] Spellbender - COST:0 [ATK:1/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
}

void VanillaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_087] Blessing of Might - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [VAN_CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore #6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_089] Holy Light - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore 6 Health.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_CS2_091] Light's Justice - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_092] Blessing of Kings - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_093] Consecration - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_094] Hammer of Wrath - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage. Draw a card.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_CS2_097] Truesilver Champion - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_130] Noble Sacrifice - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks,
    //       summon a 2/1 Defender as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_132] Eye for an Eye - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero takes damage,
    //       deal that much damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_136] Redemption - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       return it to life with 1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_349] Divine Favor - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw cards until you have as many in hand
    //       as your opponent.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_354] Lay on Hands - COST:8
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Restore #8 Health. Draw 3 cards.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_355] Blessed Champion - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Double a minion's Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_360] Humility - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Attack to 1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_362] Argent Protector - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_363] Blessing of Wisdom - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Whenever it attacks, draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_365] Holy Wrath - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card and deal damage equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_EX1_366] Sword of Justice - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       give it +1/+1 and this loses 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_371] Hand of Protection - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_379] Repentance - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       reduce its Health to 1.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change an enemy minion's Attack to 1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
    //       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_384] Avenging Wrath - COST:6
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 8 damage randomly split
    //       among all enemy characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_619] Equality - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Change the Health of all minions to 1.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [VAN_CS2_101t] Silver Hand Recruit - COST:1 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_101t", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_130a] Defender - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
}

void VanillaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_112] Holy Nova - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    //       Restore 2 Health to all friendly characters.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_113] Mind Control - COST:10
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Take control of an enemy minion.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_129] Inner Fire - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_130] Holy Smite - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_003] Mind Vision - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Put a copy of a random card in your opponent's
    //       hand into your hand.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_004] Power Word: Shield - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +2 Health. Draw a card.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_234] Shadow Word: Pain - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 3 or less Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion is healed, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_236] Divine Spirit - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Double a minion's Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_DS1_233] Mind Blast - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_091] Cabal Shadow Priest - COST:6 [ATK:4/HP:5]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of an enemy minion
    //       that has 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_332] Silence - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_334] Shadow Madness - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Gain control of an enemy minion with 3 or
    //       less Attack until end of turn.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_335] Lightspawn - COST:4 [ATK:0/HP:5]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: This minion's Attack is always equal to its Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_339] Thoughtsteal - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Copy 2 cards in your opponent's deck and
    //       add them to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_341] Lightwell - COST:2 [ATK:0/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, restore 3 Health
    //       to a damaged friendly character.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_345] Mindgames - COST:4
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put a copy of a random minion from
    //       your opponent's deck into the battlefield.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Double the damage and healing of
    //       your spells and Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your cards and powers that restore Health
    //       now deal damage instead.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_621] Circle of Healing - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore #4 Health to all minions.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_622] Shadow Word: Death - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 5 or more Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_623] Temple Enforcer - COST:6 [ATK:6/HP:6]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_624] Holy Fire - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage. Restore 5 Health to your hero.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_625] Shadowform - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power becomes 'Deal 2 damage.'
    //       If already in Shadowform: 3 damage.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_626] Mass Dispel - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Silence</b> all enemy minions. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_345t] Shadow of Nothing - COST:0 [ATK:0/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Mindgames whiffed! Your opponent had no minions!
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [VAN_EX1_tk31] Mind Controlling - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - SUMMONED = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [VAN_HERO_09e1] Lesser Fortitude - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_072] Backstab - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to an undamaged minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_073] Cold Blood - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2 Attack.
    //       <b>Combo:</b> +4 Attack instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_074] Deadly Poison - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your weapon +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_075] Sinister Strike - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to the enemy hero.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_076] Assassinate - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy an enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_077] Sprint - COST:7
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_CS2_080] Assassin's Blade - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_233] Blade Flurry - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy your weapon and deal its damage
    //       to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_124] Eviscerate - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Combo:</b> Deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_126] Betrayal - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Force an enemy minion to deal its damage
    //       to the minions next to it.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_128] Conceal - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_129] Fan of Knives - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions. Draw a card.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_EX1_133] Perdition's Blade - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    //       <b>Combo:</b> Deal 2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_137] Headcrack - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to the enemy hero.
    //       <b>Combo:</b> Return this to your hand next turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_144] Shadowstep - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_145] Preparation - COST:0
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_278] Shiv - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage. Draw a card.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>.
    //       Destroy any minion damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_581] Sap - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Return an enemy minion to your opponent's hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_613] Edwin VanCleef - COST:3 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +2/+2 for each card
    //       played earlier this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_NEW1_004] Vanish - COST:6
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Return a minion to its owner's hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [VAN_NEW1_014] Master of Disguise - COST:4 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_CS2_082] Wicked Knife - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_082", CardDef(power));

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [VAN_EX1_145o] Preparation - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_037] Frost Shock - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to an enemy character and
    //       <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_038] Ancestral Spirit - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a minion. When that minion is destroyed,
    //       return it to the battlefield.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_039] Windfury - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Windfury</b>.
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_041] Ancestral Healing - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_045] Rockbiter Weapon - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly character +3 Attack this turn.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_046] Bloodlust - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your minions +3 Attack this turn.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_053] Far Sight - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a card. That card costs (3) less.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_238] Lightning Bolt - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_241] Lava Burst - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_244] Totemic Might - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your Totems +2 Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_245] Earth Shock - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion, then deal 1 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_246] Hex - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [VAN_EX1_247] Stormforged Axe - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_248] Feral Spirit - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b><b>Overload</b>:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_251] Forked Lightning - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to 2 random enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_258] Unbound Elemental - COST:3 [ATK:3/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a card with <b>Overload</b>, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_259] Lightning Storm - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2-3 damage to all enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:3]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Adjacent minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [VAN_EX1_567] Doomhammer - COST:5
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // - WINDFURY = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_050] Searing Totem - COST:1 [ATK:1/HP:1]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_050", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_051] Stoneclaw Totem - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_051", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_052] Wrath of Air Totem - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_052", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_tk11] Spirit Wolf - COST:2 [ATK:2/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [VAN_HERO_02e2] Strength of Earth - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_NEW1_009] Healing Totem - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 1 Health to all friendly minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("VAN_NEW1_009", CardDef(power));
}

void VanillaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_057] Shadow Bolt - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
    // - Race: Demon, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_061] Drain Life - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage. Restore 2 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_062] Hellfire - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to all characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::ALL, 3, true));
    cards.emplace("VAN_CS2_062", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_063] Corruption - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Choose an enemy minion.
    //       At the start of your turn, destroy it.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_301] Felguard - COST:3 [ATK:3/HP:5]
    // - Race: Demon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Destroy one of your Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_302] Mortal Coil - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion. If that kills it,
    //       draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_303] Shadowflame - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a friendly minion and deal its Attack damage
    //       to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_304] Void Terror - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy both adjacent minions
    //       and gain their Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_306] Felstalker - COST:2 [ATK:4/HP:3]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_308] Soulfire - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage. Discard a random card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_309] Siphon Soul - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore 3 Health to your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
    // - Race: Demon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Discard two random cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_312] Twisting Nether - COST:8
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
    // - Race: Demon, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_315] Summoning Portal - COST:4 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (2) less, but not less than (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_316] Power Overwhelming - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a friendly minion +4/+4 until end of turn.
    //       Then, it dies. Horribly.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_317] Sense Demons - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 Demons from your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_319] Flame Imp - COST:1 [ATK:3/HP:2]
    // - Race: Demon, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_320] Bane of Doom - COST:5
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to a character.
    //       If that kills it, summon a random Demon.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_323] Lord Jaraxxus - COST:9 [ATK:3/HP:15]
    // - Race: Demon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your hero and
    //       replace it with Lord Jaraxxus.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ReplaceHeroTask>(
        "EX1_323h", "VAN_EX1_tk33", "EX1_323w"));
    cards.emplace("VAN_EX1_323", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_596] Demonfire - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it's a friendly Demon, give it +2/+2 instead.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_NEW1_003] Sacrificial Pact - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a Demon. Restore 5 Health to your hero.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_tk34] Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Set: VANILLA
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_tk34", CardDef(power));
}

void VanillaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_103] Charge - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly minion +2 Attack and <b>Charge</b>.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_104] Rampage - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a damaged minion +3/+3.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_105] Heroic Strike - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_CS2_106] Fiery War Axe - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_108] Execute - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a damaged enemy minion.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_CS2_112] Arcanite Reaper - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_114] Cleave - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to two random enemy minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_084] Warsong Commander - COST:3 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever you summon a minion with 3 or less Attack,
    //       give it <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_391] Slam - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it survives, draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_392] Battle Rage - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card for each damaged friendly character.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_398] Arathi Weaponsmith - COST:4 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 2/2 weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_400] Whirlwind - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly minion takes damage,
    //       gain 1 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_407] Brawl - COST:5
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except one.
    //       <i>(chosen randomly)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_408] Mortal Strike - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    //       If you have 12 or less Health, deal 6 instead.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_409] Upgrade! - COST:1
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you have a weapon, give it +1/+1.
    //       Otherwise equip a 1/3 weapon.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_410] Shield Slam - COST:1
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion for each Armor you have.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_EX1_411] Gorehowl - COST:7
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Attacking a minion costs 1 Attack instead of 1 Durability.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b> <b>Enrage:</b> +6 Attack
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion and
    //       give it +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a minion takes damage, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_606] Shield Block - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 5 Armor. Draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_607] Inner Rage - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and give it +2 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [VAN_NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_NEW1_036] Commanding Shout - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    //       Draw a card.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [VAN_CS2_103e2] Charge - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Charge</b>.
    // --------------------------------------------------------
}

void VanillaCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void VanillaCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [VAN_HERO_10bpe] Demon Claws - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("VAN_HERO_10bpe"));
    cards.emplace("VAN_HERO_10bpe", CardDef(power));

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [VAN_HERO_10pe2] Demon's Bite - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("VAN_HERO_10pe2"));
    cards.emplace("VAN_HERO_10pe2", CardDef(power));
}

void VanillaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_122] Raid Leader - COST:3 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Charge</b> while you have a weapon equipped.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Squire.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_155] Archmage - COST:6 [ATK:4/HP:7]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
    // - Faction: Horde, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to HIMSELF.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_186] War Golem - COST:7 [ATK:7/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_188] Abusive Sergeant - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Boar.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_203] Ironbeak Owl - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> Your weapon has +2 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_222] Stormwind Champion - COST:7 [ATK:6/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each other friendly
    //       minion on the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (3) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_DS1_055] Darkscale Healer - COST:5 [ATK:4/HP:5]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health to
    //       all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a character is healed, gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_002] The Black Knight - COST:6 [ATK:4/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy minion
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, give another random
    //       friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_005] Big Game Hunter - COST:3 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion with 7
    //       or more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_006] Alarm-o-Bot - COST:3 [ATK:0/HP:3]
    // - Race: Mechanical, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       swap this minion with a random one in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +5 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_014] King Mukla - COST:3 [ATK:5/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent 2 Bananas.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Take control of a random
    //       enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_029] Leper Gnome - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
    // - Race: Dragon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Health for each card
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play a card, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_057] Ancient Brewmaster - COST:4 [ATK:5/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_058] Sunfury Protector - COST:2 [ATK:2/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
    // - Race: Murloc, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>. Has +1 Attack for each other Murloc
    //       on the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first minion you play each turn costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_080] Secretkeeper - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a <b>Secret</b> is played, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage randomly split
    //       between all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_083] Tinkmaster Overspark - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform another random minion
    //       into a 5/5 Devilsaur or a 1/1 Squirrel.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 4 or more
    //       minions, take control of one at random.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_089] Arcane Golem - COST:3 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Give your opponent a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_093] Defender of Argus - COST:4 [ATK:2/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions +1/+1
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_097] Abomination - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Deathrattle:</b> Deal 2 damage to all characters.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_100] Lorewalker Cho - COST:2 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever a player casts a spell,
    //       put a copy into the other player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_102] Demolisher - COST:3 [ATK:1/HP:4]
    // - Race: Mechanical, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all other Murlocs +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other card in your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_110] Cairne Bloodhoof - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/5 Baine Bloodhoof.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_112] Gelbin Mekkatorque - COST:6 [ATK:6/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon an AWESOME invention.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_116] Leeroy Jenkins - COST:4 [ATK:6/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Summon two 1/1 Whelps for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Adjacent minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy any minion damaged by this minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_249] Baron Geddon - COST:7 [ATK:7/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_283] Frost Elemental - COST:6 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> a character.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
    // - Race: Dragon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_298] Ragnaros the Firelord - COST:8 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't attack. At the end of your turn,
    //       deal 8 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CANT_ATTACK = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Enrage:</b> +3 Attack
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +3 Attack
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_412] Raging Worgen - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> <b>Windfury</b> and +1 Attack
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
    // - Race: Murloc, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: ALL other murlocs have +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: ALL other Murlocs have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a Murloc is summoned, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn, you have a 50% chance
    //       to draw an extra card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_558] Harrison Jones - COST:5 [ATK:5/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon
    //       and draw cards equal to its Durability.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_560] Nozdormu - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Players only have 15 seconds to take their turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_561] Alexstrasza - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set a hero's remaining Health to 15.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_562] Onyxia - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 1/1 Whelps until your side
    //       of the battlefield is full.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_563] Malygos - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +5</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_572] Ysera - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, add a Dream Card to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_577] The Beast - COST:6 [ATK:9/HP:7]
    // - Race: Beast, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/3 Finkle Einhorn
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_584] Ancient Mage - COST:4 [ATK:2/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions
    //       <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other minion on the battlefield.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_590] Blood Knight - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> All minions lose <b>Divine Shield</b>.
    //       Gain +3/+3 for each Shield lost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_595] Cult Master - COST:4 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly minion dies, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_597] Imp Master - COST:3 [ATK:1/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to this minion and summon a 1/1 Imp.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_614] Illidan Stormrage - COST:6 [ATK:7/HP:5]
    // - Race: Demon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you play a card,
    //       summon a 2/1 Flame of Azzinoth.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_616] Mana Wraith - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: All minions cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage your hero has taken.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_016] Captain's Parrot - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Pirate from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Murloc and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
    // - Race: Pirate, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain Attack equal to the Attack
    //       of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_019] Knife Juggler - COST:2 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, destroy all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_022] Dread Corsair - COST:4 [ATK:3/HP:3]
    // - Race: Pirate, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less per Attack of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_023] Faerie Dragon - COST:2 [ATK:3/HP:2]
    // - Race: Dragon, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_024] Captain Greenskin - COST:5 [ATK:5/HP:4]
    // - Race: Pirate, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_025] Bloodsail Corsair - COST:1 [ATK:1/HP:2]
    // - Race: Pirate, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Remove 1 Durability from
    //       your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a 1/1 Violet Apprentice.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Pirates have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_029] Millhouse Manastorm - COST:2 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy spells cost (0) next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_030] Deathwing - COST:10 [ATK:12/HP:12]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other minions
    //       and discard your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_037] Master Swordsmith - COST:2 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_038] Gruul - COST:8 [ATK:7/HP:7]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of each turn, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_040] Hogger - COST:6 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a 2/2 Gnoll with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_041] Stampeding Kodo - COST:5 [ATK:3/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy minion
    //       with 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_PRO_001] Elite Tauren Chieftain - COST:5 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give both players the power to ROCK!
    //       (with a Power Chord card)
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_tt_004] Flesheating Ghoul - COST:3 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void VanillaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_152] Squire - COST:1 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_CS2_222o] Might of Stormwind - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_boar] Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_tk1] Sheep - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_DREAM_05e] Nightmare - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Has +5/+5, but will be destroyed soon.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_110t] Baine Bloodhoof - COST:4 [ATK:4/HP:5]
    // - Set: VANILLA
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_EX1_145e] Preparation - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_506a] Murloc Scout - COST:0 [ATK:1/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_EX1_507e] Mrgglaargl! - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2/+1 from Murloc Warleader.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_598] Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: VANILLA
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_finkle] Finkle Einhorn - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_tk28] Squirrel - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_tk29] Devilsaur - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_026t] Violet Apprentice - COST:0 [ATK:1/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_NEW1_027e] Yarrr! - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_skele11] Skeleton - COST:1 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b></b>
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_skele21] Damaged Golem - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Set: VANILLA
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_TU4e_002t] Flame of Azzinoth - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
}

void VanillaCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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