/*************************************************************************
> File Name: PowerLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Power loader that loads data from card data generators.
> Created Time: 2018/08/03
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/PowerLoader.h>
#include <Enchants/Powers.h>

namespace Hearthstonepp
{
void PowerLoader::LoadData(std::vector<Card*>& cards) const
{
    Powers* powers = Powers::GetInstance();

    for (auto& card : cards)
    {
        card->power = powers->FindPowerByCardID(card->id);
    }
}
}  // namespace Hearthstonepp