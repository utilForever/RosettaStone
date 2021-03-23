// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSOLE_HPP
#define ROSETTASTONE_CONSOLE_HPP

#include <Rosetta/PlayMode/Agents/IAgent.hpp>
#include <Rosetta/PlayMode/Decks/Deck.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

#include <memory>

namespace RosettaStone
{
class Console
{
 public:
    enum class Mode
    {
        STANDARD,
        WILD,
        BATTLEGROUNDS,
    };

    //! Constructs a Console instance with \p mode.
    //! \param mode The game mode such as standard, wild and battlegrounds.
    explicit Console(Mode mode);

    //! Process a Hearthstone game.
    void ProcessGame();

 private:
    //! Inputs two deck codes to play Standard or Wild mode.
    void InputDeckCodes();

    //! Plays a Standard or Wild mode.
    //! \param deck1 The deck of player 1.
    //! \param deck2 The deck of player 2.
    void PlayStandardOrWild(PlayMode::Deck&& deck1, PlayMode::Deck&& deck2);

    //! Plays a Battlegrounds mode.
    void PlayBattlegrounds();

    //! Processes a mulligan.
    //! \param game The game context.
    void ProcessMulligan(PlayMode::Game& game);

    //! Processes a mulligan for human.
    //! \param game The game context.
    void ProcessMulliganForHuman(PlayMode::Game& game);

    //! Processes a mulligan for computer.
    //! \param game The game context.
    void ProcessMulliganForComputer(PlayMode::Game& game);

    //! Shows simple card information.
    //! \param playable A playable to show card information.
    void ShowSimpleCardInfo(PlayMode::Playable* playable);

    Mode m_mode;

    std::unique_ptr<PlayMode::IAgent> m_computerAgent;
};
}  // namespace RosettaStone

#endif