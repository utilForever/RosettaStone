/*************************************************************************
> File Name: PlayerLoader.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player loader that loads data from <playerName>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYER_LOADER_H
#define HEARTHSTONEPP_PLAYER_LOADER_H

#include <json/json.hpp>
#include <Models/Player.h>

namespace Hearthstonepp
{
	using json = nlohmann::json;

	class PlayerLoader
	{
	public:
		Player* Load(std::string playerName) const;
		void Save(Player* p) const;
	};
}

#endif