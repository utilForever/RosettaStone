// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameManager.hpp>

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

    // Add hero and hero power
    GetPlayer1().AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(gameConfig.player1Class),
        Cards::GetInstance().GetDefaultHeroPower(gameConfig.player1Class));
    GetPlayer2().AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(gameConfig.player2Class),
        Cards::GetInstance().GetDefaultHeroPower(gameConfig.player2Class));

    // Set opponent player
    GetPlayer1().SetOpponent(&GetPlayer2());
    GetPlayer2().SetOpponent(&GetPlayer1());
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
    return m_currentPlayer->GetOpponent();
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
    GameManager::ProcessNextStep(*this, nextStep);
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
    GameManager::ProcessNextStep(*this, nextStep);
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
            Card coin = Cards::GetInstance().FindCardByID("GAME_005");
            p.GetHand().AddCard(*Entity::GetFromCard(p, std::move(coin)));
        }
    }

    // Set next step
    nextStep =
        m_gameConfig.skipMulligan ? Step::MAIN_BEGIN : Step::BEGIN_MULLIGAN;
    GameManager::ProcessNextStep(*this, nextStep);
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
}

void Game::MainBegin()
{
    // Set next step
    nextStep = Step::MAIN_READY;
    GameManager::ProcessNextStep(*this, nextStep);
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
    curPlayer.GetHero()->SetGameTag(GameTag::EXHAUSTED, 0);
    // Weapon
    if (curPlayer.GetHero()->weapon != nullptr)
    {
        curPlayer.GetHero()->weapon->SetGameTag(GameTag::EXHAUSTED, 0);
    }
    // Hero power
    curPlayer.GetHero()->heroPower->SetGameTag(GameTag::EXHAUSTED, 0);
    // Field
    for (auto& m : curPlayer.GetField().GetAllMinions())
    {
        m->SetGameTag(GameTag::EXHAUSTED, 0);
    }

    // Set next step
    nextStep = Step::MAIN_START_TRIGGERS;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainStartTriggers()
{
    // Set next step
    nextStep = Step::MAIN_RESOURCE;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainResource()
{
    auto& curPlayer = GetCurrentPlayer();

    // Add mana crystal to current player
    Generic::ChangeManaCrystal(curPlayer, 1, false);

    // Reset current mana
    curPlayer.currentMana = curPlayer.maximumMana;

    // Set next step
    nextStep = Step::MAIN_DRAW;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainDraw()
{
    // Draw a card for current player
    Generic::Draw(GetCurrentPlayer());

    // Set next step
    nextStep = Step::MAIN_START;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainStart()
{
    // Set next step
    nextStep = Step::MAIN_ACTION;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainEnd()
{
    // Set next step
    nextStep = Step::MAIN_CLEANUP;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainCleanUp()
{
    auto& curPlayer = GetCurrentPlayer();

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
            m->GetGameTag(GameTag::EXHAUSTED) == 0)
        {
            m->SetGameTag(GameTag::FROZEN, 0);
        }
    }

    // Set next step
    nextStep = Step::MAIN_NEXT;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::MainNext()
{
    // Set player for next turn
    m_currentPlayer = &m_currentPlayer->GetOpponent();

    // Count next turn
    m_turn++;

    // Set next step
    nextStep = Step::MAIN_READY;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::FinalWrapUp()
{
    // Set game states according by result
    for (auto& p : m_players)
    {
        if (p.playState == +PlayState::LOSING ||
            p.playState == +PlayState::CONCEDED)
        {
            p.playState = PlayState::LOST;
            p.GetOpponent().playState = PlayState::WON;
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
        if (card.cardType == +CardType::INVALID)
        {
            continue;
        }

        Entity* entity = Entity::GetFromCard(GetPlayer1(), std::move(card));
        GetPlayer1().GetDeck().AddCard(*entity);
    }
    for (auto& card : m_gameConfig.player2Deck)
    {
        if (card.cardType == +CardType::INVALID)
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
                Card card = Cards::GetInstance().FindCardByID(cardID);
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
    GameManager::ProcessNextStep(*this, nextStep);
}
}  // namespace RosettaStone
