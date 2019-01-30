// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HERO_HPP
#define HEARTHSTONEPP_HERO_HPP

#include <hspp/Models/Character.hpp>
#include <hspp/Models/HeroPower.hpp>
#include <hspp/Models/Weapon.hpp>

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

    //! Constructs hero with given \p gameAgent and \p card.
    //! \param gameAgent The game agent.
    //! \param card A reference to the card.
    Hero(GameAgent* gameAgent, Card& card);

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

    //! Summons minion.
    //! \param pos The position to summon in battlefield.
    void Summon(std::size_t pos) override;

    //! Destroys hero.
    void Destroy() override;

    //! Returns the presence of weapon.
    //! \return true if hero has weapon, and false otherwise.
    bool HasWeapon() const;

    //! Returns the value of attack.
    //! \return The value of attack.
    size_t GetAttack() const override;

    HeroPower* heroPower = nullptr;
    Weapon* weapon = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HERO_HPP