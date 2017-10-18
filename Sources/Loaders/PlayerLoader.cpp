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
	}
}