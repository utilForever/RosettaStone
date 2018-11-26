// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HSPP_HPP
#define HEARTHSTONEPP_HSPP_HPP

#include <hspp/Accounts/Account.hpp>
#include <hspp/Accounts/Player.hpp>
#include <hspp/Actions/Generic.hpp>
#include <hspp/CardSets/BasicCardsGen.hpp>
#include <hspp/Cards/Card.hpp>
#include <hspp/Cards/Cards.hpp>
#include <hspp/Cards/Character.hpp>
#include <hspp/Cards/Deck.hpp>
#include <hspp/Cards/Entity.hpp>
#include <hspp/Cards/Hero.hpp>
#include <hspp/Cards/HeroPower.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Spell.hpp>
#include <hspp/Cards/Weapon.hpp>
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
#include <hspp/Flatbuffers/generated/FlatData_generated.hpp>
#include <hspp/Loaders/AccountLoader.hpp>
#include <hspp/Loaders/CardLoader.hpp>
#include <hspp/Loaders/PowerLoader.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Managers/GameInterface.hpp>
#include <hspp/Managers/SyncBuffer.hpp>
#include <hspp/Tasks/BasicTasks/BriefTask.hpp>
#include <hspp/Tasks/BasicTasks/CombatTask.hpp>
#include <hspp/Tasks/BasicTasks/DamageTask.hpp>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.hpp>
#include <hspp/Tasks/BasicTasks/DestroyTask.hpp>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.hpp>
#include <hspp/Tasks/BasicTasks/DrawTask.hpp>
#include <hspp/Tasks/BasicTasks/GameEndTask.hpp>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.hpp>
#include <hspp/Tasks/BasicTasks/ModifyManaTask.hpp>
#include <hspp/Tasks/BasicTasks/MulliganTask.hpp>
#include <hspp/Tasks/BasicTasks/PlayCardTask.hpp>
#include <hspp/Tasks/BasicTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/BasicTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/BasicTasks/PlayWeaponTask.hpp>
#include <hspp/Tasks/BasicTasks/PlayerSettingTask.hpp>
#include <hspp/Tasks/BasicTasks/ShuffleTask.hpp>
#include <hspp/Tasks/MetaData.hpp>
#include <hspp/Tasks/PowerTasks/AddEnchantmentTask.hpp>
#include <hspp/Tasks/PowerTasks/DiscardTask.hpp>
#include <hspp/Tasks/PowerTasks/FreezeTask.hpp>
#include <hspp/Tasks/PowerTasks/HealFullTask.hpp>
#include <hspp/Tasks/PowerTasks/HealTask.hpp>
#include <hspp/Tasks/PowerTasks/PoisonousTask.hpp>
#include <hspp/Tasks/Requirement.hpp>
#include <hspp/Tasks/TaskAgent.hpp>
#include <hspp/Tasks/TaskMeta.hpp>
#include <hspp/Tasks/TaskSerializer.hpp>
#include <hspp/Tasks/TaskWrapper.hpp>
#include <hspp/Tasks/Tasks.hpp>
#include <hspp/hspp.hpp>

#endif  // HEARTHSTONEPP_HSPP_HPP
