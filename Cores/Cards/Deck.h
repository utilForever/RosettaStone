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

#include <Cards/Card.h>
#include <Cards/Cards.h>
#include <Enums/CardEnums.h>

#include <string>

namespace Hearthstonepp
{
class Deck
{
 public:
    Deck();
    Deck(std::string name, const CardClass playerClass);

    std::string GetName() const;
    CardClass GetClass() const;
    unsigned int GetNumOfCards() const;
    size_t GetUniqueNumOfCards() const;
    unsigned int GetNumCardInDeck(std::string cardID);
    std::vector<const Card*> GetPrimitiveDeck() const;
    std::pair<std::string, int> GetCard(size_t idx) const;

    void ShowCardList() const;

    bool AddCard(std::string cardID, int numCardToAdd);
    bool DeleteCard(std::string cardID, const int numCardToDelete);

 private:
    std::string m_name;
    CardClass m_class;

    unsigned int m_numOfCards;
    std::vector<std::pair<std::string, int>> m_cards;
};
}

#endif