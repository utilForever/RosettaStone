// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/CardDefs.hpp>
#include <Rosetta/Loaders/InternalCardLoader.hpp>

namespace RosettaStone
{
void InternalCardLoader::Load(std::vector<Card*>& cards)
{
    for (auto& card : cards)
    {
        const auto cardDef =
            CardDefs::GetInstance().FindCardDefByCardID(card->id);

        card->power = cardDef.power;
        card->playRequirements = cardDef.playReqs;
        card->chooseCardIDs = cardDef.chooseCardIDs;
        card->entourages = cardDef.entourages;
        card->gameTags[GameTag::QUEST_PROGRESS_TOTAL] =
            cardDef.questProgressTotal;
    }
}
}  // namespace RosettaStone
