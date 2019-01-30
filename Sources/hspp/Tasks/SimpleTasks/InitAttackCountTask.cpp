// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Models/Entity.hpp>
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
    ProcessOpField(player.GetOpponent());

    return MetaData::INIT_ATTACK_COUNT_SUCCESS;
}

void InitAttackCountTask::ProcessMyField(Player& player)
{
    // Add minions in field and hero
    std::vector<Character*> characters = player.GetField().GetAllMinions();
    characters.emplace_back(player.GetHero());

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

void InitAttackCountTask::ProcessOpField(Player& player)
{
    // Add minions in field and hero
    std::vector<Character*> characters = player.GetField().GetAllMinions();
    characters.emplace_back(player.GetHero());

    for (auto& character : characters)
    {
        // Process Frozen status
        if (character->GetGameTag(GameTag::FROZEN) == 1)
        {
            character->numTurnToUnfreeze--;

            if (character->numTurnToUnfreeze == 0)
            {
                character->SetGameTag(GameTag::FROZEN, 0);
            }
        }

        // Attack count is always 0 because it's my turn
        character->attackableCount = 0;
    }
}
}  // namespace Hearthstonepp::SimpleTasks
