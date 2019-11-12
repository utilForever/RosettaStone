// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Cards/Card.hpp>
#include <Rosetta/Cards/Card.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddCard(pybind11::module& m)
{
    pybind11::class_<Card>(
        static_cast<pybind11::handle>(m), "Card",
        R"pbdoc(This class stores card information such as attack, health and cost.)pbdoc")
        .def(pybind11::init<>(), R"pbdoc(Constructs Card class.)pbdoc")
        .def_readwrite("id", &Card::id, R"pbdoc(ID of the card.)pbdoc")
        .def_readwrite("name", &Card::name, R"pbdoc(Name of the card.)pbdoc")
        .def_readwrite("text", &Card::text, R"pbdoc(Text of the card.)pbdoc")
        .def_readwrite("game_tags", &Card::gameTags,
                       R"pbdoc(Game tags of the card.)pbdoc")
        .def_readwrite("play_reqs", &Card::playRequirements,
                       R"pbdoc(Play requirements of the card.)pbdoc")
        .def_readwrite("entourages", &Card::entourages,
                       R"pbdoc(Entourages of the card.)pbdoc")
        .def_readwrite("power", &Card::power, R"pbdoc(Power of the card.)pbdoc")
        .def_readwrite("max_allowed_in_deck", &Card::maxAllowedInDeck,
                       R"pbdoc(Maximum of card in deck.)pbdoc")
        .def("initialize", &Card::Initialize,
             R"pbdoc(Initializes card data.)pbdoc")
        .def("card_class", &Card::GetCardClass,
             R"pbdoc(Returns the value of card class.)pbdoc")
        .def("card_set", &Card::GetCardSet,
             R"pbdoc(Returns the value of card set.)pbdoc")
        .def("card_type", &Card::GetCardType,
             R"pbdoc(Returns the value of card set.)pbdoc")
        .def("faction", &Card::GetFaction,
             R"pbdoc(Returns the value of faction.)pbdoc")
        .def("race", &Card::GetRace, R"pbdoc(Returns the value of race.)pbdoc")
        .def("rarity", &Card::GetRarity,
             R"pbdoc(Returns the value of rarity.)pbdoc")
        .def("has_game_tag", &Card::HasGameTag,
             R"pbdoc(Finds out if this card has game tag.

             true if this card has game tag, and false otherwise.

             Parameters
             ----------
             - game_tag : The game tag of card.)pbdoc",
             pybind11::arg("game_tag"));
}