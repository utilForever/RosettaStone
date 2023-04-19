// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/CardDefs.hpp>
#include <Rosetta/Battlegrounds/Loaders/InternalCardLoader.hpp>

namespace RosettaStone::Battlegrounds
{
void InternalCardLoader::Load(std::array<Card, NUM_BATTLEGROUNDS_CARDS>& cards)
{
    for (auto& card : cards)
    {
        const auto cardDef = CardDefs::GetInstance().FindCardDefByID(card.id);

        card.power = cardDef.power;
        card.playRequirements = cardDef.playReqs;
    }
}
}  // namespace RosettaStone::Battlegrounds
