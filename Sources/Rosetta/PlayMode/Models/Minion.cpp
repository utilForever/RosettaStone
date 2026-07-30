// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Minion::Minion(Player* _player, Card* _card, std::map<GameTag, int> tags,
               int id)
    : Character(_player, _card, std::move(tags), id)
{
    // Do nothing
}

bool Minion::IsSummoned() const
{
    return static_cast<bool>(GetGameTag(GameTag::SUMMONED));
}

void Minion::SetSummoned(bool value)
{
    SetGameTag(GameTag::SUMMONED, static_cast<int>(value));
}

int Minion::GetLastBoardPos() const
{
    return GetGameTag(GameTag::TAG_LAST_KNOWN_COST_IN_HAND);
}

void Minion::SetLastBoardPos(int value)
{
    SetGameTag(GameTag::TAG_LAST_KNOWN_COST_IN_HAND, value);
}

std::vector<Minion*> Minion::GetAdjacentMinions() const
{
    std::vector<Minion*> minions;
    minions.reserve(2);

    if (GetZoneType() == ZoneType::PLAY)
    {
        FieldZone* fieldZone = player->GetFieldZone();
        const int pos = GetZonePosition();

        if (pos > 0)
        {
            const auto left = dynamic_cast<Minion*>((*fieldZone)[pos - 1]);

            if (left && !left->IsUntouchable())
            {
                minions.emplace_back(left);
            }

            if (pos < fieldZone->GetCount() - 1)
            {
                const auto right = dynamic_cast<Minion*>((*fieldZone)[pos + 1]);

                if (right && !right->IsUntouchable())
                {
                    minions.emplace_back(right);
                }
            }
        }
        else if (fieldZone->GetCount() > 1)
        {
            const auto right = dynamic_cast<Minion*>((*fieldZone)[pos + 1]);

            if (right && !right->IsUntouchable())
            {
                minions.emplace_back(right);
            }
        }
    }

    return minions;
}

bool Minion::IsUntouchable() const
{
    return static_cast<bool>(GetGameTag(GameTag::UNTOUCHABLE));
}

bool Minion::HasCharge() const
{
    return static_cast<bool>(GetGameTag(GameTag::CHARGE));
}

bool Minion::HasTaunt() const
{
    return static_cast<bool>(GetGameTag(GameTag::TAUNT));
}

bool Minion::HasDivineShield() const
{
    return static_cast<bool>(GetGameTag(GameTag::DIVINE_SHIELD));
}

bool Minion::HasPoisonous() const
{
    return static_cast<bool>(GetGameTag(GameTag::POISONOUS));
}

bool Minion::HasFreeze() const
{
    return static_cast<bool>(GetGameTag(GameTag::FREEZE));
}

bool Minion::HasRush() const
{
    return static_cast<bool>(GetGameTag(GameTag::RUSH));
}

bool Minion::HasReborn() const
{
    return static_cast<bool>(GetGameTag(GameTag::REBORN));
}

bool Minion::HasFrenzy() const
{
    return static_cast<bool>(GetGameTag(GameTag::FRENZY));
}

bool Minion::IsAttackableByRush() const
{
    return static_cast<bool>(GetGameTag(GameTag::ATTACKABLE_BY_RUSH));
}

void Minion::SetAttackableByRush(bool attackable)
{
    SetGameTag(GameTag::ATTACKABLE_BY_RUSH, static_cast<int>(attackable));
}

bool Minion::CanAttack() const
{
    return Character::CanAttack() && !IsUntouchable();
}

void Minion::Silence()
{
    using enum GameTag;

    SetGameTag(TAUNT, 0);
    SetGameTag(FROZEN, 0);
    SetGameTag(ENRAGED, 0);
    SetGameTag(CHARGE, 0);
    SetGameTag(WINDFURY, 0);
    SetGameTag(DIVINE_SHIELD, 0);
    SetGameTag(STEALTH, 0);
    SetGameTag(DEATHRATTLE, 0);
    SetGameTag(BATTLECRY, 0);
    SetGameTag(INSPIRE, 0);
    SetGameTag(LIFESTEAL, 0);
    SetGameTag(CANT_BE_TARGETED_BY_HERO_POWERS, 0);
    SetGameTag(CANT_BE_TARGETED_BY_SPELLS, 0);
    SetGameTag(IMMUNE, 0);
    SetGameTag(CANT_ATTACK, 0);
    SetGameTag(RUSH, 0);
    SetGameTag(REBORN, 0);
    SetGameTag(SPELLPOWER, 0);
    SetGameTag(SPELLPOWER_ARCANE, 0);
    SetGameTag(SPELLPOWER_FIRE, 0);
    SetGameTag(SPELLPOWER_FROST, 0);
    SetGameTag(SPELLPOWER_NATURE, 0);
    SetGameTag(SPELLPOWER_HOLY, 0);
    SetGameTag(SPELLPOWER_SHADOW, 0);
    SetGameTag(SPELLPOWER_FEL, 0);

    if (ongoingEffect)
    {
        ongoingEffect->Remove();
    }

    EraseIf(game->oneTurnEffects, [this](const auto& effect) {
        return effect.first->GetGameTag(ENTITY_ID) == GetGameTag(ENTITY_ID);
    });

    if (activatedTrigger)
    {
        activatedTrigger->Remove();
    }

    if (!appliedEnchantments.empty())
    {
        const auto size = static_cast<int>(appliedEnchantments.size());
        for (int i = size - 1; i >= 0; --i)
        {
            if (appliedEnchantments[i]->card->power.GetAura())
            {
                appliedEnchantments[i]->Remove();
            }
        }
    }

    // NOTE: Abyssal Destroyer's Attack, Health, and Mana cost are set upon
    // being summoned and are not changed when targeted by effects that remove
    // enchantments.
    if (card->id == "DRG_207t")
    {
        SetGameTag(ATK, GetGameTag(TAG_SCRIPT_DATA_NUM_1));

        if (GetBaseHealth() > GetGameTag(TAG_SCRIPT_DATA_NUM_1))
        {
            SetBaseHealth(GetGameTag(TAG_SCRIPT_DATA_NUM_1));
        }
        else
        {
            const int cardBaseHealth = GetGameTag(TAG_SCRIPT_DATA_NUM_1);
            const int delta = GetGameTag(HEALTH) - cardBaseHealth;

            if (delta > 0)
            {
                SetDamage(GetDamage() - delta);
            }

            SetGameTag(HEALTH, GetGameTag(TAG_SCRIPT_DATA_NUM_1));
        }

        SetGameTag(COST, GetGameTag(TAG_SCRIPT_DATA_NUM_1));
    }
    else
    {
        SetGameTag(ATK, card->gameTags[ATK]);

        if (GetBaseHealth() > card->gameTags[HEALTH])
        {
            SetBaseHealth(card->gameTags[HEALTH]);
        }
        else
        {
            const int cardBaseHealth = card->gameTags[HEALTH];
            const int delta = GetGameTag(HEALTH) - cardBaseHealth;

            if (delta > 0)
            {
                SetDamage(GetDamage() - delta);
            }

            SetGameTag(HEALTH, card->gameTags[HEALTH]);
        }
    }

    SetGameTag(SILENCED, 1);
}

void Minion::Reset()
{
    Entity::Reset();

    if (ongoingEffect)
    {
        ongoingEffect->Remove();
    }

    if (isDestroyed)
    {
        if (const auto iter = game->deadMinions.find(orderOfPlay);
            iter != game->deadMinions.end())
        {
            game->deadMinions.erase(iter);
        }

        isDestroyed = false;
    }
}

void Minion::Destroy()
{
    Playable::Destroy();

    game->deadMinions.emplace(orderOfPlay, this);
}
}  // namespace RosettaStone::PlayMode
