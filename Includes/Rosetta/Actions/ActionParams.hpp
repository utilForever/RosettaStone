// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_PARAMS_HPP
#define ROSETTASTONE_ACTION_PARAMS_HPP

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

    int GetMinionPutLocation(int minions);

    Character* GetSpecifiedTarget(const std::vector<Character*>& targets);

    int ChooseOne(int choices);

    Entity* ChooseHandCard();

    Character* GetAttacker();

    virtual int GetNumber(ActionType actionType, std::vector<int>& choices) = 0;

 private:
    int GetNumber(ActionType actionType, int exclusiveMax);

    ActionValidChecker m_checker;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_PARAMS_HPP
