// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_RANDOM_POLICY_HPP
#define ROSETTASTONE_RANDOM_POLICY_HPP

#include <Rosetta/Policies/BasicPolicy.hpp>

namespace RosettaStone
{
class RandomPolicy : public BasicPolicy
{
 private:
    //! Virtual method for MulliganTask requirement.
    TaskMeta RequireMulligan(Player& player) override;

    //! Virtual method for PlayCardTask requirement.
    TaskMeta RequirePlayCard(Player& player) override;

    //! Virtual method for AttackTask requirement.
    TaskMeta RequireAttack(Player& player) override;
};
}  // namespace RosettaStone

#endif