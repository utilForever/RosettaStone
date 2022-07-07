// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Enchants/Power.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Managers/GameManager.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;
using namespace RosettaStone::PlayMode::PlayerTasks;

namespace RosettaStone::PlayMode
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

    // Set base class
    GetPlayer1()->baseClass = gameConfig.player1Class;
    GetPlayer2()->baseClass = gameConfig.player2Class;

    // Reverse card order in deck
    if (!m_gameConfig.doShuffle)
    {
        std::reverse(m_gameConfig.player1Deck.begin(),
                     m_gameConfig.player1Deck.end());
        std::reverse(m_gameConfig.player2Deck.begin(),
                     m_gameConfig.player2Deck.end());
    }

    // Set up decks
    for (const auto& card : m_gameConfig.player1Deck)
    {
        if (!card || card->id.empty())
        {
            continue;
        }

        Playable* playable = Entity::GetFromCard(
            GetPlayer1(), card, std::nullopt, GetPlayer1()->GetDeckZone());
        GetPlayer1()->GetDeckZone()->Add(playable);

        //! Set Galakrond hero card
        if (card->IsGalakrond())
        {
            GetPlayer1()->galakrond = playable;
        }
    }

    for (const auto& card : m_gameConfig.player2Deck)
    {
        if (!card || card->id.empty())
        {
            continue;
        }

        Playable* playable = Entity::GetFromCard(
            GetPlayer2(), card, std::nullopt, GetPlayer2()->GetDeckZone());
        GetPlayer2()->GetDeckZone()->Add(playable);

        //! Set Galakrond hero card
        if (card->IsGalakrond())
        {
            GetPlayer2()->galakrond = playable;
        }
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
    rushMinions.reserve(MAX_FIELD_SIZE);

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

std::array<Card*, START_DECK_SIZE> Game::GetPlayerDeck(PlayerType type) const
{
    return type == PlayerType::PLAYER1 ? m_gameConfig.player1Deck
                                       : m_gameConfig.player2Deck;
}

FormatType Game::GetFormatType() const
{
    return m_gameConfig.formatType;
}

Player* Game::GetPlayer1()
{
    return &m_players[0];
}

Player* Game::GetPlayer2()
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

int Game::GetTurn() const
{
    return m_turn;
}

void Game::SetTurn(int turn)
{
    m_turn = turn;
}

int Game::GetNextID()
{
    return m_entityID++;
}

int Game::GetNextOOP()
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
    std::vector<int> p1HandIDs, p2HandIDs;

    for (const auto& entity : GetPlayer1()->GetHandZone()->GetAll())
    {
        p1HandIDs.emplace_back(entity->GetGameTag(GameTag::ENTITY_ID));
    }
    for (const auto& entity : GetPlayer2()->GetHandZone()->GetAll())
    {
        p2HandIDs.emplace_back(entity->GetGameTag(GameTag::ENTITY_ID));
    }

    // Create choice for each player
    Generic::CreateChoice(GetPlayer1(), GetPlayer1(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p1HandIDs);
    Generic::CreateChoice(GetPlayer2(), GetPlayer1(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p2HandIDs);
}

void Game::MainBegin()
{
    // Give "The Coin" card to second player
    Card* coin = Cards::FindCardByID("GAME_005");
    GetOpponentPlayer()->GetHandZone()->Add(
        Entity::GetFromCard(GetOpponentPlayer(), coin));

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
        // Hero
        player.GetHero()->SetNumAttacksThisTurn(0);

        // Field
        for (const auto& minion : player.GetFieldZone()->GetAll())
        {
            minion->SetNumAttacksThisTurn(0);
        }

        // Player
        player.SetNumCardsDrawnThisTurn(0);
        player.SetNumCardsPlayedThisTurn(0);
        player.SetNumMinionsPlayedThisTurn(0);
        player.SetNumTauntMinionsPlayedThisTurn(0);
        player.SetNumFriendlyMinionsDiedThisTurn(0);
    }

    // Reset exhaust for current player
    const auto curPlayer = GetCurrentPlayer();

    // Hero
    curPlayer->GetHero()->SetExhausted(false);

    // Hero power
    curPlayer->GetHeroPower().SetExhausted(false);

    // Weapon
    if (curPlayer->GetHero()->HasWeapon())
    {
        curPlayer->GetWeapon().SetExhausted(false);
    }

    // Field
    for (const auto& minion : curPlayer->GetFieldZone()->GetAll())
    {
        minion->SetExhausted(false);
    }

    // Player
    const int numElementalPlayedThisTurn =
        curPlayer->GetNumElementalPlayedThisTurn();
    curPlayer->SetNumElementalPlayedLastTurn(numElementalPlayedThisTurn);
    curPlayer->SetNumElementalPlayedThisTurn(0);

    const int numSpellCastThisTurn = curPlayer->GetNumSpellsCastThisTurn();
    curPlayer->SetNumSpellsCastLastTurn(numSpellCastThisTurn);
    curPlayer->SetNumSpellsCastThisTurn(0);

    curPlayer->SetAmountHealedThisTurn(0);
    curPlayer->cardsPlayedThisTurn.clear();

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
    ProcessDestroyAndUpdateAura();

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

    if (!rushMinions.empty())
    {
        for (auto& minion : rushMinions)
        {
            entityList[minion]->SetGameTag(GameTag::ATTACKABLE_BY_RUSH, 0);
        }

        rushMinions.clear();
    }

    GetCurrentPlayer()->GetHero()->damageTakenThisTurn = 0;

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

    // Remove ghostly cards
    for (auto& id : ghostlyCards)
    {
        Playable* playable = entityList[id];

        if (playable->GetZoneType() != ZoneType::HAND)
        {
            continue;
        }

        playable->player->GetSetasideZone()->Add(
            playable->zone->Remove(playable));
    }

    // Remove one-turn effects
    if (const auto enchantments = oneTurnEffectEnchantments;
        !enchantments.empty())
    {
        for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
        {
            enchantments[i]->Remove();
        }
    }

    for (const auto& effectPair : oneTurnEffects)
    {
        Entity* entity = effectPair.first;
        const IEffect* effect = effectPair.second;

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
    for (const auto& minion : curPlayer->GetFieldZone()->GetAll())
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
    taskQueue.StartEvent();
    for (const auto& minion : summonedMinions)
    {
        triggerManager.OnSummonTrigger(minion);
    }
    summonedMinions.clear();
    ProcessTasks();
    taskQueue.EndEvent();

    taskQueue.StartEvent();
    do
    {
        ProcessGraveyard();
        ProcessTasks();
        ProcessReborn();
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

            // If player has extra deathrattle, activate power task again
            if (minion->player->ExtraMinionDeathrattle())
            {
                minion->ActivateTask(PowerType::DEATHRATTLE);
            }

            // Add minion to graveyard
            minion->player->GetGraveyardZone()->Add(minion);

            const int val = minion->player->GetNumFriendlyMinionsDiedThisTurn();
            minion->player->SetNumFriendlyMinionsDiedThisTurn(val + 1);

            // Add reborn minion if it has reborn
            if (minion->HasReborn())
            {
                rebornMinions.emplace(deadMinion);
            }
        }

        deadMinions.clear();
    }

    CheckGameOver();
}

void Game::ProcessReborn()
{
    if (!rebornMinions.empty())
    {
        for (const auto& rebornMinion : rebornMinions)
        {
            Generic::SummonReborn(rebornMinion.second);
        }

        rebornMinions.clear();
    }
}

void Game::UpdateAura() const
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

std::tuple<PlayState, PlayState> Game::Process(Player* player,
                                               std::unique_ptr<ITask> task)
{
    // Process task
    task->SetPlayer(player);
    Task::Run(std::move(task));

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
}  // namespace RosettaStone::PlayMode
