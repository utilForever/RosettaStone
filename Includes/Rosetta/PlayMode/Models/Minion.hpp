// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_MINION_HPP
#define ROSETTASTONE_PLAYMODE_MINION_HPP

#include <Rosetta/PlayMode/Models/Character.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Minion class.
//!
//! This class inherits from Character class.
//!
class Minion : public Character
{
 public:
    //! Constructs minion with given \p player, \p card, \p tags and \p id.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    //! \param id The ID.
    Minion(Player* player, Card* card, std::map<GameTag, int> tags,
           int id = -1);

    //! Default destructor.
    ~Minion() = default;

    //! Deleted copy constructor.
    Minion(const Minion&) = delete;

    //! Deleted copy assignment operator.
    Minion& operator=(const Minion&) = delete;

    //! Deleted move constructor.
    Minion(Minion&&) noexcept = delete;

    //! Deleted move assignment operator.
    Minion& operator=(Minion&&) noexcept = delete;

    //! Returns the value of last board position.
    //! \return The value of last board position.
    int GetLastBoardPos() const;

    //! Sets the value of last board position.
    //! \param value The value of last board position.
    void SetLastBoardPos(int value);

    //! Gets the minions adjacent to this minion in order from left to right.
    //! \return The minions adjacent to this minion.
    std::vector<Minion*> GetAdjacentMinions() const;

    //! Returns the flag that indicates whether it is Lackey.
    //! \return The flag that indicates whether it is Lackey.
    bool IsLackey() const;

    //! Returns the flag that indicates whether it is untouchable.
    //! \return The flag that indicates whether it is untouchable.
    bool IsUntouchable() const;

    //! Returns the flag that indicates whether it has charge.
    //! \return The flag that indicates whether it has charge.
    bool HasCharge() const;

    //! Returns the flag that indicates whether it has taunt.
    //! \return The flag that indicates whether it has taunt.
    bool HasTaunt() const;

    //! Returns the flag that indicates whether it has divine shield.
    //! \return The flag that indicates whether it has divine shield.
    bool HasDivineShield() const;

    //! Returns the flag that indicates whether it has poisonous.
    //! \return The flag that indicates whether it has poisonous.
    bool HasPoisonous() const;

    //! Returns the flag that indicates whether it has freeze.
    //! \return The flag that indicates whether it has freeze.
    bool HasFreeze() const;

    //! Returns the flag that indicates whether it has rush.
    //! \return The flag that indicates whether it has rush.
    bool HasRush() const;

    //! Returns the flag that indicates whether it has reborn.
    //! \return The flag that indicates whether it has reborn.
    bool HasReborn() const;

    //! Returns the flag that indicates whether it has spellburst.
    //! \return The flag that indicates whether it has spellburst.
    bool HasSpellburst() const;

    //! Returns the flag that indicates whether it is attackable by rush.
    //! \return The flag that indicates whether it is attackable by rush.
    bool IsAttackableByRush() const;

    //! Sets the flag that indicates whether it is attackable by rush.
    //! \param attackable The value of attackable.
    void SetAttackableByRush(bool attackable);

    //! Returns whether attack is possible.
    //! \return Whether attack is possible.
    bool CanAttack() const override;

    //! Disables all special effects on this minion.
    void Silence();

    //! Resets all game tag values that where changed after creation.
    //! Any enchants and trigger is removed.
    void Reset() override;

    //! Destroys minion.
    void Destroy() override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_MINION_HPP
