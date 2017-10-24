/*************************************************************************
> File Name: AgentStructure.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_AGENT_STRUCTURES_H
#define HEARTHSTONEPP_AGENT_STRUCTURES_H

#include <Enums/EnumsToString.h>
#include <Models/Card.h>
#include <Models/Cards.h>
#include <Models/Deck.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Weapon.h>
#include <Models/Player.h>

namespace Hearthstonepp
{
	using BYTE = unsigned char;

	class User
	{
	public:
		User(Player *player, int deckID);

		int m_id;
		Player *m_player;
		Hero *m_hero;
		HeroPower *m_power;
		Weapon *m_weapon;

		std::vector<Card*> m_deck;
		std::vector<Card*> m_field;
		std::vector<Card*> m_hand;
		std::vector<Card*> m_usedSpell;
		std::vector<Card*> m_usedMinion;
	};

	struct GameResult
	{

	};

	struct DrawStructure
	{
		DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, BYTE numHands, Card** cards);

		BYTE m_id;
		BYTE m_userID;
		BYTE m_numDraw;
		BYTE m_numHands;
		Card** m_cards;
	};

	struct BeginFirstStructure
	{
		BeginFirstStructure(std::string* userFirst, std::string* userLast);

		BYTE m_id = static_cast<BYTE>(Step::BEGIN_FIRST);
		std::string* m_userFirst;
		std::string* m_userLast;
	};

	struct BeginShuffleStructure
	{
		BeginShuffleStructure(int userID);

		BYTE m_id = static_cast<BYTE>(Step::BEGIN_SHUFFLE);
		int m_userID;
	};

	struct BeginMulliganStructure
	{
		BeginMulliganStructure(int userID);

		BYTE m_id = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		int m_userID;
	};
}

#endif