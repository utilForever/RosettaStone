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

inline std::vector<Card> QueryCardSetList(CardSet cardSet)
{
    if (cardSet == +CardSet::ALL)
    {
        return Cards::GetInstance()->GetAllCards();
    }

    return Cards::GetInstance()->FindCardBySet(cardSet);
}

inline bool CheckCardImpl(const std::string& path, const std::string& id)
{
#ifndef HEARTHSTONEPP_MACOSX
    const filesystem::path p(path + "/Tests/UnitTests/CardSets");

    if (!filesystem::exists(p))
    {
        std::cerr << p << " does not exist\n";
        exit(EXIT_FAILURE);
    }

    if (!filesystem::is_directory(p))
    {
        std::cerr << p << " exists, but is not directory\n";
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
#endif
    return false;
}

inline void ExportFile(const std::string& projectPath, std::vector<Card>& cards)
{
    std::ofstream outputFile("result.md");
    if (outputFile)
    {
        size_t collectibleCardNum = 0;
        size_t implementedCardNum = 0;

        outputFile << "Set | ID | Name | Tag | Implemented\n";
        outputFile << ":---: | :---: | :---: | :---: | :---:\n";

        for (auto& card : cards)
        {
            if (!card.isCollectible)
            {
                continue;
            }

            collectibleCardNum++;

            std::string mechanicStr;
            for (auto& mechanic : card.mechanics)
            {
                mechanicStr += mechanic._to_string();
            }

            const bool isImplemented = CheckCardImpl(projectPath, card.id);
            if (isImplemented)
            {
                implementedCardNum++;
            }

            outputFile << card.cardSet._to_string() << " | " << card.id << " | "
                       << card.name << " | " << mechanicStr << " | "
                       << (isImplemented ? 'O' : ' ') << '\n';
        }

        const size_t implPercent = static_cast<size_t>(
            static_cast<double>(implementedCardNum) / collectibleCardNum * 100);
        outputFile << '\n';
        outputFile << "- Progress: " << implPercent << "% ("
                   << implementedCardNum << " of " << collectibleCardNum
                   << " Cards)";

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
    bool exportAllCard = false;
    std::string cardSetName;
    std::string projectPath;

    // Parsing
    auto parser = clara::Help(showHelp) |
                  clara::Opt(exportAllCard)["-a"]["--all"](
                      "Export all card set list to markdown format") |
                  clara::Opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export specific card set list to markdown format") |
                  clara::Opt(projectPath, "path")["-p"]["--path"](
                      "Hearthstone++ project path");

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

    std::vector<Card> cards;

    if (exportAllCard)
    {
        cards = QueryCardSetList(CardSet::ALL);
    }
    else if (!cardSetName.empty())
    {
        const auto maybeCardSet =
            CardSet::_from_string_nothrow(cardSetName.c_str());
        if (!maybeCardSet)
        {
            std::cerr << "Invalid card set name: " << cardSetName << '\n';
            exit(EXIT_FAILURE);
        }

        cards = QueryCardSetList(*maybeCardSet);
    }

    if (cards.empty())
    {
        std::cerr << "Your search did not generate any hits.\n";
        exit(EXIT_SUCCESS);
    }

    ExportFile(projectPath, cards);

    exit(EXIT_SUCCESS);
}