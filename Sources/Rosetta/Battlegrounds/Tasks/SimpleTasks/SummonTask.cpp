// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
SummonTask::SummonTask(const std::string_view& cardID, int amount,
                       SummonSide side)
    : m_card(Cards::FindCardByID(cardID)), m_side(side), m_amount(amount)
{
    // Do nothing
}

TaskStatus SummonTask::Impl(Player& player)
{
    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
