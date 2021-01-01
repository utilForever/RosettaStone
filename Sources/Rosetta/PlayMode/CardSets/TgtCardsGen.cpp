// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/TgtCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
void TgtCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AT_132_DRUIDe] Dire Claws (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("AT_132_DRUIDe"));
    cards.emplace("AT_132_DRUIDe", CardDef(power));
}

void TgtCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- WEAPON - ROGUE
    // [AT_132_ROGUEt] Poisoned Dagger (*) - COST:1 [ATK:2/HP:0]
    // - Set: Tgt
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("AT_132_ROGUEt", CardDef(power));
}

void TgtCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANa] Healing Totem (*) - COST:0 [ATK:0/HP:2]
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: At the end of your turn, restore 1 Health to all friendly minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("AT_132_SHAMANa", CardDef(power));
}

void TgtCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
