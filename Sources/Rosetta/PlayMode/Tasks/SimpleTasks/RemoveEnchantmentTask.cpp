// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus RemoveEnchantmentTask::Impl(Player* player)
{
    const auto enchantment = dynamic_cast<Enchantment*>(m_source);

    if (!enchantment)
    {
        return TaskStatus::STOP;
    }

    if (const auto enchant = enchantment->card->power.GetEnchant())
    {
        if (enchantment->IsOneTurnActive() &&
            player->game->step == Step::MAIN_CLEANUP)
        {
            enchantment->Remove();
            return TaskStatus::COMPLETE;
        }

        if (enchant->useScriptTag)
        {
            enchant->RemoveEffect(enchantment->GetTarget(),
                                  enchantment->GetScriptTag1(),
                                  enchantment->GetScriptTag2());
        }
        else
        {
            enchant->RemoveEffect(enchantment->GetTarget());
        }

        if (enchantment->IsOneTurnActive())
        {
            for (const auto& effect : enchant->effects)
            {
                EraseIf(player->game->oneTurnEffects,
                        [=](std::pair<Entity*, IEffect*> eff) {
                            return eff.first == enchantment->GetTarget() &&
                                   eff.second == effect.get();
                        });
            }
        }
    }

    enchantment->Remove();

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RemoveEnchantmentTask::CloneImpl()
{
    return std::make_unique<RemoveEnchantmentTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
