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
		std::vector<Card*> cards;
		cards.reserve(j.size());

		// For test
		int nHeroCard = 0, nMinionCard = 0, nSpellCard = 0, nEnchantmentCard = 0, nWeaponCard = 0, nHeroPowerCard = 0;

		for (auto& card : j)
		{
			if (card["type"] == "HERO")
			{
				nHeroCard++;
			}
			else if (card["type"] == "MINION")
			{
				nMinionCard++;
			}
			else if (card["type"] == "SPELL")
			{
				nSpellCard++;
			}
			else if (card["type"] == "ENCHANTMENT")
			{
				nEnchantmentCard++;
			}
			else if (card["type"] == "WEAPON")
			{
				nWeaponCard++;
			}
			else if (card["type"] == "HERO_POWER")
			{
				nHeroPowerCard++;
			}
		}

		std::cout << "nHeroCard = " << nHeroCard << std::endl;
		std::cout << "nMinionCard = " << nMinionCard << std::endl;
		std::cout << "nSpellCard = " << nSpellCard << std::endl;
		std::cout << "nEnchantmentCard = " << nEnchantmentCard << std::endl;
		std::cout << "nWeaponCard = " << nWeaponCard << std::endl;
		std::cout << "nHeroPowerCard = " << nHeroPowerCard << std::endl;
		std::cout << "Total = " << nHeroCard + nMinionCard + nSpellCard + nEnchantmentCard + nWeaponCard + nHeroPowerCard << std::endl;
	}
}