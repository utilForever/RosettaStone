// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

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

    if (!target)
    {
        return TaskStatus::STOP;
    }

    const auto source = dynamic_cast<Minion*>(m_toTarget ? m_target : m_source);

    if (source->GetZoneType() != ZoneType::PLAY)
    {
        return TaskStatus::STOP;
    }

    const auto copiedCard = Entity::GetFromCard(player, target->card, {});
    IAura* aura = target->ongoingEffect;

    source->player->GetFieldZone()->Replace(source,
                                            dynamic_cast<Minion*>(copiedCard));

    if (!target->appliedEnchantments.empty())
    {
        for (const auto& enchantment : target->appliedEnchantments)
        {
            const auto instance =
                Enchantment::GetInstance(target, enchantment->card, copiedCard);
            if (enchantment->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1) > 0)
            {
                instance->SetGameTag(
                    GameTag::TAG_SCRIPT_DATA_NUM_1,
                    enchantment->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));

                if (enchantment->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2) > 0)
                {
                    instance->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2,
                                         enchantment->GetGameTag(
                                             GameTag::TAG_SCRIPT_DATA_NUM_2));
                }
            }
        }
    }

    for (const auto& tag : target->GetGameTags())
    {
        switch (tag.first)
        {
            case GameTag::ZONE:
            case GameTag::ZONE_POSITION:
            case GameTag::EXHAUSTED:
                break;
            default:
                copiedCard->SetGameTag(tag.first, tag.second);
        }
    }

    if (aura && !copiedCard->ongoingEffect)
    {
        aura->Clone(copiedCard);
    }

    if (target->HasCharge())
    {
        copiedCard->SetExhausted(false);
    }
    else if (target->HasRush())
    {
        dynamic_cast<Minion*>(copiedCard)->SetAttackableByRush(true);
        copiedCard->game->rushMinions.emplace_back(
            copiedCard->GetGameTag(GameTag::ENTITY_ID));
    }

    if (m_addToStack)
    {
        player->game->taskStack.AddPlayables({ copiedCard });
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TransformCopyTask::CloneImpl()
{
    return std::make_unique<TransformCopyTask>(m_toTarget, m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
