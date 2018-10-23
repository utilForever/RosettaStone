// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_MINION_H
#define HEARTHSTONEPP_MINION_H

#include <hspp/Cards/Character.h>

namespace Hearthstonepp
{
//!
//! \brief Minion structure.
//!
//! This structure inherits from Character structure.
//!
struct Minion : public Character
{
    //! Default constructor.
    Minion() = default;

    //! Constructs minion with given \p card.
    //! \param card A reference to the card.
    Minion(Card& card);

    //! Default destructor.
    virtual ~Minion() = default;

    //! Sets ability to the card.
    //! \param tag The game tag to indicate ability.
    //! \param flag The flag that specifies whether or not the ability is set.
    void SetAbility(GameTag tag, bool flag) override;

    //! Checks newly assigned abilities.
    void CheckAbilities();
};
}  // namespace Hearthstonepp

#endif