/*************************************************************************
> File Name: Player.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Player class that stores a list of decks.
> Created Time: 2017/10/18
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYER_H
#define HEARTHSTONEPP_PLAYER_H

#include <Models/Deck.h>

namespace Hearthstonepp
{
	class Player
	{
	public:
		Player();
		Player(std::string&& name);
		Player(std::string&& name, std::vector<Deck*> decks);

		size_t GetNumOfDeck() const;
		Deck* GetDeck(size_t idx) const;

		void ShowDeckList() const;
		void CreateDeck(std::string name, CardClass playerClass);
		void DeleteDeck(size_t selectedDeck);

	private:
		std::string m_name;
		std::vector<Deck*> m_decks;
	};
}

#endif