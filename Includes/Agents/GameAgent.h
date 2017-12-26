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

#include <array>
#include <functional>
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
		const unsigned int GAME_END = 0;
		const unsigned int GAME_CONTINUE = 1;

		User m_userCurrent;
		User m_userOpponent;

		int m_bufferCapacity;
		// Temporal Buffer
		BYTE* m_buffer;
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
		void ModifyMana(User& user, NumericModification mod, ManaType type, int num);

		void BeginPhase();
		const int MainPhase();
		void FinalPhase(GameResult& result);

		void BeginFirst();
		void BeginShuffle(User& user);
		void BeginDraw(User& user);
		void BeginMulligan(User& user);

		void MainDraw(User& user);
		const int MainMenu(User& user, User& enemy);
		void MainUseCard(User& user);
		void MainCombat(User& user);
		void MainEnd(User& user);

		std::array<std::function<void(GameAgent&, User&)>, GAME_MAIN_MENU_SIZE - 1> m_mainMenuFuncs =
		{
			&GameAgent::MainUseCard,
			&GameAgent::MainCombat,
		};
	};
}

#endif