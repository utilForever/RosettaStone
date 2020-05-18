// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Accounts/AccountInfo.hpp>
#include <Rosetta/PlayMode/Accounts/AccountInfo.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone::PlayMode;

void AddAccountInfo(pybind11::module& m)
{
    pybind11::class_<AccountInfo>(m, "AccountInfo")
        .def(pybind11::init<>(), R"pbdoc(Constructs anonymous account.)pbdoc")
        .def(pybind11::init<std::string&&, std::string&&>(),
             R"pbdoc(Constructs account with given email and nickname.

             Parameters
             ----------
             email : E-mail address of account.
             nickname : Nickname of account.)pbdoc",
             pybind11::arg("email"), pybind11::arg("nickname"))
        .def(pybind11::init<std::string&&, std::string&&,
                            std::vector<DeckInfo*>>(),
             R"pbdoc(Constructs account with given email and nickname
             and fill deck list with decks.

             Parameters
             ----------
             email : E-mail address of account.
             nickname : Nickname of account.
             decks : A list of decks)pbdoc",
             pybind11::arg("email"), pybind11::arg("nickname"),
             pybind11::arg("decks"))
        .def("email", &AccountInfo::GetEmail,
             R"pbdoc(Returns e-mail address of account.)pbdoc")
        .def("nickname", &AccountInfo::GetNickname,
             R"pbdoc(Returns nickname of account.)pbdoc")
        .def("num_of_deck", &AccountInfo::GetNumOfDeck,
             R"pbdoc(Returns the number of decks.)pbdoc")
        .def("deck", &AccountInfo::GetDeck,
             R"pbdoc(Returns a pointer to deck at idx.

             Parameters
             ----------
             - idx : Index of decks.)pbdoc",
             pybind11::arg("idx"))
        .def("show_deck_list", &AccountInfo::ShowDeckList,
             R"pbdoc(Prints a list of decks.)pbdoc")
        .def("create_deck", &AccountInfo::CreateDeck,
             R"pbdoc(Creates a deck with given name and deckClass.

             true if deck is created successfully, and false otherwise.

             Parameters
             ----------
             name : The name of deck.
             deck_class : The class of deck.)pbdoc",
             pybind11::arg("name"), pybind11::arg("deck_class"))
        .def("delete_deck", &AccountInfo::DeleteDeck,
             R"pbdoc(Deletes a deck at idx.

             true if deck is deleted successfully, and false otherwise.

             Parameters
             ----------
             idx : Index of decks.)pbdoc",
             pybind11::arg("idx"));
}
