// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
{
GetGameTagTask::GetGameTagTask(EntityType entityType, GameTag tag,
                               int entityIndex, int numIndex)
    : ITask(entityType),
      m_gameTag(tag),
      m_entityIndex(entityIndex),
      m_numIndex(numIndex)
{
    // Do nothing
}

TaskStatus GetGameTagTask::Impl(Player* player)
{
    const auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    if (entities.empty() || static_cast<int>(entities.size()) <= m_entityIndex)
    {
        return TaskStatus::STOP;
    }

    const int value = entities[m_entityIndex]->GetGameTag(m_gameTag);

    if (m_numIndex == 0)
    {
        player->game->taskStack.num[0] = value;
    }
    else if (static_cast<int>(entities.size()) > m_entityIndex)
    {
        switch (m_numIndex)
        {
            case 1:
                player->game->taskStack.num[1] = value;
                break;
            case 2:
                player->game->taskStack.num[2] = value;
                break;
            case 3:
                player->game->taskStack.num[3] = value;
                break;
            case 4:
                player->game->taskStack.num[4] = value;
                break;
            default:
                throw std::invalid_argument(
                    "GetGameTagTask::Impl() - Invalid number index");
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> GetGameTagTask::CloneImpl()
{
    return std::make_unique<GetGameTagTask>(m_entityType, m_gameTag,
                                            m_entityIndex, m_numIndex);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
