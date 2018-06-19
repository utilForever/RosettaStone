/*************************************************************************
> File Name: Cards.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Cards class that stores a list of cards.
> Created Time: 2017/10/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARDS_H
#define HEARTHSTONEPP_CARDS_H

#include <Models/Card.h>

#include <vector>

namespace Hearthstonepp
{
struct SearchFilter
{
    Rarity rarity = Rarity::INVALID;
    CardClass playerClass = CardClass::INVALID;
    CardType cardType = CardType::INVALID;
    Race race = Race::INVALID;
    GameTag mechanic = GameTag::INVALID;

    std::string name;
    size_t costMin, costMax;
    size_t attackMin, attackMax;
    size_t healthMin, healthMax;
};

class Cards
{
 public:
    static Cards* GetInstance();

    std::vector<Card*> GetAllCards() const;

    const Card* FindCardByID(const std::string id);
    std::vector<Card*> FindCardByRarity(Rarity rarity);
    std::vector<Card*> FindCardByClass(CardClass cardClass);
    std::vector<Card*> FindCardByType(CardType cardType);
    std::vector<Card*> FindCardByRace(Race race);
    Card* FindCardByName(const std::string name);
    std::vector<Card*> FindCardByCost(size_t minVal, size_t maxVal);
    std::vector<Card*> FindCardByAttack(size_t minVal, size_t maxVal);
    std::vector<Card*> FindCardByHealth(size_t minVal, size_t maxVal);
    std::vector<Card*> FindCardByMechanics(std::vector<GameTag> mechanics);

    const Card* GetHeroCard(CardClass cardClass);
    const Card* GetDefaultHeroPower(CardClass cardClass);

 private:
    Cards();
    ~Cards();
    Cards(const Cards&) = delete;
    Cards(Cards&&) = delete;
    Cards& operator=(const Cards&) = delete;
    Cards& operator=(Cards&&) = delete;

    static Cards* m_instance;

    std::vector<Card*> m_cards;
};
}

#endif