// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

#include <stdexcept>

namespace Hearthstonepp::SimpleTasks
{
TaskID IncludeTask::GetTaskID() const
{
    return TaskID::INCLUDE;
}

std::vector<Entity*> IncludeTask::GetEntities(EntityType entityType,
                                              Player& player, Entity* source,
                                              Entity* target)
{
    std::vector<Entity*> entities;

    switch (entityType)
    {
        case EntityType::SOURCE:
            entities.emplace_back(source);
            break;
        case EntityType::TARGET:
            entities.emplace_back(target);
            break;
        case EntityType::HERO:
            entities.emplace_back(player.GetHero());
            break;
        case EntityType::FRIENDS:
            for (auto& minion : player.GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetHero());
            break;
        case EntityType::ENEMIES:
            for (auto& minion : player.GetOpponent().GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetOpponent().GetHero());
            break;
        default:
            throw std::domain_error("Invalid entity type");
    }

    return entities;
}

MetaData IncludeTask::Impl(Player&)
{
    return MetaData::INCLUDE_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
