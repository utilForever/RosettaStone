/*************************************************************************
> File Name: BasicCardsGen.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: BasicCardsGen class that stores the power of basic cards.
> Created Time: 2018/06/23
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <CardSets/BasicCardsGen.h>
#include <Enchants/Effects.h>
#include <Tasks/PowerTasks/AddEnchantmentTask.h>
#include <Tasks/PowerTasks/DestroyTask.h>
#include <Tasks/PowerTasks/HealFullTask.h>

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
}

void BasicCardsGen::AddPaladinNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPriest(std::map<std::string, Power*>& cards)
{
    (void)cards;
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
    p->powerTask.emplace_back(new PowerTask::AddEnchantmentTask("CS2_041e", EntityType::TARGET));
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
    (void)cards;
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
        new PowerTask::DestroyTask(EntityType::OPPONENT_WEAPON));
    cards.emplace("EX1_066", p);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: beast, Fac: neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_171", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Race: troll, Fac: HORDE, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - Taunt = 1
    // --------------------------------------------------------
    cards.emplace("CS2_179", nullptr);

	// --------------------------------------- MINION - NEUTRAL
    // [CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Race: element, Fac: neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    cards.emplace("CS2_118", nullptr);
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
}