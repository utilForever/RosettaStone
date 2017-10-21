/*************************************************************************
> File Name: PlayerLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player loader that loads data from <playerName>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/PlayerLoader.h>

#include <fstream>
#include "Enums/StringToEnums.h"

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

		Player* p = nullptr;

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
		std::ofstream playerFile("Datas/" + p->GetName() + ".json");
		json j;

		if (!playerFile.is_open())
		{
			std::cout << "An error occurred while saving player data.\n";
		}
	}
}
