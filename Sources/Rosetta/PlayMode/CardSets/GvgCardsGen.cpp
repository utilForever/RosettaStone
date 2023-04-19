// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/GvgCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void GvgCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GvgCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GvgCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [GVG_030] Anodized Robo Cub - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Choose One -</b> +1 Attack; or +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_031] Recycle - COST:6
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Shuffle an enemy minion into your opponent's deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GVG_032] Grove Tender - COST:3 [ATK:2/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give each player a Mana Crystal;
    //       or Each player draws a card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_033] Tree of Life - COST:9
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Restore all characters to full Health.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GVG_034] Mech-Bear-Cat - COST:6 [ATK:7/HP:6]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       add a <b>Spare Part</b> card to your hand.
    // --------------------------------------------------------
    // Entourage: PART_007, PART_006, PART_005, PART_001,
    //            PART_003, PART_002, PART_004
    // --------------------------------------------------------
    // RefTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GVG_035] Malorne - COST:7 [ATK:9/HP:7]
    // - Race: Beast, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle this minion into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - 542 = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_041] Dark Wispers - COST:6
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Summon 5 Wisps;
    //       or Give a minion +5/+5 and <b>Taunt</b>.
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

    // ----------------------------------------- MINION - DRUID
    // [GVG_080] Druid of the Fang - COST:5 [ATK:4/HP:4]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a Beast,
    //       transform this minion into a 7/7.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [GVG_030a] Attack Mode (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [GVG_030ae] Attack Mode (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_030b] Tank Mode (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [GVG_030be] Tank Mode (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_032a] Gift of Mana (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Give each player a Mana Crystal.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_032b] Gift of Cards (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Each player draws a card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_041a] Dark Wispers (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +5/+5 and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GVG_041b] Dark Wispers (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Summon 5 Wisps.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [GVG_041c] Dark Wispers (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +5/+5 and <b>Taunt</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GVG_080t] Druid of the Fang (*) - COST:5 [ATK:7/HP:7]
    // - Race: Beast, Set: Gvg
    // --------------------------------------------------------
}

void GvgCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [GVG_017] Call Pet - COST:2
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card. If it's a Beast, it costs (4) less.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [GVG_026] Feign Death - COST:2
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Trigger all <b>Deathrattles</b> on your minions.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [GVG_043] Glaivezooka - COST:2 [ATK:2/HP:0]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly minion
    //       +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GVG_046] King of Beasts - COST:5 [ATK:2/HP:6]
    // - Race: Beast, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> Gain +1 Attack
    //      for each other Beast you have.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GVG_048] Metaltooth Leaper - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Mechs +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GVG_049] Gahz'rilla - COST:7 [ATK:6/HP:9]
    // - Race: Beast, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, double its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [GVG_073] Cobra Shot - COST:5
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion and the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GVG_087] Steamwheedle Sniper - COST:2 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power can target minions.
    // --------------------------------------------------------
}

void GvgCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [GVG_043e] Glaivezooka (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [GVG_046e] The King (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [GVG_048e] Metal Teeth (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [GVG_049e] Might of Zul'Farrak (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Multiplying Attack.
    // --------------------------------------------------------
}

void GvgCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [GVG_001] Flamecannon - COST:2
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage to a random enemy minion
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GVG_002] Snowchugger - COST:2 [ATK:2/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [GVG_003] Unstable Portal - COST:2
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add a random minion to your hand. It costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GVG_004] Goblin Blastmage - COST:4 [ATK:5/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a Mech,
    //       deal 4 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [GVG_005] Echo of Medivh - COST:4
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put a copy of each friendly minion into your hand.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GVG_007] Flame Leviathan - COST:7 [ATK:7/HP:7]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: When you draw this, deal 2 damage to all characters.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GVG_122] Wee Spellstopper - COST:4 [ATK:2/HP:5]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Adjacent minions can't be targeted by
    //       spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GVG_123] Soot Spewer - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GvgCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [GVG_057] Seal of Light - COST:2
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 4 Health to your hero and gain
    //       +2 Attack this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GVG_058] Shielded Minibot - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [GVG_059] Coghammer - COST:3 [ATK:2/HP:0]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly minion
    //       <b>Divine Shield</b> and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GVG_060] Quartermaster - COST:5 [ATK:2/HP:5]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your Silver Hand Recruits +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [GVG_061] Muster for Battle - COST:3
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon three 1/1 Silver Hand Recruits.
    //       Equip a 1/4 Weapon.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GVG_062] Cobalt Guardian - COST:5 [ATK:6/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Mech, gain <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GVG_063] Bolvar Fordragon - COST:5 [ATK:1/HP:7]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies while this is in
    //       your hand, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GVG_101] Scarlet Purifier - COST:3 [ATK:4/HP:3]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all minions
    //       with <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [GVG_060e] Well Equipped (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [GVG_101e] Pure (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Stats.
    // --------------------------------------------------------
}

void GvgCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [GVG_008] Lightbomb - COST:6
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal damage to each minion equal to its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::ALL_MINIONS, std::vector<EntityType>(), true));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            const auto source = playables[0];

            for (std::size_t i = 1; i < playables.size(); ++i)
            {
                const auto character = dynamic_cast<Character*>(playables[i]);
                Generic::TakeDamageToCharacter(source, character,
                                               character->GetAttack(), true);
            }

            return std::vector<Playable*>{};
        }));
    cards.emplace("GVG_008", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [GVG_009] Shadowbomber - COST:1 [ATK:2/HP:1]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to each hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [GVG_010] Velen's Chosen - COST:3
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+4 and <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GVG_011] Shrinkmeister - COST:2 [ATK:3/HP:2]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion -2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [GVG_012] Light of the Naaru - COST:1
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Restore 3 Health. If the target is still damaged,
    //       summon a Lightwarden.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GVG_014] Vol'jin - COST:5 [ATK:6/HP:2]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap Health with another minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GVG_072] Shadowboxer - COST:2 [ATK:2/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a minion is healed,
    //       deal 1 damage to a random enemy.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GVG_083] Upgraded Repair Bot - COST:5 [ATK:5/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Mech +4 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 17
    // --------------------------------------------------------
}

void GvgCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [GVG_014a] Shadowed (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Health was swapped.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [GVG_069a] Repairs! (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +4 Health.
    // --------------------------------------------------------
}

void GvgCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - ROGUE
    // [GVG_022] Tinker's Sharpsword Oil - COST:4
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your weapon +3 Attack.
    //       <b>Combo:</b> Give a random friendly minion +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GVG_023] Goblin Auto-Barber - COST:2 [ATK:3/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [GVG_024] Cogmaster's Wrench - COST:3 [ATK:1/HP:0]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have a Mech.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GVG_025] One-eyed Cheat - COST:2 [ATK:4/HP:1]
    // - Race: Pirate, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Pirate, gain <b>Stealth</b>.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GVG_027] Iron Sensei - COST:3 [ATK:2/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another friendly Mech +2/+2.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GVG_028] Trade Prince Gallywix - COST:6 [ATK:5/HP:8]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell,
    //       gain a copy of it and give them a Coin.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [GVG_047] Sabotage - COST:4
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    //       <b>Combo:</b> And your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GVG_088] Ogre Ninja - COST:5 [ATK:6/HP:6]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - FORGETFUL = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [GVG_027e] Ironed Out (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void GvgCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [GVG_029] Ancestor's Call - COST:4
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put a random minion from each player's hand
    //       into the battlefield.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [GVG_036] Powermace - COST:3 [ATK:3/HP:0]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly Mech +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GVG_037] Whirling Zap-o-matic - COST:2 [ATK:3/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [GVG_038] Crackle - COST:2
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3-6 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GVG_039] Vitality Totem - COST:2 [ATK:0/HP:3]
    // - Race: Totem, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 4 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GVG_040] Siltfin Spiritwalker - COST:4 [ATK:2/HP:5]
    // - Race: Murloc, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever another friendly Murloc dies, draw a card.
    //       <b><b>Overload</b>:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GVG_042] Neptulon - COST:7 [ATK:7/HP:7]
    // - Race: Elemental, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 4 random Murlocs to your hand.
    //       <b>Overload:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - OVERLOAD = 3
    // - BATTLECRY = 1
    // - OVERLOAD_OWED = 3
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GVG_066] Dunemaul Shaman - COST:4 [ATK:5/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (1)
    //       50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // - FORGETFUL = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [GVG_036e] Powered (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
}

void GvgCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [GVG_015] Darkbomb - COST:2
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_018] Queen of Pain - COST:2 [ATK:1/HP:4]
    // - Race: Demon, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [GVG_019] Demonheart - COST:5
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    //       If it's a friendly Demon, give it +5/+5 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_020] Fel Cannon - COST:4 [ATK:3/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to a non-Mech minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_021] Mal'Ganis - COST:9 [ATK:9/HP:7]
    // - Race: Demon, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your other Demons have +2/+2.
    //       Your hero is <b>Immune</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [GVG_045] Imp-losion - COST:4
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2-4 damage to a minion.
    //       Summon a 1/1 Imp for each damage dealt.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_077] Anima Golem - COST:6 [ATK:9/HP:9]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of each turn,
    //       destroy this minion if it's your only one.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_100] Floating Watcher - COST:5 [ATK:4/HP:4]
    // - Race: Demon, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your hero takes damage on your turn,
    //       gain +2/+2.
    // --------------------------------------------------------
}

void GvgCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [GVG_019e] Demonheart (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [GVG_021e] Grasp of Mal'Ganis (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Mal'Ganis is granting +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GVG_045t] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Gvg
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [GVG_100e] Brow Furrow (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void GvgCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [GVG_050] Bouncing Blade - COST:3
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a random minion.
    //       Repeat until a minion dies.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_TOTAL_MINIONS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GVG_051] Warbot - COST:1 [ATK:1/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [GVG_052] Crush - COST:7
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. If you have a damaged minion,
    //       this costs (4) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GVG_053] Shieldmaiden - COST:6 [ATK:5/HP:5]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(5));
    cards.emplace("GVG_053", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [GVG_054] Ogre Warmaul - COST:3 [ATK:4/HP:0]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: 50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GVG_055] Screwjank Clunker - COST:4 [ATK:2/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Mech +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 17
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GVG_056] Iron Juggernaut - COST:6 [ATK:6/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a Mine into your opponent's
    //       deck. When drawn, it explodes for 10 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GVG_086] Siege Engine - COST:5 [ATK:5/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you gain Armor, give this minion +1 Attack.
    // --------------------------------------------------------
}

void GvgCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [GVG_051e] Enraged (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [GVG_055e] Screwy Jank (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [GVG_056t] Burrowing Mine (*) - COST:6
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: You take 10 damage.
    //       Draw a card. This explodes when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [GVG_086e] Armor Plated (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
}

void GvgCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_006] Mechwarper - COST:2 [ATK:2/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Mechs cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_013] Cogmaster - COST:1 [ATK:1/HP:2]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have a Mech.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            const auto minions = playable->player->GetFieldZone()->GetAll();

            for (auto& minion : minions)
            {
                if (minion->card->GetRace() == Race::MECHANICAL)
                {
                    return 2;
                }
            }

            return 0;
        }));
    cards.emplace("GVG_013", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_016] Fel Reaver - COST:5 [ATK:8/HP:8]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever your opponent plays a card,
    //       remove the top 3 cards of your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_044] Spider Tank - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("GVG_044", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_064] Puddlestomper - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: Gvg, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_065] Ogre Brute - COST:3 [ATK:4/HP:4]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: 50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - FORGETFUL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_067] Stonesplinter Trogg - COST:2 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell, gain +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_068] Burly Rockjaw Trogg - COST:4 [ATK:3/HP:5]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell, gain +2 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_069] Antique Healbot - COST:5 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 8 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_070] Salty Dog - COST:5 [ATK:7/HP:4]
    // - Race: Pirate, Set: Gvg, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_071] Lost Tallstrider - COST:4 [ATK:5/HP:4]
    // - Race: Beast, Set: Gvg, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_074] Kezan Mystic - COST:4 [ATK:4/HP:3]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of a random enemy
    //       <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_075] Ship's Cannon - COST:2 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a Pirate,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_076] Explosive Sheep - COST:2 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 2));
    cards.emplace("GVG_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_078] Mechanical Yeti - COST:4 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give each player a <b>Spare Part.</b>
    // --------------------------------------------------------
    // Entourage: PART_007, PART_006, PART_005, PART_001,
    //            PART_003, PART_002, PART_004
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_079] Force-Tank MAX - COST:8 [ATK:7/HP:7]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_081] Gilblin Stalker - COST:2 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_082] Clockwork Gnome - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a <b>Spare Part</b> card
    //       to your hand.
    // --------------------------------------------------------
    // Entourage: PART_007, PART_006, PART_005, PART_001,
    //            PART_003, PART_002, PART_004
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_084] Flying Machine - COST:3 [ATK:1/HP:4]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_085] Annoy-o-Tron - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("GVG_085", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_089] Illuminator - COST:3 [ATK:2/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you control a <b>Secret</b> at the end of your turn,
    //       restore 4 Health to your hero.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_090] Madder Bomber - COST:5 [ATK:5/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 6 damage randomly split
    //       between all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_091] Arcane Nullifier X-21 - COST:4 [ATK:2/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_092] Gnomish Experimenter - COST:3 [ATK:3/HP:2]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    //       If it's a minion, transform it into a Chicken.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_093] Target Dummy - COST:0 [ATK:0/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_094] Jeeves - COST:4 [ATK:1/HP:4]
    // - Race: Mechanical, Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of each player's turn,
    //       that player draws until they have 3 cards.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_095] Goblin Sapper - COST:3 [ATK:2/HP:4]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: Has +4 Attack while your opponent has 6 or
    //       more cards in hand.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_096] Piloted Shredder - COST:4 [ATK:4/HP:3]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_097] Lil' Exorcist - COST:3 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Gain +1/+1 for each enemy
    //       <b>Deathrattle</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_098] Gnomeregan Infantry - COST:3 [ATK:1/HP:4]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_099] Bomb Lobber - COST:5 [ATK:3/HP:3]
    // - Set: Gvg, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_102] Tinkertown Technician - COST:3 [ATK:3/HP:3]
    // - Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a Mech,
    //       gain +1/+1 and add a <b>Spare Part</b> to your hand.
    // --------------------------------------------------------
    // Entourage: PART_007, PART_006, PART_005, PART_001,
    //            PART_003, PART_002, PART_004
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_103] Micro Machine - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of each turn, gain +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_104] Hobgoblin - COST:3 [ATK:2/HP:3]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a 1-Attack minion, give it +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_105] Piloted Sky Golem - COST:6 [ATK:6/HP:4]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random 4-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_106] Junkbot - COST:5 [ATK:1/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever a friendly Mech dies, gain +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_107] Enhance-o Mechano - COST:4 [ATK:3/HP:2]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other minions
    //       <b>Windfury</b>, <b>Taunt</b>, or <b>Divine Shield</b>
    //       <i>(at random)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_108] Recombobulator - COST:2 [ATK:3/HP:2]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform a friendly minion
    //       into a random minion with the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_109] Mini-Mage - COST:3 [ATK:3/HP:1]
    // - Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("GVG_109", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_110] Dr. Boom - COST:7 [ATK:7/HP:7]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Boom Bots.
    //       <i>WARNING: Bots may explode.</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_111] Mimiron's Head - COST:5 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn, if you have at least 3 Mechs,
    //       destroy them all and form V-07-TR-0N.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_112] Mogor the Ogre - COST:6 [ATK:7/HP:6]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: All minions have a 50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_113] Foe Reaper 4000 - COST:8 [ATK:6/HP:9]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever it attacks.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_114] Sneed's Old Shredder - COST:8 [ATK:5/HP:7]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random
    //       <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_115] Toshley - COST:6 [ATK:5/HP:7]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Add a <b>Spare Part</b> card to your hand.
    // --------------------------------------------------------
    // Entourage: PART_007, PART_006, PART_005, PART_003,
    //            PART_002, PART_001, PART_004
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_116] Mekgineer Thermaplugg - COST:9 [ATK:9/HP:7]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever an enemy minion dies, summon a Leper Gnome.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_117] Gazlowe - COST:6 [ATK:3/HP:6]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you cast a 1-mana spell,
    //       add a random Mech to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_118] Troggzor the Earthinator - COST:7 [ATK:6/HP:6]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell,
    //       summon a Burly Rockjaw Trogg.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_119] Blingtron 3000 - COST:5 [ATK:3/HP:4]
    // - Race: Mechanical, Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a random weapon for each player.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_120] Hemet Nesingwary - COST:5 [ATK:6/HP:3]
    // - Set: Gvg, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Beast.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_121] Clockwork Giant - COST:12 [ATK:8/HP:8]
    // - Race: Mechanical, Set: Gvg, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each card in your opponent's hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->opponent->GetHandZone()->GetCount();
        }));
    cards.emplace("GVG_121", cardDef);
}

void GvgCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_010b] Velen's Chosen (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2/+4 and <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_011a] Shrink Ray (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: -2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_022a] Tinker's Sharpsword Oil (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_022b] Tinker's Sharpsword Oil (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_023a] Extra Sharp (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [GVG_028t] Gallywix's Coin (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    //       <i>(Won't trigger Gallywix.)</i>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_057a] Seal of Light (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_063a] Retribution (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_067a] Metabolized Magic (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_068a] Metabolized Magic (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_076a] Pistons (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_092t] Chicken (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gvg
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_102e] Might of Tinkertown (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_104a] HERE, TAKE BUFF. (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GVG_106e] Junked Up (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_110t] Boom Bot (*) - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Gvg
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1-4 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<MathRandTask>(1, 4));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK));
    cards.emplace("GVG_110t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GVG_111t] V-07-TR-0N (*) - COST:8 [ATK:4/HP:8]
    // - Race: Mechanical, Set: Gvg
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Mega-Windfury</b>
    //       <i>(Can attack four times a turn.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_001] Armor Plating (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Give a minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [PART_001e] Armor Plating (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_002] Time Rewinder (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_003] Rusty Horn (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Give a minion <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_004] Finicky Cloakfield (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Give a friendly minion <b>Stealth</b>
    //       until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [PART_004e] Cloaked (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_005] Emergency Coolant (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_006] Reversing Switch (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Swap a minion's Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [PART_006a] Switched (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped by Reversing Switch.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [PART_007] Whirling Blades (*) - COST:1
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: Give a minion +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [PART_007e] Whirling Blades (*) - COST:0
    // - Set: Gvg
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - SPARE_PART = 1
    // --------------------------------------------------------
}

void GvgCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
