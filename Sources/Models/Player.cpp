/*************************************************************************
> File Name: Player.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player class that stores a list of decks.
> Created Time: 2017/10/18
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Player.h>

namespace Hearthstonepp
{
	Player::Player() : m_name("Anonymous")
	{
		// Do nothing
	}

	Player::Player(std::string&& name) : m_name(std::move(name))
	{
		// Do nothing
	}

	Player::Player(std::string&& name, std::vector<Deck*> decks) : m_name(std::move(name)), m_decks(decks)
	{
		// Do nothing
	}
}