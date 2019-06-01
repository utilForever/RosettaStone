// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>

#include <utility>

namespace RosettaStone
{
Minion::Minion(Player& _owner, Card& _card, std::map<GameTag, int> tags)
    : Character(_owner, _card, std::move(tags))
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

    const int spellPower = GetGameTag(GameTag::SPELLPOWER);
    if (spellPower > 0)
    {
        owner->currentSpellPower -= spellPower;
        SetGameTag(GameTag::SPELLPOWER, 0);
    }

    if (onGoingEffect != nullptr)
    {
        onGoingEffect->Remove();
    }

    EraseIf(owner->GetGame()->oneTurnEffects,
            [this](std::pair<Entity*, Effect*> effect) {
                return effect.first->id == id;
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
            if (appliedEnchantments[i]->card.power.GetAura() != nullptr)
            {
                appliedEnchantments[i]->Remove();
            }
        }
    }

    SetGameTag(GameTag::ATK, card.gameTags[GameTag::ATK]);
    if (GetHealth() > card.gameTags[GameTag::HEALTH])
    {
        SetHealth(card.gameTags[GameTag::HEALTH]);
    }
    else
    {
        const int cardBaseHealth = card.gameTags[GameTag::HEALTH];
        const int delta = GetGameTag(GameTag::HEALTH) - cardBaseHealth;
        if (delta > 0)
        {
            SetDamage(GetDamage() - delta);
        }
        SetGameTag(GameTag::HEALTH, card.gameTags[GameTag::HEALTH]);
    }

    SetGameTag(GameTag::SILENCED, 1);
}

void Minion::Reset()
{
    Entity::Reset();

    if (onGoingEffect != nullptr)
    {
        onGoingEffect->Remove();
    }

    if (isDestroyed)
    {
        auto iter = owner->GetGame()->deadMinions.find(orderOfPlay);
        if (iter != owner->GetGame()->deadMinions.end())
        {
            owner->GetGame()->deadMinions.erase(iter);
        }

        isDestroyed = false;
    }
}

void Minion::Destroy()
{
    Entity::Destroy();

    owner->GetGame()->deadMinions.emplace(orderOfPlay, this);
}
}  // namespace RosettaStone
