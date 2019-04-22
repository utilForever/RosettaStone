// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Policies/Policy.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Tasks/Tasks.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;

namespace RosettaStone
{
Game::Game(GameConfig& gameConfig) : m_gameConfig(gameConfig)
{
    // Set game to player
    for (auto& p : m_players)
    {
        p.SetGame(this);
    }

    // Set player type
    GetPlayer1().playerType = PlayerType::PLAYER1;
    GetPlayer2().playerType = PlayerType::PLAYER2;

    // Add hero and hero power
    GetPlayer1().AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player1Class),
        Cards::GetDefaultHeroPower(gameConfig.player1Class));
    GetPlayer2().AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player2Class),
        Cards::GetDefaultHeroPower(gameConfig.player2Class));

    // Set opponent player
    GetPlayer1().opponent = &GetPlayer2();
    GetPlayer2().opponent = &GetPlayer1();
}

Player& Game::GetPlayer1()
{
    return m_players[0];
}

Player& Game::GetPlayer2()
{
    return m_players[1];
}

Player& Game::GetCurrentPlayer() const
{
    return *m_currentPlayer;
}

Player& Game::GetOpponentPlayer() const
{
    return *m_currentPlayer->opponent;
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
        GetPlayer1().GetDeck().Shuffle();
        GetPlayer2().GetDeck().Shuffle();
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
    for (auto& p : m_players)
    {
        // Draw 3 cards
        Generic::Draw(p);
        Generic::Draw(p);
        Generic::Draw(p);

        if (&p != m_firstPlayer)
        {
            // Draw 4th card for second player
            Generic::Draw(p);

            // Give "The Coin" card to second player
            Card coin = Cards::FindCardByID("GAME_005");
            p.GetHand().AddCard(*Entity::GetFromCard(p, std::move(coin)));
        }
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
    GetPlayer1().mulliganState = Mulligan::INPUT;
    GetPlayer2().mulliganState = Mulligan::INPUT;

    // Collect cards that can redraw
    std::vector<std::size_t> p1HandIDs, p2HandIDs;
    for (auto& entity : GetPlayer1().GetHand().GetAllCards())
    {
        p1HandIDs.emplace_back(entity->id);
    }
    for (auto& entity : GetPlayer2().GetHand().GetAllCards())
    {
        p2HandIDs.emplace_back(entity->id);
    }

    // Create choice for each player
    Generic::CreateChoice(GetPlayer1(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p1HandIDs);
    Generic::CreateChoice(GetPlayer2(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p2HandIDs);

    Player& player1 = GetPlayer1();
    // Request mulligan choices to policy.
    TaskMeta p1Choice = player1.policy->Require(player1, TaskID::MULLIGAN);

    // Get mulligan choices from policy.
    Generic::ChoiceMulligan(player1,
                            p1Choice.GetObject<std::vector<std::size_t>>());

    Player& player2 = GetPlayer2();
    // Request mulligan choices to policy.
    TaskMeta p2Choice = player2.policy->Require(player2, TaskID::MULLIGAN);

    // Get mulligan choices from policy.
    Generic::ChoiceMulligan(player2,
                            p2Choice.GetObject<std::vector<std::size_t>>());

    nextStep = Step::MAIN_BEGIN;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainBegin()
{
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
    for (auto& p : m_players)
    {
        // Hero
        p.GetHero()->numAttacked = 0;
        // Field
        for (auto& m : p.GetField().GetAllMinions())
        {
            m->numAttacked = 0;
        }
    }

    // Reset exhaust for current player
    auto& curPlayer = GetCurrentPlayer();
    // Hero
    curPlayer.GetHero()->SetExhausted(false);
    // Weapon
    if (curPlayer.GetHero()->weapon != nullptr)
    {
        curPlayer.GetHero()->weapon->SetExhausted(false);
    }
    // Hero power
    curPlayer.GetHero()->heroPower->SetExhausted(false);
    // Field
    for (auto& m : curPlayer.GetField().GetAllMinions())
    {
        m->SetExhausted(false);
    }

    // Set next step
    nextStep = Step::MAIN_START_TRIGGERS;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainStartTriggers()
{
    triggerManager.OnStartTurnTrigger(&GetCurrentPlayer(), nullptr);
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
    auto& curPlayer = GetCurrentPlayer();

    // Add mana crystal to current player
    Generic::ChangeManaCrystal(curPlayer, 1, false);

    // Clear used mana
    curPlayer.SetUsedMana(0);
    // Remove temporary mana
    curPlayer.SetTemporaryMana(0);

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
    auto& player = GetCurrentPlayer();

    // If game end.
    if (player.GetHero()->GetHealth() <= 0 ||
        player.opponent->GetHero()->GetHealth() <= 0)
    {
        // Set losing user.
        if (player.GetHero()->GetHealth() <= 0)
        {
            player.playState = PlayState::LOSING;
        }
        else
        {
            player.opponent->playState = PlayState::LOSING;
        }

        nextStep = Step::FINAL_WRAPUP;
        if (m_gameConfig.autoRun)
        {
            GameManager::ProcessNextStep(*this, nextStep);
        }
        return;
    }

    // Get next action as TaskID, ex) TaskID::END_TURN, TaskID::ATTACK,
    // TaskID::PLAY_CARD
    TaskMeta next = player.policy->Next(*this);
    // If turn end.
    if (next.GetID() == TaskID::END_TURN)
    {
        nextStep = Step::MAIN_END;
        if (m_gameConfig.autoRun)
        {
            GameManager::ProcessNextStep(*this, nextStep);
        }
        return;
    }

    // Get requirements for proper action.
    TaskMeta req = player.policy->Require(player, next.GetID());
    SizedPtr<Entity*> list = req.GetObject<SizedPtr<Entity*>>();
    switch (next.GetID())
    {
        // Attack target
        case TaskID::ATTACK:
        {
            if (list.size() >= 2)
            {
                Entity* source = list[0];
                Entity* target = list[1];
                Task::Run(player, PlayerTasks::AttackTask(source, target));
            }
            break;
        }
        // Play card
        case TaskID::PLAY_CARD:
        {
            // If requirement doesn't satisfy
            if (list.size() < 1)
            {
                break;
            }

            Entity* source = list[0];
            switch (source->card.GetCardType())
            {
                // Summon minion
                case CardType::MINION:
                    Task::Run(player, PlayerTasks::PlayCardTask::Minion(
                                          player, source));
                    break;
                // Cast spell
                case CardType::SPELL:
                    if (list.size() == 1)
                    {
                        Task::Run(player, PlayerTasks::PlayCardTask::Spell(
                                              player, source));
                    }
                    else
                    {
                        Entity* target = list[1];
                        Task::Run(player,
                                  PlayerTasks::PlayCardTask::SpellTarget(
                                      player, source, target));
                    }
                    break;
                // Use weapon
                case CardType::WEAPON:
                    Task::Run(player, PlayerTasks::PlayCardTask::Weapon(
                                          player, source));
                    break;
                default:
                    throw std::invalid_argument(
                        "Game::MainAction() - Invalid card type!");
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "Game::MainAction() - Invalid task type!");
    }

    nextStep = Step::MAIN_ACTION;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
    return;
}

void Game::MainEnd()
{
    // Set next step
    nextStep = Step::MAIN_CLEANUP;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainCleanUp()
{
    auto& curPlayer = GetCurrentPlayer();

    // Remove one-turn effects
    for (auto& effectPair : oneTurnEffects)
    {
        Character* character = effectPair.first;
        Effect* effect = effectPair.second;

        effect->Remove(character);
        delete effect;
    }
    oneTurnEffects.clear();

    // Unfreeze all characters they control that are Frozen, don't have
    // summoning sickness (or do have Charge) and have not attacked that turn
    // Hero
    if (curPlayer.GetHero()->GetGameTag(GameTag::FROZEN) == 1 &&
        curPlayer.GetHero()->numAttacked == 0)
    {
        curPlayer.GetHero()->SetGameTag(GameTag::FROZEN, 0);
    }
    // Field
    for (auto& m : curPlayer.GetField().GetAllMinions())
    {
        if (m->GetGameTag(GameTag::FROZEN) == 1 && m->numAttacked == 0 &&
            !m->GetExhausted())
        {
            m->SetGameTag(GameTag::FROZEN, 0);
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
    m_currentPlayer = m_currentPlayer->opponent;

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
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::FinalGameOver()
{
    // Set game state to complete
    state = State::COMPLETE;
}

void Game::StartGame()
{
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

        Entity* entity = Entity::GetFromCard(GetPlayer1(), std::move(card));
        GetPlayer1().GetDeck().AddCard(*entity);
    }
    for (auto& card : m_gameConfig.player2Deck)
    {
        if (card.id.empty())
        {
            continue;
        }

        Entity* entity = Entity::GetFromCard(GetPlayer2(), std::move(card));
        GetPlayer2().GetDeck().AddCard(*entity);
    }

    // Fill cards to deck
    if (m_gameConfig.doFillDecks)
    {
        for (auto& p : m_players)
        {
            for (auto& cardID : m_gameConfig.fillCardIDs)
            {
                Card card = Cards::FindCardByID(cardID);
                Entity* entity = Entity::GetFromCard(p, std::move(card));
                p.GetDeck().AddCard(*entity);
            }
        }
    }

    // Set game states
    state = State::RUNNING;
    for (auto& p : m_players)
    {
        p.playState = PlayState::PLAYING;
    }

    // Determine first player
    switch (m_gameConfig.startPlayer)
    {
        case PlayerType::RANDOM:
        {
            const auto val = Random::get(0, 1);
            m_firstPlayer = &m_players[val];
            break;
        }
        case PlayerType::PLAYER1:
            m_firstPlayer = &m_players[0];
            break;
        case PlayerType::PLAYER2:
            m_firstPlayer = &m_players[1];
            break;
    }
    m_currentPlayer = m_firstPlayer;

    // Set first turn
    m_turn = 1;

    // Set next step
    nextStep = Step::BEGIN_FIRST;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::ProcessDestroyAndUpdateAura()
{
    UpdateAura();

    // Destroy weapons
    if (GetPlayer1().GetHero()->weapon != nullptr &&
        GetPlayer1().GetHero()->weapon->isDestroyed)
    {
        GetPlayer1().GetHero()->RemoveWeapon();
    }
    if (GetPlayer2().GetHero()->weapon != nullptr &&
        GetPlayer2().GetHero()->weapon->isDestroyed)
    {
        GetPlayer2().GetHero()->RemoveWeapon();
    }

    // Destroy minions
    if (!deadMinions.empty())
    {
        for (auto& deadMinion : deadMinions)
        {
            Minion* minion = deadMinion.second;

            // Process deathrattle tasks
            for (auto& power : minion->card.power.GetDeathrattleTask())
            {
                if (power == nullptr)
                {
                    continue;
                }

                power->Run(*minion->owner);
            }

            // Remove minion from battlefield
            minion->owner->GetField().RemoveMinion(*minion);
            // Add minion to graveyard
            minion->owner->GetGraveyard().AddCard(*minion);
        }

        deadMinions.clear();
    }

    UpdateAura();
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

void Game::ProcessUntil(Step untilStep)
{
    m_gameConfig.autoRun = false;
    while (nextStep != untilStep)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::ProcessTasks()
{
    while (!taskQueue.empty())
    {
        ITask* task = taskQueue.front();
        task->Run(GetCurrentPlayer());

        taskQueue.pop_front();
    }
}
}  // namespace RosettaStone
