/*************************************************************************
> File Name: PlayerLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player loader that loads data from <playerName>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Enums/EnumsToString.h>
#include <Enums/StringToEnums.h>
#include <Loaders/PlayerLoader.h>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace filesystem = std::experimental::filesystem;

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

			std::string name = std::move(j["name"].get<std::string>());

			std::vector<Deck*> decks;
			decks.reserve(j["decks"].size());

			if (!j["decks"].is_null())
			{
				for (auto& deck : j["decks"])
				{
					const CardClass deckClass = std::move(ConverterFromStringToCardClass.at(deck["class"].get<std::string>()));
					const std::string deckName = std::move(deck["name"].get<std::string>());

					Deck* d = new Deck(deckName, deckClass);
					for (auto& card : deck["cards"])
					{
						const std::string cardID = std::move(card["id"].get<std::string>());
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
		filesystem::create_directory("Datas");
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
					{ "class", ConverterFromCardClassToString.at(p->GetDeck(deckIdx)->GetClass()) },
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
