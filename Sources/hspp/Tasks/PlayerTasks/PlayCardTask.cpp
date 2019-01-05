// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Targeting.hpp>
#include <hspp/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayWeaponTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
PlayCardTask::PlayCardTask(TaskAgent& agent, Entity* source, int fieldPos,
                           Entity* target)
    : ITask(source, target),
      m_agent(agent),
      m_requirement(TaskID::SELECT_CARD, agent),
      m_fieldPos(fieldPos)
{
    // Do nothing
}

TaskID PlayCardTask::GetTaskID() const
{
    return TaskID::PLAY_CARD;
}

MetaData PlayCardTask::Impl(Player& player)
{
    BYTE handIndex;

    if (m_source != nullptr)
    {
        const auto handIter = std::find(player.GetHand().begin(),
                                        player.GetHand().end(), m_source);
        handIndex = static_cast<BYTE>(
            std::distance(player.GetHand().begin(), handIter));
    }
    else
    {
        TaskMeta serialized;

        // Get response from GameInterface
        m_requirement.Interact(player.GetID(), serialized);

        using RequireTaskMeta = FlatData::ResponsePlayCard;
        const auto& buffer = serialized.GetBuffer();
        const auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

        if (req == nullptr)
        {
            return MetaData::PLAY_CARD_FLATBUFFER_NULLPTR;
        }

        handIndex = req->cardIndex();
    }

    Card* card = player.GetHand()[handIndex]->card;

    // Verify index of card hand
    if (handIndex >= player.GetHand().size())
    {
        return MetaData::PLAY_CARD_IDX_OUT_OF_RANGE;
    }

    // Verify mana is sufficient
    if (card->cost > player.GetAvailableMana())
    {
        return MetaData::PLAY_CARD_NOT_ENOUGH_MANA;
    }

    // Verify target is valid
    if (!Targeting::IsValidTarget(card, m_target))
    {
        return MetaData::PLAY_CARD_INVALID_TARGET;
    }

    Entity* entity = player.GetHand()[handIndex];

    // Erase from user's hand
    if (player.GetHand().size() == 1)
    {
        player.GetHand().clear();
    }
    else
    {
        player.GetHand().erase(player.GetHand().begin() + handIndex);
    }

    // Pass to sub-logic
    switch (entity->card->cardType)
    {
        case CardType::MINION:
            return PlayMinionTask(m_agent, entity, m_fieldPos, m_target)
                .Run(player);
        case CardType::WEAPON:
            return PlayWeaponTask(entity).Run(player);
        case CardType::SPELL:
            return PlaySpellTask(m_agent, entity, m_target).Run(player);
        default:
            return MetaData::PLAY_CARD_INVALID_CARD_TYPE;
    }
}
}  // namespace Hearthstonepp::PlayerTasks