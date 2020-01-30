// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Tasks/SimpleTasks/QuestProgressTask.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

namespace RosettaStone::SimpleTasks
{
QuestProgressTask::QuestProgressTask(const std::string& questRewardID)
    : m_card(Cards::FindCardByID(questRewardID))
{
    // Do nothing
}

TaskStatus QuestProgressTask::Impl(Player* player)
{
    auto spell = dynamic_cast<Spell*>(m_source);
    if (spell == nullptr)
    {
        return TaskStatus::STOP;
    }

    spell->IncreaseQuestProgress();

    if (spell->GetQuestProgress() == spell->GetQuestProgressTotal())
    {
        Playable* reward = Entity::GetFromCard(player, m_card);

        // Reward card is hero power or minion
        if (const auto heroPower = dynamic_cast<HeroPower*>(reward); heroPower)
        {
            delete player->GetHero()->heroPower;
            player->GetHero()->heroPower = heroPower;
        }
        else
        {
            Generic::AddCardToHand(player, reward);
        }

        spell->SetGameTag(GameTag::REVEALED, 1);

        // Move quest to graveyard
        player->GetSecretZone()->quest = nullptr;
        player->GetGraveyardZone()->Add(spell);

        return TaskStatus::COMPLETE;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> QuestProgressTask::CloneImpl()
{
    return std::make_unique<QuestProgressTask>(m_card->id);
}
}  // namespace RosettaStone::SimpleTasks
