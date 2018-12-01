// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASKS_HPP
#define HEARTHSTONEPP_TASKS_HPP

#include <hspp/Accounts/Player.hpp>
#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Tasks/MetaData.hpp>
#include <hspp/Tasks/TaskMeta.hpp>

namespace Hearthstonepp
{
//!
//! \brief ITask class.
//!
//! This class is interface of various task classes.
//! All classes that inherit from it must implement GetTaskID and Impl methods.
//!
class ITask
{
 public:
    template <typename T>
    static inline constexpr bool isTask =
        std::is_convertible_v<std::decay_t<T>, ITask>;

    //! Default constructor.
    ITask() = default;

    //!
    ITask(EntityType entityType);

    //!
    ITask(Entity* source, Entity* target);

    //!
    ITask(EntityType entityType, Entity* source, Entity* target);

    //! Default destructor.
    virtual ~ITask() = default;

    //! Default copy constructor.
    ITask(const ITask& task) = default;

    //! Default move constructor.
    ITask(ITask&& task) = default;

    //! Default copy assignment operator.
    ITask& operator=(const ITask& task) = default;

    //! Default move assignment operator.
    ITask& operator=(ITask&& task) = default;

    //! Returns entity type.
    //! \return Entity type.
    EntityType GetEntityType() const;

    //! Sets the target.
    //! \param target A pointer to the target.
    void SetTarget(Entity* target);

    //! Calls Impl method and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Run(Player& player);

    //! Calls Impl method and returns meta data.
    //! \param player The player to run task.
    //! \param meta The task meta that stores game status.
    //! \return The result of task processing.
    MetaData Run(Player& player, TaskMeta& meta);

    //! Returns task ID (pure virtual).
    //! \return Task ID.
    virtual TaskID GetTaskID() const = 0;

 protected:
    EntityType m_entityType = EntityType::EMPTY;
    Entity* m_source = nullptr;
    Entity* m_target = nullptr;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    virtual MetaData Impl(Player& player) = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKS_HPP
