// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Games/Game.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Models/Enchantment.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddGame(pybind11::module& m)
{
    pybind11::class_<Game>(m, "Game")
        .def(pybind11::init<>())
        .def_readwrite("state", &Game::state)
        .def_readwrite("step", &Game::step)
        .def_readwrite("next_step", &Game::nextStep)
        .def_readwrite("task_queue", &Game::taskQueue)
        .def_readwrite("task_stack", &Game::taskStack)
        .def_readwrite("trigger_manager", &Game::triggerManager)
        .def_readwrite("current_event_data", &Game::currentEventData)
        .def_readwrite("auras", &Game::auras)
        .def_readwrite("triggers", &Game::triggers)
        .def_readwrite("one_turn_effects", &Game::oneTurnEffects)
        .def_readwrite("one_turn_effect_enchantments",
                       &Game::oneTurnEffectEchantments)
        .def_readwrite("summoned_minions", &Game::summonedMinions)
        .def_readwrite("dead_minions", &Game::deadMinions)
        .def("initialize", &Game::Initialize)
        .def("ref_copy_from", &Game::RefCopyFrom)
        .def("get_format_type", &Game::GetFormatType)
        .def("get_player1", (Player * (Game::*)()) & Game::GetPlayer1)
        .def("get_player1",
             (const Player* (Game::*)() const) & Game::GetPlayer1)
        .def("get_player2", (Player * (Game::*)()) & Game::GetPlayer2)
        .def("get_player2",
             (const Player* (Game::*)() const) & Game::GetPlayer2)
        .def("get_current_player",
             (Player * (Game::*)()) & Game::GetCurrentPlayer)
        .def("get_current_player",
             (const Player* (Game::*)() const) & Game::GetCurrentPlayer)
        .def("set_current_player", &Game::SetCurrentPlayer)
        .def("get_opponent_player",
             (Player * (Game::*)()) & Game::GetOpponentPlayer)
        .def("get_opponent_player",
             (const Player* (Game::*)() const) & Game::GetOpponentPlayer)
        .def("get_turn", &Game::GetTurn)
        .def("set_turn", &Game::SetTurn)
        .def("get_next_id", &Game::GetNextID)
        .def("get_next_oop", &Game::GetNextOOP)
        .def("begin_first", &Game::BeginFirst)
        .def("begin_shuffle", &Game::BeginShuffle)
        .def("begin_draw", &Game::BeginDraw)
        .def("begin_mulligan", &Game::BeginMulligan)
        .def("main_begin", &Game::MainBegin)
        .def("main_ready", &Game::MainReady)
        .def("main_start_triggers", &Game::MainStartTriggers)
        .def("main_resource", &Game::MainResource)
        .def("main_draw", &Game::MainDraw)
        .def("main_start", &Game::MainStart)
        .def("main_action", &Game::MainAction)
        .def("main_end", &Game::MainEnd)
        .def("main_cleanup", &Game::MainCleanUp)
        .def("main_next", &Game::MainNext)
        .def("final_wrap_up", &Game::FinalWrapUp)
        .def("final_game_over", &Game::FinalGameOver)
        .def("start", &Game::Start)
        .def("process_tasks", &Game::ProcessTasks)
        .def("process_destroy_and_update_aura",
             &Game::ProcessDestroyAndUpdateAura)
        .def("process_graveyard", &Game::ProcessGraveyard)
        .def("process",
             (std::tuple<PlayState, PlayState>(Game::*)(Player*, ITask*)) &
                 Game::Process)
        .def("process",
             (std::tuple<PlayState, PlayState>(Game::*)(Player*, ITask*)) &
                 Game::Process)
        .def("process_until", &Game::ProcessUntil)
        .def("perform_action", &Game::PerformAction)
        .def("create_view", &Game::CreateView);
}
