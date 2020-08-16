// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Minion::Minion(Player* player, Card* card, std::map<GameTag, int> tags, int id)
    : Character(player, card, std::move(tags), id)
{
    // Do nothing
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
            Minion* left = (*fieldZone)[pos - 1];

            if (!left->IsUntouchable())
            {
                minions.emplace_back(left);
            }

            if (pos < fieldZone->GetCount() - 1)
            {
                Minion* right = (*fieldZone)[pos + 1];

                if (!right->IsUntouchable())
                {
                    minions.emplace_back(right);
                }
            }
        }
        else if (fieldZone->GetCount() > 1)
        {
            Minion* right = (*fieldZone)[pos + 1];

            if (!right->IsUntouchable())
            {
                minions.emplace_back(right);
            }
        }
    }

    return minions;
}

bool Minion::IsLackey() const
{
    auto lackeys = Cards::GetLackeys();

    return std::find(lackeys.begin(), lackeys.end(), card) != lackeys.end();
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

bool Minion::HasSpellburst() const
{
    return static_cast<bool>(GetGameTag(GameTag::SPELLBURST));
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
    SetGameTag(GameTag::TAUNT, 0);
    SetGameTag(GameTag::FROZEN, 0);
    SetGameTag(GameTag::ENRAGED, 0);
    SetGameTag(GameTag::CHARGE, 0);
    SetGameTag(GameTag::WINDFURY, 0);
    SetGameTag(GameTag::DIVINE_SHIELD, 0);
    SetGameTag(GameTag::STEALTH, 0);
    SetGameTag(GameTag::DEATHRATTLE, 0);
    SetGameTag(GameTag::BATTLECRY, 0);
    SetGameTag(GameTag::INSPIRE, 0);
    SetGameTag(GameTag::LIFESTEAL, 0);
    SetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS, 0);
    SetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS, 0);
    SetGameTag(GameTag::IMMUNE, 0);
    SetGameTag(GameTag::CANT_ATTACK, 0);
    SetGameTag(GameTag::RUSH, 0);
    SetGameTag(GameTag::REBORN, 0);
    SetGameTag(GameTag::SPELLPOWER, 0);

    if (ongoingEffect != nullptr)
    {
        ongoingEffect->Remove();
    }

    EraseIf(game->oneTurnEffects, [this](std::pair<Entity*, IEffect*> effect) {
        return effect.first->GetGameTag(GameTag::ENTITY_ID) ==
               GetGameTag(GameTag::ENTITY_ID);
    });

    if (activatedTrigger != nullptr)
    {
        activatedTrigger->Remove();
    }

    if (!appliedEnchantments.empty())
    {
        const auto size = static_cast<int>(appliedEnchantments.size());
        for (int i = size - 1; i >= 0; --i)
        {
            if (appliedEnchantments[i]->card->power.GetAura() != nullptr)
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
        SetGameTag(GameTag::ATK, GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));

        if (GetHealth() > GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1))
        {
            SetHealth(GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));
        }
        else
        {
            const int cardBaseHealth =
                GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1);
            const int delta = GetGameTag(GameTag::HEALTH) - cardBaseHealth;

            if (delta > 0)
            {
                SetDamage(GetDamage() - delta);
            }

            SetGameTag(GameTag::HEALTH,
                       GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));
        }

        SetGameTag(GameTag::COST, GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));
    }
    else
    {
        SetGameTag(GameTag::ATK, card->gameTags[GameTag::ATK]);

        if (GetHealth() > card->gameTags[GameTag::HEALTH])
        {
            SetHealth(card->gameTags[GameTag::HEALTH]);
        }
        else
        {
            const int cardBaseHealth = card->gameTags[GameTag::HEALTH];
            const int delta = GetGameTag(GameTag::HEALTH) - cardBaseHealth;

            if (delta > 0)
            {
                SetDamage(GetDamage() - delta);
            }

            SetGameTag(GameTag::HEALTH, card->gameTags[GameTag::HEALTH]);
        }
    }

    SetGameTag(GameTag::SILENCED, 1);
}

void Minion::Reset()
{
    Entity::Reset();

    if (ongoingEffect != nullptr)
    {
        ongoingEffect->Remove();
    }

    if (isDestroyed)
    {
        auto iter = game->deadMinions.find(orderOfPlay);
        if (iter != game->deadMinions.end())
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
