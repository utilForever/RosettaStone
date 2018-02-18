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
		size_t ReadBuffer(BYTE* arr, size_t maxSize);
		// write data to Agent
		size_t WriteBuffer(BYTE* arr, size_t size);

	private:
		const unsigned int GAME_END = 0;
		const unsigned int GAME_CONTINUE = 1;

		const unsigned int MANA_EXIST = 0;
		const unsigned int MANA_TOTAL = 1;

		const unsigned int DRAW_SUCCESS = 0;
		// over draw or deck exhausted
		const unsigned int DRAW_FAIL = 1;

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
		size_t ReadInputBuffer(BYTE* arr, size_t maxSize);
		// write data to User
		size_t WriteOutputBuffer(BYTE* arr, size_t size);

		// Get opponent user of parameter
		User& GetOpponentOf(User& user);

		bool IsGameEnd();
		unsigned int Draw(User& user, int num);
		void ModifyMana(User& user, NumericModification mod, unsigned int type, BYTE num);

		void BeginPhase();
		// Return game status, GAME_END or GAME_CONTINUE
		unsigned int MainPhase();
		void FinalPhase(GameResult& result);

		void BeginFirst();
		void BeginShuffle(User& user);
		void BeginDraw(User& user);
		void BeginMulligan(User& user);

		// Ready for main phase, draw, mana, clear attacekd vector
		void MainReady(User& user);
		void MainDraw(User& user);
		// Select main menu and call action method, return game status
		unsigned int MainMenu(User& user, User& enemy);
		// Use card, summon minion, use spell etc.
		void MainUseCard(User& user);
		// Combat with other minion or hero.
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