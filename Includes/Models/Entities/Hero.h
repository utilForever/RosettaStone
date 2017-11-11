/*************************************************************************
> File Name: Hero.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hero class inherits from Card class.
> Created Time: 2017/08/21
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_HERO_H
#define HEARTHSTONEPP_HERO_H

#include <Enums/Enums.h>
#include <Models/Card.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp 
{
	class Hero : public Card
	{
	public:
		Hero(
			std::string id, Rarity rarity, Faction faction, CardSet cardSet,
			CardClass cardClass, CardType cardType, Race race,
			std::string name, std::string text, bool collectible,
			int cost, int attack, int health, int durability,
			std::vector<GameTag> mechanics,
			std::map<PlayReq, int> playRequirements,
			std::vector<std::string> entourages);

		void ShowInfo() const override;
	};
}

#endif