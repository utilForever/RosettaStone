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
#include <Flatbuffers/MetaData_generated.h>

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
        using status_t = TaskMetaTrait::status_t;

        TaskMeta();
        TaskMeta(const TaskMetaTrait& trait);

        TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer);
        TaskMeta(const TaskMetaTrait& trait, size_t size, std::unique_ptr<BYTE[]>&& buffer);

        TaskMeta(TaskMeta&& meta);
        TaskMeta(const TaskMeta&) = delete;

        TaskMeta& operator=(TaskMeta&& meta);
        TaskMeta& operator=(const TaskMeta&) = delete;

        static TaskMeta CopyFrom(const TaskMeta& meta);
        static TaskMeta ConvertFrom(const FlatData::TaskMeta* meta);

        size_t GetBufferSize() const;
        std::unique_ptr<BYTE[]>&& GetBuffer() const;

    private:
        size_t m_size;
        std::unique_ptr<BYTE[]> m_buffer;
    };
}

#endif //HEARTHSTONEPP_TASKMETA_H
