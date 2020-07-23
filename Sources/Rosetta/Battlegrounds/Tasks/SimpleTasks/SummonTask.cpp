// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SummonTask.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
SummonTask::SummonTask(const std::string_view& cardID, int amount,
                       SummonSide side)
    : m_cardID(cardID), m_side(side), m_amount(amount)
{
    // Do nothing
}

int SummonTask::GetPosition(Minion& source, SummonSide side)
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
            if (source.GetZoneType() == ZoneType::PLAY)
            {
                summonPos = source.GetZonePosition();
            }
            else
            {
                summonPos = source.GetLastFieldPos();
            }
            break;
        }
        case SummonSide::RIGHT:
        {
            if (source.GetZoneType() == ZoneType::PLAY)
            {
                summonPos = source.GetZonePosition() + 1;
            }
            else
            {
                summonPos = source.GetLastFieldPos();
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "SummonTask::Impl() - Invalid summon side");
    }

    return summonPos;
}

TaskStatus SummonTask::Run(Player& player, Minion& source)
{
    Card card = Cards::FindCardByID(m_cardID);

    for (int i = 0; i < m_amount; ++i)
    {
        if (player.GetField().IsFull())
        {
            return TaskStatus::STOP;
        }
    }

    Minion summonMinion{ card };

    int summonPos = GetPosition(source, m_side);
    if (summonPos > player.GetField().GetCount())
    {
        summonPos = player.GetField().GetCount();
    }

    player.GetField().Add(summonMinion, summonPos);

    return TaskStatus::COMPLETE;
}

TaskStatus SummonTask::Run(Player& player, Minion& source,
                           [[maybe_unused]] Minion& target)
{
    Card card = Cards::FindCardByID(m_cardID);

    for (int i = 0; i < m_amount; ++i)
    {
        if (player.GetField().IsFull())
        {
            return TaskStatus::STOP;
        }
    }

    Minion summonMinion{ card };

    int summonPos = GetPosition(source, m_side);
    if (summonPos > player.GetField().GetCount())
    {
        summonPos = player.GetField().GetCount();
    }

    player.GetField().Add(summonMinion, summonPos);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
