/*************************************************************************
> File Name: Entity.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: The base class of all data-holding/action-performing/
           visible or invisible objects in a Hearthstone++.
           An entity is defined as a collection of properties, called Tags.
> Created Time: 2018/07/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Entity.h>

namespace Hearthstonepp
{
Entity::Entity(const Card* pCard) : card(pCard)
{
    // Do nothing
}

Entity::~Entity()
{
    
}

void Entity::GetDataFromCard()
{

}
}