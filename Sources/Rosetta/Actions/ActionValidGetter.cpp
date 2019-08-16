// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Actions/ActionValidGetter.hpp>
#include <Rosetta/Actions/PlayCard.hpp>
#include "Rosetta/Actions/Targeting.hpp"

namespace RosettaStone
{
ActionValidGetter::ActionValidGetter(const Game& game) : m_game(game)
{
    // Do nothing
}

Hero* ActionValidGetter::GetHero(PlayerType playerType) const
{
    const auto hero = (playerType == PlayerType::PLAYER1)
                          ? m_game.GetPlayer1().GetHero()
                          : m_game.GetPlayer2().GetHero();

    return hero;
}

bool ActionValidGetter::CanUseHeroPower() const
{
    auto& heroPower = m_game.GetCurrentPlayer().GetHero()->heroPower;

    if (!Generic::IsPlayableByPlayer(m_game.GetCurrentPlayer(), heroPower) ||
        !Generic::IsPlayableByCardReq(heroPower))
    {
        return false;
    }

    if (heroPower->IsExhausted())
    {
        return false;
    }

    return true;
}

bool ActionValidGetter::IsPlayable(Entity* entity) const
{
    if (entity->card->GetCardType() == CardType::MINION)
    {
        if (m_game.GetCurrentPlayer().GetFieldZone().IsFull())
        {
            return false;
        }
    }

    if (entity->card->HasGameTag(GameTag::SECRET))
    {
        if (m_game.GetCurrentPlayer().GetSecretZone().Exist(*entity))
        {
            return false;
        }
    }

    if (!Generic::IsPlayableByPlayer(m_game.GetCurrentPlayer(), entity) ||
        !Generic::IsPlayableByCardReq(entity))
    {
        return false;
    }

    return true;
}
}  // namespace RosettaStone