/*************************************************************************
> File Name: Hearo.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hero class that stores hero information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_HERO_H
#define HEARTHSTONEPP_HERO_H

#include <Enchants/Enchantment.h>
#include <Enums/Enums.h>
#include <Models/Card.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp 
{
	class Hero
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

		int GetHealth() const
		{
			return m_health;
		}

		void SetHealth(int health)
		{
			m_health = health;
		}

		int GetArmor() const
		{
			return m_armor;
		}

		void SetArmor(int armor)
		{
			m_armor = armor;
		}

		int GetAttack() const
		{
			return m_attack;
		}

		int SetAttack(int attack)
		{
			m_attack = attack;
		}

		bool GetIsEquippedWithWeapon() const
		{
			return m_isEquippedWithWeapon;
		}

		void SetIsEquippedWithWeapon(bool isEquippedWithWeapon)
		{
			m_isEquippedWithWeapon = isEquippedWithWeapon;
		}

		const Card& GetRefWepon() const
		{
			return m_refWeapon;
		}

		void SetRefWeapon(Card refWeapon)
		{
			m_refWeapon = refWeapon;
		}

		const HeroPower& GetHeroPower() const
		{
			return m_heroPower;
		}

		void GetHeroPower(HeroPower heroPower)
		{
			m_heroPower = heroPower;
		}

		const std::vector<Enchantment>& GetEnchantments() const
		{
			return m_enchantments;
		}

		void SetEnchantments(std::vector<Enchantment> enchantments)
		{
			m_enchantments = enchantments;
		}

		bool GetImplemented() const
		{
			return m_implemented;
		}

		void SetImplemented(bool implemented)
		{
			m_implemented = implemented;
		}

	private:
		int m_assetID;
		std::string m_id;
		std::string m_name;
		Race m_race;
		Faction m_faction; 
		std::map<GameTag, int> m_tags;
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements;
		int m_health;
		int m_armor;
		int m_attack;
		bool m_isEquippedWithWeapon;
		Card m_refWeapon;
		HeroPower m_heroPower;
		std::vector<Enchantment> m_enchantments; 
		bool m_implemented; 
	};

	class HeroPower
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

		bool GetImplemented() const
		{
			return m_implemented;
		}

		void SetImplemented(bool implemented)
		{
			m_implemented = implemented;
		}

	private:
		int m_assetID;
		std::string m_id;
		std::string m_name;
		std::string m_text;
		std::map<GameTag, int> m_tags;
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements; 
		bool m_hasCombo;
		bool m_hasOverload; 
		int m_overload;
		bool m_requiresTarget;
		bool m_requiresTargetForCombo;
		bool m_requiresTargetIfAvailable;
		bool m_requiresTargetIfAvailableAndDragonInHand; 
		bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn; 
		bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions;
		bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets;
		bool m_implemented;
		bool m_isAffectedBySpellDamage; 
	};
}

#endif