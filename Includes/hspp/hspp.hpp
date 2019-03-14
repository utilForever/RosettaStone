// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HSPP_HPP
#define HEARTHSTONEPP_HSPP_HPP

#include <hspp/Accounts/AccountInfo.hpp>
#include <hspp/Accounts/DeckInfo.hpp>
#include <hspp/Actions/Draw.hpp>
#include <hspp/Actions/Generic.hpp>
#include <hspp/Actions/PlayCard.hpp>
#include <hspp/Actions/Targeting.hpp>
#include <hspp/CardSets/CoreCardsGen.hpp>
#include <hspp/Cards/Card.hpp>
#include <hspp/Cards/Cards.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Commons/EnumMacros.hpp>
#include <hspp/Commons/Macros.hpp>
#include <hspp/Commons/Utils.hpp>
#include <hspp/Enchants/Effect.hpp>
#include <hspp/Enchants/Effects.hpp>
#include <hspp/Enchants/Enchant.hpp>
#include <hspp/Enchants/Power.hpp>
#include <hspp/Enchants/Powers.hpp>
#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Games/Game.hpp>
#include <hspp/Games/GameAgent.hpp>
#include <hspp/Games/GameConfig.hpp>
#include <hspp/Games/GameManager.hpp>
#include <hspp/Loaders/AccountLoader.hpp>
#include <hspp/Loaders/CardLoader.hpp>
#include <hspp/Loaders/PowerLoader.hpp>
#include <hspp/Models/Battlefield.hpp>
#include <hspp/Models/Character.hpp>
#include <hspp/Models/Deck.hpp>
#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Graveyard.hpp>
#include <hspp/Models/Hand.hpp>
#include <hspp/Models/Hero.hpp>
#include <hspp/Models/HeroPower.hpp>
#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Models/Spell.hpp>
#include <hspp/Models/Weapon.hpp>
#include <hspp/Policies/BasicPolicy.hpp>
#include <hspp/Policies/IoPolicy.hpp>
#include <hspp/Policies/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/CombatTask.hpp>
#include <hspp/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <hspp/Tasks/PlayerTasks/MulliganTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <hspp/Tasks/SimpleTasks/ControlTask.hpp>
#include <hspp/Tasks/SimpleTasks/DamageTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/DiscardTask.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>
#include <hspp/Tasks/SimpleTasks/FreezeTask.hpp>
#include <hspp/Tasks/SimpleTasks/HealFullTask.hpp>
#include <hspp/Tasks/SimpleTasks/HealTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>
#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>
#include <hspp/Tasks/TaskMeta.hpp>
#include <hspp/Tasks/TaskStatus.hpp>
#include <hspp/Tasks/TaskWrapper.hpp>
#include <hspp/Tasks/Tasks.hpp>
#include <hspp/hspp.hpp>

#endif  // HEARTHSTONEPP_HSPP_HPP
