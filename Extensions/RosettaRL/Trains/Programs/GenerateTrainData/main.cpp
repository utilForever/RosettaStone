// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Agents/MCTSAgent.hpp>
#include <Agents/MCTSConfig.hpp>
#include <Judges/JSON/Recorder.hpp>
#include <Judges/Judger.hpp>

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/DeckCode.hpp>

#include <effolkronium/random.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

using Random = effolkronium::random_static;

class AgentCallback
{
 public:
    explicit AgentCallback(int maxIterations)
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
    const int postfix = Random::get<int>(0, 89999) + 10000;
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
    MCTSAgent p1Agent(config, AgentCallback(config.iterationsPerAction));
    MCTSAgent p2Agent(config, AgentCallback(config.iterationsPerAction));

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

    //for (std::size_t j = 0; j < deck.size(); ++j)
    //{
    //    gameConfig.player1Deck[j] = *Cards::FindCardByID(deck[j]);
    //    gameConfig.player2Deck[j] = *Cards::FindCardByID(deck[j]);
    //}

    Game game(gameConfig);
    judger.Start(game);

    SaveJSON(recorder.GetJSON());

    return EXIT_SUCCESS;
}