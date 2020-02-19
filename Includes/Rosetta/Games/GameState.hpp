// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_GAME_STATE_HPP
#define ROSETTASTONE_GAME_STATE_HPP

#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
//!
//! \brief GameState class.
//!
//! This class stores data related the game.
//!
class GameState
{
 public:
    struct GameStateInfo
    {
        std::string cardID;
        std::map<GameTag, int> gameTags;
    };

    struct PlayerInfo
    {
        std::map<GameTag, int> gameTags;

        GameStateInfo hero;
        GameStateInfo heroPower;
        std::vector<GameStateInfo> deck;
        std::vector<GameStateInfo> hand;
    };

    //! Gets the information of player.
    //! \param type The player type.
    //! \return The information of player.
    PlayerInfo& GetPlayerInfo(PlayerType type);

    //! Sets the player controlling the current turn.
    //! \param type The player type controlling the current turn.
    void SetCurrentPlayer(PlayerType type);

    //! Gets the player controlling the current turn.
    //! \return The player type controlling the current turn.
    PlayerType GetCurrentPlayer() const;

    //! Swaps the player for the next turn.
    void SwapCurrentPlayer();

    //! Gets the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Sets the turn of the game.
    //! \param turn The turn of the game.
    void SetTurn(int turn);

    //! Increases the turn of the game.
    void IncreaseTurn();

 private:
    std::array<PlayerInfo, 2> m_playerInfo;

    PlayerType m_currentPlayer = PlayerType::INVALID;

    std::size_t m_turn = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_STATE_HPP
