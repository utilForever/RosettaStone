// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Cards/Cards.hpp>
#include <Rosetta/Cards/Cards.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCards(pybind11::module& m)
{
    pybind11::class_<SearchFilter>(m, "SearchFilter")
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

    pybind11::class_<Cards, std::unique_ptr<Cards, pybind11::nodelete>>(m, "Cards")
        .def_static("get_instance", &Cards::GetInstance, pybind11::return_value_policy::reference)
        .def_static("get_all_cards", &Cards::GetAllCards)
        .def_static("find_card_by_id", &Cards::FindCardByID)
        .def_static("find_card_by_dbf_id", &Cards::FindCardByDbfID)
        .def_static("find_card_by_rarity", &Cards::FindCardByRarity)
        .def_static("find_card_by_class", &Cards::FindCardByClass)
        .def_static("find_card_by_set", &Cards::FindCardBySet)
        .def_static("find_card_by_type", &Cards::FindCardByType)
        .def_static("find_card_by_race", &Cards::FindCardByRace)
        .def_static("find_card_by_name", &Cards::FindCardByName)
        .def_static("find_card_by_cost", &Cards::FindCardByCost)
        .def_static("find_card_by_attack", &Cards::FindCardByAttack)
        .def_static("find_Card_by_health", &Cards::FindCardByHealth)
        .def_static("find_card_by_spell_power", &Cards::FindCardBySpellPower)
        .def_static("find_card_by_game_tag", &Cards::FindCardByGameTag)
        .def_static("get_hero_card", &Cards::GetHeroCard)
        .def_static("get_default_hero_power", &Cards::GetDefaultHeroPower);
}
