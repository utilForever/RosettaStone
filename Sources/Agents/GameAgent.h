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

#include <Agents/Interface.h>
#include <Models/Card.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Weapon.h>

#include <algorithm>
#include <random>
#include <thread>
#include <vector>

namespace Hearthstonepp 
{
	using Deck = std::vector<Card*>;
	using BYTE = unsigned char;

	class System
	{
	public:
		System(int id, Hero *hero, HeroPower *power, Deck& deck);

		int id;
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
		GameAgent(System *system1, System *system2, int maxBufferSize=2048);
		std::thread* StartAgent(GameResult& result);

		int ReadBuffer(BYTE* arr, int maxSize);
		int WriteBuffer(BYTE* arr, int size);

	private:
		System *systemCurrent;
		System *systemOpponent;

		InteractBuffer inBuffer;
		InteractBuffer outBuffer;

		std::random_device rd;
		std::default_random_engine generator;
		
		int ReadInputBuffer(BYTE* arr, int maxSize);
		int WriteOutputBuffer(BYTE* arr, int size);

		bool IsGameEnd();
		void Draw(System *system, int num);

		void BeginPhase();
		void MainPhase();
		void FinalPhase(GameResult& result);
		
		void DecideDeckOrder();
		void ShuffleDeck(System *system);
		void Mulligan(System *system);
	};
}

#endif