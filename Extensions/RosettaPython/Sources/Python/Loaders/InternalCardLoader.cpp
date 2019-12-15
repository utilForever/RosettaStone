// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Loaders/InternalCardLoader.hpp>
#include <Rosetta/Loaders/InternalCardLoader.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddInternalCardLoader(pybind11::module& m)
{
    pybind11::class_<InternalCardLoader>(
        m, "InternalCardLoader",
        R"pbdoc(This class loads internal card data from card data generators.)pbdoc")
        .def_static("load", InternalCardLoader::Load,
                    R"pbdoc(Loads internal card data from card data generators.

                    Parameters
                    ----------
                    cards : The data storage to store added cards with power and play requirements.)pbdoc",
                    pybind11::arg("cards"));
}
