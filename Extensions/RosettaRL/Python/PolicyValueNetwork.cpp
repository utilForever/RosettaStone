// Copyright (c) 2026 Chris Ohk

#include <torch/python.h>

#include <pybind11/stl/filesystem.h>

#include <RosettaRL/NativeTrainer.hpp>

#include <fstream>

namespace py = pybind11;
using namespace RosettaStone::RL;

PYBIND11_MODULE(pyRosettaRL, module)
{
    py::module_::import("torch");

    torch::python::bind_module<PolicyValueNetworkImpl>(module,
                                                       "PolicyValueNetwork")
        .def(py::init<>())
        .def("save_weights", &PolicyValueNetworkImpl::SaveWeights,
             py::arg("filename"))
        .def("load_weights", &PolicyValueNetworkImpl::LoadWeights,
             py::arg("filename"))
        .def("training_losses", &ComputeTrainingLosses, py::arg("predictions"),
             py::arg("policy_targets"), py::arg("outcomes"))
        .def("save_checkpoint", &SaveTrainingCheckpoint, py::arg("filename"));

    module.def(
        "load_training_batch",
        [](const std::filesystem::path& filename) {
            std::ifstream input(filename, std::ios::binary);
            TORCH_CHECK(input.is_open(),
                        "Cannot open training batch: ", filename);

            return ReadTrainingBatch(input);
        },
        py::arg("filename"));
}
