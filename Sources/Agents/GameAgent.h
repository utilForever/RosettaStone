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

	class User
	{
	public:
		User(int id, Hero *hero, HeroPower *power, Deck& deck);

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
		GameAgent(User *user1, User *user2, int maxBufferSize=2048);
		std::thread* StartAgent(GameResult& result);

		int ReadBuffer(BYTE* arr, int maxSize); // Read data written by Agent
		int WriteBuffer(BYTE* arr, int size); // Write data to Agent

	private:
		User *userCurrent;
		User *userOpponent;

		InteractBuffer inBuffer; // Pipe IO : User -> Agent 
		InteractBuffer outBuffer; // Pipe IO : Agent -> User

		std::random_device rd;
		std::default_random_engine generator; // random generator
		
		int ReadInputBuffer(BYTE* arr, int maxSize); // Read data written by User
		int WriteOutputBuffer(BYTE* arr, int size); // Write data to User

		bool IsGameEnd();
		void Draw(User *user, int num);

		void BeginPhase();
		void MainPhase();
		void FinalPhase(GameResult& result);
		
		void DecideDeckOrder();
		void ShuffleDeck(User *user);
		void Mulligan(User *user);
	};
}

#endif