// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BoomsdayCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void BoomsdayCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void BoomsdayCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - NEUTRAL
    // [BOT_511t] Bomb (*) - COST:5
    // - Set: Boomsday
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>\nYou take 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - TOPDECK = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTopdeckTask(std::make_shared<DamageTask>(EntityType::HERO, 5));
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::HERO, 5));
    cards.emplace("BOT_511t", CardDef(power));
}

void BoomsdayCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
