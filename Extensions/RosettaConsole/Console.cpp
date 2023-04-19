// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Agents/RandomAgent.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <iostream>

namespace RosettaStone
{
Console::Console(Mode mode) : m_mode{ mode }
{
    if (mode == Mode::STANDARD || mode == Mode::WILD)
    {
        m_computerAgent = std::make_unique<PlayMode::RandomAgent>();
    }
}

void Console::ProcessGame()
{
    switch (m_mode)
    {
        case Mode::STANDARD:
        case Mode::WILD:
            PlayMode::Cards::GetInstance();
            InputDeckCodes();
            break;
        case Mode::BATTLEGROUNDS:
            Battlegrounds::Cards::GetInstance();
            PlayBattlegrounds();
            break;
    }
}

void Console::InputDeckCodes()
{
    std::string deckCode1, deckCode2;

    std::cout << "Input player 1 (You) deck code: ";
    std::cin >> deckCode1;

    std::cout << "Input player 2 (Computer) deck code: ";
    std::cin >> deckCode2;

    PlayMode::Deck deck1 = PlayMode::DeckCode::Decode(deckCode1);
    PlayMode::Deck deck2 = PlayMode::DeckCode::Decode(deckCode2);

    if (m_mode == Mode::STANDARD)
    {
        if (deck1.GetFormatType() != FormatType::STANDARD ||
            deck2.GetFormatType() != FormatType::STANDARD)
        {
            throw std::runtime_error(
                "The game mode and the deck's format type aren't match.");
        }
    }
    else
    {
        if (deck1.GetFormatType() != FormatType::WILD ||
            deck2.GetFormatType() != FormatType::WILD)
        {
            throw std::runtime_error(
                "The game mode and the deck's format type aren't match.");
        }
    }

    PlayStandardOrWild(std::move(deck1), std::move(deck2));
}

void Console::PlayStandardOrWild(PlayMode::Deck&& deck1, PlayMode::Deck&& deck2)
{
    PlayMode::GameConfig gameConfig;
    gameConfig.player1Class = deck1.GetClass();
    gameConfig.player1Deck = deck1.GetCards();
    gameConfig.player2Class = deck2.GetClass();
    gameConfig.player2Deck = deck2.GetCards();
    gameConfig.autoRun = true;
    gameConfig.skipMulligan = false;
    gameConfig.startPlayer = PlayMode::PlayerType::RANDOM;

    // Player 2 is computer-based agent
    m_computerAgent->SetPlayerType(PlayMode::PlayerType::PLAYER2);

    PlayMode::Game game{ gameConfig };
    game.Start();

    ProcessMulligan(game);
}

void Console::PlayBattlegrounds()
{
}

void Console::ProcessMulligan(PlayMode::Game& game)
{
    ProcessMulliganForHuman(game);
    ProcessMulliganForComputer(game);
}

void Console::ProcessMulliganForHuman(PlayMode::Game& game)
{
    std::cout << "Starting hand\n";
    std::cout << "Keep or Replace Cards\n\n";
    std::vector<int> p1Choices = game.GetPlayer1()->choice->choices;
    for (auto& choice : p1Choices)
    {
        PlayMode::Playable* playable = game.entityList[choice];
        ShowSimpleCardInfo(playable);
    }

    std::string indexStr;
    std::cout << "Choose card index to replace: ";
    std::cin.ignore(32767, '\n');
    std::getline(std::cin, indexStr);

    const std::vector<std::string> strIndices = SplitString(indexStr, " ");
    std::vector<int> intIndices;
    intIndices.reserve(strIndices.size());

    for (const auto& index : strIndices)
    {
        intIndices.emplace_back(
            p1Choices[std::strtol(index.c_str(), nullptr, 10)]);
    }

    PlayMode::Generic::ChoiceMulligan(game.GetPlayer1(), intIndices);

    std::cout << "Replaced Cards\n\n";
    for (auto& playable : game.GetPlayer1()->GetHandZone()->GetAll())
    {
        ShowSimpleCardInfo(playable);
    }
}

void Console::ProcessMulliganForComputer(PlayMode::Game& game)
{
    std::cout << "Starting hand\n";
    std::cout << "Keep or Replace Cards\n\n";
    std::vector<int> p2Choices = game.GetPlayer2()->choice->choices;
    for (auto& choice : p2Choices)
    {
        PlayMode::Playable* playable = game.entityList[choice];
        ShowSimpleCardInfo(playable);
    }

    const std::vector<int> intIndices =
        m_computerAgent->GetActionForMulligan(game);

    PlayMode::Generic::ChoiceMulligan(game.GetPlayer2(), intIndices);

    std::cout << "Replaced Cards\n\n";
    for (auto& playable : game.GetPlayer2()->GetHandZone()->GetAll())
    {
        ShowSimpleCardInfo(playable);
    }
}

void Console::ShowSimpleCardInfo(PlayMode::Playable* playable)
{
    std::cout << playable->card->name << " (" << playable->card->GetCost()
              << "): " << playable->card->text << '\n';
}
}  // namespace RosettaStone