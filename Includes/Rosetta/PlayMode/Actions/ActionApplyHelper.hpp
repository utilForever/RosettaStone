// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_ACTION_APPLY_HELPER_HPP
#define ROSETTASTONE_PLAYMODE_ACTION_APPLY_HELPER_HPP

#include <Rosetta/PlayMode/Actions/ActionParams.hpp>

#include <variant>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief ActionApplyHelper class.
//!
//! This class is simple helper for applying action.
//!
class ActionApplyHelper
{
 public:
    //!
    //! \brief NullInfo struct.
    //!
    //! This struct stores the information for null.
    //!
    struct NullInfo
    {
        // Do nothing
    };

    //!
    //! \brief ChooseHandCardInfo struct.
    //!
    //! This struct stores the information for choose hand card.
    //!
    struct ChooseHandCardInfo
    {
        // Do nothing
    };

    //!
    //! \brief MainOpInfo struct.
    //!
    //! This struct stores the information for main operation.
    //!
    struct MainOpInfo
    {
        // Do nothing
    };

    //!
    //! \brief MinionPutLocationInfo struct.
    //!
    //! This struct stores the information for minion put location.
    //!
    struct MinionPutLocationInfo
    {
        explicit MinionPutLocationInfo(int _minions) : minions(_minions)
        {
            // Do nothing
        }

        int minions;
    };

    //!
    //! \brief ChooseAttackerInfo struct.
    //!
    //! This struct stores the information for choose attacker.
    //!
    struct ChooseAttackerInfo
    {
        // Do nothing
    };

    //!
    //! \brief GetSpecifiedTargetInfo struct.
    //!
    //! This struct stores the information for specified target.
    //!
    struct GetSpecifiedTargetInfo
    {
        explicit GetSpecifiedTargetInfo(const std::vector<Character*>& _targets)
            : targets(_targets)
        {
            // Do nothing
        }

        std::vector<Character*> targets;
    };

    //!
    //! \brief ChooseOneInfo struct.
    //!
    //! This struct stores the information for choose one.
    //!
    struct ChooseOneInfo
    {
        explicit ChooseOneInfo(const std::vector<std::size_t>& _cards)
            : cards(_cards)
        {
            // Do nothing
        }

        std::vector<std::size_t> cards;
    };

    //!
    //! \brief ChooseRandomInfo struct.
    //!
    //! This struct stores the information for choose random.
    //!
    struct ChooseRandomInfo
    {
        explicit ChooseRandomInfo(int _maxValue) : maxValue(_maxValue)
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
    //!
    //! \brief ActionParamsChooser class.
    //!
    //! This class inherits from ActionParams class.
    //!
    class ActionParamsChooser : public ActionParams
    {
     public:
        //! Constructs action params chooser with given \p choices and
        //! \p choicesIdx.
        //! \param choices A list of action choices.
        //! \param choicesIdx The index of action choices.
        ActionParamsChooser(const std::vector<int>& choices,
                            std::size_t& choicesIdx);

        //! Returns the flag that whether this chooser has further choices.
        //! \return The flag that whether this chooser has further choices.
        bool HasFurtherChoices() const;

        //! Returns the flag that whether this chooser should skip.
        //! \return The flag that whether this chooser should skip.
        bool ShouldSkip() const;

        //! Returns the number using \p actionType and \p choices.
        //! \param actionType The action type.
        //! \param choices The action choices.
        //! \return The chosen number using action type and action choices.
        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& choices) final;

     private:
        //! Returns the next action choice.
        //! \param min The minimum value of choices range.
        //! \param max The maximum value of choices range.
        //! \return The next action choice.
        int GetNextChoice(int min, [[maybe_unused]] int max) const;

        const std::vector<int>& m_choices;
        std::size_t& m_choicesIdx;
        bool m_shouldSkip;
    };

    //!
    //! \brief ActionParamsCallback class.
    //!
    //! This class inherits from ActionParams class.
    //!
    class ActionParamsCallback : public ActionParams
    {
     public:
        //! Constructs action params callback with given \p choices,
        //! \p choicesIdx and \p result.
        //! \param choices A list of action choices.
        //! \param choicesIdx The index of action choices.
        //! \param result The result of action params callback.
        ActionParamsCallback(const std::vector<int>& choices,
                             std::size_t& choicesIdx, CallbackInfo& result);

        //! Initializes action params by running
        //! ActionValidChecker::Check() method.
        //! \param game The game context.
        void Initialize(const Game& game) override;

        //! Returns the main operation using the action valid checker.
        //! \return The chosen main operation.
        MainOpType ChooseMainOp() override;

        //! Returns a card in hand zone that is playable.
        //! \return A chosen card in hand zone that is playable.
        Playable* ChooseHandCard() override;

        //! Returns a minion card in field zone that can attack.
        //! \return A chosen minion card in field zone that can attack.
        Character* GetAttacker() override;

        //! Returns the location of minion to put.
        //! \param minions The number of minions in field zone.
        //! \return The chosen location of minion.
        std::size_t GetMinionPutLocation(int minions) override;

        //! Returns the specified target.
        //! \param targets A list of targets that can specify.
        //! \return The chosen specified target.
        Character* GetSpecifiedTarget(
            const std::vector<Character*>& targets) override;

        //! Returns a card from a list of choice cards.
        //! \param cards A list of choice cards.
        //! \return A chosen card from a list of choice cards.
        std::size_t ChooseOne(const std::vector<std::size_t>& cards) override;

        //! Returns the number using \p actionType and \p choices.
        //! \param actionType The action type.
        //! \param choices The action choices.
        //! \return The chosen number using action type and action choices.
        std::size_t GetNumber([[maybe_unused]] ActionType actionType,
                              [[maybe_unused]] ActionChoices& choices) override;

     private:
        //! Returns the flag that whether this callback should record.
        //! \return The flag that whether this callback should record.
        bool ShouldRecord() const;

        CallbackInfo& m_result;
        ActionParamsChooser m_choser;
    };

 public:
    //! Appends choice to a list of choices.
    //! \param choice The choice value to append.
    void AppendChoice(int choice);

    //! Clears a list of choices.
    void ClearChoices();

    //! Applies choice by performing action to the game.
    //! \param startBoardGetter A function to get the game.
    template <class StartBoardGetter>
    CallbackInfo ApplyChoices(StartBoardGetter&& startBoardGetter) const
    {
        Game game = startBoardGetter();
        return ApplyChoices(game);
    }

    //! Applies choice by performing action to the game.
    //! \param game The game context.
    CallbackInfo ApplyChoices(Game& game) const;

    //! Applies choice by performing action to the game.
    //! \param game The game context.
    //! \param result The result of the game (player1 and player2).
    CallbackInfo ApplyChoices(Game& game,
                              std::tuple<PlayState, PlayState>& result) const;

 private:
    std::vector<int> m_choices;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACTION_APPLY_HELPER_HPP
