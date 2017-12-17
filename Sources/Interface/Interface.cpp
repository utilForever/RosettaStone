/*************************************************************************
> File Name: Interface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Commons/Constants.h>
#include <Enums/EnumsToString.h>
#include <Interface/Interface.h>

#include <iostream>

namespace Hearthstonepp
{
	GameInterface::GameInterface(GameAgent& agent) :
		m_agent(agent), m_bufferCapacity(agent.GetBufferCapacity())
	{
		m_buffer = new BYTE[m_bufferCapacity];
	}

	GameResult GameInterface::StartGame()
	{
		GameResult result;
		std::thread at = m_agent.StartAgent(result);

		while (true)
		{
			const int msg = HandleMessage();
			if (msg == HANDLE_STOP)
			{
				break;
			}
		}

		// join agent thread
		at.join();

		return result;
	}

	const int GameInterface::HandleMessage()
	{
		m_agent.ReadBuffer(m_buffer, m_bufferCapacity);

		if (m_buffer[0] == static_cast<BYTE>(Step::FINAL_GAMEOVER))
		{
			return HANDLE_STOP;
		}
		
		if (m_handler.find(m_buffer[0]) != m_handler.end())
		{
			m_handler[m_buffer[0]](*this);
		}

		return HANDLE_CONTINUE;
	}

	std::ostream& GameInterface::LogWriter(std::string& name)
	{
		std::cout << "[*] " << name << " : ";
		return std::cout;
	}

	void GameInterface::ModifiedMana()
	{
		ModifyManaStructure *data = reinterpret_cast<ModifyManaStructure*>(m_buffer);

		LogWriter(m_users[data->userID]) << "Mana is modified to " << static_cast<int>(data->mana) << std::endl;
	}

	void GameInterface::ShowCards(Card** cards, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			std::string type = ConverterFromCardTypeToString.at(cards[i]->GetCardType());
			std::cout << '[' << cards[i]->GetName() << '(' << type << " / " << cards[i]->GetCost() << ")]\n";
		}
	}

	void GameInterface::BeginFirst()
	{
		BeginFirstStructure* data = reinterpret_cast<BeginFirstStructure*>(m_buffer);

		m_users[0] = data->userFirst;
		m_users[1] = data->userLast;

		LogWriter(m_users[0]) << "Begin First" << std::endl;
		LogWriter(m_users[1]) << "Begin Last" << std::endl;
	}

	void GameInterface::BeginShuffle()
	{
		BeginShuffleStructure* data = reinterpret_cast<BeginShuffleStructure*>(m_buffer);
		LogWriter(m_users[data->userID]) << "Begin Shuffle" << std::endl;
	}

	void GameInterface::BeginDraw()
	{
		DrawStructure* data = reinterpret_cast<DrawStructure*>(m_buffer);

		LogWriter(m_users[data->userID]) << "Begin Draw" << std::endl;
		ShowCards(data->cards, data->numDraw);
	}

	void GameInterface::BeginMulligan()
	{
		BeginMulliganStructure* data = reinterpret_cast<BeginMulliganStructure*>(m_buffer);

		LogWriter(m_users[data->userID]) << "Begin Mulligan" << std::endl;

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

		// send index to agent
		m_agent.WriteBuffer(mulligan, numMulligan);
		// get new card data
		m_agent.ReadBuffer(m_buffer, sizeof(DrawStructure));
		
		LogWriter(m_users[data->userID]) << "Mulligan Result" << std::endl;

		DrawStructure* draw = reinterpret_cast<DrawStructure*>(m_buffer);
		ShowCards(draw->cards, draw->numDraw);
	}

	void GameInterface::MainDraw()
	{
		DrawStructure* data = reinterpret_cast<DrawStructure*>(m_buffer);

		LogWriter(m_users[data->userID]) << "Main Draw" << std::endl;
		ShowCards(data->cards, data->numDraw);
	}

	void GameInterface::MainMenu()
	{

	}

	void GameInterface::MainUseCard()
	{

	}

	void GameInterface::MainCombat()
	{

	}

	void GameInterface::MainEnd()
	{

	}
}
