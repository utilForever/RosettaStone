// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode
{
AdjacentAura::AdjacentAura(std::string&& enchantmentID)
    : m_enchantmentCard(Cards::FindCardByID(enchantmentID))
{
    // Do nothing
}

void AdjacentAura::Activate(Playable* owner, [[maybe_unused]] bool cloning)
{
    new AdjacentAura(*this, *dynamic_cast<Minion*>(owner), false);
}

void AdjacentAura::Update()
{
    if (m_toBeRemoved)
    {
        if (m_left)
        {
            Disapply(m_left);
        }

        if (m_right)
        {
            Disapply(m_right);
        }

        m_owner->ongoingEffect = nullptr;
        EraseIf(m_owner->game->auras,
                [this](const IAura* aura) { return aura == this; });

        return;
    }

    if (!m_isFieldChanged)
    {
        return;
    }

    const int pos = m_owner->GetZonePosition();

    // Check left side
    if (m_left)
    {
        if (m_left->GetZoneType() != ZoneType::PLAY ||
            m_left->GetZonePosition() != pos - 1)
        {
            Disapply(m_left);
            m_left = nullptr;
        }
    }

    if (!m_left && pos > 0)
    {
        Minion* left = (*m_fieldZone)[pos - 1];

        if (!left->GetGameTag(GameTag::UNTOUCHABLE))
        {
            Apply(left);
            m_left = left;
        }
    }

    // Check right side
    if (m_right)
    {
        if (m_right->GetZoneType() != ZoneType::PLAY ||
            m_right->GetZonePosition() != pos + 1)
        {
            Disapply(m_right);
            m_right = nullptr;
        }
    }

    if (!m_right && pos < m_fieldZone->GetCount() - 1)
    {
        Minion* right = (*m_fieldZone)[pos + 1];

        if (!right->GetGameTag(GameTag::UNTOUCHABLE))
        {
            Apply(right);
            m_right = right;
        }
    }

    m_isFieldChanged = false;
}

void AdjacentAura::Remove()
{
    m_toBeRemoved = true;
}

void AdjacentAura::Clone(Playable* clone)
{
    new AdjacentAura(*this, *dynamic_cast<Minion*>(clone), true);
}

void AdjacentAura::SetIsFieldChanged(bool isFieldChanged)
{
    m_isFieldChanged = isFieldChanged;
}

void AdjacentAura::Apply(Minion* minion) const
{
    for (auto& effect : m_effects)
    {
        effect->ApplyAuraTo(minion);
    }

    if (m_enchantmentCard)
    {
        Enchantment::GetInstance(minion, m_enchantmentCard, minion);
    }
}

void AdjacentAura::Disapply(Minion* minion) const
{
    for (auto& effect : m_effects)
    {
        effect->RemoveAuraFrom(minion);
    }

    if (m_enchantmentCard && m_enchantmentCard->power.GetTrigger())
    {
        const std::string cardID = m_enchantmentCard->id;
        auto enchantments = minion->appliedEnchantments;

        for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
        {
            if (enchantments[i]->card->id == cardID)
            {
                enchantments.erase(enchantments.begin() + i);
                break;
            }
        }
    }
}

AdjacentAura::AdjacentAura(const AdjacentAura& prototype, Minion& owner,
                           bool cloning)
    : m_owner(&owner), m_enchantmentCard(prototype.m_enchantmentCard)
{
    if (prototype.m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }
    else
    {
        m_effects = prototype.m_effects;
    }

    owner.ongoingEffect = this;
    owner.game->auras.emplace_back(this);

    m_fieldZone = owner.player->GetFieldZone();
    m_fieldZone->adjacentAuras.emplace_back(this);

    if (cloning)
    {
        if (prototype.m_left)
        {
            m_left = prototype.m_left;
        }

        if (prototype.m_right)
        {
            m_right = prototype.m_right;
        }
    }
}
}  // namespace RosettaStone::PlayMode
