#ifndef HEARTHSTONEPP_POWER_LOADER_H
#define HEARTHSTONEPP_POWER_LOADER_H

#include <Cards/Card.h>

#include <vector>

namespace Hearthstonepp
{
//!
//! \brief PowerLoader class.
//!
//! This class loads power data from card data generators.
//!
class PowerLoader
{
 public:
    //! Loads power data from card data generators.
    //! \param cards Data storage to store added cards with power.
    void LoadData(std::vector<Card*>& cards) const;
};
}  // namespace Hearthstonepp

#endif