#include <Tasks/BasicTasks/InitAttackCountTask.h>

#include <Cards/Entity.h>

namespace Hearthstonepp::BasicTasks
{
TaskID InitAttackCountTask::GetTaskID() const
{
    return TaskID::INIT_ATTACK_COUNT;
}

MetaData InitAttackCountTask::Impl(Player& player1, Player&)
{
    for (auto& character : player1.field)
    {
        if (character->gameTags[+GameTag::FROZEN] == 1)
        {
            character->gameTags[+GameTag::FROZEN] = 0;
        }
        else if (character->gameTags[+GameTag::FROZEN] == 2)
        {
            character->gameTags[+GameTag::FROZEN] = 1;
            character->attackableCount = 0;
            continue;
        }

        character->attackableCount =
            character->gameTags[+GameTag::WINDFURY] == 1 ? 2 : 1;
    }

    return MetaData::INIT_ATTACK_COUNT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
