// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSSETASTONE_ROSETTA_HPP
#define ROSSETASTONE_ROSETTA_HPP

#include <Rosetta/Accounts/AccountInfo.hpp>
#include <Rosetta/Accounts/DeckInfo.hpp>
#include <Rosetta/Actions/Attack.hpp>
#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/CardSets/CoreCardsGen.hpp>
#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Commons/EnumMacros.hpp>
#include <Rosetta/Commons/Macros.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Effect.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchant.hpp>
#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Enchants/Powers.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameAgent.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Loaders/AccountLoader.hpp>
#include <Rosetta/Loaders/CardLoader.hpp>
#include <Rosetta/Loaders/PowerLoader.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/Choice.hpp>
#include <Rosetta/Models/Deck.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Graveyard.hpp>
#include <Rosetta/Models/Hand.hpp>
#include <Rosetta/Models/Hero.hpp>
#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Models/Weapon.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <Rosetta/Policies/IoPolicy.hpp>
#include <Rosetta/Policies/Policy.hpp>
#include <Rosetta/RosettaStone.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealFullTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ModifyManaTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Tasks/TaskMeta.hpp>
#include <Rosetta/Tasks/TaskStatus.hpp>
#include <Rosetta/Tasks/TaskWrapper.hpp>
#include <Rosetta/Tasks/Tasks.hpp>

#endif  // ROSSETASTONE_ROSETTA_HPP
