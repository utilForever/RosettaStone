/*************************************************************************
> File Name: GameAgent.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_GAME_AGENT_H
#define HEARTHSTONEPP_GAME_AGENT_H

#include <Agents/Utility.h>
#include <Models/Card.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Weapon.h>

#include <algorithm>
#include <vector>

namespace Hearthstonepp 
{
	using Deck = std::vector<Card*>;

	class System
	{
	public:
		System(Hero *hero, HeroPower *power, Deck& deck);

		Hero *hero;
		HeroPower *power;
		Weapon *weapon;

		Deck deck;
		std::vector<Card*> field;
		std::vector<Card*> hand;
		std::vector<Card*> usedSpell;
		std::vector<Card*> usedMinion;
	};

	struct GameResult
	{

	};

	class GameAgent
	{
	public:
		GameAgent(System *system1, System *system2);
		GameResult StartAgent();

		void BeginPhase();
		void MainPhase();
		GameResult FinalPhase();

		int ReadBuffer(BYTE* arr, int maxSize);
		int WriteBuffer(BYTE* arr, int size);

	private:
		InteractBuffer buffer;

		System *systemCurrent;
		System *systemOpponent;
		
		bool IsGameEnd();
		Card* Draw(System *system, int num);
		
		void DecideDeckOrder();
		void ShuffleDeck(System *system);
		void Mulligan(System *system);
	};
}

#endif