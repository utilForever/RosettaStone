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
	private:
		int m_assetID;
		int m_id;
		std::string m_name;
		std::string m_text;
		std::vector<std::string> m_entourage; // 주변 하수인
		std::map<GameTag, int> m_tags; // 게임정보
		std::map<GameTag, int> m_refTags;
		std::map<PlayReq, int> m_playRequirements; // 플레이 요구 사항
		bool m_isCollectible; // 회수 가능 여부
		Race m_race; //종족
		Faction m_faction; // 호드 or 얼라
		bool m_hasCombo; // 연계
		bool m_rarity; // 희귀도
		CardType m_type; // 카드 종류
		CardSet m_set; // 
		int m_cost; // 코스트
		bool m_hasOverload; // 과부화
		int m_overload; // 과부화 코스트
		bool m_requiresTarget;
		bool m_requiresTargetForCombo;
		bool m_requiresTargetIfAvailable;
		bool m_requiresTargetIfAvailableAndDragonInHand; // 핸드에 용족이 있을 떄
		bool m_requiresTargetIfAvailableAndElementalPlayedLastTurn;
		bool m_requiresTargetIfAvailableAndMinimumFriendlyMinions;
		bool m_requiresTargetIfAvailableAndMinimumFriendlySecrets;
		int m_maxAllowedInDeck; // 덱에 최대로 넣을 수 있는 카드 수
		bool m_isImplemented; // 구현되어있는 클래스인지
		std::vector<Enchantment> m_enchantments; // 카드에 부여된 효과 목록
		bool m_isAffectedBySpellDamage; // 주문 카드로 피해를 입었는지
		int m_multiClassGroup;
	};
}

#endif