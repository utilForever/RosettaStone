// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP
#define ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Commons/JSONSerializer.hpp>
#include <Rosetta/Enums/ActionEnums.hpp>
#include <Rosetta/Games/Game.hpp>

#include <json/json.hpp>

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
    void Start()
    {
        m_json.clear();
    }

    //! Returns the JSON object that contains the game data.
    //! \return The JSON object that contains the game data.
    const nlohmann::json& GetJSON() const
    {
        return m_json;
    }

    //! Records the main action data to JSON object.
    //! \param game The game context.
    //! \param op The main operation type.
    void RecordMainAction(Game& game, MainOpType op)
    {
        nlohmann::json obj;

        obj["type"] = "MAIN_ACTION";
        obj["game"] = JSONSerializer::Serialize(game);
        obj["choice"] = GetMainOpString(op);

        m_json.emplace_back(obj);
    }

    //! Records the randomly selected action to JSON object.
    //! \param maxValue The number of available actions.
    //! \param action The index of available actions selected randomly.
    void RecordRandomAction(int maxValue, int action)
    {
        nlohmann::json obj;

        obj["type"] = "RANDOM";
        obj["max_value"] = maxValue;
        obj["choice"] = action;

        m_json.emplace_back(obj);
    }

    //! Records the manually selected action to JSON object.
    //! \param actionType The selected action type.
    //! \param choices The type of action choices.
    //! \param action The index of available choices selected manually.
    void RecordManualAction(ActionType actionType, ActionChoices choices,
                            int action)
    {
        nlohmann::json obj;

        obj["type"] = GetActionTypeString(actionType);
        obj["choices_type"] = GetChoiceTypeString(choices);

        nlohmann::json choicesObj;
        for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
        {
            nlohmann::json choice;
            choice = choices.Get();
            choicesObj.emplace_back(choice);
        }

        obj["choices"] = choicesObj;
        obj["choice"] = action;

        m_json.emplace_back(obj);
    }

    //! Records the game end data to JSON object.
    //! \param playerType The type of player to get the game result.
    //! \param result The result of game to record.
    void End(PlayerType playerType, PlayState result)
    {
        nlohmann::json obj;

        obj["type"] = "END";
        obj["result"] = GetResultString(playerType, result);

        m_json.emplace_back(obj);
    }

 private:
    //! Converts the action type to string.
    //! \param type The action type to convert.
    //! \return The converted string of the action type.
    std::string GetActionTypeString(ActionType type)
    {
        using RosettaStone::ActionType;

        switch (type)
        {
            case ActionType::MAIN_ACTION:
                return "MAIN_ACTION";
            case ActionType::CHOOSE_HAND_CARD:
                return "CHOOSE_HAND_CARD";
            case ActionType::CHOOSE_ATTACKER:
                return "CHOOSE_ATTACKER";
            case ActionType::CHOOSE_MINION_PUT_LOCATION:
                return "CHOOSE_MINION_PUT_LOCATION";
            case ActionType::CHOOSE_TARGET:
                return "CHOOSE_TARGET";
            case ActionType::CHOOSE_ONE:
                return "CHOOSE_ONE";
            case ActionType::RANDOM:
                return "RANDOM";
            case ActionType::INVALID:
                return "INVALID";
            default:
                return "UNKNOWN";
        }
    }

    //! Converts the choice type to string.
    //! \param choices The choice type to convert.
    //! \return The converted string of the choice type.
    std::string GetChoiceTypeString(const ActionChoices& choices)
    {
        if (choices.CheckType<ChooseFromNumbers>())
        {
            return "CHOOSE_FROM_NUMBERS";
        }

        if (choices.CheckType<ChooseFromCardIDs>())
        {
            return "CHOOSE_FROM_CARD_IDS";
        }

        return "INVALID";
    }

    //! Converts the game result to string.
    //! \param playerType The type of player.
    //! \param result The result of the game.
    //! \return The converted string of the game result.
    std::string GetResultString(PlayerType playerType, PlayState result)
    {
        switch (result)
        {
            case PlayState::TIED:
                return "DRAW";
            case PlayState::WON:
                if (playerType == PlayerType::PLAYER1)
                {
                    return "PLAYER1_WIN";
                }
                else
                {
                    return "PLAYER2_WIN";
                }
            case PlayState::LOST:
                if (playerType == PlayerType::PLAYER1)
                {
                    return "PLAYER2_WIN";
                }
                else
                {
                    return "PLAYER1_WIN";
                }
            default:
                return "INVALID";
        }
    }

    nlohmann::json m_json;
};
}  // namespace RosettaTorch::Judges::JSON

#endif  // ROSETTASTONE_TORCH_JUDGES_RECORDER_HPP