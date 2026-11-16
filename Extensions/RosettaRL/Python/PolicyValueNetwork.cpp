// Copyright (c) 2026 Chris Ohk

#include <torch/python.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

namespace py = pybind11;
using RosettaStone::RL::PolicyValueNetworkImpl;

PYBIND11_MODULE(pyRosettaRL, module)
{
    py::module_::import("torch");

    torch::python::bind_module<PolicyValueNetworkImpl>(module,
                                                       "PolicyValueNetwork")
        .def(py::init<>())
        .def(
            "save_weights",
            [](const PolicyValueNetworkImpl& model,
               const std::filesystem::path::string_type& filename) {
                model.SaveWeights(filename);
            },
            py::arg("filename"))
        .def(
            "load_weights",
            [](PolicyValueNetworkImpl& model,
               const std::filesystem::path::string_type& filename) {
                model.LoadWeights(filename);
            },
            py::arg("filename"));
}
