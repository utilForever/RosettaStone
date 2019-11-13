// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Commons/DeckCode.hpp>
#include <Rosetta/Commons/DeckCode.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddDeckCode(pybind11::module& m)
{
    pybind11::class_<DeckCode>(m, "DeckCode")
        .def_static("decode", &DeckCode::Decode);
}
