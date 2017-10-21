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
		m_class(CardClass::INVALID), m_name("Empty"), m_numOfCards(0)
	{

	}

	Deck::Deck(const CardClass playerClass, std::string name) :
		m_class(playerClass), m_name(std::move(name)), m_numOfCards(0)
	{

	}

	std::string Deck::GetName() const
	{
		return m_name;
	}

	unsigned int Deck::GetNumOfCards() const
	{
		return m_numOfCards;
	}

	unsigned int Deck::GetNumCardInDeck(std::string cardID)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			return (*isCardExistInDeck).second;
		}

		return 0;
	}

	void Deck::AddCard(std::string cardID, int numCardToAdd)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			(*isCardExistInDeck).second += numCardToAdd;
		}
		else
		{
			m_cards.emplace_back(std::make_pair(cardID, numCardToAdd));
		}

		m_numOfCards += numCardToAdd;
	}

	void Deck::DeleteCard(std::string cardID, const int numCardToDelete)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

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