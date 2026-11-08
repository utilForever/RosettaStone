// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <algorithm>

namespace RosettaStone::PlayMode
{
namespace
{
namespace Schema = PolicySchema;

std::size_t FindSlot(const std::vector<int>& ids, int id)
{
    const auto found = std::ranges::find(ids, id);

    if (found == ids.end())
    {
        throw std::invalid_argument("Policy action has no visible slot");
    }

    return static_cast<std::size_t>(found - ids.begin());
}

std::size_t EncodeIndex(const PlayerAction& action,
                        const std::vector<int>& hand,
                        const std::vector<int>& targets,
                        const std::vector<int>& choices)
{
    switch (action.type)
    {
        case PlayerActionType::END_TURN:
            return Schema::END_TURN;
        case PlayerActionType::PLAY_CARD:
        {
            if (action.fieldPos < -1 ||
                action.fieldPos >= static_cast<int>(Schema::POSITION_SLOTS) ||
                action.chooseOne < 0 ||
                action.chooseOne > static_cast<int>(Schema::OPTION_SLOTS))
            {
                throw std::invalid_argument("Policy play exceeds v1 layout");
            }

            // Default/Choose Both and option one never coexist for a source.
            const auto option = std::max(0, action.chooseOne - 1);
            const auto position = std::max(0, action.fieldPos);

            return Schema::PLAY_CARD +
                   ((FindSlot(hand, action.sourceID) * Schema::TARGET_SLOTS +
                     FindSlot(targets, action.targetID)) *
                        Schema::POSITION_SLOTS +
                    position) *
                       Schema::OPTION_SLOTS +
                   option;
        }
        case PlayerActionType::ATTACK:
        {
            const auto source = FindSlot(targets, action.sourceID);
            const auto target = FindSlot(targets, action.targetID);

            if (source == 0 || source > Schema::CHARACTER_SLOTS ||
                target <= Schema::CHARACTER_SLOTS)
            {
                throw std::invalid_argument("Policy attack has invalid owners");
            }

            return Schema::ATTACK + (source - 1) * Schema::CHARACTER_SLOTS +
                   target - Schema::CHARACTER_SLOTS - 1;
        }
        case PlayerActionType::HERO_POWER:
            return Schema::HERO_POWER + FindSlot(targets, action.targetID);
        case PlayerActionType::CHOOSE:
            return Schema::CHOOSE + FindSlot(choices, action.choiceID);
    }

    throw std::invalid_argument("Unknown policy action type");
}
}  // namespace

PolicyActions::PolicyActions(const Game& game)
{
    const auto actions = EnumerateActions(game);

    if (actions.empty())
    {
        return;
    }

    const auto* actor = game.GetCurrentPlayer();
    const auto cards = actor->GetHandZone()->GetAll();
    const auto choices =
        actor->choice ? actor->choice->choices : std::vector<int>{};

    if (cards.size() > ObservationSchema::HAND_SLOTS ||
        choices.size() > ObservationSchema::CHOICE_SLOTS)
    {
        throw std::invalid_argument(
            "Policy hand or choices exceed v1 capacity");
    }

    std::vector<int> hand;

    for (const auto* card : cards)
    {
        if (card->card->chooseCardIDs.size() > Schema::OPTION_SLOTS)
        {
            throw std::invalid_argument(
                "Policy has too many Choose One options");
        }

        hand.push_back(card->GetGameTag(GameTag::ENTITY_ID));
    }

    std::vector<int> targets(Schema::TARGET_SLOTS, -1);
    std::size_t owner = 0;

    for (const auto* player :
         { actor, static_cast<const Player*>(actor->opponent) })
    {
        const auto board = player->GetFieldZone()->GetAll();

        if (board.size() > ObservationSchema::BOARD_SLOTS)
        {
            throw std::invalid_argument("Policy board exceeds v1 capacity");
        }

        const auto first = 1 + owner * Schema::CHARACTER_SLOTS;
        targets[first] = player->GetHero()->GetGameTag(GameTag::ENTITY_ID);

        for (std::size_t slot = 0; slot < board.size(); ++slot)
        {
            targets[first + 1 + slot] =
                board[slot]->GetGameTag(GameTag::ENTITY_ID);
        }

        ++owner;
    }

    for (const auto& action : actions)
    {
        const auto index = EncodeIndex(action, hand, targets, choices);

        if (index >= Schema::NUM_ACTIONS ||
            !m_actions.emplace(index, action).second)
        {
            throw std::invalid_argument("Policy actions do not fit v1 layout");
        }

        m_mask[index] = 1;
    }
}

std::size_t PolicyActions::Encode(const PlayerAction& action) const
{
    for (const auto& [index, legal] : m_actions)
    {
        if (legal == action)
        {
            return index;
        }
    }

    throw std::invalid_argument("Cannot encode an illegal policy action");
}

PlayerAction PolicyActions::Decode(std::size_t index) const
{
    const auto found = m_actions.find(index);

    if (found == m_actions.end())
    {
        throw std::invalid_argument("Cannot decode a masked policy index");
    }

    return found->second;
}

const PolicySchema::LegalMask& PolicyActions::GetLegalMask() const
{
    return m_mask;
}
}  // namespace RosettaStone::PlayMode
