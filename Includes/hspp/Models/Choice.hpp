// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_CHOICE_HPP
#define HEARTHSTONEPP_CHOICE_HPP

namespace Hearthstonepp
{
//! The action type of choice.
enum class ChoiceAction
{
    HAND = 0,       //!< Hand.
};

//!
//! \brief Choice struct.
//!
//! This struct holds all configuration values to offer a choice of options.
//!
struct Choice
{
    ChoiceType choiceType;
    ChoiceAction choiceAction;

    std::vector<std::size_t> choices;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_CHOICE_HPP