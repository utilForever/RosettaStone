// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformCopyTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TransformCopyTask::TransformCopyTask(bool toTarget, bool addToStack)
    : m_toTarget(toTarget), m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus TransformCopyTask::Impl(Player* player)
{
    const auto target = dynamic_cast<Minion*>(m_toTarget ? m_source : m_target);
    if (target == nullptr)
    {
        return TaskStatus::STOP;
    }

    const auto source = dynamic_cast<Minion*>(m_toTarget ? m_target : m_source);
    if (source->GetZoneType() != ZoneType::PLAY)
    {
        return TaskStatus::STOP;
    }

    auto copy = Entity::GetFromCard(player, target->card, {});
    IAura* aura = target->ongoingEffect;

    source->player->GetFieldZone()->Replace(source,
                                            dynamic_cast<Minion*>(copy));

    if (!target->appliedEnchantments.empty())
    {
        for (auto& e : target->appliedEnchantments)
        {
            auto instance = Enchantment::GetInstance(player, e->card, copy);
            if (e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1) > 0)
            {
                instance->SetGameTag(
                    GameTag::TAG_SCRIPT_DATA_NUM_1,
                    e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));

                if (e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2) > 0)
                {
                    instance->SetGameTag(
                        GameTag::TAG_SCRIPT_DATA_NUM_2,
                        e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2));
                }
            }
        }
    }

    for (auto& tag : target->GetGameTags())
    {
        switch (tag.first)
        {
            case GameTag::ZONE:
            case GameTag::ZONE_POSITION:
            case GameTag::EXHAUSTED:
                break;
            default:
                copy->SetGameTag(tag.first, tag.second);
        }
    }

    if (aura != nullptr && copy->ongoingEffect == nullptr)
    {
        aura->Clone(copy);
    }

    if (target->HasCharge())
    {
        copy->SetExhausted(false);
    }
    else if (target->HasRush())
    {
        dynamic_cast<Minion*>(copy)->SetAttackableByRush(true);
        copy->game->rushMinions.emplace_back(
            copy->GetGameTag(GameTag::ENTITY_ID));
    }

    if (m_addToStack)
    {
        player->game->taskStack.AddPlayables({ copy });
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TransformCopyTask::CloneImpl()
{
    return std::make_unique<TransformCopyTask>(m_toTarget, m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
