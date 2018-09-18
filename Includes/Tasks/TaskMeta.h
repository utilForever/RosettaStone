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

#include <Accounts/Player.h>
#include <Enums/TaskEnums.h>
#include <Tasks/MetaData.h>

#include <Flatbuffers/generated/FlatData_generated.h>

#include <memory>

namespace Hearthstonepp
{
using BYTE = unsigned char;

// Abstract of TaskMeta, store default meta data
// `id(TaskID)`, `status(MetaData)`, `accountID(unsigned char)`
struct TaskMetaTrait
{
    static constexpr BYTE USER_INVALID = Player::USER_INVALID;

    TaskID id;
    MetaData status;
    BYTE userID;

    TaskMetaTrait();
    TaskMetaTrait(TaskID id);
    TaskMetaTrait(TaskID id, MetaData status);
    TaskMetaTrait(TaskID id, MetaData status, BYTE userID);

    TaskMetaTrait(const TaskMetaTrait& trait);
    TaskMetaTrait& operator=(const TaskMetaTrait&);

    bool operator==(const TaskMetaTrait& trait) const;
};

// Meta data of run Task.
class TaskMeta : public TaskMetaTrait
{
 public:
    TaskMeta();
    TaskMeta(const TaskMetaTrait& trait);

    TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer);
    TaskMeta(const TaskMetaTrait& trait, size_t size,
             std::unique_ptr<BYTE[]>&& buffer);

    // Non copy-assignable object, only movable.
    // noexcept by move constructor of std::unique_ptr
    TaskMeta(TaskMeta&& meta) noexcept;
    TaskMeta(const TaskMeta&) = delete;

    TaskMeta& operator=(TaskMeta&& meta);
    TaskMeta& operator=(const TaskMeta&) = delete;

    bool operator==(const TaskMeta& meta) const;

    // Deep copy of TaskMeta
    static TaskMeta CopyFrom(const TaskMeta& meta);
    // Convert from FlatData::TaskMeta, deep copy of byte data
    static TaskMeta ConvertFrom(const FlatData::TaskMeta* meta);

    template <typename T>
    static inline const T* ConvertTo(const TaskMeta& meta)
    {
        const auto& buffer = meta.GetConstBuffer();
        if (buffer.get() == nullptr)
        {
            return nullptr;
        }
        return flatbuffers::GetRoot<T>(buffer.get());
    }

    // Reset std::unique_ptr and size data
    void reset();
    size_t GetBufferSize() const;

    std::unique_ptr<BYTE[]>&& MoveBuffer();
    const std::unique_ptr<BYTE[]>& GetConstBuffer() const;

 private:
    size_t m_size;
    std::unique_ptr<BYTE[]> m_buffer;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKMETA_H
