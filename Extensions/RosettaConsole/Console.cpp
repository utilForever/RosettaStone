// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

#include <iostream>

namespace RosettaStone
{
Console::Console(Mode mode) : m_mode{ mode }
{
    // Do nothing
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

    std::cout << "Input player 1 deck code: ";
    std::cin >> deckCode1;

    std::cout << "Input player 2 deck code: ";
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

    PlayMode::Game game{ gameConfig };
    game.Start();
}

void Console::PlayBattlegrounds()
{
}
}  // namespace RosettaStone