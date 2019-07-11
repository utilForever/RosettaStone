// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_HERO_HPP
#define ROSETTASTONE_HERO_HPP

#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Weapon.hpp>

namespace RosettaStone
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

    //! Constructs hero with given \p _owner, \p _card and \p tags.
    //! \param _owner The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    Hero(Player& _owner, Card* _card, std::map<GameTag, int> tags);

    //! Default destructor.
    ~Hero();

    //! Deleted copy constructor.
    Hero(const Hero& hero) = delete;

    //! Deleted move constructor.
    Hero(Hero&& hero) = delete;

    //! Copy assignment operator.
    Hero& operator=(const Hero& hero) = delete;

    //! Move assignment operator.
    Hero& operator=(Hero&& hero) = delete;

    //! Returns the value of attack.
    //! \return The value of attack.
    int GetAttack() const override;

    //! Returns the value of armor.
    //! \return The value of armor.
    int GetArmor() const;

    //! Sets the value of armor.
    //! \param armor The value of armor.
    void SetArmor(int armor);

    //! Adds weapon to hero.
    //! \param _weapon A weapon card to add.
    void AddWeapon(Weapon& _weapon);

    //! Removes weapon from hero.
    void RemoveWeapon();

    //! Returns the presence of weapon.
    //! \return true if hero has weapon, and false otherwise.
    bool HasWeapon() const;

    //! Gains armor to hero.
    //! \p amount The amount to gain armor.
    void GainArmor(int amount);

    HeroPower* heroPower = nullptr;
    Weapon* weapon = nullptr;

    int fatigue = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HERO_HPP
