// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Managers/TriggerManager.hpp>

namespace RosettaStone::Battlegrounds
{
void TriggerManager::OnDeathTrigger(Minion& sender)
{
    deathTrigger(sender);
}
}  // namespace RosettaStone::Battlegrounds
