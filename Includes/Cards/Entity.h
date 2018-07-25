/*************************************************************************
> File Name: Entity.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: The base class of all data-holding/action-performing/
           visible or invisible objects in a Hearthstone++.
           An entity is defined as a collection of properties, called Tags.
> Created Time: 2018/07/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_ENTITY_H
#define HEARTHSTONEPP_ENTITY_H

#include <Cards/Card.h>

#include <map>

namespace Hearthstonepp
{
struct Card;
class GameTag;

struct Entity
{
    Entity() = default;
    Entity(const Card* pCard);
    virtual ~Entity();

    const Card* card = nullptr;

    std::map<GameTag, int> gameTags;

    virtual void GetDataFromCard();
};
}

#endif