// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_BOARD_REF_VIEW_HPP
#define ROSETTASTONE_BOARD_REF_VIEW_HPP

#include <Rosetta/Actions/ActionValidGetter.hpp>
#include <Rosetta/Games/Game.hpp>

namespace RosettaStone
{
//!
//! \brief BoardRefView class.
//!
//! This class considers when a particular player looks at a game
//! from his or her point of view.
//!
class BoardRefView
{
 public:
    //! Constructs board with given \p game and \p playerType.
    //! \param game The game context.
    //! \param playerType The player type of the board.
    BoardRefView(const Game& game, PlayerType playerType);

    //! Returns the current turn of the game.
    //! \return The current turn of the game.
    int GetTurn() const;

    //! Returns the player type of the view.
    //! \return the player type of the view.
    PlayerType GetPlayerType() const;

    //! Returns the current player of the game.
    //! \return The current player of the game.
    Player& GetCurrentPlayer() const;

    //! Returns the fatigue damage of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The fatigue damage of the player in the game.
    int GetFatigueDamage(PlayerType playerType) const;

    //! Returns the total mana of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The total mana of the player in the game.
    int GetTotalMana(PlayerType playerType) const;

    //! Returns the used mana of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The used mana of the player in the game.
    int GetUsedMana(PlayerType playerType) const;

    //! Returns the temporary mana of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The temporary mana of the player in the game.
    int GetTemporaryMana(PlayerType playerType) const;

    //! Returns the mana that is overload owed of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The mana that is overload owed of the player in the game.
    int GetOverloadOwed(PlayerType playerType) const;

    //! Returns the mana that is overload locked of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The mana that is overload locked of the player in the game.
    int GetOverloadLocked(PlayerType playerType) const;

    //! Returns the remaining mana of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The remaining mana of the player in the game.
    int GetRemainingMana(PlayerType playerType) const;

    //! Returns the hero of the current player.
    //! \return The hero of the current player.
    Hero* GetHero() const;

    //! Returns the hero of the opponent player.
    //! \return The hero of the opponent player.
    Hero* GetOpponentHero() const;

    //! Returns the remaining mana of the player in the game.
    //! \param playerType The player type to separate players.
    //! \return The remaining mana of the player in the game.
    HeroPower* GetHeroPower(PlayerType playerType) const;

    Weapon* GetWeapon(PlayerType playerType) const;

    std::vector<Entity*> GetHandCards() const;

    std::vector<std::pair<Entity*, bool>> GetOpponentHandCards() const;

    int GetOpponentHandCardCount() const;

    std::vector<Minion*> GetMinions(PlayerType playerType) const;

    int GetDeckCardCount(PlayerType playerType) const;

    bool IsHeroAttackable(PlayerType playerType) const;

    bool IsMinionAttackable(PlayerType playerType, int idx) const;

 private:
    const Game& m_game;
    PlayerType m_playerType;
};

//!
//! \brief CurrentPlayerBoardRefView class.
//!
class CurrentPlayerBoardRefView
{
 public:
    explicit CurrentPlayerBoardRefView(const Game& game);

    Player& GetCurrentPlayer() const;

    ActionValidGetter GetActionValidGetter() const;

 private:
    const Game& m_game;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_REF_VIEW_HPP
