// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_ACTION_VALID_CHECKER_HPP
#define ROSETTASTONE_PLAYMODE_ACTION_VALID_CHECKER_HPP

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionTargets.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief ActionValidChecker class.
//!
//! This class contains some data such as operation map, attackers,
//! playable cards and targets. Also, it contains several getters.
//!
class ActionValidChecker
{
 public:
    //! Resets operation map.
    void Reset();

    //! Checks game data and adds the valid action.
    //! \param game The game context.
    void Check(const Game& game);

    //! Checks game data and adds the valid action.
    //! \param getter The action valid getter.
    void Check(ActionValidGetter& getter);

    //! Checks game data and adds the valid action.
    //! \param getter The action valid getter.
    void Check(ActionValidGetter&& getter);

    //! Returns the available main actions.
    //! \return The available main actions.
    const std::array<MainOpType, 4>& GetMainActions() const;

    //! Returns the number of available main actions.
    //! \return The number of available main actions.
    int GetMainActionsCount() const;

    //! Returns a list of cards that is playable.
    //! \return A list of cards that is playable.
    const std::vector<Playable*>& GetPlayableCards() const;

    //! Returns a list of attackers that can attack.
    //! \return A list of attackers that can attack.
    const std::vector<Character*>& GetAttackers() const;

    //! Returns the main operation type.
    //! \param choice An index of operation map.
    //! \return The main operation type.
    MainOpType GetMainOpType(std::size_t choice) const;

    //! Runs \p functor on each main operation.
    //! \param functor A function to run for each main operation.
    template <class Functor>
    void ForEachMainOp(Functor&& functor) const
    {
        for (std::size_t i = 0; i < m_opMapSize; ++i)
        {
            const auto idx = static_cast<std::size_t>(m_opMap[i]);

            if (!functor(i, GetMainOpType(idx)))
            {
                return;
            }
        }
    }

 private:
    std::array<MainOpType, 4> m_opMap = {};
    std::size_t m_opMapSize = 0;

    std::vector<Character*> m_attackers;
    std::vector<Playable*> m_playableCards;
    ActionTargets m_actionTargets;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACTION_VALID_CHECKER_HPP
