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

    const py::object modelType = module.attr("PolicyValueNetwork");
    const py::object init = modelType.attr("__init__");

    modelType.attr("__init__") = py::cpp_function(
        [init](const py::object& self, py::args args, py::kwargs kwargs) {
            init(self, *args, **kwargs);

            // ModuleWrapper shadows nn.Module methods on each instance.
            const py::object pop = self.attr("__dict__").attr("pop");

            for (const char* name : { "parameters", "named_parameters" })
            {
                pop(name, py::none());
            }
        },
        py::is_method(modelType));

    const py::object namedParameters = modelType.attr("named_parameters");

    modelType.attr("named_parameters") = py::cpp_function(
        [namedParameters](const py::object& self, py::args args,
                          py::kwargs kwargs) {
            // The C++ binding accepted recurse as a lone positional flag.
            if (args.size() == 1 && kwargs.empty() &&
                py::isinstance<py::bool_>(args[0]))
            {
                return namedParameters(self, py::arg("recurse") = args[0]);
            }

            return namedParameters(self, *args, **kwargs);
        },
        py::name("named_parameters"), py::is_method(modelType));

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
