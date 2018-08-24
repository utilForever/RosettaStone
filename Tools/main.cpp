
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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace Hearthstonepp;

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

inline void ExportFile(const std::string& fileName, std::vector<Card*> cards)
{
    std::ofstream outputFile(fileName + ".md");
    if (outputFile)
    {
        outputFile << "Set | ID | Name\n";
        outputFile << "--- | --- | ---\n";

        for (auto& card : cards)
        {
            if (!card->isCollectible)
            {
                continue;
            }

            outputFile << card->cardSet._to_string() << " | " << card->id
                       << " | " << card->name << '\n';
        }
    }
    else
    {
        fprintf(stderr, "Failed to write file %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    // Parse command
    bool showHelp = false;
    bool exportAllCard = false;
    std::string cardSetName;

    // Parsing
    auto parser = clara::Help(showHelp) |
                  clara::Opt(exportAllCard)["-a"]["--all"](
                      "Export all card set list to markdown format") |
                  clara::Opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export specific card set list to markdown format");

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

    ExportFile("result", cards);

    exit(EXIT_SUCCESS);
}