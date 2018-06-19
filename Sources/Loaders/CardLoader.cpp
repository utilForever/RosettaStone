/*************************************************************************
> File Name: CardLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card loader that loads data from cards.json.
> Created Time: 2017/08/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Hero.h>
#include <Cards/Minion.h>
#include <Cards/Spell.h>
#include <Cards/Weapon.h>
#include <Enchants/Enchant.h>
#include <Enchants/HeroPower.h>
#include <Loaders/CardLoader.h>

#include <fstream>

namespace Hearthstonepp
{
std::vector<Card*> CardLoader::Load() const
{
    // Read card data from JSON file
    std::ifstream cardFile(RESOURCES_DIR "cards.json");
    json j;

    if (!cardFile.is_open())
    {
        throw std::runtime_error("Can't open cards.json");
    }

    cardFile >> j;

    std::vector<Card*> cards;
    cards.reserve(j.size());

    for (auto& cardData : j)
    {
        const std::string id = cardData["id"].get<std::string>();
        const Rarity rarity =
            cardData["rarity"].is_null()
                ? +Rarity::FREE
                : Rarity::_from_string(
                      cardData["rarity"].get<std::string>().c_str());
        const Faction faction =
            cardData["faction"].is_null()
                ? +Faction::NEUTRAL
                : Faction::_from_string(
                      cardData["faction"].get<std::string>().c_str());
        const CardSet cardSet =
            cardData["set"].is_null()
                ? +CardSet::NONE
                : CardSet::_from_string(
                      cardData["set"].get<std::string>().c_str());
        const CardClass cardClass =
            cardData["cardClass"].is_null()
                ? +CardClass::NEUTRAL
                : CardClass::_from_string(
                      cardData["cardClass"].get<std::string>().c_str());
        const CardType cardType =
            cardData["type"].is_null()
                ? +CardType::INVALID
                : CardType::_from_string(
                      cardData["type"].get<std::string>().c_str());
        const Race race =
            cardData["race"].is_null()
                ? +Race::INVALID
                : Race::_from_string(
                      cardData["race"].get<std::string>().c_str());

        const std::string name =
            cardData["name"].is_null()
                ? ""
                : cardData["name"]["enUS"].get<std::string>();
        const std::string text =
            cardData["text"].is_null()
                ? ""
                : cardData["text"]["enUS"].get<std::string>();

        const bool collectible = cardData["collectible"].is_null()
                                     ? false
                                     : cardData["collectible"].get<bool>();
        const int cost =
            cardData["cost"].is_null() ? -1 : cardData["cost"].get<int>();
        const int durability = cardData["durability"].is_null()
                                   ? -1
                                   : cardData["durability"].get<int>();

        const int attack =
            cardData["attack"].is_null() ? -1 : cardData["attack"].get<int>();

        std::vector<GameTag> mechanics;
        for (auto& mechanic : cardData["mechanics"])
        {
            mechanics.emplace_back(
                GameTag::_from_string(mechanic.get<std::string>().c_str()));
        }

        std::map<PlayReq, int> playRequirements;
        for (auto iter = cardData["playRequirements"].begin();
             iter != cardData["playRequirements"].end(); ++iter)
        {
            playRequirements.try_emplace(
                PlayReq::_from_string(iter.key().c_str())),
                iter.value().get<int>();
        }

        std::vector<std::string> entourages;
        for (auto& entourage : cardData["entourage"])
        {
            entourages.emplace_back(entourage.get<std::string>());
        }

        // Check invalid card type for 'Placeholder'
        // See https://hearthstone.gamepedia.com/Placeholder_Card
        if (cardType == +CardType::INVALID)
        {
            continue;
        }

        Card* card = nullptr;
        switch (cardType)
        {
            case +CardType::ENCHANTMENT:
                card = new Enchantment();
                break;
            case +CardType::HERO:
                card = new Hero();
                break;
            case +CardType::HERO_POWER:
                card = new HeroPower();
                break;
            case +CardType::MINION:
                card = new Minion();
                break;
            case +CardType::SPELL:
                card = new Spell();
                break;
            case +CardType::WEAPON:
                card = new Weapon();
                break;
            default:
                // TODO: Handle invalid card type
                break;
        }

        if (card == nullptr)
        {
            continue;
        }

        card->id = id;
        card->rarity = rarity;
        card->faction = faction;
        card->cardSet = cardSet;
        card->cardClass = cardClass;
        card->cardType = cardType;
        card->race = race;
        card->name = name;
        card->text = text;
        card->isCollectible = collectible;
        card->cost = cost;
        card->mechanics = mechanics;
        card->playRequirements = playRequirements;
        card->entourages = entourages;
        card->Initialize();

        if (cardType == +CardType::WEAPON)
        {
            const auto weapon = dynamic_cast<Weapon*>(card);
            weapon->attack = attack;
            weapon->durability = durability;
        }

        cards.emplace_back(card);
    }

    cardFile.close();

    return cards;
}
}