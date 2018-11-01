// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.h>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID InitAttackCountTask::GetTaskID() const
{
    return TaskID::INIT_ATTACK_COUNT;
}

MetaData InitAttackCountTask::Impl(Player& player1, Player& player2)
{
    for (auto& character : player1.field)
    {
        if (character->GetGameTag(GameTag::FROZEN) == 1)
        {
            character->remainTurnToThaw--;

            if (character->remainTurnToThaw == 0)
            {
                character->SetGameTag(GameTag::FROZEN, 0);
                character->attackableCount =
                    character->GetGameTag(GameTag::WINDFURY) == 1 ? 2 : 1;
            }
            else
            {
                character->attackableCount = 0;
            }
        }
        else
        {
            character->attackableCount =
                character->GetGameTag(GameTag::WINDFURY) == 1 ? 2 : 1;
        }
    }

    for (auto& character : player2.field)
    {
        if (character->GetGameTag(GameTag::FROZEN) == 1)
        {
            character->remainTurnToThaw--;

            if (character->remainTurnToThaw == 0)
            {
                character->SetGameTag(GameTag::FROZEN, 0);
            }
        }

        character->attackableCount = 0;
    }

    return MetaData::INIT_ATTACK_COUNT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
