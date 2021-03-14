// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

#include <Rosetta/PlayMode/Decks/Deck.hpp>
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
            InputDeckCodes();
            break;
        case Mode::BATTLEGROUNDS:
            PlayBattlegrounds();
            break;
    }
}

void Console::InputDeckCodes()
{
    std::string deckCode1, deckCode2;

    std::cout << "Input first player's deck code: ";
    std::cin >> deckCode1;

    std::cout << "Input second player's deck code: ";
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
}

void Console::PlayBattlegrounds()
{
}
}  // namespace RosettaStone