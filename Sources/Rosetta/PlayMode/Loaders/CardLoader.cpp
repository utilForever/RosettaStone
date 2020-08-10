// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Loaders/CardLoader.hpp>

#include <fstream>
#include <regex>

namespace RosettaStone::PlayMode
{
void CardLoader::Load(std::vector<Card*>& cards)
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

        const std::string name = cardData["name"].is_null()
                                     ? ""
                                     : cardData["name"].get<std::string>();
        const int dbfID =
            cardData["dbfId"].is_null() ? 0 : cardData["dbfId"].get<int>();
        const std::string text = cardData["text"].is_null()
                                     ? ""
                                     : cardData["text"].get<std::string>();

        const int attack =
            cardData["attack"].is_null() ? 0 : cardData["attack"].get<int>();
        const int cardRace = cardData["race"].is_null()
                                 ? 0
                                 : static_cast<int>(StrToEnum<Race>(
                                       cardData["race"].get<std::string>()));
        const int cardSet = cardData["set"].is_null()
                                ? 1
                                : static_cast<int>(StrToEnum<CardSet>(
                                      cardData["set"].get<std::string>()));
        const int cardType = cardData["type"].is_null()
                                 ? 0
                                 : static_cast<int>(StrToEnum<CardType>(
                                       cardData["type"].get<std::string>()));
        const int cardClass =
            cardData["cardClass"].is_null()
                ? 0
                : static_cast<int>(StrToEnum<CardClass>(
                      cardData["cardClass"].get<std::string>()));
        const int multiClassGroup =
            cardData["multiClassGroup"].is_null()
                ? 0
                : static_cast<int>(StrToEnum<MultiClassGroup>(
                      cardData["multiClassGroup"].get<std::string>()));
        const int collectible = cardData["collectible"].is_null()
                                    ? 0
                                    : cardData["collectible"].get<int>();
        const int cost =
            cardData["cost"].is_null() ? 0 : cardData["cost"].get<int>();
        const int durability = cardData["durability"].is_null()
                                   ? 0
                                   : cardData["durability"].get<int>();
        const int faction = cardData["faction"].is_null()
                                ? 0
                                : static_cast<int>(StrToEnum<Faction>(
                                      cardData["faction"].get<std::string>()));
        const int armor =
            cardData["armor"].is_null() ? 0 : cardData["armor"].get<int>();
        const int health =
            cardData["health"].is_null() ? 0 : cardData["health"].get<int>();
        const int rarity = cardData["rarity"].is_null()
                               ? 0
                               : static_cast<int>(StrToEnum<Rarity>(
                                     cardData["rarity"].get<std::string>()));
        const int spellPower = cardData["spellDamage"].is_null()
                                   ? 0
                                   : cardData["spellDamage"].get<int>();
        const int overload = cardData["overload"].is_null()
                                 ? 0
                                 : cardData["overload"].get<int>();

        std::map<GameTag, int> gameTags;
        for (auto& mechanic : cardData["mechanics"])
        {
            GameTag gameTag = StrToEnum<GameTag>(mechanic.get<std::string>());

            // NOTE: Erase mechanics 'FREEZE' of Frost Elemental (EX1_283)
            if (name == "Frost Elemental" && gameTag == GameTag::FREEZE)
            {
                continue;
            }

            gameTags.emplace(gameTag, 1);
        }

        Card* card = new Card();
        card->id = id;
        card->dbfID = dbfID;
        card->name = name;
        card->text = text;

        card->gameTags = gameTags;
        card->gameTags[GameTag::ATK] = attack;
        card->gameTags[GameTag::CARDRACE] = cardRace;
        card->gameTags[GameTag::CARD_SET] = cardSet;
        card->gameTags[GameTag::CARDTYPE] = cardType;
        card->gameTags[GameTag::CLASS] = cardClass;
        card->gameTags[GameTag::MULTI_CLASS_GROUP] = multiClassGroup;
        card->gameTags[GameTag::COLLECTIBLE] = collectible;
        card->gameTags[GameTag::COST] = cost;
        card->gameTags[GameTag::DAMAGE] = 0;
        card->gameTags[GameTag::DURABILITY] = durability;
        card->gameTags[GameTag::FACTION] = faction;
        card->gameTags[GameTag::ARMOR] = armor;
        card->gameTags[GameTag::HEALTH] = health;
        card->gameTags[GameTag::RARITY] = rarity;

        if (spellPower > 0)
        {
            card->gameTags[GameTag::SPELLPOWER] = spellPower;
        }
        if (overload > 0)
        {
            card->gameTags[GameTag::OVERLOAD] = overload;
        }

        static std::regex spellburstRegex("(<b>Spellburst:</b>)");
        std::smatch values;

        if (std::regex_search(text, values, spellburstRegex))
        {
            card->gameTags[GameTag::SPELLBURST] = 1;
        }

        cards.emplace_back(card);
    }

    cardFile.close();
}
}  // namespace RosettaStone::PlayMode
