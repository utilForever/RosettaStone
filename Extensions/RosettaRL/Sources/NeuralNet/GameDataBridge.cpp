// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/GameDataBridge.hpp>

#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>

namespace RosettaTorch::NeuralNet
{
void GameDataBridge::Reset(const RosettaStone::PlayMode::Game& game)
{
    m_game = &game;

    RosettaStone::PlayMode::ActionValidGetter getter(*m_game);

    m_playableCards.clear();
    getter.ForEachPlayableCard([this](RosettaStone::PlayMode::Entity* card) {
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

double GameDataBridge::GetSideField(
    FieldType fieldType, int arg,
    const RosettaStone::PlayMode::Player* player) const
{
    auto& handZone = *(player->GetHandZone());
    auto& fieldZone = *(player->GetFieldZone());

    switch (fieldType)
    {
        case FieldType::MANA_CRYSTAL_CURRENT:
            return player->GetRemainingMana();
        case FieldType::MANA_CRYSTAL_TOTAL:
            return player->GetTotalMana();
        case FieldType::MANA_CRYSTAL_OVERLOAD_OWED:
            return player->GetOverloadOwed();
        case FieldType::MANA_CRYSTAL_OVERLOAD_LOCKED:
            return player->GetOverloadLocked();
        case FieldType::HERO_HEALTH:
            return player->GetHero()->GetHealth();
        case FieldType::HERO_ARMOR:
            return player->GetHero()->GetArmor();
        case FieldType::MINION_COUNT:
            return fieldZone.GetCount();
        case FieldType::MINION_HEALTH:
            return fieldZone[arg]->GetHealth();
        case FieldType::MINION_MAX_HEALTH:
            return fieldZone[arg]->GetMaxHealth();
        case FieldType::MINION_ATTACK:
            return fieldZone[arg]->GetAttack();
        case FieldType::MINION_ATTACKABLE:
            return fieldZone[arg]->CanAttack();
        case FieldType::MINION_TAUNT:
            return fieldZone[arg]->GetGameTag(RosettaStone::GameTag::TAUNT);
        case FieldType::MINION_DIVINE_SHIELD:
            return fieldZone[arg]->GetGameTag(
                RosettaStone::GameTag::DIVINE_SHIELD);
        case FieldType::MINION_STEALTH:
            return fieldZone[arg]->GetGameTag(RosettaStone::GameTag::STEALTH);
        case FieldType::HAND_COUNT:
            return handZone.GetCount();
        case FieldType::HAND_PLAYABLE:
            return (std::find(m_playableCards.begin(), m_playableCards.end(),
                              handZone[arg]) != m_playableCards.end());
        case FieldType::HAND_COST:
            return handZone[arg]->GetCost();
        case FieldType::HERO_POWER_PLAYABLE:
            return m_canUseHeroPower;
        default:
            throw std::runtime_error("Unknown field type");
    }
}
}  // namespace RosettaTorch::NeuralNet