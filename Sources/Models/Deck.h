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
#include <Models/Card.h>

#include <string>

namespace Hearthstonepp
{
    class Deck
    {
	public:
		Deck();
		Deck(const PlayerClass playerClass, std::string name);

		unsigned int GetNumOfCards() const;
		unsigned int GetNumCardInDeck(std::string cardID);

		void AddCard(const Card* card, int numCardToAdd);
		void DeleteCard(const Card* card, const int numCardToDelete);

    private:
    	PlayerClass m_class;
    	std::string m_name;
    	unsigned int m_numOfCards;
    	std::vector<std::pair<const Card*, int>> m_cards;
    };
}

#endif