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
	private:
		int m_assetID;
		int m_id;
		std::string m_name;
		Race m_race; //종족
		Faction m_faction; // 호드 or 얼라
		std::map<GameTag, int> m_tags; // 게임정보
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements; // 플레이 요구 사항
		int m_health;
		int m_armor;
		int m_attack;
		bool m_isEquippedWithWeopon; // 무기 장착 여부
		Card m_refWepon; // 무기 레퍼런스
		HeroPower m_heroPower; // 영웅 능력
		std::vector<Enchantment> m_enchantments; // 카드에 부여된 효과 목록
		bool m_isImplemented; // 구현되어있는 클래스인지

		// std::vector<std::string> m_entourage; // 주변 하수인
		// bool m_isCollectible; // 회수 가능 여부
		// bool m_hasCombo; // 연계
		// bool m_rarity; // 희귀도
		// CardType m_type; // 카드 종류
		// CardSet m_set; // 
		// int m_cost; // 코스트
		// bool m_hasOverload; // 과부화
		// int m_overload; // 과부화 코스트
		// bool m_requiresTarget;
		// bool m_requiresTargetForCombo; 
		// bool m_requiresTargetIfAvailable;
		// bool m_requiresTargetIfAvailableAndDragonInHand; // 핸드에 용족이 있을 떄
		// bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn; // 이전 턴에 정령을 냈을 때
		// bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions; // 필드 개체가 n 마리 이상일 때
		// bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets; // 비밀이 걸려 있는가
		// bool m_isAffectedBySpellDamage; // 주문 카드로 피해를 입었는지
		// int m_maxAllowedInDeck; // 덱에 최대로 넣을 수 있는 카드 수
		// int m_multiClassGroup;
	};

	class HeroPower
	{
	private:

	};
}

#endif