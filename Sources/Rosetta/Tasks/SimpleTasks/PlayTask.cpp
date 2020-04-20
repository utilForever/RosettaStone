// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/CastSpell.hpp>
#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Tasks/SimpleTasks/PlayTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
PlayTask::PlayTask(PlayType playType, bool randTarget)
    : m_playType(playType), m_randTarget(randTarget)
{
    // Do nothing
}

TaskStatus PlayTask::Impl(Player* player)
{
    TaskStack& taskStack = player->game->taskStack;

    if (m_playType == PlayType::SPELL)
    {
        for (auto& playable : taskStack.playables)
        {
            auto spell = dynamic_cast<Spell*>(playable);
            if (spell == nullptr)
            {
                throw std::runtime_error("PlayTask::Impl() - Spell is nullptr");
            }

            Player* spellPlayer = spell->player;
            Character* spellTarget = nullptr;

            if (m_randTarget)
            {
                if (spell->card->mustHaveToTargetToPlay)
                {
                    spellTarget = spell->GetRandomValidTarget();
                    if (spellTarget == nullptr)
                    {
                        if (spell->zone != nullptr)
                        {
                            spell->zone->Remove(spell);
                        }

                        return TaskStatus::STOP;
                    }
                }
            }

            if (spell->zone == nullptr || spell->zone->Remove(spell) != nullptr)
            {
                Generic::CastSpell(spellPlayer, spell, spellTarget, 0);
            }

            while (spellPlayer->choice.has_value())
            {
                auto choices = spellPlayer->choice->choices;
                const auto idx =
                    Random::get<std::size_t>(0, choices.size() - 1);
                Generic::ChoicePick(spellPlayer, choices[idx]);
            }
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> PlayTask::CloneImpl()
{
    return std::make_unique<PlayTask>(m_playType, m_randTarget);
}
}  // namespace RosettaStone::SimpleTasks
