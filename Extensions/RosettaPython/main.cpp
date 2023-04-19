// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Cards/Card.hpp>
#include <Python/PlayMode/Cards/Cards.hpp>

#include <Python/PlayMode/Decks/Deck.hpp>

#include <Python/PlayMode/Enums/AuraEnums.hpp>
#include <Python/PlayMode/Enums/CardEnums.hpp>
#include <Python/PlayMode/Enums/GameEnums.hpp>
#include <Python/PlayMode/Enums/TargetingEnums.hpp>
#include <Python/PlayMode/Enums/TaskEnums.hpp>
#include <Python/PlayMode/Enums/TriggerEnums.hpp>

#include <Python/PlayMode/Loaders/InternalCardLoader.hpp>
#include <Python/PlayMode/Loaders/TargetingPredicates.hpp>

#include <Python/PlayMode/Utils/Constants.hpp>
#include <Python/PlayMode/Utils/DeckCode.hpp>

#include <pybind11/pybind11.h>

PYBIND11_MODULE(pyRosetta, m)
{
    m.doc() =
        R"pbdoc(Hearthstone simulator with some reinforcement learning)pbdoc";

    // Cards
    AddCard(m);
    AddCards(m);

    // Decks
    AddDeck(m);

    // Enums
    AddAuraEnums(m);
    AddCardEnums(m);
    AddGameEnums(m);
    AddTargetingEnums(m);
    AddTaskEnums(m);
    AddTriggerEnums(m);

    // Loaders
    AddInternalCardLoader(m);
    AddTargetingPredicates(m);

    // Utils
    AddConstants(m);
    AddDeckCode(m);
}