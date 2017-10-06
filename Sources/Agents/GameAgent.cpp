/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/GameAgent.h>

namespace Hearthstonepp
{
	System::System(int id, Hero *hero, HeroPower *power, Deck& deck)
	{
		this->id = id;
		this->hero = hero;
		this->power = power;
		this->weapon = nullptr;
		this->deck = deck;
	}

	GameAgent::GameAgent(System *system1, System *system2, int maxBufferSize)
		: inBuffer(maxBufferSize)
		, outBuffer(maxBufferSize)
		, generator(rd())
	{
		this->systemCurrent = system1;
		this->systemOpponent = system2;
	}

	std::thread* GameAgent::StartAgent(GameResult& result)
	{
		std::thread *agent = new std::thread([this](GameResult& result) {
			BeginPhase();

			while (!IsGameEnd())
			{
				MainPhase();
			}
			
			FinalPhase(result);
		}, std::ref(result));

		return agent;
	}

	void GameAgent::BeginPhase()
	{
		DecideDeckOrder();

		ShuffleDeck(systemCurrent);
		ShuffleDeck(systemOpponent);

		Draw(systemCurrent, 4);
		Draw(systemOpponent, 4);

		Mulligan(systemCurrent);
		Mulligan(systemOpponent);

		systemOpponent->hand.push_back(new Card());
	}

	void GameAgent::MainPhase()
	{

	}

	void GameAgent::FinalPhase(GameResult& result)
	{

	}

	void GameAgent::DecideDeckOrder()
	{
		std::uniform_int_distribution<int> bin(0, 1);
		if (bin(generator) == 1)
		{
			std::swap(systemCurrent, systemOpponent);
		}
	}

	void GameAgent::ShuffleDeck(System* system)
	{
		Deck& deck = system->deck;
		std::shuffle(deck.begin(), deck.end(), generator);
	}

	void GameAgent::Mulligan(System* system)
	{
		BYTE index[4] = { 0, };
		std::vector<Card*>& hand = system->hand;

		WriteOutputBuffer((BYTE*)hand.data(), sizeof(Card*) * 4);
		int read = ReadInputBuffer(index, 4);

		std::sort(index, index + read);
		for (int i = 0; i < read; ++i)
		{
			hand.erase(hand.begin() + index[i] - i);
		}

		Draw(system, read);

		WriteOutputBuffer((BYTE*)hand.data(), sizeof(Card*) * 4);
	}

	bool GameAgent::IsGameEnd()
	{
		return true;
		/*
		int healthCurrent = systemCurrent->hero->health;
		int healthOpponent = systemOpponent->hero->health;

		if (healthCurrent <= 0 || healthOpponent <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
	}

	void GameAgent::Draw(System *system, int num)
	{
		Deck& deck = system->deck;
		std::vector<Card*>& hand = system->hand;

		for (int i = 0; i < num; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
	}

	int GameAgent::ReadBuffer(BYTE *arr, int maxSize)
	{
		return outBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteBuffer(BYTE *arr, int size)
	{
		return inBuffer.WriteBuffer(arr, size);
	}

	int GameAgent::ReadInputBuffer(BYTE* arr, int maxSize)
	{
		return inBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteOutputBuffer(BYTE* arr, int size)
	{
		return outBuffer.WriteBuffer(arr, size);
	}
}