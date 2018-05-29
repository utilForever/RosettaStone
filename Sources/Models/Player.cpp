/*************************************************************************
> File Name: Player.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player class that stores a list of decks.
> Created Time: 2017/10/18
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Player.h>

#include <iostream>

namespace Hearthstonepp
{
	Player::Player() : m_id("Anonymous"), m_name("Anonymous")
	{
		// Do nothing
	}

	Player::Player(std::string&& id, std::string&& name) : m_id(std::move(id)), m_name(std::move(name))
	{
		// Do nothing
	}

	Player::Player(std::string&& id, std::string&& name, std::vector<Deck*> decks) : m_id(std::move(id)), m_name(std::move(name)), m_decks(decks)
	{
		// Do nothing
	}

	std::string Player::GetID() const
	{
		return m_id;
	}

	std::string Player::GetName() const
	{
		return m_name;
	}

	size_t Player::GetNumOfDeck() const
	{
		return m_decks.size();
	}

	Deck* Player::GetDeck(size_t idx) const
	{
		return m_decks[idx];
	}

	void Player::ShowDeckList() const
	{
		size_t idx = 0;
		for (auto& deck : m_decks)
		{
			std::cout << ++idx << ". " << deck->GetName() << " (" << deck->GetNumOfCards() << " cards)\n";
		}
	}

	bool Player::CreateDeck(std::string name, CardClass deckClass)
	{
		if (deckClass == +CardClass::INVALID)
			return false;
		
		m_decks.emplace_back(new Deck(name, deckClass));
		return true;
	}

	bool Player::DeleteDeck(size_t selectedDeck)
	{
		m_decks.erase(m_decks.begin() + selectedDeck);
		return true;
	}
}