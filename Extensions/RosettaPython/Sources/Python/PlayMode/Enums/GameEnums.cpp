// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/GameEnums.hpp>
#include <Rosetta/Common/Enums/GameEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone::PlayMode;

void AddGameEnums(pybind11::module& m)
{
    pybind11::enum_<PlayerType>(
        m, "PlayerType",
        R"pbdoc(An enumerator for identifying the player.)pbdoc")
        .value("INVALID", PlayerType::INVALID,
               R"pbdoc(The invalid player.)pbdoc")
        .value("RANDOM", PlayerType::RANDOM, R"pbdoc(The random player.)pbdoc")
        .value("PLAYER1", PlayerType::PLAYER1, R"pbdoc(The first player.)pbdoc")
        .value("PLAYER2", PlayerType::PLAYER2,
               R"pbdoc(The second player.)pbdoc");
}
