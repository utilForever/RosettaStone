// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_QUEST_LOADER_HPP
#define ROSETTASTONE_QUEST_LOADER_HPP

#include <Rosetta/Cards/Card.hpp>

#include <string_view>

namespace RosettaStone
{
//!
//! \brief QuestLoader class.
//!
//! This class finds quest related data such as GameTag::QUEST_PROGRESS_TOTAL.
//!
class QuestLoader
{
 public:
    //! Gets the value of GameTag::QUEST_PROGRESS_TOTAL.
    //! \param cardID The card ID to find the value.
    //! \return The value of GameTag::QUEST_PROGRESS_TOTAL.
    static int GetQuestProgressTotal(const std::string_view& cardID);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_QUEST_LOADER_HPP
