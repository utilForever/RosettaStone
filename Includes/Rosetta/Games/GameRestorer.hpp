// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_GAME_RESTORER_HPP
#define ROSETTASTONE_GAME_RESTORER_HPP

#include <Rosetta/Views/BoardView.hpp>

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
    //! \param info The information of player.
    //! \param gameState The game state.
    //! \param viewPlayer The player type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakePlayer(
        GameState::PlayerInfo& info, GameState& gameState,
        const Views::Types::Player& viewPlayer,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the hero and hero power data to restore the game.
    //! \param info The information of player.
    //! \param hero The hero type of the view.
    //! \param heroPower The hero power type of the view.
    void MakeHeroAndHeroPower(GameState::PlayerInfo& info,
                              const Views::Types::Hero& hero,
                              const Views::Types::HeroPower& heroPower);

    //! Makes the deck data to restore the game.
    //! \param info The information of player.
    //! \param cards The deck type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakeDeck(
        GameState::PlayerInfo& info, std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the hand data to restore the game.
    //! \param info The information of player.
    //! \param cards The hand type of the view.
    //! \param unknownCardsSetsManager The manager of unknown cards sets.
    void MakeHand(
        GameState::PlayerInfo& info, std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    //! Makes the minions data to restore the game.
    //! \param info The information of player.
    //! \param minions The minions type of the view.
    void MakeMinions(GameState::PlayerInfo& info,
                     const Views::Types::Minions& minions);

    //! Makes the mana crystal data to restore the game.
    //! \param info The information of player.
    //! \param manaCrystal The mana crystal type of the view.
    void MakeManaCrystal(GameState::PlayerInfo& info,
                         const Views::Types::ManaCrystal& manaCrystal);

    //! Adds minion to minions data.
    //! \param info The information of player.
    //! \param minion The minion type of the view.
    void AddMinion(GameState::PlayerInfo& info,
                   const Views::Types::Minion& minion);

    const BoardView& m_view;

    Views::Types::UnknownCardsInfo p1UnknownCardsInfo;
    Views::Types::UnknownCardsInfo p2UnknownCardsInfo;

    Views::Types::UnknownCardsSetsManager p1UnknownCardsManager;
    Views::Types::UnknownCardsSetsManager p2UnknownCardsManager;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_RESTORER_HPP
