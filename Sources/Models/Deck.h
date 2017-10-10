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

#include <string>

namespace Hearthstonepp
{
    struct Deck
    {
        std::string name;
        unsigned int numOfCards = 0;
    };
}

#endif