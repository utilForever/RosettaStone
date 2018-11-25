// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_CHARACTER_H
#define HEARTHSTONEPP_CHARACTER_H

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
class Player;

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

    //! Default copy constructor.
    Character(const Character& c) = default;

    //! Default move constructor.
    Character(Character&& c) = default;

    //! Default copy assignment operator.
    Character& operator=(const Character& c) = default;

    //! Default move assignment operator.
    Character& operator=(Character&& c) = default;

    //! Clones member variables.
    Character* Clone() const override;

    //! Returns the value of attack.
    //! \return The value of attack.
    virtual size_t GetAttack() const;

    //! Sets the value of attack.
    //! \param attack the value of attack.
    void SetAttack(size_t attack);

    //! Returns whether attack is possible.
    //! \return Whether attack is possible.
    bool CanAttack() const;

    //! Returns whether the target is valid.
    //! \param opponent The opponent player.
    //! \param target A pointer to the target.
    //! \return Whether the target is valid.
    bool IsValidAttackTarget(Player& opponent, Character* target) const;

    //! Returns a list of valid target.
    //! \param opponent The opponent player.
    //! \return A list of pointer to valid target.
    static std::vector<Character*> GetValidAttackTargets(Player& opponent);

    //! Takes damage from \p source with \p damage value.
    //! \param source The character to give damage.
    //! \param damage The value of damage.
    //! \return Final damage taking into account ability.
    size_t TakeDamage(Character& source, size_t damage);

    size_t attackableCount = 0;
    size_t numTurnToUnfreeze = 0;
    int health = 0;
    int maxHealth = 0;

 protected:
    size_t m_attack = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_CHARACTER_H