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

namespace Hearthstonepp
{
	Player* PlayerLoader::Load(std::string playerName) const
	{
		// Read player data from JSON file
		std::ifstream playerFile("Datas/" + playerName + ".json");
		json j;

		if (!playerFile.is_open())
		{
			return nullptr;
		}

		playerFile >> j;

		Player* p = nullptr;

		const std::string name = std::move(j["name"].get<std::string>());
		
		std::vector<Deck*> decks;
		if (!j["decks"].is_null())
		{
			for (auto& deck : j["decks"])
			{
				std::string playerClass = std::move(deck["class"].get<std::string>());
				std::string deckName = std::move(deck["name"].get<std::string>());

				// TODO: Parse cards				
			}
		}
	}
}