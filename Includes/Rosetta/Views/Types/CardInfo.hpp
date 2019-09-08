// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_VIEWS_TYPES_CARD_INFO_HPP
#define ROSETTASTONE_VIEWS_TYPES_CARD_INFO_HPP

#include <Rosetta/Views/Types/UnknownCards.hpp>

#include <utility>

namespace RosettaStone::Views::Types
{
//!
//! \brief CardInfo struct.
//!
struct CardInfo
{
    void SetAsRevealedCard(std::string _cardID)
    {
        cardID = std::move(_cardID);
    }

    void SetAsHiddenCard(size_t setID, size_t cardIdx)
    {
        cardID = INVALID_CARD_ID;
        unknownCardsSetID = setID;
        unknownCardsSetCardIdx = cardIdx;
    }

    std::string GetCardID(
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

    std::string cardID;
    std::size_t unknownCardsSetID = 0;
    std::size_t unknownCardsSetCardIdx = 0;
};
}  // namespace RosettaStone::Views::Types

#endif  // ROSETTASTONE_VIEWS_TYPES_CARD_INFO_HPP
