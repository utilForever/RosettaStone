// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP
#define ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP

#include <Judges/IAgent.hpp>

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Enums/ActionEnums.hpp>
#include <Rosetta/Games/Game.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::Judges
{
class NullRecorder
{
 public:
    void Start()
    {
        // Do nothing
    }

    void RecordMainAction([[maybe_unused]] const Game& game,
                          [[maybe_unused]] MainOpType op)
    {
        // Do nothing
    }

    void RecordRandomAction([[maybe_unused]] int exclusiveMax,
                            [[maybe_unused]] int action)
    {
        // Do nothing
    }

    void RecordManualAction([[maybe_unused]] ActionType actionType,
                            [[maybe_unused]] ActionChoices actionChoices,
                            [[maybe_unused]] int action)
    {
        // Do nothing
    }

    void End([[maybe_unused]] PlayState result)
    {
        // Do nothing
    }
};

template <class AgentType = IAgent, class RecorderType = NullRecorder>
class Judger
{
 public:
    Judger(RecorderType& recorder)
        : m_actionCallback(*this),
          m_first(nullptr),
          m_second(nullptr),
          m_recorder(recorder)
    {
        // Do nothing
    }

    //! Deleted copy constructor.
    Judger(const Judger& rhs) = delete;

    //! Deleted move constructor.
    Judger(Judger&& rhs) noexcept = delete;

    //! Deleted copy assignment operator.
    Judger& operator=(const Judger& rhs) = delete;

    //! Deleted move assignment operator.
    Judger& operator=(Judger&& rhs) noexcept = delete;

    void SetFirstAgent(AgentType* first)
    {
        m_first = first;
    }

    void SetSecondAgent(AgentType* second)
    {
        m_second = second;
    }

    PlayState Start(Game& game)
    {
        m_recorder.Start();

        PlayState result;
        AgentType* nextAgent = nullptr;

        while (true)
        {
            if (game.GetCurrentPlayer().playerType == PlayerType::PLAYER1)
            {
                nextAgent = m_first;
            }
            else
            {
                nextAgent = m_second;
            }

            nextAgent->Think(
                BoardRefView(game, game.GetCurrentPlayer().playerType));

            m_actionCallback.Initialize(game, nextAgent);
            result = game.PerformAction(m_actionCallback);

            if (result != PlayState::PLAYING)
            {
                break;
            }
        }

        m_recorder.End(game.GetCurrentPlayer().playerType, result);

        return result;
    }

 private:
    class ActionCallback : public ActionParams
    {
     public:
        ActionCallback(Judger& guide)
            : m_guide(guide), m_callback(nullptr), m_game(nullptr)
        {
            // Do nothing
        }

        //! Deleted copy constructor.
        ActionCallback(const ActionCallback& rhs) = delete;

        //! Deleted move constructor.
        ActionCallback(ActionCallback&& rhs) noexcept = delete;

        //! Deleted copy assignment operator.
        ActionCallback& operator=(const ActionCallback& rhs) = delete;

        //! Deleted move assignment operator.
        ActionCallback& operator=(ActionCallback&& rhs) noexcept = delete;

        void Initialize(Game& game, AgentType* callback)
        {
            m_game = &game;
            m_callback = callback;

            ActionParams::Initialize(*m_game);
        }

        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& choices) final
        {
            if (actionType == ActionType::RANDOM)
            {
                int exclusiveMax = choices.Size();
                auto action = Random::get<std::size_t>(0, exclusiveMax - 1);
                m_guide.m_recorder.RecordRandomAction(exclusiveMax, action);
                return action;
            }

            int action = m_callback->GetAction(actionType, choices);

            if (actionType == ActionType::MAIN_ACTION)
            {
                auto mainOp = m_checker.GetMainActions()[action];
                m_guide.m_recorder.RecordMainAction(*m_game, mainOp);
                return action;
            }

            m_guide.m_recorder.RecordManualAction(actionType, choices, action);
            return action;
        }

     private:
        Judger& m_guide;
        AgentType* m_callback;
        Game* m_game;
    };

    ActionCallback m_actionCallback;
    AgentType* m_first;
    AgentType* m_second;
    RecorderType& m_recorder;
};
}  // namespace RosettaTorch::Judges

#endif  // ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP