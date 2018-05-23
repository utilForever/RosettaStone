/*************************************************************************
> File Name: TaskMeta.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Meta data structure for managing task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <TaskMeta.h>

namespace Hearthstonepp
{
    TaskMetaTrait::TaskMetaTrait() :
            id(TaskID::INVALID), status(STATUS_INVALID), userID(USER_INVALID)
    {
        // Do Nothing
    }

    TaskMetaTrait::TaskMetaTrait(TaskID id) :
            id(id), status(STATUS_INVALID), userID(USER_INVALID)
    {
        // Do Nothing
    }

    TaskMetaTrait::TaskMetaTrait(TaskID id, status_t status) :
            id(id), status(status), userID(USER_INVALID)
    {
        // Do Nothing
    }

    TaskMetaTrait::TaskMetaTrait(TaskID id, status_t status, BYTE userID) :
            id(id), status(status), userID(userID)
    {
        // Do Nothing
    }

    TaskMetaTrait::TaskMetaTrait(const TaskMetaTrait& trait) :
            id(trait.id), status(trait.status), userID(trait.userID)
    {
        // Do Nothing
    }

    TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer) :
            TaskMetaTrait(trait), m_size(size), m_buffer(std::make_unique(size))
    {
        for (BYTE* dst = m_buffer; size; --size)
        {
            *buffer++ = *dst++;
        }
    }

    TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size, std::unique_ptr<BYTE[]>&& buffer) :
            TaskMetaTrait(trait), m_size(size), m_buffer(std::move(buffer))
    {
        // Do Nothing
    }

    TaskMeta::TaskMeta(TaskMeta&& meta) :
            TaskMetaTrait(meta), m_size(meta.GetBufferSize()), m_buffer(std::move(meta.GetBuffer()))
    {
        // Do NOthing
    }

    TaskMeta& TaskMeta::operator=(TaskMeta&& meta)
    {
        id = meta.id;
        status = meta.status;
        userID = meta.userID;

        m_size = meta.GetBufferSize();
        m_buffer = std::move(meta.GetBuffer());
    }

    static TaskMeta TaskMeta::CopyFrom(const TaskMeta& meta)
    {
        return TaskMeta(meta, meta.GetBufferSize(), meta.GetBuffer());
    }

    static TaskMeta TaskMeta::ConvertFrom(const FlatData::TaskMeta *meta)
    {
        auto trait = meta->trait();
        auto taskID = TaskID::_from_integral(trait->id());
        auto buffer = meta->buffer();

        return TaskMeta(TaskMetaTrait(taskID, trait->status(), trait->userID()), buffer->size(), buffer->data());
    }

    size_t TaskMeta::GetBufferSize() const
    {
        return m_size;
    }

    std::unique_ptr<BYTE[]>&& TaskMeta::GetBuffer() const
    {
        return m_buffer;
    }
}
