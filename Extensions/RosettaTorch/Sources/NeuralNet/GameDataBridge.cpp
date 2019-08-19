// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/GameDataBridge.hpp>

#include <Rosetta/Actions/ActionValidGetter.hpp>

namespace RosettaTorch::NeuralNet
{
void GameDataBridge::Reset(const RosettaStone::Game& game)
{
    m_game = &game;

    const RosettaStone::ActionValidGetter getter(*m_game);

    m_playableCards.clear();
    getter.ForEachPlayableCard([this](RosettaStone::Entity* card) {
        m_playableCards.push_back(card);
        return true;
    });

    m_canUseHeroPower = getter.CanUseHeroPower();
}

double GameDataBridge::GetField(FieldSide fieldSide, FieldType fieldType,
                                int arg) const
{
    if (fieldSide == FieldSide::CURRENT)
    {
        return GetSideField(fieldType, arg, m_game->GetCurrentPlayer());
    }

    if (fieldSide == FieldSide::OPPONENT)
    {
        return GetSideField(fieldType, arg, m_game->GetOpponentPlayer());
    }

    throw std::runtime_error("Invalid field side");
}

double GameDataBridge::GetSideField(FieldType fieldType, int arg,
                                    const RosettaStone::Player& player) const
{
    switch (fieldType)
    {
        case FieldType::MANA_CRYSTAL_CURRENT:
            return player.GetRemainingMana();
        case FieldType::MANA_CRYSTAL_TOTAL:
            return player.GetTotalMana();
        case FieldType::MANA_CRYSTAL_OVERLOAD_OWED:
            return player.GetOverloadOwed();
        case FieldType::MANA_CRYSTAL_OVERLOAD_LOCKED:
            return player.GetOverloadLocked();
        case FieldType::HERO_HEALTH:
            return player.GetHero()->GetHealth();
        case FieldType::HERO_ARMOR:
            return player.GetHero()->GetArmor();
        case FieldType::MINION_COUNT:
            return player.GetFieldZone().GetCount();
        case FieldType::MINION_HEALTH:
            return player.GetFieldZone()[arg]->GetHealth();
        case FieldType::MINION_MAX_HEALTH:
            return player.GetFieldZone()[arg]->GetMaxHealth();
        case FieldType::MINION_ATTACK:
            return player.GetFieldZone()[arg]->GetAttack();
        case FieldType::MINION_ATTACKABLE:
            return player.GetFieldZone()[arg]->CanAttack();
        case FieldType::MINION_TAUNT:
            return player.GetFieldZone()[arg]->GetGameTag(
                RosettaStone::GameTag::TAUNT);
        case FieldType::MINION_DIVINE_SHIELD:
            return player.GetFieldZone()[arg]->GetGameTag(
                RosettaStone::GameTag::DIVINE_SHIELD);
        case FieldType::MINION_STEALTH:
            return player.GetFieldZone()[arg]->GetGameTag(
                RosettaStone::GameTag::STEALTH);
        case FieldType::HAND_COUNT:
            return player.GetHandZone().GetCount();
        case FieldType::HAND_PLAYABLE:
            return (std::find(m_playableCards.begin(), m_playableCards.end(),
                              player.GetHandZone()[arg]) !=
                    m_playableCards.end());
        case FieldType::HAND_COST:
            return player.GetHandZone()[arg]->GetCost();
        case FieldType::HERO_POWER_PLAYABLE:
            return m_canUseHeroPower;
        default:
            throw std::runtime_error("Unknown field type");
    }
}
}  // namespace RosettaTorch::NeuralNet