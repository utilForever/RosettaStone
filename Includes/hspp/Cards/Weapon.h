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

    //! Constructs weapon with given \p card.
    //! \param card A reference to the card.
    Weapon(Card& card);

    //! Default destructor.
    virtual ~Weapon() = default;

    //! Default copy constructor.
    Weapon(const Weapon& weapon) = default;

    //! Default move constructor.
    Weapon(Weapon&& weapon) = default;

    //! Default copy assignment operator.
    Weapon& operator=(const Weapon& weapon) = default;

    //! Default move assignment operator.
    Weapon& operator=(Weapon&& weapon) = default;

    //! Clones member variables.
    Weapon* Clone() const override;

    //! Returns the value of attack.
    //! \return The value of attack.
    virtual size_t GetAttack() const;

    //! Sets the value of attack.
    //! \param attack the value of attack.
    void SetAttack(size_t attack);

    //! Returns the value of durability.
    //! \return The value of durability.
    virtual size_t GetDurability() const;

    //! Sets the value of durability.
    //! \param durability the value of durability.
    void SetDurability(size_t durability);

 protected:
    size_t m_attack = 0;
    size_t m_durability = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_WEAPON_H