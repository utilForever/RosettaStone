// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_VIEWS_TYPES_CARD_INFO_HPP
#define ROSETTASTONE_PLAYMODE_VIEWS_TYPES_CARD_INFO_HPP

#include <Rosetta/PlayMode/Views/Types/UnknownCards.hpp>

namespace RosettaStone::PlayMode::Views::Types
{
//!
//! \brief CardInfo struct.
//!
//! This struct stores the card ID, the ID and card index of the card set.
//!
struct CardInfo
{
    //! Sets that the card as revealed.
    //! \param _cardID The card ID to set.
    void SetAsRevealedCard(std::string _cardID);

    //! Sets that the card as hidden.
    //! \param setID The ID of the card set.
    //! \param cardIdx The card index of the card set.
    void SetAsHiddenCard(size_t setID, size_t cardIdx);

    //! Returns the card ID considering whether it is valid.
    //! \param unknownCardsManager The manager of unknown cards.
    //! \return the card ID considering whether it is valid.
    std::string GetCardID(
        const UnknownCardsSetsManager& unknownCardsManager) const;

    std::string cardID;
    std::size_t unknownCardsSetID = 0;
    std::size_t unknownCardsSetCardIdx = 0;
};
}  // namespace RosettaStone::PlayMode::Views::Types

#endif  // ROSETTASTONE_PLAYMODE_VIEWS_TYPES_CARD_INFO_HPP
