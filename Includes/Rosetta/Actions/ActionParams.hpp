// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_PARAMS_HPP
#define ROSETTASTONE_ACTION_PARAMS_HPP

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionType.hpp>
#include <Rosetta/Actions/ActionValidChecker.hpp>

namespace RosettaStone
{
//!
//! \brief ActionParams class.
//!
class ActionParams
{
 public:
    virtual ~ActionParams() = default;

    void Initialize(const Game& game);
    void Initialize(const ActionValidGetter& getter);

    const ActionValidChecker& GetChecker() const;

    MainOpType ChooseMainOp();

    size_t GetMinionPutLocation(int minions);

    Character* GetSpecifiedTarget(const std::vector<Character*>& targets);

    size_t ChooseOne(std::vector<size_t> cards);

    Entity* ChooseHandCard();

    Character* GetAttacker();

    virtual size_t GetNumber(ActionType actionType, ActionChoices& choices) = 0;

 private:
    size_t GetNumber(ActionType actionType, size_t exclusiveMax);

    ActionValidChecker m_checker;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_PARAMS_HPP
