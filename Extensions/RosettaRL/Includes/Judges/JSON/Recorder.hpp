// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP
#define ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Utils/JSONSerializer.hpp>

namespace RosettaTorch::Judges::JSON
{
//!
//! \brief Recorder class.
//!
//! This class is created to record the game data.
//!
class Recorder
{
 public:
    //! Starts recording by clearing JSON object.
    void Start();

    //! Returns the JSON object that contains the game data.
    //! \return The JSON object that contains the game data.
    const nlohmann::json& GetJSON() const;

    //! Records the main action data to JSON object.
    //! \param game The game context.
    //! \param op The main operation type.
    void RecordMainAction(RosettaStone::PlayMode::Game& game,
                          RosettaStone::MainOpType op);

    //! Records the randomly selected action to JSON object.
    //! \param maxValue The number of available actions.
    //! \param action The index of available actions selected randomly.
    void RecordRandomAction(int maxValue, int action);

    //! Records the manually selected action to JSON object.
    //! \param actionType The selected action type.
    //! \param choices The type of action choices.
    //! \param action The index of available choices selected manually.
    void RecordManualAction(RosettaStone::ActionType actionType,
                            RosettaStone::PlayMode::ActionChoices choices,
                            int action);

    //! Records the game end data to JSON object.
    //! \param result The result of the game (player1 and player2).
    void End(
        std::tuple<RosettaStone::PlayState, RosettaStone::PlayState> result);

 private:
    //! Converts the action type to string.
    //! \param type The action type to convert.
    //! \return The converted string of the action type.
    std::string GetActionTypeString(RosettaStone::ActionType type);

    //! Converts the choice type to string.
    //! \param choices The choice type to convert.
    //! \return The converted string of the choice type.
    std::string GetChoiceTypeString(
        const RosettaStone::PlayMode::ActionChoices& choices);

    //! Converts the game result to string.
    //! \param result The result of the game (player1 and player2).
    //! \return The converted string of the game result.
    std::string GetResultString(
        std::tuple<RosettaStone::PlayState, RosettaStone::PlayState> result)
        const;

    nlohmann::json m_json;
};
}  // namespace RosettaTorch::Judges::JSON

#endif  // ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP