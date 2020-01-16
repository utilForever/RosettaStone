// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Accounts/AccountInfo.hpp>
#include <Python/Accounts/DeckInfo.hpp>

#include <Python/Cards/Card.hpp>
#include <Python/Cards/Cards.hpp>

#include <Python/Commons/Constants.hpp>
#include <Python/Commons/DeckCode.hpp>

#include <Python/Conditions/RelaCondition.hpp>
#include <Python/Conditions/SelfCondition.hpp>

#include <Python/Enums/ActionEnums.hpp>
#include <Python/Enums/AuraEnums.hpp>
#include <Python/Enums/CardEnums.hpp>
#include <Python/Enums/GameEnums.hpp>
#include <Python/Enums/TargetingEnums.hpp>
#include <Python/Enums/TaskEnums.hpp>
#include <Python/Enums/TriggerEnums.hpp>

#include <Python/Games/GameConfig.hpp>

#include <Python/Loaders/AccountLoader.hpp>
#include <Python/Loaders/InternalCardLoader.hpp>
#include <Python/Loaders/TargetingPredicates.hpp>

#include <Python/Managers/CostManager.hpp>

#include <pybind11/pybind11.h>

PYBIND11_MODULE(pyRosetta, m)
{
    m.doc() =
        R"pbdoc(Hearthstone simulator with some reinforcement learning)pbdoc";

    // Accounts
    AddAccountInfo(m);
    AddDeckInfo(m);

    // Cards
    AddCard(m);
    AddCards(m);

    // Commons
    AddConstants(m);
    AddDeckCode(m);

    // Conditions
    AddRelaCondition(m);
    AddSelfCondition(m);

    // Enums
    AddActionEnums(m);
    AddAuraEnums(m);
    AddCardEnums(m);
    AddGameEnums(m);
    AddTargetingEnums(m);
    AddTaskEnums(m);
    AddTriggerEnums(m);

    // Games
    AddGameConfig(m);

    // Loaders
    AddAccountLoader(m);
    AddInternalCardLoader(m);
    AddTargetingPredicates(m);

    // Managers
    AddCostManager(m);
}