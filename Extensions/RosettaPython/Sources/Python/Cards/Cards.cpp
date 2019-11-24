// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Cards/Cards.hpp>
#include <Rosetta/Cards/Cards.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>
#include <pybind11/functional.h>

using namespace RosettaStone;

void AddCards(pybind11::module& m)
{
    pybind11::class_<SearchFilter>(
        m, "SearchFilter",
        R"pbdoc(This structure stores the filter value for searching the card.)pbdoc")
        .def_readwrite("rarity", &SearchFilter::rarity)
        .def_readwrite("player_class", &SearchFilter::playerClass)
        .def_readwrite("card_type", &SearchFilter::cardType)
        .def_readwrite("race", &SearchFilter::race)
        .def_readwrite("game_tag", &SearchFilter::gameTag)
        .def_readwrite("name", &SearchFilter::name)
        .def_readwrite("cost_min", &SearchFilter::costMin)
        .def_readwrite("cost_max", &SearchFilter::costMax)
        .def_readwrite("attack_min", &SearchFilter::attackMin)
        .def_readwrite("attack_max", &SearchFilter::attackMax)
        .def_readwrite("health_min", &SearchFilter::healthMin)
        .def_readwrite("health_max", &SearchFilter::healthMax);

    pybind11::class_<Cards, std::unique_ptr<Cards, pybind11::nodelete>>(
        m, "Cards",
        R"pbdoc(This class stores a list of cards and provides several search methods.)pbdoc")
        .def_static("get_instance", &Cards::GetInstance,
					pybind11::return_value_policy::reference,
                    R"pbdoc(Returns an instance of Cards class.)pbdoc")
        .def_static("get_all_cards", &Cards::GetAllCards,
                    R"pbdoc(Returns a list of all cards.)pbdoc")
        .def_static("find_card_by_id", &Cards::FindCardByID,
                    R"pbdoc(Returns a card that matches id.

                    Parameters
                    ----------
                    id : The ID of the card.)pbdoc")
        .def_static("find_card_by_dbf_id", &Cards::FindCardByDbfID,
                    R"pbdoc(Returns a card that matches dbf_id.

                    Parameters
                    ----------
                    dbf_id : The dbfID of the card.)pbdoc")
        .def_static("find_card_by_rarity", &Cards::FindCardByRarity,
                    R"pbdoc(Returns a list of cards that matches rarity.

                    Parameters
                    ----------
                    rarity : The rarity of the card.)pbdoc")
        .def_static("find_card_by_class", &Cards::FindCardByClass,
                    R"pbdoc(Returns a list of cards that matches card_class.

                    Parameters
                    ----------
                    class_class : The class of the card.)pbdoc")
        .def_static("find_card_by_set", &Cards::FindCardBySet,
                    R"pbdoc(Returns a list of cards that matches card_set.

                    Parameters
                    ----------
                    card_set : The set of the card.)pbdoc")
        .def_static("find_card_by_type", &Cards::FindCardByType,
                    R"pbdoc(Returns a list of cards that matches card_type.

                    Parameters
                    ----------
                    card_type : The type of the card.)pbdoc")
        .def_static("find_card_by_race", &Cards::FindCardByRace,
                    R"pbdoc(Returns a list of cards that matches race.

                    Parameters
                    ----------
                    race : The race of the card.)pbdoc")
        .def_static("find_card_by_name", &Cards::FindCardByName,
                    R"pbdoc(Returns a card that matches name.

                    Parameters
                    ----------
                    name : The name of the card.)pbdoc")
        .def_static(
            "find_card_by_cost", &Cards::FindCardByCost,
            R"pbdoc(Returns a list of cards whose cost is between min_val and max_val.

                    Parameters
                    ----------
                    min_val : The minimum cost value of the card.
                    max_val : The maximum cost value of the card.)pbdoc")
        .def_static(
            "find_card_by_attack", &Cards::FindCardByAttack,
            R"pbdoc(Returns a list of cards whose cost is between min_val and max_val.

                    Parameters
                    ----------
                    min_val : The minimum cost value of the card.
                    max_val : The maximum cost value of the card.)pbdoc")
        .def_static(
            "find_card_by_health", &Cards::FindCardByHealth,
            R"pbdoc(Returns a list of cards whose health is between min_val and max_val.

                    Parameters
                    ----------
                    min_val : The minimum health value of the card.
                    max_val : The maximum health value of the card.)pbdoc")
        .def_static(
            "find_card_by_spell_power", &Cards::FindCardBySpellPower,
            R"pbdoc(Returns a list of cards whose spell power is between min_val and max_val

                    Parameters
                    ----------
                    min_val : The minimum spell power value of the card.
                    max_val : The maximum spell power value of the card.)pbdoc")
        .def_static("find_card_by_game_tag", &Cards::FindCardByGameTag,
                    R"pbdoc(Returns a list of cards that has game_tags.

                    Parameters
                    ----------
                    game_tags : A list of game tag of the card.)pbdoc")
        .def_static("get_hero_card", &Cards::GetHeroCard,
                    R"pbdoc(Returns a hero card that matches card_class.

                    Parameters
                    ----------
                    card_class : The class of the card.)pbdoc")
        .def_static(
            "get_default_hero_power", &Cards::GetDefaultHeroPower,
            R"pbdoc(Returns a default hero power card that matches card_class.

                    Parameters
                    ----------
                    card_class : The class of the card.)pbdoc");
}
