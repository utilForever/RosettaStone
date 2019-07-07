// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/InteractiveShell.hpp>

#include <iostream>
#include <sstream>

using namespace RosettaTorch;

static Agents::MCTSConfig g_config;

void Run(Agents::MCTSRunner* controller, int secs)
{
    auto& s = std::cout;

    s << "Running for " << secs << " seconds with " << g_config.threads
      << " threads " << std::endl;

    // const auto start = std::chrono::steady_clock::now();
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

    // auto startIter = controller->GetStatistic().GetSuccededIterates();
    controller->Run();
    // controller->Run(BoardRefView(game, game.GetCurrentPlayer().playerType));
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
    // auto endIter = controller->GetStatistic().GetSuccededIterates();

    s << std::endl;
    // s << "Done iterations: " << (endIter - startIter) << std::endl;
    // s << "====== Statistics =====" << std::endl;
    // controller->GetStatistic().GetDebugMessage();

    // auto now = std::chrono::steady_clock::now();
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now -
    // start)
    //              .count();
    // auto speed = static_cast<double>(endIter - startIter) / ms * 1000;
    // s << "Iterations per second: " << speed << std::endl;
    // s << std::endl;
}

bool CheckRun(const std::string& cmdLine, Agents::MCTSRunner* controller)
{
    std::stringstream ss(cmdLine);

    std::string cmd;
    ss >> cmd;

    if (cmd == "t" || cmd == "threads")
    {
        ss >> g_config.threads;
        return true;
    }

    if (cmd == "s" || cmd == "start")
    {
        int secs = 0;
        ss >> secs;
        Run(controller, secs);
        return true;
    }

    return false;
}

int main()
{
    Cards::GetInstance();

    g_config.threads = 1;
    g_config.treeSamples = 10;

    Agents::MCTSRunner controller(g_config);
    MCTS::InteractiveShell handler(&controller);
    handler.SetConfig(g_config);

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
