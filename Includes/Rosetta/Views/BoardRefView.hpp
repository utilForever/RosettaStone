// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_BOARD_REF_VIEW_HPP
#define ROSETTASTONE_BOARD_REF_VIEW_HPP

#include <Rosetta/Games/Game.hpp>

namespace RosettaStone
{
//!
//! \brief BoardRefView class.
//!
class BoardRefView
{
 public:
    BoardRefView(Game& game, PlayerType type);

    PlayerType GetType() const;
    int GetTurn() const;
    Player& GetCurrentPlayer() const;

    int GetFatigueDamage(PlayerType type) const;
    int GetTotalMana(PlayerType type) const;
    int GetUsedMana(PlayerType type) const;
    int GetTemporaryMana(PlayerType type) const;
    int GetOverloadOwed(PlayerType type) const;
    int GetOverloadLocked(PlayerType type) const;
    int GetRemainingMana(PlayerType type) const;

    Hero* GetHero() const;
    Hero* GetOpponentHero() const;
    HeroPower* GetHeroPower(PlayerType type) const;
    Weapon* GetWeapon(PlayerType type) const;

    std::vector<Entity*> GetHandCards() const;
    std::vector<Entity*> GetOpponentHandCards() const;
    int GetOpponentHandCardCount() const;

    std::vector<Minion*> GetMinions(PlayerType type) const;

    int GetDeckCardCount(PlayerType type) const;

    bool IsHeroAttackable(PlayerType type) const;
    bool IsMinionAttackable(PlayerType type, int idx) const;

 private:
    Game& m_game;
    PlayerType m_type;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_REF_VIEW_HPP
