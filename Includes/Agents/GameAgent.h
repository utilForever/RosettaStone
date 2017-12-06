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

#include <Agents/AgentStructures.h>
#include <Interface/InteractBuffer.h>

#include <random>
#include <thread>

namespace Hearthstonepp
{
	class GameAgent
	{
	public:
		GameAgent(User& user1, User& user2, int maxBufferSize = 2048);
		GameAgent(User&& user1, User&& user2, int maxBufferSize = 2048);

		std::thread StartAgent(GameResult& result);

		int GetBufferCapacity() const;
		// read data written by Agent
		int ReadBuffer(BYTE* arr, int maxSize);
		// write data to Agent
		int WriteBuffer(BYTE* arr, int size);

	private:
		User m_userCurrent;
		User m_userOpponent;

		int m_bufferCapacity;
		// Pipe IO : User -> Agent 
		InteractBuffer m_inBuffer; 
		// Pipe IO : Agent -> User
		InteractBuffer m_outBuffer;

		std::random_device m_rd;
		// random generator
		std::default_random_engine m_generator;

		// read data written by User
		int ReadInputBuffer(BYTE* arr, int maxSize);
		// write data to User
		int WriteOutputBuffer(BYTE* arr, int size);

		bool IsGameEnd();
		void Draw(User& user, int num);
		void ModifyMana(User& user, ManaModification mod, int num);

		void BeginPhase();
		void MainPhase();
		void FinalPhase(GameResult& result);

		void DecideDeckOrder();
		void ShuffleDeck(User& user);
		void BeginDraw(User& user);
		void Mulligan(User& user);

		void MainDraw(User& user);
	};
}

#endif