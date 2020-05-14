// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_ACTION_CHOICES_HPP
#define ROSETTASTONE_PLAYMODE_ACTION_CHOICES_HPP

#include <Rosetta/PlayMode/Actions/Choices/ChooseFromCardIDs.hpp>
#include <Rosetta/PlayMode/Actions/Choices/ChooseFromNumbers.hpp>
#include <Rosetta/PlayMode/Actions/Choices/InvalidChoice.hpp>

#include <cstddef>
#include <variant>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief ActionChoices class.
//!
//! This class contains several choice methods for the action such as
//! invalid choice, choose from numeric range or a list of card IDs.
//!
class ActionChoices
{
 public:
    //! Constructs action choices and initializes item to invalid choice.
    ActionChoices();

    //! Constructs action choices and initializes item to choose from numbers.
    //! \param max The maximum value of the range.
    explicit ActionChoices(std::size_t max);

    //! Constructs action choices and initializes item to choose from cardIDs.
    //! \param cardIDs A list of card IDs.
    explicit ActionChoices(const std::vector<std::size_t>& cardIDs);

    //! Checks if a variant currently holds a given type.
    //! \return The flag that indicates whether a variant currently holds
    //! a given type.
    template <class T>
    bool CheckType() const
    {
        return std::holds_alternative<T>(m_item);
    }

    //! Compares this object and \p rhs as \p comparator function.
    //! \param rhs ActionChoices object to compare.
    //! \param comparator The function to use for comparison.
    //! \return The result of \p comparator function.
    template <class Comparator>
    bool Compare(const ActionChoices& rhs, Comparator&& comparator) const
    {
        return std::visit(
            [&](auto&& arg1, auto&& arg2) -> bool {
                return comparator(std::forward<decltype(arg1)>(arg1),
                                  std::forward<decltype(arg2)>(arg2));
            },
            m_item, rhs.m_item);
    }

    //! Returns the zero-based index of the alternative held by the variant.
    //! \return The zero-based index of the alternative held by the variant.
    std::size_t GetIndex() const;

    //! Returns the action choice at \p idx.
    //! \param idx The index of action choices.
    //! \return The action choice at \p idx.
    std::size_t Get(std::size_t idx) const;

    //! Returns the flag indicates that action choices are empty.
    //! \return The flag indicates that action choices are empty.
    bool IsEmpty() const;

    //! Returns the number of action choices.
    //! \return The number of action choices.
    std::size_t Size() const;

    //! Initializes iterator variable.
    void Begin();

    //! Returns the element that iterator variable points to.
    //! \return The element that iterator variable points to.
    std::size_t Get() const;

    //! Processes iterator to point to the next element.
    void StepNext();

    //! Returns the flag indicates that iterator is in the end position.
    //! \return the flag indicates that iterator is in the end position.
    bool IsEnd() const;

 private:
    using ItemType =
        std::variant<InvalidChoice, ChooseFromNumbers, ChooseFromCardIDs>;

    ItemType m_item;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACTION_CHOICES_HPP
