// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ReplaceHeroTask.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ReplaceHeroTask::ReplaceHeroTask(const std::string_view& heroCard,
                                 const std::string_view& heroPowerCard,
                                 const std::string_view& weaponCard)
{
    if (!heroCard.empty())
    {
        m_heroCard = Cards::FindCardByID(heroCard);
    }

    if (!heroPowerCard.empty())
    {
        m_heroPowerCard = Cards::FindCardByID(heroPowerCard);
    }

    if (!weaponCard.empty())
    {
        m_weaponCard = Cards::FindCardByID(weaponCard);
    }
}

ReplaceHeroTask::ReplaceHeroTask(Card* heroCard, Card* heroPowerCard,
                                 Card* weaponCard)
    : m_heroCard(heroCard),
      m_heroPowerCard(heroPowerCard),
      m_weaponCard(weaponCard)
{
    // Do nothing
}

TaskStatus ReplaceHeroTask::Impl(Player* player)
{
    if (!player)
    {
        return TaskStatus::STOP;
    }

    if (const auto playable = dynamic_cast<Playable*>(m_source))
    {
        playable->player->GetSetasideZone()->Add(
            playable->zone->Remove(playable));
    }

    player->AddHeroAndPower(m_heroCard, m_heroPowerCard);

    if (m_weaponCard)
    {
        const auto weapon =
            dynamic_cast<Weapon*>(Entity::GetFromCard(player, m_weaponCard));

        player->GetHero()->AddWeapon(*weapon);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ReplaceHeroTask::CloneImpl()
{
    return std::make_unique<ReplaceHeroTask>(m_heroCard, m_heroPowerCard,
                                             m_weaponCard);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
