// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformCopyTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone::SimpleTasks
{
TaskStatus TransformCopyTask::Impl(Player* player)
{
    const auto target = dynamic_cast<Minion*>(m_target);
    if (target == nullptr)
    {
        return TaskStatus::STOP;
    }

    const auto source = dynamic_cast<Minion*>(m_source);
    if (source->GetZoneType() != ZoneType::PLAY)
    {
        return TaskStatus::STOP;
    }

    auto copy = Entity::GetFromCard(player, m_target->card, {});
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

    if (target->GetGameTag(GameTag::CHARGE) == 0)
    {
        copy->SetExhausted(true);
    }

    return TaskStatus::COMPLETE;
}

ITask* TransformCopyTask::CloneImpl()
{
    return new TransformCopyTask();
}
}  // namespace RosettaStone::SimpleTasks
