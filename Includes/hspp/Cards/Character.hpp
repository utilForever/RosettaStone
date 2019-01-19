// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_CHARACTER_HPP
#define HEARTHSTONEPP_CHARACTER_HPP

#include <hspp/Cards/Entity.hpp>

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
    Character(GameAgent* gameAgent, Card& card);

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

    //! Sets the value of attack.
    //! \param attack the value of attack.
    void SetAttack(size_t attack);

    //! Summons character (pure virtual function).
    //! \param pos The position to summon.
    virtual void Summon(std::size_t pos) = 0;

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
    size_t TakeDamage(Character& source, size_t damage);

    //! Gets healed by a certain other entity.
    //! \param source The character to get heal.
    //! \param heal The value of heal.
    void TakeHeal(Character& source, int heal);

    size_t attackableCount = 0;
    size_t numTurnToUnfreeze = 0;
    int health = 0;
    int maxHealth = 0;
    bool isDestroyed = false;

 protected:
    size_t m_attack = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_CHARACTER_HPP