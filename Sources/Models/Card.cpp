/*************************************************************************
> File Name: Card.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/30
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Card.h>

namespace Hearthstonepp
{
	Card::Card(
		std::string id, Rarity rarity, Faction faction, CardSet cardSet,
		CardClass cardClass, CardType cardType, Race race,
		std::string name, std::string text, bool collectible,
		int cost, int attack, int health, int durability,
		std::vector<GameTag> mechanics,
		std::map<PlayReq, int> playRequirements,
		std::vector<std::string> entourages) :
		m_id(std::move(id)), m_rarity(rarity), m_faction(faction), m_cardSet(cardSet),
		m_cardClass(cardClass), m_cardType(cardType), m_race(race),
		m_name(std::move(name)), m_text(std::move(text)), m_collectible(collectible),
		m_cost(cost), m_attack(attack), m_health(health), m_durability(durability),
		m_mechanics(std::move(mechanics)),
		m_playRequirements(std::move(playRequirements)),
		m_entourages(std::move(entourages))
	{

	}

    std::string Card::GetID() const
	{
        return m_id;
	}

	void Card::ShowInfo() const
	{
		
	}
}