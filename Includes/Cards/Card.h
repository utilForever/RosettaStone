/*************************************************************************
> File Name: Card.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARD_H
#define HEARTHSTONEPP_CARD_H

#include <Enchants/Power.h>
#include <Enums/CardEnums.h>

#include <map>
#include <string>
#include <vector>

namespace Hearthstonepp
{
struct Card
{
    Card() = default;
    virtual ~Card() = default;

    void Initialize();

    bool HasMechanic(GameTag mechanic) const;

    unsigned int GetMaxAllowedInDeck() const;

    virtual void ShowBriefInfo() const;

    virtual void ShowInfo() const;

    Rarity rarity = Rarity::INVALID;
    Faction faction = Faction::INVALID;
    CardSet cardSet = CardSet::INVALID;
    CardClass cardClass = CardClass::INVALID;
    CardType cardType = CardType::INVALID;
    Race race = Race::INVALID;

    std::string id;
    std::string name;
    std::string text;
    size_t cost;

    std::vector<GameTag> mechanics;
    std::map<PlayReq, int> playRequirements;
    std::vector<std::string> entourages;

    Power power;

    unsigned int maxAllowedInDeck;    
    bool isCollectible;
};
}

#endif