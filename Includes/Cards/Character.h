#ifndef HEARTHSTONEPP_CHARACTER_H
#define HEARTHSTONEPP_CHARACTER_H

#include <Cards/Entity.h>

namespace Hearthstonepp
{
//!
//! \brief Abstract character structure that stores hero and minion data.
//!
//! This structure inherits from Entity structure. Also, it stores some
//! attributes that only characters have such as attack and health.
//!
struct Character : public Entity
{
    //! Default constructor.
    Character() = default;

    //! Constructs character with given \p pCard.
    //! \param pCard A pointer to the card.
    Character(const Card* pCard);

    //! Default destructor.
    virtual ~Character() = default;

    size_t attack = 0;
    size_t attackableCount = 0;
    size_t health = 0;
    size_t maxHealth = 0;
};
}  // namespace Hearthstonepp

#endif