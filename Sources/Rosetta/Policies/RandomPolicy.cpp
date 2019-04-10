// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Policies/RandomPolicy.hpp>

#include <effolkronium/random.hpp>

namespace RosettaStone
{
TaskMeta RandomPolicy::Next(const Game& game)
{
    return TaskMeta();
}

TaskMeta RandomPolicy::RequireMulligan(Player& player)
{
    using Random = effolkronium::random_static;

    std::vector<std::size_t> selected;
    for (std::size_t id : player.choice.value().choices)
    {
        if (Random::get(0, 1) == 0)
        {
            selected.push_back(id);
        }
    }

    return TaskMeta(TaskMetaTrait(TaskID::MULLIGAN), std::move(selected));
}

TaskMeta RandomPolicy::RequirePlayCard(Player& player)
{
    (void)player;
    return TaskMeta();
}

TaskMeta RandomPolicy::RequireAttack(Player& player)
{
    (void)player;
    return TaskMeta();
}
}  // namespace RosettaStone