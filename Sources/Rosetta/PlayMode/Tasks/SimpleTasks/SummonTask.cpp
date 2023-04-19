// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SummonTask::SummonTask(SummonSide side, std::optional<Card*> card,
                       bool removeFromStack, bool addToStack, int amount)
    : m_card(card),
      m_side(side),
      m_amount(amount),
      m_removeFromStack(removeFromStack),
      m_addToStack(addToStack)
{
    // Do nothing
}

SummonTask::SummonTask(const std::string& cardID, SummonSide side,
                       bool addToStack)
    : m_card(Cards::FindCardByID(cardID)),
      m_side(side),
      m_addToStack(addToStack)
{
    // Do nothing
}

SummonTask::SummonTask(const std::string& cardID, int amount, SummonSide side,
                       bool addToStack)
    : m_card(Cards::FindCardByID(cardID)),
      m_side(side),
      m_amount(amount),
      m_addToStack(addToStack)
{
    // Do nothing
}

int SummonTask::GetPosition(Entity* source, SummonSide side, Entity* target,
                            int& alternateCount)
{
    int summonPos = -1;

    switch (side)
    {
        case SummonSide::DEFAULT:
        {
            summonPos = -1;
            break;
        }
        case SummonSide::LEFT:
        {
            if (source->zone->GetType() == ZoneType::PLAY)
            {
                const auto src = dynamic_cast<Playable*>(source);
                summonPos = src->GetZonePosition();
            }
            else
            {
                const auto src = dynamic_cast<Minion*>(source);
                summonPos = src->GetLastBoardPos();
            }
            break;
        }
        case SummonSide::RIGHT:
        {
            if (source->zone->GetType() == ZoneType::PLAY)
            {
                const auto src = dynamic_cast<Playable*>(source);
                summonPos = src->GetZonePosition() + 1;
            }
            else
            {
                const auto src = dynamic_cast<Minion*>(source);
                summonPos = src->GetLastBoardPos();
            }
            break;
        }
        case SummonSide::DEATHRATTLE:
        {
            if (const auto minion = dynamic_cast<Minion*>(source))
            {
                summonPos = minion->GetLastBoardPos();
            }
            else if (const auto enchantment =
                         dynamic_cast<Enchantment*>(source))
            {
                const auto enchantmentTarget =
                    dynamic_cast<Minion*>(enchantment->GetTarget());
                summonPos = enchantmentTarget->GetLastBoardPos();
            }
            else
            {
                throw std::invalid_argument(
                    "SummonTask::Impl() - Invalid summon side");
            }
            break;
        }
        case SummonSide::NUMBER:
        {
            summonPos = source->game->taskStack.num[0] - 1;
            break;
        }
        case SummonSide::SPELL:
        {
            summonPos = -1;
            break;
        }
        case SummonSide::TARGET:
        {
            if (const auto _target = dynamic_cast<Playable*>(target))
            {
                summonPos = _target->GetZonePosition() + 1;
            }
            else
            {
                throw std::invalid_argument(
                    "SummonTask::Impl() - target is nullptr");
            }
            break;
        }
        case SummonSide::ALTERNATE_FRIENDLY:
        {
            const auto src = dynamic_cast<Playable*>(source);

            if (alternateCount % 2 == 0)
            {
                summonPos = src->GetZonePosition() - alternateCount / 2;
            }
            else
            {
                summonPos = src->GetZonePosition() + alternateCount / 2 + 1;
            }

            alternateCount++;
            break;
        }
        case SummonSide::ALTERNATE_ENEMY:
        {
            if (alternateCount % 2 == 0)
            {
                summonPos = 0;
            }
            else
            {
                summonPos =
                    source->player->opponent->GetFieldZone()->GetCount();
            }

            alternateCount++;
            break;
        }
    }

    return summonPos;
}

TaskStatus SummonTask::Impl(Player* player)
{
    TaskStack& stack = player->game->taskStack;

    if (!m_card.has_value() && stack.playables.empty())
    {
        return TaskStatus::COMPLETE;
    }

    int alternateCount = 0;

    for (int i = 0; i < m_amount; ++i)
    {
        if (player->GetFieldZone()->IsFull())
        {
            if (!m_card.has_value() && !stack.playables.empty())
            {
                const Playable* playable = stack.playables[0];

                if (!playable->zone)
                {
                    playable->player->GetGraveyardZone()->Add(
                        stack.playables[0]);
                }
            }

            return TaskStatus::STOP;
        }

        Minion* summonEntity = nullptr;

        if (m_card.has_value())
        {
            summonEntity = dynamic_cast<Minion*>(
                Entity::GetFromCard(player, m_card.value()));

            if (m_addToStack)
            {
                stack.playables.emplace_back(summonEntity);
            }
        }
        else if (!stack.playables.empty())
        {
            summonEntity = dynamic_cast<Minion*>(stack.playables[0]);

            if (m_removeFromStack)
            {
                EraseIf(stack.playables, [&](const Playable* entity) {
                    return entity == summonEntity;
                });
            }
        }

        if (!summonEntity)
        {
            return TaskStatus::STOP;
        }

        const int pos = GetPosition(m_source, m_side, m_target, alternateCount);
        const int summonPos = std::min(pos, player->GetFieldZone()->GetCount());

        if (summonEntity->IsUntouchable())
        {
            player->GetFieldZone()->Add(summonEntity, summonPos);
        }
        else
        {
            Generic::Summon(summonEntity, summonPos, m_source);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonTask::CloneImpl()
{
    return std::make_unique<SummonTask>(m_side, m_card, m_removeFromStack,
                                        m_addToStack, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
