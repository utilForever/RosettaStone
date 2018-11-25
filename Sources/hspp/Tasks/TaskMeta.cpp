// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/TaskMeta.h>

namespace Hearthstonepp
{
TaskMetaTrait::TaskMetaTrait(TaskID id) : m_id(id)
{
    // Do nothing
}

TaskMetaTrait::TaskMetaTrait(TaskID id, MetaData status)
    : m_id(id), m_status(status)
{
    // Do nothing
}

TaskMetaTrait::TaskMetaTrait(TaskID id, MetaData status, BYTE userID)
    : m_id(id), m_status(status), m_userID(userID)
{
    // Do nothing
}

bool TaskMetaTrait::operator==(const TaskMetaTrait& trait) const
{
    return m_id == trait.m_id && m_status == trait.m_status &&
           m_userID == trait.m_userID;
}

TaskID TaskMetaTrait::GetID() const
{
    return m_id;
}

void TaskMetaTrait::SetID(TaskID id)
{
    m_id = id;
}

MetaData TaskMetaTrait::GetStatus() const
{
    return m_status;
}

void TaskMetaTrait::SetStatus(MetaData status)
{
    m_status = status;
}

BYTE TaskMetaTrait::GetUserID() const
{
    return m_userID;
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait) : TaskMetaTrait(trait)
{
    // Do nothing
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer)
    : TaskMetaTrait(trait),
      m_size(size),
      m_buffer(std::make_unique<BYTE[]>(size))
{
    // Deep copy
    for (BYTE* dst = m_buffer.get(); size; --size)
    {
        *dst++ = *buffer++;
    }
}

TaskMeta::TaskMeta(const TaskMetaTrait& trait, size_t size,
                   std::unique_ptr<BYTE[]>&& buffer)
    : TaskMetaTrait(trait), m_size(size), m_buffer(std::move(buffer))
{
    // Do nothing
}

TaskMeta::TaskMeta(TaskMeta&& meta) noexcept
    : TaskMetaTrait(meta),
      m_size(meta.GetBufferSize()),
      m_buffer(meta.MoveBuffer())
{
    // Do nothing
}

TaskMeta& TaskMeta::operator=(TaskMeta&& meta) noexcept
{
    if (*this == meta)
    {
        return *this;
    }

    TaskMetaTrait::operator=(meta);

    m_size = meta.GetBufferSize();
    m_buffer = meta.MoveBuffer();

    return *this;
}

bool TaskMeta::operator==(const TaskMeta& meta) const
{
    if (TaskMetaTrait::operator==(meta) && m_size == meta.GetBufferSize())
    {
        const auto& buffer = meta.GetBuffer();
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_buffer[i] != buffer[i])
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

TaskMeta TaskMeta::CopyFrom(const TaskMeta& meta)
{
    // Deep copy
    return TaskMeta(meta, meta.GetBufferSize(), meta.GetBuffer().get());
}

TaskMeta TaskMeta::ConvertFrom(const FlatData::TaskMeta* meta)
{
    // Convert from FlatData::TaskMeta and deep copy
    const auto trait = meta->trait();
    const auto taskID = TaskID::_from_integral(trait->id());
    const auto buffer = meta->buffer();

    return TaskMeta(
        TaskMetaTrait(taskID, static_cast<MetaData>(trait->status()),
                      trait->userID()),
        buffer->size(), buffer->data());
}

void TaskMeta::Reset()
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
    m_size = 0;
    return std::move(m_buffer);
}

const std::unique_ptr<BYTE[]>& TaskMeta::GetBuffer() const
{
    return m_buffer;
}
}  // namespace Hearthstonepp
