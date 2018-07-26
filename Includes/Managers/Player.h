/*************************************************************************
> File Name: Player.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Player Structure for GameAgent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_AGENT_STRUCTURES_H
#define HEARTHSTONEPP_AGENT_STRUCTURES_H

#include <Accounts/Account.h>
#include <Cards/Entity.h>
#include <Cards/Hero.h>
#include <Cards/HeroPower.h>
#include <Cards/Minion.h>
#include <Cards/Spell.h>
#include <Cards/Weapon.h>
#include <Enchants/Enchant.h>

#include <memory>

namespace Hearthstonepp
{
using BYTE = unsigned char;

struct Player
{
	static constexpr BYTE USER_INVALID = 255;

    Player(const Account* account, const Deck* deck);

    BYTE id;
    BYTE totalMana;
    BYTE existMana;
    BYTE exhausted;

    std::string email;
    Hero* hero;
    HeroPower* power;

    // Card storage
    std::vector<Entity*> cards;

    // Card objects
    std::vector<Character*> field;
    std::vector<Entity*> hand;
    std::vector<Spell*> usedSpell;
    std::vector<Character*> usedMinion;

    // Already Attacked Minion
    std::vector<Character*> attacked;

    bool operator==(const Player& player) const
    {
        return this->email == player.email;
    }
};
}  // namespace Hearthstonepp

#endif