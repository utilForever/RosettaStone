// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayLocationTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>

#include <stdexcept>
#include <typeinfo>
#include <utility>

using Random = effolkronium::random_static;
using namespace RosettaStone::PlayMode::PlayerTasks;

namespace RosettaStone::PlayMode
{
namespace
{
class RandomScope
{
 public:
    explicit RandomScope(Random::engine_type& engine) : m_engine(engine)
    {
        std::swap(Random::engine(), m_engine);
    }

    ~RandomScope()
    {
        std::swap(Random::engine(), m_engine);
    }

    RandomScope(const RandomScope&) = delete;
    RandomScope& operator=(const RandomScope&) = delete;

 private:
    Random::engine_type& m_engine;
};
}  // namespace

ReplayGame::ReplayGame(const GameConfig& gameConfig, unsigned int seed)
    : m_config(gameConfig), m_seed(seed), m_random(seed)
{
    if (!m_config.skipMulligan ||
        Cards::GetHeroCard(m_config.player1Class)->id.empty() ||
        Cards::GetHeroCard(m_config.player2Class)->id.empty() ||
        (m_config.startPlayer != PlayerType::PLAYER1 &&
         m_config.startPlayer != PlayerType::PLAYER2 &&
         m_config.startPlayer != PlayerType::RANDOM))
    {
        throw std::invalid_argument(
            "ReplayGame requires valid players and a skipped mulligan");
    }

    m_config.autoRun = true;

    RandomScope random(m_random);

    m_game = std::make_unique<Game>(m_config);
    m_game->Start();
}

const Game& ReplayGame::GetGame() const
{
    return *m_game;
}

const Player* ReplayGame::GetCurrentPlayer() const
{
    return m_game->GetCurrentPlayer();
}

void ReplayGame::CheckReady() const
{
    if (m_failed || m_game->state != State::RUNNING ||
        m_game->step != Step::MAIN_ACTION || !m_game->taskQueue.IsIdle() ||
        !m_game->deadMinions.empty() || !m_game->rebornMinions.empty() ||
        !m_game->summonedMinions.empty())
    {
        throw std::logic_error("ReplayGame requires a quiescent MAIN_ACTION");
    }
}

int ReplayGame::GetEntityID(const Entity* entity) const
{
    if (!entity)
    {
        return -1;
    }

    const int id = entity->GetGameTag(GameTag::ENTITY_ID);
    const auto it = m_game->entityList.find(id);

    if (entity->game != m_game.get() || it == m_game->entityList.end() ||
        it->second != entity)
    {
        throw std::invalid_argument(
            "Task entity does not belong to this replay");
    }

    return id;
}

std::tuple<PlayState, PlayState> ReplayGame::Process(ITask&& task)
{
    CheckReady();

    const auto& type = typeid(task);

    // Only these tasks keep all runtime pointers in ITask's three fields.
    if (type != typeid(AttackTask) && type != typeid(ChooseTask) &&
        type != typeid(EndTurnTask) && type != typeid(HeroPowerTask) &&
        type != typeid(PlayCardTask) && type != typeid(PlayLocationTask) &&
        type != typeid(TradeCardTask))
    {
        throw std::invalid_argument(
            "ReplayGame only records built-in player tasks");
    }

    const auto* player = GetCurrentPlayer();

    if ((type == typeid(ChooseTask)) != static_cast<bool>(player->choice) ||
        player->opponent->choice)
    {
        throw std::logic_error("Resolve the current player's choice first");
    }

    if (type == typeid(ChooseTask) &&
        static_cast<const ChooseTask&>(task).GetChoiceCount() != 1)
    {
        throw std::invalid_argument("Choose exactly one offered entity ID");
    }

    const auto* source = task.GetSource();
    const auto* target = task.GetTarget();

    if ((type == typeid(AttackTask) &&
         (!dynamic_cast<const Character*>(source) ||
          !dynamic_cast<const Character*>(target))) ||
        ((type == typeid(PlayCardTask) || type == typeid(TradeCardTask)) &&
         !dynamic_cast<const Playable*>(source)))
    {
        throw std::invalid_argument(
            "Player task requires a source and valid target");
    }

    RecordedTask record{ GetEntityID(source), GetEntityID(target),
                         task.Clone() };

    if (source && source->player != player)
    {
        throw std::invalid_argument(
            "Task source must belong to the current player");
    }

    record.task->SetPlayer(nullptr);
    record.task->SetSource(nullptr);
    record.task->SetTarget(nullptr);

    m_history.emplace_back(std::move(record));

    return Apply(m_history.back());
}

std::tuple<PlayState, PlayState> ReplayGame::Apply(const RecordedTask& record)
{
    RandomScope random(m_random);
    try
    {
        auto task = record.task->Clone();
        task->SetSource(record.sourceID < 0
                            ? nullptr
                            : m_game->entityList.at(record.sourceID));
        task->SetTarget(record.targetID < 0
                            ? nullptr
                            : m_game->entityList.at(record.targetID));

        return m_game->Process(m_game->GetCurrentPlayer(), std::move(task));
    }
    catch (...)
    {
        // A throwing task can leave partially applied effects; never replay it.
        m_failed = true;
        throw;
    }
}

std::unique_ptr<ReplayGame> ReplayGame::Branch() const
{
    CheckReady();

    if (GetCurrentPlayer()->choice || GetCurrentPlayer()->opponent->choice)
    {
        throw std::logic_error("Resolve choices before branching");
    }

    auto child = std::make_unique<ReplayGame>(m_config, m_seed);
    child->m_history.reserve(m_history.size());

    for (const auto& record : m_history)
    {
        child->m_history.push_back(
            { record.sourceID, record.targetID, record.task->Clone() });
        child->Apply(child->m_history.back());
    }

    child->CheckReady();
    return child;
}
}  // namespace RosettaStone::PlayMode
