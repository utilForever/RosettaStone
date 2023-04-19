// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/VanillaCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void VanillaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void VanillaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_CS2_102_H3] Armor Up! - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_CS2_102_H3", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_EX1_tk33] INFERNO! - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 6/6 Infernal.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("VAN_EX1_tk34"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_tk33", cardDef);

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_HERO_01bp] Armor Up! - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_HERO_01bp", cardDef);

    // ----------------------------------- HERO_POWER - WARRIOR
    // [VAN_HERO_01bp2] Tank Up! - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 4 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cards.emplace("VAN_HERO_01bp2", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            const auto minions = playable->player->GetFieldZone()->GetAll();
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
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 },
                  { PlayReq::REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY, 0 } };
    cardDef.property.entourages = Entourages{ "VAN_CS2_050", "VAN_CS2_051",
                                              "VAN_CS2_052", "VAN_NEW1_009" };
    cards.emplace("VAN_HERO_02bp", cardDef);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [VAN_HERO_02bp2] Totemic Slam - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a Totem of your choice.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::BASIC_TOTEM_CLASSIC, 4));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_HERO_02bp2", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [VAN_HERO_03bp] Dagger Mastery - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 1/2 Dagger.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("VAN_CS2_082"));
    cards.emplace("VAN_HERO_03bp", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [VAN_HERO_03bp2] Poisoned Daggers - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 2/2 Weapon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("AT_132_ROGUEt"));
    cards.emplace("VAN_HERO_03bp2", cardDef);

    // ----------------------------------- HERO_POWER - PALADIN
    // [VAN_HERO_04bp] Reinforce - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_101t", SummonSide::DEFAULT));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_HERO_04bp", cardDef);

    // ----------------------------------- HERO_POWER - PALADIN
    // [VAN_HERO_04bp2] The Silver Hand - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon two 1/1 Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_101t", 2, SummonSide::DEFAULT));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_HERO_04bp2", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, false));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_STEADY_SHOT, 0 },
                  { PlayReq::REQ_MINION_OR_ENEMY_HERO, 0 } };
    cards.emplace("VAN_HERO_05bp", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, false));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_STEADY_SHOT, 0 },
                  { PlayReq::REQ_MINION_OR_ENEMY_HERO, 0 } };
    cards.emplace("VAN_HERO_05bp2", cardDef);

    // ------------------------------------- HERO_POWER - DRUID
    // [VAN_HERO_06bp] Shapeshift - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn. +1 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_017o", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(1));
    cards.emplace("VAN_HERO_06bp", cardDef);

    // ------------------------------------- HERO_POWER - DRUID
    // [VAN_HERO_06bp2] Dire Shapeshift - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn. +2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "AT_132_DRUIDe", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("VAN_HERO_06bp2", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_HERO_07bp] Life Tap - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card and take 2 damage.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 2, false));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_HERO_07bp", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [VAN_HERO_07bp2] Soul Tap - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_HERO_07bp2", cardDef);

    // -------------------------------------- HERO_POWER - MAGE
    // [VAN_HERO_08bp] Fireblast - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, false));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_HERO_08bp", cardDef);

    // -------------------------------------- HERO_POWER - MAGE
    // [VAN_HERO_08bp2] Fireblast Rank 2 - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, false));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_HERO_08bp2", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [VAN_HERO_09bp] Lesser Heal - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 2 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_HERO_09bp", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [VAN_HERO_09bp2] Heal - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 4 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 4));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_HERO_09bp2", cardDef);

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [VAN_HERO_10bp] Demon Claws - COST:1
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_HERO_10bpe", EntityType::HERO));
    cards.emplace("VAN_HERO_10bp", cardDef);

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [VAN_HERO_10bp2] Demon's Bite - COST:1
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_HERO_10pe2", EntityType::HERO));
    cards.emplace("VAN_HERO_10bp2", cardDef);
}

void VanillaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_005] Claw - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Gain 2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_005o", EntityType::HERO));
    cards.emplace("VAN_CS2_005", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_007] Healing Touch - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore 8 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 8));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_CS2_007", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_008] Moonfire - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_CS2_008", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_CS2_009e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_009", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_011] Savage Roar - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your characters +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_011o", EntityType::FRIENDS));
    cards.emplace("VAN_CS2_011", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES_NOTARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_CS2_012", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_CS2_013] Wild Growth - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsManaCrystalFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddCardTask>(EntityType::HAND,
                                                      "CS2_013t", 1) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<ManaCrystalTask>(1, false) }));
    cards.emplace("VAN_CS2_013", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [VAN_CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_232", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_154a", "VAN_EX1_154b" };
    cards.emplace("VAN_EX1_154", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_155a", "VAN_EX1_155b" };
    cards.emplace("VAN_EX1_155", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_EX1_158e", EntityType::MINIONS));
    cards.emplace("VAN_EX1_158", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_160a", "VAN_EX1_160b" };
    cards.emplace("VAN_EX1_160", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_161] Naturalize - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion. Your opponent draws 2 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_161", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_164a", "VAN_EX1_164b" };
    cards.emplace("VAN_EX1_164", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "OG_044a"));
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_165a", "VAN_EX1_165b" };
    cards.emplace("VAN_EX1_165", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_166a", "VAN_EX1_166b" };
    cards.emplace("VAN_EX1_166", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_169] Innervate - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals this turn only.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TempManaTask>(2));
    cards.emplace("VAN_EX1_169", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_173] Starfire - COST:6
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 5 damage. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_173", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_178a", "VAN_EX1_178b" };
    cards.emplace("VAN_EX1_178", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_570] Bite - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn. Gain 4 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_570e", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cards.emplace("VAN_EX1_570", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_571] Force of Nature - COST:6
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon three 2/2 Treants with <b>Charge</b>
    //       that die at the end of the turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_EX1_tk9b", 3, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_571", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_EX1_573a", "VAN_EX1_573b" };
    cards.emplace("VAN_EX1_573", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_578] Savagery - COST:1
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal damage equal to your hero's Attack to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_578", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_NEW1_007a", "VAN_NEW1_007b" };
    cards.emplace("VAN_NEW1_007", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cardDef.property.chooseCardIDs =
        ChooseCardIDs{ "VAN_NEW1_008a", "VAN_NEW1_008b" };
    cards.emplace("VAN_NEW1_008", cardDef);
}

void VanillaCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [VAN_CS2_009e] Mark of the Wild - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_CS2_009e"));
    cards.emplace("VAN_CS2_009e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_154a", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_154b", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155ae", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_155a", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155be", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_155b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [VAN_EX1_158e] Soul of the Forest - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Treant.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_158t", SummonSide::DEFAULT));
    cards.emplace("VAN_EX1_158e", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_160a] Summon a Panther - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Summon a 3/2 Panther.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_160t", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_160a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_160b] Leader of the Pack - COST:2
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_160be", EntityType::MINIONS));
    cards.emplace("VAN_EX1_160b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_164a] Rampant Growth - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(2, true));
    cards.emplace("VAN_EX1_164a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_164b] Enrich - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cards.emplace("VAN_EX1_164b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_165a] Cat Form - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "VAN_EX1_165t1"));
    cards.emplace("VAN_EX1_165a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_165b] Bear Form - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "VAN_EX1_165t2"));
    cards.emplace("VAN_EX1_165b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_165t1] Druid of the Claw - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_165t1", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [VAN_EX1_165t2] Druid of the Claw - COST:5 [ATK:4/HP:6]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_165t2", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_166a] Moonfire - COST:4
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_166a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_166b] Dispel - COST:4
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_166b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_178a] Rooted - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_178ae", EntityType::SOURCE));
    cards.emplace("VAN_EX1_178a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_178b] Uproot - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_178be", EntityType::SOURCE));
    cards.emplace("VAN_EX1_178b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_573a] Demigod's Favor - COST:9
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Give your other minions +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_573ae", EntityType::MINIONS_NOSOURCE));
    cards.emplace("VAN_EX1_573a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_EX1_573b] Shan'do's Lesson - COST:9
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants with <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("EX1_573t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("EX1_573t", SummonSide::LEFT) },
        1));
    cards.emplace("VAN_EX1_573b", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::SOURCE) };
    cards.emplace("VAN_EX1_tk9b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_007a] Stellar Drift - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cards.emplace("VAN_NEW1_007a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_007b] Starlord - COST:5
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_NEW1_007b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_008a] Ancient Teachings - COST:7
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cards.emplace("VAN_NEW1_008a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [VAN_NEW1_008b] Ancient Secrets - COST:7
    // - Set: VANILLA
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
    cards.emplace("VAN_NEW1_008b", cardDef);
}

void VanillaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_CS2_084] Hunter's Mark - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Health to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_084e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_084", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_CS2_237] Starving Buzzard - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever you summon a Beast, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_CS2_237", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DS1_070o", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 20 } };
    cards.emplace("VAN_DS1_070", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other Beasts have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "DS1_175o"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST));
    }
    cards.emplace("VAN_DS1_175", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::FIELD, "DS1_178e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST));
    }
    cards.emplace("VAN_DS1_178", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_183] Multi-Shot - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to two random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 3, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("VAN_DS1_183", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_184] Tracking - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Look at the top 3 cards of your deck.
    //       Draw one and discard the others.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](Playable* playable) {
            DeckZone* deck = playable->player->GetDeckZone();
            if (deck->IsEmpty())
            {
                return 0;
            }

            std::vector<int> ids;
            ids.reserve(3);

            for (int i = 0; i < 3 && deck->GetCount() != 0; ++i)
            {
                Playable* card = deck->GetTopCard();
                deck->Remove(card);
                ids.emplace_back(card->GetGameTag(GameTag::ENTITY_ID));
                playable->player->GetSetasideZone()->Add(card);
            }

            Generic::CreateChoice(playable->player, playable,
                                  ChoiceType::GENERAL, ChoiceAction::HAND, ids);

            return 0;
        }));
    cards.emplace("VAN_DS1_184", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_DS1_185] Arcane Shot - COST:1
    // - Set: VANILLA, Rarity: Free
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
    cards.emplace("VAN_DS1_185", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [VAN_DS1_188] Gladiator's Longbow - COST:7
    // - Set: VANILLA, Rarity: Epic
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
    cards.emplace("VAN_DS1_188", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_531] Scavenging Hyena - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly Beast dies, gain +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_531e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_531", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(
            EntityType::ALL,
            EntityTypeList{ EntityType::TARGET, EntityType::HERO }),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
            std::make_shared<SelfCondition>(SelfCondition::IsNotImmune()) }),
        std::make_shared<ConditionTask>(
            EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                                   SelfCondition::IsInZone(ZoneType::PLAY)) }),
        std::make_shared<FlagTask>(
            true,
            TaskList{ std::make_shared<ConditionTask>(
                EntityType::TARGET,
                SelfCondList{ std::make_shared<SelfCondition>(
                                  SelfCondition::IsInZone(ZoneType::PLAY)),
                              std::make_shared<SelfCondition>(
                                  SelfCondition::IsNotDead()) }) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<RandomTask>(EntityType::STACK, 1),
                      std::make_shared<ChangeAttackingTargetTask>(
                          EntityType::TARGET, EntityType::STACK) }))
    };
    cards.emplace("VAN_EX1_533", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_534t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("VAN_EX1_534", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [VAN_EX1_536] Eaglehorn Bow - COST:3 [ATK:3/HP:0]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a <b>Secret</b> is revealed,
    //       gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::SECRET_REVEALED));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_536e", EntityType::WEAPON) };
    cards.emplace("VAN_EX1_536", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_537] Explosive Shot - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion and 2 damage
    //       to adjacent ones.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_537", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_538] Unleash the Hounds - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: For each enemy minion,
    //       summon a 1/1 Hound with <b>Charge</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<SummonTask>("EX1_538t", SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_538", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_539] Kill Command - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage. If you control a Beast,
    //       deal 5 damage instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 5, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 3, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_539", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_543", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RevealStealthTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<MoveToGraveyardTask>(EntityType::ENEMY_SECRETS));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_544", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_549] Bestial Wrath - COST:1
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a Beast +2 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_549o", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_TARGET_WITH_RACE, 20 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_549", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsProposedDefender(CardType::MINION)),
                      std::make_shared<SelfCondition>(
                          SelfCondition::IsEventTargetFieldNotFull()) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("VAN_EX1_554t", 3) });
    cards.emplace("VAN_EX1_554", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true,
            ComplexTask::ActivateSecret(TaskList{
                std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }))
    };
    cards.emplace("VAN_EX1_609", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true) });
    cards.emplace("VAN_EX1_610", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<ReturnHandTask>(EntityType::TARGET),
                      std::make_shared<AddAuraEffectTask>(
                          Effects::AddCost(2), EntityType::TARGET) }))
    };
    cards.emplace("VAN_EX1_611", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_EX1_617] Deadly Shot - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("VAN_EX1_617", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [VAN_NEW1_031] Animal Companion - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon a random Beast Companion.
    // --------------------------------------------------------
    // Entourage: VAN_NEW1_032, VAN_NEW1_033, VAN_NEW1_034
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cardDef.property.entourages =
        Entourages{ "VAN_NEW1_032", "VAN_NEW1_033", "VAN_NEW1_034" };
    cards.emplace("VAN_NEW1_031", cardDef);
}

void VanillaCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [VAN_EX1_554t] Snake - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_554t", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_032] Misha - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_032", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_033] Leokk - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "NEW1_033o"));
    cards.emplace("VAN_NEW1_033", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [VAN_NEW1_034] Huffer - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_034", cardDef);
}

void VanillaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_022] Polymorph - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion into a 1/1 Sheep.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::TARGET, "VAN_CS2_tk1"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_022", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_023] Arcane Intellect - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cards.emplace("VAN_CS2_023", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_024] Frostbolt - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to a character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
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
    cards.emplace("VAN_CS2_024", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_025] Arcane Explosion - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cards.emplace("VAN_CS2_025", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_026] Frost Nova - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("VAN_CS2_026", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_027] Mirror Image - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon two 0/2 minions with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_mirror", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_CS2_027", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_028] Blizzard - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("VAN_CS2_028", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_029] Fireball - COST:4
    // - Set: VANILLA, Rarity: Free
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
    cards.emplace("VAN_CS2_029", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_031] Ice Lance - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a character.
    //       If it was already <b>Frozen</b>, deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_CS2_031", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_CS2_032] Flamestrike - COST:7
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 4, true));
    cards.emplace("VAN_CS2_032", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [VAN_CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_033", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsControllingSecret())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_274e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_274", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_275", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_277] Arcane Missiles - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage randomly split among all enemy characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        3, true));
    cards.emplace("VAN_EX1_277", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [VAN_EX1_279] Pyroblast - COST:10
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 10 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 10, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_279", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<SetGameTagTask>(
            EntityType::TARGET, GameTag::CANT_PLAY, 1) });
    cardDef.power.GetTrigger()->fastExecution = true;
    cards.emplace("VAN_EX1_287", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<ArmorTask>(8) });
    cards.emplace("VAN_EX1_289", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::EVENT_SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsNotUntouchable()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsOpFieldNotFull()) }),
        std::make_shared<FlagTask>(
            true,
            ComplexTask::ActivateSecret(TaskList{
                std::make_shared<SummonCopyTask>(EntityType::EVENT_SOURCE) }))
    };
    cards.emplace("VAN_EX1_294", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHeroFatalPreDamaged())
    };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<AddEnchantmentTask>("EX1_295o", EntityType::HERO) });
    cards.emplace("VAN_EX1_295", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddCardTask>(
        EntityType::HAND, "VAN_CS2_029") };
    cards.emplace("VAN_EX1_559", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) });
    cards.emplace("VAN_EX1_594", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [VAN_EX1_608] Sorcerer's Apprentice - COST:2 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your spells cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cards.emplace("VAN_EX1_608", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_612o", EntityType::PLAYER));
    cards.emplace("VAN_EX1_612", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [VAN_NEW1_012] Mana Wyrm - COST:1 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SPELLS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "NEW1_012o", EntityType::SOURCE) };
    cards.emplace("VAN_NEW1_012", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpellTargetingMinion())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(
                    SelfCondition::IsFieldNotFull()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsTagValue(GameTag::CANT_PLAY, 0)) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<SummonTask>("VAN_tt_010a",
                                                   SummonSide::SPELL, true),
                      std::make_shared<IncludeTask>(
                          EntityType::SOURCE, std::vector<EntityType>(), true),
                      std::make_shared<IncludeTask>(
                          EntityType::TARGET, std::vector<EntityType>(), true),
                      std::make_shared<FuncPlayableTask>(
                          [=](const std::vector<Playable*>& playables) {
                              playables[2]->SetCardTarget(
                                  playables[0]->GetGameTag(GameTag::ENTITY_ID));
                              return playables;
                          }) }))
    };
    cards.emplace("VAN_tt_010", cardDef);
}

void VanillaCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [VAN_CS2_mirror] Mirror Image - COST:0 [ATK:0/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_mirror", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [VAN_tt_010a] Spellbender - COST:0 [ATK:1/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_tt_010a", cardDef);
}

void VanillaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_087] Blessing of Might - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_087e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_087", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [VAN_CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 6));
    cards.emplace("VAN_CS2_088", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_089] Holy Light - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore 6 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 6));
    cards.emplace("VAN_CS2_089", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_CS2_091] Light's Justice - COST:1 [ATK:1/HP:0]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_091", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_092] Blessing of Kings - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_092e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_092", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_093] Consecration - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true));
    cards.emplace("VAN_CS2_093", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_CS2_094] Hammer of Wrath - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_CS2_094", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::HERO, 2) };
    cards.emplace("VAN_CS2_097", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("VAN_EX1_130a", SummonSide::SPELL, true),
        std::make_shared<ChangeAttackingTargetTask>(EntityType::TARGET,
                                                    EntityType::STACK) });
    cards.emplace("VAN_EX1_130", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<GetEventNumberTask>(),
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_HERO, true) });
    cards.emplace("VAN_EX1_132", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY, 1, true),
        std::make_shared<FuncPlayableTask>(
            [=](const std::vector<Playable*>& playables) {
                const auto target = dynamic_cast<Minion*>(playables[0]);

                if (!target)
                {
                    return std::vector<Playable*>{};
                }

                target->SetDamage(target->GetHealth() - 1);

                return std::vector<Playable*>{ target };
            }) });
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("VAN_EX1_136", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_349] Divine Favor - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw cards until you have as many in hand
    //       as your opponent.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            const int diffHands =
                playable->player->opponent->GetHandZone()->GetCount() -
                playable->player->GetHandZone()->GetCount();

            return diffHands > 0 ? diffHands : 0;
        }));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("VAN_EX1_349", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_354] Lay on Hands - COST:8
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Restore 8 Health. Draw 3 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 8));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_354", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_355] Blessed Champion - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Double a minion's Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_355e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_355", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_360] Humility - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Attack to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_360e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_360", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_EX1_362", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_363] Blessing of Wisdom - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Whenever it attacks, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_363e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_363", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_365] Holy Wrath - COST:5
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card and deal damage equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::STACK, GameTag::COST));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_365", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [VAN_EX1_366] Sword of Justice - COST:3 [ATK:1/HP:0]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       give it +1/+1 and this loses 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 5
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<AddEnchantmentTask>("EX1_366e", EntityType::TARGET),
        std::make_shared<DamageWeaponTask>(false)
    };
    cards.emplace("VAN_EX1_366", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_371] Hand of Protection - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_371", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::EVENT_SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsNotUntouchable()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(
                      TaskList{ std::make_shared<AddEnchantmentTask>(
                          "EX1_379e", EntityType::EVENT_SOURCE) }))
    };
    cards.emplace("VAN_EX1_379", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change an enemy minion's Attack to 1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_382e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_382", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<WeaponTask>("EX1_383t"));
    cards.emplace("VAN_EX1_383", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        8, true));
    cards.emplace("VAN_EX1_384", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [VAN_EX1_619] Equality - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Change the Health of all minions to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_619e", EntityType::ALL_MINIONS));
    cards.emplace("VAN_EX1_619", cardDef);
}

void VanillaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [VAN_CS2_101t] Silver Hand Recruit - COST:1 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_101t", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [VAN_EX1_130a] Defender - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_130a", cardDef);
}

void VanillaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_112] Holy Nova - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    //       Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 2));
    cards.emplace("VAN_CS1_112", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_113] Mind Control - COST:10
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Take control of an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ControlTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_CS1_113", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_129] Inner Fire - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
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
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "CS1_129e", EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS1_129", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS1_130] Holy Smite - COST:1
    // - Set: VANILLA, Rarity: Free
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
    cards.emplace("VAN_CS1_130", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_003] Mind Vision - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Put a copy of a random card in your opponent's
    //       hand into your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_HAND, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("VAN_CS2_003", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_004] Power Word: Shield - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +2 Health. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_004e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_004", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_234] Shadow Word: Pain - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 3 or less Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_MAX_ATTACK = 3
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_TARGET_MAX_ATTACK, 3 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_234", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [VAN_CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion is healed, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_CS2_235", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_CS2_236] Divine Spirit - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Double a minion's Health.
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
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "CS2_236e", EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_236", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_DS1_233] Mind Blast - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 5, true));
    cards.emplace("VAN_DS1_233", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_MAX_ATTACK = 2
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ControlTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_TARGET_MAX_ATTACK, 2 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_EX1_091", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_332] Silence - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_332", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_334] Shadow Madness - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Gain control of an enemy minion with 3 or
    //       less Attack until end of turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_TARGET_MAX_ATTACK = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ControlTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_334e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 },
                  { PlayReq::REQ_TARGET_MAX_ATTACK, 3 } };
    cards.emplace("VAN_EX1_334", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_335] Lightspawn - COST:4 [ATK:0/HP:5]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: This minion's Attack is always equal to its Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::SET, [=](Playable* playable) {
            return dynamic_cast<Minion*>(playable)->GetHealth();
        }));
    cards.emplace("VAN_EX1_335", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_339] Thoughtsteal - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Copy 2 cards in your opponent's deck and
    //       add them to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_DECK, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("VAN_EX1_339", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::FRIENDS),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<HealTask>(EntityType::STACK, 3)
    };
    cards.emplace("VAN_EX1_341", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_345] Mindgames - COST:4
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put a copy of a random minion from
    //       your opponent's deck into the battlefield.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsStackNum(1, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomTask>(EntityType::STACK, 1),
                        std::make_shared<CopyTask>(EntityType::STACK,
                                                   ZoneType::PLAY) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<SummonTask>("VAN_EX1_345t",
                                                      SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_345", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Double the damage and healing of
    //       your spells and Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::ADD, 1) }));
    cards.emplace("VAN_EX1_350", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your cards and powers that restore Health
    //       now deal damage instead.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::HEALING_DOES_DAMAGE,
                                             EffectOperator::SET, 1) }));
    cards.emplace("VAN_EX1_591", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_621] Circle of Healing - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 4 Health to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::ALL_MINIONS, 4));
    cards.emplace("VAN_EX1_621", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_622] Shadow Word: Death - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 5 or more Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 5
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_MIN_ATTACK, 5 } };
    cards.emplace("VAN_EX1_622", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_623] Temple Enforcer - COST:6 [ATK:6/HP:6]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_623e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_623", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_624] Holy Fire - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage. Restore 5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_624", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_625] Shadowform - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power becomes 'Deal 2 damage.'
    //       If already in Shadowform: 3 damage.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHeroPowerCard("EX1_625t")) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ChangeHeroPowerTask>("EX1_625t2") }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<ConditionTask>(
                      EntityType::SOURCE,
                      SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsHeroPowerCard("EX1_625t2")) }),
                  std::make_shared<FlagTask>(
                      false, TaskList{ std::make_shared<ChangeHeroPowerTask>(
                                 "EX1_625t") }) }));
    cards.emplace("VAN_EX1_625", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [VAN_EX1_626] Mass Dispel - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Silence</b> all enemy minions. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_626", cardDef);
}

void VanillaCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [VAN_EX1_345t] Shadow of Nothing - COST:0 [ATK:0/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Mindgames whiffed! Your opponent had no minions!
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_345t", cardDef);

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
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_072] Backstab - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to an undamaged minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_UNDAMAGED_TARGET, 0 } };
    cards.emplace("VAN_CS2_072", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e", EntityType::TARGET));
    cardDef.power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e2", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_073", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_074] Deadly Poison - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your weapon +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_074e", EntityType::WEAPON));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } };
    cards.emplace("VAN_CS2_074", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_075] Sinister Strike - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3, true));
    cards.emplace("VAN_CS2_075", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_076] Assassinate - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_CS2_076", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_CS2_077] Sprint - COST:7
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(4));
    cards.emplace("VAN_CS2_077", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_CS2_080] Assassin's Blade - COST:5 [ATK:2/HP:0]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 5
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_080", cardDef);

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
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::WEAPON, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::WEAPON));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } };
    cards.emplace("VAN_CS2_233", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_124] Eviscerate - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Combo:</b> Deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_124", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_126] Betrayal - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Force an enemy minion to deal its damage
    //       to the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_EX1_126", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_128] Conceal - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_128e", EntityType::MINIONS, false, false,
        SelfCondition::HasNotStealth()));
    cards.emplace("VAN_EX1_128", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_129] Fan of Knives - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions. Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_129", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<SummonTask>("EX1_131t", SummonSide::RIGHT));
    cards.emplace("VAN_EX1_131", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_EX1_133] Perdition's Blade - COST:3 [ATK:2/HP:0]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    //       <b>Combo:</b> Deal 2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_133", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_FOR_COMBO, 0 } };
    cards.emplace("VAN_EX1_134", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddComboTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::HEADCRACK_COMBO, 1));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE,
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsTagValue(GameTag::HEADCRACK_COMBO, 1)) }),
        std::make_shared<FlagTask>(
            true,
            TaskList{ std::make_shared<IncludeTask>(EntityType::SOURCE),
                      std::make_shared<FuncPlayableTask>(
                          [=](const std::vector<Playable*>& playables) {
                              const auto source = playables[0];
                              source->zone->Remove(source);
                              source->SetGameTag(GameTag::HEADCRACK_COMBO, 0);

                              return std::vector<Playable*>{ source };
                          }),
                      std::make_shared<AddStackToTask>(EntityType::HAND) })
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("VAN_EX1_137", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_144] Shadowstep - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<AddAuraEffectTask>(
        Effects::ReduceCost(2), EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_144", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_145] Preparation - COST:0
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_EX1_145o", EntityType::PLAYER));
    cards.emplace("VAN_EX1_145", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_278] Shiv - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_278", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [VAN_EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>.
    //       Destroy any minion damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_522", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_EX1_581] Sap - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Return an enemy minion to your opponent's hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_EX1_581", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddComboTask(std::make_shared<GetPlayerGameTagTask>(
        GameTag::NUM_CARDS_PLAYED_THIS_TURN));
    cardDef.power.AddComboTask(std::make_shared<MathSubtractTask>(1));
    cardDef.power.AddComboTask(std::make_shared<MathMultiplyTask>(2));
    cardDef.power.AddComboTask(std::make_shared<AddEnchantmentTask>(
        "EX1_613e", EntityType::SOURCE, true));
    cards.emplace("VAN_EX1_613", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [VAN_NEW1_004] Vanish - COST:6
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::ALL_MINIONS));
    cards.emplace("VAN_NEW1_004", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [VAN_NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Return a minion to its owner's hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_FOR_COMBO, 0 } };
    cards.emplace("VAN_NEW1_005", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [VAN_NEW1_014] Master of Disguise - COST:4 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::STEALTH, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_NEW1_014", cardDef);
}

void VanillaCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- WEAPON - ROGUE
    // [VAN_CS2_082] Wicked Knife - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_082", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(3) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
        aura->removeTrigger = { TriggerType::CAST_SPELL, nullptr };
    }
    cards.emplace("VAN_EX1_145o", cardDef);
}

void VanillaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_CS2_037", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_038] Ancestral Spirit - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a minion. When that minion is destroyed,
    //       return it to the battlefield.
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
        std::make_shared<AddEnchantmentTask>("CS2_038e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_038", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_039] Windfury - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Windfury</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::WINDFURY, 1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_039", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_041] Ancestral Healing - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealFullTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_041e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_041", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_CS2_042", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_045] Rockbiter Weapon - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly character +3 Attack this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_045e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_CS2_045", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_046] Bloodlust - COST:5
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your minions +3 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_046e", EntityType::MINIONS));
    cards.emplace("VAN_CS2_046", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_CS2_053] Far Sight - COST:3
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a card. That card costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_053e", EntityType::STACK));
    cards.emplace("VAN_CS2_053", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_238] Lightning Bolt - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_238", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_241] Lava Burst - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_241", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_243", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_244] Totemic Might - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your Totems +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::TOTEM)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_244e", EntityType::STACK));
    cards.emplace("VAN_EX1_244", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_245] Earth Shock - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion, then deal 1 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_245", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_246] Hex - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::TARGET, "hexfrog"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_246", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [VAN_EX1_247] Stormforged Axe - COST:2 [ATK:2/HP:0]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_247", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_248] Feral Spirit - COST:3
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("VAN_EX1_tk11", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("VAN_EX1_248", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b><b>Overload</b>:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // - OVERLOAD_OWED = 3
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_250", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [VAN_EX1_251] Forked Lightning - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to 2 random enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("VAN_EX1_251", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_258] Unbound Elemental - COST:3 [ATK:2/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a card with <b>Overload</b>,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOverloadCard())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_258e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_258", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, 1, true));
    cards.emplace("VAN_EX1_259", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdjacentAura>("EX1_565o"));
    cards.emplace("VAN_EX1_565", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [VAN_EX1_567] Doomhammer - COST:5 [ATK:2/HP:0]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 8
    // - WINDFURY = 1
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_567", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_EX1_575", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::WINDFURY, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_587", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_010", cardDef);
}

void VanillaCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_050] Searing Totem - COST:1 [ATK:1/HP:1]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_050", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_051] Stoneclaw Totem - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_051", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_CS2_052] Wrath of Air Totem - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_052", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [VAN_EX1_tk11] Spirit Wolf - COST:2 [ATK:2/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_tk11", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("VAN_NEW1_009", cardDef);
}

void VanillaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_057] Shadow Bolt - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_057", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("CS2_059o", EntityType::STACK)
    };
    cards.emplace("VAN_CS2_059", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_061] Drain Life - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage. Restore 2 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_CS2_061", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_062] Hellfire - COST:4
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to all characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL, 3, true));
    cards.emplace("VAN_CS2_062", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_CS2_063] Corruption - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Choose an enemy minion.
    //       At the start of your turn, destroy it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_063e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_CS2_063", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL, 1));
    cards.emplace("VAN_CS2_064", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_065", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(-1, false));
    cards.emplace("VAN_EX1_301", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_302] Mortal Coil - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion.
    //       If that kills it, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_302", cardDef);

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
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_303", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ATK, 0, 1));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ATK, 1, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(1, 2, MathOperation::ADD));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::HEALTH, 0, 3));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::HEALTH, 1, 4));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(3, 4, MathOperation::ADD, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_304e", EntityType::SOURCE, true));
    cards.emplace("VAN_EX1_304", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_306] Felstalker - COST:2 [ATK:4/HP:3]
    // - Race: Demon, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(1));
    cards.emplace("VAN_EX1_306", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_308] Soulfire - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 4 damage. Discard a random card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4));
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_308", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_309] Siphon Soul - COST:6
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore 3 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_309", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(2));
    cards.emplace("VAN_EX1_310", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_312] Twisting Nether - COST:8
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS));
    cards.emplace("VAN_EX1_312", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
    // - Race: Demon, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 5));
    cards.emplace("VAN_EX1_313", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_315] Summoning Portal - COST:4 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (2) less, but not less than (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SummoningPortalAura>());
    cards.emplace("VAN_EX1_315", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_316] Power Overwhelming - COST:1
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a friendly minion +4/+4 until end of turn.
    //       Then, it dies. Horribly.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_316e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_316", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_317] Sense Demons - COST:3
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 Demons from your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    for (size_t i = 0; i < 2; ++i)
    {
        cardDef.power.AddPowerTask(
            std::make_shared<IncludeTask>(EntityType::DECK));
        cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::DEMON)) }));
        cardDef.power.AddPowerTask(
            std::make_shared<CountTask>(EntityType::STACK));
        cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
            EntityType::HERO,
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsStackNum(1, RelaSign::GEQ)) }));
        cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<RandomTask>(EntityType::STACK, 1),
                            std::make_shared<DrawStackTask>() }));
        cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
            false, TaskList{ std::make_shared<AddCardTask>(EntityType::HAND,
                                                           "EX1_317t") }));
    }
    cards.emplace("VAN_EX1_317", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_319] Flame Imp - COST:1 [ATK:3/HP:2]
    // - Race: Demon, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 3));
    cards.emplace("VAN_EX1_319", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_320] Bane of Doom - COST:5
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to a character.
    //       If that kills it, summon a random Demon.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomCardTask>(
                            CardType::MINION, CardClass::INVALID, Race::DEMON),
                        std::make_shared<SummonTask>(SummonSide::SPELL) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_320", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ReplaceHeroTask>(
        "EX1_323h", "VAN_EX1_tk33", "EX1_323w"));
    cards.emplace("VAN_EX1_323", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_EX1_596] Demonfire - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it's a friendly Demon, give it +2/+2 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DEMON)) },
        RelaCondList{
            std::make_shared<RelaCondition>(RelaCondition::IsFriendly()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "EX1_596e", EntityType::TARGET) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_596", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [VAN_NEW1_003] Sacrificial Pact - COST:0
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a Demon.
    //       Restore 5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 15 } };
    cards.emplace("VAN_NEW1_003", cardDef);
}

void VanillaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [VAN_EX1_tk34] Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_tk34", cardDef);
}

void VanillaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_103] Charge - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly minion +2 Attack and <b>Charge</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "VAN_CS2_103e2", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_103", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_104] Rampage - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a damaged minion +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_104e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_DAMAGED_TARGET, 0 } };
    cards.emplace("VAN_CS2_104", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_105] Heroic Strike - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_105e", EntityType::HERO));
    cards.emplace("VAN_CS2_105", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_CS2_106] Fiery War Axe - COST:2 [ATK:3/HP:0]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_106", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_108] Execute - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a damaged enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 },
                                          { PlayReq::REQ_DAMAGED_TARGET, 0 } };
    cards.emplace("VAN_CS2_108", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_CS2_112] Arcanite Reaper - COST:5 [ATK:5/HP:0]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_112", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_CS2_114] Cleave - COST:2
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 2 damage to two random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("VAN_CS2_114", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsAttack(3, RelaSign::LEQ)) };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::EVENT_SOURCE, GameTag::CHARGE, 1) };
    cards.emplace("VAN_EX1_084", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_391] Slam - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it survives, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNotDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_391", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_392] Battle Rage - COST:2
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card for each damaged friendly character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(
        EntityType::FRIENDS, 0,
        std::vector<SelfCondition>{ SelfCondition::IsDamaged() }));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_392", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_398] Arathi Weaponsmith - COST:4 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 2/2 weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("EX1_398t"));
    cards.emplace("VAN_EX1_398", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_400] Whirlwind - COST:1
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("VAN_EX1_400", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(1) };
    cards.emplace("VAN_EX1_402", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_407] Brawl - COST:5
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except one.
    //       <i>(chosen randomly)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_TOTAL_MINIONS = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS, 1));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::ALL_MINIONS, std::vector<EntityType>{ EntityType::STACK }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_TOTAL_MINIONS, 2 } };
    cards.emplace("VAN_EX1_407", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_408] Mortal Strike - COST:4
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    //       If you have 12 or less Health, deal 6 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHealth(12, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 6, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_408", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_409] Upgrade! - COST:1
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you have a weapon, give it +1/+1.
    //       Otherwise equip a 1/3 weapon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsWeaponEquipped()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "EX1_409e", EntityType::WEAPON) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<WeaponTask>("EX1_409t") }));
    cards.emplace("VAN_EX1_409", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_410] Shield Slam - COST:1
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion for each Armor you have.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ARMOR));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("VAN_EX1_410", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [VAN_EX1_411] Gorehowl - COST:7 [ATK:7/HP:0]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Attacking a minion costs 1 Attack instead of 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::MINION)) };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_411e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_411", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::SELF, "EX1_414e"));
    cards.emplace("VAN_EX1_414", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion
    //       and give it +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_603e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_EX1_603", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [VAN_EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a minion takes damage, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_604o", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_604", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_606] Shield Block - COST:3
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(5));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_606", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_EX1_607] Inner Rage - COST:0
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and give it +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_607e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_607", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [VAN_NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_011", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [VAN_NEW1_036] Commanding Shout - COST:2
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    //       Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_036e2", EntityType::PLAYER));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_NEW1_036", cardDef);
}

void VanillaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [VAN_CS2_103e2] Charge - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Charge</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_CS2_103e2"));
    cards.emplace("VAN_CS2_103e2", cardDef);
}

void VanillaCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void VanillaCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [VAN_HERO_10bpe] Demon Claws - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_HERO_10bpe"));
    cards.emplace("VAN_HERO_10bpe", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [VAN_HERO_10pe2] Demon's Bite - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_HERO_10pe2"));
    cards.emplace("VAN_HERO_10pe2", cardDef);
}

void VanillaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS1_042", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS1_069", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
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
    cards.emplace("VAN_CS2_117", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_118", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_119", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_120", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_121", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_122] Raid Leader - COST:3 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "CS2_122e"));
    cards.emplace("VAN_CS2_122", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_124", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_125", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_127", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_131", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_CS2_141", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_142", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Charge</b> while you have a weapon equipped.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(SelfCondition::IsWeaponEquipped()),
        GameTag::CHARGE));
    cards.emplace("VAN_CS2_146", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_CS2_147", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_CS2_150", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Squire.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_152", SummonSide::RIGHT));
    cards.emplace("VAN_CS2_151", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_155] Archmage - COST:6 [ATK:4/HP:7]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_155", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_161", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_162", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_168", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_169", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_171", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_172", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_173", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_179", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
    // - Faction: Horde, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to HIMSELF.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::SOURCE, 4, false));
    cards.emplace("VAN_CS2_181", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_182", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_186] War Golem - COST:7 [ATK:7/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_186", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_187", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_188] Abusive Sergeant - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
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
        std::make_shared<AddEnchantmentTask>("CS2_188o", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_188", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_CS2_189", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Boar.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_CS2_boar", SummonSide::RIGHT));
    cards.emplace("VAN_CS2_196", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_197", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_200", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
    // - Race: Beast, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_201", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_203] Ironbeak Owl - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_CS2_203", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_213", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> Your weapon has +2 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::WEAPON, "CS2_221e"));
    cards.emplace("VAN_CS2_221", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_222] Stormwind Champion - COST:7 [ATK:6/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "VAN_CS2_222o"));
    cards.emplace("VAN_CS2_222", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each
    //       other friendly minion on the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "CS2_226e", EntityType::SOURCE, true));
    cards.emplace("VAN_CS2_226", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (3) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::AddCost(3) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("VAN_CS2_227", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_231", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 2));
    cards.emplace("VAN_DS1_055", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a character is healed, gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_001e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_001", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_MUST_TARGET_TAUNTER = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_MUST_TARGET_TAUNTER, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("VAN_EX1_002", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("EX1_004e", EntityType::STACK)
    };
    cards.emplace("VAN_EX1_004", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_005] Big Game Hunter - COST:3 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion
    //       with 7 or more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 7
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_MIN_ATTACK, 7 } };
    cards.emplace("VAN_EX1_005", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasMinionInHand())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::ZONE_POSITION),
        std::make_shared<MoveToSetasideTask>(EntityType::SOURCE),
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<RemoveHandTask>(EntityType::STACK),
        std::make_shared<SummonTask>(SummonSide::NUMBER),
        std::make_shared<ReturnHandTask>(EntityType::SOURCE)
    };
    cards.emplace("VAN_EX1_006", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_EX1_007", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_008", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +5 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_009e")));
    cards.emplace("VAN_EX1_009", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_010", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
    // - Faction: Horde, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_011", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_012", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_HAND, "EX1_014t", 2));
    cards.emplace("VAN_EX1_014", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_015", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b>
    //       Take control of a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ControlTask>(EntityType::STACK));
    cards.emplace("VAN_EX1_016", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_017", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
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
        std::make_shared<AddEnchantmentTask>("EX1_019e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_020", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_021", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_023", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_025t", SummonSide::RIGHT));
    cards.emplace("VAN_EX1_025", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_028", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_029] Leper Gnome - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("VAN_EX1_029", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_032", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_033", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
    // - Race: Dragon, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Health
    //       for each card in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_043e", EntityType::SOURCE, true));
    cards.emplace("VAN_EX1_043", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play a card, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_044e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_044", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_045", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
    // - Faction: Alliance, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
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
        std::make_shared<AddEnchantmentTask>("EX1_046e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("VAN_EX1_046", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
    // - Faction: Horde, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_EX1_048", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("VAN_EX1_049", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cards.emplace("VAN_EX1_050", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_055o", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_055", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_EX1_057", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 1));
    cards.emplace("VAN_EX1_058", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SwapAttackHealthTask>(EntityType::TARGET, "EX1_059e"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_059", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [](const Playable* playable) {
            int addAttackAmount = 0;
            const auto& myMinions = playable->player->GetFieldZone()->GetAll();
            const auto& opMinions =
                playable->player->opponent->GetFieldZone()->GetAll();

            for (const auto& minion : myMinions)
            {
                if (playable->GetZonePosition() == minion->GetZonePosition())
                {
                    continue;
                }

                if (minion->IsRace(Race::MURLOC))
                {
                    ++addAttackAmount;
                }
            }

            for (const auto& minion : opMinions)
            {
                if (minion->IsRace(Race::MURLOC))
                {
                    ++addAttackAmount;
                }
            }

            return addAttackAmount;
        }));
    cards.emplace("VAN_EX1_062", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cards.emplace("VAN_EX1_066", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_067", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first minion you play each turn costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SwitchingAura>(
        AuraType::HAND, SelfCondition::MinionsPlayedThisTurn(0),
        TriggerType::PLAY_MINION, EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("VAN_EX1_076", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSecret())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_080o", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_080", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ALL_NOSOURCE, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        3, false));
    cards.emplace("VAN_EX1_082", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS_NOSOURCE, 1));
    cardDef.power.AddPowerTask(std::make_shared<ChanceTask>(true));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<TransformTask>(EntityType::STACK,
                                                        "VAN_EX1_tk28") }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<TransformTask>(EntityType::STACK,
                                                         "VAN_EX1_tk29") }));
    cards.emplace("VAN_EX1_083", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 4 or
    //       more minions, take control of one at random.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            return playables.size() > 3 ? playables : std::vector<Playable*>{};
        }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::STACK) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<ControlTask>(EntityType::STACK) }));
    cards.emplace("VAN_EX1_085", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ManaCrystalTask>(1, false, true));
    cards.emplace("VAN_EX1_089", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_093e", EntityType::STACK));
    cards.emplace("VAN_EX1_093", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_EX1_095", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_096", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL, 2));
    cards.emplace("VAN_EX1_097", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, RelaCondList{ std::make_shared<RelaCondition>(
                                    RelaCondition::IsFriendly()) }),
        std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<CopyTask>(
                      EntityType::TARGET, ZoneType::HAND, 1, false, true) }),
        std::make_shared<FlagTask>(
            false, TaskList{ std::make_shared<CopyTask>(EntityType::TARGET,
                                                        ZoneType::HAND) })
    };
    cards.emplace("VAN_EX1_100", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 2)
    };
    cards.emplace("VAN_EX1_102", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all other Murlocs +2 Health.
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
        std::make_shared<AddEnchantmentTask>("EX1_103e", EntityType::STACK));
    cards.emplace("VAN_EX1_103", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetHandZone()->GetCount() - 1;
        }));
    cards.emplace("VAN_EX1_105", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("VAN_EX1_110t", SummonSide::DEATHRATTLE));
    cards.emplace("VAN_EX1_110", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_112] Gelbin Mekkatorque - COST:6 [ATK:6/HP:6]
    // - Faction: Alliance, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon an AWESOME invention.
    // --------------------------------------------------------
    // Entourage: Mekka1, Mekka2, Mekka3, Mekka4
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cardDef.property.entourages =
        Entourages{ "Mekka1", "Mekka2", "Mekka3", "Mekka4" };
    cards.emplace("VAN_EX1_112", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonOpTask>("EX1_116t") }, 2));
    cards.emplace("VAN_EX1_116", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdjacentAura>("EX1_162o"));
    cards.emplace("VAN_EX1_162", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy any minion damaged by this minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::POISONOUS, 1));
    cards.emplace("VAN_EX1_170", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_NOSOURCE, 2) };
    cards.emplace("VAN_EX1_249", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("VAN_EX1_283", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("VAN_EX1_284", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMIES),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 8)
    };
    cards.emplace("VAN_EX1_298", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Enrage:</b> +3 Attack
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_390e")));
    cards.emplace("VAN_EX1_390", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +3 Attack
    // --------------------------------------------------------
    // RefTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_393e")));
    cards.emplace("VAN_EX1_393", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_396", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:7]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_399e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_399", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_405", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::SELF, "EX1_412e"));
    cards.emplace("VAN_EX1_412", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("VAN_EX1_506a", SummonSide::RIGHT));
    cards.emplace("VAN_EX1_506", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
    // - Race: Murloc, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: ALL other murlocs have +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "VAN_EX1_507e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("VAN_EX1_507", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: ALL other Murlocs have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "EX1_508o"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("VAN_EX1_508", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a Murloc is summoned, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_509e", EntityType::SOURCE) };
    cards.emplace("VAN_EX1_509", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("VAN_skele21", SummonSide::DEATHRATTLE));
    cards.emplace("VAN_EX1_556", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
    // - Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       you have a 50% chance to draw an extra card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->percentage = 0.5f;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_EX1_557", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::ENEMY_WEAPON, GameTag::DURABILITY));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::ENEMY_WEAPON, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("VAN_EX1_558", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_560] Nozdormu - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Players only have 15 seconds to take their turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYERS, EffectList{ std::make_shared<Effect>(
                               GameTag::TIMEOUT, EffectOperator::SET, -60) }));
    cards.emplace("VAN_EX1_560", cardDef);

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
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_HERO_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        []([[maybe_unused]] Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            Hero* hero = dynamic_cast<Hero*>(target);
            hero->SetDamage(hero->GetBaseHealth() - 15);
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_HERO_TARGET, 0 } };
    cards.emplace("VAN_EX1_561", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("EX1_116t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("EX1_116t", SummonSide::LEFT) },
        3));
    cards.emplace("VAN_EX1_562", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_563", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TransformCopyTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("VAN_EX1_564", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_572] Ysera - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: VANILLA, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, add a Dream Card to your hand.
    // --------------------------------------------------------
    // Entourage: DREAM_01, DREAM_02, DREAM_03, DREAM_04, DREAM_05
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomEntourageTask>(1),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cardDef.property.entourages =
        Entourages{ "DREAM_01", "DREAM_02", "DREAM_03", "DREAM_04",
                    "DREAM_05" };
    cards.emplace("VAN_EX1_572", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonOpTask>("VAN_EX1_finkle"));
    cards.emplace("VAN_EX1_577", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_582", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 4));
    cards.emplace("VAN_EX1_583", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_584e", EntityType::STACK));
    cards.emplace("VAN_EX1_584", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other minion on the battlefield.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetFieldZone()->GetCount() +
                   playable->player->opponent->GetFieldZone()->GetCount();
        }));
    cards.emplace("VAN_EX1_586", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::DIVINE_SHIELD, 1)) }));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::DIVINE_SHIELD, 0));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<MathMultiplyTask>(3));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_590e", EntityType::SOURCE, true));
    cards.emplace("VAN_EX1_590", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
    // - Set: VANILLA, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cards.emplace("VAN_EX1_593", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_595] Cult Master - COST:4 [ATK:4/HP:2]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly minion dies, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("VAN_EX1_595", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<DamageTask>(EntityType::SOURCE, 1),
        std::make_shared<SummonTask>("VAN_EX1_598", SummonSide::RIGHT)
    };
    cards.emplace("VAN_EX1_597", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "VAN_TU4e_002t", SummonSide::RIGHT) };
    cards.emplace("VAN_EX1_614", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_616] Mana Wraith - COST:2 [ATK:2/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: All minions cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HANDS, EffectList{ Effects::AddCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("VAN_EX1_616", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage your hero has taken.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetHero()->GetDamage();
        }));
    cards.emplace("VAN_EX1_620", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_016] Captain's Parrot - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Pirate from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawRaceMinionTask>(Race::PIRATE, 1, false));
    cards.emplace("VAN_NEW1_016", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Murloc and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 14
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET),
                        std::make_shared<AddEnchantmentTask>(
                            "NEW1_017e", EntityType::SOURCE) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 14 } };
    cards.emplace("VAN_NEW1_017", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::WEAPON, GameTag::ATK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "NEW1_018e", EntityType::SOURCE, true));
    cards.emplace("VAN_NEW1_018", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMIES),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1)
    };
    cards.emplace("VAN_NEW1_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
    // - Set: VANILLA, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 1) };
    cards.emplace("VAN_NEW1_020", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
    // - Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, destroy all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::ALL_MINIONS) };
    cards.emplace("VAN_NEW1_021", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (!playable->player->GetHero()->HasWeapon())
            {
                return 0;
            }

            return playable->player->GetHero()->weapon->GetAttack();
        }));
    cards.emplace("VAN_NEW1_022", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_023", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_024o", EntityType::WEAPON));
    cards.emplace("VAN_NEW1_024", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RemoveDurabilityTask>(1, true));
    cards.emplace("VAN_NEW1_025", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "VAN_NEW1_026t", SummonSide::RIGHT) };
    cards.emplace("VAN_NEW1_026", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: VANILLA, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Pirates have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "VAN_NEW1_027e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::PIRATE));
    }
    cards.emplace("VAN_NEW1_027", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_029t", EntityType::PLAYER));
    cards.emplace("VAN_NEW1_029", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<RemoveHandTask>(EntityType::HAND));
    cards.emplace("VAN_NEW1_030", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("NEW1_037e", EntityType::STACK)
    };
    cards.emplace("VAN_NEW1_037", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->eitherTurn = true;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "NEW1_038o", EntityType::SOURCE) };
    cards.emplace("VAN_NEW1_038", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "NEW1_040t", SummonSide::RIGHT) };
    cards.emplace("VAN_NEW1_040", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 2, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("VAN_NEW1_041", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.property.entourages =
        Entourages{ "PRO_001a", "PRO_001b", "PRO_001c" };
    cards.emplace("VAN_PRO_001", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_tt_004] Flesheating Ghoul - COST:3 [ATK:2/HP:3]
    // - Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "tt_004o", EntityType::SOURCE) };
    cards.emplace("VAN_tt_004", cardDef);
}

void VanillaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_152] Squire - COST:1 [ATK:2/HP:2]
    // - Faction: Alliance, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_152", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_CS2_222o] Might of Stormwind - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_CS2_222o"));
    cards.emplace("VAN_CS2_222o", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_boar] Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_boar", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_CS2_tk1] Sheep - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_CS2_tk1", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_110t", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_506a", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_EX1_507e] Mrgglaargl! - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +2/+1 from Murloc Warleader.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_EX1_507e"));
    cards.emplace("VAN_EX1_507e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_598] Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_598", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_finkle] Finkle Einhorn - COST:3 [ATK:3/HP:3]
    // - Set: VANILLA
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_finkle", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_tk28] Squirrel - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_tk28", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_EX1_tk29] Devilsaur - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_EX1_tk29", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_NEW1_026t] Violet Apprentice - COST:0 [ATK:1/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_NEW1_026t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [VAN_NEW1_027e] Yarrr! - COST:0
    // - Set: VANILLA
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("VAN_NEW1_027e"));
    cards.emplace("VAN_NEW1_027e", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_skele21", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [VAN_TU4e_002t] Flame of Azzinoth - COST:1 [ATK:2/HP:1]
    // - Set: VANILLA
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("VAN_TU4e_002t", cardDef);
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