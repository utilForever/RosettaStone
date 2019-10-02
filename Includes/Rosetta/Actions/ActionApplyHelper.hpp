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
                           std::size_t& choicesIdx);

        bool HasFurtherChoices() const;

        bool ShouldSkip() const;

        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& actionChoices) final;

     private:
        int GetNextChoice(int min, [[maybe_unused]] int max) const;

        const std::vector<int>& m_choices;
        std::size_t& m_choicesIdx;
        bool m_shouldSkip;
    };

    class ActionParamsCallback : public ActionParams
    {
     public:
        ActionParamsCallback(const std::vector<int>& choices,
                             std::size_t& choicesIdx, CallbackInfo& result);

        void Initialize(const Game& game) override;

        MainOpType ChooseMainOp() override;

        Entity* ChooseHandCard() override;

        Character* GetAttacker() override;

        std::size_t GetMinionPutLocation(int minions) override;

        Character* GetSpecifiedTarget(
            const std::vector<Character*>& targets) override;

        std::size_t ChooseOne(const std::vector<std::size_t>& cards) override;

        std::size_t GetNumber([[maybe_unused]] ActionType actionType,
                              [[maybe_unused]] ActionChoices& choices) override;

     private:
        bool ShouldRecord() const;

        CallbackInfo& m_result;
        ActionParamsChoser m_choser;
    };

 public:
    void AppendChoice(int choice);

    void ClearChoices();

    template <class StartBoardGetter>
    CallbackInfo ApplyChoices(StartBoardGetter&& startBoardGetter) const
    {
        Game game = startBoardGetter();
        return ApplyChoices(game);
    }

    CallbackInfo ApplyChoices(Game& game) const;

    CallbackInfo ApplyChoices(Game& game, PlayState& result) const;

 private:
    std::vector<int> m_choices;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_APPLY_HELPER_HPP
