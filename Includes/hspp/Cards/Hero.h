// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HERO_H
#define HEARTHSTONEPP_HERO_H

#include <hspp/Cards/Character.h>
#include <hspp/Cards/Weapon.h>

namespace Hearthstonepp
{
//!
//! \brief Hero class.
//!
//! This class inherits from Character structure.
//! Also, it stores weapon that can attack to enemy.
//!
class Hero : public Character
{
 public:
    //! Default constructor.
    Hero() = default;

    //! Constructs hero with given \p card.
    //! \param card A reference to the card.
    Hero(Card& card);

    //! Default destructor.
    ~Hero();

    //! Copy constructor.
    Hero(const Hero& hero);

    //! Move constructor.
    Hero(Hero&& hero) noexcept;

    //! Copy assignment operator.
    Hero& operator=(const Hero& hero);

    //! Move assignment operator.
    Hero& operator=(Hero&& hero) noexcept;

    //! Clones member variables.
    Hero* Clone() const override;

    //! Returns the value of attack.
    //! \return The value of attack.
    size_t GetAttack() const override;

    Weapon* weapon = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HERO_H