// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai
//
#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Views/Types/CardInfo.hpp>

namespace RosettaStone::PlayMode::Views::Types
{
void CardInfo::SetAsRevealedCard(std::string _cardID)
{
    cardID = std::move(_cardID);
}

void CardInfo::SetAsHiddenCard(size_t setID, size_t cardIdx)
{
    cardID = INVALID_CARD_ID;
    unknownCardsSetID = setID;
    unknownCardsSetCardIdx = cardIdx;
}

std::string CardInfo::GetCardID(
    const UnknownCardsSetsManager& unknownCardsManager) const
{
    if (cardID != INVALID_CARD_ID)
    {
        return cardID;
    }
    else
    {
        return unknownCardsManager.GetCardID(unknownCardsSetID,
                                             unknownCardsSetCardIdx);
    }
}
}  // namespace RosettaStone::PlayMode::Views::Types
