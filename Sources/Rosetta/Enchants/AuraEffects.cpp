// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/AuraEffects.hpp>

#include <stdexcept>

namespace RosettaStone
{
AuraEffects::AuraEffects(CardType type) : m_type(type)
{
    switch (type)
    {
        case CardType::HERO:
            m_data = new int[AURA_EFFECT_HERO_SIZE];
            break;
        case CardType::MINION:
            m_data = new int[AURA_EFFECT_MINION_SIZE];
            break;
        case CardType::WEAPON:
            m_data = new int[AURA_EFFECT_WEAPON_SIZE];
            break;
        case CardType::SPELL:
            m_data = new int[AURA_EFFECT_CARD_SIZE];
            break;
        default:
            throw std::invalid_argument(
                "AuraEffects::AuraEffects() - Invalid card type!");
    }
}

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
