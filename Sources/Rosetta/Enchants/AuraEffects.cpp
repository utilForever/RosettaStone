// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/AuraEffects.hpp>

namespace RosettaStone
{
int AuraEffects::GetGameTag(GameTag tag) const
{
    if (m_gameTags.find(tag) == m_gameTags.end())
    {
        return 0;
    }

    return m_gameTags.at(tag);
}

void AuraEffects::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}
}  // namespace RosettaStone
