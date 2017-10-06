/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ simulator.
> Created Time: 2017/08/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Agents/GameAgent.h>
#include <Loaders/CardLoader.h>

#include <iostream>
#include <thread>

using namespace Hearthstonepp;

int main()
{
	Hearthstonepp::CardLoader loader;
	std::vector<Hearthstonepp::Card*> cards;

	loader.Load(cards);

	Deck deck1; // temporal deck
	Deck deck2;

	deck1.reserve(30);
	deck2.reserve(30);

	deck1.assign(cards.begin(), cards.begin() + 30); 
	deck2.assign(cards.begin() + 30, cards.begin() + 60);

	User user1(0, new Hero(), new HeroPower(), deck1); // define new user
	User user2(1, new Hero(), new HeroPower(), deck2);

	GameAgent agent(&user1, &user2);
	GameResult result;

	std::thread *at = agent.StartAgent(result);

	for (int i = 0; i < 2; ++i)
	{
		Card *list[4] = { 0, };
		int result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 4); // get card data

		for (auto card : list)
		{
			std::cout << "[" << card->name << "] ";
		}
		std::cout << std::endl;

		BYTE mulligan[] = { 0, 2, 3 }; // index of the card to be mulligan
		result = agent.WriteBuffer(mulligan, 3); // send index to agent

		result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 4); // get new card data

		for (auto card : list)
		{
			std::cout << "[" << card->name << "] ";
		}
		std::cout << std::endl;
	}

	at->join(); // join agent thread

	return 0;
}