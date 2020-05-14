// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/Choices/InvalidChoice.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
std::size_t InvalidChoice::Get([[maybe_unused]] std::size_t idx)
{
    throw std::runtime_error("ActionChoices::Get() - Invalid Choice");
}

bool InvalidChoice::IsEmpty()
{
    throw std::runtime_error("ActionChoices::IsEmpty() - Invalid Choice");
}

std::size_t InvalidChoice::Size()
{
    throw std::runtime_error("ActionChoices::Size() - Invalid Choice");
}

void InvalidChoice::Begin()
{
    throw std::runtime_error("ActionChoices::Begin() - Invalid Choice");
}

std::size_t InvalidChoice::Get()
{
    throw std::runtime_error("ActionChoices::Get() - Invalid Choice");
}

void InvalidChoice::StepNext()
{
    throw std::runtime_error("ActionChoices::StepNext() - Invalid Choice");
}

bool InvalidChoice::IsEnd()
{
    throw std::runtime_error("ActionChoices::IsEnd() - Invalid Choice");
}
}  // namespace RosettaStone::PlayMode