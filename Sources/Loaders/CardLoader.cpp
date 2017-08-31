/*************************************************************************
> File Name: CardLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card loader that loads data from cards.json.
> Created Time: 2017/08/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/CardLoader.h>
#include <Models/Card.h>

#include <fstream>

namespace Hearthstonepp
{
	void CardLoader::Load()
	{
		// Read card data from JSON file
		std::ifstream cardFile("cards.json");
		json j;

		if (!cardFile.is_open())
		{
			throw std::runtime_error("Can't open cards.json");
		}

		cardFile >> j;

		Parse(j);

		cardFile.close();
	}

	void CardLoader::Parse(json& j)
	{
		std::vector<Card> cards;
		cards.reserve(j.size());
	}
}