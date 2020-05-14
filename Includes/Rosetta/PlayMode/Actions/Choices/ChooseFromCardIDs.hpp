// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_CHOOSE_FROM_CARD_IDS_HPP
#define ROSETTASTONE_PLAYMODE_CHOOSE_FROM_CARD_IDS_HPP

#include <cstddef>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief ChooseFromNumbers class.
//!
//! This class indicates the choice is choose from a list of card IDs.
//!
class ChooseFromCardIDs
{
 public:
    //! Constructs choose from card IDs with given \p cardIDs.
    //! \param cardIDs A list of card IDs.
    explicit ChooseFromCardIDs(const std::vector<std::size_t>& cardIDs);

    //! Returns the action choice at \p idx.
    //! \param idx The index of action choices.
    //! \return The action choice at \p idx.
    std::size_t Get(std::size_t idx) const;

    //! Returns the flag indicates that action choices are empty.
    //! \return The flag indicates that action choices are empty.
    bool IsEmpty() const;

    //! Returns the number of action choices.
    //! \return The number of action choices.
    std::size_t Size() const;

    //! Initializes iterator variable.
    void Begin();

    //! Returns the element that iterator variable points to.
    //! \return The element that iterator variable points to.
    std::size_t Get() const;

    //! Processes iterator to point to the next element.
    void StepNext();

    //! Returns the flag indicates that iterator is in the end position.
    //! \return the flag indicates that iterator is in the end position.
    bool IsEnd() const;

 private:
    std::vector<std::size_t> m_cardIDs;
    std::vector<std::size_t>::const_iterator m_iter;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CHOOSE_FROM_CARD_IDS_HPP
