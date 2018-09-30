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
PlayCardTask::PlayCardTask(TaskAgent& agent)
    : m_agent(agent), m_requirement(TaskID::SELECT_CARD, agent)
{
    // Do Nothing
}

TaskID PlayCardTask::GetTaskID() const
{
    return TaskID::PLAY_CARD;
}

MetaData PlayCardTask::Impl(Player& player1, Player& player2)
{
    TaskMeta serialized;
    // Get Response from GameInterface
    m_requirement.Interact(player1.id, serialized);

    using RequireTaskMeta = FlatData::ResponsePlayCard;
    const auto& buffer = serialized.GetBuffer();
    auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::PLAY_CARD_FLATBUFFER_NULLPTR;
    }

    BYTE cardIndex = req->cardIndex();

    // Card Hand Index Verification
    if (cardIndex >= player1.hand.size())
    {
        return MetaData::PLAY_CARD_IDX_OUT_OF_RANGE;
    }
    // Sufficient Mana Verification
    if (player1.hand[cardIndex]->card->cost > player1.existMana)
    {
        return MetaData::PLAY_CARD_NOT_ENOUGH_MANA;
    }

    Entity* entity = player1.hand[cardIndex];

    // erase from user's hand
    player1.hand.erase(player1.hand.begin() + cardIndex);

    // Pass to Sub Logics
    switch (entity->card->cardType)
    {
        case CardType::MINION:
            return PlayMinionTask(m_agent, entity).Run(player1, player2);
        case CardType::WEAPON:
            return PlayWeaponTask(entity).Run(player1, player2);
        case CardType::SPELL:
            return PlaySpellTask(m_agent, entity).Run(player1, player2);
        default:
            return MetaData::PLAY_CARD_INVALID_CARD_TYPE;
    }
}
}  // namespace Hearthstonepp::BasicTasks