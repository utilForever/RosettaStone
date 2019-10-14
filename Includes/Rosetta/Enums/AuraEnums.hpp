// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_AURA_ENUMS_HPP
#define ROSETTASTONE_AURA_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying aura type.
enum class AuraType
{
    INVALID,   //!< Invalid type.
    SELF,      //!< This type of aura only affects the source of the aura.
    ADJACENT,  //!< This type of aura affects the minions adjacent to the source
               //!< of the aura.
    FIELD,     //!< This type of aura affects all friendly minions.
    FIELD_EXCEPT_SOURCE,  //!< This type of aura affects all friendly minions
                          //!< except the source of the aura.
    WEAPON,   //!< This type of aura affects the weapon of the source's
              //!< controller.
    HAND,     //!< This type of aura affects all entities in the hand of the
              //!< source's controller.
    ADAPTIVE  //!< This type of aura is influenced by other factors in game.
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_ENUMS_HPP
