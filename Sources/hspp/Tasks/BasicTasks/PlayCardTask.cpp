// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/PlayCardTask.h>
#include <hspp/Tasks/BasicTasks/PlayMinionTask.h>
#include <hspp/Tasks/BasicTasks/PlaySpellTask.h>
#include <hspp/Tasks/BasicTasks/PlayWeaponTask.h>

namespace Hearthstonepp::BasicTasks
{
PlayCardTask::PlayCardTask(TaskAgent& agent, Entity* source, int fieldPos,
                           Entity* target)
    : m_agent(agent),
      m_requirement(TaskID::SELECT_CARD, agent),
      m_source(source),
      m_fieldPos(fieldPos),
      m_target(target)
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
        const auto handIter =
            std::find(player.hand.begin(), player.hand.end(), m_source);
        handIndex =
            static_cast<BYTE>(std::distance(player.hand.begin(), handIter));
    }
    else
    {
        TaskMeta serialized;

        // Get response from GameInterface
        m_requirement.Interact(player.id, serialized);

        using RequireTaskMeta = FlatData::ResponsePlayCard;
        const auto& buffer = serialized.GetBuffer();
        const auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

        if (req == nullptr)
        {
            return MetaData::PLAY_CARD_FLATBUFFER_NULLPTR;
        }

        handIndex = req->cardIndex();
    }

    // Verify index of card hand
    if (handIndex >= player.hand.size())
    {
        return MetaData::PLAY_CARD_IDX_OUT_OF_RANGE;
    }

    // Verify mana is sufficient
    if (player.hand[handIndex]->card->cost > player.existMana)
    {
        return MetaData::PLAY_CARD_NOT_ENOUGH_MANA;
    }

    Entity* entity = player.hand[handIndex];

    // Erase from user's hand
    if (player.hand.size() == 1)
    {
        player.hand.clear();
    }
    else
    {
        player.hand.erase(player.hand.begin() + handIndex);
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
}  // namespace Hearthstonepp::BasicTasks