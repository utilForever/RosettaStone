// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Policies/RandomPolicy.hpp>

#include <effolkronium/random.hpp>

namespace RosettaStone
{
TaskMeta RandomPolicy::Next(const Game& game)
{
    using Random = effolkronium::random_static;

    std::vector<TaskID> list = { TaskID::END_TURN };

    Player& player = game.GetCurrentPlayer();
    if (player.GetHand().GetNumOfCards() > 0)
    {
        list.push_back(TaskID::PLAY_CARD);
    }

    if (player.GetField().GetNumOfMinions() > 0)
    {
        list.push_back(TaskID::ATTACK);
    }

    return TaskMeta(TaskMetaTrait(*Random::get(list)));
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
    using Random = effolkronium::random_static;

    std::vector<std::tuple<Entity*, Entity*>> possible;
    const bool summonAvailable = !player.GetField().IsFull();

    for (Entity* entity : player.GetHand().GetAllCards())
    {
        if (entity->GetCost() > player.GetRemainingMana())
        {
            continue;
        }

        switch (entity->card.GetCardType())
        {
            case CardType::MINION:
                if (summonAvailable)
                {
                    possible.emplace_back(std::make_tuple(entity, nullptr));
                }
                break;
            case CardType::SPELL:
                // TODO: Add possible spell lists to vector `possible`.
                break;
            case CardType::WEAPON:
                possible.emplace_back(std::make_tuple(entity, nullptr));
                break;
            default:
                break;
        }
    }

    if (possible.empty())
    {
        return TaskMeta(TaskMetaTrait(TaskID::PLAY_CARD), SizedPtr<Entity*>());
    }
    else
    {
        auto [source, target] = *Random::get(possible);

        SizedPtr<Entity*> ptr;
        if (target != nullptr)
        {
            ptr = SizedPtr<Entity*>(2);
            ptr[0] = source;
            ptr[1] = target;
        }
        else
        {
            ptr = SizedPtr<Entity*>(1);
            ptr[0] = source;
        }

        return TaskMeta(TaskMetaTrait(TaskID::PLAY_CARD), std::move(ptr));
    }
}

TaskMeta RandomPolicy::RequireAttack(Player& player)
{
    using Random = effolkronium::random_static;

    Player& other = *player.opponent;

    std::vector<Character*> sources = player.GetField().GetAllMinions();
    sources.push_back(player.GetHero());

    std::vector<std::tuple<Character*, Character*>> possible;
    for (Character* source : sources)
    {
        if (!source->CanAttack())
        {
            continue;
        }

        Hero* hero = other.GetHero();
        if (source->IsValidCombatTarget(other, hero))
        {
            possible.emplace_back(std::make_tuple(source, hero));
        }

        for (Character* target : other.GetField().GetAllMinions())
        {
            if (source->IsValidCombatTarget(other, target))
            {
                possible.emplace_back(std::make_tuple(source, target));
            }
        }
    }

    if (possible.empty())
    {
        return TaskMeta(TaskMetaTrait(TaskID::ATTACK), SizedPtr<Entity*>());
    }
    else
    {
        auto [source, target] = *Random::get(possible);

        SizedPtr<Entity*> ptr(2);
        ptr[0] = source;
        ptr[1] = target;

        return TaskMeta(TaskMetaTrait(TaskID::ATTACK), std::move(ptr));
    }
}
}  // namespace RosettaStone