// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SELF_CONDITION_HPP
#define ROSETTASTONE_PLAYMODE_SELF_CONDITION_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <functional>

namespace RosettaStone::PlayMode
{
class Playable;

//!
//! \brief SelfCondition class.
//!
//! This class is a container for all conditions about the subject entity.
//!
class SelfCondition
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    explicit SelfCondition(std::function<bool(Playable*)> func);

    //! SelfCondition wrapper for checking it is current player.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsCurrentPlayer();

    //! SelfCondition wrapper for checking the entity is not start in deck.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotStartInDeck();

    //! SelfCondition wrapper for checking the deck zone is empty.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDeckEmpty();

    //! SelfCondition wrapper for checking the hero is Galakrond.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsGalakrondHero();

    //! SelfCondition wrapper for checking the hero power equals \p cardID.
    //! \param cardID The card ID of hero power.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHeroPowerCard(const std::string& cardID);

    //! SelfCondition wrapper for checking the card has Battlecry.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsBattlecryCard();

    //! SelfCondition wrapper for checking the entity is destroyed.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDead();

    //! SelfCondition wrapper for checking the entity is not destroyed.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotDead();

    //! SelfCondition wrapper for checking the entity is not immune.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotImmune();

    //! SelfCondition wrapper for checking the entity is not untouchable.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotUntouchable();

    //! SelfCondition wrapper for checking the field is full.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFieldFull();

    //! SelfCondition wrapper for checking the field is not full.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFieldNotFull();

    //! SelfCondition wrapper for checking the field is not empty.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFieldNotEmpty();

    //! SelfCondition wrapper for checking the opponent field is not full.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsOpFieldNotFull();

    //! SelfCondition wrapper for checking the entity is damaged.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDamaged();

    //! SelfCondition wrapper for checking the entity is undamaged.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsUndamaged();

    //! SelfCondition wrapper for checking the hero equips weapon.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsWeaponEquipped();

    //! SelfCondition wrapper for checking it is Treant.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsTreant();

    //! SelfCondition wrapper for checking race of entity is \p race.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsRace(Race race);

    //! SelfCondition wrapper for checking there is the entity
    //! with \p race in field zone.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingRace(Race race);

    //! SelfCondition wrapper for checking there is the entity
    //! with \p race in opponent's field zone.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsOpControllingRace(Race race);

    //! SelfCondition wrapper for checking the secret exists
    //! in the owner's secret zone.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingSecret();

    //! SelfCondition wrapper for checking there is the entity
    //! with Lackey in field zone.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingLackey();

    //! SelfCondition wrapper for checking the player has entity
    //! with \p race in hand zone.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHoldingRace(Race race);

    //! SelfCondition wrapper for checking the entity is another class card.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsAnotherClassCard();

    //! SelfCondition wrapper for checking the player has entity
    //! with another class in hand zone.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHoldingAnotherClassCard();

    //! SelfCondition wrapper for checking it's card ID is \p cardID.
    //! \param cardID The card ID.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsCardID(std::string_view cardID);

    //! SelfCondition wrapper for checking the entity is minion.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsMinion();

    //! SelfCondition wrapper for checking the entity is spell.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsSpell();

    //! SelfCondition wrapper for checking the entity is weapon.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsWeapon();

    //! SelfCondition wrapper for checking the entity is secret.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsSecret();

    //! SelfCondition wrapper for checking the entity is choose one card.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsChooseOneCard();

    //! SelfCondition wrapper for checking the entity is frozen.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFrozen();

    //! SelfCondition wrapper for checking the entity has rush.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasRush();

    //! SelfCondition wrapper for checking the entity has deathrattle.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasDeathrattle();

    //! SelfCondition wrapper for checking the entity has not stealth.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasNotStealth();

    //! SelfCondition wrapper for checking the entity has windfury.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasWindfury();

    //! SelfCondition wrapper for checking the entity has reborn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasReborn();

    //! SelfCondition wrapper for checking the player has spellpower.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasSpellPower();

    //! SelfCondition wrapper for checking the player has invoked twice.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasInvokedTwice();

    //! SelfCondition wrapper for checking the player has minion in hand.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasMinionInHand();

    //! SelfCondition wrapper for checking the card has overload.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsOverloadCard();

    //! SelfCondition wrapper for checking the card has combo.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsComboCard();

    //! SelfCondition wrapper for checking the entity attacks this turn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsAttackThisTurn();

    //! SelfCondition wrapper for checking the number of minions
    //! that played this turn.
    //! \param num The number of minions for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition MinionsPlayedThisTurn(int num);

    //! SelfCondition wrapper for checking the number of spells
    //! that played this turn.
    //! \param num The number of spells for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition SpellsPlayedThisTurn(int num);

    //! SelfCondition wrapper for checking the player don't play
    //! elemental minion in this turn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotPlayElementalMinionThisTurn();

    //! SelfCondition wrapper for checking the cost satisfies condition with
    //! \p value and \p relaSign.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsCost(int value, RelaSign relaSign = RelaSign::EQ);

    //! SelfCondition wrapper for checking there is the entity that satisfies
    //! condition with \p tag, \p value and \p relaSign.
    //! \param tag The game tag to check condition.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsTagValue(GameTag tag, int value,
                                    RelaSign relaSign = RelaSign::EQ);

    //! SelfCondition wrapper for checking the name of entity equals \p name.
    //! \param name The name of card to check condition.
    //! \param isEqual The flag to indicate that the condition for equality.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsName(const std::string& name, bool isEqual = true);

    //! SelfCondition wrapper for checking num in taskStack satisfy condition
    //! with \p value and \p relaSign.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \param index If index is 0, use num; If index is 1, use num1.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsStackNum(int value, RelaSign relaSign = RelaSign::EQ,
                                    int index = 0);

    //! SelfCondition wrapper for checking the health that satisfies
    //! condition with \p value and \p relaSign.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHealth(int value, RelaSign relaSign);

    //! SelfCondition wrapper for checking the entity has target.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasTarget();

    //! SelfCondition wrapper for checking it is proposed defender.
    //! \param cardType The type of the card to check.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsProposedDefender(CardType cardType);

    //! SelfCondition wrapper for checking the defender is dead.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDefenderDead();

    //! SelfCondition wrapper for checking the event source is friendly.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsEventSourceFriendly();

    //! SelfCondition wrapper for checking the event target is \p cardType.
    //! \param cardType The type of the card to check.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsEventTargetIs(CardType cardType);

    //! SelfCondition wrapper for checking it is a minion
    //! that is targeted by spell.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsSpellTargetingMinion();

    //! SelfCondition wrapper for checking the entity is in \p zone.
    //! \param zone The zone type to check.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsInZone(ZoneType zone);

    //! SelfCondition wrapper for checking it is enemy turn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsEnemyTurn();

    //! SelfCondition wrapper for checking my hero is undamaged in enemy turn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsMyHeroUndamagedEnemyTurn();

    //! SelfCondition wrapper for checking the player is overloaded.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsOverloaded();

    //! SelfCondition wrapper for checking the player's total mana is full.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsManaCrystalFull();

    //! SelfCondition wrapper for checking the player has unspent mana.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsUnspentMana();

    //! SelfCondition wrapper for checking it is no duplicate cards in deck.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNoDuplicateInDeck();

    //! SelfCondition wrapper for checking the player has no neutral cards
    //! in deck.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasNoNeutralCardsInDeck();

    //! SelfCondition wrapper for checking it is left- or right-most card
    //! in your hand.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsLeftOrRightMostCardInHand();

    //! SelfCondition wrapper for checking the hero don't have spell damage.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasNotSpellDamageOnHero();

    //! SelfCondition wrapper for checking the player has spell card
    //! that costs 5 or more in hand.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition Has5MoreCostSpellInHand();

    //! SelfCondition wrapper for checking the player casts a spell
    //! that costs (5) or more this turn.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition Cast5MoreCostSpellInThisTurn();

    //! SelfCondition wrapper for checking the threshold value.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition CheckThreshold(RelaSign relaSign);

    //! Evaluates condition using checking function.
    //! \param owner The owner entity.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Playable* owner) const;

 private:
    std::function<bool(Playable*)> m_func;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_SELF_CONDITION_HPP
