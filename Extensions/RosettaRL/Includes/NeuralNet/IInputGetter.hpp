// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_IINPUT_GETTER_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_IINPUT_GETTER_HPP

#include <NeuralNet/FieldEnums.hpp>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief IInputGetter class.
//!
//! This class is interface of input getter that contains GetField() method.
//!
class IInputGetter
{
 public:
    //! Default virtual destructor.
    virtual ~IInputGetter() = default;

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    virtual double GetField(FieldSide fieldSide, FieldType fieldType,
                            int arg = 0) const = 0;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_IINPUT_GETTER_HPP