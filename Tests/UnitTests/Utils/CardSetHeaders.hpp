// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_UNIT_TESTS_CARD_SET_HEADERS_HPP
#define ROSETTASTONE_UNIT_TESTS_CARD_SET_HEADERS_HPP

#include <iostream>
#include <doctest.h>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

#endif  // ROSETTASTONE_UNIT_TESTS_CARD_SET_HEADERS_HPP
