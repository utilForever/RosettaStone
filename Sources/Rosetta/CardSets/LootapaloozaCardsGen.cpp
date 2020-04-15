// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/LootapaloozaCardsGen.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeEntityTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncPlayableTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void LootapaloozaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998h] Tolin's Goblet (*) - COST:3
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Draw a card. Fill your hand with copies of it.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            if (playables.empty())
            {
                return std::vector<Playable*>{};
            }

            Playable* drawedCard = playables[0];
            if (drawedCard == nullptr)
            {
                return std::vector<Playable*>{};
            }

            const int space = drawedCard->player->GetHandZone()->GetFreeSpace();
            for (int i = 0; i < space; ++i)
            {
                Playable* copiedCard =
                    Entity::GetFromCard(drawedCard->player, drawedCard->card);
                drawedCard->player->GetHandZone()->Add(copiedCard);
            }

            return std::vector<Playable*>{};
        }));
    cards.emplace("LOOT_998h", CardDef(power));

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998j] Zarog's Crown (*) - COST:3
    // - Faction: Neutral, Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Legendary</b> minion.
    //       Summon two copies of it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::LEGENDARY_MINION_SUMMON));
    power.AddAfterChooseTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY));
    cards.emplace(
        "LOOT_998j",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998l] Wondrous Wand (*) - COST:3
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Draw 3 cards. Reduce their Costs to (0).
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(3, true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("LOOT_998le", EntityType::STACK));
    cards.emplace("LOOT_998l", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_998le] Wand's Wonder (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("LOOT_998le", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_998k] Golden Kobold (*) - COST:3 [ATK:6/HP:6]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Replace your hand with <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::HAND, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY, false));
    cards.emplace("LOOT_998k", CardDef(power));
}

void LootapaloozaCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
}  // namespace RosettaStone
