/*************************************************************************
> File Name: TaskMeta.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Meta data structure for managing task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskMeta.h>

namespace Hearthstonepp
{
TaskMetaTrait::TaskMetaTrait()
    : id(TaskID::INVALID), status(MetaData::INVALID), userID(USER_INVALID)
{
    // Do Nothing
}

TaskMetaTrait::TaskMetaTrait(TaskID id)
    : id(id), status(MetaData::INVALID), userID(USER_INVALID)
{
    // Do Nothing
}

TaskMetaTrait::TaskMetaTrait(TaskID id, MetaData status)
    : id(id), status(status), userID(USER_INVALID)
{
    // Do Nothing
}

TaskMetaTrait::TaskMetaTrait(TaskID id, MetaData status, BYTE userID)
    : id(id), status(status), userID(userID)
{
    // Do Nothing
}

TaskMetaTrait::TaskMetaTrait(const TaskMetaTrait& trait)
    : id(trait.id), status(trait.status), userID(trait.userID)
{
    // Do Nothing
}

TaskMeta::TaskMeta() : TaskMetaTrait(), m_size(0)
{
    // Do Nothing
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait) : TaskMetaTrait(trait), m_size(0)
{
    // Do Nothing
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer)
    : TaskMetaTrait(trait),
      m_size(size),
      m_buffer(std::make_unique<BYTE[]>(size))
{
    // Deep Copy
    for (BYTE* dst = m_buffer.get(); size; --size)
    {
        *dst++ = *buffer++;
    }
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size,
                   std::unique_ptr<BYTE[]>&& buffer)
    : TaskMetaTrait(trait), m_size(size), m_buffer(std::move(buffer))
{
    // Do Nothing
}

TaskMeta::TaskMeta(TaskMeta&& meta) noexcept
    : TaskMetaTrait(meta),
      m_size(meta.GetBufferSize()),
      m_buffer(meta.MoveBuffer())
{
    // Do Nothing
}

TaskMeta& TaskMeta::operator=(TaskMeta&& meta)
{
    id = meta.id;
    status = meta.status;
    userID = meta.userID;

    m_size = meta.GetBufferSize();
    m_buffer = meta.MoveBuffer();

    return *this;
}

TaskMeta TaskMeta::CopyFrom(const TaskMeta& meta)
{
    // Deep Copy of TaskMeta
    return TaskMeta(meta, meta.GetBufferSize(), meta.GetConstBuffer().get());
}

TaskMeta TaskMeta::ConvertFrom(const FlatData::TaskMeta* meta)
{
    // Convert from FlatDat::TaskMeta, deep copy
    auto trait = meta->trait();
    auto taskID = TaskID::_from_integral(trait->id());
    auto buffer = meta->buffer();

    return TaskMeta(
        TaskMetaTrait(taskID, static_cast<MetaData>(trait->status()),
                      trait->userID()),
        buffer->size(), buffer->data());
}

void TaskMeta::reset()
{
    m_size = 0;
    m_buffer.reset();
}

size_t TaskMeta::GetBufferSize() const
{
    return m_size;
}

std::unique_ptr<BYTE[]>&& TaskMeta::MoveBuffer()
{
    return std::move(m_buffer);
}

const std::unique_ptr<BYTE[]>& TaskMeta::GetConstBuffer() const
{
    return m_buffer;
}
}  // namespace Hearthstonepp
