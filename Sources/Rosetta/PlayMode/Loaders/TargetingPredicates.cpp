// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Loaders/TargetingPredicates.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
TargetingPredicate TargetingPredicates::ReqMurlocTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::MURLOC);
    };
}

TargetingPredicate TargetingPredicates::ReqDemonTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::DEMON);
    };
}

TargetingPredicate TargetingPredicates::ReqMechanicalTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::MECHANICAL);
    };
}

TargetingPredicate TargetingPredicates::ReqElementalTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::ELEMENTAL);
    };
}

TargetingPredicate TargetingPredicates::ReqBeastTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::BEAST);
    };
}

TargetingPredicate TargetingPredicates::ReqTotemTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::TOTEM);
    };
}

TargetingPredicate TargetingPredicates::ReqPirateTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::PIRATE);
    };
}

TargetingPredicate TargetingPredicates::ReqDragonTarget()
{
    return [](const Character* character) {
        return character->IsRace(Race::DRAGON);
    };
}

TargetingPredicate TargetingPredicates::ReqLackeyTarget()
{
    return
        [](const Character* character) { return character->card->IsLackey(); };
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
    return
        [](const Character* character) { return character->HasDeathrattle(); };
}

TargetingPredicate TargetingPredicates::ReqLegendaryTarget()
{
    return [](const Character* character) {
        return character->card->GetRarity() == Rarity::LEGENDARY;
    };
}

TargetingPredicate TargetingPredicates::ReqDamagedTarget()
{
    return
        [](const Character* character) { return character->GetDamage() > 0; };
}

TargetingPredicate TargetingPredicates::ReqDamagedTargetUnlessCombo()
{
    return [](const Character* character) {
        if (character->game->GetCurrentPlayer()->IsComboActive())
        {
            return true;
        }

        return character->GetDamage() > 0;
    };
}

TargetingPredicate TargetingPredicates::ReqUndamagedTarget()
{
    return
        [](const Character* character) { return character->GetDamage() == 0; };
}

TargetingPredicate TargetingPredicates::ReqTargetMaxAttack(int value)
{
    return [=](const Character* character) {
        return character->GetAttack() <= value;
    };
}

TargetingPredicate TargetingPredicates::ReqTargetMinAttack(int value)
{
    return [=](const Character* character) {
        return character->GetAttack() >= value;
    };
}

AvailabilityPredicate TargetingPredicates::ReqTargetForCombo()
{
    return [](const Player* player, [[maybe_unused]] Card* card) {
        return player->IsComboActive();
    };
}

TargetingPredicate TargetingPredicates::ReqMustTargetTaunter()
{
    return [](Character* character) {
        const auto minion = dynamic_cast<Minion*>(character);
        return minion && minion->HasTaunt();
    };
}

AvailabilityPredicate TargetingPredicates::MinimumFriendlySecrets(int value)
{
    return [=](const Player* player, [[maybe_unused]] Card* card) {
        return player->GetSecretZone()->GetCount() >= value;
    };
}

AvailabilityPredicate TargetingPredicates::ElementalPlayedLastTurn()
{
    return [=](const Player* player, [[maybe_unused]] Card* card) {
        return player->GetNumElementalPlayedLastTurn() > 0;
    };
}

AvailabilityPredicate TargetingPredicates::MaximumCardsInDeck(int value)
{
    return [=](const Player* player, [[maybe_unused]] Card* card) {
        return player->GetDeckZone()->GetCount() <= value;
    };
}

AvailabilityPredicate TargetingPredicates::DragonInHand()
{
    return [=](const Player* player, [[maybe_unused]] Card* card) {
        auto cards = player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::MINION &&
                       handCard->card->GetRace() == Race::DRAGON;
            });
    };
}
}  // namespace RosettaStone::PlayMode
