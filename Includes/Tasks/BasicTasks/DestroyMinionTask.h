/*************************************************************************
> File Name: DestroyMinionTask.h
> Project Name: Hearthstonepp
> Author: SeungHyun Jeon
> Purpose: Implement DestroyMinion
> Created Time: 2018/08/21
> Copyright (c) 2018, SeungHyun Jeon
*************************************************************************/
#ifndef HEARTHSTONEPP_DESTORYMINIONTASK_H
#define HEARTHSTONEPP_DESTORYMINIONTASK_H

#include <Cards/Character.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class DestroyMinionTask : public ITask
{
public:
    DestroyMinionTask(Character* character);

    TaskID GetTaskID() const override;

private:
    Character* m_character;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTask

#endif //HEARTHSTONEPP_DESTORYMINIONTASK_H
