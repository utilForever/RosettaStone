// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

namespace RosettaStone::PlayMode::Generic
{
void CastSpell(Player* player, Spell* spell, Character* target, int chooseOne)
{
    player->game->taskQueue.StartEvent();

    if (spell->IsSecret() || spell->IsQuest() || spell->IsSidequest())
    {
        // Process trigger
        if (spell->card->power.GetTrigger())
        {
            spell->card->power.GetTrigger()->Activate(spell);
        }

        player->GetSecretZone()->Add(spell);
        spell->SetExhausted(true);
    }
    else
    {
        // Process trigger
        if (spell->card->power.GetTrigger())
        {
            spell->card->power.GetTrigger()->Activate(spell);
        }

        // Process aura
        if (spell->card->power.GetAura())
        {
            spell->card->power.GetAura()->Activate(spell);
        }

        // Process power or combo tasks
        if (spell->HasCombo() && player->IsComboActive())
        {
            spell->ActivateTask(PowerType::COMBO, target);
        }
        else
        {
            spell->ActivateTask(PowerType::POWER, target, chooseOne);
        }

        // Process outcast tasks
        if (spell->HasOutcast() &&
            (spell->GetZonePosition() == 0 ||
             spell->GetZonePosition() == player->GetHandZone()->GetCount()))
        {
            spell->ActivateTask(PowerType::OUTCAST, target);
        }

        if (spell->IsTwinspell())
        {
            const auto twinspell = Entity::GetFromCard(
                player, Cards::FindCardByID(spell->card->id + "ts"));
            AddCardToHand(player, twinspell);
        }

        // Check card has overload
        if (spell->HasOverload())
        {
            const int amount = spell->GetOverload();
            player->SetOverloadOwed(player->GetOverloadOwed() + amount);
        }

        player->game->ProcessTasks();

        player->GetGraveyardZone()->Add(spell);
    }

    player->game->taskQueue.EndEvent();
}
}  // namespace RosettaStone::PlayMode::Generic