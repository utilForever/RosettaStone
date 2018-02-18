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

		BYTE id;
		BYTE totalMana;
		BYTE existMana;
		BYTE exhausted;

		std::string userID;
		Hero* hero;
		HeroPower* power;
		Weapon* weapon;

		// Card storage, not for processing
		std::vector<Card> cardDeck;

		// Card objects for procesisng, based on pointer
		std::vector<Card*> deck;
		std::vector<Card*> field;
		std::vector<Card*> hand;
		std::vector<Card*> usedSpell;
		std::vector<Card*> usedMinion;

		// Card objects for already attacked minion
		std::vector<Card*> attacked;
	};

	struct GameResult
	{
		std::string winnerUserID;
	};

	// Briefing games, mana, hands, fields, and hero info
	struct GameBrief
	{
		GameBrief(
			BYTE currentUser, BYTE oppositeUser, BYTE currentMana, BYTE oppositeMana, 
			BYTE numCurrentHand, BYTE numOppositeHand, BYTE numCurrentField, BYTE numOppositeField,
			Card* currentHero, Card* oppositeHero,
			Card** currentField, Card** currentHand, Card** oppositeField);
	
		BYTE id = static_cast<BYTE>(Action::BRIEF);

		// current user id
		BYTE currentUser;
		// opposite user id
		BYTE oppositeUser;
		BYTE currentMana;
		BYTE oppositeMana;

		BYTE numCurrentHand;
		BYTE numOppositeHand;
		BYTE numCurrentField;
		BYTE numOppositeField;

		Card* currentHero;
		Card* oppositeHero;

		Card** currentField;
		Card** currentHand;
		Card** oppositeField;
	};

	// Structure for targeting, eg. combat, spell, etc.
	struct TargetingStructure
	{
		TargetingStructure(BYTE src, BYTE dst);

		BYTE src;
		BYTE dst;
	};

	struct DrawStructure
	{
		DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, Card** cards);

		BYTE id;
		BYTE userID;
		BYTE numDraw;
		// drawn cards
		Card** cards;
	};

	// When number of hands over 10
	struct OverDrawStructure
	{
		OverDrawStructure(BYTE userID, BYTE numOver, Card** cards);

		BYTE id = static_cast<BYTE>(Action::OVER_DRAW);
		BYTE userID;
		BYTE numOver;
		// over drawn cards, burnt
		Card** cards;
	};

	// When deck size equals to zero
	struct ExhaustDeckStructure
	{
		ExhaustDeckStructure(BYTE userID, BYTE numOver);

		BYTE id = static_cast<BYTE>(Action::EXHAUST_DECK);
		BYTE userID;
		// 
		BYTE numOver;
	};

	// Modify mana value of user
	struct ModifyManaStructure
	{
		ModifyManaStructure(BYTE userID, BYTE mana);

		BYTE id = static_cast<BYTE>(Action::MANA_MODIFICATION);
		BYTE userID;
		BYTE mana;
	};

	// Modify health value of card
	struct ModifyHealthStructure
	{
		ModifyHealthStructure(BYTE userID, Card* card);

		BYTE id = static_cast<BYTE>(Action::HEALTH_MODIFICATION);
		BYTE userID;
		Card* card;
	};

	// When health value of minion under zero
	struct ExhaustMinionStructure
	{
		ExhaustMinionStructure(BYTE userID, Card* card);

		BYTE id = static_cast<BYTE>(Action::EXHAUST_MINION);
		BYTE userID;
		Card* card;
	};

	struct BeginFirstStructure
	{
		BeginFirstStructure(std::string& firstUserID, std::string& lastuserID);

		BYTE id = static_cast<BYTE>(Step::BEGIN_FIRST);
		std::string& firstUserID;
		std::string& lastUserID;
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

	// Ready for main phase, draw, add mana, clear attacked vector
	struct MainReadyStructure
	{
		MainReadyStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_READY);
		BYTE userID;
	};

	// Select main menu and call action methods
	struct MainMenuStructure
	{
		MainMenuStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_START);
		BYTE userID;
	};

	// Use cards, eg. summon minion, use spell, etc.
	struct MainUseCardStructure
	{
		MainUseCardStructure(BYTE userID, BYTE existMana, BYTE numFields, BYTE numHands, Card** hands);

		BYTE id = static_cast<BYTE>(Step::MAIN_ACTION);
		BYTE userID;
		BYTE existMana;
		BYTE numFields;
		BYTE numHands;
		Card** hands;
	};

	// Response of MainUseCardStructure, summon minion
	struct MainUseMinionStructure
	{
		MainUseMinionStructure(BYTE cardIndex, BYTE position);

		BYTE id = static_cast<BYTE>(CardType::MINION);
		BYTE cardIndex;
		BYTE position;
	};

	// Combat with other minion or hero
	struct MainCombatStructure
	{
		MainCombatStructure(
			BYTE userID, BYTE numCurrentField, BYTE numOppositeField, BYTE numAttacked,
			Card** currentField, Card** oppositeField, Card** attacked);

		BYTE id = static_cast<BYTE>(Step::MAIN_COMBAT);
		BYTE userID;
		BYTE numCurrentField;
		BYTE numOppositeField;
		BYTE numAttacked;

		Card** currentField;
		Card** oppositeField;
		Card** attacked;
	};

	struct MainEndStructure
	{
		MainEndStructure(BYTE userID);

		BYTE id = static_cast<BYTE>(Step::MAIN_END);
		BYTE userID;
	};

	struct FinalGameOverStructure
	{
		FinalGameOverStructure(BYTE winnerUserID);

		BYTE id = static_cast<BYTE>(Step::FINAL_GAMEOVER);
		BYTE winnerUserID;
	};
}

#endif