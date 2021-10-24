// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveEffect.hpp>
#include <Rosetta/PlayMode/CardSets/HoFCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void HoFCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [NEW1_004] Vanish - COST:6
    // - Set: Legacy, Rarity: Free
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::ALL_MINIONS));
    cards.emplace("NEW1_004", CardDef(power));
}

void HoFCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
    // - Race: Murloc, Faction: Neutral. Set: Legacy, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>. Has +1 Attack for each other Murloc on the
    // battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [](Playable* playable) {
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
    cards.emplace("EX1_062", CardDef(power));
}

void HoFCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
