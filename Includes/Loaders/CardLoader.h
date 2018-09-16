#ifndef HEARTHSTONEPP_CARD_LOADER_H
#define HEARTHSTONEPP_CARD_LOADER_H

#include <Cards/Card.h>

#include <json/json.hpp>

#include <vector>

namespace Hearthstonepp
{
//!
//! \brief CardLoader class.
//!
//! This class loads card data from cards.json.
//!
class CardLoader
{
 public:
    //! Loads card data from cards.json.
    //! \param cards Data storage to store added cards with power.
    void Load(std::vector<Card*>& cards) const;
};
}  // namespace Hearthstonepp

#endif