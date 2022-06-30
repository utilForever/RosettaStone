// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_HERO_HPP
#define ROSETTASTONE_PLAYMODE_HERO_HPP

#include <Rosetta/PlayMode/Models/Character.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Hero class.
//!
//! This class inherits from Character class.
//! Also, it stores weapon that can attack to enemy.
//!
class Hero : public Character
{
 public:
    //! Constructs hero with given \p _player, \p _card, \p tags and \p id.
    //! \param _player The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param id The ID.
    Hero(Player* _player, Card* _card, std::map<GameTag, int> tags,
         int id = -1);

    //! Default destructor.
    ~Hero();

    //! Deleted copy constructor.
    Hero(const Hero&) = delete;

    //! Deleted copy assignment operator.
    Hero& operator=(const Hero&) = delete;

    //! Deleted move constructor.
    Hero(Hero&&) noexcept = delete;

    //! Deleted move assignment operator.
    Hero& operator=(Hero&&) noexcept = delete;

    //! Returns the value of attack.
    //! \return The value of attack.
    int GetAttack() const override;

    //! Returns the value of armor.
    //! \return The value of armor.
    int GetArmor() const;

    //! Sets the value of armor.
    //! \param armor The value of armor.
    void SetArmor(int armor);

    //! Returns the value of hero power damage.
    //! \return The value of hero power damage.
    int GetHeroPowerDamage() const;

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

    //! Returns the flag that indicates whether it has lifesteal.
    //! \return The flag that indicates whether it has lifesteal.
    bool HasLifesteal() const override;

    //! Returns the flag that indicates whether it has honorable kill.
    //! \return The flag that indicates whether it has honorable kill.
    bool HasHonorableKill() const override;

    HeroPower* heroPower = nullptr;
    Weapon* weapon = nullptr;

    std::vector<Aura*> weaponAuras;

    TriggerEvent gainAttackTrigger;

    int fatigue = 0;
    int damageTakenThisTurn = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_HERO_HPP
