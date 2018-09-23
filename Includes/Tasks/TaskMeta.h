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
    //! \param buffer A pointer points to the start position of task array.
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
