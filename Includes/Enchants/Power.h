#ifndef HEARTHSTONEPP_POWER_H
#define HEARTHSTONEPP_POWER_H

#include <vector>

namespace Hearthstonepp
{
class ITask;
class Enchant;

//!
//! \brief Power structure.
//!
//! This structure stores task to perform power and enchant to apply it.
//!
struct Power
{
    std::vector<ITask*> powerTask;
    Enchant* enchant = nullptr;
};
}  // namespace Hearthstonepp

#endif