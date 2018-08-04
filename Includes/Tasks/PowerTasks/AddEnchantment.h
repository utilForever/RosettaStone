/*************************************************************************
> File Name: AddEnchantment.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_H
#define HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
class AddEnchantmentTask : public ITask
{
 public:
    AddEnchantmentTask(std::string&& cardID, EntityType entityType);

 private:
    std::string m_cardID;
    EntityType m_entityType;
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_HEAL_FULL_TASK_H
