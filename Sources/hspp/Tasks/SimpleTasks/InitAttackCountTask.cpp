// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.hpp>
#include <hspp/Tasks/SimpleTasks/InitAttackCountTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
TaskID InitAttackCountTask::GetTaskID() const
{
    return TaskID::INIT_ATTACK_COUNT;
}

MetaData InitAttackCountTask::Impl(Player& player)
{
    ProcessMyField(player);
    ProcessEnemyField(player.GetOpponent());

    return MetaData::INIT_ATTACK_COUNT_SUCCESS;
}

void InitAttackCountTask::ProcessMyField(Player& my)
{
    // Add minions in field and hero
    std::vector<Character*> characters = my.GetField();
    characters.emplace_back(my.GetHero());

    for (auto& character : characters)
    {
        // Process Frozen status
        if (character->GetGameTag(GameTag::FROZEN) == 1)
        {
            character->numTurnToUnfreeze--;

            // If character is removed Frozen status, initialize attack count
            if (character->numTurnToUnfreeze == 0)
            {
                character->SetGameTag(GameTag::FROZEN, 0);
                // Consider Windfury status
                character->attackableCount =
                    character->GetGameTag(GameTag::WINDFURY) == 1 ? 2 : 1;
            }
            // Otherwise, character can't attack
            else
            {
                character->attackableCount = 0;
            }
        }
        else
        {
            // Consider Windfury status
            character->attackableCount =
                character->GetGameTag(GameTag::WINDFURY) == 1 ? 2 : 1;
        }
    }
}

void InitAttackCountTask::ProcessEnemyField(Player& opponent)
{
    for (auto& minion : opponent.GetField())
    {
        // Process Frozen status
        if (minion->GetGameTag(GameTag::FROZEN) == 1)
        {
            minion->numTurnToUnfreeze--;

            if (minion->numTurnToUnfreeze == 0)
            {
                minion->SetGameTag(GameTag::FROZEN, 0);
            }
        }

        // Attack count is always 0 because it's my turn
        minion->attackableCount = 0;
    }
}
}  // namespace Hearthstonepp::SimpleTasks
