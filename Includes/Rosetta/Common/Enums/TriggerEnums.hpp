// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_ENUMS_HPP
#define ROSETTASTONE_TRIGGER_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying trigger type.
enum class TriggerType
{
    NONE,        //!< The effect has nothing.
    TURN_START,  //!< The effect will be triggered at the start of turn.
    TURN_END,    //!< The effect will be triggered at the end of turn.
    ADD_CARD,    //!< The effect will be triggered when a card is added in hand.
    DRAW_CARD,   //!< The effect will be triggered when a card is drawn.
    PLAY_CARD,   //!< The effect will be triggered when a player plays a card.
    AFTER_PLAY_CARD,  //!< The effect will be triggered after a card is played.
    CAST_SPELL,  //!< The effect will be triggered when a player plays a Spell
                 //!< card.
    AFTER_CAST,  //!< The effect will be triggered after a spell is played.
    SECRET_REVEALED,  //!< The effect will be triggered when a secret is
                      //!< activated.
    ZONE,  //!< The effect will be triggered when an entity enters any types of
           //!< zone.
    GIVE_HEAL,     //!< The effect will be triggered when a playable heals a
                   //!< character.
    TAKE_HEAL,     //!< The effect will be triggered when a character is healed.
    ATTACK,        //!< The effect will be triggered when characters attack.
    AFTER_ATTACK,  //!< The effect will be triggered after an attack action is
                   //!< ended.
    AFTER_ATTACKED,  //!< The effect will be triggered after a character is
                     //!< attacked.
    SUMMON,  //!< The effect will be triggered whenever a minion is summoned.
    AFTER_SUMMON,  //!< The effect will be triggered after a minion is summoned.
    PLAY_MINION,  //!< The effect will be triggered when a player plays a Minion
                  //!< card.
    AFTER_PLAY_MINION,  //!< The effect will be triggered after a minion is
                        //!< played.
    DEAL_DAMAGE,  //!< The effect will be triggered when a spell or a character
                  //!< deals damages to source.
    TAKE_DAMAGE,  //!< The effect will be triggered when a character is damaged.
    PREDAMAGE,    //!< The effect will be triggered when a character gets
                //!< predamage. This event happens just before the character is
                //!< actually damaged.
    TARGET,  //!< The effect will be triggered when a card is targeted by an
             //!< attacking minion or a played card.
    DEATH,   //!< The effect will be triggered when a minion dies.
    USE_HERO_POWER,  //!< The effect will be triggered when a hero uses power.
    SHUFFLE_INTO_DECK,  //!< The effect will be triggered when a card is
                        //!< shuffled into a deck.
    MULTI_TRIGGER,      //!< The effect for multi trigger.
};

//! \brief An enumerator for identifying trigger source.
enum class TriggerSource
{
    NONE,
    SELF,
    ENEMY,
    HERO,
    ALL_MINIONS,
    MINIONS,
    MINIONS_EXCEPT_SELF,
    ENEMY_MINIONS,
    ENCHANTMENT_TARGET,
    ENEMY_SPELLS,
    FRIENDLY,
    FRIENDLY_EVENT_SOURCE,
};

//! \brief An enumerator for identifying trigger activation.
enum class TriggerActivation
{
    PLAY,
    HAND,
    DECK,
    HAND_OR_PLAY
};

//! \brief An enumerator for identifying sequence type.
enum class SequenceType
{
    NONE,
    PLAY_CARD,
    PLAY_MINION,
    PLAY_SPELL,
    TARGET
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_ENUMS_HPP
