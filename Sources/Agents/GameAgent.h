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

#include <Models/Card.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Weapon.h>

#include <vector>

namespace Hearthstonepp 
{
	struct System
	{
		Hero hero;
		HeroPower heroPower;
		Weapon weapon;

		std::vector<Card*> deck;
		std::vector<Card*> usedSpell;
		std::vector<Card*> usedMinion;
	};

	class GameAgent
	{
	public:
		void InitSystems();
		void BeginPhase();
		void MainPhase();
		void FinalPhase();

		Card* Draw(System *system);

		void LoadDeck(std::vector<Card*>& deck1, std::vector<Card*>& deck2);
		void DecideDeckOrder();
		void ShuffleDeck(System *system);
		void Mulligan(System *system);

	private:
		System *systemCurrent;
		System *systemOpponent;
	};
}

#endif