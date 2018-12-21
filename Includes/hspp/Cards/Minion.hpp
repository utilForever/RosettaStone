// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_MINION_HPP
#define HEARTHSTONEPP_MINION_HPP

#include <hspp/Cards/Character.hpp>

namespace Hearthstonepp
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

    //! Constructs minion with given \p card.
    //! \param card A reference to the card.
    Minion(GameAgent* gameAgent, Card& card);

    //! Default destructor.
    virtual ~Minion() = default;

    //! Default copy constructor.
    Minion(const Minion& minion) = default;

    //! Default move constructor.
    Minion(Minion&& minion) = default;

    //! Default copy assignment operator.
    Minion& operator=(const Minion& minion) = default;

    //! Default move assignment operator.
    Minion& operator=(Minion&& minion) = default;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value) override;

    //! Checks newly assigned abilities.
    void CheckAbilities();
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_MINION_HPP