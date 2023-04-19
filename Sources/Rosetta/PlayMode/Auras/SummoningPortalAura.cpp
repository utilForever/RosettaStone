// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Auras/SummoningPortalAura.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode
{
SummoningPortalAura::SummoningPortalAura()
    : Aura(AuraType::HAND, std::vector<std::shared_ptr<IEffect>>{})
{
    // Do nothing
}

void SummoningPortalAura::Activate(Playable* owner, bool cloning)
{
    auto instance = new SummoningPortalAura(*this, *owner);
    owner->ongoingEffect = instance;
    owner->player->GetHandZone()->auras.emplace_back(instance);
    owner->game->auras.emplace_back(instance);

    if (!cloning)
    {
        instance->m_auraUpdateInstQueue.Push(
            AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
    }
}

void SummoningPortalAura::Update()
{
    bool isAddAllProcessed = false;

    while (m_auraUpdateInstQueue.GetCount() > 0)
    {
        AuraUpdateInstruction inst = m_auraUpdateInstQueue.Pop();

        switch (inst.instruction)
        {
            case AuraInstruction::ADD:
            {
                if (isAddAllProcessed)
                {
                    break;
                }

                Apply(inst.source);
                m_appliedEntities.emplace_back(inst.source);
            }
            break;
            case AuraInstruction::ADD_ALL:
            {
                isAddAllProcessed = true;
                AddAll();
            }
            break;
            case AuraInstruction::REMOVE:
            {
                const auto iter =
                    std::find(m_appliedEntities.begin(),
                              m_appliedEntities.end(), inst.source);

                if (iter != m_appliedEntities.end())
                {
                    m_appliedEntities.erase(iter);
                }
                else
                {
                    break;
                }

                Disapply(inst.source);
            }
            break;
            case AuraInstruction::REMOVE_ALL:
            {
                RemoveAll();
            }
            break;
            case AuraInstruction::INVALID:
                throw std::invalid_argument(
                    "SummoningPortalAura::Update() - Invalid aura "
                    "instruction!");
        }
    }
}

void SummoningPortalAura::Clone(Playable* clone)
{
    Activate(clone, true);
}

void SummoningPortalAura::Apply(Playable* playable)
{
    CalculateCost(playable);
}

void SummoningPortalAura::Disapply(Playable* playable)
{
    CalculateCost(playable);
}

SummoningPortalAura::SummoningPortalAura(const SummoningPortalAura& prototype,
                                         Playable& owner)
    : Aura(prototype, owner)
{
    // Do nothing
}

void SummoningPortalAura::AddAll()
{
    for (auto& playable : m_owner->player->GetHandZone()->GetAll())
    {
        Apply(playable);
        m_appliedEntities.emplace_back(playable);
    }
}

void SummoningPortalAura::RemoveAll()
{
    EraseIf(m_owner->game->auras,
            [this](const IAura* aura) { return aura == this; });

    for (const auto& entity : m_appliedEntities)
    {
        Disapply(entity);
    }
}

void SummoningPortalAura::CalculateCost(Playable* playable) const
{
    std::size_t numSPAura = 0;

    for (const auto& aura : m_owner->game->auras)
    {
        if (const auto spAura = dynamic_cast<SummoningPortalAura*>(aura);
            spAura)
        {
            ++numSPAura;
        }
    }

    const auto minion = dynamic_cast<Minion*>(playable);
    if (!minion)
    {
        return;
    }

    const int cardValue = minion->card->GetCost();
    int cost = cardValue;

    for (std::size_t i = 0; i < numSPAura; ++i)
    {
        cost = cost > 2 ? cost - 2 : 1;
    }

    minion->SetCost(cost);

    if (const auto costManager = playable->costManager; costManager)
    {
        costManager->QueueUpdate();
    }
}
}  // namespace RosettaStone::PlayMode
