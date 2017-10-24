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
#include <Commons/Constants.h>
#include <Interface/InteractBuffer.h>

#include <algorithm>
#include <random>
#include <thread>
#include <vector>

namespace Hearthstonepp
{
	class GameAgent
	{
	public:
		GameAgent(User& user1, User& user2, int maxBufferSize = 2048);
		GameAgent(User&& user1, User&& user2, int maxBufferSize = 2048);
		std::thread* StartAgent(GameResult& result);

		int GetBufferCapacity() const;
		int ReadBuffer(BYTE* arr, int maxSize); // Read data written by Agent
		int WriteBuffer(BYTE* arr, int size); // Write data to Agent

	private:
		User m_userCurrent;
		User m_userOpponent;

		int m_bufferCapacity;
		InteractBuffer m_inBuffer; // Pipe IO : User -> Agent 
		InteractBuffer m_outBuffer; // Pipe IO : Agent -> User

		std::random_device m_rd;
		std::default_random_engine m_generator; // random generator

		int ReadInputBuffer(BYTE* arr, int maxSize); // Read data written by User
		int WriteOutputBuffer(BYTE* arr, int size); // Write data to User

		bool IsGameEnd();
		void Draw(User& user, int num);

		void BeginPhase();
		void MainPhase();
		void FinalPhase(GameResult& result);

		void DecideDeckOrder();
		void ShuffleDeck(User& user);
		void BeginDraw(User& user);
		void Mulligan(User& user);
	};
}

#endif