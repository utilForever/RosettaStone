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
    Player(std::string&& email, std::string&& nickname);
    Player(std::string&& email, std::string&& nickname,
           std::vector<Deck*> decks);

    std::string GetEmail() const;
    std::string GetNickname() const;
    size_t GetNumOfDeck() const;
    Deck* GetDeck(size_t idx) const;

    void ShowDeckList() const;
    bool CreateDeck(std::string name, CardClass playerClass);
    bool DeleteDeck(size_t selectedDeck);

 private:
    std::string m_email;
    std::string m_nickname;
    std::vector<Deck*> m_decks;
};
}

#endif