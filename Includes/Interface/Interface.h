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

#include <functional>
#include <map>

namespace Hearthstonepp
{
	class GameInterface
	{
	public:
		const unsigned int HANDLE_CONTINUE = 0;
		const unsigned int HANDLE_STOP = 1;

		GameInterface(GameAgent& agent);

		GameResult StartGame();

	private:
		int HandleMessage();
		void LogWriter(std::string& name, std::string meesage);

		void BeginFirst();
		void BeginShuffle();
		void BeginDraw();
		void BeginMulligan();

		GameAgent& m_agent;
		std::string m_users[2];

		BYTE* m_buffer;
		int m_bufferCapacity;

		std::map<BYTE, std::function<void(GameInterface&)>> m_handler =
		{
			{ static_cast<BYTE>(Step::BEGIN_FIRST),		&GameInterface::BeginFirst },
			{ static_cast<BYTE>(Step::BEGIN_SHUFFLE),	&GameInterface::BeginShuffle },
			{ static_cast<BYTE>(Step::BEGIN_DRAW),		&GameInterface::BeginDraw },
			{ static_cast<BYTE>(Step::BEGIN_MULLIGAN),	&GameInterface::BeginMulligan }
		};
	};
}

#endif