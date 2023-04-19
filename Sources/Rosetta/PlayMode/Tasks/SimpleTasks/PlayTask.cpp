// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/PlayTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
PlayTask::PlayTask(PlayType playType, bool randTarget)
    : m_playType(playType), m_randTarget(randTarget)
{
    // Do nothing
}

TaskStatus PlayTask::Impl(Player* player)
{
    if (m_playType == PlayType::SPELL)
    {
        for (const auto& playable : player->game->taskStack.playables)
        {
            const auto spell = dynamic_cast<Spell*>(playable);

            if (!spell)
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

                    if (!spellTarget)
                    {
                        if (spell->zone)
                        {
                            spell->zone->Remove(spell);
                        }

                        return TaskStatus::STOP;
                    }
                }
            }

            if (!spell->zone || spell->zone->Remove(spell))
            {
                Generic::CastSpell(spellPlayer, spell, spellTarget, 0);
            }

            while (spellPlayer->choice)
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
}  // namespace RosettaStone::PlayMode::SimpleTasks
