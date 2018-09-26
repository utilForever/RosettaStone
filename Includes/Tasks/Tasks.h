#ifndef HEARTHSTONEPP_TASKS_H
#define HEARTHSTONEPP_TASKS_H

#include <Accounts/Player.h>
#include <Enums/CardEnums.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskMeta.h>

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
