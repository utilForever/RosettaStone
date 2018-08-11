/*************************************************************************
> File Name: PlaySpell.h
> Project Name: Hearthstonepp
> Author: Chan-Ho Chris Ohk
> Purpose: Implement PlaySpell, cast spells
> Created Time: 2018/07/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYSPELL_H
#define HEARTHSTONEPP_PLAYSPELL_H

#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
// Cast spells
class PlaySpellTask : public ITask
{
 public:
    PlaySpellTask(TaskAgent& agent, Entity* entity);
    TaskID GetTaskID() const override;

 private:
    Entity* m_entity;
    Requirement m_requirement;
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYSPELL_H
