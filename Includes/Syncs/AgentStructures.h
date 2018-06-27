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

#include <Accounts/Account.h>
#include <Cards/Card.h>
#include <Cards/Hero.h>
#include <Cards/Weapon.h>
#include <Enchants/HeroPower.h>

namespace Hearthstonepp
{
using BYTE = unsigned char;

struct Player
{
    Player(const Account* account, const Deck* deck);

    BYTE id;
    BYTE totalMana;
    BYTE existMana;
    BYTE exhausted;

    std::string email;
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

    bool operator==(const Player& player) const
    {
        return this->email == player.email;
    }
};
}  // namespace Hearthstonepp

#endif