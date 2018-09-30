// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HERO_POWER_H
#define HEARTHSTONEPP_HERO_POWER_H

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
//!
//! \brief HeroPower structure.
//!
//! This structure inherits from Entity structure.
//!
struct HeroPower : public Entity
{
    //! Constructs hero power with given \p pCard.
    //! \param pCard A pointer to the card.
    HeroPower(const Card* pCard);
};
}  // namespace Hearthstonepp

#endif