// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_ACTION_PARAMS_HPP
#define ROSETTASTONE_PLAYMODE_ACTION_PARAMS_HPP

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>
#include <Rosetta/PlayMode/Actions/ActionValidChecker.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief ActionParams class.
//!
//! This class contains several parameter methods for the action such as choose
//! main operation/hand card and get specified target/attacker/number and so on.
//!
class ActionParams
{
 public:
    //! Virtual default destructor.
    virtual ~ActionParams() = default;

    //! Initializes action params by running ActionValidChecker::Check() method.
    //! \param game The game context.
    virtual void Initialize(const Game& game);

    //! Initializes action params by running ActionValidChecker::Check() method.
    //! \param getter The action valid getter.
    void Initialize(ActionValidGetter& getter);

    //! Initializes action params by running ActionValidChecker::Check() method.
    //! \param getter The action valid getter.
    void Initialize(ActionValidGetter&& getter);

    //! Returns the action valid checker.
    //! \return The action valid checker.
    const ActionValidChecker& GetChecker() const;

    //! Returns the main operation using the action valid checker.
    //! \return The chosen main operation.
    virtual MainOpType ChooseMainOp();

    //! Returns the location of minion to put.
    //! \param minions The number of minions in field zone.
    //! \return The chosen location of minion.
    virtual std::size_t GetMinionPutLocation(int minions);

    //! Returns the specified target.
    //! \param targets A list of targets that can specify.
    //! \return The chosen specified target.
    virtual Character* GetSpecifiedTarget(
        const std::vector<Character*>& targets);

    //! Returns a card from a list of choice cards.
    //! \param cards A list of choice cards.
    //! \return A chosen card from a list of choice cards.
    virtual std::size_t ChooseOne(const std::vector<std::size_t>& cards);

    //! Returns a card in hand zone that is playable.
    //! \return A chosen card in hand zone that is playable.
    virtual Playable* ChooseHandCard();

    //! Returns a minion card in field zone that can attack.
    //! \return A chosen minion card in field zone that can attack.
    virtual Character* GetAttacker();

    //! Returns the number using \p actionType and \p choices.
    //! \param actionType The action type.
    //! \param choices The action choices.
    //! \return The chosen number using action type and action choices.
    virtual std::size_t GetNumber(ActionType actionType,
                                  ActionChoices& choices) = 0;

 protected:
    //! Returns the number using \p actionType and \p max.
    //! \param actionType The action type.
    //! \param max The maximum value of the range.
    //! \return The chosen number using action type and maximum value.
    std::size_t GetNumber(ActionType actionType, std::size_t max);

    ActionValidChecker m_checker;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACTION_PARAMS_HPP
