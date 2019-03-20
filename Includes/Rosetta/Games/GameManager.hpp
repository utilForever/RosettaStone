// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_MANAGER_HPP
#define HEARTHSTONEPP_GAME_MANAGER_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/Game.hpp>

namespace Hearthstonepp
{
//!
//! \brief GameManager class.
//!
//! This class monitors game and invokes method when a state is changed.
//!
class GameManager
{
 public:
    //! Invokes method when a state is changed.
    static void ProcessNextStep(Game& game, Step step);
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_MANAGER_HPP