// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_VALID_GETTER_HPP
#define ROSETTASTONE_ACTION_VALID_GETTER_HPP

#include <Rosetta/Games/Game.hpp>

#include <functional>

namespace RosettaStone
{
//!
//! \brief ActionValidGetter class.
//!
//! This class contains several methods that checks target is valid,
//! card is playable, hero/minion can attack and player can use hero power.
//!
class ActionValidGetter
{
 public:
    //! Constructs action valid getter with given \p game.
    //! \param game The game context.
    explicit ActionValidGetter(const Game& game);

    //! Returns the hero of the player.
    //! \param playerType The player type to separate players.
    //! \return The hero of the player.
    Hero* GetHero(PlayerType playerType) const;

    //! Runs \p functor on each minion of the player.
    //! \param playerType The player type to separate players.
    //! \param functor A function to run for each minion.
    void ForEachMinion(PlayerType playerType,
                       const std::function<void(Minion*)>& functor) const;

    //! Checks a card is playable and runs \p functor on each playable card.
    //! \param functor A function to run for each playable card.
    void ForEachPlayableCard(const std::function<bool(Entity*)>& functor) const;

    //! Checks a character can attack and runs \p functor on each attacker.
    //! \param functor A function to run for each attacker.
    void ForEachAttacker(const std::function<bool(Character*)>& functor) const;

    //! Returns the flag indicates whether the player can use hero power.
    //! \return the flag indicates whether the player can use hero power.
    bool CanUseHeroPower() const;

 private:
    //! Returns the flag indicates whether the card is playable.
    //! \return the flag indicates whether the card is playable.
    bool IsPlayable(Entity* entity) const;

    const Game& m_game;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_VALID_CHECKER_HPP
