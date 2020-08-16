// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Macros.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>

#include <lyra/cli_parser.hpp>
#include <lyra/help.hpp>
#include <lyra/opt.hpp>

#if defined(ROSETTASTONE_WINDOWS)
#include <filesystem>
#elif defined(ROSETTASTONE_LINUX)
#include <experimental/filesystem>
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#if defined(ROSETTASTONE_WINDOWS)
namespace filesystem = std::filesystem;
#elif defined(ROSETTASTONE_LINUX)
namespace filesystem = std::experimental::filesystem;
#endif

using namespace RosettaStone;
using namespace PlayMode;

inline bool CheckCardImpl(const std::string& path, const std::string& id)
{
#if defined(ROSETTASTONE_WINDOWS) || defined(ROSETTASTONE_LINUX)
    const filesystem::path p(path + "/Tests/UnitTests/PlayMode/CardSets");

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
                           [](const Card* c) {
                               return c->gameTags.at(GameTag::COLLECTIBLE) == 0;
                           }),
            cards.end());

        // Excludes 9 hero cards from CardSet::CORE
        if (cardSet == CardSet::CORE)
        {
            cards.erase(std::remove_if(cards.begin(), cards.end(),
                                       [](const Card* c) {
                                           return c->GetCardType() ==
                                                  CardType::HERO;
                                       }),
                        cards.end());
        }

        size_t impledCardNum = 0;
        const size_t allCardNum = cards.size();

        outputFile << "Set | ID | Name | Implemented\n";
        outputFile << ":---: | :---: | :---: | :---:\n";

        for (auto& card : cards)
        {
            std::string gameTagStr;
            for (auto& gameTag : card->gameTags)
            {
                gameTagStr += EnumToStr<GameTag>(gameTag.first);
            }

            const bool isImplemented = CheckCardImpl(projectPath, card->id);
            if (isImplemented)
            {
                impledCardNum++;
            }

            outputFile << EnumToStr<CardSet>(card->GetCardSet()) << " | "
                       << card->id << " | " << card->name << " | "
                       << (isImplemented ? 'O' : ' ') << '\n';
        }

        // Adds the number of card that implemented by ability
        const auto implPercent = static_cast<size_t>(
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
    auto parser = lyra::cli_parser() | lyra::help(showHelp) |
                  lyra::opt(isExportAllCard)["-a"]["--all"](
                      "Export a list of all expansion cards") |
                  lyra::opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export a list of specific expansion cards") |
                  lyra::opt(projectPath, "path")["-p"]["--path"](
                      "Specify RosettaStone project path");

    auto result = parser.parse({ argc, argv });

    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(EXIT_FAILURE);
    }

    if (showHelp)
    {
        std::cout << parser << '\n';
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
        cardSet = StrToEnum<CardSet>(cardSetName);
        if (cardSet == CardSet::INVALID)
        {
            std::cerr << "Invalid card set name: " << cardSetName << '\n';
            exit(EXIT_FAILURE);
        }
    }

    ExportFile(projectPath, cardSet);

    exit(EXIT_SUCCESS);
}