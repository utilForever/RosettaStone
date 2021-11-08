// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawSpellTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawSpellTask::DrawSpellTask(int amount, SpellSchool spellSchool,
                             bool addToStack)
    : m_amount(amount), m_spellSchool(spellSchool), m_addToStack(addToStack)
{
    // Do nothing
}

DrawSpellTask::DrawSpellTask(DrawSpellType drawSpellType, int amount,
                             bool addToStack)
    : m_amount(amount), m_drawSpellType(drawSpellType), m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DrawSpellTask::Impl(Player* player)
{
    if (m_addToStack)
    {
        player->game->taskStack.playables.clear();
    }

    auto deck = player->GetDeckZone()->GetAll();
    if (deck.empty())
    {
        return TaskStatus::STOP;
    }

    std::vector<Playable*> cards;
    cards.reserve(m_amount);

    for (auto& deckCard : deck)
    {
        if (deckCard->card->GetCardType() != CardType::SPELL)
        {
            continue;
        }

        if (auto spell = dynamic_cast<Spell*>(deckCard);
            (spell && spell->GetSpellSchool() == m_spellSchool) ||
            m_spellSchool == SpellSchool::NONE)
        {
            cards.emplace_back(deckCard);
        }
    }

    if (cards.empty())
    {
        return TaskStatus::STOP;
    }

    if (static_cast<int>(cards.size()) <= m_amount)
    {
        for (int i = 0; i < m_amount; ++i)
        {
            if (m_addToStack)
            {
                player->game->taskStack.playables.emplace_back(cards[i]);
            }

            Generic::Draw(player, cards[i]);
        }
    }
    else
    {
        for (int i = 0; i < m_amount; ++i)
        {
            const auto pick = Random::get<std::size_t>(0, cards.size() - 1);

            if (m_addToStack)
            {
                player->game->taskStack.playables.emplace_back(cards[pick]);
            }

            Generic::Draw(player, cards[pick]);
            cards.erase(std::begin(cards) + pick);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawSpellTask::CloneImpl()
{
    return std::make_unique<DrawSpellTask>(m_amount, m_spellSchool,
                                           m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks