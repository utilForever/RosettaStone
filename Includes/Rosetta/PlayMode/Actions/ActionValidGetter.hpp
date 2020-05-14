// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_ACTION_VALID_GETTER_HPP
#define ROSETTASTONE_PLAYMODE_ACTION_VALID_GETTER_HPP

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode
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
    template <typename Functor>
    void ForEachMinion(PlayerType playerType, Functor&& functor) const
    {
        auto fieldZone = (playerType == PlayerType::PLAYER1)
                             ? m_game.GetPlayer1()->GetFieldZone()
                             : m_game.GetPlayer2()->GetFieldZone();

        for (auto& minion : fieldZone->GetAll())
        {
            functor(minion);
        }
    }

    //! Checks a card is playable and runs \p functor on each playable card.
    //! \param functor A function to run for each playable card.
    template <typename Functor>
    void ForEachPlayableCard(Functor&& functor) const
    {
        auto handZone = m_game.GetCurrentPlayer()->GetHandZone();

        for (auto& card : handZone->GetAll())
        {
            if (!IsPlayable(m_game.GetCurrentPlayer(), card))
            {
                continue;
            }

            if (!functor(card))
            {
                return;
            }
        }
    }

    //! Checks a character can attack and runs \p functor on each attacker.
    //! \param functor A function to run for each attacker.
    template <typename Functor>
    void ForEachAttacker(Functor&& functor) const
    {
        auto fieldZone = m_game.GetCurrentPlayer()->GetFieldZone();

        for (auto& minion : fieldZone->GetAll())
        {
            if (!minion->CanAttack())
            {
                continue;
            }

            if (!functor(minion))
            {
                return;
            }
        }

        const auto& hero = m_game.GetCurrentPlayer()->GetHero();
        if (hero->CanAttack())
        {
            if (!functor(hero))
            {
                return;
            }
        }
    }

    //! Returns the flag indicates whether the player can use hero power.
    //! \return the flag indicates whether the player can use hero power.
    bool CanUseHeroPower();

 private:
    //! Returns the flag indicates whether the card is playable.
    //! \param player The player context.
    //! \param entity The target entity.
    //! \return the flag indicates whether the card is playable.
    bool IsPlayable(const Player* player, Playable* entity) const;

    const Game& m_game;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACTION_VALID_GETTER_HPP
