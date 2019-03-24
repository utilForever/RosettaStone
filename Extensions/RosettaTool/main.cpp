// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Macros.hpp>

#include <better-enums/enum.h>
#include <clara.hpp>

#if defined(ROSETTASTONE_WINDOWS)
#include <filesystem>
#elif defined(ROSETTASTONE_LINUX)
#include <experimental/filesystem>
#endif
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#if defined(ROSETTASTONE_WINDOWS)
namespace filesystem = std::filesystem;
#elif defined(ROSETTASTONE_LINUX)
namespace filesystem = std::experimental::filesystem;
#endif

using namespace RosettaStone;

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
    std::vector<GameTag> result;

#if defined(ROSETTASTONE_WINDOWS) || defined(ROSETTASTONE_LINUX)
    std::map<std::string, GameTag> abilityStrMap = {
        { "Adapt", GameTag::ADAPT },
        { "Charge", GameTag::CHARGE },
        { "DivineShield", GameTag::DIVINE_SHIELD },
        { "Freeze", GameTag::FREEZE },
        { "Poisonous", GameTag::POISONOUS },
        { "Stealth", GameTag::STEALTH },
        { "Taunt", GameTag::TAUNT },
        { "Windfury", GameTag::WINDFURY },
        { "Immune", GameTag::IMMUNE },
    };

    const filesystem::path p(
        path + "/Tests/UnitTests/Tasks/PlayerTasks/AttackTaskTests.cpp");

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
            std::string sentence = "TEST(AttackTask, " + ability.first + ")";
            if (line.find(sentence, 0) != std::string::npos)
            {
                result.emplace_back(ability.second);
                break;
            }
        }
    }
#elif defined(ROSETTASTONE_MACOSX)
    std::cerr
        << "CheckAbilityImpl skip: apple-clang doesn't support <filesystem>\n";
    exit(EXIT_FAILURE);
#endif

    return result;
}

inline bool CheckCardImpl(const std::string& path,
                          const std::vector<GameTag>& abilityList,
                          const std::string& id)
{
#if defined(ROSETTASTONE_WINDOWS) || defined(ROSETTASTONE_LINUX)
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
        std::ifstream fileInput;
        std::string line;

        fileInput.open(file.path().string());

        if (fileInput.is_open())
        {
            while (getline(fileInput, line))
            {
                if (line.find(id, 0) != std::string::npos)
                {
                    return true;
                }
            }
        }

        fileInput.close();
    }

    Card card = Cards::GetInstance().FindCardByID(id);

    bool isAbilityImpl = true;
    for (auto& mechanic : card.mechanics)
    {
        if (std::find(abilityList.begin(), abilityList.end(), mechanic) ==
            abilityList.end())
        {
            isAbilityImpl = false;
            break;
        }
    }

    // Counts minion and weapon card only
    if (isAbilityImpl && (card.cardType == +CardType::MINION ||
                          card.cardType == +CardType::WEAPON))
    {
        // Excludes cards that its power doesn't appear in ability
        return std::find(excludeCardList.begin(), excludeCardList.end(),
                         card.id) == excludeCardList.end();
    }
#elif defined(ROSETTASTONE_MACOSX)
    std::cerr
        << "CheckCardImpl skip: apple-clang doesn't support <filesystem>\n";
    exit(EXIT_FAILURE);
#endif

    return false;
}

inline void ExportFile(const std::string& projectPath, CardSet cardSet)
{
    std::ofstream outputFile("result.md");
    if (outputFile)
    {
        auto cards = Cards::GetInstance().FindCardBySet(cardSet);
        if (cards.empty())
        {
            std::cerr << "Your search did not generate any hits.\n";
            exit(EXIT_SUCCESS);
        }

        // Excludes cards that is not collectible
        cards.erase(
            std::remove_if(cards.begin(), cards.end(),
                           [](const Card& c) { return !c.isCollectible; }),
            cards.end());

        // Excludes 9 hero cards from CardSet::CORE
        if (cardSet == +CardSet::CORE)
        {
            cards.erase(std::remove_if(cards.begin(), cards.end(),
                                       [](const Card& c) {
                                           return c.cardType == +CardType::HERO;
                                       }),
                        cards.end());
        }

        size_t impledCardNum = 0;
        const size_t allCardNum = cards.size();

        outputFile << "Set | ID | Name | Implemented\n";
        outputFile << ":---: | :---: | :---: | :---:\n";

        std::vector<GameTag> abilityList = CheckAbilityImpl(projectPath);

        for (auto& card : cards)
        {
            std::string mechanicStr;
            for (auto& mechanic : card.mechanics)
            {
                mechanicStr += mechanic._to_string();
            }

            const bool isImplemented =
                CheckCardImpl(projectPath, abilityList, card.id);
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
    std::string cardSetName;
    std::string projectPath;

    // Parsing
    auto parser = clara::Help(showHelp) |
                  clara::Opt(isExportAllCard)["-a"]["--all"](
                      "Export a list of all expansion cards") |
                  clara::Opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export a list of specific expansion cards") |
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
        std::cout << "You should input RosettaStone project path\n";
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

    ExportFile(projectPath, cardSet);

    exit(EXIT_SUCCESS);
}