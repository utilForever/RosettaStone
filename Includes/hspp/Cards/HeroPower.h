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
//! \brief HeroPower class.
//!
//! This class inherits from Entity structure.
//!
class HeroPower : public Entity
{
 public:
    //! Default constructor.
    HeroPower() = default;

    //! Constructs hero power with given \p card.
    //! \param card A reference to the card.
    HeroPower(Card& card);

    //! Default destructor.
    ~HeroPower() = default;

    //! Default copy constructor.
    HeroPower(const HeroPower& power) = default;

    //! Default move constructor.
    HeroPower(HeroPower&& power) = default;

    //! Default copy assignment operator.
    HeroPower& operator=(const HeroPower& power) = default;

    //! Default move assignment operator.
    HeroPower& operator=(HeroPower&& power) = default;

    //! Clones member variables.
    HeroPower* Clone() const override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HERO_POWER_H