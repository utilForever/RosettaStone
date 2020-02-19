// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_GAME_RESTORER_HPP
#define ROSETTASTONE_GAME_RESTORER_HPP

#include <Rosetta/Views/BoardView.hpp>

#include <memory>

namespace RosettaStone
{
//!
//! \brief GameRestorer class.
//!
//! This class prepares the game state from board view and restores the game.
//!
class GameRestorer
{
 public:
    //! Constructs game restorer with given \p view.
    //! \param view The board view to prepare the game state.
    explicit GameRestorer(const BoardView& view);

    //! Prepares the game restorer by setting unknown cards info.
    //! \param view The board view to prepare the game restorer.
    //! \param p1Unknown The information of unknown cards of player 1.
    //! \param p2Unknown The information of unknown cards of player 2.
    //! \return The game restorer that is newly created.
    static GameRestorer Prepare(BoardView& view,
                                Views::Types::UnknownCardsInfo& p1Unknown,
                                Views::Types::UnknownCardsInfo& p2Unknown);

    //! Restore the game state from the board view.
    //! \return The restored game state.
    GameState RestoreGameState();

 private:
    //! Makes the player data to restore the game.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param viewPlayer The player type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakePlayer(
        PlayerType playerType, GameState& gameState,
        const Views::Types::Player& viewPlayer,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the hero and hero power data to restore the game.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param hero The hero type of the view.
    //! \param heroPower The hero power type of the view.
    void MakeHeroAndHeroPower(PlayerType playerType, GameState& gameState,
                              const Views::Types::Hero& hero,
                              const Views::Types::HeroPower& heroPower);

    //! Makes the deck data to restore the game.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param cards The deck type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakeDeck(
        PlayerType playerType, GameState& gameState,
        std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the hand data to restore the game.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param cards The hand type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakeHand(
        PlayerType playerType, GameState& gameState,
        std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the minions data to restore the game.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param minions The minions type of the view.
    void MakeMinions(PlayerType playerType, GameState& gameState,
                     const Views::Types::Minions& minions);

    //! Makes the mana crystal data to restore the game.
    //! \param player The player context.
    //! \param manaCrystal The mana crystal type of the view.
    void MakeManaCrystal(Player* player,
                         const Views::Types::ManaCrystal& manaCrystal);

    //! Adds minion to minions data.
    //! \param playerType The type of the player.
    //! \param gameState The game state.
    //! \param minion The minion type of the view.
    //! \param pos The position of the minion.
    void AddMinion(PlayerType playerType, GameState& gameState,
                   const Views::Types::Minion& minion, int pos);

    const BoardView& m_view;

    Views::Types::UnknownCardsInfo p1UnknownCardsInfo;
    Views::Types::UnknownCardsInfo p2UnknownCardsInfo;

    Views::Types::UnknownCardsSetsManager p1UnknownCardsManager;
    Views::Types::UnknownCardsSetsManager p2UnknownCardsManager;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_RESTORER_HPP
