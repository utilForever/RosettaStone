// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASK_META_HPP
#define HEARTHSTONEPP_TASK_META_HPP

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Tasks/MetaData.hpp>

#include <hspp/Flatbuffers/generated/FlatData_generated.hpp>

#include <memory>

namespace Hearthstonepp
{
using BYTE = unsigned char;

//!
//! \brief TaskMetaTrait class.
//!
//! This class is abstract class of TaskMeta class.
//! It stores default meta data such as id, status and userID.
//!
class TaskMetaTrait
{
 public:
    static constexpr BYTE USER_INVALID = Player::USER_INVALID;

    //! Default constructor.
    TaskMetaTrait() = default;

    //! Constructs task meta trait with given \p id.
    //! \param id The task ID.
    TaskMetaTrait(TaskID id);

    //! Constructs task meta trait with given \p id and \p status.
    //! \param id The task ID.
    //! \param status The task status.
    TaskMetaTrait(TaskID id, MetaData status);

    //! Constructs task meta trait with given \p id, \p status and \p userID.
    //! \param id The task ID.
    //! \param status The task status.
    //! \param userID The user ID.
    TaskMetaTrait(TaskID id, MetaData status, BYTE userID);

    //! Default destructor.
    ~TaskMetaTrait() = default;

    //! Default copy constructor.
    TaskMetaTrait(const TaskMetaTrait& trait) = default;

    //! Default move constructor.
    TaskMetaTrait(TaskMetaTrait&& trait) = default;

    //! Default copy assignment operator.
    TaskMetaTrait& operator=(const TaskMetaTrait& trait) = default;

    //! Default move assignment operator.
    TaskMetaTrait& operator=(TaskMetaTrait&& trait) = default;

    //! Operator overloading: The equality operator.
    bool operator==(const TaskMetaTrait& trait) const;

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetID() const;

    //! Sets task ID.
    //! \param id Task ID.
    void SetID(TaskID id);

    //! Returns status of task meta.
    //! \return Status of task meta.
    MetaData GetStatus() const;

    //! Sets status of task meta.
    //! \param status Status of task meta.
    void SetStatus(MetaData status);

    //! Returns user ID.
    //! \return User ID.
    BYTE GetUserID() const;

 protected:
    TaskID m_id = TaskID::INVALID;
    MetaData m_status = MetaData::INVALID;
    BYTE m_userID = USER_INVALID;
};

//!
//! \brief TaskMeta class.
//!
//! This class manages task array as buffer.
//! Also, it provides conversion methods to/from flatbuffers type.
//!
class TaskMeta : public TaskMetaTrait
{
 public:
    //! Default constructor.
    TaskMeta() = default;

    //! Constructs task meta with given \p trait.
    //! \param trait An instance of base class that stores default meta data.
    TaskMeta(const TaskMetaTrait& trait);

    //! Constructs task meta with given \p trait, \p size and \p buffer.
    //! \param trait An instance of base class that stores default meta data.
    //! \param size The size of tasks.
    //! \param buffer A pointer to the start position of task array.
    TaskMeta(const TaskMetaTrait& trait, size_t size, const BYTE* buffer);

    //! Constructs task meta with given \p trait, \p size and \p buffers.
    //! \param trait An instance of base class that stores default meta data.
    //! \param size The size of tasks.
    //! \param buffer std::unique_ptr to task array (rvalue ref).
    TaskMeta(const TaskMetaTrait& trait, size_t size,
             std::unique_ptr<BYTE[]>&& buffer);

    //! Default destructor.
    ~TaskMeta() = default;

    //! Deleted copy constructor.
    TaskMeta(const TaskMeta&) = delete;

    //! Move constructor.
    TaskMeta(TaskMeta&& meta) noexcept;

    //! Deleted copy assignment operator.
    TaskMeta& operator=(const TaskMeta&) = delete;

    //! Move assignment operator.
    TaskMeta& operator=(TaskMeta&& meta) noexcept;

    //! Operator overloading: The equality operator.
    bool operator==(const TaskMeta& meta) const;

    //! Copies TaskMeta object (deep copy).
    //! \param meta A TaskMeta object to copy.
    //! \return Copied TaskMeta object.
    static TaskMeta CopyFrom(const TaskMeta& meta);

    //! Converts TaskMeta object from FlatData::TaskMeta object.
    //! \param meta A pointer to FlatData::TaskMeta object to convert.
    //! \return Converted TaskMeta object.
    static TaskMeta ConvertFrom(const FlatData::TaskMeta* meta);

    //! Converts TaskMeta object to FlatData::TaskMeta object.
    //! \tparam T The type of flatbuffers.
    //! \param meta A TaskMeta object to convert.
    //! \return Converted flatbuffers task meta object.
    template <typename T>
    static inline const T* ConvertTo(const TaskMeta& meta)
    {
        const auto& buffer = meta.GetBuffer();
        if (buffer.get() == nullptr)
        {
            return nullptr;
        }
        return flatbuffers::GetRoot<T>(buffer.get());
    }

    //! Resets buffer and its size.
    void Reset();

    //! Returns the size of buffer.
    //! \return The size of buffer.
    size_t GetBufferSize() const;

    //! Move buffer to another through rvalue reference.
    //! \return Moved buffer (rvalue ref).
    std::unique_ptr<BYTE[]>&& MoveBuffer();

    //! Returns the buffer as const type.
    //! \return The buffer (const).
    const std::unique_ptr<BYTE[]>& GetBuffer() const;

 private:
    size_t m_size = 0;
    std::unique_ptr<BYTE[]> m_buffer = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASK_META_HPP
