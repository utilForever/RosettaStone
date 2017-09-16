/*************************************************************************
> File Name: Card.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARD_H
#define HEARTHSTONEPP_CARD_H

#include <Enums/Enums.h>

#include <map>
#include <vector>

namespace Hearthstonepp
{
	struct Card
	{
		std::string ID;
		Rarity rarity;
		Faction faction;
		CardSet cardSet;
		CardClass cardClass;
		CardType cardType;
		Race race;

		std::string name;
		std::string text;

		bool collectible;
		int cost;
		int attack;
		int health;
		int durability;

		std::vector<GameTag> mechanics;
		std::map<PlayReq, int> playRequirements;
		std::vector<std::string> entourage;
	};
}

#endif
