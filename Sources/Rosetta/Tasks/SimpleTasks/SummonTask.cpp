// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

namespace RosettaStone::SimpleTasks
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

SummonTask::SummonTask(const std::string& cardID, int amount, SummonSide side)
    : m_card(Cards::FindCardByID(cardID)), m_side(side), m_amount(amount)
{
    // Do nothing
}

int SummonTask::GetPosition(Entity* source, SummonSide side)
{
    int summonPos;

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
            if (const auto minion = dynamic_cast<Minion*>(source); minion)
            {
                summonPos = minion->GetLastBoardPos();
            }
            else if (const auto enchantment =
                         dynamic_cast<Enchantment*>(source);
                     enchantment)
            {
                const auto target =
                    dynamic_cast<Minion*>(enchantment->GetTarget());
                summonPos = target->GetLastBoardPos();
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
        default:
            throw std::invalid_argument(
                "SummonTask::Impl() - Invalid summon side");
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

    for (int i = 0; i < m_amount; ++i)
    {
        if (player->GetFieldZone()->IsFull())
        {
            if (!m_card.has_value() && !stack.playables.empty())
            {
                Playable* playable = stack.playables[0];

                if (playable->zone == nullptr)
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
                EraseIf(stack.playables, [&](Playable* entity) {
                    return entity == summonEntity;
                });
            }
        }

        if (summonEntity == nullptr)
        {
            return TaskStatus::STOP;
        }

        int summonPos = GetPosition(m_source, m_side);
        if (summonPos > player->GetFieldZone()->GetCount())
        {
            summonPos = player->GetFieldZone()->GetCount();
        }

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

ITask* SummonTask::CloneImpl()
{
    return new SummonTask(m_side, m_card, m_removeFromStack, m_addToStack,
                          m_amount);
}
}  // namespace RosettaStone::SimpleTasks
