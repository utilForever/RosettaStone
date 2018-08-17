//
// Created by byunjuneseok on 8/17/18.
//

#ifndef HEARTHSTONEPP_HEALTASK_H
#define HEARTHSTONEPP_HEALTASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
    class HealTask : public ITask
    {
    public:
        HealTask(EntityType entityType, int amount);

        TaskID GetTaskID() const override;

    private:
        EntityType m_entityType;
        int m_amount;

        MetaData Impl(Player& player1, Player&) override;
    };
}  // namespace Hearthstonepp::PowerTask



#endif //HEARTHSTONEPP_HEALTASK_H
