// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>

namespace RosettaStone::SimpleTasks
{
TaskStatus RemoveEnchantmentTask::Impl([[maybe_unused]] Player* player)
{
    auto enchantment = dynamic_cast<Enchantment*>(m_source);
    if (enchantment == nullptr)
    {
        return TaskStatus::STOP;
    }

    if (auto enchant = enchantment->card->power.GetEnchant();
        enchant != nullptr && (!enchantment->IsOneTurnActive() ||
                               player->game->step != Step::MAIN_CLEANUP))
    {
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

        //if (enchantment->IsOneTurnActive())
        //{
        //    for (auto& effect : enchant->effects)
        //    {
        //        EraseIf(player->game->oneTurnEffects,
        //                [=](std::pair<Entity*, IEffect*> eff) {
        //                    return eff.first == enchantment->GetTarget() &&
        //                           eff.second == effect.get();
        //                });
        //    }
        //}
    }

    enchantment->Remove();

    return TaskStatus::COMPLETE;
}

ITask* RemoveEnchantmentTask::CloneImpl()
{
    return new RemoveEnchantmentTask();
}
}  // namespace RosettaStone::SimpleTasks
