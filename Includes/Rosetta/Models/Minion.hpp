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
//! This class inherits from Character structure.
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
    Minion(Player& _owner, Card& _card, std::map<GameTag, int> tags);

    //! Default destructor.
    ~Minion() = default;

    //! Default copy constructor.
    Minion(const Minion& minion) = default;

    //! Default move constructor.
    Minion(Minion&& minion) = default;

    //! Default copy assignment operator.
    Minion& operator=(const Minion& minion) = default;

    //! Default move assignment operator.
    Minion& operator=(Minion&& minion) = default;

    //! Returns the value of last board position.
    //! \return The value of last board position.
    int GetLastBoardPos() const;

    //! Sets the value of last board position.
    //! \param value The value of last board position.
    void SetLastBoardPos(int value);

    //! Resets all game tag values that where changed after creation.
    //! Any enchants and trigger is removed.
    void Reset() override;

    //! Destroys minion.
    void Destroy() override;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_MINION_HPP
