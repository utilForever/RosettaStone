// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CustomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
void BlackTempleCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [BT_258] Imprisoned Homunculus - COST:1 [ATK:2/HP:5]
    // - Race: Demon, Set: Black Temple, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::UNTOUCHABLE, 1));
    power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1, 2));
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { std::make_shared<CustomTask>(
        []([[maybe_unused]] Player* player, Entity* source,
           [[maybe_unused]] Playable* target) {
            const int value =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2);
            if (value <= 2)
            {
                source->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, value + 1);
            }

            if (value + 1 == source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1))
            {
                source->SetGameTag(GameTag::UNTOUCHABLE, 0);
                source->SetGameTag(GameTag::EXHAUSTED, 1);
            }
        }) };
    cards.emplace("BT_258", CardDef(power));
}

void BlackTempleCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
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
