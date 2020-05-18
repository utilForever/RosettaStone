// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/BoardRefView.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode
{
BoardRefView::BoardRefView(Game& game, PlayerType playerType)
    : m_game(game), m_playerType(playerType)
{
    // Do nothing
}

PlayerType BoardRefView::GetSide() const
{
    return m_playerType;
}

int BoardRefView::GetTurn() const
{
    return m_game.GetTurn();
}

PlayerType BoardRefView::GetCurrentPlayer() const
{
    return m_game.GetCurrentPlayer()->playerType;
}

int BoardRefView::GetFatigueDamage(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetHero()->fatigue;
    }
    else
    {
        return m_game.GetPlayer2()->GetHero()->fatigue;
    }
}

int BoardRefView::GetTotalMana(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetTotalMana();
    }
    else
    {
        return m_game.GetPlayer2()->GetTotalMana();
    }
}

int BoardRefView::GetUsedMana(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetUsedMana();
    }
    else
    {
        return m_game.GetPlayer2()->GetUsedMana();
    }
}

int BoardRefView::GetTemporaryMana(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetTemporaryMana();
    }
    else
    {
        return m_game.GetPlayer2()->GetTemporaryMana();
    }
}

int BoardRefView::GetOverloadOwed(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetOverloadOwed();
    }
    else
    {
        return m_game.GetPlayer2()->GetOverloadOwed();
    }
}

int BoardRefView::GetOverloadLocked(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetOverloadLocked();
    }
    else
    {
        return m_game.GetPlayer2()->GetOverloadLocked();
    }
}

int BoardRefView::GetRemainingMana(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetRemainingMana();
    }
    else
    {
        return m_game.GetPlayer2()->GetRemainingMana();
    }
}

Hero* BoardRefView::GetHero() const
{
    if (m_playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetHero();
    }
    else
    {
        return m_game.GetPlayer2()->GetHero();
    }
}
Hero* BoardRefView::GetOpponentHero() const
{
    if (m_playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer2()->GetHero();
    }
    else
    {
        return m_game.GetPlayer1()->GetHero();
    }
}

HeroPower& BoardRefView::GetHeroPower(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetHeroPower();
    }
    else
    {
        return m_game.GetPlayer2()->GetHeroPower();
    }
}

Weapon* BoardRefView::GetWeapon(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return &m_game.GetPlayer1()->GetWeapon();
    }
    else
    {
        return &m_game.GetPlayer2()->GetWeapon();
    }
}

std::vector<Playable*> BoardRefView::GetHandCards() const
{
    if (m_playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetHandZone()->GetAll();
    }
    else
    {
        return m_game.GetPlayer2()->GetHandZone()->GetAll();
    }
}

std::vector<std::pair<Playable*, bool>> BoardRefView::GetOpponentHandCards()
    const
{
    std::vector<Playable*> playables;

    if (m_playerType == PlayerType::PLAYER1)
    {
        playables = m_game.GetPlayer2()->GetHandZone()->GetAll();
    }
    else
    {
        playables = m_game.GetPlayer1()->GetHandZone()->GetAll();
    }

    std::vector<std::pair<Playable*, bool>> result;

    for (auto& playable : playables)
    {
        if (playable->card->id == "GAME_005")
        {
            // The Coin. This also reveals to opponent.
            result.emplace_back(std::make_pair(playable, true));
        }
        else
        {
            result.emplace_back(std::make_pair(playable, false));
        }
    }

    return result;
}

int BoardRefView::GetOpponentHandCardCount() const
{
    if (m_playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer2()->GetHandZone()->GetCount();
    }
    else
    {
        return m_game.GetPlayer1()->GetHandZone()->GetCount();
    }
}

std::vector<Minion*> BoardRefView::GetMinions(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetFieldZone()->GetAll();
    }
    else
    {
        return m_game.GetPlayer2()->GetFieldZone()->GetAll();
    }
}

int BoardRefView::GetDeckCardCount(PlayerType playerType) const
{
    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetDeckZone()->GetCount();
    }
    else
    {
        return m_game.GetPlayer2()->GetDeckZone()->GetCount();
    }
}

bool BoardRefView::IsHeroAttackable(PlayerType playerType) const
{
    if (GetCurrentPlayer() != playerType)
    {
        return false;
    }

    if (playerType == PlayerType::PLAYER1)
    {
        return m_game.GetPlayer1()->GetHero()->CanAttack();
    }
    else
    {
        return m_game.GetPlayer2()->GetHero()->CanAttack();
    }
}

bool BoardRefView::IsMinionAttackable(PlayerType playerType, int idx) const
{
    if (GetCurrentPlayer() != playerType)
    {
        return false;
    }

    if (playerType == PlayerType::PLAYER1)
    {
        const auto fieldZone = m_game.GetPlayer1()->GetFieldZone();
        return (*fieldZone)[idx]->CanAttack();
    }
    else
    {
        const auto fieldZone = m_game.GetPlayer2()->GetFieldZone();
        return (*fieldZone)[idx]->CanAttack();
    }
}

CurrentPlayerBoardRefView::CurrentPlayerBoardRefView(Game& game) : m_game(game)
{
    // Do nothing
}

Player* CurrentPlayerBoardRefView::GetCurrentPlayer() const
{
    return m_game.GetCurrentPlayer();
}

ActionValidGetter CurrentPlayerBoardRefView::GetActionValidGetter() const
{
    return ActionValidGetter(m_game);
}
}  // namespace RosettaStone::PlayMode