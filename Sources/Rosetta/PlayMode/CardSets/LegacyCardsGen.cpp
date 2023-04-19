// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/LegacyCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void LegacyCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- HERO - WARRIOR
    // [HERO_01] Garrosh Hellscream - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 725
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_01", cardDef);

    // ------------------------------------------ HERO - SHAMAN
    // [HERO_02] Thrall - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 687
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_02", cardDef);

    // ------------------------------------------- HERO - ROGUE
    // [HERO_03] Valeera Sanguinar - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 730
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_03", cardDef);

    // ----------------------------------------- HERO - PALADIN
    // [HERO_04] Uther Lightbringer - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 472
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_04", cardDef);

    // ------------------------------------------ HERO - HUNTER
    // [HERO_05] Rexxar - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 229
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_05", cardDef);

    // ------------------------------------------- HERO - DRUID
    // [HERO_06] Malfurion Stormrage - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 1123
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_06", cardDef);

    // ----------------------------------------- HERO - WARLOCK
    // [HERO_07] Gul'dan - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 300
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_07", cardDef);

    // -------------------------------------------- HERO - MAGE
    // [HERO_08] Jaina Proudmoore - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 807
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_08", cardDef);

    // ------------------------------------------ HERO - PRIEST
    // [HERO_09] Anduin Wrynn - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 479
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_09", cardDef);

    // ------------------------------------- HERO - DEMONHUNTER
    // [HERO_10] Illidan Stormrage - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 60224
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("HERO_10", cardDef);
}

void LegacyCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- HERO_POWER - WARRIOR
    // [HERO_01bp] Armor Up! (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("HERO_01bp", cardDef);

    // ----------------------------------- HERO_POWER - WARRIOR
    // [HERO_01bp2] Tank Up! (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Gain 4 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cards.emplace("HERO_01bp2", cardDef);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [HERO_02bp] Totemic Call (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a random Totem.
    // --------------------------------------------------------
    // Entourage: CS2_050, CS2_051, CS2_058, NEW1_009
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
    cardDef.property.entourages =
        Entourages{ "CS2_050", "CS2_051", "CS2_058", "NEW1_009" };
    cards.emplace("HERO_02bp", cardDef);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [HERO_02bp2] Totemic Slam (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a Totem of your choice.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::BASIC_TOTEM, 4));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("HERO_02bp2", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [HERO_03bp] Dagger Mastery (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 1/2 Dagger.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("CS2_082"));
    cards.emplace("HERO_03bp", cardDef);

    // ------------------------------------- HERO_POWER - ROGUE
    // [HERO_03bp2] Poisoned Daggers (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 2/2 Weapon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("AT_132_ROGUEt"));
    cards.emplace("HERO_03bp2", cardDef);

    // ----------------------------------- HERO_POWER - PALADIN
    // [HERO_04bp] Reinforce (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", SummonSide::DEFAULT));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("HERO_04bp", cardDef);

    // ----------------------------------- HERO_POWER - PALADIN
    // [HERO_04bp2] The Silver Hand (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon two 1/1 Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", 2, SummonSide::DEFAULT));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("HERO_04bp2", cardDef);

    // ------------------------------------ HERO_POWER - HUNTER
    // [HERO_05bp] Steady Shot (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_05bp", cardDef);

    // ------------------------------------ HERO_POWER - HUNTER
    // [HERO_05bp2] Ballista Shot (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_05bp2", cardDef);

    // ------------------------------------- HERO_POWER - DRUID
    // [HERO_06bp] Shapeshift (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn. +1 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_017o", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(1));
    cards.emplace("HERO_06bp", cardDef);

    // ------------------------------------- HERO_POWER - DRUID
    // [HERO_06bp2] Dire Shapeshift (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn. +2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "AT_132_DRUIDe", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cards.emplace("HERO_06bp2", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [HERO_07bp] Life Tap (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card and take 2 damage.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 2, false));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("HERO_07bp", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [HERO_07bp2] Soul Tap (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("HERO_07bp2", cardDef);

    // -------------------------------------- HERO_POWER - MAGE
    // [HERO_08bp] Fireblast (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_08bp", cardDef);

    // -------------------------------------- HERO_POWER - MAGE
    // [HERO_08bp2] Fireblast Rank 2 (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_08bp2", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [HERO_09bp] Lesser Heal (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_09bp", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [HERO_09bp2] Heal (*) - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("HERO_09bp2", cardDef);

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [HERO_10bp] Demon Claws (*) - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +1 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("HERO_10bpe", EntityType::HERO));
    cards.emplace("HERO_10bp", cardDef);

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [HERO_10bp2] Demon's Bite (*) - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("HERO_10pe2", EntityType::HERO));
    cards.emplace("HERO_10bp2", cardDef);
}

void LegacyCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [CS2_005] Claw - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Gain 2 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(2));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_005o", EntityType::HERO));
    cards.emplace("CS2_005", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_007] Healing Touch - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_007", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_008] Moonfire - COST:0
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Arcane
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
    cards.emplace("CS2_008", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_009] Mark of the Wild - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion <b>Taunt</b> and +2/+3.<i>
    //       (+2 Attack/+3 Health)</i>
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
        std::make_shared<AddEnchantmentTask>("CS2_009e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_009", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_011] Savage Roar - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your characters +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_011o", EntityType::FRIENDS));
    cards.emplace("CS2_011", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_012] Swipe - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_012", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_013] Wild Growth - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_013", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_232", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [CS3_012] Nordrassil Druid - COST:4 [ATK:3/HP:5]
    // - Set: Legacy, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next spell you cast this turn
    //       costs (3) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS3_012e", EntityType::PLAYER));
    cards.emplace("CS3_012", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_169] Innervate - COST:0
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TempManaTask>(1));
    cards.emplace("EX1_169", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_173] Starfire - COST:6
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Arcane
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
    cards.emplace("EX1_173", cardDef);
}

void LegacyCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_005o] Claw (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_005o"));
    cards.emplace("CS2_005o", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_009e] Mark of the Wild (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2/+3 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_009e"));
    cards.emplace("CS2_009e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_011o] Savage Roar (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_011o"));
    cards.emplace("CS2_011o", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_013t] Excess Mana (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Draw a card.
    //       <i>(You can only have 10 Mana in your tray.)</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("CS2_013t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_017o] Claws (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_017o"));
    cards.emplace("CS2_017o", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS3_012e] Nature's Rite - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Your next spell this turn costs (3) less.
    // --------------------------------------------------------
    // GameTag:
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
    cards.emplace("CS3_012e", cardDef);
}

void LegacyCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [CS2_084] Hunter's Mark - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_084", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [CS2_237] Starving Buzzard - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever you summon a Beast, draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("CS2_237", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_070] Houndmaster - COST:4 [ATK:4/HP:3]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("DS1_070", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("DS1_175", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_178] Tundra Rhino - COST:5 [ATK:2/HP:5]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("DS1_178", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_183] Multi-Shot - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("DS1_183", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_184] Tracking - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Discover</b> a card from your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::DECK));
    cards.emplace("DS1_184", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_185] Arcane Shot - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Arcane
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
    cards.emplace("DS1_185", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_539] Kill Command - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_539", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [NEW1_031] Animal Companion - COST:3
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon a random Beast Companion.
    // --------------------------------------------------------
    // Entourage: NEW1_032, NEW1_033, NEW1_034
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
        Entourages{ "NEW1_032", "NEW1_033", "NEW1_034" };
    cards.emplace("NEW1_031", cardDef);
}

void LegacyCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [CS2_084e] Hunter's Mark (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: This minion has 1 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(GameTag::HEALTH, EffectOperator::SET, 1));
    cards.emplace("CS2_084e", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_070o] Master's Presence (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DS1_070o"));
    cards.emplace("DS1_070o", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_175o] Furious Howl (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +1 Attack from Timber Wolf.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DS1_175o"));
    cards.emplace("DS1_175o", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_178e] Charge (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Tundra Rhino grants <b>Charge</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DS1_178e"));
    cards.emplace("DS1_178e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_032] Misha (*) - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_032", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_033] Leokk (*) - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "NEW1_033o"));
    cards.emplace("NEW1_033", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [NEW1_033o] Eye In The Sky (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Leokk is granting this minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("NEW1_033o"));
    cards.emplace("NEW1_033o", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_034] Huffer (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_034", cardDef);
}

void LegacyCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_022] Polymorph - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Transform a minion into a 1/1 Sheep.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::TARGET, "CS2_tk1"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_022", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_023] Arcane Intellect - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cards.emplace("CS2_023", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_024] Frostbolt - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Frost
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
    cards.emplace("CS2_024", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_025] Arcane Explosion - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cards.emplace("CS2_025", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_026] Frost Nova - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("CS2_026", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_027] Mirror Image - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("CS2_mirror", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("CS2_027", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_029] Fireball - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Fire
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
    cards.emplace("CS2_029", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_032] Flamestrike - COST:7
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 5, true));
    cards.emplace("CS2_032", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_033", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_277] Arcane Missiles - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage randomly split among all enemies.
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
    cards.emplace("EX1_277", cardDef);
}

void LegacyCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [CS2_mirror] Mirror Image - COST:0 [ATK:0/HP:2]
    // - Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_mirror", cardDef);
}

void LegacyCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_087] Blessing of Might - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS2_087", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:7]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Restore 6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 6));
    cards.emplace("CS2_088", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_089] Holy Light - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 8 Health to your hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 8));
    cards.emplace("CS2_089", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [CS2_091] Light's Justice - COST:1 [ATK:1/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_091", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_092] Blessing of Kings - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS2_092", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_093] Consecration - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true));
    cards.emplace("CS2_093", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_094] Hammer of Wrath - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS2_094", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_097", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [CS3_029] Pursuit of Justice - COST:2
    // - Set: Legacy, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give +1 Attack to Silver Hand Recruits
    //       you summon this game.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_360] Humility - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_360", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_371] Hand of Protection - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("EX1_371", cardDef);
}

void LegacyCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS2_087e] Blessing of Might (*) - COST:0
    // - Faction: Neutral, Set: Legacy
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_087e"));
    cards.emplace("CS2_087e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS2_092e] Blessing of Kings (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_092e"));
    cards.emplace("CS2_092e", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [CS2_101t] Silver Hand Recruit (*) - COST:1 [ATK:1/HP:1]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_101t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_360e] Humility (*) - COST:0
    // - Faction: Neutral, Set: Legacy
    // --------------------------------------------------------
    // Text: Attack has been changed to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(GameTag::ATK, EffectOperator::SET, 1));
    cards.emplace("EX1_360e", cardDef);
}

void LegacyCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_112] Holy Nova - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    //       Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::FRIENDS, 2));
    cards.emplace("CS1_112", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_113] Mind Control - COST:10
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("CS1_113", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_130] Holy Smite - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS1_130", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_003] Mind Vision - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Put a copy of a random card in your opponent's
    //       hand into your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_HAND, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("CS2_003", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_004] Power Word: Shield - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS2_004", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_234] Shadow Word: Pain - COST:2
    // - Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("CS2_234", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
    // - Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_235", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_236] Divine Spirit - COST:2
    // - Set: Legacy, Rarity: Free
    // - Spell School: Holy
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
    cards.emplace("CS2_236", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [CS3_014] Crimson Clergy - COST:1 [ATK:1/HP:3]
    // - Set: Legacy, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a friendly character is healed, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "CS3_014e", EntityType::SOURCE) };
    cards.emplace("CS3_014", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [DS1_233] Mind Blast - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 5, true));
    cards.emplace("DS1_233", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_192] Radiance - COST:1
    // - Set: Legacy, Rarity: Free
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 5 Health to your hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cards.emplace("EX1_192", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_193] Psychic Conjurer - COST:1 [ATK:1/HP:1]
    // - Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a card in your opponent's deck
    //       and add it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_DECK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("EX1_193", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_194] Power Infusion - COST:4
    // - Set: Legacy, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+6.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_194e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_194", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_622] Shadow Word: Death - COST:2
    // - Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("EX1_622", cardDef);
}

void LegacyCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS2_004e] Power Word: Shield (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_004e"));
    cards.emplace("CS2_004e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS2_236e] Divine Spirit (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This minion has double Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddHealthScriptTag));
    cards.emplace("CS2_236e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_194e] Power Infusion (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2/+6.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_194e"));
    cards.emplace("EX1_194e", cardDef);
}

void LegacyCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_072] Backstab - COST:0
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_072", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_074] Deadly Poison - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_074", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_075] Sinister Strike - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3, true));
    cards.emplace("CS2_075", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_076] Assassinate - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_076", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_077] Sprint - COST:5
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(4));
    cards.emplace("CS2_077", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [CS2_080] Assassin's Blade - COST:4 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 5
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_080", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_129] Fan of Knives - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions. Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_129", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_191] Plaguebringer - COST:4 [ATK:3/HP:3]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_191e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_191", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_278] Shiv - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_278", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_581] Sap - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_581", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [NEW1_004] Vanish - COST:6
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::ALL_MINIONS));
    cards.emplace("NEW1_004", cardDef);
}

void LegacyCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- WEAPON - ROGUE
    // [CS2_082] Wicked Knife (*) - COST:1 [ATK:1/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_082", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [EX1_191e] Plaguetouched (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_191e"));
    cards.emplace("EX1_191e", cardDef);
}

void LegacyCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_037] Frost Shock - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Frost
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
    cards.emplace("CS2_037", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_039] Windfury - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_039", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_041", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
    // - Race: Elemental, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("CS2_042", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_045] Rockbiter Weapon - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("CS2_045", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_046] Bloodlust - COST:5
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your minions +3 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_046e", EntityType::MINIONS));
    cards.emplace("CS2_046", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_244] Totemic Might - COST:0
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_244", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_246] Hex - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Nature
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
    cards.emplace("EX1_246", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Adjacent minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdjacentAura>("EX1_565o"));
    cards.emplace("EX1_565", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Legacy, Rarity: free
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
    cards.emplace("EX1_587", cardDef);
}

void LegacyCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::Taunt));
    cards.emplace("CS2_041e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_045e] Rockbiter Weapon (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: This character has +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_045e"));
    cards.emplace("CS2_045e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_046e] Bloodlust (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_046e"));
    cards.emplace("CS2_046e", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_050] Searing Totem (*) - COST:1 [ATK:1/HP:1]
    // - Race: Totem, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_050", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_051] Stoneclaw Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_051", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_052] Wrath of Air Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_052", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_058] Strength Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another friendly minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("CS2_058e", EntityType::STACK)
    };
    cards.emplace("CS2_058", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_058e] Strength of Earth (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_058e"));
    cards.emplace("CS2_058e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [EX1_244e] Totemic Might (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_244e"));
    cards.emplace("EX1_244e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [EX1_565o] Flametongue (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack from Flametongue Totem.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_565o"));
    cards.emplace("EX1_565o", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [NEW1_009] Healing Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 1 Health to all friendly minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("NEW1_009", cardDef);
}

void LegacyCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_057] Shadow Bolt - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("CS2_057", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_061] Drain Life - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("CS2_061", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_062] Hellfire - COST:4
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 3 damage to all characters.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL, 3, true));
    cards.emplace("CS2_062", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_063] Corruption - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_063", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL, 1));
    cards.emplace("CS2_064", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_065", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS3_002] Ritual of Doom - COST:0
    // - Set: Legacy, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a friendly minion.
    //       If you had 5 or more, summon a 5/5 Demon.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(5, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET),
                        std::make_shared<SummonTask>("CS3_002t",
                                                     SummonSide::TARGET) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS3_002", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [CS3_021] Enslaved Fel Lord - COST:7 [ATK:4/HP:10]
    // - Race: Demon, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Also damages the minions next to
    //       whomever this attacks.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::DamageMinionsNextToAttack()
    };
    cards.emplace("CS3_021", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_302] Mortal Coil - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Shadow
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
    cards.emplace("EX1_302", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_306] Felstalker - COST:2 [ATK:4/HP:3]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(1));
    cards.emplace("EX1_306", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_308] Soulfire - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // - Spell School: Fire
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
    cards.emplace("EX1_308", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [NEW1_003] Sacrificial Pact - COST:0
    // - Set: Legacy, Rarity: Free
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a friendly Demon.
    //       Restore 5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 15 } };
    cards.emplace("NEW1_003", cardDef);
}

void LegacyCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [CS2_063e] Corruption (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: At the start of the corrupting player's turn, destroy this minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::TARGET) };
    cards.emplace("CS2_063e", cardDef);
}

void LegacyCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_103] Charge - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_103e2", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_103", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_105] Heroic Strike - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_105e", EntityType::HERO));
    cards.emplace("CS2_105", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [CS2_106] Fiery War Axe - COST:3 [ATK:3/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_106", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_108] Execute - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_108", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [CS2_112] Arcanite Reaper - COST:5 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_112", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_114] Cleave - COST:2
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_114", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS3_009] War Cache - COST:3
    // - Set: Legacy, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add a random Warrior minion, spell,
    //       and weapon to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::WARRIOR));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::WARRIOR));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::WEAPON, CardClass::WARRIOR));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("CS3_009", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [CS3_030] Warsong Outrider - COST:4 [ATK:5/HP:4]
    // - Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS3_030", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_084] Warsong Commander - COST:3 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: After you summon another minion, give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_084e", EntityType::TARGET) };
    cards.emplace("EX1_084", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_400] Whirlwind - COST:1
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("EX1_400", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_606] Shield Block - COST:3
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(5));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_606", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_011", cardDef);
}

void LegacyCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_103e2] Charge (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Charge</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_103e2"));
    cards.emplace("CS2_103e2", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_105e] Heroic Strike (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_105e"));
    cards.emplace("CS2_105e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_084e] Rush (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Has <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_084e"));
    cards.emplace("EX1_084e", cardDef);
}

void LegacyCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_035] Chaos Strike - COST:2
    // - Set: Legacy, Rarity: Free
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_035e", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("BT_035", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_036] Coordinated Strike - COST:3
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon three 1/1 Illidari with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("BT_036t", 3));
    cards.emplace("BT_036", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_142] Shadowhoof Slayer (*) - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your hero +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_142e", EntityType::HERO));
    cards.emplace("BT_142", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_235] Chaos Nova - COST:5
    // - Set: Legacy, Rarity: Free
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 4 damage to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 4, true));
    cards.emplace("BT_235", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_323] Sightless Watcher (*) - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards in your deck.
    //       Choose one to put on top.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::DECK, 3));
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](Playable* playable) {
            const auto playables = playable->game->taskStack.playables;

            std::vector<int> ids;
            ids.reserve(3);

            for (auto& p : playables)
            {
                ids.emplace_back(p->GetGameTag(GameTag::ENTITY_ID));
            }

            Generic::CreateChoice(playable->player, playable,
                                  ChoiceType::GENERAL,
                                  ChoiceAction::SIGHTLESS_WATCHER, ids);

            return 0;
        }));
    cards.emplace("BT_323", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_352] Satyr Overseer (*) - COST:3 [ATK:4/HP:2]
    // - Race: Demon, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: After your hero attacks, summon a 2/2 Satyr.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BT_352t", SummonSide::RIGHT) };
    cards.emplace("BT_352", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_495] Glaivebound Adept (*) - COST:5 [ATK:6/HP:4]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero attacked this turn,
    //       deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsAttackThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("BT_495", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_512] Inner Demon - COST:8
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +8 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_512e", EntityType::HERO));
    cards.emplace("BT_512", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_740] Soul Cleave - COST:3
    // - Set: Legacy, Rarity: Free
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> Deal 2 damage to two random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
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
    cards.emplace("BT_740", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [BT_921] Aldrachi Warblades - COST:3 [ATK:2/HP:0]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_921", cardDef);
}

void LegacyCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_035e] Chaos Strike (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_035e"));
    cards.emplace("BT_035e", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_036t] Illidari Initiate (*) - COST:1 [ATK:1/HP:1]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_036t", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_142e] Sharpened Claws (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_142e"));
    cards.emplace("BT_142e", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [BT_352t] Illidari Satyr (*) - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("BT_352t", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_512e] Demon Power (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +8 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BT_512e"));
    cards.emplace("BT_512e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [HERO_10bpe] Demon Claws (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("HERO_10bpe"));
    cards.emplace("HERO_10bpe", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [HERO_10pe2] Demon's Bite (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("HERO_10pe2"));
    cards.emplace("HERO_10pe2", cardDef);
}

void LegacyCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS1_042", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Race: Elemental, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_118", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
    // - Race: Beast, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_119", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_120", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_121", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_122] Raid Leader - COST:3 [ATK:2/HP:3]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "CS2_122e"));
    cards.emplace("CS2_122", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_124", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_125", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_127", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_131", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_141", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_142", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("CS2_147", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_150", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_155] Archmage - COST:6 [ATK:4/HP:7]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_155", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_162", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_168", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_171", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_172", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_173", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_179", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_182", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_186] War Golem - COST:7 [ATK:7/HP:7]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_186", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_187", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
    // - Faction: Horde, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_189", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Boar.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_boar", SummonSide::RIGHT));
    cards.emplace("CS2_196", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_197", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_200", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
    // - Race: Beast, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_201", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
    // - Faction: Horde, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_213", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_222] Stormwind Champion - COST:7 [ATK:7/HP:7]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "CS2_222o"));
    cards.emplace("CS2_222", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
    // - Faction: Horde, Set: Legacy, Rarity: Free
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
    cards.emplace("CS2_226", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [DS1_055] Darkscale Healer - COST:5 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("DS1_055", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
    // - Faction: Horde, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_011", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_015", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_025t", SummonSide::RIGHT));
    cards.emplace("EX1_025", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
    // - Race: Murloc, Faction: Neutral. Set: Legacy, Rarity: Legendary
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
    cards.emplace("EX1_062", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cards.emplace("EX1_066", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_112] Gelbin Mekkatorque - COST:6 [ATK:6/HP:6]
    // - Faction: Alliance, Set: Legacy, Rarity: Legendary
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
    cards.emplace("EX1_112", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:8]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
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
    cards.emplace("EX1_399", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_506a", SummonSide::RIGHT));
    cards.emplace("EX1_506", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other Murlocs have +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "EX1_508o"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("EX1_508", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_582", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cards.emplace("EX1_593", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_016] Captain's Parrot - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: Legacy, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Pirate from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawRaceMinionTask>(Race::PIRATE, 1, false));
    cards.emplace("NEW1_016", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [PRO_001] Elite Tauren Chieftain - COST:5 [ATK:5/HP:5]
    // - Set: Legacy, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give both players the power to ROCK!
    //       (with a Power Chord card)
    // --------------------------------------------------------
    // Entourage: PRO_001a, PRO_001b, PRO_001c
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
    cards.emplace("PRO_001", cardDef);
}

void LegacyCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_074e] Deadly Poison (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_074e"));
    cards.emplace("CS2_074e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_122e] Enhanced (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Raid Leader is granting this minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_122e"));
    cards.emplace("CS2_122e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_222o] Might of Stormwind (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_222o"));
    cards.emplace("CS2_222o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_226e] Frostwolf Banner (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("CS2_226e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_boar] Boar (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_boar", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_tk1] Sheep (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_tk1", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_019e] Cleric's Blessing (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_019e"));
    cards.emplace("EX1_019e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_025t] Mechanical Dragonling (*) - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Faction: Neutral, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_025t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_506a] Murloc Scout (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_506a", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_508o] Mlarggragllabl! (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: This Murloc has +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_508o"));
    cards.emplace("EX1_508o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_399e] Berserking (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: This minion has increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::AttackN(3)));
    cards.emplace("EX1_399e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [hexfrog] Frog (*) - COST:0 [ATK:0/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("hexfrog", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [Mekka1] Homing Chicken (*) - COST:1 [ATK:0/HP:1]
    // - Race: Mechanical, Faction: Alliance, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       destroy this minion and draw 3 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
                                              EntityType::SOURCE),
                                          std::make_shared<DrawTask>(3) };
    cards.emplace("Mekka1", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [Mekka2] Repair Bot (*) - COST:1 [ATK:0/HP:3]
    // - Race: Mechanical, Faction: Alliance, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 6 Health to a damaged character.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ALL),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<HealTask>(EntityType::STACK, 6)
    };
    cards.emplace("Mekka2", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [Mekka3] Emboldener 3000 (*) - COST:1 [ATK:0/HP:4]
    // - Race: Mechanical, Faction: Alliance, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, give a random minion +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<AddEnchantmentTask>("Mekka3e", EntityType::STACK)
    };
    cards.emplace("Mekka3", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [Mekka3e] Emboldened! (*) - COST:0
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Increased Stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::AttackHealthN(1) }));
    cards.emplace("Mekka3e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [Mekka4] Poultryizer (*) - COST:1 [ATK:0/HP:3]
    // - Race: Mechanical, Faction: Alliance, Set: Legacy, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       transform a random minion into a 1/1 Chicken.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<TransformTask>(EntityType::STACK, "Mekka4t")
    };
    cards.emplace("Mekka4", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [Mekka4t] Chicken (*) - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: Legacy
    // --------------------------------------------------------
    // Text: <i>Hey Chicken!</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("Mekka4t", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [PRO_001a] I Am Murloc (*) - COST:4
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Summon three, four, or five 1/1 Murlocs.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<MathRandTask>(3, 5));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<SummonTask>("PRO_001at", SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("PRO_001a", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [PRO_001at] Murloc (*) - COST:0 [ATK:1/HP:1]
    // - Race: Murloc, Set: Legacy
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("PRO_001at", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [PRO_001b] Rogues Do It... (*) - COST:4
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Deal 4 damage. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("PRO_001b", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [PRO_001c] Power of the Horde (*) - COST:4
    // - Set: Legacy
    // --------------------------------------------------------
    // Text: Summon a random Horde Warrior.
    // --------------------------------------------------------
    // Entourage: CS2_121, EX1_021, EX1_023, EX1_110, EX1_390, CS2_179
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cardDef.property.entourages = Entourages{ "CS2_121", "EX1_021", "EX1_023",
                                              "EX1_110", "EX1_390", "CS2_179" };
    cards.emplace("PRO_001c", cardDef);
}

void LegacyCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
