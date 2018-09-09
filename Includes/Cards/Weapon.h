#ifndef HEARTHSTONEPP_WEAPON_H
#define HEARTHSTONEPP_WEAPON_H

#include <Cards/Entity.h>

namespace Hearthstonepp
{
//!
//! \brief Weapon structure.
//!
//! This structure inherits from Entity structure.
//! Also, it stores durability that shows the number of times you can use that
//! weapon before it is destroyed.
//!
struct Weapon : public Entity
{
    //! Default constructor.
    Weapon() = default;

    //! Constructs weapon with given \p pCard.
    //! \param pCard A pointer to the card.
    Weapon(const Card* pCard);
    
    //! Default destructor.
    virtual ~Weapon();

    size_t durability = 0;
};
}

#endif