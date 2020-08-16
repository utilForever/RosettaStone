// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Character.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone::PlayMode
{
Character::Character(Player* player, Card* card, std::map<GameTag, int> tags,
                     int id)
    : Playable(player, card, std::move(tags), id)
{
    // Do nothing
}

int Character::GetAttack() const
{
    const int value = GetGameTag(GameTag::ATK);

    return value < 0 ? 0 : value;
}

void Character::SetAttack(int attack)
{
    SetGameTag(GameTag::ATK, attack);
}

int Character::GetPreDamage() const
{
    return GetGameTag(GameTag::PREDAMAGE);
}

void Character::SetPreDamage(int preDamage)
{
    SetGameTag(GameTag::PREDAMAGE, preDamage);
}

int Character::GetDamage() const
{
    return GetGameTag(GameTag::DAMAGE);
}

void Character::SetDamage(int damage)
{
    if (damage < 0)
    {
        damage = 0;
    }
    else if (GetGameTag(GameTag::HEALTH) <= damage)
    {
        Destroy();
    }

    SetGameTag(GameTag::DAMAGE, damage);
}

int Character::GetHealth() const
{
    return GetMaxHealth() - GetGameTag(GameTag::DAMAGE);
}

void Character::SetHealth(int health)
{
    if (health == 0)
    {
        Destroy();
    }

    SetGameTag(GameTag::HEALTH, health);
    SetGameTag(GameTag::DAMAGE, 0);
}

int Character::GetMaxHealth() const
{
    return GetGameTag(GameTag::HEALTH);
}

void Character::SetMaxHealth(int maxHealth)
{
    SetGameTag(GameTag::HEALTH, maxHealth);
}

int Character::GetSpellPower() const
{
    return GetGameTag(GameTag::SPELLPOWER);
}

void Character::SetSpellPower(int spellPower)
{
    SetGameTag(GameTag::SPELLPOWER, spellPower);
}

int Character::GetNumAttacksThisTurn() const
{
    return GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN);
}

void Character::SetNumAttacksThisTurn(int amount)
{
    SetGameTag(GameTag::NUM_ATTACKS_THIS_TURN, amount);
}

bool Character::IsRace(Race race) const
{
    return race == card->GetRace();
}

bool Character::IsImmune() const
{
    return static_cast<bool>(GetGameTag(GameTag::IMMUNE));
}

bool Character::IsFrozen() const
{
    return static_cast<bool>(GetGameTag(GameTag::FROZEN));
}

bool Character::HasStealth() const
{
    return static_cast<bool>(GetGameTag(GameTag::STEALTH));
}

bool Character::HasWindfury() const
{
    return static_cast<bool>(GetGameTag(GameTag::WINDFURY));
}

bool Character::HasMegaWindfury() const
{
    return static_cast<bool>(GetGameTag(GameTag::MEGA_WINDFURY)) ||
           player->playerAuraEffects.GetValue(GameTag::MEGA_WINDFURY) > 0;
}

bool Character::CanAttack() const
{
    //! If the current player is opponent, returns false
    if (player != game->GetCurrentPlayer())
    {
        return false;
    }

    // If the value of attack is 0, returns false
    if (GetAttack() == 0)
    {
        return false;
    }

    // If the character is frozen, returns false
    if (IsFrozen())
    {
        return false;
    }

    // If the character is exhausted, returns false
    if (IsExhausted())
    {
        return false;
    }

    //! If the character can't attack, returns false
    if (CantAttack())
    {
        return false;
    }

    return true;
}

bool Character::CantAttack() const
{
    return static_cast<bool>(GetGameTag(GameTag::CANT_ATTACK));
}

bool Character::CantAttackHeroes() const
{
    return static_cast<bool>(GetGameTag(GameTag::CANNOT_ATTACK_HEROES));
}

bool Character::IsValidAttackTarget(Player* opponent, Character* target) const
{
    auto targets = GetValidAttackTargets(opponent);
    if (std::find(targets.begin(), targets.end(), target) == targets.end())
    {
        return false;
    }

    if (const auto hero = dynamic_cast<Hero*>(target); hero)
    {
        if (CantAttackHeroes())
        {
            return false;
        }

        if (const auto minion = dynamic_cast<const Minion*>(this);
            minion && minion->IsAttackableByRush())
        {
            return false;
        }
    }

    return true;
}

std::vector<Character*> Character::GetValidAttackTargets(Player* opponent) const
{
    bool isExistTauntInField = false;
    std::vector<Character*> targets;
    std::vector<Character*> targetsHaveTaunt;

    for (auto& minion : opponent->GetFieldZone()->GetAll())
    {
        if (!minion->HasStealth())
        {
            if (minion->HasTaunt())
            {
                isExistTauntInField = true;
                targetsHaveTaunt.emplace_back(minion);
                continue;
            }

            if (!isExistTauntInField)
            {
                targets.emplace_back(minion);
            }
        }
    }

    if (isExistTauntInField)
    {
        return targetsHaveTaunt;
    }

    if (!CantAttackHeroes() && !opponent->GetHero()->IsImmune() &&
        !opponent->GetHero()->HasStealth())
    {
        targets.emplace_back(opponent->GetHero());
    }

    return targets;
}

int Character::TakeDamage(Playable* source, int damage)
{
    if (source == nullptr)
    {
        throw std::invalid_argument(
            "Character::TakeDamage() - source is nullptr");
    }

    const auto hero = dynamic_cast<Hero*>(this);
    const auto minion = dynamic_cast<Minion*>(this);

    const bool isFatigue = (hero != nullptr) && (this == source);
    if (isFatigue)
    {
        hero->fatigue = damage;
    }

    if (minion != nullptr && GetGameTag(GameTag::DIVINE_SHIELD) == 1)
    {
        SetGameTag(GameTag::DIVINE_SHIELD, 0);
        return 0;
    }

    const int armor = (hero != nullptr) ? hero->GetArmor() : 0;
    int amount =
        (hero == nullptr) ? damage : armor < damage ? damage - armor : 0;

    game->taskQueue.StartEvent();
    auto tempEventData = std::move(game->currentEventData);
    game->currentEventData =
        std::make_unique<EventMetaData>(source, this, amount);

    preDamageTrigger(this);
    game->ProcessTasks();
    amount = game->currentEventData->eventNumber;

    if (amount == 0 && armor == 0)
    {
        game->taskQueue.EndEvent();

        game->currentEventData.reset();
        game->currentEventData = std::move(tempEventData);

        return 0;
    }

    if (IsImmune())
    {
        game->taskQueue.EndEvent();

        game->currentEventData.reset();
        game->currentEventData = std::move(tempEventData);

        return 0;
    }

    if (armor > 0)
    {
        hero->SetArmor(armor < damage ? 0 : armor - damage);
    }

    SetDamage(GetDamage() + amount);

    // Process damage triggers
    takeDamageTrigger(this);
    game->triggerManager.OnTakeDamageTrigger(this);
    game->triggerManager.OnDealDamageTrigger(source);

    game->ProcessTasks();
    game->taskQueue.EndEvent();
    game->currentEventData.reset();
    game->currentEventData = std::move(tempEventData);

    if (source->HasLifesteal() && amount > 0)
    {
        source->player->GetHero()->TakeHeal(source, amount);
    }

    if (hero != nullptr)
    {
        hero->damageTakenThisTurn += amount;
    }

    return amount;
}

void Character::TakeFullHeal(Playable* source)
{
    TakeHeal(source, GetDamage());
}

void Character::TakeHeal(Playable* source, int heal)
{
    if (const auto value = source->player->playerAuraEffects.GetValue(
            GameTag::SPELL_HEALING_DOUBLE);
        (dynamic_cast<Spell*>(source) || dynamic_cast<HeroPower*>(source)) &&
        value > 0)
    {
        heal *= static_cast<int>(std::pow(2.0, value));
    }

    if (source->player->IsHealingDoesDamage())
    {
        TakeDamage(source, heal);
        return;
    }

    if (GetDamage() == 0)
    {
        return;
    }

    game->taskQueue.StartEvent();
    game->triggerManager.OnGiveHealTrigger(source);
    game->ProcessTasks();
    game->taskQueue.EndEvent();

    const int amount = GetDamage() > heal ? heal : GetDamage();
    SetDamage(GetDamage() - amount);

    const int value = player->GetAmountHealedThisGame();
    player->SetAmountHealedThisGame(value + amount);

    game->taskQueue.StartEvent();
    auto tempEventData = std::move(game->currentEventData);
    game->currentEventData =
        std::make_unique<EventMetaData>(source, this, amount);
    game->triggerManager.OnTakeHealTrigger(this);
    game->ProcessTasks();
    game->taskQueue.EndEvent();
    game->currentEventData.reset();
    game->currentEventData = std::move(tempEventData);
}

void Character::CopyInternalAttributes(Character* copy) const
{
    copy->SetAttack(GetAttack());
    copy->SetMaxHealth(GetMaxHealth());
    copy->SetDamage(GetDamage());
    copy->SetNumAttacksThisTurn(GetNumAttacksThisTurn());
    copy->SetGameTag(GameTag::DEATHRATTLE, GetGameTag(GameTag::DEATHRATTLE));
    copy->SetGameTag(GameTag::STEALTH, GetGameTag(GameTag::STEALTH));
    copy->SetGameTag(GameTag::IMMUNE, GetGameTag(GameTag::IMMUNE));
    copy->SetGameTag(GameTag::TAUNT, GetGameTag(GameTag::TAUNT));
    copy->SetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS,
                     GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS));
    copy->SetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS,
                     GetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS));
}
}  // namespace RosettaStone::PlayMode
