/*************************************************************************
> File Name: AgentStructure.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_AGENT_STRUCTURES_H
#define HEARTHSTONEPP_AGENT_STRUCTURES_H

#include <Models/Card.h>
#include <Models/Cards.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Weapon.h>
#include <Models/Account.h>

namespace Hearthstonepp
{
using BYTE = unsigned char;

struct Player
{
    Player(Account* account, Deck* deck);

    BYTE id;
    BYTE totalMana;
    BYTE existMana;
    BYTE exhausted;

    std::string accountID;
    Hero* hero;
    HeroPower* power;
    Weapon* weapon;

    // Card storage
    std::vector<Card> cardsInDeck;

    // Card objects
    std::vector<Card*> cardsPtrInDeck;
    std::vector<Card*> field;
    std::vector<Card*> hand;
    std::vector<Card*> usedSpell;
    std::vector<Card*> usedMinion;

    // Already Attacked Minion
    std::vector<Card*> attacked;
};
}  // namespace Hearthstonepp

#endif