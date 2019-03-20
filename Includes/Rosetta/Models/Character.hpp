// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_CHARACTER_HPP
#define ROSETTASTONE_CHARACTER_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
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

    //! Constructs character with given \p _owner and \p _card.
    //! \param _owner An owner of the card.
    //! \param _card A reference to the card.
    Character(Player& _owner, Card& _card);

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

    //! Returns the value of attack.
    //! \return The value of attack.
    virtual size_t GetAttack() const;

    //! Destroys character.
    void Destroy() override;

    //! Returns whether attack is possible.
    //! \return Whether attack is possible.
    bool CanAttack() const;

    //! Returns whether the target is valid in combat.
    //! \param opponent The opponent player.
    //! \param target A pointer to the target.
    //! \return true if the target is valid, and false otherwise.
    bool IsValidCombatTarget(Player& opponent, Character* target) const;

    //! Returns a list of valid target in combat.
    //! \param opponent The opponent player.
    //! \return A list of pointer to valid target.
    static std::vector<Character*> GetValidCombatTargets(Player& opponent);

    //! Takes damage from a certain other entity.
    //! \param source The character to take damage.
    //! \param damage The value of damage.
    //! \return Final damage taking into account ability.
    size_t TakeDamage(Character& source, std::size_t damage);

    //! Gets healed by a certain other entity.
    //! \param source The character to get heal.
    //! \param heal The value of heal.
    void TakeHeal(Character& source, std::size_t heal);

    std::size_t numAttacked = 0;
    std::size_t attack = 0;
    int health = 0;
    int maxHealth = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHARACTER_HPP
