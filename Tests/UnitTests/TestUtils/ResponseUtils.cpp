#include "ResponseUtils.h"

#include <Tasks/TaskSerializer.h>

namespace TestUtils
{
AutoResponder::AutoResponder(GameAgent& agent) : m_agent(agent)
{
    // Do Nothing
}

std::future<TaskMeta> AutoResponder::Mulligan(const BYTE* index, size_t size)
{
    return std::async(std::launch::async, [this, index, size] {
        TaskMeta meta;
        m_agent.GetTaskMeta(meta);

        TaskMeta mulligan = Serializer::CreateResponseMulligan(index, size);
        m_agent.WriteSyncBuffer(std::move(mulligan));

        return meta;
    });
}

std::future<TaskMeta> AutoResponder::PlayCard(size_t cardIndex)
{
    return std::async(std::launch::async, [this, cardIndex] {
        TaskMeta meta;
        m_agent.GetTaskMeta(meta);

        TaskMeta playCard = Serializer::CreateResponsePlayCard(cardIndex);
        m_agent.WriteSyncBuffer(std::move(playCard));

        return meta;
    });
}

std::future<TaskMeta> AutoResponder::PlayMinion(size_t position)
{
    return std::async(std::launch::async, [this, position] {
        TaskMeta meta;
        m_agent.GetTaskMeta(meta);

        TaskMeta playMinion = Serializer::CreateResponsePlayMinion(position);
        m_agent.WriteSyncBuffer(std::move(playMinion));

        return meta;
    });
}

std::future<TaskMeta> AutoResponder::Target(size_t src, size_t dst)
{
    return std::async(std::launch::async, [this, src, dst] {
        TaskMeta meta;
        m_agent.GetTaskMeta(meta);

        TaskMeta target = Serializer::CreateResponseTarget(src, dst);
        m_agent.WriteSyncBuffer(std::move(target));

        return meta;
    });
}

auto AutoResponder::AutoMinion(size_t cardIndex, size_t position)
    -> std::future<std::tuple<TaskMeta, TaskMeta>>
{
    return std::async(std::launch::async, [this, cardIndex, position] {
        auto playCard = PlayCard(cardIndex);
        playCard.wait();

        auto playMinion = PlayMinion(position);
        return std::make_tuple(playCard.get(), playMinion.get());
    });
}
}  // namespace TestUtils
