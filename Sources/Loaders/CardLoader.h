/*************************************************************************
> File Name: CardLoader.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card loader that loads data from cards.json.
> Created Time: 2017/08/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARD_LOADER_H
#define HEARTHSTONEPP_CARD_LOADER_H

#include <json/json.hpp>
#include <Models/Card.h>

#include <vector>

namespace Hearthstonepp
{
	using json = nlohmann::json;

	class CardLoader
	{
	public:
	    std::vector<Card*> Load() const;
	};
}

#endif