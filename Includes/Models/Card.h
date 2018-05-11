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
#include <string>
#include <vector>

namespace Hearthstonepp
{
	class Card
	{
	public:
		Card() = default;
		Card(
			std::string id, Rarity rarity, Faction faction, CardSet cardSet,
			CardClass cardClass, CardType cardType, Race race,
			std::string name, std::string text, bool collectible,
			int cost, int attack, int health, int durability,
			std::vector<GameTag> mechanics,
			std::map<PlayReq, int> playRequirements,
			std::vector<std::string> entourages);
		virtual ~Card() = default;

		std::string GetID() const;
		Rarity GetRarity() const;
		CardClass GetCardClass() const;
		CardType GetCardType() const;
		Race GetRace() const;
		std::string GetName() const;
		bool GetCollectible() const;
		int GetCost() const;
		int GetAttack() const;
		int GetHealth() const;
		int GetDurability() const;
		std::vector<GameTag> GetMechanics() const;

		void SetHealth(int health);

		bool HasMechanics(std::vector<GameTag> mechanics) const;

		unsigned int GetMaxAllowedInDeck() const;

		virtual void ShowBriefInfo() const;
		virtual void ShowInfo() const;

	private:
		std::string m_id;
		Rarity m_rarity;
		Faction m_faction;
		CardSet m_cardSet;
		CardClass m_cardClass = CardClass::INVALID;
		CardType m_cardType = CardType::INVALID;
		Race m_race = Race::INVALID;

		std::string m_name;
		std::string m_text;

		bool m_collectible;
		int m_cost;
		int m_attack;
		int m_health;
		int m_durability;

		std::vector<GameTag> m_mechanics;
		std::map<PlayReq, int> m_playRequirements;
		std::vector<std::string> m_entourages;

		unsigned int m_maxAllowedInDeck;
	};
}

#endif
