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

    //! Constructs minion with given \p pCard.
    //! \param pCard A pointer to the card.
    Minion(const Card* pCard);

    //! Default destructor.
    virtual ~Minion() = default;
};
}  // namespace Hearthstonepp

#endif