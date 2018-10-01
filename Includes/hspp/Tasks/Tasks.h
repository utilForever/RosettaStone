// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASKS_H
#define HEARTHSTONEPP_TASKS_H

#include <hspp/Accounts/Player.h>
#include <hspp/Enums/CardEnums.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/TaskMeta.h>

#include <functional>

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

    //! Destructor: Releases pointers to source and target.
    virtual ~ITask();

    //! Calls Impl method and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Run(Player& player1, Player& player2);

    //! Calls Impl method and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \param meta The task meta that stores game status.
    //! \return The result of task processing.
    MetaData Run(Player& player1, Player& player2, TaskMeta& meta);

    //! Returns task ID (pure virtual).
    //! \return Task ID.
    virtual TaskID GetTaskID() const = 0;

    Character* source = nullptr;
    Character* target = nullptr;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    virtual MetaData Impl(Player& player1, Player& player2) = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKS_H
