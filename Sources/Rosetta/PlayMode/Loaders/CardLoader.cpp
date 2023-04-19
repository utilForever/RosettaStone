// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>
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
        throw std::runtime_error(
            "Can't open cards.json - Path: " RESOURCES_DIR);
    }

    cardFile >> j;

    cards.reserve(j.size());

    std::regex spellburstRegex("([<b>]*<b>Spellburst[</b>]*:</b>)");
    std::regex dormantRegex("<b>Dormant</b>");
    std::regex dormantTurnRegex("for ([[:digit:]]) turns");
    std::regex tradeableRegex("<b>Tradeable[.]*</b>");
    std::regex questlineRegex("<b>Questline:[ ]*</b>");
    std::regex infusedRegex("<b>.*Infused.*</b>");
    std::smatch values;

    for (auto& cardData : j)
    {
        int cardSet = cardData["set"].is_null()
                          ? 1
                          : static_cast<int>(StrToEnum<CardSet>(
                                cardData["set"].get<std::string>()));

        if (static_cast<CardSet>(cardSet) == CardSet::BATTLEGROUNDS ||
            static_cast<CardSet>(cardSet) == CardSet::LETTUCE ||
            static_cast<CardSet>(cardSet) == CardSet::PLACEHOLDER_202204)
        {
            continue;
        }

        const std::string id = cardData["id"].get<std::string>();
        const std::string name = cardData["name"].is_null()
                                     ? ""
                                     : cardData["name"].get<std::string>();
        const int dbfID =
            cardData["dbfId"].is_null() ? 0 : cardData["dbfId"].get<int>();
        std::string text = cardData["text"].is_null()
                               ? ""
                               : cardData["text"].get<std::string>();

        const int attack =
            cardData["attack"].is_null() ? 0 : cardData["attack"].get<int>();
        int cardRace = cardData["race"].is_null()
                           ? 0
                           : static_cast<int>(StrToEnum<Race>(
                                 cardData["race"].get<std::string>()));
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
        const int spellSchool =
            cardData["spellSchool"].is_null()
                ? 0
                : static_cast<int>(StrToEnum<SpellSchool>(
                      cardData["spellSchool"].get<std::string>()));

        // NOTE: Lantern of Power (LOEA16_3, LOEA16_3e), Timepiece of Horror
        // (LOEA16_4), Mirror of Doom(LOEA16_5), Mummy Zombie(LOEA16_5t) are
        // discovered cards by Arch-Thief Rafaam (LOE_092)
        if (dbfID == 19614 || dbfID == 36450 || dbfID == 19615 ||
            dbfID == 19616 || dbfID == 36452)
        {
            cardSet = static_cast<int>(CardSet::LOE);
        }

        std::map<GameTag, int> gameTags;
        for (auto& mechanic : cardData["mechanics"])
        {
            GameTag gameTag = StrToEnum<GameTag>(mechanic.get<std::string>());

            // NOTE: Erase mechanics 'FREEZE' of Frost Elemental (EX1_283)
            // NOTE: Erase mechanics 'FREEZE' of Frost Elemental (VAN_EX1_283)
            if ((dbfID == 512 || dbfID == 69906) && gameTag == GameTag::FREEZE)
            {
                continue;
            }

            gameTags.emplace(gameTag, 1);
        }

        // NOTE: Skyvateer (YOD_016), Cowardly Grunt (SW_021),
        //       Sesselie of the Fae Court (REV_319)
        //       doesn't have GameTag::DEATHRATTLE
        // NOTE: Icehoof Protector (AV_133) doesn't have GameTag::FREEZE
        // NOTE: Patient Assassin (VAN_EX1_522) doesn't have GameTag::POISONOUS
        // NOTE: Carousel Gryphon (DMF_064) doesn't have GameTag::DIVINE_SHIELD
        // NOTE: Healing Totem (AT_132_SHAMANa), Searing Totem (AT_132_SHAMANb),
        //       Stoneclaw Totem (AT_132_SHAMANc), Wrath of Air Totem
        //       (AT_132_SHAMANd), Strength Totem (AT_132_SHAMANe)
        //       doesn't have Race::TOTEM
        // NOTE: Wailing Demon (WC_003t), Naga Centaur (TSC_941t)
        //       doesn't have GameTag::TAUNT
        // NOTE: Spring the Trap (AV_224), Axe Berserker (AV_565)
        //       doesn't have GameTag::HONORABLEKILL
        if (dbfID == 56091 || dbfID == 64196 || dbfID == 78383)
        {
            gameTags.emplace(GameTag::DEATHRATTLE, 1);
        }
        else if (dbfID == 70236)
        {
            gameTags.emplace(GameTag::FREEZE, 1);
        }
        else if (dbfID == 69961)
        {
            gameTags.emplace(GameTag::POISONOUS, 1);
        }
        else if (dbfID == 61581)
        {
            gameTags.emplace(GameTag::DIVINE_SHIELD, 1);
        }
        else if (dbfID == 16221 || dbfID == 16222 || dbfID == 16223 ||
                 dbfID == 16225 || dbfID == 72268)
        {
            cardRace = static_cast<int>(Race::TOTEM);
        }
        else if (dbfID == 63500 || dbfID == 74675)
        {
            gameTags.emplace(GameTag::TAUNT, 1);
        }
        else if (dbfID == 67241 || dbfID == 73459)
        {
            gameTags.emplace(GameTag::HONORABLEKILL, 1);
        }

        Card* card = new Card();
        card->id = id;
        card->dbfID = dbfID;
        card->name = name;

        // Remove unnecessary substrings
        RemoveSubstrs(text, std::string{ "\n" });
        RemoveSubstrs(text, std::string{ "[x]" });

        // Remove unnecessary whitespace
        std::string::size_type pos = text.find_first_not_of(' ');
        text.erase(0, pos);
        text = std::regex_replace(text, std::regex("[' ']{2,}"), " ");

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
        card->gameTags[GameTag::SPELL_SCHOOL] = spellSchool;

        if (spellPower > 0)
        {
            card->gameTags[GameTag::SPELLPOWER] = spellPower;
        }
        if (overload > 0)
        {
            card->gameTags[GameTag::OVERLOAD] = overload;
        }

        if (std::regex_search(text, values, spellburstRegex))
        {
            card->gameTags[GameTag::SPELLBURST] = 1;
        }
        if (std::regex_search(text, values, dormantRegex))
        {
            card->gameTags[GameTag::DORMANT] = 1;

            if (std::regex_search(text, values, dormantTurnRegex))
            {
                card->gameTags[GameTag::TAG_SCRIPT_DATA_NUM_1] =
                    std::stoi(values[1].str());
            }
        }
        if (std::regex_search(text, values, tradeableRegex))
        {
            card->gameTags[GameTag::TRADEABLE] = 1;
        }
        if (std::regex_search(text, values, questlineRegex))
        {
            card->gameTags[GameTag::QUESTLINE] = 1;
        }
        if (std::regex_search(text, values, infusedRegex))
        {
            card->gameTags[GameTag::INFUSED] = 1;
        }

        // NOTE: Runic Carvings (SCH_612) has GameTag::OVERLOAD
        if (dbfID == 59542)
        {
            card->gameTags.erase(GameTag::OVERLOAD);
        }

        cards.emplace_back(card);
    }

    cardFile.close();
}
}  // namespace RosettaStone::PlayMode
