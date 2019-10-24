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
    //! Default constructor.
    Minion() = default;

    //! Constructs minion with given \p _owner, \p _card and \p tags.
    //! \param _owner The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    Minion(Player& _owner, Card* _card, std::map<GameTag, int> tags);

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
