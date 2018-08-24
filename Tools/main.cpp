/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ tool.
> Created Time: 2018/08/21
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Cards.h>

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

inline std::vector<Card*> QueryCardSetList(CardSet cardSet)
{
    if (cardSet == +CardSet::ALL)
    {
        return Cards::GetInstance()->GetAllCards();
    }

    return Cards::GetInstance()->FindCardBySet(cardSet);
}

inline bool CheckCardImpl(std::string path, std::string id)
{
#ifndef HEARTHSTONEPP_MACOSX
    filesystem::path p(path + "/Tests/UnitTests/CardSets");

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
    std::cerr << "CheckCardImpl skip: apple-clang doesn't support <filesystem>\n";
#endif
    return false;
}

inline void ExportFile(const std::string& projectPath, std::vector<Card*> cards)
{
    std::ofstream outputFile("result.md");
    if (outputFile)
    {
        outputFile << "Set | ID | Name | Implemented\n";
        outputFile << ":---: | :---: | :---: | :---:\n";

        for (auto& card : cards)
        {
            if (!card->isCollectible)
            {
                continue;
            }

            bool isImplemented = CheckCardImpl(projectPath, card->id);

            outputFile << card->cardSet._to_string() << " | " << card->id
                       << " | " << card->name << " | "
                       << (isImplemented ? 'O' : ' ') << '\n';
        }
    }
    else
    {
        std::cerr << "Failed to write file result.md\n";
        exit(EXIT_FAILURE);
    }
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

    std::vector<Card*> cards;

    if (exportAllCard)
    {
        cards = QueryCardSetList(CardSet::ALL);
    }
    else if (!cardSetName.empty())
    {
        auto maybeCardSet = CardSet::_from_string_nothrow(cardSetName.c_str());
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