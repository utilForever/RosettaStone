// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode
{
Playable::Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags,
                   int _id)
    : Entity(_player->game, _card, std::move(_tags), _id)
{
    player = _player;
}

Playable::~Playable()
{
    delete ongoingEffect;
}

ZoneType Playable::GetZoneType() const
{
    return static_cast<ZoneType>(GetGameTag(GameTag::ZONE));
}

void Playable::SetZoneType(ZoneType type)
{
    SetGameTag(GameTag::ZONE, static_cast<int>(type));
}

int Playable::GetZonePosition() const
{
    return GetGameTag(GameTag::ZONE_POSITION) - 1;
}

void Playable::SetZonePosition(int value)
{
    SetGameTag(GameTag::ZONE_POSITION, value + 1);
}

int Playable::GetCost() const
{
    const int value =
        GetGameTag(GameTag::COST) < 0 ? 0 : GetGameTag(GameTag::COST);

    if (costManager)
    {
        return costManager->GetCost(value);
    }

    return value;
}

void Playable::SetCost(int cost)
{
    SetGameTag(GameTag::COST, cost);
}

int Playable::GetNumInfuse() const
{
    return GetGameTag(GameTag::INFUSE_COUNTER);
}

void Playable::IncreaseNumInfuse()
{
    const int val = GetGameTag(GameTag::INFUSE_COUNTER);
    SetGameTag(GameTag::INFUSE_COUNTER, val + 1);
}

bool Playable::IsExhausted() const
{
    // Consider windfury
    if (GetGameTag(GameTag::WINDFURY) == 1 &&
        GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) == 1)
    {
        return false;
    }

    // Consider charge
    if (GetGameTag(GameTag::CHARGE) == 1 &&
        GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) == 0)
    {
        return false;
    }

    return GetGameTag(GameTag::EXHAUSTED) == 1;
}

void Playable::SetExhausted(bool exhausted)
{
    SetGameTag(GameTag::EXHAUSTED, static_cast<int>(exhausted));
}

bool Playable::IsTransformed() const
{
    return static_cast<bool>(GetGameTag(GameTag::TRANSFORMED_FROM_CARD));
}

void Playable::SetTransformed(bool value)
{
    SetGameTag(GameTag::TRANSFORMED_FROM_CARD, static_cast<int>(value));
}

bool Playable::IsGoldenCard() const
{
    return static_cast<bool>(GetGameTag(GameTag::PREMIUM));
}

bool Playable::HasCombo() const
{
    return GetGameTag(GameTag::COMBO) == 1;
}

bool Playable::HasOverload() const
{
    return GetGameTag(GameTag::OVERLOAD) > 0;
}

int Playable::GetOverload() const
{
    return GetGameTag(GameTag::OVERLOAD);
}

bool Playable::HasBattlecry() const
{
    return GetGameTag(GameTag::BATTLECRY) == 1;
}

bool Playable::HasDeathrattle() const
{
    return GetGameTag(GameTag::DEATHRATTLE) == 1;
}

bool Playable::HasOutcast() const
{
    return GetGameTag(GameTag::OUTCAST) == 1;
}

bool Playable::HasChooseOne() const
{
    return GetGameTag(GameTag::CHOOSE_ONE) == 1;
}

bool Playable::HasDiscover() const
{
    return GetGameTag(GameTag::DISCOVER) == 1;
}

bool Playable::HasLifesteal() const
{
    return GetGameTag(GameTag::LIFESTEAL) == 1;
}

bool Playable::HasEcho() const
{
    return GetGameTag(GameTag::ECHO) == 1;
}

bool Playable::HasDormant() const
{
    return GetGameTag(GameTag::DORMANT) == 1;
}

bool Playable::HasSpellburst() const
{
    return GetGameTag(GameTag::SPELLBURST) == 1;
}

bool Playable::HasCorrupt() const
{
    return GetGameTag(GameTag::CORRUPT) == 1;
}

bool Playable::HasTradeable() const
{
    return GetGameTag(GameTag::TRADEABLE) == 1;
}

bool Playable::HasHonorableKill() const
{
    return GetGameTag(GameTag::HONORABLEKILL) == 1;
}

bool Playable::HasInfuse() const
{
    return GetGameTag(GameTag::INFUSE) == 1;
}

bool Playable::IsInfused() const
{
    return GetGameTag(GameTag::INFUSED) == 1;
}

bool Playable::CanActivateSpellburst() const
{
    if (!HasSpellburst())
    {
        return false;
    }

    if (const auto minion = dynamic_cast<const Minion*>(this); minion)
    {
        if (minion->isDestroyed || minion->IsSummoned() ||
            minion->IsTransformed() || minion->IsUntouchable())
        {
            return false;
        }
    }

    return true;
}

void Playable::ResetCost()
{
    costManager = nullptr;
    if (const auto iter = m_gameTags.find(GameTag::COST);
        iter != m_gameTags.end())
    {
        m_gameTags.erase(iter);
    }

    if (const auto effect = dynamic_cast<AdaptiveCostEffect*>(ongoingEffect);
        effect)
    {
        effect->Remove();
    }
}

void Playable::Destroy()
{
    isDestroyed = true;
}

bool Playable::TargetingRequirements(Card* _card, Character* target) const
{
    return _card->TargetingRequirements(player, target);
}

bool Playable::IsPlayableByPlayer()
{
    // Check if player has enough mana to play card
    if (player->GetRemainingMana() < GetCost())
    {
        return false;
    }

    // Check if player is on turn
    if (player != game->GetCurrentPlayer())
    {
        return false;
    }

    // Check if entity is in hand to be played
    if (!dynamic_cast<HeroPower*>(this) && GetZoneType() != ZoneType::HAND)
    {
        return false;
    }

    return true;
}

bool Playable::IsPlayableByCardReq(int chooseOne) const
{
    // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
    // These cards can be targeting or non-targeting.
    if (card->dbfID == 52812)
    {
        Card* card1 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
        Card* card2 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

        return IsPlayableByCardReqInternal(card1, card2);
    }

    if (HasChooseOne())
    {
        if (player->ChooseBoth())
        {
            Card* card1 = Cards::FindCardByID(card->chooseCardIDs[0]);
            Card* card2 = Cards::FindCardByID(card->chooseCardIDs[1]);

            return IsPlayableByCardReqInternal(card1, card2);
        }

        if (!player->ChooseBoth() && chooseOne > 0)
        {
            Card* chosenCard =
                Cards::FindCardByID(card->chooseCardIDs[chooseOne - 1]);

            return IsPlayableByCardReqInternal(chosenCard);
        }
    }

    return IsPlayableByCardReqInternal(card);
}

std::vector<Character*> Playable::GetValidPlayTargets() const
{
    // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
    // These cards can be targeting or non-targeting.
    if (card->dbfID == 52812)
    {
        const auto card1 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
        const auto card2 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

        auto targets1 = card1->GetValidPlayTargets(player);
        auto targets2 = card2->GetValidPlayTargets(player);

        std::vector<Character*> targets;
        targets.reserve(targets1.size() + targets2.size());

        for (auto& target : targets1)
        {
            targets.emplace_back(target);
        }
        for (auto& target : targets2)
        {
            targets.emplace_back(target);
        }

        return targets;
    }

    return card->GetValidPlayTargets(player);
}

Character* Playable::GetRandomValidTarget()
{
    const std::vector<Character*> validTargets = GetValidPlayTargets();
    if (validTargets.empty())
    {
        return nullptr;
    }

    const auto idx = Random::get<std::size_t>(0, validTargets.size() - 1);
    Character* randTarget = validTargets[idx];
    SetCardTarget(randTarget->GetGameTag(GameTag::ENTITY_ID));

    return randTarget;
}

bool Playable::IsValidPlayTarget(Character* target, int chooseOne) const
{
    if (target)
    {
        // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
        // These cards can be targeting or non-targeting.
        if (card->dbfID == 52812)
        {
            const auto card1 = Cards::FindCardByDbfID(
                GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
            const auto card2 = Cards::FindCardByDbfID(
                GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

            return IsValidPlayTargetInternal(target, card1, card2);
        }

        if (HasChooseOne())
        {
            if (player->ChooseBoth())
            {
                Card* card1 = Cards::FindCardByID(card->chooseCardIDs[0]);
                Card* card2 = Cards::FindCardByID(card->chooseCardIDs[1]);

                return IsValidPlayTargetInternal(target, card1, card2);
            }

            if (!player->ChooseBoth() && chooseOne > 0)
            {
                Card* chosenCard =
                    Cards::FindCardByID(card->chooseCardIDs[chooseOne - 1]);

                return IsValidPlayTargetInternal(target, chosenCard);
            }
        }

        return IsValidPlayTargetInternal(target, card);
    }

    // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
    // These cards can be targeting or non-targeting.
    if (card->dbfID == 52812)
    {
        const auto card1 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
        const auto card2 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

        return IsValidPlayTargetInternal(card1, card2);
    }

    if (HasChooseOne())
    {
        if (player->ChooseBoth())
        {
            Card* card1 = Cards::FindCardByID(card->chooseCardIDs[0]);
            Card* card2 = Cards::FindCardByID(card->chooseCardIDs[1]);

            return IsValidPlayTargetInternal(card1, card2);
        }

        if (!player->ChooseBoth() && chooseOne > 0)
        {
            Card* chosenCard =
                Cards::FindCardByID(card->chooseCardIDs[chooseOne - 1]);

            return IsValidPlayTargetInternal(chosenCard);
        }
    }

    return IsValidPlayTargetInternal(card);
}

bool Playable::HasAnyValidPlayTargets(Card* _card) const
{
    bool friendlyMinions = false, enemyMinions = false;
    bool hero = false, enemyHero = false;

    switch (_card->targetingType)
    {
        case TargetingType::NONE:
            return false;
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
        for (const auto& minion : player->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(_card, minion))
            {
                return true;
            }
        }
    }

    if (enemyMinions)
    {
        for (const auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(_card, minion))
            {
                return true;
            }
        }
    }

    if (hero && TargetingRequirements(_card, player->GetHero()))
    {
        return true;
    }

    if (enemyHero && TargetingRequirements(_card, player->opponent->GetHero()))
    {
        return true;
    }

    return false;
}

bool Playable::CheckTargetingType(const Card* _card, Character* target) const
{
    switch (_card->targetingType)
    {
        case TargetingType::NONE:
            return false;
        case TargetingType::ALL:
            break;
        case TargetingType::CHARACTERS_EXCEPT_HERO:
            if (const auto hero = dynamic_cast<Hero*>(target);
                hero && hero->player == player)
            {
                return false;
            }
            break;
        case TargetingType::FRIENDLY_CHARACTERS:
            if (target && target->player != player)
            {
                return false;
            }
            break;
        case TargetingType::ENEMY_CHARACTERS:
            if (target && target->player == player)
            {
                return false;
            }
            break;
        case TargetingType::ALL_MINIONS:
            if (const auto hero = dynamic_cast<Hero*>(target); hero)
            {
                return false;
            }
            break;
        case TargetingType::FRIENDLY_MINIONS:
            if (dynamic_cast<Hero*>(target) ||
                (target && target->player != player))
            {
                return false;
            }
            break;
        case TargetingType::ENEMY_MINIONS:
            if (dynamic_cast<Hero*>(target) ||
                (target && target->player == player))
            {
                return false;
            }
            break;
        case TargetingType::HEROES:
            if (dynamic_cast<Minion*>(target))
            {
                return false;
            }
            break;
    }

    return true;
}

void Playable::ActivateTask(PowerType type, Character* target, int chooseOne,
                            Playable* chooseBase)
{
    if (HasChooseOne())
    {
        if (player->ChooseBoth() && !card->IsTransformMinion())
        {
            if (card->chooseCardIDs.empty())
            {
                return;
            }

            Playable* playable0 =
                GetFromCard(player, Cards::FindCardByID(card->chooseCardIDs[0]),
                            std::nullopt, player->GetSetasideZone());

            // Check card has overload
            if (playable0->HasOverload())
            {
                const int amount = playable0->GetOverload();
                player->SetOverloadOwed(player->GetOverloadOwed() + amount);
            }

            playable0->ActivateTask(type, target, chooseOne, this);

            Playable* playable1 =
                GetFromCard(player, Cards::FindCardByID(card->chooseCardIDs[1]),
                            std::nullopt, player->GetSetasideZone());

            // Check card has overload
            if (playable1->HasOverload())
            {
                const int amount = playable1->GetOverload();
                player->SetOverloadOwed(player->GetOverloadOwed() + amount);
            }

            playable1->ActivateTask(type, target, chooseOne, this);

            return;
        }

        if (!player->ChooseBoth() && chooseOne > 0)
        {
            if (card->chooseCardIDs.empty())
            {
                return;
            }

            Playable* playable = GetFromCard(
                player, Cards::FindCardByID(card->chooseCardIDs[chooseOne - 1]),
                std::nullopt, player->GetSetasideZone());

            // Check card has overload
            if (playable->HasOverload())
            {
                const int amount = playable->GetOverload();
                player->SetOverloadOwed(player->GetOverloadOwed() + amount);
            }

            playable->ActivateTask(type, target, chooseOne, this);

            return;
        }
    }

    std::vector<std::shared_ptr<ITask>> tasks;
    switch (type)
    {
        case PowerType::POWER:
            tasks = card->power.GetPowerTask();
            break;
        case PowerType::DEATHRATTLE:
            tasks = card->power.GetDeathrattleTask();
            break;
        case PowerType::COMBO:
            tasks = card->power.GetComboTask();
            break;
        case PowerType::OUTCAST:
            tasks = card->power.GetOutcastTask();
            break;
        case PowerType::SPELLBURST:
            tasks = card->power.GetSpellburstTask();
            break;
        case PowerType::FRENZY:
            tasks = card->power.GetFrenzyTask();
            break;
        case PowerType::HONORABLE_KILL:
            tasks = card->power.GetHonorableKillTask();
            break;
        default:
            throw std::invalid_argument(
                "Playable::ActivateTask() - Invalid power type");
    }

    for (const auto& task : tasks)
    {
        if (!task)
        {
            continue;
        }

        std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(chooseBase ? chooseBase : this);
        clonedTask->SetTarget(target);

        game->taskQueue.Enqueue(std::move(clonedTask));
    }
}

bool Playable::IsPlayableByCardReqInternal(Card* _card) const
{
    if (!_card->IsPlayableByCardReq(player))
    {
        return false;
    }

    if (_card->mustHaveToTargetToPlay && !HasAnyValidPlayTargets(_card))
    {
        return false;
    }

    return true;
}

bool Playable::IsPlayableByCardReqInternal(Card* card1, Card* card2) const
{
    if (!card1->IsPlayableByCardReq(player) ||
        !card2->IsPlayableByCardReq(player))
    {
        return false;
    }

    if ((card1->mustHaveToTargetToPlay && !HasAnyValidPlayTargets(card1)) ||
        (card2->mustHaveToTargetToPlay && !HasAnyValidPlayTargets(card2)))
    {
        return false;
    }

    return true;
}

bool Playable::IsValidPlayTargetInternal(Card* _card) const
{
    if (_card->mustHaveToTargetToPlay)
    {
        return false;
    }

    if (_card->targetingType == TargetingType::NONE)
    {
        return true;
    }

    for (auto& predicate : _card->targetingAvailabilityPredicate)
    {
        if (!predicate(player, _card))
        {
            return true;
        }
    }

    if (!HasAnyValidPlayTargets(_card))
    {
        return true;
    }

    return false;
}

bool Playable::IsValidPlayTargetInternal(Card* card1, Card* card2) const
{
    if (card1->mustHaveToTargetToPlay && card2->mustHaveToTargetToPlay)
    {
        return false;
    }

    if (card1->targetingType == TargetingType::NONE &&
        card2->targetingType == TargetingType::NONE)
    {
        return true;
    }

    bool check1 = false, check2 = false;

    for (auto& predicate : card1->targetingAvailabilityPredicate)
    {
        if (!predicate(player, card1))
        {
            check1 = true;
        }
    }

    for (auto& predicate : card2->targetingAvailabilityPredicate)
    {
        if (!predicate(player, card2))
        {
            check2 = true;
        }
    }

    if (check1 && check2)
    {
        return true;
    }

    if (!HasAnyValidPlayTargets(card1) && !HasAnyValidPlayTargets(card2))
    {
        return true;
    }

    return false;
}

bool Playable::IsValidPlayTargetInternal(Character* target, Card* _card) const
{
    if (!CheckTargetingType(_card, target))
    {
        return false;
    }

    for (auto& predicate : _card->targetingAvailabilityPredicate)
    {
        if (!predicate(player, _card))
        {
            return false;
        }
    }

    if (TargetingRequirements(_card, target))
    {
        return true;
    }

    return false;
}

bool Playable::IsValidPlayTargetInternal(Character* target, Card* card1,
                                         Card* card2) const
{
    if (!CheckTargetingType(card1, target) &&
        !CheckTargetingType(card2, target))
    {
        return false;
    }

    bool check1 = false, check2 = false;

    for (auto& predicate : card1->targetingAvailabilityPredicate)
    {
        if (!predicate(player, card1))
        {
            check1 = true;
        }
    }

    for (auto& predicate : card2->targetingAvailabilityPredicate)
    {
        if (!predicate(player, card2))
        {
            check2 = true;
        }
    }

    if (check1 && check2)
    {
        return true;
    }

    if (TargetingRequirements(card1, target) &&
        TargetingRequirements(card2, target))
    {
        return true;
    }

    return false;
}
}  // namespace RosettaStone::PlayMode
