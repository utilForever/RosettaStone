// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASK_META_HPP
#define HEARTHSTONEPP_TASK_META_HPP

#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/TaskStatus.hpp>

#include <any>

namespace RosettaStone
{
//!
//! \brief TaskMetaTrait class.
//!
//! This class is abstract class of TaskMeta class.
//! It stores default meta data such as id, status and userID.
//!
class TaskMetaTrait
{
 public:
    static constexpr std::size_t USER_INVALID = Player::USER_INVALID;

    //! Default constructor.
    TaskMetaTrait() = default;

    //! Constructs task meta trait with given \p id.
    //! \param id The task ID.
    TaskMetaTrait(TaskID id);

    //! Constructs task meta trait with given \p id and \p status.
    //! \param id The task ID.
    //! \param status The task status.
    TaskMetaTrait(TaskID id, TaskStatus status);

    //! Constructs task meta trait with given \p id, \p status and \p userID.
    //! \param id The task ID.
    //! \param status The task status.
    //! \param userID The user ID.
    TaskMetaTrait(TaskID id, TaskStatus status, std::size_t userID);

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
    TaskStatus GetStatus() const;

    //! Sets status of task meta.
    //! \param status Status of task meta.
    void SetStatus(TaskStatus status);

    //! Returns user ID.
    //! \return User ID.
    std::size_t GetUserID() const;

 protected:
    TaskID m_id = TaskID::INVALID;
    TaskStatus m_status = TaskStatus::INVALID;
    std::size_t m_userID = USER_INVALID;
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

    //! Constructs task meta with given \p trait and \p object.
    //! \param trait An instance of base class that stores default meta data.
    //! \param object An object to save in this class.
    TaskMeta(const TaskMetaTrait& trait, std::any object);

    //! Default destructor.
    ~TaskMeta() = default;

    //! Copy constructor.
    TaskMeta(const TaskMeta&);

    //! Move constructor.
    TaskMeta(TaskMeta&& meta) noexcept;

    //! Copy assignment operator.
    TaskMeta& operator=(const TaskMeta&);

    //! Move assignment operator.
    TaskMeta& operator=(TaskMeta&& meta) noexcept;

    //! Resets object.
    void Reset();

    //! Queries that object has value.
    //! \return true if object has value, false otherwise.
    bool HasObjects() const;

    //! Gets object from this class.
    //! \return Object from this class.
    template <typename T>
    T& GetObject()
    {
        return std::any_cast<T&>(m_object);
    }

    //! Gets object from this class.
    //! \return Object from this class.
    template <typename T>
    const T& GetObject() const
    {
        return std::any_cast<const T&>(m_object);
    }

    //! Moves object from this class.
    //! \return Moved object from this class.
    template <typename T>
    T MoveObject()
    {
        return std::any_cast<T&&>(std::move(m_object));
    }

 private:
    std::any m_object;
};
}  // namespace RosettaStone

#endif  // HEARTHSTONEPP_TASK_META_HPP