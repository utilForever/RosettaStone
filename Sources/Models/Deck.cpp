/*************************************************************************
> File Name: Deck.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Deck class that stores a list of cards.
> Created Time: 2017/10/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Deck.h>

#include <algorithm>

namespace Hearthstonepp
{
	Deck::Deck() :
		m_class(PlayerClass::INVALID), m_name("Empty"), m_numOfCards(0)
	{
		
	}

	Deck::Deck(const PlayerClass playerClass, std::string name) :
		m_class(playerClass), m_name(std::move(name)), m_numOfCards(0)
	{
		
	}

	unsigned int Deck::GetNumOfCards() const
	{
		return m_numOfCards;
	}

	unsigned int Deck::GetNumCardInDeck(std::string cardID)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<const Card*, int>& elem) { return elem.first->GetID() == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			return (*isCardExistInDeck).second;
		}
		
		return 0;
	}

	void Deck::AddCard(const Card* card, int numCardToAdd)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&card](const std::pair<const Card*, int>& elem) { return elem.first->GetID() == card->GetID(); });

		if (isCardExistInDeck != m_cards.end())
		{
			(*isCardExistInDeck).second += numCardToAdd;
		}
		else
		{
			m_cards.emplace_back(std::make_pair(card, numCardToAdd));
		}

		m_numOfCards += numCardToAdd;
	}

	void Deck::DeleteCard(const Card* card, const int numCardToDelete)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&card](const std::pair<const Card*, int>& elem) { return elem.first->GetID() == card->GetID(); });

		if (isCardExistInDeck != m_cards.end())
		{
			(*isCardExistInDeck).second -= numCardToDelete;

			if ((*isCardExistInDeck).second == 0)
			{
				m_cards.erase(isCardExistInDeck);
			}

			m_numOfCards -= numCardToDelete;
		}
	}
}