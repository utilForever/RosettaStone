/*************************************************************************
> File Name: Weapon.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Weapon class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_WEAPON_H
#define HEARTHSTONEPP_WEAPON_H

#include <Enums/Enums.h>
#include <Models/Card.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp
{
	class Weapon : public Card
	{
	public:
		Weapon(
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