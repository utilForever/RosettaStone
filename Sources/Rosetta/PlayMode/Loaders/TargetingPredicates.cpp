// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Loaders/TargetingPredicates.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
TargetingPredicate TargetingPredicates::ReqMurlocTarget()
{
    return [](Character* character) { return character->IsRace(Race::MURLOC); };
}

TargetingPredicate TargetingPredicates::ReqDemonTarget()
{
    return [](Character* character) { return character->IsRace(Race::DEMON); };
}

TargetingPredicate TargetingPredicates::ReqMechanicalTarget()
{
    return [](Character* character) {
        return character->IsRace(Race::MECHANICAL);
    };
}

TargetingPredicate TargetingPredicates::ReqElementalTarget()
{
    return
        [](Character* character) { return character->IsRace(Race::ELEMENTAL); };
}

TargetingPredicate TargetingPredicates::ReqBeastTarget()
{
    return [](Character* character) { return character->IsRace(Race::BEAST); };
}

TargetingPredicate TargetingPredicates::ReqTotemTarget()
{
    return [](Character* character) { return character->IsRace(Race::TOTEM); };
}

TargetingPredicate TargetingPredicates::ReqPirateTarget()
{
    return [](Character* character) { return character->IsRace(Race::PIRATE); };
}

TargetingPredicate TargetingPredicates::ReqDragonTarget()
{
    return [](Character* character) { return character->IsRace(Race::DRAGON); };
}

TargetingPredicate TargetingPredicates::ReqTargetWithRace(Race race)
{
    switch (race)
    {
        case Race::MURLOC:
            return ReqMurlocTarget();
        case Race::DEMON:
            return ReqDemonTarget();
        case Race::MECHANICAL:
            return ReqMechanicalTarget();
        case Race::ELEMENTAL:
            return ReqElementalTarget();
        case Race::BEAST:
            return ReqBeastTarget();
        case Race::TOTEM:
            return ReqTotemTarget();
        case Race::PIRATE:
            return ReqPirateTarget();
        case Race::DRAGON:
            return ReqDragonTarget();
        case Race::UNDEAD:
        case Race::EGG:
            return []([[maybe_unused]] Character* character) { return true; };
        default:
            throw std::invalid_argument(
                "TargetingPredicates::ReqTargetWithRace() - "
                "Race is not implemented!");
    }
}

TargetingPredicate TargetingPredicates::ReqTargetWithDeathrattle()
{
    return [=](Character* character) { return character->HasDeathrattle(); };
}

TargetingPredicate TargetingPredicates::ReqDamagedTarget()
{
    return [=](Character* character) { return character->GetDamage() > 0; };
}

TargetingPredicate TargetingPredicates::ReqUndamagedTarget()
{
    return [=](Character* character) { return character->GetDamage() == 0; };
}

TargetingPredicate TargetingPredicates::ReqTargetMaxAttack(int value)
{
    return
        [=](Character* character) { return character->GetAttack() <= value; };
}

TargetingPredicate TargetingPredicates::ReqTargetMinAttack(int value)
{
    return
        [=](Character* character) { return character->GetAttack() >= value; };
}

AvailabilityPredicate TargetingPredicates::ReqTargetForCombo()
{
    return [](Player* player, [[maybe_unused]] Card* card) {
        return player->IsComboActive();
    };
}

TargetingPredicate TargetingPredicates::ReqMustTargetTaunter()
{
    return [=](Character* character) {
        const auto minion = dynamic_cast<Minion*>(character);
        return minion && minion->HasTaunt();
    };
}

AvailabilityPredicate TargetingPredicates::MinimumFriendlySecrets(int value)
{
    return [=](Player* player, [[maybe_unused]] Card* card) {
        return player->GetSecretZone()->GetCount() >= value;
    };
}

}  // namespace RosettaStone::PlayMode
