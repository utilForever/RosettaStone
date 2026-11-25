// Copyright (c) 2026 Chris Ohk

#include <Python/PlayMode/Agents/SelfPlaySample.hpp>
#include <Rosetta/Common/DefaultFloatEnvScope.hpp>
#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>

#include <pybind11/stl.h>

#include <cmath>
#include <numeric>
#include <string_view>
#include <utility>

namespace py = pybind11;
using RosettaStone::DefaultFloatEnvScope;
using namespace RosettaStone::PlayMode;

namespace
{
template <typename Row, typename Read>
void ReadRow(py::iterator entry, Row& row, Read read)
{
    const auto end = py::iterator::sentinel();

    for (std::size_t i = 0; i < row.size(); ++i, ++entry)
    {
        if (entry == end)
        {
            throw py::type_error("Self-play row is too short");
        }

        row[i] = read(*entry, i);
    }

    if (entry != end)
    {
        throw py::type_error("Self-play row is too long");
    }
}

void CheckScalar(py::handle value)
{
    if (PyFloat_CheckExact(value.ptr()) || PyLong_CheckExact(value.ptr()))
    {
        return;
    }

    if (!PyNumber_Check(value.ptr()) ||
        py::getattr(value, "ndim", py::int_(0)).cast<int>() != 0)
    {
        throw py::type_error("Self-play fields require numeric scalars");
    }

    const auto dtype = py::getattr(value, "dtype", py::none());
    const auto kind = py::getattr(dtype, "kind", py::none());

    if (PyComplex_Check(value.ptr()) ||
        (!kind.is_none() &&
         !std::string_view("biuf").contains(kind.cast<char>())) ||
        py::getattr(dtype, "is_complex", py::bool_(false)).cast<bool>())
    {
        throw py::type_error("Self-play fields require real scalars");
    }

    if (!kind.is_none() &&
        py::getattr(value, "mask", py::bool_(false)).cast<bool>())
    {
        throw py::value_error("Self-play fields cannot contain masked scalars");
    }
}

template <typename T>
T ReadInteger(py::handle value)
{
    CheckScalar(value);

    if (!PyIndex_Check(value.ptr()))
    {
        throw py::type_error(
            "Self-play observations and masks require integers");
    }

    const auto integer = PyLong_AsLongLong(value.ptr());

    if (integer == -1 && PyErr_Occurred())
    {
        throw py::error_already_set();
    }

    if (!std::in_range<T>(integer))
    {
        throw py::value_error("Self-play integer is out of range");
    }

    return static_cast<T>(integer);
}

double ReadReal(py::handle value)
{
    CheckScalar(value);

    const auto real = PyFloat_AsDouble(value.ptr());

    if (real == -1 && PyErr_Occurred())
    {
        throw py::error_already_set();
    }

    return real;
}

float ReadProbability(py::handle value, bool legal)
{
    const double number = ReadReal(value);
    const int maximum = legal ? 1 : 0;

    if (!(number >= 0 && number <= maximum) ||
        (!PyFloat_CheckExact(value.ptr()) && !PyLong_CheckExact(value.ptr()) &&
         !(value >= py::int_(0) && value <= py::int_(maximum))))
    {
        throw py::value_error("Invalid self-play probability for this action");
    }

    const auto rounded = static_cast<float>(number);

    if (PyFloat_CheckExact(value.ptr()) || number == rounded)
    {
        return rounded;
    }

    // Only double results at a float midpoint can round the wrong way.
    const bool upward = rounded < number;
    const auto adjacent = std::nextafter(rounded, upward ? 1.0f : 0.0f);

    if (number == std::midpoint<double>(rounded, adjacent))
    {
        py::object midpoint = py::float_(number);
        const auto fromFloat = py::getattr(value, "from_float", py::none());

        if (!fromFloat.is_none())
        {
            // Decimal contexts can forbid comparisons with floats.
            midpoint = fromFloat(midpoint);
        }

        if (upward ? value > midpoint : value < midpoint)
        {
            return adjacent;
        }
    }

    return rounded;
}

float ReadOutcome(py::handle value)
{
    const DefaultFloatEnvScope environment;
    const double number = ReadReal(value);

    if ((number != -1 && number != 0 && number != 1) ||
        !value.equal(py::int_(static_cast<int>(number))))
    {
        throw py::value_error("Self-play outcome must be -1, 0 or +1");
    }

    return static_cast<float>(number);
}
}  // namespace

void AddSelfPlaySample(py::module& m)
{
    m.def(
        "serialize_self_play_sample",
        [](py::handle observation, py::handle legalMask,
           py::handle policy, py::handle outcome) {
            SelfPlaySample sample;

            ReadRow(py::iter(observation), sample.observation,
                    [](py::handle value, std::size_t) {
                        return ReadInteger<std::int32_t>(value);
                    });
            ReadRow(py::iter(legalMask), sample.legalMask,
                    [](py::handle value, std::size_t) {
                        return ReadInteger<std::uint8_t>(value);
                    });
            ReadRow(py::iter(policy), sample.policyTarget,
                    [&sample](py::handle value, std::size_t i) {
                        const DefaultFloatEnvScope environment;
                        return ReadProbability(value, sample.legalMask[i] != 0);
                    });

            sample.outcome = ReadOutcome(outcome);
            return py::bytes(sample.Serialize());
        },
        py::arg("observation"), py::arg("legal_mask"), py::arg("policy_target"),
        py::arg("outcome"));
    m.def(
        "deserialize_self_play_sample",
        [](const py::bytes& data) {
            const auto sample = SelfPlaySample::Deserialize(data);
            return py::make_tuple(sample.observation, sample.legalMask,
                                  sample.policyTarget, sample.outcome);
        },
        py::arg("data"), py::call_guard<DefaultFloatEnvScope>());
}
