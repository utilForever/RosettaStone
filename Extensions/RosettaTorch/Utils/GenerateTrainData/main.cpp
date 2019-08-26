// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Agents/MCTSAgent.hpp>
#include <Agents/MCTSConfig.hpp>
#include <Judges/JSON/Recorder.hpp>
#include <Judges/Judger.hpp>

#include <Rosetta/Cards/Cards.hpp>

#include <effolkronium/random.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

using Random = effolkronium::random_static;

class AgentCallback
{
 public:
    AgentCallback(int maxIterations)
        : m_isFirstTime(true), m_maxIterations(maxIterations)
    {
        // Do nothing
    }

    void BeforeThink([[maybe_unused]] const BoardRefView& boardView)
    {
        m_isFirstTime = true;
    }

    void Think(const BoardRefView& boardView, uint64_t iteration)
    {
        if (m_isFirstTime)
        {
            std::cout << "Turn: " << boardView.GetTurn() << std::endl;
            m_lastShown = std::chrono::steady_clock::now();
            m_isFirstTime = false;
        }

        using namespace std::chrono;

        const auto now = steady_clock::now();
        const auto afterLastShown =
            duration_cast<seconds>(now - m_lastShown).count();
        if (afterLastShown > 5)
        {
            const double percent =
                static_cast<double>(iteration) / m_maxIterations;
            std::cout << "Iterations: " << iteration << " (" << percent * 100.0
                      << "%)" << std::endl;
            m_lastShown = now;
        }
    }

    void AfterThink(uint64_t iteration)
    {
        std::cout << "Total iterations: " << iteration << std::endl;
    }

 private:
    bool m_isFirstTime;
    std::uint64_t m_maxIterations;
    std::chrono::steady_clock::time_point m_lastShown;
};

static void Initialize()
{
    std::cout << "Reading json file...";

    Cards::GetInstance();

    std::cout << " Done." << std::endl;
}

void SaveJSON(const nlohmann::json& json)
{
    time_t now;
    time(&now);

    struct tm timeinfo
    {
    };
#ifdef _MSC_VER
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif

    char buffer[80];
    strftime(buffer, 80, "%Y%m%d-%H%M%S", &timeinfo);

    std::ostringstream ss;
    const int postfix = rand() % 90000 + 10000;
    ss << buffer << "-" << postfix << ".json";
    const std::string fileName = ss.str();

    std::ofstream fs(fileName, std::ofstream::trunc);
    fs << json;
    fs.close();
}

int main(int argc, char* argv[])
{
    std::cout << "Generate train data started." << std::endl;

    Initialize();

    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " (threads)"
                  << " (iterations)" << std::endl;
        return EXIT_FAILURE;
    }

    RosettaTorch::Agents::MCTSConfig config;
    config.threads = 1;
    config.iterationsPerAction = 1000;
    config.mcts.neuralNetPath = "neural_net";

    {
        std::istringstream ss(argv[1]);
        ss >> config.threads;
    }
    {
        std::istringstream ss(argv[2]);
        ss >> config.iterationsPerAction;
    }

    std::cout << "Parameters: " << std::endl;
    std::cout << "\tThreads: " << config.threads << std::endl;
    std::cout << "\tIterations: " << config.iterationsPerAction << std::endl;

    using MCTSAgent = RosettaTorch::Agents::MCTSAgent<AgentCallback>;
    using namespace RosettaTorch::Judges::JSON;

    Recorder recorder;
    RosettaTorch::Judges::Judger<MCTSAgent, Recorder> judger(recorder);
    MCTSAgent first(config, AgentCallback(config.iterationsPerAction));
    MCTSAgent second(config, AgentCallback(config.iterationsPerAction));

    judger.SetFirstAgent(&first);
    judger.SetSecondAgent(&second);

    GameConfig gameConfig;
    gameConfig.player1Class = CardClass::PRIEST;
    gameConfig.player2Class = CardClass::MAGE;
    gameConfig.startPlayer = PlayerType::PLAYER1;
    gameConfig.doShuffle = false;
    gameConfig.doFillDecks = false;
    gameConfig.skipMulligan = true;
    gameConfig.autoRun = true;

    std::array<std::string, START_DECK_SIZE> deck = {
        "CS2_106", "CS2_105", "CS1_112", "CS1_112",  // 1
        "CS1_113", "CS1_113", "CS1_130", "CS1_130",  // 2
        "CS2_007", "CS2_007", "CS2_022", "CS2_022",  // 3
        "CS2_023", "CS2_023", "CS2_024", "CS2_024",  // 4
        "CS2_025", "CS2_025", "CS2_026", "CS2_026",  // 5
        "CS2_027", "CS2_027", "CS2_029", "CS2_029",  // 6
        "CS2_032", "CS2_032", "CS2_033", "CS2_033",  // 7
        "CS2_037", "CS2_037"
    };

    for (size_t j = 0; j < START_DECK_SIZE; ++j)
    {
        gameConfig.player1Deck[j] = *Cards::FindCardByID(deck[j]);
        gameConfig.player2Deck[j] = *Cards::FindCardByID(deck[j]);
    }

    Game game(gameConfig);
    game.StartGame();
    judger.Start(game);

    SaveJSON(recorder.GetJSON());

    return EXIT_SUCCESS;
}