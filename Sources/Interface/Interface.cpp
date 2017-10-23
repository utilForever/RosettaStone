/*************************************************************************
> File Name: Interface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Interface/Interface.h>

namespace Hearthstonepp
{
	GameInterface::GameInterface(GameAgent& agent)
		: m_agent(agent)
	{
		// Do Nothing
	}

	GameResult GameInterface::StartGame()
	{
		GameResult result;
		std::thread *at = m_agent.StartAgent(result);

		for (int i = 0; i < 2; ++i)
		{
			Mulligan();
		}

		at->join(); // join agent thread

		return result;
	}

	void GameInterface::Mulligan()
	{
		Card *list[3] = { 0, };
		int result = m_agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get card data

		for (auto card : list)
		{
			std::cout << "[" << card->GetCardName() << "] ";
		}
		std::cout << std::endl;

		BYTE mulligan[] = { 0, 2 }; // index of the card to be mulligan
		result = m_agent.WriteBuffer(mulligan, 2); // send index to agent

		result = m_agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get new card data

		for (auto card : list)
		{
			std::cout << "[" << card->GetCardName() << "] ";
		}
		std::cout << std::endl;
	}
}