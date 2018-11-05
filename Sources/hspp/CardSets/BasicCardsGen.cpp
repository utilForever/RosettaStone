// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/CardSets/BasicCardsGen.h>
#include <hspp/Enchants/Effects.h>
#include <hspp/Tasks/BasicTasks/DestroyTask.h>
#include <hspp/Tasks/PowerTasks/AddEnchantmentTask.h>
#include <hspp/Tasks/PowerTasks/DiscardTask.h>
#include <hspp/Tasks/PowerTasks/HealFullTask.h>
#include <hspp/Tasks/PowerTasks/HealTask.h>

namespace Hearthstonepp
{
void BasicCardsGen::AddHeroes(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddHeroPowers(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddDruid(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddDruidNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddHunter(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddHunterNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddMage(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddMageNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPaladin(std::map<std::string, Power*>& cards)
{
    (void)cards;

    // --------------------------------------- MINION - PALADIN
    // [CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::HealTask(EntityType::MY_HERO, 6));
    cards.emplace("CS2_088", p);
}

void BasicCardsGen::AddPaladinNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPriest(std::map<std::string, Power*>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [CS1_112] Holy Nova - COST:5
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemies.
    //       Restore #2 Health to all friendly characters.
    // --------------------------------------------------------
    //Power* p = new Power;
    //p->powerTask.emplace_back(
    //    new PowerTask::DamageTask(EntityType::ENEMIES, 2));
    //p->powerTask.emplace_back(new PowerTask::HealTask(EntityType::FRIENDS, 2));
    //cards.emplace("CS1_112", p);
}

void BasicCardsGen::AddPriestNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddRogue(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddRogueNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddShaman(std::map<std::string, Power*>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Basic, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion
    //       to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Tag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::HealFullTask(EntityType::TARGET));
    p->powerTask.emplace_back(
        new PowerTask::AddEnchantmentTask("CS2_041e", EntityType::TARGET));
    cards.emplace("CS2_041", p);
}

void BasicCardsGen::AddShamanNonCollect(std::map<std::string, Power*>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: core,
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->enchant = new Enchant(Effects::Taunt);
    cards.emplace("CS2_041e", p);
}

void BasicCardsGen::AddWarlock(std::map<std::string, Power*>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [EX1_306] Succubus - COST:2 [ATK:4/HP:3]
    // - Fac: horde, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::DiscardTask(EntityType::MY_HAND));
    cards.emplace("EX1_306", p);
}

void BasicCardsGen::AddWarlockNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddWarrior(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddWarriorNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddNeutral(std::map<std::string, Power*>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Fac: alliance, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(
        new BasicTasks::DestroyTask(EntityType::OPPONENT_WEAPON));
    cards.emplace("EX1_066", p);
}

void BasicCardsGen::AddNeutralNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddAll(std::map<std::string, Power*>& cards)
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
}  // namespace Hearthstonepp
