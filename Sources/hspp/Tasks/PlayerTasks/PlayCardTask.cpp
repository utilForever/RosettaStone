// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Targeting.hpp>
#include <hspp/Policies/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayWeaponTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
PlayCardTask::PlayCardTask(Entity* source, int fieldPos, Entity* target)
    : ITask(source, target), m_fieldPos(fieldPos)
{
    // Do nothing
}

TaskID PlayCardTask::GetTaskID() const
{
    return TaskID::PLAY_CARD;
}

TaskStatus PlayCardTask::Impl(Player& player)
{
    std::size_t handIndex;

    if (m_source != nullptr)
    {
        auto& hand = player.GetHand();
        const auto handPos = hand.FindCardPos(*m_source).value_or(
            std::numeric_limits<std::size_t>::max());
        if (handPos == std::numeric_limits<std::size_t>::max())
        {
            return TaskStatus::PLAY_CARD_INVALID_POSITION;
        }

        handIndex = static_cast<std::size_t>(handPos);
    }
    else
    {
        TaskMeta req = player.GetPolicy().Require(player, TaskID::PLAY_CARD);

        if (!req.HasObjects())
        {
            return TaskStatus::PLAY_CARD_INVALID_REQUIRE;
        }

        handIndex = req.GetObject<std::size_t>();
    }

    Entity* entity = player.GetHand().GetCard(handIndex);

    // Verify index of card hand
    if (handIndex >= player.GetHand().GetNumOfCards())
    {
        return TaskStatus::PLAY_CARD_IDX_OUT_OF_RANGE;
    }

    // Verify mana is sufficient
    if (entity->card.cost > player.currentMana)
    {
        return TaskStatus::PLAY_CARD_NOT_ENOUGH_MANA;
    }

    // Verify target is valid
    if (!Generic::IsValidTarget(entity, m_target))
    {
        return TaskStatus::PLAY_CARD_INVALID_TARGET;
    }

    // Erase from user's hand
    player.GetHand().RemoveCard(*entity);

    entity->SetOwner(player);

    // Pass to sub-logic
    switch (entity->card.cardType)
    {
        case CardType::MINION:
            return PlayMinionTask(entity, m_fieldPos, m_target).Run(player);
        case CardType::WEAPON:
            return PlayWeaponTask(entity).Run(player);
        case CardType::SPELL:
            return PlaySpellTask(entity, m_target).Run(player);
        default:
            return TaskStatus::PLAY_CARD_INVALID_CARD_TYPE;
    }
}
}  // namespace Hearthstonepp::PlayerTasks