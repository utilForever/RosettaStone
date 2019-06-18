// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Views/BoardRefView.hpp>

namespace RosettaStone
{
BoardRefView::BoardRefView(Game& game, PlayerType type)
    : m_game(game), m_type(type)
{
    // Do nothing
}

PlayerType BoardRefView::GetType() const
{
    return m_type;
}

int BoardRefView::GetTurn() const
{
    return m_game.GetTurn();
}

Player& BoardRefView::GetCurrentPlayer() const
{
    return m_game.GetCurrentPlayer();
}

int BoardRefView::GetFatigueDamage(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetHero()->fatigue;
    }
    else
    {
        return m_game.GetPlayer2().GetHero()->fatigue;
    }
}

int BoardRefView::GetTotalMana(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetTotalMana();
    }
    else
    {
        return m_game.GetPlayer2().GetTotalMana();
    }
}

int BoardRefView::GetUsedMana(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetUsedMana();
    }
    else
    {
        return m_game.GetPlayer2().GetUsedMana();
    }
}

int BoardRefView::GetTemporaryMana(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetTemporaryMana();
    }
    else
    {
        return m_game.GetPlayer2().GetTemporaryMana();
    }
}

int BoardRefView::GetOverloadOwed(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetOverloadOwed();
    }
    else
    {
        return m_game.GetPlayer2().GetOverloadOwed();
    }
}

int BoardRefView::GetOverloadLocked(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetOverloadLocked();
    }
    else
    {
        return m_game.GetPlayer2().GetOverloadLocked();
    }
}

int BoardRefView::GetRemainingMana(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetRemainingMana();
    }
    else
    {
        return m_game.GetPlayer2().GetRemainingMana();
    }
}

Hero* BoardRefView::GetHero() const
{
    if (m_type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetHero();
    }
    else
    {
        return m_game.GetPlayer2().GetHero();
    }
}
Hero* BoardRefView::GetOpponentHero() const
{
    if (m_type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer2().GetHero();
    }
    else
    {
        return m_game.GetPlayer1().GetHero();
    }
}

std::vector<Entity*> BoardRefView::GetHandCards() const
{
    if (m_type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1().GetHandZone().GetAll();
    }
    else
    {
        return m_game.GetPlayer2().GetHandZone().GetAll();
    }
}

std::vector<Entity*> BoardRefView::GetOpponentHandCards() const
{
    std::vector<Entity*> result;

    if (m_type == PlayerType::PLAYER1)
    {
        result = m_game.GetPlayer2().GetHandZone().GetAll();
    }
    else
    {
        result = m_game.GetPlayer1().GetHandZone().GetAll();
    }

    for (auto& entity : result)
    {
        if (entity->card.id == "GAME_005")
        {
            // The Coin. This also reveals to opponent.
        }
        else
        {
            entity->card.id = "INVALID";
        }
    }

    return result;
}

int BoardRefView::GetOpponentHandCardCount() const
{
    if (m_type == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer2().GetHandZone().GetCount();
    }
    else
    {
        return m_game.GetPlayer1().GetHandZone().GetCount();
    }
}
}  // namespace RosettaStone