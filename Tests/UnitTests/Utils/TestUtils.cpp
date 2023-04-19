// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

namespace TestUtils
{
Card GenerateMinionCard(std::string&& id, int attack, int health)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::MINION);

    card.id = std::move(id);
    card.gameTags[GameTag::ATK] = attack;
    card.gameTags[GameTag::DAMAGE] = 0;
    card.gameTags[GameTag::HEALTH] = health;
    card.gameTags[GameTag::COST] = 0;
    card.gameTags[GameTag::CARDRACE] = static_cast<int>(Race::INVALID);

    return card;
}

Card GenerateWeaponCard(std::string&& id, int attack, int durability)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::WEAPON);

    card.id = std::move(id);
    card.gameTags[GameTag::ATK] = attack;
    card.gameTags[GameTag::DURABILITY] = durability;

    return card;
}

Card GenerateEnchantmentCard(std::string&& id)
{
    Card card;
    card.gameTags[GameTag::CARDTYPE] = static_cast<int>(CardType::ENCHANTMENT);

    card.id = std::move(id);

    return card;
}

void PlayMinionCard(Player* player, Card* card)
{
    FieldZone& fieldZone = *(player->GetFieldZone());
    const std::map<GameTag, int> tags;

    const auto minion = new Minion(player, card, tags);
    player->game->entityList.emplace(minion->GetGameTag(GameTag::ENTITY_ID),
                                     minion);

    fieldZone.Add(minion);
    fieldZone[minion->GetZonePosition()]->player = player;
}

void PlayWeaponCard(Player* player, Card* card)
{
    const std::map<GameTag, int> tags;

    const auto weapon = new Weapon(player, card, tags);
    player->game->entityList.emplace(weapon->GetGameTag(GameTag::ENTITY_ID),
                                     weapon);

    player->GetHero()->AddWeapon(*weapon);
}

void PlayEnchantmentCard(Player* player, Card* card, Entity* target)
{
    GraveyardZone& graveyardZone = *(player->GetGraveyardZone());
    const std::map<GameTag, int> tags;

    const auto enchantment = new Enchantment(player, card, tags, nullptr, target, -1);
    player->game->entityList.emplace(
        enchantment->GetGameTag(GameTag::ENTITY_ID), enchantment);

    graveyardZone.Add(enchantment);
}

void ChangeHeroPower(Player* player, Card* card)
{
    const auto newHeroPower = Entity::GetFromCard(player, card);

    delete player->GetHero()->heroPower;
    newHeroPower->SetGameTag(GameTag::ZONE, static_cast<int>(ZoneType::PLAY));
    player->GetHero()->heroPower = dynamic_cast<HeroPower*>(newHeroPower);
}

void ExpectCardEqual(const Card& card1, const Card& card2)
{
    CHECK_EQ(card1.id, card2.id);
    CHECK_EQ(card1.name, card2.name);
    CHECK_EQ(card1.text, card2.text);
    CHECK_EQ(card1.GetCardClass(), card2.GetCardClass());
    CHECK_EQ(card1.GetCardSet(), card2.GetCardSet());
    CHECK_EQ(card1.GetCardType(), card2.GetCardType());
    CHECK_EQ(card1.GetFaction(), card2.GetFaction());
    CHECK_EQ(card1.GetRace(), card2.GetRace());
    CHECK_EQ(card1.GetRarity(), card2.GetRarity());
    CHECK_EQ(card1.gameTags.at(GameTag::COLLECTIBLE),
             card2.gameTags.at(GameTag::COLLECTIBLE));
    CHECK_EQ(card1.gameTags.at(GameTag::COST),
             card2.gameTags.at(GameTag::COST));
    CHECK_EQ(card1.gameTags.at(GameTag::ATK), card2.gameTags.at(GameTag::ATK));
    CHECK_EQ(card1.gameTags.at(GameTag::HEALTH),
             card2.gameTags.at(GameTag::HEALTH));
    CHECK_EQ(card1.gameTags.at(GameTag::DURABILITY),
             card2.gameTags.at(GameTag::DURABILITY));
    CHECK_EQ(card1.gameTags, card2.gameTags);
    CHECK_EQ(card1.playRequirements, card2.playRequirements);
    CHECK_EQ(card1.entourages, card2.entourages);
    CHECK_EQ(card1.maxAllowedInDeck, card2.maxAllowedInDeck);
}

Playable* ChooseNthChoice(Game& game, std::size_t n)
{
    if (n > game.GetCurrentPlayer()->choice->choices.size())
    {
        throw std::out_of_range(
            "ChooseNthChoice() - n is greater than the size of choices");
    }

    const int pick = game.GetCurrentPlayer()->choice->choices[n - 1];
    game.Process(game.GetCurrentPlayer(),
                 ChooseTask::Pick(game.GetCurrentPlayer(), pick));

    return game.entityList[pick];
}

std::vector<Card*> GetChoiceCards(Game& game)
{
    if (!game.GetCurrentPlayer()->choice)
    {
        throw std::logic_error("There is no active choices.");
    }

    std::vector<int> choices = game.GetCurrentPlayer()->choice->choices;

    std::vector<Card*> result;
    result.reserve(choices.size());

    for (int choice : choices)
    {
        result.emplace_back(game.entityList[choice]->card);
    }

    return result;
}
}  // namespace TestUtils
