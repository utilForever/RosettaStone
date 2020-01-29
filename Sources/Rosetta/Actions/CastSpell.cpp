// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/CastSpell.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

namespace RosettaStone::Generic
{
void CastSpell(Player* player, Spell* spell, Character* target, int chooseOne)
{
    player->game->taskQueue.StartEvent();

    if (spell->IsSecret())
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

        if (spell->IsTwinspell())
        {
            const auto twinspell = Entity::GetFromCard(
                player, Cards::FindCardByID(spell->card->id + "ts"));
            player->GetHandZone()->Add(twinspell);
        }

        player->GetGraveyardZone()->Add(spell);
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
}
}  // namespace RosettaStone::Generic