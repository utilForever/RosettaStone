// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Loaders/PowerLoader.hpp>
#include <Rosetta/Loaders/PowerLoader.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddPowerLoader(pybind11::module& m)
{
    pybind11::class_<PowerLoader>(
        m, "PowerLoader",
        R"pbdoc(This class loads power data from card data generators.)pbdoc")
        .def_static("load", PowerLoader::Load,
             R"pbdoc(Loads power data from card data generators.

             Parameters
             ----------
             cards : Data storage to store added cards with power.)pbdoc", pybind11::arg("cards"));
}
