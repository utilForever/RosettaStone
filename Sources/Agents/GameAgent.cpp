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
	System::System(Hero *hero, HeroPower *power, Deck& deck)
	{
		this->hero = hero;
		this->power = power;
		this->weapon = nullptr;
		this->deck = deck;
	}

	GameAgent::GameAgent(System *system1, System *system2)
	{
		this->systemCurrent = system1;
		this->systemOpponent = system2;
	}

	GameResult GameAgent::StartAgent()
	{
		BeginPhase();

		while (IsGameEnd())
		{
			MainPhase();
		}

		return FinalPhase();
	}

	void GameAgent::BeginPhase()
	{
		DecideDeckOrder();

		ShuffleDeck(systemCurrent);
		ShuffleDeck(systemOpponent);

		Mulligan(systemCurrent);
		Mulligan(systemOpponent);
	}

	void GameAgent::MainPhase()
	{

	}

	GameResult GameAgent::FinalPhase()
	{
		return GameResult();
	}

	void GameAgent::DecideDeckOrder()
	{
		RandomInt bin(2);
		if (bin.get() == 1)
		{
			std::swap(systemCurrent, systemOpponent);
		}
	}

	void GameAgent::ShuffleDeck(System* system)
	{
		Deck& deck = system->deck;
		std::random_shuffle(deck.begin(), deck.end());
	}

	void GameAgent::Mulligan(System* system)
	{

	}

	bool GameAgent::IsGameEnd()
	{
		int healthCurrent = systemCurrent->hero->health;
		int healthOpponent = systemOpponent->hero->health;

		if (healthCurrent == 0 || healthOpponent == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Card* GameAgent::Draw(System *system, int num)
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
		return buffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteBuffer(BYTE *arr, int size)
	{
		return buffer.WriteBuffer(arr, size);
	}
}