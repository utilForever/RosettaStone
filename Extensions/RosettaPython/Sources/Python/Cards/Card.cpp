// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Cards/Card.hpp>
#include <Rosetta/Cards/Card.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCard(pybind11::module& m)
{
    pybind11::class_<Card>(
        static_cast<pybind11::handle>(m), "Card",
        R"pbdoc(This class stores card information such as attack, health and cost.)pbdoc")
        .def_readwrite("id", &Card::id, R"pbdoc(ID of the card.)pbdoc")
        .def_readwrite("name", &Card::name, R"pbdoc(Name of the card.)pbdoc")
        .def_readwrite("text", &Card::text, R"pbdoc(Text of the card.)pbdoc")
        .def_readwrite("gameTags", &Card::gameTags,
                       R"pbdoc(Game tags of the card.)pbdoc")
        .def_readwrite("playReqs", &Card::playRequirements,
                       R"pbdoc(Play requirements of the card.)pbdoc")
        .def_readwrite("entourages", &Card::entourages,
                       R"pbdoc(Entourages of the card.)pbdoc")
        .def_readwrite("power", &Card::power, R"pbdoc(Power of the card.)pbdoc")
        .def_readwrite("maxAllowedInDeck", &Card::maxAllowedInDeck,
                       "Maximum of card in deck.)pbdoc");
}