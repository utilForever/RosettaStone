// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Accounts/DeckInfo.hpp>
#include <Rosetta/PlayMode/Accounts/DeckInfo.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;
using namespace PlayMode;

void AddDeckInfo(pybind11::module& m)
{
    pybind11::class_<DeckInfo>(
        m, "DeckInfo",
        R"pbdoc(This class stores deck information that contains exactly 30 cards.)pbdoc")
        .def(pybind11::init<>(), R"pbdoc(Default constructor.)pbdoc")
        .def(pybind11::init<std::string, CardClass>(),
             R"pbdoc(Constructs deck with given name and deck_class.

             Parameters
             ----------
             name : The name of deck.
             deck_class : The class of deck.)pbdoc",
             pybind11::arg("name"), pybind11::arg("deck_class"))
        .def("name", &DeckInfo::GetName,
             R"pbdoc(Returns the name of deck.)pbdoc")
        .def("deck_class", &DeckInfo::GetClass,
             R"pbdoc(Returns the class of deck.)pbdoc")
        .def("num_of_cards", &DeckInfo::GetNumOfCards,
             R"pbdoc(Returns the number of cards in deck.)pbdoc")
        .def("unique_num_of_cards", &DeckInfo::GetUniqueNumOfCards,
             R"pbdoc(Returns the unique number of cards in deck.)pbdoc")
        .def("num_card_in_deck", &DeckInfo::GetNumCardInDeck,
             R"pbdoc(Returns the number of cards in deck that matches card_id.

             Parameters
             ----------
             card_id : The ID of the card.)pbdoc",
             pybind11::arg("card_id"))
        .def(
            "primitive_deck", &DeckInfo::GetPrimitiveDeck,
            R"pbdoc(Creates a deck from a list of pointers to cards to play game.)pbdoc")
        .def("card", &DeckInfo::GetCard,
             R"pbdoc(Returns card ID and the number of card at idx in deck.

             Parameters
             ----------
             idx : Index of cards in deck.)pbdoc",
             pybind11::arg("idx"))
        .def("show_card_list", &DeckInfo::ShowCardList,
             R"pbdoc(Prints card list in deck.)pbdoc")
        .def(
            "add_card", &DeckInfo::AddCard,
            R"pbdoc(Add card(s) to deck with given card_id and num_card_to_add.

            true if card(s) is added to deck successfully, and false otherwise.

            Parameters
            ----------
            card_id : The ID of the card to add to deck.
            num_card_to_add : The number of card to add to deck.)pbdoc",
            pybind11::arg("card_id"), pybind11::arg("num_cards_to_add"))
        .def(
            "delete_card", &DeckInfo::DeleteCard,
            R"pbdoc(Delete card(s) from deck with given card_id and num_card_to_delete.

            true if card(s) is deleted from deck successfully, and false otherwise.

            Parameters
            ----------
            card_id : The ID of the card to delete from deck.
            num_card_to_delete : The number of card to delete from deck.)pbdoc",
            pybind11::arg("card_id"), pybind11::arg("num_card_to_delete"))
        .def("card_ids", &DeckInfo::GetCardIDs,
             R"pbdoc(Returns a list of card IDs.)pbdoc");
}
