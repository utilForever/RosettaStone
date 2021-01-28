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
    HERO,              //!< This type of aura affects the source's controller.
    HERO_POWER,        //!< This type of aura effects the power of the source's
                       //!< controller.
    ENEMY_HERO_POWER,  //!< This type of aura effects the power of the source's
                       //!< enemy controller.
    WEAPON,            //!< This type of aura affects the weapon of the source's
                       //!< controller.
    HAND,        //!< This type of aura affects all entities in the hand of the
                 //!< source's controller.
    ENEMY_HAND,  //!< This type of aura affects all entities in the hand of the
                 //!< opponent of the source's controller.
    HANDS,  //!< This type of aura affects all entities in the both player's
            //!< hand.
    FIELD_AND_HAND,  //!< This type of aura affects all friendly minions and
                     //!< entities in the hand of the source's controller.
    PLAYER,  //!< This type of aura only affects the player of the source of
             //!< the aura.
    ENEMY_PLAYER,  //!< This type of aura only affects the opponent player of
                   //!< the source of the aura.
    PLAYERS,       //!< This type of aura affects the both controllers.
};

//! \brief An enumerator for identifying instruction of aura update.
enum class AuraInstruction
{
    INVALID,
    ADD,
    ADD_ALL,
    REMOVE,
    REMOVE_ALL
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_ENUMS_HPP
