// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Managers/CostManager.hpp>
#include <Rosetta/Managers/CostManager.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCostManager(pybind11::module& m)
{
    pybind11::class_<CostManager>(
        m, "CostManager",
        R"pbdoc(This class manages the cost of the card. It is affected by cost aura, adaptive effect and enchangment.)pbdoc")
        .def(pybind11::init<>())
        .def(
            "get_cost", &CostManager::GetCost,
            R"pbdoc(Calculates the value of the cost by considering the factors such as cost aura, adaptive effect and enchantment.

            The final value of the cost.

            Parameters
            ----------
            - cost : The original value of the cost.)pbdoc",
            pybind11::arg("cost"))
        .def("add_cost_aura", &CostManager::AddCostAura,
             R"pbdoc(Adds the aura that affects the cost.

             Parameters
             ----------
             - effect_op : The effect operator to affect the cost value.
             - value The value to affect the cost value.)pbdoc",
             pybind11::arg("effect_op"), pybind11::arg("value"))
        .def("remove_cost_aura", &CostManager::RemoveCostAura,
             R"pbdoc(Removes the aura that affects the cost.

             Parameters
             ----------
             - effect_op : The effect operator to affect the cost value.
             - value : The value to affect the cost value.)pbdoc",
             pybind11::arg("effect_op"), pybind11::arg("value"))
        .def("activate_adaptive_effect", &CostManager::ActivateAdaptiveEffect,
             R"pbdoc(Activates the adaptive effect that affects the cost.

             Parameters
             ----------
             - effect : The adaptive cost effect to change the cost value.)pbdoc",
             pybind11::arg("effect"))
        .def("update_adaptive_effect", &CostManager::UpdateAdaptiveEffect,
             R"pbdoc(Updates the adaptive effect that affects the cost.

             Parameters
             ----------
             - value : The value that affects the cost value to update.)pbdoc",
             pybind11::arg("value"))
        .def(
            "deactivate_adaptive_effect",
            &CostManager::DeactivateAdaptiveEffect,
            R"pbdoc(Deactivates the adaptive effect that affects the cost.)pbdoc")
        .def("add_cost_enchantment", &CostManager::AddCostEnchantment,
             R"pbdoc(Adds the enchantment that affects the cost.

             Parameters
             ----------
             - effect_op : The effect operator to affect the cost value.
             - value : The value to affect the cost value.)pbdoc");
}
