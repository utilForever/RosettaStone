// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_WEAPON_H
#define HEARTHSTONEPP_WEAPON_H

#include <hspp/Cards/Entity.h>

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

    //! Constructs weapon with given \p card.
    //! \param card A reference to the card.
    Weapon(Card& card);

    //! Default destructor.
    virtual ~Weapon() = default;

    //! Copy constructor.
    Weapon(const Weapon& weapon);

    //! Copy assignment operator.
    Weapon& operator=(const Weapon& weapon);

    //! Clones member variables.
    Weapon* Clone() const override;

    size_t attack = 0;
    size_t durability = 0;
};
}  // namespace Hearthstonepp

#endif