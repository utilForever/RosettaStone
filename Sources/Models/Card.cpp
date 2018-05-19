/*************************************************************************
> File Name: Card.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/30
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Card.h>

#include <algorithm>
#include <iostream>

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
		m_maxAllowedInDeck = (rarity == +Rarity::LEGENDARY) ? 1 : 2;
	}

	std::string Card::GetID() const
	{
		return m_id;
	}

	Rarity Card::GetRarity() const
	{
		return m_rarity;
	}

	CardClass Card::GetCardClass() const
	{
		return m_cardClass;
	}

	CardType Card::GetCardType() const
	{
		return m_cardType;
	}

	Race Card::GetRace() const
	{
		return m_race;
	}

	std::string Card::GetName() const
	{
		return m_name;
	}

	bool Card::GetCollectible() const
	{
		return m_collectible;
	}

	int Card::GetCost() const
	{
		return m_cost;
	}

	int Card::GetAttack() const
	{
		return m_attack;
	}

	int Card::GetHealth() const
	{
		return m_health;
	}

	void Card::SetHealth(int health)
	{
		m_health = health;
	}

	int Card::GetDurability() const
	{
		return m_durability;
	}

	std::vector<GameTag> Card::GetMechanics() const
	{
		return m_mechanics;
	}

	bool Card::HasMechanic(GameTag mechanic) const
	{
		if (std::find(m_mechanics.begin(), m_mechanics.end(), mechanic) != m_mechanics.end())
		{
			return true;
		}

		return false;
	}

	unsigned int Card::GetMaxAllowedInDeck() const
	{
		return m_maxAllowedInDeck;
	}

	void Card::ShowBriefInfo() const
	{
		std::cout << m_name.c_str() << " (" << m_id.c_str() << ") ";
	}

	void Card::ShowInfo() const
	{
		std::cout << "ID: " << m_id.c_str() << '\n';
		std::cout << "Name: " << m_name.c_str() << '\n';
		std::cout << "Text: " << m_text.c_str() << '\n';
		std::cout << "Rarity: " << m_rarity._to_string() << '\n';
		std::cout << "Faction: " << m_faction._to_string() << '\n';
		std::cout << "CardSet: " << m_cardSet._to_string() << '\n';
		std::cout << "CardClass: " << m_cardClass._to_string() << '\n';
		std::cout << "CardType: " << m_cardType._to_string() << '\n';
		std::cout << "Race: " << m_race._to_string() << '\n';
	}
}