#ifndef HEARTHSTONEPP_HERO_POWER_H
#define HEARTHSTONEPP_HERO_POWER_H

#include <Cards/Entity.h>

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
}

#endif