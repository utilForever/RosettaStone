// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Loaders/InternalCardLoader.hpp>
#include <Rosetta/Managers/CardDataManager.hpp>

namespace RosettaStone
{
void InternalCardLoader::Load(std::vector<Card*>& cards)
{
    for (auto& card : cards)
    {
        card->power =
            CardDataManager::GetInstance().FindPowerByCardID(card->id);
        card->playRequirements =
            CardDataManager::GetInstance().FindPlayReqsByCardID(card->id);
        card->entourages =
            CardDataManager::GetInstance().FindEntouragesByCardID(card->id);
    }
}
}  // namespace RosettaStone
