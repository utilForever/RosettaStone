// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Loaders/AccountLoader.hpp>
#include <Rosetta/PlayMode/Loaders/AccountLoader.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone::PlayMode;

void AddAccountLoader(pybind11::module& m)
{
    pybind11::class_<AccountLoader>(
        m, "AccountLoader",
        R"pbdoc(This class loads/saves account data from/to <email>.json.)pbdoc")
        .def("load", &AccountLoader::Load,
             R"pbdoc(Loads account information from a json file named email.

             Parameters
             ----------
             email : The email address of the account.)pbdoc",
             pybind11::arg("email"))
        .def("save", &AccountLoader::Save,
             R"pbdoc(Saves account information p to a json file.

             Parameters
             ----------
             account : A pointer to account instance that stores information.)pbdoc",
             pybind11::arg("account"));
}