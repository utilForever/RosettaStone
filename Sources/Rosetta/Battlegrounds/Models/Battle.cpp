// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Battle.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::Battlegrounds
{
Battle::Battle(Player& player1, Player& player2)
    : m_player1(player1),
      m_player2(player2),
      m_p1Field(m_player1.battleField),
      m_p2Field(m_player2.battleField)
{
    m_player1.battleField = m_player1.recruitField;
    m_player2.battleField = m_player2.recruitField;
}

void Battle::Initialize()
{
    // Determine the player attacks first
    // NOTE: The player with the greater number of minions attacks first.
    // If the number of minions is equal for both players, one of the players
    // is randomly selected to attack first.
    const int p1NumMinions = m_p1Field.GetCount();
    const int p2NumMinions = m_p2Field.GetCount();

    if (p1NumMinions > p2NumMinions)
    {
        m_turn = Turn::PLAYER1;
    }
    else if (p1NumMinions < p2NumMinions)
    {
        m_turn = Turn::PLAYER2;
    }
    else
    {
        m_turn = static_cast<Turn>(Random::get<int>(0, 1));
    }

    m_p1NextAttackerIdx = 0;
    m_p2NextAttackerIdx = 0;

    if (m_turn == Turn::PLAYER1)
    {
        m_p1Field.ForEach([&](MinionData& minion) {
            minion.value().ActivateTask(PowerType::START_OF_COMBAT, m_player1);
        });
        m_p2Field.ForEach([&](MinionData& minion) {
            minion.value().ActivateTask(PowerType::START_OF_COMBAT, m_player2);
        });
    }
    else
    {
        m_p2Field.ForEach([&](MinionData& minion) {
            minion.value().ActivateTask(PowerType::START_OF_COMBAT, m_player2);
        });
        m_p1Field.ForEach([&](MinionData& minion) {
            minion.value().ActivateTask(PowerType::START_OF_COMBAT, m_player1);
        });
    }

    ProcessDestroy(true);
}

void Battle::Run()
{
    Initialize();

    bool prevAttackSuccess = false;

    while (!IsDone())
    {
        if (m_turn == Turn::PLAYER1)
        {
            m_p1Field.ForEachAlive([&](MinionData& owner) {
                m_p1Field.ForEachAlive([&](MinionData& minion) {
                    {
                        owner.value().ActivateTrigger(TriggerType::TURN_START,
                                                      minion.value());
                    };
                });
            });

            m_p2Field.ForEachAlive([&](MinionData& owner) {
                m_p2Field.ForEachAlive([&](MinionData& minion) {
                    {
                        owner.value().ActivateTrigger(TriggerType::TURN_START,
                                                      minion.value());
                    };
                });
            });
        }
        else
        {
            m_p2Field.ForEachAlive([&](MinionData& owner) {
                m_p2Field.ForEachAlive([&](MinionData& minion) {
                    {
                        owner.value().ActivateTrigger(TriggerType::TURN_START,
                                                      minion.value());
                    };
                });
            });

            m_p1Field.ForEachAlive([&](MinionData& owner) {
                m_p1Field.ForEachAlive([&](MinionData& minion) {
                    {
                        owner.value().ActivateTrigger(TriggerType::TURN_START,
                                                      minion.value());
                    };
                });
            });
        }

        const bool curAttackSuccess = Attack();
        if (!prevAttackSuccess && !curAttackSuccess)
        {
            m_turn = Turn::DONE;
            break;
        }

        prevAttackSuccess = curAttackSuccess;
    }

    ProcessResult();

    const int damage = CalculateDamage();
    if (m_result == BattleResult::PLAYER1_WIN)
    {
        m_player2.hero.TakeDamage(m_player2, damage);
    }
    else if (m_result == BattleResult::PLAYER2_WIN)
    {
        m_player1.hero.TakeDamage(m_player1, damage);
    }
}

bool Battle::Attack()
{
    const int attackerIdx = FindAttacker();
    // No minions that can attack, switch players
    if (attackerIdx == -1)
    {
        m_turn = (m_turn == Turn::PLAYER1) ? Turn::PLAYER2 : Turn::PLAYER1;
        return false;
    }

    Minion& attacker = (m_turn == Turn::PLAYER1) ? m_p1Field[attackerIdx]
                                                 : m_p2Field[attackerIdx];
    Minion& target = GetProperTarget(attacker);
    target.TakeDamage(attacker);
    attacker.TakeDamage(target);

    ProcessDestroy(false);

    m_turn = (m_turn == Turn::PLAYER1) ? Turn::PLAYER2 : Turn::PLAYER1;
    return true;
}

int Battle::FindAttacker()
{
    FieldZone& fieldZone = (m_turn == Turn::PLAYER1) ? m_p1Field : m_p2Field;
    int nextAttackerIdx =
        (m_turn == Turn::PLAYER1) ? m_p1NextAttackerIdx : m_p2NextAttackerIdx;

    for (int i = 0; i < fieldZone.GetCount(); ++i)
    {
        if (fieldZone[nextAttackerIdx].GetAttack() > 0)
        {
            return nextAttackerIdx;
        }

        ++nextAttackerIdx;
        if (nextAttackerIdx == fieldZone.GetCount())
        {
            nextAttackerIdx = 0;
        }
    }

    return -1;
}

Minion& Battle::GetProperTarget([[maybe_unused]] Minion& attacker)
{
    auto& minions = (m_turn == Turn::PLAYER1) ? m_p2Field : m_p1Field;

    std::vector<std::size_t> tauntMinions;
    tauntMinions.reserve(MAX_FIELD_SIZE);

    std::size_t minionIdx = 0;
    minions.ForEach([&](const MinionData& minion) {
        if (minion.value().HasTaunt())
        {
            tauntMinions.emplace_back(minionIdx);
        }

        ++minionIdx;
    });

    if (!tauntMinions.empty())
    {
        const auto idx = Random::get<std::size_t>(0, tauntMinions.size() - 1);
        return minions[tauntMinions[idx]];
    }

    const auto idx = Random::get<int>(0, minions.GetCount() - 1);
    return minions[idx];
}

void Battle::ProcessDestroy(bool beforeAttack)
{
    std::vector<std::tuple<int, Minion&>> deadMinions;

    if (m_turn == Turn::PLAYER1)
    {
        m_p2Field.ForEach([&](MinionData& minion) {
            if (minion.value().IsDestroyed())
            {
                deadMinions.emplace_back(
                    std::make_tuple(2, std::ref(minion.value())));
            }
        });

        m_p1Field.ForEach([&](MinionData& minion) {
            if (minion.value().IsDestroyed())
            {
                deadMinions.emplace_back(
                    std::make_tuple(1, std::ref(minion.value())));
            }
        });
    }
    else
    {
        m_p1Field.ForEach([&](MinionData& minion) {
            if (minion.value().IsDestroyed())
            {
                deadMinions.emplace_back(
                    std::make_tuple(1, std::ref(minion.value())));
            }
        });

        m_p2Field.ForEach([&](MinionData& minion) {
            if (minion.value().IsDestroyed())
            {
                deadMinions.emplace_back(
                    std::make_tuple(2, std::ref(minion.value())));
            }
        });
    }

    // A variable to check a minion at the index of next attacker is destroyed
    bool isAttackerDestroyed = false;

    for (auto& deadMinion : deadMinions)
    {
        Minion& minion = std::get<1>(deadMinion);
        Minion removedMinion;

        if (std::get<0>(deadMinion) == 1)
        {
            if (!beforeAttack)
            {
                // If the zone position of minion that is destroyed is lower
                // than nextAttackerIdx and greater than 0, decrease by 1
                if (m_p1NextAttackerIdx < minion.GetZonePosition() &&
                    m_p1NextAttackerIdx > 0)
                {
                    --m_p1NextAttackerIdx;
                }
                // If the turn is player 1 and the zone position of minion that
                // is destroyed equals nextAttackerIdx, keep the value of it
                else if (m_turn == Turn::PLAYER1 &&
                         m_p1NextAttackerIdx == minion.GetZonePosition())
                {
                    isAttackerDestroyed = true;
                }
            }

            m_p1Field.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::DEATH, minion);
            });

            m_p2Field.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::DEATH, minion);
            });

            minion.SetLastFieldPos(minion.GetZonePosition());
            removedMinion = m_p1Field.Remove(minion);
        }
        else
        {
            if (!beforeAttack)
            {
                // If the zone position of minion that is destroyed is lower
                // than nextAttackerIdx and greater than 0, decrease by 1
                if (m_p2NextAttackerIdx < minion.GetZonePosition() &&
                    m_p2NextAttackerIdx > 0)
                {
                    --m_p2NextAttackerIdx;
                }
                // If the turn is player 2 and the zone position of minion that
                // is destroyed equals nextAttackerIdx, keep the value of it
                else if (m_turn == Turn::PLAYER2 &&
                         m_p2NextAttackerIdx == minion.GetZonePosition())
                {
                    isAttackerDestroyed = true;
                }
            }

            m_p1Field.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::DEATH, minion);
            });

            m_p2Field.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::DEATH, minion);
            });

            minion.SetLastFieldPos(minion.GetZonePosition());
            removedMinion = m_p2Field.Remove(minion);
        }

        // Process deathrattle tasks
        if (removedMinion.HasDeathrattle())
        {
            removedMinion.ActivateTask(
                PowerType::DEATHRATTLE,
                std::get<0>(deadMinion) == 1 ? m_player1 : m_player2);
        }
    }

    if (!beforeAttack)
    {
        // If the zone position of minion that is destroyed not equals
        // nextAttackerIdx, increase by 1
        if (!isAttackerDestroyed)
        {
            if (m_turn == Turn::PLAYER1)
            {
                ++m_p1NextAttackerIdx;
            }
            else
            {
                ++m_p2NextAttackerIdx;
            }
        }

        // Check the boundaries of field zone
        if (m_p1NextAttackerIdx == m_p1Field.GetCount())
        {
            m_p1NextAttackerIdx = 0;
        }
        if (m_p2NextAttackerIdx == m_p2Field.GetCount())
        {
            m_p2NextAttackerIdx = 0;
        }
    }
}

bool Battle::IsDone() const
{
    return m_p1Field.IsEmpty() || m_p2Field.IsEmpty() || m_turn == Turn::DONE;
}

void Battle::ProcessResult()
{
    if (m_p1Field.IsEmpty() && !m_p2Field.IsEmpty())
    {
        m_result = BattleResult::PLAYER2_WIN;
    }
    else if (!m_p1Field.IsEmpty() && m_p2Field.IsEmpty())
    {
        m_result = BattleResult::PLAYER1_WIN;
    }
    else
    {
        m_result = BattleResult::DRAW;
    }
}

int Battle::CalculateDamage()
{
    int totalDamage = 0;

    if (m_result == BattleResult::PLAYER1_WIN)
    {
        m_p1Field.ForEach([&](const MinionData& minion) {
            totalDamage += minion.value().GetTier();
        });

        totalDamage += m_player1.currentTier;
    }
    else
    {
        m_p2Field.ForEach([&](const MinionData& minion) {
            totalDamage += minion.value().GetTier();
        });

        totalDamage += m_player2.currentTier;
    }

    return totalDamage;
}

const FieldZone& Battle::GetPlayer1Field() const
{
    return m_p1Field;
}

const FieldZone& Battle::GetPlayer2Field() const
{
    return m_p2Field;
}

int Battle::GetPlayer1NextAttacker() const
{
    return m_p1NextAttackerIdx;
}

int Battle::GetPlayer2NextAttacker() const
{
    return m_p2NextAttackerIdx;
}

BattleResult Battle::GetResult() const
{
    return m_result;
}
}  // namespace RosettaStone::Battlegrounds
