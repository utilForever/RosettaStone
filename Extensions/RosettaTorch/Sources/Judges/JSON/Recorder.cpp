// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Judges/JSON/Recorder.hpp>

#include <json/json.hpp>

namespace RosettaTorch::Judges::JSON
{
void Recorder::Start()
{
    m_json.clear();
}

const nlohmann::json& Recorder::GetJSON() const
{
    return m_json;
}

void Recorder::RecordMainAction(RosettaStone::Game& game,
                                RosettaStone::MainOpType op)
{
    nlohmann::json obj;

    obj["type"] = "MAIN_ACTION";
    obj["game"] = RosettaStone::JSONSerializer::Serialize(game);
    obj["choice"] = GetMainOpString(op);

    m_json.emplace_back(obj);
}

void Recorder::RecordRandomAction(int maxValue, int action)
{
    nlohmann::json obj;

    obj["type"] = "RANDOM";
    obj["max_value"] = maxValue;
    obj["choice"] = action;

    m_json.emplace_back(obj);
}

void Recorder::RecordManualAction(RosettaStone::ActionType actionType,
                                  RosettaStone::ActionChoices choices,
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

void Recorder::End(RosettaStone::PlayerType playerType,
                   RosettaStone::PlayState result)
{
    nlohmann::json obj;

    obj["type"] = "END";
    obj["result"] = GetResultString(playerType, result);

    m_json.emplace_back(obj);
}

std::string Recorder::GetActionTypeString(RosettaStone::ActionType type)
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

std::string Recorder::GetChoiceTypeString(
    const RosettaStone::ActionChoices& choices)
{
    if (choices.CheckType<RosettaStone::ChooseFromNumbers>())
    {
        return "CHOOSE_FROM_NUMBERS";
    }

    if (choices.CheckType<RosettaStone::ChooseFromCardIDs>())
    {
        return "CHOOSE_FROM_CARD_IDS";
    }

    return "INVALID";
}

std::string Recorder::GetResultString(RosettaStone::PlayerType playerType,
                                      RosettaStone::PlayState result)
{
    switch (result)
    {
        case RosettaStone::PlayState::TIED:
            return "DRAW";
        case RosettaStone::PlayState::WON:
            if (playerType == RosettaStone::PlayerType::PLAYER1)
            {
                return "PLAYER1_WIN";
            }
            else
            {
                return "PLAYER2_WIN";
            }
        case RosettaStone::PlayState::LOST:
            if (playerType == RosettaStone::PlayerType::PLAYER1)
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
}  // namespace RosettaTorch::Judges::JSON