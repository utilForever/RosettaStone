// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_AURA_UPDATE_INSTRUCTION_HPP
#define ROSETTASTONE_PLAYMODE_AURA_UPDATE_INSTRUCTION_HPP

#include <Rosetta/Common/Enums/AuraEnums.hpp>

namespace RosettaStone::PlayMode
{
class Playable;

//!
//! \brief AuraUpdateInstruction struct.
//!
//! This struct stores source and instruction data for updating aura.
//!
struct AuraUpdateInstruction
{
    //! Default constructor.
    AuraUpdateInstruction() = default;

    //! Constructs aura update instruction with given \p _source and
    //! \p _instruction.
    //! \param _source The source entity.
    //! \param _instruction The instruction of the aura.
    explicit AuraUpdateInstruction(Playable* _source,
                                   AuraInstruction _instruction)
        : source(_source), instruction(_instruction)
    {
        // Do nothing
    }

    //! Constructs aura update instruction with given \p _instruction.
    //! \param _instruction The instruction of the aura.
    explicit AuraUpdateInstruction(AuraInstruction _instruction)
        : instruction(_instruction)
    {
        // Do nothing
    }

    //! Operator overloading: operator==.
    bool operator==(const AuraUpdateInstruction& other) const
    {
        return (source == other.source) && (instruction == other.instruction);
    }

    Playable* source = nullptr;
    AuraInstruction instruction = AuraInstruction::INVALID;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_AURA_UPDATE_INSTRUCTION_HPP
