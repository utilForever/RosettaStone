// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2024 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>

#include <algorithm>

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

        const auto& oneTurnEffects = enchantment->GetOneTurnEffects();

        if (!oneTurnEffects.empty())
        {
            for (const auto& effect : oneTurnEffects)
            {
                if (const auto appliedEffect = effect.lock())
                {
                    appliedEffect->RemoveFrom(enchantment->GetTarget());
                }
            }

            EraseIf(player->game->oneTurnEffects,
                    [&](const auto& registeredEffect) {
                        if (registeredEffect.first != enchantment->GetTarget())
                        {
                            return false;
                        }

                        return std::ranges::any_of(
                            oneTurnEffects, [&](const auto& effect) {
                                const auto appliedEffect = effect.lock();
                                return appliedEffect &&
                                       appliedEffect.get() ==
                                           registeredEffect.second.get();
                            });
                    });
        }
        else if (enchant->useScriptTag)
        {
            enchant->RemoveEffect(enchantment->GetTarget(),
                                  enchantment->GetScriptTag1(),
                                  enchantment->GetScriptTag2());
        }
        else
        {
            enchant->RemoveEffect(enchantment->GetTarget());
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
