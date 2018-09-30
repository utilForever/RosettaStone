#ifndef HEARTHSTONEPP_TASKMETA_H
#define HEARTHSTONEPP_TASKMETA_H

#include <hspp/Accounts/Player.h>
#include <hspp/Enums/TaskEnums.h>
#include <hspp/Tasks/MetaData.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

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
struct TaskMetaTrait
{
    static constexpr BYTE USER_INVALID = Player::USER_INVALID;

    //! Default constructor.
    TaskMetaTrait();

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

    //! Copy constructor.
    TaskMetaTrait(const TaskMetaTrait& trait);

    //! Copy assignment operator.
    TaskMetaTrait& operator=(const TaskMetaTrait&);

    //! Operator overloading: The equality operator.
    bool operator==(const TaskMetaTrait& trait) const;

    TaskID id;
    MetaData status;
    BYTE userID;
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
    TaskMeta();

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
    //! \param buffers The task array (rvalue ref).
    TaskMeta(const TaskMetaTrait& trait, size_t size,
             std::unique_ptr<BYTE[]>&& buffers);

    //! Deleted copy constructor.
    TaskMeta(const TaskMeta&) = delete;

    //! Constructs task meta with given \p meta (move constructor).
    //! \param meta An instance of TaskMeta class (rvalue ref).
    TaskMeta(TaskMeta&& meta) noexcept;

    //! Deleted copy assignment operator.
    TaskMeta& operator=(const TaskMeta&) = delete;

    //! Assigns task meta with given \p meta (move assignment operator).
    //! \param meta An instance of TaskMeta class (rvalue ref).
    TaskMeta& operator=(TaskMeta&& meta);

    //! Operator overloading: The equality operator.
    //! \param meta An instance of TaskMeta class (lvalue ref).
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
    size_t m_size;
    std::unique_ptr<BYTE[]> m_buffer;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKMETA_H
