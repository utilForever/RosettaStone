// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>
#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

namespace RosettaStone::PlayMode
{
ActionValidGetter::ActionValidGetter(const Game& game) : m_game(game)
{
    // Do nothing
}

Hero* ActionValidGetter::GetHero(PlayerType playerType) const
{
    const auto hero = (playerType == PlayerType::PLAYER1)
                          ? m_game.GetPlayer1()->GetHero()
                          : m_game.GetPlayer2()->GetHero();

    return hero;
}

bool ActionValidGetter::CanUseHeroPower()
{
    auto& heroPower = m_game.GetCurrentPlayer()->GetHeroPower();

    if (!heroPower.IsPlayable())
    {
        return false;
    }

    if (heroPower.IsExhausted())
    {
        return false;
    }

    return true;
}

bool ActionValidGetter::IsPlayable([[maybe_unused]] const Player* player,
                                   Playable* entity) const
{
    if (entity->card->GetCardType() == CardType::MINION)
    {
        if (m_game.GetCurrentPlayer()->GetFieldZone()->IsFull())
        {
            return false;
        }
    }

    if (entity->card->HasGameTag(GameTag::SECRET))
    {
        if (m_game.GetCurrentPlayer()->GetSecretZone()->Exist(entity))
        {
            return false;
        }
    }

    if (!entity->IsPlayable())
    {
        return false;
    }

    if (auto playReqs = entity->card->playRequirements;
        (playReqs.find(PlayReq::REQ_TARGET_TO_PLAY) != playReqs.end()) &&
        entity->GetValidPlayTargets().empty())
    {
        return false;
    }

    return true;
}
}  // namespace RosettaStone::PlayMode