/*************************************************************************
> File Name: Deck.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Deck class that stores a list of cards.
> Created Time: 2017/10/09
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_DECK_H
#define HEARTHSTONEPP_DECK_H

#include <Enums/Enums.h>

#include <string>

namespace Hearthstonepp
{
    class Deck
    {
	public:
		//Deck();
		//Deck(std::string name);

		//void AddCard(Card* card, int num);

    private:
    	PlayerClass m_class;
    	std::string m_name;
    	unsigned int m_numOfCards = 0;
    	std::vector<std::pair<Card*, int>> m_cards;
    };
}

#endif