// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>

namespace RosettaStone::Battlegrounds
{
void Power::ClearData()
{
    m_battlecryTask.clear();
}

void Power::AddBattlecryTask(TaskType&& task)
{
    m_battlecryTask.emplace_back(task);
}
}  // namespace RosettaStone::Battlegrounds
