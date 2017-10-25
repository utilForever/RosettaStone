/*************************************************************************
> File Name: Card.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/30
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Enums/EnumsToString.h>
#include <Models/Card.h>

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
		m_maxAllowedInDeck = (rarity == Rarity::LEGENDARY) ? 1 : 2;
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

	std::string Card::GetName() const
	{
		return m_name;
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

	unsigned int Card::GetMaxAllowedInDeck() const
	{
		return m_maxAllowedInDeck;
	}

	void Card::ShowInfo() const
	{
		std::cout << "========================================\n";
		std::cout << "               Card Info!               \n";
		std::cout << "========================================\n";
		std::cout << "ID: " << m_id.c_str() << '\n';
		std::cout << "Name: " << m_name.c_str() << '\n';
		std::cout << "Text: " << m_text.c_str() << '\n';
		std::cout << "Rarity: " << ConverterFromRarityToString.at(m_rarity).c_str() << '\n';
		std::cout << "Faction: " << ConverterFromFactionToString.at(m_faction).c_str() << '\n';
		std::cout << "CardSet: " << ConverterFromCardSetToString.at(m_cardSet).c_str() << '\n';
		std::cout << "CardClass: " << ConverterFromCardClassToString.at(m_cardClass).c_str() << '\n';
		std::cout << "CardType: " << ConverterFromCardTypeToString.at(m_cardType).c_str() << '\n';
		std::cout << "Race: " << ConverterFromRaceToString.at(m_race).c_str() << '\n';
	}
}