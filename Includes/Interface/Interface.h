/*************************************************************************
> File Name: Interface.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_INTERFACE_H
#define HEARTHSTONEPP_INTERFACE_H

#include <Agents/GameAgent.h>

#include <array>
#include <functional>
#include <map>

namespace Hearthstonepp
{
	class GameInterface
	{
	public:
		GameInterface(GameAgent& agent);

		GameResult StartGame();

	private:
		const unsigned int HANDLE_CONTINUE = 0;
		const unsigned int HANDLE_STOP = 1;

		const int HandleMessage();
		std::ostream& LogWriter(std::string& name);

		template <std::size_t SIZE>
		void ShowMenus(std::array<std::string, SIZE> menus);
		void ShowCards(Card** cards, int size);

		void BriefGame();

		void OverDraw();
		void ExhaustDeck();
		void ModifiedMana();

		void BeginFirst();
		void BeginShuffle();
		void BeginDraw();
		void BeginMulligan();

		void MainDraw();
		void MainMenu();
		void MainUseCard();
		void MainCombat();
		void MainEnd();

		GameAgent& m_agent;
		std::string m_users[2];

		BYTE* m_buffer;
		int m_bufferCapacity;

		std::map<BYTE, std::function<void(GameInterface&)>> m_handler =
		{
			{ static_cast<BYTE>(Step::BEGIN_FIRST),			&GameInterface::BeginFirst },
			{ static_cast<BYTE>(Step::BEGIN_SHUFFLE),		&GameInterface::BeginShuffle },
			{ static_cast<BYTE>(Step::BEGIN_DRAW),			&GameInterface::BeginDraw },
			{ static_cast<BYTE>(Step::BEGIN_MULLIGAN),		&GameInterface::BeginMulligan },
			{ static_cast<BYTE>(Step::MAIN_DRAW),			&GameInterface::MainDraw },
			{ static_cast<BYTE>(Step::MAIN_START),			&GameInterface::MainMenu },
			{ static_cast<BYTE>(Step::MAIN_ACTION),			&GameInterface::MainUseCard },
			{ static_cast<BYTE>(Step::MAIN_COMBAT),			&GameInterface::MainCombat },
			{ static_cast<BYTE>(Step::MAIN_END),			&GameInterface::MainEnd },
			{ static_cast<BYTE>(Action::BRIEF),				&GameInterface::BriefGame },
			{ static_cast<BYTE>(Action::OVER_DRAW),			&GameInterface::OverDraw },
			{ static_cast<BYTE>(Action::EXHAUST_DECK),		&GameInterface::ExhaustDeck },
			{ static_cast<BYTE>(Action::MANA_MODIFICATION), &GameInterface::ModifiedMana },
		};

		std::array<std::string, GAME_MAIN_MENU_SIZE> m_mainMenuStr =
		{
			"1. Use Card",
			"2. Combat",
			"3. Stop"
		};
	};
}

#endif