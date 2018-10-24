// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.h>

#include <better-enums/enum.h>
#include <clara.hpp>

#ifdef HEARTHSTONEPP_WINDOWS
#include <filesystem>
#endif
#ifdef HEARTHSTONEPP_LINUX
#include <experimental/filesystem>
#endif
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace Hearthstonepp;

#ifndef HEARTHSTONEPP_MACOSX
namespace filesystem = std::experimental::filesystem;
#endif

inline std::string ToString(const clara::Opt& opt)
{
    std::ostringstream oss;
    oss << (clara::Parser() | opt);
    return oss.str();
}

inline std::string ToString(const clara::Parser& p)
{
    std::ostringstream oss;
    oss << p;
    return oss.str();
}

inline std::vector<GameTag> CheckAbilityImpl(const std::string& path)
{
    std::map<std::string, GameTag> abilityStrMap = {
        { "Adapt", GameTag::ADAPT },
        { "Charge", GameTag::CHARGE },
        { "DivineShield", GameTag::DIVINE_SHIELD },
        { "Freeze", GameTag::FREEZE },
        { "Poisonous", GameTag::POISONOUS },
        { "Stealth", GameTag::STEALTH },
        { "Taunt", GameTag::TAUNT },
        { "Windfury", GameTag::WINDFURY }
    };

    std::vector<GameTag> result;

#ifndef HEARTHSTONEPP_MACOSX
    const filesystem::path p(
        path + "/Tests/UnitTests/Tasks/BasicTasks/CombatTaskTests.cpp");

    if (!filesystem::exists(p))
    {
        std::cerr << p << " does not exist\n";
        exit(EXIT_FAILURE);
    }

    if (!filesystem::is_regular_file(p))
    {
        std::cerr << p << " exists, but is not regular file\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream abilityFile;
    abilityFile.open(p.string());

    if (!abilityFile.is_open())
    {
        std::cerr << p << " couldn't open\n";
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(abilityFile, line))
    {
        for (auto& ability : abilityStrMap)
        {
            std::string sentence = "TEST(CombatTask, " + ability.first + ")";
            if (line.find(sentence, 0) != std::string::npos)
            {
                result.emplace_back(ability.second);
                break;
            }
        }
    }

#else
    std::cerr
        << "CheckAbilityImpl skip: apple-clang doesn't support <filesystem>\n";
    exit(EXIT_FAILURE);
#endif

    return result;
}

inline std::vector<Card> QueryCardSetList(const std::string& projectPath,
                                          CardSet cardSet, bool implCardOnly)
{
    // Excludes this cards because it has power that doesn't appear in ability
    // EX1_508: Grimscale Oracle (CORE)
    // CS2_146: Southsea Deckhand (EXPERT1)
    // DS1_188: Gladiator's Longbow (EXPERT1)
    // EX1_105: Mountain Giant (EXPERT1)
    // EX1_335: Lightspawn (EXPERT1)
    // EX1_350: Prophet Velen (EXPERT1)
    // EX1_411: Gorehowl (EXPERT1)
    // EX1_560: Nozdormu (EXPERT1)
    // EX1_586: Sea Giant (EXPERT1)
    // NEW1_022: Dread Corsair (EXPERT1)
    std::vector<std::string> excludeCardList = {
        "EX1_508", "CS2_146", "DS1_188", "EX1_105", "EX1_335",
        "EX1_350", "EX1_411", "EX1_560", "EX1_586", "NEW1_022",
    };

    if (cardSet == +CardSet::ALL)
    {
        return Cards::GetInstance()->GetAllCards();
    }

    std::vector<GameTag> abilityList{};
    if (implCardOnly)
    {
        abilityList = CheckAbilityImpl(projectPath);
    }

    std::vector<Card> result;
    for (auto& card : Cards::GetInstance()->FindCardBySet(cardSet))
    {
        if (implCardOnly)
        {
            bool isAbilityImpl = true;
            for (auto& mechanic : card.mechanics)
            {
                if (std::find(abilityList.begin(), abilityList.end(),
                              mechanic) == abilityList.end())
                {
                    isAbilityImpl = false;
                    break;
                }
            }

            // Counts minion and weapon card only
            if (isAbilityImpl && (card.cardType == +CardType::MINION ||
                                  card.cardType == +CardType::WEAPON))
            {
                result.emplace_back(card);
            }
        }
        else
        {
            result.emplace_back(card);
        }
    }

    return result;
}

inline bool CheckCardImpl(const std::string& path, std::vector<Card>& cards,
                          const std::string& id)
{
#ifndef HEARTHSTONEPP_MACOSX
    auto iter = std::find_if(cards.begin(), cards.end(),
                             [&id](const Card& c) { return c.id == id; });
    if (iter != cards.end())
    {
        return true;
    }

    const filesystem::path p(path + "/Tests/UnitTests/CardSets");

    if (!filesystem::exists(p))
    {
        std::cerr << p << " does not exist\n";
        exit(EXIT_FAILURE);
    }

    if (!filesystem::is_directory(p))
    {
        std::cerr << p << " exists, but is not directory\n";
        exit(EXIT_FAILURE);
    }

    for (auto&& file : filesystem::recursive_directory_iterator(p))
    {
        std::regex fileNamePattern(R"(.*\\(.*)\..*$)");
        std::smatch match;

        std::string pathStr = file.path().string();

        if (std::regex_match(pathStr, match, fileNamePattern))
        {
            if (match[1] == id)
            {
                return true;
            }
        }
    }
#else
    std::cerr
        << "CheckCardImpl skip: apple-clang doesn't support <filesystem>\n";
    exit(EXIT_FAILURE);
#endif

    return false;
}

inline void ExportFile(const std::string& projectPath, CardSet cardSet,
                       std::vector<Card>& cards)
{
    std::ofstream outputFile("result.md");
    if (outputFile)
    {
        auto cardsInCardSet = Cards::GetInstance()->FindCardBySet(cardSet);

        // Excludes cards that is not collectible
        cardsInCardSet.erase(
            std::remove_if(cardsInCardSet.begin(), cardsInCardSet.end(),
                           [](const Card& c) { return !c.isCollectible; }),
            cardsInCardSet.end());

        // Excludes 9 hero cards from CardSet::CORE
        if (cardSet == +CardSet::CORE)
        {
            cardsInCardSet.erase(
                std::remove_if(cardsInCardSet.begin(), cardsInCardSet.end(),
                               [](const Card& c) {
                                   return c.cardType == +CardType::HERO;
                               }),
                cardsInCardSet.end());
        }

        size_t impledCardNum = 0;
        const size_t allCardNum = cardsInCardSet.size();

        outputFile << "Set | ID | Name | Implemented\n";
        outputFile << ":---: | :---: | :---: | :---:\n";

        for (auto& card : cardsInCardSet)
        {
            std::string mechanicStr;
            for (auto& mechanic : card.mechanics)
            {
                mechanicStr += mechanic._to_string();
            }

            const bool isImplemented =
                CheckCardImpl(projectPath, cards, card.id);
            if (isImplemented)
            {
                impledCardNum++;
            }

            outputFile << card.cardSet._to_string() << " | " << card.id << " | "
                       << card.name << " | " << (isImplemented ? 'O' : ' ')
                       << '\n';
        }

        // Adds the number of card that implemented by ability
        const size_t implPercent = static_cast<size_t>(
            static_cast<double>(impledCardNum) / allCardNum * 100);
        outputFile << '\n';
        outputFile << "- Progress: " << implPercent << "% (" << impledCardNum
                   << " of " << allCardNum << " Cards)";

        std::cout << "Export file is completed.\n";
        exit(EXIT_SUCCESS);
    }

    std::cerr << "Failed to write file result.md\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    // Parse command
    bool showHelp = false;
    bool isExportAllCard = false;
    bool implCardOnly = false;
    std::string cardSetName;
    std::string projectPath;

    // Parsing
    auto parser = clara::Help(showHelp) |
                  clara::Opt(isExportAllCard)["-a"]["--all"](
                      "Export a list of all expansion cards") |
                  clara::Opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export a list of specific expansion cards") |
                  clara::Opt(implCardOnly)["-i"]["--implcardonly"](
                      "Export a list of cards that need to be implemented") |
                  clara::Opt(projectPath, "path")["-p"]["--path"](
                      "Specify Hearthstone++ project path");

    auto result = parser.parse(clara::Args(argc, argv));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(EXIT_FAILURE);
    }

    if (showHelp)
    {
        std::cout << ToString(parser) << '\n';
        exit(EXIT_SUCCESS);
    }

    if (projectPath.empty())
    {
        std::cout << "You should input Hearthstone++ project path\n";
        exit(EXIT_FAILURE);
    }

    CardSet cardSet = CardSet::INVALID;

    if (isExportAllCard)
    {
        cardSet = CardSet::ALL;
    }
    else if (!cardSetName.empty())
    {
        const auto convertedCardSet =
            CardSet::_from_string_nothrow(cardSetName.c_str());
        if (!convertedCardSet)
        {
            std::cerr << "Invalid card set name: " << cardSetName << '\n';
            exit(EXIT_FAILURE);
        }

        cardSet = *convertedCardSet;
    }

    std::vector<Card> cards =
        QueryCardSetList(projectPath, cardSet, implCardOnly);

    if (cards.empty())
    {
        std::cerr << "Your search did not generate any hits.\n";
        exit(EXIT_SUCCESS);
    }

    ExportFile(projectPath, cardSet, cards);

    exit(EXIT_SUCCESS);
}