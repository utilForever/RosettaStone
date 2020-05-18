// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_MANAGER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_MANAGER_HPP

#include <Rosetta/Battlegrounds/Games/Game.hpp>

namespace RosettaStone::Battlegrounds
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
    //! \param game The game context.
    //! \param phase The next phase.
    static void ProcessNextPhase(Game& game, Phase phase);
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_MANAGER_HPP
