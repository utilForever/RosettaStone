// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_HPP

#include <AlphaZero/Evaluation/Runner.hpp>
#include <AlphaZero/Logger/ILogger.hpp>
#include <AlphaZero/Optimizer/Runner.hpp>
#include <AlphaZero/SelfPlay/Runner.hpp>
#include <AlphaZero/TrainerConfig.hpp>
#include <AlphaZero/Training/TrainingData.hpp>
#include <AlphaZero/Utils/ThreadPool.hpp>
#include <NeuralNet/NeuralNetwork.hpp>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief Trainer class.
//!
//! This class is a trainer for target to end-user devices.
//! Eliminate context switch as much as possible.
//! Don't rely on threads and OS scheduling.
//! Not targeting for distributed environments.
//!
class Trainer
{
 public:
    //! Constructs trainer with given \p logger.
    //! \param logger The logger to write the log.
    explicit Trainer(ILogger& logger);

    //! Initializes the trainer.
    //! \param config The trainer config.
    void Initialize(const TrainerConfig& config);

    //! Releases the trainer.
    void Release();

    //! Trains the neural network.
    void Train();

 private:
    //! Prepares the data.
    void PrepareData();

    //! Adjusts schedule.
    void AdjustSchedule();

    //! Trains the neural network.
    void TrainNeuralNetwork();

    //! Evaluates the neural network.
    void EvaluateNeuralNetwork();

    //! Starts self play.
    void SelfPlay();

    //! Starts self play for preparing minimum training data.
    //! \param condition The condition callback for self play.
    //! \return The result of self player.
    SelfPlay::RunResult InternalSelfPlay(
        ThreadRunner::ConditionCallback condition);

    //!
    //! \brief Trainer::Schedule struct.
    //!
    //! This struct holds schedule data such as self-play time and train epochs.
    //!
    struct Schedule
    {
        int selfPlayTime = 0;
        int trainEpochs = 0;
    };

    ILogger& m_logger;
    TrainerConfig m_config;

    Schedule m_schedule;
    ThreadPool m_threads;

    TrainingData m_trainingData;
    NeuralNet::NeuralNetwork m_bestNeuralNet;
    NeuralNet::NeuralNetwork m_neuralNet;

    Optimizer::Runner m_optimizer;
    Evaluation::Runner m_evaluator;
    SelfPlay::Runner m_selfPlayer;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_HPP