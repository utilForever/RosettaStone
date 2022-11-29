// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_PLACEABLE_HPP
#define ROSETTASTONE_PLAYMODE_PLACEABLE_HPP

namespace RosettaStone::PlayMode
{
//!
//! \brief Placeable class.
//!
//! This class inherits from Playable class.
//!
class Placeable
{
 public:
    //! Virtual default destructor.
    virtual ~Placeable() = default;

    //! Returns the value of last board position.
    //! \return The value of last board position.
    virtual int GetLastBoardPos() const = 0;

    //! Sets the value of last board position.
    //! \param value The value of last board position.
    virtual void SetLastBoardPos(int value) = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PLACEABLE_HPP
