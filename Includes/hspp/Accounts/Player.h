#ifndef HEARTHSTONEPP_AGENT_STRUCTURES_H
#define HEARTHSTONEPP_AGENT_STRUCTURES_H

#include <hspp/Accounts/Account.h>
#include <hspp/Cards/Entity.h>
#include <hspp/Cards/Hero.h>
#include <hspp/Cards/HeroPower.h>
#include <hspp/Cards/Minion.h>
#include <hspp/Cards/Spell.h>

namespace Hearthstonepp
{
using BYTE = unsigned char;

//!
//! \brief Player class.
//!
//! This class stores various information that used in Hearthstone game.
//! NOTE: This information should be used differently from the existing card
//! information because there are various effects on the card.
//!
class Player
{
 public:
    static constexpr BYTE USER_INVALID = 255;

    //! Constructs player with given \p account and \p deck.
    //! \param account The account stores user information.
    //! \param deck A deck where cards are stored.
    Player(const Account* account, const Deck* deck);

    //! Operator overloading: The equality operator.
    bool operator==(const Player& player) const
    {
        return this->email == player.email;
    }

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
};
}  // namespace Hearthstonepp

#endif
