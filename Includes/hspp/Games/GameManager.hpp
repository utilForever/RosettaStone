// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_MANAGER_HPP
#define HEARTHSTONEPP_GAME_MANAGER_HPP

namespace Hearthstonepp
{
class Game;

//!
//! \brief GameManager class.
//!
//! This class monitors game and invokes method when a state is changed.
//!
class GameManager
{
 public:
    //! Constructs game manager with given \p game.
    //! \param game A pointer to game that is monitored.
    GameManager(Game* game);

    //! Invokes method when a state is changed.
    void ProcessNextStep();

 private:
    Game* m_game = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_MANAGER_HPP