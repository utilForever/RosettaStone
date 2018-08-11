/*************************************************************************
> File Name: PowerLoader.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Power loader that loads data from card data generators.
> Created Time: 2018/08/03
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_POWER_LOADER_H
#define HEARTHSTONEPP_POWER_LOADER_H

#include <Cards/Card.h>

#include <vector>

namespace Hearthstonepp
{
class PowerLoader
{
 public:
    void LoadData(std::vector<Card*>& cards) const;
};
}  // namespace Hearthstonepp

#endif