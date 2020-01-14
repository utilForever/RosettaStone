// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <iostream>

namespace RosettaStone
{
void Card::Initialize()
{
    maxAllowedInDeck = (GetRarity() == Rarity::LEGENDARY) ? 1 : 2;

    bool needsTarget = false;
    CharacterType characterType = CharacterType::CHARACTERS;
    FriendlyType friendlyType = FriendlyType::ALL;

    for (auto& requirement : playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_TARGET_TO_PLAY:
                mustHaveToTargetToPlay = true;
                needsTarget = true;
                break;
            case PlayReq::REQ_NONSELF_TARGET:
            case PlayReq::REQ_TARGET_IF_AVAILABLE:
                needsTarget = true;
                break;
            case PlayReq::REQ_MINION_TARGET:
                characterType = CharacterType::MINIONS;
                break;
            case PlayReq::REQ_FRIENDLY_TARGET:
                friendlyType = FriendlyType::FRIENDLY;
                break;
            case PlayReq::REQ_ENEMY_TARGET:
                friendlyType = FriendlyType::ENEMY;
                break;
            case PlayReq::REQ_HERO_TARGET:
                characterType = CharacterType::HEROES;
                break;
            case PlayReq::REQ_DAMAGED_TARGET:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqDamagedTarget());
                break;
            case PlayReq::REQ_UNDAMAGED_TARGET:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqUndamagedTarget());
                break;
            case PlayReq::REQ_TARGET_MAX_ATTACK:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqTargetMaxAttack(
                        requirement.second));
                break;
            case PlayReq::REQ_TARGET_MIN_ATTACK:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqTargetMinAttack(
                        requirement.second));
                break;
            case PlayReq::REQ_TARGET_WITH_RACE:
            {
                Race race = static_cast<Race>(requirement.second);

                // NOTE: Race::EGG has special value that is not 27, but 38.
                if (requirement.second == 38)
                {
                    race = Race::EGG;
                }

                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqTargetWithRace(race));
            }
            break;
            case PlayReq::REQ_TARGET_FOR_COMBO:
                needsTarget = true;
                targetingAvailabilityPredicate.emplace_back(
                    TargetingPredicates::ReqTargetForCombo());
                break;
            case PlayReq::REQ_MUST_TARGET_TAUNTER:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqMustTargetTaunter());
                break;
            default:
                continue;
        }
    }

    if (needsTarget)
    {
        switch (characterType)
        {
            case CharacterType::CHARACTERS:
                switch (friendlyType)
                {
                    case FriendlyType::ALL:
                        targetingType = TargetingType::ALL;
                        break;
                    case FriendlyType::FRIENDLY:
                        targetingType = TargetingType::FRIENDLY_CHARACTERS;
                        break;
                    case FriendlyType::ENEMY:
                        targetingType = TargetingType::ENEMY_CHARACTERS;
                        break;
                }
                break;
            case CharacterType::HEROES:
                targetingType = TargetingType::HEROES;
                break;
            case CharacterType::MINIONS:
                switch (friendlyType)
                {
                    case FriendlyType::ALL:
                        targetingType = TargetingType::ALL_MINIONS;
                        break;
                    case FriendlyType::FRIENDLY:
                        targetingType = TargetingType::FRIENDLY_MINIONS;
                        break;
                    case FriendlyType::ENEMY:
                        targetingType = TargetingType::ENEMY_MINIONS;
                        break;
                }
        }
    }
}

void Card::RefCopy(const Card& rhs)
{
    id = rhs.id;
    dbfID = rhs.dbfID;
    name = rhs.name;
    text = rhs.text;

    gameTags = rhs.gameTags;
    playRequirements = rhs.playRequirements;
    entourages = rhs.entourages;

    targetingPredicate = rhs.targetingPredicate;
    targetingAvailabilityPredicate = rhs.targetingAvailabilityPredicate;

    targetingType = rhs.targetingType;
    power.RefCopy(rhs.power);

    maxAllowedInDeck = rhs.maxAllowedInDeck;
    mustHaveToTargetToPlay = rhs.mustHaveToTargetToPlay;
}

CardClass Card::GetCardClass() const
{
    return static_cast<CardClass>(gameTags.at(GameTag::CLASS));
}

CardSet Card::GetCardSet() const
{
    return static_cast<CardSet>(gameTags.at(GameTag::CARD_SET));
}

CardType Card::GetCardType() const
{
    return static_cast<CardType>(gameTags.at(GameTag::CARDTYPE));
}

Faction Card::GetFaction() const
{
    return static_cast<Faction>(gameTags.at(GameTag::FACTION));
}

Race Card::GetRace() const
{
    return static_cast<Race>(gameTags.at(GameTag::CARDRACE));
}

Rarity Card::GetRarity() const
{
    return static_cast<Rarity>(gameTags.at(GameTag::RARITY));
}

int Card::GetCost() const
{
    return gameTags.at(GameTag::COST);
}

bool Card::HasGameTag(GameTag gameTag) const
{
    return gameTags.find(gameTag) != gameTags.end();
}

bool Card::IsUntouchable() const
{
    return HasGameTag(GameTag::UNTOUCHABLE) &&
           static_cast<bool>(gameTags.at(GameTag::UNTOUCHABLE));
}

bool Card::IsSecret() const
{
    return HasGameTag(GameTag::SECRET) &&
           static_cast<bool>(gameTags.at(GameTag::SECRET));
}

bool Card::IsCollectible() const
{
    return static_cast<bool>(gameTags.at(GameTag::COLLECTIBLE));
}

bool Card::IsStandardSet() const
{
    for (auto& cardSet : STANDARD_CARD_SETS)
    {
        if (GetCardSet() == cardSet)
        {
            return true;
        }
    }

    return false;
}

bool Card::IsWildSet() const
{
    for (auto& cardSet : WILD_CARD_SETS)
    {
        if (GetCardSet() == cardSet)
        {
            return true;
        }
    }

    return false;
}

std::size_t Card::GetMaxAllowedInDeck() const
{
    return maxAllowedInDeck;
}

bool Card::TargetingRequirements(Player* player, Character* target)
{
    if (target->card->IsUntouchable())
    {
        return false;
    }

    if ((target->HasStealth() || target->IsImmune()) &&
        target->player != player)
    {
        return false;
    }

    if (!targetingPredicate.empty())
    {
        for (auto& predicate : targetingPredicate)
        {
            if (!predicate(target))
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<Character*> Card::GetValidPlayTargets(Player* player)
{
    std::vector<Character*> ret;

    if (!targetingAvailabilityPredicate.empty())
    {
        for (auto& predicate : targetingAvailabilityPredicate)
        {
            if (!predicate(player, this))
            {
                return ret;
            }
        }
    }

    bool friendlyMinions = false, enemyMinions = false;
    bool hero = false, enemyHero = false;

    switch (targetingType)
    {
        case TargetingType::NONE:
            // If this is a non-targeting card, return an empty list
            return ret;
        case TargetingType::ALL:
            friendlyMinions = true;
            enemyMinions = true;
            hero = true;
            enemyHero = true;
            break;
        case TargetingType::FRIENDLY_CHARACTERS:
            friendlyMinions = true;
            hero = true;
            break;
        case TargetingType::ENEMY_CHARACTERS:
            enemyMinions = true;
            enemyHero = true;
            break;
        case TargetingType::ALL_MINIONS:
            friendlyMinions = true;
            enemyMinions = true;
            break;
        case TargetingType::FRIENDLY_MINIONS:
            friendlyMinions = true;
            break;
        case TargetingType::ENEMY_MINIONS:
            enemyMinions = true;
            break;
        case TargetingType::HEROES:
            hero = true;
            enemyHero = true;
            break;
    }

    if (friendlyMinions)
    {
        for (auto& minion : player->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(player, minion))
            {
                ret.emplace_back(minion);
            }
        }
    }

    if (enemyMinions)
    {
        for (auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(player, minion))
            {
                ret.emplace_back(minion);
            }
        }
    }

    if (hero)
    {
        if (TargetingRequirements(player, player->GetHero()))
        {
            ret.emplace_back(player->GetHero());
        }
    }

    if (enemyHero)
    {
        if (TargetingRequirements(player, player->opponent->GetHero()))
        {
            ret.emplace_back(player->opponent->GetHero());
        }
    }

    return ret;
}

void Card::ShowBriefInfo() const
{
    std::cout << name.c_str() << " (" << id.c_str() << ") ";
}

void Card::ShowInfo() const
{
    std::cout << "ID: " << id.c_str() << '\n';
    std::cout << "dbfID: " << dbfID << '\n';
    std::cout << "Name: " << name.c_str() << '\n';
    std::cout << "Text: " << text.c_str() << '\n';
    std::cout << "Rarity: " << EnumToStr<Rarity>(GetRarity()) << '\n';
    std::cout << "Faction: " << EnumToStr<Faction>(GetFaction()) << '\n';
    std::cout << "CardSet: " << EnumToStr<CardSet>(GetCardSet()) << '\n';
    std::cout << "CardClass: " << EnumToStr<CardClass>(GetCardClass()) << '\n';
    std::cout << "CardType: " << EnumToStr<CardType>(GetCardType()) << '\n';
    std::cout << "Race: " << EnumToStr<Race>(GetRace()) << '\n';
}
}  // namespace RosettaStone
