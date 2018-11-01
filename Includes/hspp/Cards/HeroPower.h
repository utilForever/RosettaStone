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
    //! Constructs hero power with given \p card.
    //! \param card A reference to the card.
    HeroPower(Card& card);

    //! Copy constructor.
    HeroPower(const HeroPower& power);

    //! Copy assignment operator.
    HeroPower& operator=(const HeroPower& power);

    //! Clones member variables.
    HeroPower* Clone() const override;
};
}  // namespace Hearthstonepp

#endif