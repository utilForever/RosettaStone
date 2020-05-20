// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP
#define ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP

#include <Judges/IAgent.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>
#include <Rosetta/PlayMode/Actions/ActionParams.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

#include <effolkronium/random.hpp>

#include <tuple>

using Random = effolkronium::random_static;

namespace RosettaTorch::Judges
{
//!
//! \brief NullRecorder class.
//!
//! This class is a type of Recorder class and does nothing.
//!
class NullRecorder
{
 public:
    //! Starts recording by clearing JSON object.
    void Start()
    {
        // Do nothing
    }

    //! Records the main action data to JSON object.
    //! \param game The game context.
    //! \param op The main operation type.
    void RecordMainAction([[maybe_unused]] const Game& game,
                          [[maybe_unused]] MainOpType op)
    {
        // Do nothing
    }

    //! Records the randomly selected action to JSON object.
    //! \param maxValue The number of available actions.
    //! \param action The index of available actions selected randomly.
    void RecordRandomAction([[maybe_unused]] int maxValue,
                            [[maybe_unused]] int action)
    {
        // Do nothing
    }

    //! Records the manually selected action to JSON object.
    //! \param actionType The selected action type.
    //! \param choices The type of action choices.
    //! \param action The index of available choices selected manually.
    void RecordManualAction([[maybe_unused]] ActionType actionType,
                            [[maybe_unused]] ActionChoices choices,
                            [[maybe_unused]] int action)
    {
        // Do nothing
    }

    //! Records the game end data to JSON object.
    //! \param result The result of the game (player1 and player2).
    void End([[maybe_unused]] std::tuple<PlayState, PlayState> result)
    {
        // Do nothing
    }
};

//!
//! \brief Judger class.
//!
//! This class allows two agents to compete with each other, and make sure
//! they're following the game rules.
//!
template <class AgentType = IAgent, class RecorderType = NullRecorder>
class Judger
{
 public:
    //! Constructs judger with given \p recorder.
    //! \param recorder The type of recorder.
    explicit Judger(RecorderType& recorder)
        : m_actionCallback(*this),
          m_player1(nullptr),
          m_player2(nullptr),
          m_recorder(recorder)
    {
        // Do nothing
    }

    //! Default destructor.
    ~Judger() = default;

    //! Deleted copy constructor.
    Judger(const Judger& rhs) = delete;

    //! Deleted move constructor.
    Judger(Judger&& rhs) noexcept = delete;

    //! Deleted copy assignment operator.
    Judger& operator=(const Judger& rhs) = delete;

    //! Deleted move assignment operator.
    Judger& operator=(Judger&& rhs) noexcept = delete;

    //! Sets the agent for player 1.
    //! \param player1 The agent type for player 1.
    void SetPlayer1Agent(AgentType* player1)
    {
        m_player1 = player1;
    }

    //! Sets the agent for player 2.
    //! \param player2 The agent type for player 2.
    void SetPlayer2Agent(AgentType* player2)
    {
        m_player2 = player2;
    }

    //! Starts the recorder and the game.
    //! \param game The game context.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> Start(Game& game)
    {
        m_recorder.Start();

        game.Start();

        std::tuple<PlayState, PlayState> result;
        AgentType* nextAgent = nullptr;

        while (true)
        {
            if (game.GetCurrentPlayer()->playerType == PlayerType::PLAYER1)
            {
                nextAgent = m_player1;
            }
            else
            {
                nextAgent = m_player2;
            }

            nextAgent->Think(
                BoardRefView(game, game.GetCurrentPlayer()->playerType));

            m_actionCallback.Init(game, nextAgent);
            result = game.PerformAction(m_actionCallback);

            auto& [p1Result, p2Result] = result;
            if (p1Result != PlayState::PLAYING &&
                p2Result != PlayState::PLAYING)
            {
                break;
            }
        }

        m_recorder.End(result);

        return result;
    }

 private:
    //!
    //! \brief ActionCallback class.
    //!
    //! This class inherits from ActionParams class.
    //!
    class ActionCallback : public ActionParams
    {
     public:
        //! Constructs action callback with given \p guide.
        //! \param guide The judger object to guide.
        explicit ActionCallback(Judger& guide)
            : m_guide(guide), m_callback(nullptr), m_game(nullptr)
        {
            // Do nothing
        }

        //! Default destructor.
        ~ActionCallback() = default;

        //! Deleted copy constructor.
        ActionCallback(const ActionCallback& rhs) = delete;

        //! Deleted move constructor.
        ActionCallback(ActionCallback&& rhs) noexcept = delete;

        //! Deleted copy assignment operator.
        ActionCallback& operator=(const ActionCallback& rhs) = delete;

        //! Deleted move assignment operator.
        ActionCallback& operator=(ActionCallback&& rhs) noexcept = delete;

        //! Initializes member variables and call ActionParams::Initialize().
        //! \param game The game context.
        //! \param callback A callback to get action.
        void Init(Game& game, AgentType* callback)
        {
            m_game = &game;
            m_callback = callback;

            ActionParams::Initialize(*m_game);
        }

        //! Returns the number using \p actionType and \p choices.
        //! \param actionType The action type.
        //! \param choices The action choices.
        //! \return The chosen number using action type and action choices.
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
    AgentType* m_player1;
    AgentType* m_player2;
    RecorderType& m_recorder;
};
}  // namespace RosettaTorch::Judges

#endif  // ROSETTASTONE_TORCH_JUDGES_JUDGER_HPP