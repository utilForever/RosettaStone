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

#include <iostream>

namespace Hearthstonepp
{
	class GameInterface
	{
	public:
		GameInterface(GameAgent& agent);
		GameResult StartGame();

	private:
		GameAgent& m_agent;

		void Mulligan();
	};
}

#endif