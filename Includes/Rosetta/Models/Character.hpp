// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

    //! Constructs character with given \p _owner, \p _card and \p tags.
    //! \param _owner The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    Character(Player& _owner, Card* _card, std::map<GameTag, int> tags);

    //! Default destructor.
    ~Character() = default;

    //! Deleted copy constructor.
    Character(const Character&) = delete;

    //! Deleted copy assignment operator.
    Character& operator=(const Character&) = delete;

    //! Deleted move constructor.
    Character(Character&&) noexcept = delete;

    //! Deleted move assignment operator.
    Character& operator=(Character&&) noexcept = delete;

    //! Returns the value of attack.
    //! \return The value of attack.
    virtual int GetAttack() const;

    //! Sets the value of attack.
    //! \param attack The value of attack.
    void SetAttack(int attack);

    //! Returns the value of pre-damage.
    //! \return The value of pre-damage.
    int GetPreDamage() const;

    //! Sets the value of pre-damage.
    //! \param preDamage The value of pre-damage.
    void SetPreDamage(int preDamage);

    //! Returns the value of damage.
    //! \return The value of damage.
    int GetDamage() const;

    //! Sets the value of damage.
    //! \param damage The value of damage.
    void SetDamage(int damage);

    //! Returns the value of health.
    //! \return The value of health.
    int GetHealth() const;

    //! Sets the value of health.
    //! \param health The value of health.
    void SetHealth(int health);

    //! Returns the value of spell power.
    //! \return The value of spell power.
    int GetSpellPower() const;

    //! Sets the value of spell power.
    //! \param spellPower The value of spell power.
    void SetSpellPower(int spellPower);

    //! Returns the number of attacks at this turn.
    //! \return The number of attacks at this turn.
    int GetNumAttacksThisTurn() const;

    //! Gets the number of attacks at this turn.
    //! \param amount The number of attacks at this turn.
    void SetNumAttacksThisTurn(int amount);

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
    std::vector<Character*> GetValidCombatTargets(Player& opponent) const;

    //! Takes damage from a certain other entity.
    //! \param source An entity to give damage.
    //! \param damage The value of damage.
    //! \return Final damage taking into account ability.
    int TakeDamage(Entity& source, int damage);

    //! Takes heal up all taken damage.
    //! \param source An entity to give full heal.
    void TakeFullHeal(Entity& source);

    //! Takes heal a specified amount of health.
    //! \param source An entity to give heal.
    //! \param heal The value of heal.
    void TakeHeal(Entity& source, int heal);

    std::function<void(Player*, Entity*)> afterAttackTrigger;
    std::function<void(Player*, Entity*)> preDamageTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHARACTER_HPP
