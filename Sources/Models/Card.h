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

#include <Enchants/Enchantment.h>
#include <Enums/Enums.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp
{
	class Card
	{
	public:
		int GetAssetID() const
		{
			return m_assetID;
		}

		void SetAssetID(int assetID)
		{
			m_assetID = assetID;
		}

		std::string GetID() const
		{
			return m_id;
		}

		void SetID(std::string id)
		{
			m_id = id;
		}

		std::string GetName() const
		{
			return m_name;
		}

		void SetName(std::string name)
		{
			m_name = name;
		}

		std::string GetText() const
		{
			return m_text;
		}

		void SetText(std::string text)
		{
			m_text = text;
		}

		const std::vector<std::string>& GetEntourage() const
		{
			return m_entourage;
		}

		void SetEntourage(std::vector<std::string> entourage)
		{
			m_entourage = entourage;
		}

		const std::map<GameTag, int>& GetTags() const
		{
			return m_tags;
		}

		void SetTags(std::map<GameTag, int> tags)
		{
			m_tags = tags;
		}

		const std::map<GameTag, int>& GetRefTags() const
		{
			return m_refTags;
		}

		void SetRefTags(std::map<GameTag, int> refTags)
		{
			m_refTags = refTags;
		}

		const std::map<PlayReq, int>& GetPlayRequirements() const
		{
			return m_playRequirements;
		}

		void SetPlayRequirements(std::map<PlayReq, int> playRequirements)
		{
			m_playRequirements = playRequirements;
		}

	private:
		int m_assetID;
		std::string m_id;
		std::string m_name;
		std::string m_text;
		std::vector<std::string> m_entourage;
		std::map<GameTag, int> m_tags;
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements;
		bool m_isCollectible;
		Race m_race;
		Faction m_faction;
		bool m_hasCombo;
		bool m_rarity;
		CardType m_type;
		CardSet m_set;
		int m_cost;
		bool m_hasOverload;
		int m_overload;
		bool m_requiresTarget;
		bool m_requiresTargetForCombo;
		bool m_requiresTargetIfAvailable;
		bool m_requiresTargetIfAvailableAndDragonInHand;
		bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn;
		bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions;
		bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets;
		int m_maxAllowedInDeck;
		bool m_isImplemented;
		std::vector<Enchantment> m_enchantments;
		bool m_isAffectedBySpellDamage;
		int m_multiClassGroup;
	};
}

#endif