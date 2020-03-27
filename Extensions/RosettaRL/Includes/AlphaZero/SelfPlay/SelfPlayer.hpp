// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP

#include <Agents/MCTSAgent.hpp>
#include <AlphaZero/Logger/ILogger.hpp>
#include <AlphaZero/SelfPlay/RunOptions.hpp>
#include <AlphaZero/SelfPlay/RunResult.hpp>
#include <AlphaZero/Training/TrainingData.hpp>
#include <Judges/JSON/Recorder.hpp>
#include <Judges/Judger.hpp>
#include <NeuralNet/NeuralNetwork.hpp>

#include <Rosetta/Commons/DeckCode.hpp>

#include <chrono>

namespace RosettaTorch::AlphaZero::SelfPlay
{
//!
//! \brief AgentCallback class.
//!
//! This class is an agent callback for self-play of AlphaZero.
//!
class AgentCallback
{
 public:
    //! Constructs agent callback with given \p logger.
    //! \param logger The logger to write the log.
    explicit AgentCallback(ILogger& logger);

    //! Processes something before calling Think() method.
    //! \param view The board ref view.
    void BeforeThink(const RosettaStone::BoardRefView& view);

    //! Processes something related to agent.
    //! \param view The board ref view.
    //! \param iteration The number of iteration.
    void Think(const RosettaStone::BoardRefView& view, std::uint64_t iteration);

    //! Processes something after calling Think() method.
    //! \param iteration The number of iteration.
    void AfterThink(std::uint64_t iteration);

 private:
    ILogger& m_logger;
    std::chrono::steady_clock::time_point m_nextShow;
    std::chrono::milliseconds m_showInterval;
};

//!
//! \brief SelfPlayer class.
//!
//! This class is a helper for self-playing the game that provides BeforeRun(),
//! Run() and AfterRun().
//!
class SelfPlayer
{
 public:
    //! Constructs self player with given \p logger.
    //! \param logger The logger to write the log.
    explicit SelfPlayer(ILogger& logger);

    //! Destructor.
    ~SelfPlayer();

    //! The method that runs before method Run().
    //! \param data The training data.
    //! \param neuralNet The neural network.
    //! \param config The options of the runner.
    void BeforeRun(TrainingData& data,
                   const NeuralNet::NeuralNetwork& neuralNet,
                   const RunOptions& config);

    //! The main method of the self player.
    //! \param callback The callback to run.
    template <typename Callback>
    void Run(Callback&& callback)
    {
        while (callback())
        {
            using MCTSAgent = Agents::MCTSAgent<AgentCallback>;

            Judges::JSON::Recorder recorder;
            Judges::Judger<MCTSAgent, Judges::JSON::Recorder> judger(recorder);
            MCTSAgent p1Agent(m_config.agentConfig, AgentCallback(m_logger));
            MCTSAgent p2Agent(m_config.agentConfig, AgentCallback(m_logger));

            judger.SetPlayer1Agent(&p1Agent);
            judger.SetPlayer2Agent(&p2Agent);

            GameConfig gameConfig;
            gameConfig.player1Class = CardClass::WARLOCK;
            gameConfig.player2Class = CardClass::WARLOCK;
            gameConfig.startPlayer = PlayerType::PLAYER1;
            gameConfig.doShuffle = false;
            gameConfig.doFillDecks = false;
            gameConfig.skipMulligan = true;
            gameConfig.autoRun = true;

            const std::string INNKEEPER_EXPERT_WARLOCK =
                "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
            auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

            for (std::size_t j = 0; j < deck.size(); ++j)
            {
                gameConfig.player1Deck[j] = Cards::FindCardByID(deck[j]);
                gameConfig.player2Deck[j] = Cards::FindCardByID(deck[j]);
            }

            Game game(gameConfig);
            judger.Start(game);

            SaveJSON(recorder.GetJSON());

            Judges::JSON::Reader reader;
            reader.Parse(recorder.GetJSON(),
                         [&](const Judges::JSON::NeuralNetInputGetter& input,
                             int label) {
                             m_data->Push(std::make_shared<TrainingDataItem>(
                                 input, label));
                             ++m_result.generatedCount;
                         });
        }
    }

    //! The method that runs after method Run().
    //! \return The result of self player.
    RunResult AfterRun();

 private:
    //! Removes temp file.
    void RemoveTempFile();

    //! Saves recorder data to JSON file.
    //! \param json The JSON object.
    void SaveJSON(const nlohmann::json& json);

    ILogger& m_logger;
    TrainingData* m_data = nullptr;
    RunOptions m_config;
    RunResult m_result;

    std::string m_tempFile;
};
}  // namespace RosettaTorch::AlphaZero::SelfPlay

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP