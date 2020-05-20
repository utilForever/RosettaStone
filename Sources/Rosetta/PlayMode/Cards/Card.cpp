// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <iostream>

namespace RosettaStone::PlayMode
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
            case PlayReq::REQ_STEADY_SHOT:
                mustHaveToTargetToPlay = true;
                needsTarget = true;
                break;
            case PlayReq::REQ_NONSELF_TARGET:
            case PlayReq::REQ_TARGET_IF_AVAILABLE:
            case PlayReq::REQ_DRAG_TO_PLAY:
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
            case PlayReq::REQ_MINION_OR_ENEMY_HERO:
                characterType = CharacterType::CHARACTERS_EXCEPT_HERO;
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
            case PlayReq::REQ_TARGET_WITH_DEATHRATTLE:
                targetingPredicate.emplace_back(
                    TargetingPredicates::ReqTargetWithDeathrattle());
                break;
            case PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS:
                needsTarget = true;
                targetingAvailabilityPredicate.emplace_back(
                    TargetingPredicates::MinimumFriendlySecrets(
                        requirement.second));
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
            case CharacterType::CHARACTERS_EXCEPT_HERO:
                targetingType = TargetingType::CHARACTERS_EXCEPT_HERO;
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

bool Card::IsQuest() const
{
    return HasGameTag(GameTag::QUEST);
}

bool Card::IsLackey() const
{
    if (id == "DAL_613" ||  // DAL_613: Faceless Lackey
        id == "DAL_614" ||  // DAL_614: Kobold Lackey
        id == "DAL_615" ||  // DAL_615: Witchy Lackey
        id == "DAL_739" ||  // DAL_739: Goblin Lackey
        id == "DAL_741" ||  // DAL_741: Ethereal Lackey
        id == "ULD_616" ||  // ULD_616: Titanic Lackey
        id == "DRG_052")    // DRG_052: Draconic Lackey
    {
        return true;
    }

    return false;
}

bool Card::IsTransformMinion() const
{
    // NOTE: Transformed minions list
    // EX1_165: Druid of the Claw -> OG_044a
    // BRM_010: Druid of the Flame -> OG_044b
    // AT_042: Druid of the Saber -> OG_044c
    // UNG_101: Shellshifter -> UNG_101t3
    // ICC_051: Druid of the Swarm -> ICC_051t3
    // GIL_188: Druid of the Scythe -> GIL_188t3
    // TRL_343: Wardruid Loti -> TRL_343et1
    // BT_136: Msshi'fn Prime -> BT_136tt3
    if (id == "EX1_165" || id == "BRM_010" || id == "AT_042" ||
        id == "UNG_101" || id == "ICC_051" || id == "GIL_188" ||
        id == "TRL_343" || id == "BT_136")
    {
        return true;
    }

    return false;
}

bool Card::IsGalakrond() const
{
    // NOTE: Galakrond hero card list
    // DRG_600: Galakrond, the Wretched
    // DRG_610: Galakrond, the Nightmare
    // DRG_620: Galakrond, the Tempest
    // DRG_650: Galakrond, the Unbreakable
    // DRG_660: Galakrond, the Unspeakable
    if (id == "DRG_600" || id == "DRG_600t2" || id == "DRG_600t3" ||
        id == "DRG_610" || id == "DRG_610t2" || id == "DRG_610t3" ||
        id == "DRG_620" || id == "DRG_620t2" || id == "DRG_620t3" ||
        id == "DRG_650" || id == "DRG_650t2" || id == "DRG_650t3" ||
        id == "DRG_660" || id == "DRG_660t2" || id == "DRG_660t3")
    {
        return true;
    }

    return false;
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

bool Card::IsPlayableByCardReq(Player* player) const
{
    for (auto& requirement : playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_NUM_MINION_SLOTS:
                if (player->GetFieldZone()->IsFull())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_WEAPON_EQUIPPED:
                if (!player->GetHero()->HasWeapon())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_MINIMUM_ENEMY_MINIONS:
            {
                const auto opField = player->opponent->GetFieldZone();
                if (opField->GetCount() < requirement.second)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY:
            {
                auto curField = player->GetFieldZone();
                std::size_t entourageCount = 0;

                for (auto& minion : curField->GetAll())
                {
                    for (auto& entourage : entourages)
                    {
                        if (minion->card->id == entourage)
                        {
                            ++entourageCount;
                        }
                    }
                }

                if (entourageCount == entourages.size())
                {
                    return false;
                }

                break;
            }
            case PlayReq::REQ_MINIMUM_TOTAL_MINIONS:
            {
                const int fieldCount =
                    player->GetFieldZone()->GetCount() +
                    player->opponent->GetFieldZone()->GetCount();
                if (fieldCount < requirement.second)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_FRIENDLY_MINION_DIED_THIS_GAME:
            {
                bool isExist = false;
                for (auto& playable : player->GetGraveyardZone()->GetAll())
                {
                    if (const auto minion = dynamic_cast<Minion*>(playable);
                        minion && minion->isDestroyed)
                    {
                        isExist = true;
                        break;
                    }
                }

                if (!isExist)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_SECRET_ZONE_CAP_FOR_NON_SECRET:
            {
                if (player->GetSecretZone()->IsFull())
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_HAND_NOT_FULL:
            {
                if (player->GetHandZone()->IsFull())
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME:
            {
                bool isExist = false;

                for (auto& playable : player->GetGraveyardZone()->GetAll())
                {
                    if (playable->card->GetCardType() == CardType::MINION &&
                        playable->HasDeathrattle() == true &&
                        playable->isDestroyed)
                    {
                        isExist = true;
                        break;
                    }
                }

                if (!isExist)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_MINION_TARGET:
            case PlayReq::REQ_ENEMY_TARGET:
            case PlayReq::REQ_NONSELF_TARGET:
            case PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS:
                break;
            default:
                break;
        }
    }

    return true;
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
        case TargetingType::CHARACTERS_EXCEPT_HERO:
            friendlyMinions = true;
            enemyMinions = true;
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
}  // namespace RosettaStone::PlayMode
