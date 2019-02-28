// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Loaders/CardLoader.hpp>

#include <fstream>

namespace Hearthstonepp
{
void CardLoader::Load(std::vector<Card>& cards)
{
    // Read card data from JSON file
    std::ifstream cardFile(RESOURCES_DIR "cards.json");
    nlohmann::json j;

    if (!cardFile.is_open())
    {
        throw std::runtime_error("Can't open cards.json");
    }

    cardFile >> j;

    cards.reserve(j.size());

    for (auto& cardData : j)
    {
        const std::string id = cardData["id"].get<std::string>();
        // NOTE: Check invalid card type for 'Placeholder'
        // See https://hearthstone.gamepedia.com/Placeholder_Card
        if (id == "PlaceholderCard")
        {
            continue;
        }

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

        const int attack =
            cardData["attack"].is_null() ? -1 : cardData["attack"].get<int>();

        const int health =
            cardData["health"].is_null() ? -1 : cardData["health"].get<int>();

        const int spellDamage = cardData["spellDamage"].is_null()
                                    ? -1
                                    : cardData["spellDamage"].get<int>();

        const int durability = cardData["durability"].is_null()
                                   ? -1
                                   : cardData["durability"].get<int>();

        const std::size_t cost = cardData["cost"].is_null()
                                     ? 0
                                     : cardData["cost"].get<std::size_t>();

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
                PlayReq::_from_string(iter.key().c_str()),
                iter.value().get<int>());
        }

        std::vector<std::string> entourages;
        for (auto& entourage : cardData["entourage"])
        {
            entourages.emplace_back(entourage.get<std::string>());
        }

        Card card;
        card.id = id;
        card.rarity = rarity;
        card.faction = faction;
        card.cardSet = cardSet;
        card.cardClass = cardClass;
        card.cardType = cardType;
        card.race = race;
        card.name = name;
        card.text = text;
        card.isCollectible = collectible;

        card.attack =
            (attack != -1) ? std::optional<std::size_t>(attack) : std::nullopt;
        card.health =
            (health != -1) ? std::optional<std::size_t>(health) : std::nullopt;
        card.durability = (durability != -1)
                              ? std::optional<std::size_t>(durability)
                              : std::nullopt;
        card.spellDamage = (spellDamage != -1)
                               ? std::optional<std::size_t>(spellDamage)
                               : std::nullopt;

        card.cost = cost;
        card.mechanics = mechanics;
        card.playRequirements = playRequirements;
        card.entourages = entourages;
        card.Initialize();

        cards.emplace_back(card);
    }

    cardFile.close();
}
}  // namespace Hearthstonepp
