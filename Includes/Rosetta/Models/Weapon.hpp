// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_WEAPON_HPP
#define ROSETTASTONE_WEAPON_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
{
//!
//! \brief Weapon class.
//!
//! This class inherits from Entity class.
//! Also, it stores durability that shows the number of times you can use that
//! weapon before it is destroyed.
//!
class Weapon : public Entity
{
 public:
    //! Default constructor.
    Weapon() = default;

    //! Constructs weapon with given \p _owner and \p _card.
    //! \param _owner An owner of the card.
    //! \param _card A reference to the card.
    Weapon(Player& _owner, Card& _card);

    //! Destructor.
    virtual ~Weapon();

    //! Default copy constructor.
    Weapon(const Weapon& weapon) = default;

    //! Default move constructor.
    Weapon(Weapon&& weapon) = default;

    //! Default copy assignment operator.
    Weapon& operator=(const Weapon& weapon) = default;

    //! Default move assignment operator.
    Weapon& operator=(Weapon&& weapon) = default;

    std::size_t attack = 0;
    std::size_t durability = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_WEAPON_HPP
