/*************************************************************************
> File Name: PlayerLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player loader that loads data from <playerName>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Commons/Macros.h>
#include <Loaders/PlayerLoader.h>

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
	Player* PlayerLoader::Load(std::string playerID) const
	{
		// Read player data from JSON file
		std::ifstream playerFile("Datas/" + playerID + ".json");
		json j;

		if (!playerFile.is_open())
		{
			return nullptr;
		}

		Player* p;

		try
		{
			playerFile >> j;

			std::string name = j["name"].get<std::string>();

			std::vector<Deck*> decks;
			decks.reserve(j["decks"].size());

			if (!j["decks"].is_null())
			{
				for (auto& deck : j["decks"])
				{
					const CardClass deckClass = CardClass::_from_string(deck["class"].get<std::string>().c_str());
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

			p = new Player(std::move(playerID), std::move(name), decks);
		}
		catch (...)
		{
			playerFile.close();

			return nullptr;
		}

		playerFile.close();

		return p;
	}

	void PlayerLoader::Save(Player* p) const
	{
		// Store player data to JSON file
#ifndef HEARTHSTONEPP_MACOSX
		filesystem::create_directory("Datas");
#else
		system("mkdir Datas");
#endif
		std::ofstream playerFile("Datas/" + p->GetID() + ".json");

		json j;

		if (!playerFile.is_open())
		{
			std::cout << "An error occurred while saving player data.\n";
		}

		try
		{
			j["name"] = p->GetName();

			j["decks"] = json::array();

			for (size_t deckIdx = 0; deckIdx < p->GetNumOfDeck(); ++deckIdx)
			{
				j["decks"].emplace_back(json::object({
					{ "class", p->GetDeck(deckIdx)->GetClass()._to_string() },
					{ "name", p->GetDeck(deckIdx)->GetName() },
					{ "cards", json::array() }
				}));

				for (size_t cardIdx = 0; cardIdx < p->GetDeck(deckIdx)->GetUniqueNumOfCards(); ++cardIdx)
				{
					j["decks"].at(deckIdx)["cards"].emplace_back(json::object({
						{ "id", p->GetDeck(deckIdx)->GetCard(cardIdx).first },
						{ "num", p->GetDeck(deckIdx)->GetCard(cardIdx).second }
					}));
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
}
