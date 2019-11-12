// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Accounts/AccountInfo.hpp>
#include <Rosetta/Accounts/AccountInfo.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddAccountInfo(pybind11::module& m)
{
    pybind11::class_<AccountInfo>(m, "AccountInfo")
        .def(pybind11::init<>(), R"pbdoc(Constructs anonymous account.)pbdoc")
        .def(pybind11::init<std::string&&, std::string&&>())
        .def(
            pybind11::init<std::string&&, std::string&&,
                           std::vector<DeckInfo*>>(),
            R"pbdoc(Constructs account with given \p email and \p nickname.)pbdoc")
        .def("get_email", &AccountInfo::GetEmail,
             R"pbdoc(Returns e-mail address of account.)pbdoc")
        .def("get_nickname", &AccountInfo::GetNickname,
             R"pbdoc(Returns nickname of account.)pbdoc")
        .def("get_num_of_deck", &AccountInfo::GetNumOfDeck,
             R"pbdoc(Returns the number of decks.)pbdoc")
        .def("get_deck", &AccountInfo::GetDeck,
             R"pbdoc(Returns a pointer to deck at idx.

             Parameters
             ----------
             - idx : Index of decks.)pbdoc")
        .def("show_deck_list", &AccountInfo::ShowDeckList,
             R"pbdoc(Prints a list of decks.)pbdoc")
        .def("create_deck", &AccountInfo::CreateDeck,
             R"pbdoc(Creates a deck with given name and deckClass.

             Parameters
             ----------
             name : The name of deck.
             deck_class : The class of deck.)pbdoc")
        .def("delete_deck", &AccountInfo::DeleteDeck,
             R"pbdoc(Deletes a deck at idx.

             Parameters
             ----------
             idx : Index of decks.)pbdoc");
}
