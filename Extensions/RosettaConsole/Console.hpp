// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSOLE_HPP
#define ROSETTASTONE_CONSOLE_HPP

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

    //! Plays a Battlegrounds mode.
    void PlayBattlegrounds();

    Mode m_mode;
};
}  // namespace RosettaStone

#endif