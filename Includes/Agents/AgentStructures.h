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

#include <Models/Card.h>
#include <Models/Cards.h>
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
		int mana;
		int exhausted;

		std::string userID;
		Hero* hero;
		HeroPower* power;
		Weapon* weapon;

		std::vector<Card> cardDeck;

		std::vector<Card*> deck;
		std::vector<Card*> field;
		std::vector<Card*> hand;
		std::vector<Card*> usedSpell;
		std::vector<Card*> usedMinion;
	};

	struct GameResult
	{

	};

	struct GameBrief
	{
		GameBrief(
			BYTE currentUser, BYTE oppositeUser, BYTE currentMana, BYTE oppositeMana, 
			BYTE numCurrentHand, BYTE numOppositeHand, BYTE numCurrentField, BYTE numOppositeField,
			Card** currentField, Card** currentHand, Card** oppositeField);
	
		BYTE currentUser;
		BYTE oppositeUser;
		BYTE currentMana;
		BYTE oppositeMana;

		BYTE numCurrentHand;
		BYTE numOppositeHand;
		BYTE numCurrentField;
		BYTE numOppositeField;

		Card** currentField;
		Card** currentHand;
		Card** oppositeField;
	};

	struct DrawStructure
	{
		DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, Card** cards);

		BYTE id;
		BYTE userID;
		BYTE numDraw;
		Card** cards;
	};

	struct OverDrawStructure
	{
		OverDrawStructure(BYTE userID, BYTE numOver, Card** cards);

		BYTE id = static_cast<BYTE>(Action::OVER_DRAW);
		BYTE userID;
		BYTE numOver;
		Card** cards;
	};

	struct ExhaustDeckStructure
	{
		ExhaustDeckStructure(BYTE userID, BYTE numOver);

		BYTE id = static_cast<BYTE>(Action::EXHAUST_DECK);
		BYTE userID;
		BYTE numOver;
	};

	struct ModifyManaStructure
	{
		ModifyManaStructure(BYTE userID, BYTE mana);

		BYTE id = static_cast<BYTE>(Action::MANA_MODIFICATION);
		BYTE userID;
		BYTE mana;
	};

	struct BeginFirstStructure
	{
		BeginFirstStructure(std::string& userFirst, std::string& userLast);

		BYTE id = static_cast<BYTE>(Step::BEGIN_FIRST);
		std::string& userFirst;
		std::string& userLast;
	};

	struct BeginShuffleStructure
	{
		BeginShuffleStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::BEGIN_SHUFFLE);
		BYTE userID;
	};

	struct BeginMulliganStructure
	{
		BeginMulliganStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		BYTE userID;
	};

	struct MainMenuStructure
	{
		MainMenuStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_START);
		BYTE userID;
	};

	struct MainUseCardStructure
	{
		MainUseCardStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_ACTION);
		BYTE userID;
	};

	struct MainUseMinionStructure
	{
		MainUseMinionStructure(BYTE cardIndex, BYTE position);

		BYTE id = static_cast<BYTE>(CardType::MINION);
		BYTE cardIndex;
		BYTE position;
	};

	struct MainCombatStructure
	{
		MainCombatStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_COMBAT);
		BYTE userID;
	};

	struct MainEndStructure
	{
		MainEndStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_END);
		BYTE userID;
	};
}

#endif