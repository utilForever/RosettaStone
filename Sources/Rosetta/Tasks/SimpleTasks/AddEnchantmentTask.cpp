// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(
    const std::string_view& cardID, EntityType entityType, bool useScriptTag,
    std::optional<SelfCondition> selfCondition)
    : ITask(entityType),
      m_enchantmentCard(Cards::FindCardByID(cardID)),
      m_useScriptTag(useScriptTag),
      m_selfCondition(std::move(selfCondition))
{
    // Do nothing
}

TaskStatus AddEnchantmentTask::Impl(Player* player)
{
    int num1 = 0, num2 = 0;
    if (m_useScriptTag)
    {
        num1 = m_source->game->taskStack.num[0];
        num2 = m_source->game->taskStack.num[1];
    }

    const auto source = dynamic_cast<Playable*>(m_source);

    if (m_entityType == EntityType::PLAYER)
    {
        Generic::AddEnchantment(m_enchantmentCard, source, player, num1, num2);
        return TaskStatus::COMPLETE;
    }

    if (m_entityType == EntityType::ENEMY_PLAYER)
    {
        Generic::AddEnchantment(m_enchantmentCard, source, player->opponent,
                                num1, num2);
        return TaskStatus::COMPLETE;
    }

    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (m_selfCondition.has_value() && !m_selfCondition->Evaluate(playable))
        {
            continue;
        }

        Generic::AddEnchantment(m_enchantmentCard, source, playable, num1,
                                num2);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddEnchantmentTask::CloneImpl()
{
    return std::make_unique<AddEnchantmentTask>(
        m_enchantmentCard->id, m_entityType, m_useScriptTag, m_selfCondition);
}
}  // namespace RosettaStone::SimpleTasks
