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
		Deck(const CardClass playerClass, std::string name);

		std::string GetName() const;
		unsigned int GetNumOfCards() const;
		unsigned int GetNumCardInDeck(std::string cardID);

		void AddCard(std::string cardID, int numCardToAdd);
		void DeleteCard(std::string cardID, const int numCardToDelete);

	private:
		CardClass m_class;
		std::string m_name;
		unsigned int m_numOfCards;
		std::vector<std::pair<std::string, int>> m_cards;
	};
}

#endif