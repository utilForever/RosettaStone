#include <hspp/Commons/Macros.h>
#include <hspp/Loaders/AccountLoader.h>

#ifdef HEARTHSTONEPP_WINDOWS
#include <filesystem>
#endif
#ifdef HEARTHSTONEPP_LINUX
#include <experimental/filesystem>
#endif
#ifdef HEARTHSTONEPP_MACOSX
#include <stdlib.h>
#endif
#include <fstream>
#include <iostream>

#ifndef HEARTHSTONEPP_MACOSX
namespace filesystem = std::experimental::filesystem;
#endif

namespace Hearthstonepp
{
Account* AccountLoader::Load(std::string email) const
{
    // Read account data from JSON file
    std::ifstream playerFile("Datas/" + email + ".json");
    nlohmann::json j;

    if (!playerFile.is_open())
    {
        return nullptr;
    }

    Account* p;

    try
    {
        playerFile >> j;

        std::string nickname = j["nickname"].get<std::string>();

        std::vector<Deck*> decks;
        decks.reserve(j["decks"].size());

        if (!j["decks"].is_null())
        {
            for (auto& deck : j["decks"])
            {
                const CardClass deckClass = CardClass::_from_string(
                    deck["class"].get<std::string>().c_str());
                const std::string deckName = deck["name"].get<std::string>();

                Deck* d = new Deck(deckName, deckClass);
                for (auto& card : deck["cards"])
                {
                    const std::string cardID = card["id"].get<std::string>();
                    const int numOfCard = card["num"].get<int>();

                    d->AddCard(cardID, numOfCard);
                }

                decks.emplace_back(d);
            }
        }

        p = new Account(std::move(email), std::move(nickname), decks);
    }
    catch (...)
    {
        playerFile.close();

        return nullptr;
    }

    playerFile.close();

    return p;
}

void AccountLoader::Save(Account* account) const
{
    // Store account data to JSON file
#ifndef HEARTHSTONEPP_MACOSX
    filesystem::create_directory("Datas");
#else
    system("mkdir Datas");
#endif
    std::ofstream playerFile("Datas/" + account->GetEmail() + ".json");

    nlohmann::json j;

    if (!playerFile.is_open())
    {
        std::cout << "An error occurred while saving player data.\n";
    }

    try
    {
        j["nickname"] = account->GetNickname();

        j["decks"] = nlohmann::json::array();

        for (size_t deckIdx = 0; deckIdx < account->GetNumOfDeck(); ++deckIdx)
        {
            j["decks"].emplace_back(nlohmann::json::object(
                { { "class",
                    account->GetDeck(deckIdx)->GetClass()._to_string() },
                  { "name", account->GetDeck(deckIdx)->GetName() },
                  { "cards", nlohmann::json::array() } }));

            for (size_t cardIdx = 0;
                 cardIdx < account->GetDeck(deckIdx)->GetUniqueNumOfCards();
                 ++cardIdx)
            {
                j["decks"].at(deckIdx)["cards"].emplace_back(
                    nlohmann::json::object(
                        { { "id",
                            account->GetDeck(deckIdx)->GetCard(cardIdx).first },
                          { "num", account->GetDeck(deckIdx)
                                       ->GetCard(cardIdx)
                                       .second } }));
            }
        }

        playerFile << std::setw(4) << j << "\n";
    }
    catch (...)
    {
        std::cout << "An error occurred while saving player data.\n";

        playerFile.close();

        return;
    }

    playerFile.close();
}
}  // namespace Hearthstonepp
