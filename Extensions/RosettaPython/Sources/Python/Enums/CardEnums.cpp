// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Enums/CardEnums.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCardEnums(pybind11::module& m)
{
    pybind11::enum_<CardClass>(m, "CardClass")
#define X(a) .value(#a, CardClass::a)
#include "Rosetta/Enums/CardClass.def"
#undef X
        ;

    pybind11::enum_<CardSet>(m, "CardSet")
#define X(a) .value(#a, CardSet::a)
#include "Rosetta/Enums/CardSet.def"
#undef X
        ;

    pybind11::enum_<CardType>(m, "CardType")
#define X(a) .value(#a, CardType::a)
#include "Rosetta/Enums/CardType.def"
#undef X
        ;

    pybind11::enum_<Faction>(m, "Faction")
#define X(a) .value(#a, Faction::a)
#include "Rosetta/Enums/Faction.def"
#undef X
        ;

    pybind11::enum_<GameTag>(m, "GameTag")
#define X(a) .value(#a, GameTag::a)
#include "Rosetta/Enums/GameTag.def"
#undef X
        ;

    pybind11::enum_<PlayReq>(m, "PlayReq")
#define X(a) .value(#a, PlayReq::a)
#include "Rosetta/Enums/PlayReq.def"
#undef X
        ;

    pybind11::enum_<Race>(m, "Race")
#define X(a) .value(#a, Race::a)
#include "Rosetta/Enums/Race.def"
#undef X
        ;

    pybind11::enum_<Rarity>(m, "Rarity")
#define X(a) .value(#a, Rarity::a)
#include "Rosetta/Enums/Rarity.def"
#undef X
        ;
}