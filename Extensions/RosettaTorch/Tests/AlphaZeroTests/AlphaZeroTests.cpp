// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Logger/StdoutLogger.hpp>
#include <AlphaZero/Trainer.hpp>

using namespace RosettaTorch;

static void Initialize()
{
    std::cout << "Reading json file...";

    Cards::GetInstance();

    std::cout << " Done." << std::endl;
}

int main()
{
    Initialize();

    AlphaZero::StdoutLogger logger;
    AlphaZero::Trainer trainer(logger);

    AlphaZero::TrainerConfig trainerConfig;
    trainerConfig.threads = 4;

    trainerConfig.EVALUATION_WIN_RATE = 0.55f;
    trainerConfig.TRAINING_DATA_CAPACITY = 13;  // 8192

    trainerConfig.selfPlay.saveDir = "./self_play";
    trainerConfig.selfPlay.agentConfig.threads = 1;
    trainerConfig.selfPlay.agentConfig.iterationsPerAction = 1000;
    trainerConfig.selfPlay.agentConfig.actionFollowTemperature = 1.0;

    trainerConfig.optimizer.batchSize = 32;
    trainerConfig.optimizer.batches = 100;
    trainerConfig.optimizer.epoches = 10000;
    trainerConfig.optimizer.epochesForRun =
        trainerConfig.optimizer.epoches / 10;

    trainerConfig.evaluation.runs = 100;
    trainerConfig.evaluation.agentConfig.threads = 1;
    trainerConfig.evaluation.agentConfig.iterationsPerAction = 1000;
    trainerConfig.evaluation.agentConfig.callbackInterval = 100;
    trainerConfig.evaluation.agentConfig.actionFollowTemperature = 0.0;

    trainerConfig.MINIMUM_TRAINING_DATA = trainerConfig.optimizer.batchSize * 1;

    trainerConfig.bestNetPath = "best_net";
    NeuralNet::NeuralNetwork::CreateWithRandomWeights(
        trainerConfig.bestNetPath);
    trainerConfig.isBestNetRandom = true;

    trainerConfig.competitorNetPath = "competitor_net";

    trainer.Initialize(trainerConfig);

    trainer.Train();

    trainer.Release();

    return EXIT_SUCCESS;
}
