// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Views/BoardRefView.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;
using namespace RosettaStone::PlayerTasks;

namespace RosettaStone
{
Game::Game()
{
    Initialize();

    m_gameConfig.doShuffle = true;
    m_gameConfig.skipMulligan = true;
    m_gameConfig.autoRun = true;
}

Game::Game(const GameConfig& gameConfig) : m_gameConfig(gameConfig)
{
    Initialize();

    // Add hero and hero power
    GetPlayer1()->AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player1Class),
        Cards::GetDefaultHeroPower(gameConfig.player1Class));
    GetPlayer2()->AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player2Class),
        Cards::GetDefaultHeroPower(gameConfig.player2Class));

    // Reverse card order in deck
    if (!m_gameConfig.doShuffle)
    {
        std::reverse(m_gameConfig.player1Deck.begin(),
                     m_gameConfig.player1Deck.end());
        std::reverse(m_gameConfig.player2Deck.begin(),
                     m_gameConfig.player2Deck.end());
    }

    // Set up decks
    for (auto& card : m_gameConfig.player1Deck)
    {
        if (card.id.empty())
        {
            continue;
        }

        Playable* playable = Entity::GetFromCard(
            GetPlayer1(), &card, std::nullopt, GetPlayer1()->GetDeckZone());
        GetPlayer1()->GetDeckZone()->Add(playable);
    }
    for (auto& card : m_gameConfig.player2Deck)
    {
        if (card.id.empty())
        {
            continue;
        }

        Playable* playable = Entity::GetFromCard(
            GetPlayer2(), &card, std::nullopt, GetPlayer2()->GetDeckZone());
        GetPlayer2()->GetDeckZone()->Add(playable);
    }

    // Fill cards to deck
    if (m_gameConfig.doFillDecks)
    {
        for (auto& p : m_players)
        {
            for (auto& cardID : m_gameConfig.fillCardIDs)
            {
                Card* card = Cards::FindCardByID(cardID);
                Playable* playable = Entity::GetFromCard(&p, card);
                p.GetDeckZone()->Add(playable);
            }
        }
    }

    // Determine first player
    switch (m_gameConfig.startPlayer)
    {
        case PlayerType::RANDOM:
        {
            const auto val = Random::get(0, 1);
            m_currentPlayer =
                (val == 0) ? PlayerType::PLAYER1 : PlayerType::PLAYER2;
            break;
        }
        default:
            m_currentPlayer = m_gameConfig.startPlayer;
            break;
    }

    // Set first turn
    m_turn = 1;
}

void Game::Initialize()
{
    // Set game to player
    for (auto& p : m_players)
    {
        p.game = this;
    }

    // Set player type
    GetPlayer1()->playerType = PlayerType::PLAYER1;
    GetPlayer2()->playerType = PlayerType::PLAYER2;

    // Set opponent player
    GetPlayer1()->opponent = GetPlayer2();
    GetPlayer2()->opponent = GetPlayer1();

    // Set states
    state = State::RUNNING;
    for (auto& p : m_players)
    {
        p.playState = PlayState::PLAYING;
    }
}

void Game::RefCopyFrom(const Game& rhs)
{
    state = rhs.state;

    step = rhs.step;
    nextStep = rhs.nextStep;

    taskQueue = rhs.taskQueue;
    taskStack = rhs.taskStack;
    triggerManager = rhs.triggerManager;

    auras = rhs.auras;
    triggers = rhs.triggers;
    oneTurnEffects = rhs.oneTurnEffects;
    summonedMinions = rhs.summonedMinions;
    deadMinions = rhs.deadMinions;

    m_gameConfig = rhs.m_gameConfig;

    m_players[0].RefCopy(rhs.m_players[0]);
    m_players[1].RefCopy(rhs.m_players[1]);
    m_turn = rhs.m_turn;

    m_entityID = rhs.m_entityID;
    m_oopIndex = rhs.m_oopIndex;
}

FormatType Game::GetFormatType() const
{
    return m_gameConfig.formatType;
}

Player* Game::GetPlayer1()
{
    return &m_players[0];
}

const Player* Game::GetPlayer1() const
{
    return &m_players[0];
}

Player* Game::GetPlayer2()
{
    return &m_players[1];
}

const Player* Game::GetPlayer2() const
{
    return &m_players[1];
}

Player* Game::GetCurrentPlayer()
{
    if (m_currentPlayer == PlayerType::PLAYER1)
    {
        return &m_players[0];
    }

    return &m_players[1];
}

const Player* Game::GetCurrentPlayer() const
{
    if (m_currentPlayer == PlayerType::PLAYER1)
    {
        return &m_players[0];
    }

    return &m_players[1];
}

void Game::SetCurrentPlayer(PlayerType playerType)
{
    m_currentPlayer = playerType;
}

Player* Game::GetOpponentPlayer()
{
    if (m_currentPlayer == PlayerType::PLAYER1)
    {
        return &m_players[1];
    }

    return &m_players[0];
}

const Player* Game::GetOpponentPlayer() const
{
    if (m_currentPlayer == PlayerType::PLAYER1)
    {
        return &m_players[1];
    }

    return &m_players[0];
}

int Game::GetTurn() const
{
    return m_turn;
}

void Game::SetTurn(int turn)
{
    m_turn = turn;
}

std::size_t Game::GetNextID()
{
    return m_entityID++;
}

std::size_t Game::GetNextOOP()
{
    return m_oopIndex++;
}

void Game::BeginFirst()
{
    // Set next step
    nextStep = Step::BEGIN_SHUFFLE;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginShuffle()
{
    // Shuffle cards in deck
    if (m_gameConfig.doShuffle)
    {
        GetPlayer1()->GetDeckZone()->Shuffle();
        GetPlayer2()->GetDeckZone()->Shuffle();
    }

    // Set next step
    nextStep = Step::BEGIN_DRAW;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginDraw()
{
    for (auto& player : m_players)
    {
        // Draw 3 cards
        Generic::Draw(&player);
        Generic::Draw(&player);
        Generic::Draw(&player);

        if (&player != GetCurrentPlayer())
        {
            // Draw 4th card for second player
            Generic::Draw(&player);

            // Give "The Coin" card to second player
            Card* coin = Cards::FindCardByID("GAME_005");
            player.GetHandZone()->Add(Entity::GetFromCard(&player, coin));
        }
    }

    // Initialize timeout
    for (auto& player : m_players)
    {
        player.SetTimeOut(75);
    }

    // Set next step
    nextStep =
        m_gameConfig.skipMulligan ? Step::MAIN_BEGIN : Step::BEGIN_MULLIGAN;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginMulligan()
{
    // Start mulligan state
    GetPlayer1()->mulliganState = Mulligan::INPUT;
    GetPlayer2()->mulliganState = Mulligan::INPUT;

    // Collect cards that can redraw
    std::vector<std::size_t> p1HandIDs, p2HandIDs;
    for (auto& entity : GetPlayer1()->GetHandZone()->GetAll())
    {
        p1HandIDs.emplace_back(entity->id);
    }
    for (auto& entity : GetPlayer2()->GetHandZone()->GetAll())
    {
        p2HandIDs.emplace_back(entity->id);
    }

    // Create choice for each player
    Generic::CreateChoice(GetPlayer1(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p1HandIDs);
    Generic::CreateChoice(GetPlayer2(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p2HandIDs);
}

void Game::MainBegin()
{
    // Process tasks
    ProcessTasks();

    // Set next step
    nextStep = Step::MAIN_READY;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainReady()
{
    // Reset the number of attacked
    for (auto& player : m_players)
    {
        // Field
        for (auto& minion : player.GetFieldZone()->GetAll())
        {
            minion->SetNumAttacksThisTurn(0);
        }

        // Hero
        player.GetHero()->SetNumAttacksThisTurn(0);

        // Player
        player.SetNumCardsPlayedThisTurn(0);
        player.SetNumMinionsPlayedThisTurn(0);
        player.SetNumFriendlyMinionsDiedThisTurn(0);
    }

    // Reset exhaust for current player
    const auto curPlayer = GetCurrentPlayer();
    // Hero
    curPlayer->GetHero()->SetExhausted(false);
    // Weapon
    if (curPlayer->GetHero()->HasWeapon())
    {
        curPlayer->GetWeapon().SetExhausted(false);
    }
    // Hero power
    curPlayer->GetHeroPower().SetExhausted(false);
    // Field
    for (auto& m : curPlayer->GetFieldZone()->GetAll())
    {
        m->SetExhausted(false);
    }

    // Reset combo active
    curPlayer->SetComboActive(false);

    // Set next step
    nextStep = Step::MAIN_START_TRIGGERS;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainStartTriggers()
{
    triggerManager.OnStartTurnTrigger(GetCurrentPlayer());
    ProcessTasks();
    ProcessDestroyAndUpdateAura();

    // Set next step
    nextStep = Step::MAIN_RESOURCE;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainResource()
{
    const auto curPlayer = GetCurrentPlayer();

    // Add mana crystal to current player
    Generic::ChangeManaCrystal(curPlayer, 1, false);

    // Clear used mana
    curPlayer->SetUsedMana(0);
    // Remove temporary mana
    curPlayer->SetTemporaryMana(0);

    // Process overload
    curPlayer->SetOverloadLocked(curPlayer->GetOverloadOwed());
    curPlayer->SetOverloadOwed(0);

    // Set next step
    nextStep = Step::MAIN_DRAW;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainDraw()
{
    // Draw a card for current player
    Generic::Draw(GetCurrentPlayer());

    // Set next step
    nextStep = Step::MAIN_START;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainStart()
{
    // Set next step
    nextStep = Step::MAIN_ACTION;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainAction()
{
    // Do nothing
}

void Game::MainEnd()
{
    taskQueue.StartEvent();
    triggerManager.OnEndTurnTrigger(GetCurrentPlayer());
    ProcessTasks();
    taskQueue.EndEvent();
    ProcessDestroyAndUpdateAura();

    // Set next step
    nextStep = Step::MAIN_CLEANUP;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainCleanUp()
{
    const auto curPlayer = GetCurrentPlayer();

    // Remove one-turn effects
    if (const auto enchantments = oneTurnEffectEchantments;
        !enchantments.empty())
    {
        for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
        {
            enchantments[i]->Remove();
        }
    }

    for (auto& effectPair : oneTurnEffects)
    {
        Entity* entity = effectPair.first;
        IEffect* effect = effectPair.second;

        effect->RemoveFrom(entity);
    }
    oneTurnEffects.clear();

    // Unfreeze all characters they control that are Frozen, don't have
    // summoning sickness (or do have Charge) and have not attacked that turn
    // Hero
    if (curPlayer->GetHero()->IsFrozen() &&
        curPlayer->GetHero()->GetNumAttacksThisTurn() == 0)
    {
        curPlayer->GetHero()->SetGameTag(GameTag::FROZEN, 0);
    }
    // Field
    for (auto& minion : curPlayer->GetFieldZone()->GetAll())
    {
        if (minion->IsFrozen() && minion->GetNumAttacksThisTurn() == 0 &&
            !minion->IsExhausted())
        {
            minion->SetGameTag(GameTag::FROZEN, 0);
        }
    }

    // Set next step
    nextStep = Step::MAIN_NEXT;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainNext()
{
    // Set player for next turn
    m_currentPlayer = (m_currentPlayer == PlayerType::PLAYER1)
                          ? PlayerType::PLAYER2
                          : PlayerType::PLAYER1;

    // Count next turn
    m_turn++;

    // Set next step
    nextStep = Step::MAIN_READY;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::FinalWrapUp()
{
    // Set game states according by result
    for (auto& p : m_players)
    {
        if (p.playState == PlayState::LOSING ||
            p.playState == PlayState::CONCEDED)
        {
            p.playState = PlayState::LOST;
            p.opponent->playState = PlayState::WON;
        }
    }

    // Set next step
    nextStep = Step::FINAL_GAMEOVER;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::FinalGameOver()
{
    // Set game state to complete
    state = State::COMPLETE;
}

void Game::Start()
{
    // Set next step
    nextStep = Step::BEGIN_FIRST;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::ProcessTasks()
{
    while (!taskQueue.IsEmpty())
    {
        taskQueue.Process();
    }
}

void Game::ProcessDestroyAndUpdateAura()
{
    UpdateAura();

    // Process summoned minions
    if (triggerManager.summonTrigger != nullptr)
    {
        taskQueue.StartEvent();
        for (auto& minion : summonedMinions)
        {
            triggerManager.OnSummonTrigger(minion);
        }
        summonedMinions.clear();
        ProcessTasks();
        taskQueue.EndEvent();
    }

    taskQueue.StartEvent();
    do
    {
        ProcessGraveyard();
        ProcessTasks();
    } while (!deadMinions.empty());
    taskQueue.EndEvent();

    UpdateAura();
}

void Game::ProcessGraveyard()
{
    // Destroy weapons
    if (GetPlayer1()->GetHero()->HasWeapon() &&
        GetPlayer1()->GetWeapon().isDestroyed)
    {
        GetPlayer1()->GetHero()->RemoveWeapon();
    }
    if (GetPlayer2()->GetHero()->HasWeapon() &&
        GetPlayer2()->GetWeapon().isDestroyed)
    {
        GetPlayer2()->GetHero()->RemoveWeapon();
    }

    // Destroy minions
    if (!deadMinions.empty())
    {
        for (auto& deadMinion : deadMinions)
        {
            Minion* minion = deadMinion.second;

            // Death event created
            triggerManager.OnDeathTrigger(minion);

            // Remove minion from battlefield
            minion->SetLastBoardPos(minion->GetZonePosition());
            minion->zone->Remove(minion);

            // Process deathrattle tasks
            if (minion->HasDeathrattle())
            {
                minion->ActivateTask(PowerType::DEATHRATTLE);
            }

            // Add minion to graveyard
            minion->player->GetGraveyardZone()->Add(minion);
            minion->player->SetNumFriendlyMinionsDiedThisTurn(
                minion->player->GetNumFriendlyMinionsDiedThisTurn() + 1);
        }

        deadMinions.clear();
    }

    CheckGameOver();
}

void Game::UpdateAura()
{
    const int auraSize = static_cast<int>(auras.size());
    if (auraSize == 0)
    {
        return;
    }

    for (int i = auraSize - 1; i >= 0; --i)
    {
        auras[i]->Update();
    }
}

std::tuple<PlayState, PlayState> Game::Process(Player* player, ITask* task)
{
    // Process task
    task->SetPlayer(player);
    Task::Run(task);

    if (task->IsFreeable())
    {
        delete task;
    }

    taskStack.Reset();

    return CheckGameOver();
}

std::tuple<PlayState, PlayState> Game::Process(Player* player, ITask&& task)
{
    // Process task
    task.SetPlayer(player);
    Task::Run(std::move(task));

    taskStack.Reset();

    return CheckGameOver();
}

void Game::ProcessUntil(Step untilStep)
{
    m_gameConfig.autoRun = false;
    while (nextStep != untilStep)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

std::tuple<PlayState, PlayState> Game::PerformAction(ActionParams& params)
{
    ITask* task;
    const auto mainOp = params.ChooseMainOp();

    switch (mainOp)
    {
        case MainOpType::PLAY_CARD:
        {
            Playable* card = params.ChooseHandCard();
            Character* target =
                params.GetSpecifiedTarget(card->GetValidPlayTargets());
            const int totalMinions =
                GetCurrentPlayer()->GetFieldZone()->GetCount();
            const int fieldPos = params.GetMinionPutLocation(totalMinions);
            int chooseOne = 0;
            if (card->HasChooseOne())
            {
                const std::size_t card1ID =
                    std::hash<std::string>{}(card->chooseOneCard[0]->card->id);
                const std::size_t card2ID =
                    std::hash<std::string>{}(card->chooseOneCard[1]->card->id);

                std::vector<std::size_t> cardIDs;
                cardIDs.emplace_back(card1ID);
                cardIDs.emplace_back(card2ID);

                const std::size_t chooseCardID = params.ChooseOne(cardIDs);
                if (chooseCardID == card1ID)
                {
                    chooseOne = 1;
                }
                else
                {
                    chooseOne = 2;
                }
            }
            task = new PlayCardTask(card, target, fieldPos, chooseOne);
            break;
        }
        case MainOpType::ATTACK:
        {
            Character* source = params.GetAttacker();
            Character* target = params.GetSpecifiedTarget(
                source->GetValidCombatTargets(GetCurrentPlayer()->opponent));
            task = new AttackTask(source, target);
            break;
        }
        case MainOpType::USE_HERO_POWER:
        {
            Hero* hero = GetCurrentPlayer()->GetHero();
            Character* target = params.GetSpecifiedTarget(
                hero->heroPower->GetValidPlayTargets());
            task = new HeroPowerTask(target);
            break;
        }
        case MainOpType::END_TURN:
        {
            task = new EndTurnTask();
            break;
        }
        default:
        {
            throw std::runtime_error("Invalid main op type");
        }
    }

    task->EnableFreeable();
    return Process(GetCurrentPlayer(), task);
}

ReducedBoardView Game::CreateView()
{
    if (m_currentPlayer == PlayerType::PLAYER1)
    {
        return ReducedBoardView(BoardRefView(*this, PlayerType::PLAYER1));
    }
    else
    {
        return ReducedBoardView(BoardRefView(*this, PlayerType::PLAYER2));
    }
}

std::tuple<PlayState, PlayState> Game::CheckGameOver()
{
    // Check hero of two players is destroyed
    if (GetPlayer1()->GetHero()->isDestroyed)
    {
        if (GetPlayer2()->GetHero()->isDestroyed)
        {
            GetPlayer1()->playState = PlayState::TIED;
            GetPlayer2()->playState = PlayState::TIED;
        }
        else
        {
            GetPlayer1()->playState = PlayState::LOSING;
        }

        // Set next step
        nextStep = Step::FINAL_WRAPUP;
        GameManager::ProcessNextStep(*this, nextStep);
    }
    else if (GetPlayer2()->GetHero()->isDestroyed)
    {
        GetPlayer2()->playState = PlayState::LOSING;

        // Set next step
        nextStep = Step::FINAL_WRAPUP;
        GameManager::ProcessNextStep(*this, nextStep);
    }

    return { GetPlayer1()->playState, GetPlayer2()->playState };
}
}  // namespace RosettaStone
