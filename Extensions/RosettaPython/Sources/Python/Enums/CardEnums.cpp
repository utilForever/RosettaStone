// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Enums/CardEnums.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCardEnums(pybind11::module& m)
{
    pybind11::enum_<GameTag>(m, "GameTag")
#define X(a) .value(#a, GameTag::a)
#include "Rosetta/Enums/GameTag.def"
#undef X
        ;
}