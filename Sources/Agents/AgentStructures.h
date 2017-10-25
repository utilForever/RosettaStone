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

	struct User
	{
		User(Player* player, int deckID);

		int id;
		Player* player;
		Hero* hero;
		HeroPower* power;
		Weapon* weapon;

		std::vector<Card*> deck;
		std::vector<Card*> field;
		std::vector<Card*> hand;
		std::vector<Card*> usedSpell;
		std::vector<Card*> usedMinion;
	};

	struct GameResult
	{

	};

	struct DrawStructure
	{
		DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, BYTE numHands, Card** cards);

		BYTE id;
		BYTE userID;
		BYTE numDraw;
		BYTE numHands;
		Card** cards;
	};

	struct BeginFirstStructure
	{
		BeginFirstStructure(std::string userFirst, std::string userLast);

		BYTE id = static_cast<BYTE>(Step::BEGIN_FIRST);
		std::string userFirst;
		std::string userLast;
	};

	struct BeginShuffleStructure
	{
		BeginShuffleStructure(int userID);

		BYTE id = static_cast<BYTE>(Step::BEGIN_SHUFFLE);
		int userID;
	};

	struct BeginMulliganStructure
	{
		BeginMulliganStructure(int userID);

		BYTE id = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		int userID;
	};
}

#endif