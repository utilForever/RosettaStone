// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_APPLY_HELPER_HPP
#define ROSETTASTONE_ACTION_APPLY_HELPER_HPP

#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Models/Entity.hpp>

#include <utility>
#include <variant>
#include <vector>

namespace RosettaStone
{
//!
//! \brief ActionApplyHelper class.
//!
//! This class is simple helper for applying action.
//!
class ActionApplyHelper
{
 public:
    struct NullInfo
    {
        // Do nothing
    };

    struct ChooseHandCardInfo
    {
        // Do nothing
    };

    struct MainOpInfo
    {
        // Do nothing
    };

    struct MinionPutLocationInfo
    {
        MinionPutLocationInfo(int _minions) : minions(_minions)
        {
            // Do nothing
        }

        int minions;
    };

    struct ChooseAttackerInfo
    {
        // Do nothing
    };

    struct GetSpecifiedTargetInfo
    {
        GetSpecifiedTargetInfo(std::vector<Character*> _targets)
            : targets(std::move(_targets))
        {
            // Do nothing
        }

        std::vector<Character*> targets;
    };

    struct ChooseOneInfo
    {
        ChooseOneInfo(std::vector<std::size_t> _cards)
            : cards(std::move(_cards))
        {
            // Do nothing
        }

        std::vector<std::size_t> cards;
    };

    struct ChooseRandomInfo
    {
        ChooseRandomInfo(int _maxValue) : maxValue(_maxValue)
        {
            // Do nothing
        }

        int maxValue;
    };

    using CallbackInfo = std::variant<NullInfo, MainOpInfo, ChooseHandCardInfo,
                                      MinionPutLocationInfo, ChooseAttackerInfo,
                                      GetSpecifiedTargetInfo, ChooseOneInfo>;

    using StartBoardGetter = std::function<Game()>;

 private:
    class ActionParamsChoser : public ActionParams
    {
     public:
        ActionParamsChoser(const std::vector<int>& choices,
                           std::size_t& choicesIdx)
            : m_choices(choices), m_choicesIdx(choicesIdx), m_shouldSkip(false)
        {
            // Do nothing
        }

        bool HasFurtherChoices() const
        {
            return m_choicesIdx <= m_choices.size();
        }

        bool ShouldSkip() const
        {
            return m_shouldSkip;
        }

        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& actionChoices) final
        {
            m_shouldSkip = false;

            if (actionType != ActionType::MAIN_ACTION)
            {
                if (actionChoices.Size() == 1)
                {
                    m_shouldSkip = true;
                    return 0;
                }
            }

            return GetNextChoice(0, actionChoices.Size());
        }

     private:
        int GetNextChoice(int min, [[maybe_unused]] int max)
        {
            if (m_choicesIdx >= m_choices.size())
            {
                ++m_choicesIdx;
                return min;
            }

            const int choice = m_choices[m_choicesIdx];
            ++m_choicesIdx;

            return choice;
        }

        const std::vector<int>& m_choices;
        std::size_t& m_choicesIdx;
        bool m_shouldSkip;
    };

    class ActionParamsCallback : public ActionParams
    {
     public:
        ActionParamsCallback(const std::vector<int>& choices,
                             std::size_t& choicesIdx, CallbackInfo& result)
            : m_result(result), m_choser(choices, choicesIdx)
        {
        }

        void Initialize(const Game& game) override
        {
            m_result = NullInfo();
            m_choser.Initialize(game);
        }

        MainOpType ChooseMainOp() override
        {
            auto ret = m_choser.ChooseMainOp();

            if (ShouldRecord())
            {
                m_result = MainOpInfo();
            }

            return ret;
        }

        Entity* ChooseHandCard() override
        {
            auto ret = m_choser.ChooseHandCard();

            if (ShouldRecord())
            {
                m_result = ChooseHandCardInfo();
            }

            return ret;
        }

        Character* GetAttacker() override
        {
            auto ret = m_choser.GetAttacker();

            if (ShouldRecord())
            {
                m_result = ChooseAttackerInfo();
            }

            return ret;
        }

        std::size_t GetMinionPutLocation(int minions) override
        {
            auto ret = m_choser.GetMinionPutLocation(minions);

            if (ShouldRecord())
            {
                m_result = MinionPutLocationInfo(minions);
            }

            return ret;
        }

        Character* GetSpecifiedTarget(
            const std::vector<Character*>& targets) override
        {
            auto ret = m_choser.GetSpecifiedTarget(targets);

            if (ShouldRecord())
            {
                m_result = GetSpecifiedTargetInfo(targets);
            }

            return ret;
        }

        std::size_t ChooseOne(const std::vector<std::size_t>& cards) override
        {
            auto ret = m_choser.ChooseOne(cards);

            if (ShouldRecord())
            {
                m_result = ChooseOneInfo(cards);
            }

            return ret;
        }

        std::size_t GetNumber([[maybe_unused]] ActionType actionType,
                              [[maybe_unused]] ActionChoices& choices) override
        {
            // Do nothing
            return 0;
        }

     private:
        bool ShouldRecord() const
        {
            if (!std::holds_alternative<NullInfo>(m_result))
            {
                return false;
            }
            if (m_choser.ShouldSkip())
            {
                return false;
            }
            if (m_choser.HasFurtherChoices())
            {
                return false;
            }

            return true;
        }

        CallbackInfo& m_result;
        ActionParamsChoser m_choser;
    };

 public:
    void AppendChoice(int choice)
    {
        m_choices.push_back(choice);
    }

    void ClearChoices()
    {
        m_choices.clear();
    }

    template <class StartBoardGetter>
    CallbackInfo ApplyChoices(StartBoardGetter&& startBoardGetter) const
    {
        Game game = startBoardGetter();
        return ApplyChoices(game);
    }

    CallbackInfo ApplyChoices(Game& game) const
    {
        PlayState result;
        return ApplyChoices(game, result);
    }

    CallbackInfo ApplyChoices(Game& game, PlayState& result) const
    {
        CallbackInfo info = NullInfo();
        size_t choicesIdx = 0;
        ActionParamsCallback actionCallback(m_choices, choicesIdx, info);

        while (m_choices.size() > choicesIdx)
        {
            actionCallback.Initialize(game);
            result = game.PerformAction(actionCallback);
        }

        return info;
    }

 private:
    std::vector<int> m_choices;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_APPLY_HELPER_HPP
