// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_CHARACTER_H
#define HEARTHSTONEPP_CHARACTER_H

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
//!
//! \brief Abstract character class that stores hero and minion data.
//!
//! This class inherits from Entity class. Also, it stores some
//! attributes that only characters have such as attack and health.
//!
class Character : public Entity
{
 public:
    //! Default constructor.
    Character() = default;

    //! Constructs character with given \p card.
    //! \param card A reference to the card.
    Character(Card& card);

    //! Default destructor.
    virtual ~Character() = default;

    //! Copy constructor.
    Character(const Character& c);

    //! Copy assignment operator.
    Character& operator=(const Character& c);

    //! Clones member variables.
    Character* Clone() const override;

    //! Returns the value of attack.
    //! \return The value of attack.
    size_t GetAttack() const;

    //! Sets the value of attack.
    //! \param attack the value of attack.
    void SetAttack(size_t attack);

    //! Returns whether attack is possible.
    //! \return Whether attack is possible.
    bool CanAttack() const;

    //! Takes damage from \p source with \p damage value.
    //! \param source The character to give damage.
    //! \param damage The value of damage.
    //! \return Final damage taking into account ability.
    size_t TakeDamage(Character& source, size_t damage);

    size_t attackableCount = 0;
    size_t remainTurnToThaw = 0;
    size_t health = 0;
    size_t maxHealth = 0;

 private:
    size_t m_attack = 0;
};
}  // namespace Hearthstonepp

#endif