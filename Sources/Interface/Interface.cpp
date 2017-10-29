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
		, m_bufferCapacity(agent.GetBufferCapacity())
	{
		m_buffer = new BYTE[m_bufferCapacity];
	}

	GameResult GameInterface::StartGame()
	{
		GameResult result;
		std::thread* at = m_agent.StartAgent(result);

		while (true)
		{
			int result = HandleMessage();
			if (result == HANDLE_STOP) break;
		}

		at->join(); // join agent thread
		delete at;

		return result;
	}

	int GameInterface::HandleMessage()
	{
		m_agent.ReadBuffer(m_buffer, m_bufferCapacity);
		if (m_buffer[0] == static_cast<BYTE>(Step::FINAL_GAMEOVER))
		{
			return HANDLE_STOP;
		}
		else if (m_handler.find(m_buffer[0]) != m_handler.end())
		{
			m_handler[m_buffer[0]](*this);
		}

		return HANDLE_CONTINUE;
	}

	void GameInterface::LogWriter(std::string& name, std::string message)
	{
		std::cout << "[*] " << name << " : " << message << std::endl;
	}

	void GameInterface::BeginFirst()
	{
		BeginFirstStructure* data = (BeginFirstStructure*)m_buffer;

		m_users[0] = data->userFirst;
		m_users[1] = data->userLast;

		LogWriter(m_users[0], "Begin First");
		LogWriter(m_users[1], "Begin Last");
	}

	void GameInterface::BeginShuffle()
	{
		BeginShuffleStructure* data = (BeginShuffleStructure*)m_buffer;
		LogWriter(m_users[data->userID], "Begin Shuffle");
	}

	void GameInterface::BeginDraw()
	{
		DrawStructure* data = (DrawStructure*)m_buffer;
		LogWriter(m_users[data->userID], "Begin Draw");

		for (int i = 0; i < NUM_BEGIN_DRAW; ++i)
		{
			std::cout << "[" << data->cards[i]->GetName() << "] ";
		}
		std::cout << std::endl;
	}

	void GameInterface::BeginMulligan()
	{
		BeginMulliganStructure* data = (BeginMulliganStructure*)m_buffer;
		LogWriter(m_users[data->userID], "Begin Mulligan");

		int numMulligan;
		while (true)
		{
			std::cout << "[*] How many cards to mulligan ? (0 ~ 3) ";
			std::cin >> numMulligan;

			if (numMulligan >= 0 && numMulligan <= NUM_BEGIN_DRAW)
			{
				break;
			}
		}

		BYTE mulligan[NUM_BEGIN_DRAW] = { 0, };
		for (int i = 0; i < numMulligan; ++i)
		{
			while (true)
			{
				int index = 0;
				std::cout << "[*] Input card index " << i+1 << " (0 ~ 2) : ";
				std::cin >> index;

				if (index >= 0 && index <= NUM_BEGIN_DRAW - 1)
				{
					mulligan[i] = index;
					break;
				}
			}
		}

		m_agent.WriteBuffer(mulligan, numMulligan); // send index to agent
		m_agent.ReadBuffer(m_buffer, sizeof(DrawStructure)); // get new card data
		
		LogWriter(m_users[data->userID], "Mulligan Result");

		DrawStructure* draw = (DrawStructure*)m_buffer;
		for (int i = 0; i < NUM_BEGIN_DRAW; ++i)
		{
			std::cout << "[" << draw->cards[i]->GetName() << "] ";
		}
		std::cout << std::endl;
	}
}