// Copyright (c) 2026 Chris Ohk

#include <Python/PlayMode/Agents/SelfPlaySample.hpp>
#include <Rosetta/Common/DefaultFloatEnvScope.hpp>
#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>

#include <pybind11/stl.h>

namespace py = pybind11;
using RosettaStone::DefaultFloatEnvScope;
using namespace RosettaStone::PlayMode;

void AddSelfPlaySample(py::module& m)
{
    m.def(
        "deserialize_self_play_sample",
        [](const py::bytes& data) {
            const auto sample = SelfPlaySample::Deserialize(data);
            return py::make_tuple(sample.observation, sample.legalMask,
                                  sample.policyTarget, sample.outcome);
        },
        py::arg("data"), py::call_guard<DefaultFloatEnvScope>());
}
