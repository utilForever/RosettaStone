// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionValidChecker.hpp>
#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>

namespace RosettaStone::PlayMode
{
void ActionValidChecker::Reset()
{
    m_opMapSize = 0;
}

void ActionValidChecker::Check(const Game& game)
{
    Check(ActionValidGetter(game));
}

void ActionValidChecker::Check(ActionValidGetter& getter)
{
    Reset();

    m_actionTargets.Analyze(getter);

    m_playableCards.clear();
    getter.ForEachPlayableCard([&](Playable* card) {
        m_playableCards.emplace_back(card);
        return true;
    });

    if (!m_playableCards.empty())
    {
        m_opMap[m_opMapSize] = MainOpType::PLAY_CARD;
        ++m_opMapSize;
    }

    m_attackers.clear();
    getter.ForEachAttacker([&](Character* character) {
        m_attackers.emplace_back(character);
        return true;
    });

    if (!m_attackers.empty())
    {
        m_opMap[m_opMapSize] = MainOpType::ATTACK;
        ++m_opMapSize;
    }

    if (getter.CanUseHeroPower())
    {
        m_opMap[m_opMapSize] = MainOpType::USE_HERO_POWER;
        ++m_opMapSize;
    }

    m_opMap[m_opMapSize] = MainOpType::END_TURN;
    ++m_opMapSize;
}

void ActionValidChecker::Check(ActionValidGetter&& getter)
{
    Reset();

    m_actionTargets.Analyze(getter);

    m_playableCards.clear();
    getter.ForEachPlayableCard([&](Playable* card) {
        m_playableCards.emplace_back(card);
        return true;
    });

    if (!m_playableCards.empty())
    {
        m_opMap[m_opMapSize] = MainOpType::PLAY_CARD;
        ++m_opMapSize;
    }

    m_attackers.clear();
    getter.ForEachAttacker([&](Character* character) {
        m_attackers.emplace_back(character);
        return true;
    });

    if (!m_attackers.empty())
    {
        m_opMap[m_opMapSize] = MainOpType::ATTACK;
        ++m_opMapSize;
    }

    if (getter.CanUseHeroPower())
    {
        m_opMap[m_opMapSize] = MainOpType::USE_HERO_POWER;
        ++m_opMapSize;
    }

    m_opMap[m_opMapSize] = MainOpType::END_TURN;
    ++m_opMapSize;
}

const std::array<MainOpType, 4>& ActionValidChecker::GetMainActions() const
{
    return m_opMap;
}

int ActionValidChecker::GetMainActionsCount() const
{
    return static_cast<int>(m_opMapSize);
}

const std::vector<Playable*>& ActionValidChecker::GetPlayableCards() const
{
    return m_playableCards;
}

const std::vector<Character*>& ActionValidChecker::GetAttackers() const
{
    return m_attackers;
}

MainOpType ActionValidChecker::GetMainOpType(std::size_t choice) const
{
    return m_opMap[choice];
}
}  // namespace RosettaStone::PlayMode