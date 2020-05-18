// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Agents/MCTSConfig.hpp>
#include <Agents/MCTSRunner.hpp>
#include <MCTS/Inspector/InteractiveShell.hpp>

#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

#include <iostream>
#include <sstream>

using namespace RosettaTorch;

static void Initialize()
{
    std::cout << "Reading json file...";

    Cards::GetInstance();

    std::cout << " Done." << std::endl;
}

struct Config
{
    Agents::MCTSConfig agent;
};

static Config s_config;

void Run(const Agents::MCTSConfig& config, Agents::MCTSRunner* controller,
         int secs)
{
    auto& s = std::cout;

    s << "Running for " << secs << " seconds with " << config.threads
      << " threads " << std::endl;

    const auto start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point runUntil =
        std::chrono::steady_clock::now() + std::chrono::seconds(secs);

    long long lastShowRestSec = -1;
    const auto continueChecker = [&]() {
        const auto now = std::chrono::steady_clock::now();
        if (now > runUntil)
        {
            return false;
        }

        const auto restSec =
            std::chrono::duration_cast<std::chrono::seconds>(runUntil - now)
                .count();
        if (restSec != lastShowRestSec)
        {
            s << "Rest seconds: " << restSec << std::endl;
            lastShowRestSec = restSec;
        }

        return true;
    };

    const auto startIter = controller->GetStatistics().GetSuccededIterates();

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

    for (size_t j = 0; j < deck.size(); ++j)
    {
        gameConfig.player1Deck[j] = Cards::FindCardByID(deck[j]);
        gameConfig.player2Deck[j] = Cards::FindCardByID(deck[j]);
    }

    Game game(gameConfig);
    game.Start();

    controller->Run(BoardRefView(game, game.GetCurrentPlayer()->playerType));

    while (true)
    {
        if (!continueChecker())
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    controller->NotifyStop();
    controller->WaitUntilStopped();

    const auto endIter = controller->GetStatistics().GetSuccededIterates();

    s << std::endl;
    s << "Done iterations: " << (endIter - startIter) << std::endl;
    s << "====== Statistics =====" << std::endl;
    s << controller->GetStatistics().GetDebugMessage();

    const auto now = std::chrono::steady_clock::now();
    const auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    const auto speed = static_cast<double>(endIter - startIter) / ms * 1000;
    s << "Iterations per second: " << speed << std::endl;
    s << std::endl;
}

bool CheckRun(const std::string& cmdLine, Agents::MCTSRunner* controller)
{
    std::stringstream ss(cmdLine);

    std::string cmd;
    ss >> cmd;

    if (cmd == "t" || cmd == "threads")
    {
        ss >> s_config.agent.threads;
        return true;
    }

    if (cmd == "s" || cmd == "start")
    {
        int secs = 0;
        ss >> secs;
        Run(s_config.agent, controller, secs);
        return true;
    }

    return false;
}

void TestAI()
{
    s_config.agent.threads = 8;
    s_config.agent.mcts.neuralNetPath = "neural_net_e2e_test";
    s_config.agent.mcts.isNeuralNetRandom = false;

    Agents::MCTSRunner controller(s_config.agent);
    MCTS::InteractiveShell handler(&controller);

    while (std::cin)
    {
        std::string cmdline;
        std::cout << "Command: ";
        std::getline(std::cin, cmdline);

        if (cmdline == "q" || cmdline == "quit")
        {
            std::cout << "Good bye!" << std::endl;
            break;
        }

        if (CheckRun(cmdline, &controller))
        {
            continue;
        }

        std::istringstream iss(cmdline);
        handler.DoCommand(iss, std::cout);
    }
}

int main()
{
    Initialize();
    TestAI();

    return EXIT_SUCCESS;
}
