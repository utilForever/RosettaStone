/*************************************************************************
> File Name: Spell.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Spell class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_SPELL_H
#define HEARTHSTONEPP_SPELL_H

#include <Enums/Enums.h>
#include <Models/Card.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp
{
	class Spell : public Card
	{
	public:
		Spell(
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