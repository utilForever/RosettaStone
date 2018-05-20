/*************************************************************************
> File Name: TaskMeta.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Meta data structure for managing task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/

#ifndef HEARTHSTONEPP_TASKMETA_H
#define HEARTHSTONEPP_TASKMETA_H

#include <Enums/Enums.h>

#include <memory>

namespace Hearthstonepp
{
    using BYTE = unsigned char;

    struct TaskMetaTrait
    {
        using status_t = unsigned int;
        static constexpr status_t STATUS_INVALID = 0;
        static constexpr BYTE USER_INVALID = 255;

        TaskID id;
        status_t status;
        BYTE userID;

        TaskMetaTrait();
        TaskMetaTrait(TaskID id);
        TaskMetaTrait(TaskID id, status_t status);
        TaskMetaTrait(TaskID id, status_t status, BYTE userID);

        TaskMetaTrait(const TaskMetaTrait& trait);

        TaskMetaTrait& operator=(TaskMetaTrait&&) = delete;
        TaskMetaTrait& operator=(const TaskMetaTrait&) = delete;
    };

    class TaskMeta : public TaskMetaTrait
    {
    public:
        TaskMeta() = default;

        TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer);
        TaskMeta(const TaskMetaTrait& trait, size_t size, std::unique_ptr<BYTE[]>&& buffer);

        TaskMeta(TaskMeta&& meta);
        TaskMeta(const TaskMeta&) = delete;

        TaskMeta& operator=(TaskMeta&& meta);
        TaskMeta& operator=(const TaskMeta&) = delete;

        size_t GetBufferSize();
        std::unique_ptr<BYTE[]>&& GetBuffer();

    private:
        size_t m_size;
        std::unique_ptr<BYTE[]> m_buffer;
    };
}

#endif //HEARTHSTONEPP_TASKMETA_H
