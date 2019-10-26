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

namespace RosettaStone::SimpleTasks
{
SummonTask::SummonTask(SummonSide side, std::optional<Card*> card, int amount,
                       bool toOpponent)
    : m_card(card), m_side(side), m_amount(amount), m_toOpponent(toOpponent)
{
    // Do nothing
}

SummonTask::SummonTask(const std::string& cardID, int amount, bool toOpponent)
    : m_amount(amount), m_toOpponent(toOpponent)
{
    m_card = Cards::FindCardByID(cardID);
}

SummonTask::SummonTask(const std::string& cardID, SummonSide side,
                       bool toOpponent)
    : m_side(side), m_toOpponent(toOpponent)
{
    m_card = Cards::FindCardByID(cardID);
}

TaskStatus SummonTask::Impl(Player* player)
{
    Player* summoner = m_toOpponent ? player->opponent : player;

    for (int i = 0; i < m_amount; ++i)
    {
        if (summoner->GetFieldZone()->IsFull())
        {
            return TaskStatus::STOP;
        }

        Entity* summonEntity = nullptr;
        if (m_card.has_value())
        {
            summonEntity = Entity::GetFromCard(summoner, m_card.value());
        }
        else if (!summoner->game->taskStack.entities.empty())
        {
            summonEntity = summoner->game->taskStack.entities[0];
        }

        if (summonEntity == nullptr)
        {
            return TaskStatus::STOP;
        }

        const auto summonMinion = dynamic_cast<Minion*>(summonEntity);
        if (summonMinion == nullptr)
        {
            return TaskStatus::STOP;
        }

        int summonPos;
        switch (m_side)
        {
            case SummonSide::DEFAULT:
            {
                summonPos = -1;
                break;
            }
            case SummonSide::RIGHT:
            {
                if (m_source->zone->GetType() == ZoneType::PLAY)
                {
                    const auto source = dynamic_cast<Playable*>(m_source);
                    summonPos = source->GetZonePosition() + 1;
                }
                else
                {
                    const auto source = dynamic_cast<Minion*>(m_source);
                    summonPos = source->GetLastBoardPos();
                }
                break;
            }
            case SummonSide::DEATHRATTLE:
            {
                if (const auto m = dynamic_cast<Minion*>(m_source))
                {
                    summonPos = m->GetLastBoardPos();
                }
                else if (const auto e = dynamic_cast<Enchantment*>(m_source))
                {
                    const auto target = dynamic_cast<Minion*>(e->GetTarget());
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
                summonPos = m_source->game->taskStack.num - 1;
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

        Generic::Summon(summoner, summonMinion, summonPos);
    }

    return TaskStatus::COMPLETE;
}

ITask* SummonTask::CloneImpl()
{
    return new SummonTask(m_side, m_card, m_amount, m_toOpponent);
}
}  // namespace RosettaStone::SimpleTasks
