// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Decks/Deck.hpp>
#include <Rosetta/PlayMode/Decks/Deck.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;
using namespace PlayMode;

void AddDeck(pybind11::module& m)
{
    pybind11::class_<Deck>(
        m, "Deck",
        R"pbdoc(This class stores deck information that contains exactly 30 cards.)pbdoc")
        .def(pybind11::init<>(), R"pbdoc(Default constructor.)pbdoc")
        .def(pybind11::init<FormatType, CardClass>(),
             R"pbdoc(Constructs deck with given format_type and deck_class.

             Parameters
             ----------
             format_type : The format type of deck.
             deck_class : The card class of deck.)pbdoc",
             pybind11::arg("format_type"), pybind11::arg("deck_class"))
        .def("format_type", &Deck::GetFormatType,
             R"pbdoc(Returns the format type of deck.)pbdoc")
        .def("deck_class", &Deck::GetClass,
             R"pbdoc(Returns the card class of deck.)pbdoc")
        .def("num_of_cards", &Deck::GetNumOfCards,
             R"pbdoc(Returns the number of cards in deck.)pbdoc")
        .def("unique_num_of_cards", &Deck::GetUniqueNumOfCards,
             R"pbdoc(Returns the unique number of cards in deck.)pbdoc")
        .def("num_card_in_deck", &Deck::GetNumCardInDeck,
             R"pbdoc(Returns the number of cards in deck that matches card_id.

             Parameters
             ----------
             card_id : The ID of the card.)pbdoc",
             pybind11::arg("card_id"))
        .def("card", &Deck::GetCard,
             R"pbdoc(Returns card ID and the number of card at idx in deck.

             Parameters
             ----------
             idx : Index of cards in deck.)pbdoc",
             pybind11::arg("idx"))
        .def(
            "cards", &Deck::GetCards,
            R"pbdoc(Creates a deck from a list of pointers to cards to play game.)pbdoc")
        .def(
            "add_card", &Deck::AddCard,
            R"pbdoc(Add card(s) to deck with given card_id and num_card_to_add.

            true if card(s) is added to deck successfully, and false otherwise.

            Parameters
            ----------
            card_id : The ID of the card to add to deck.
            num_card_to_add : The number of card to add to deck.)pbdoc",
            pybind11::arg("card_id"), pybind11::arg("num_cards_to_add"))
        .def(
            "delete_card", &Deck::DeleteCard,
            R"pbdoc(Delete card(s) from deck with given card_id and num_card_to_delete.

            true if card(s) is deleted from deck successfully, and false otherwise.

            Parameters
            ----------
            card_id : The ID of the card to delete from deck.
            num_card_to_delete : The number of card to delete from deck.)pbdoc",
            pybind11::arg("card_id"), pybind11::arg("num_card_to_delete"))
        .def("card_ids", &Deck::GetCardIDs,
             R"pbdoc(Returns a list of card IDs.)pbdoc");
}
