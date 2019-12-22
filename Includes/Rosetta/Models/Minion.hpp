// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_MINION_HPP
#define ROSETTASTONE_MINION_HPP

#include <Rosetta/Models/Character.hpp>

namespace RosettaStone
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

    //! Returns the flag that indicates whether it is untouchable.
    //! \return The flag that indicates whether it is untouchable.
    bool IsUntouchable() const;

    //! Returns the flag that indicates whether it has charge.
    //! \return The flag that indicates whether it has charge.
    bool HasCharge() const;

    //! Disables all special effects on this minion.
    void Silence();

    //! Resets all game tag values that where changed after creation.
    //! Any enchants and trigger is removed.
    void Reset() override;

    //! Destroys minion.
    void Destroy() override;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_MINION_HPP
