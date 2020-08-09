// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

    if (costManager != nullptr)
    {
        return costManager->GetCost(value);
    }

    return value;
}

void Playable::SetCost(int cost)
{
    SetGameTag(GameTag::COST, cost);
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

bool Playable::HasLifesteal() const
{
    return GetGameTag(GameTag::LIFESTEAL) == 1;
}

bool Playable::IsEcho() const
{
    return GetGameTag(GameTag::ECHO) == 1;
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
        effect != nullptr)
    {
        effect->Remove();
    }
}

void Playable::Destroy()
{
    isDestroyed = true;
}

bool Playable::IsPlayable()
{
    return IsPlayableByPlayer() && IsPlayableByCardReq();
}

bool Playable::TargetingRequirements(Card* card, Character* target) const
{
    return card->TargetingRequirements(player, target);
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
    if (dynamic_cast<HeroPower*>(this) == nullptr &&
        GetZoneType() != ZoneType::HAND)
    {
        return false;
    }

    return true;
}

bool Playable::IsPlayableByCardReq() const
{
    // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
    // These cards can be targeting or non-targeting.
    if (card->dbfID == 52812)
    {
        const auto card1 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
        const auto card2 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

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

    if (!card->IsPlayableByCardReq(player))
    {
        return false;
    }

    if (card->mustHaveToTargetToPlay && !HasAnyValidPlayTargets(card))
    {
        return false;
    }

    return true;
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
    std::vector<Character*> validTargets = GetValidPlayTargets();
    if (validTargets.empty())
    {
        return nullptr;
    }

    const auto idx = Random::get<std::size_t>(0, validTargets.size() - 1);
    Character* randTarget = validTargets[idx];
    SetCardTarget(randTarget->GetGameTag(GameTag::ENTITY_ID));

    return randTarget;
}

bool Playable::IsValidPlayTarget(Character* target)
{
    if (target == nullptr)
    {
        // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
        // These cards can be targeting or non-targeting.
        if (card->dbfID == 52812)
        {
            const auto card1 = Cards::FindCardByDbfID(
                GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
            const auto card2 = Cards::FindCardByDbfID(
                GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

            if (card1->mustHaveToTargetToPlay || card2->mustHaveToTargetToPlay)
            {
                return false;
            }

            if (card1->targetingType == TargetingType::NONE &&
                card2->targetingType == TargetingType::NONE)
            {
                return true;
            }

            if (!HasAnyValidPlayTargets(card1) &&
                !HasAnyValidPlayTargets(card2))
            {
                return true;
            }
        }
        else
        {
            if (card->mustHaveToTargetToPlay)
            {
                return false;
            }

            if (card->targetingType == TargetingType::NONE)
            {
                return true;
            }

            if (!HasAnyValidPlayTargets(card))
            {
                return true;
            }
        }

        return false;
    }

    // NOTE: Card 'Drustvar Horror' (DAL_431t) has two generated spells.
    // These cards can be targeting or non-targeting.
    if (card->dbfID == 52812)
    {
        const auto card1 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1));
        const auto card2 =
            Cards::FindCardByDbfID(GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2));

        if (!CheckTargetingType(card1, target) &&
            !CheckTargetingType(card2, target))
        {
            return false;
        }

        if (TargetingRequirements(card1, target) &&
            TargetingRequirements(card2, target))
        {
            return true;
        }
    }
    else
    {
        if (!CheckTargetingType(card, target))
        {
            return false;
        }

        if (TargetingRequirements(card, target))
        {
            return true;
        }
    }

    return false;
}

bool Playable::HasAnyValidPlayTargets(Card* card) const
{
    bool friendlyMinions = false, enemyMinions = false;
    bool hero = false, enemyHero = false;

    switch (card->targetingType)
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
        for (auto& minion : player->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(card, minion))
            {
                return true;
            }
        }
    }

    if (enemyMinions)
    {
        for (auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(card, minion))
            {
                return true;
            }
        }
    }

    if (hero && TargetingRequirements(card, player->GetHero()))
    {
        return true;
    }

    if (enemyHero && TargetingRequirements(card, player->opponent->GetHero()))
    {
        return true;
    }

    return false;
}

bool Playable::CheckTargetingType(Card* card, Character* target)
{
    switch (card->targetingType)
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
            if (dynamic_cast<Hero*>(target) != nullptr ||
                (target && target->player != player))
            {
                return false;
            }
            break;
        case TargetingType::ENEMY_MINIONS:
            if (dynamic_cast<Hero*>(target) != nullptr ||
                (target && target->player == player))
            {
                return false;
            }
            break;
        case TargetingType::HEROES:
            if (dynamic_cast<Minion*>(target) != nullptr)
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
    // TODO: Remove code '56057' after the card 'Rising Winds' is implemented
    // TODO: Remove code '59542' after the card 'Runic Carvings' is implemented
    if (HasChooseOne() && (card->dbfID != 56057 && card->dbfID != 59542))
    {
        if (player->ChooseBoth() && !card->IsTransformMinion())
        {
            Playable* playable0 =
                GetFromCard(player, Cards::FindCardByID(card->chooseCardIDs[0]),
                            std::nullopt, player->GetSetasideZone());
            playable0->ActivateTask(type, target, chooseOne, this);
            Playable* playable1 =
                GetFromCard(player, Cards::FindCardByID(card->chooseCardIDs[1]),
                            std::nullopt, player->GetSetasideZone());
            playable1->ActivateTask(type, target, chooseOne, this);
            return;
        }

        if (!player->ChooseBoth() && chooseOne > 0)
        {
            Playable* playable = GetFromCard(
                player, Cards::FindCardByID(card->chooseCardIDs[chooseOne - 1]),
                std::nullopt, player->GetSetasideZone());
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
        default:
            throw std::invalid_argument(
                "Playable::ActivateTask() - Invalid power type");
    }

    if (tasks.empty() || tasks[0] == nullptr)
    {
        return;
    }

    for (auto& task : tasks)
    {
        std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(chooseBase == nullptr ? this : chooseBase);
        clonedTask->SetTarget(target);

        game->taskQueue.Enqueue(std::move(clonedTask));
    }
}
}  // namespace RosettaStone::PlayMode
