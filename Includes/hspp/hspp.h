// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HSPP_H
#define HEARTHSTONEPP_HSPP_H

#include <hspp/Accounts/Account.h>
#include <hspp/Accounts/Player.h>
#include <hspp/CardSets/BasicCardsGen.h>
#include <hspp/Cards/Card.h>
#include <hspp/Cards/Cards.h>
#include <hspp/Cards/Character.h>
#include <hspp/Cards/Deck.h>
#include <hspp/Cards/Enchantment.h>
#include <hspp/Cards/Entity.h>
#include <hspp/Cards/Hero.h>
#include <hspp/Cards/HeroPower.h>
#include <hspp/Cards/Minion.h>
#include <hspp/Cards/Spell.h>
#include <hspp/Cards/Weapon.h>
#include <hspp/Commons/Constants.h>
#include <hspp/Commons/EnumMacros.h>
#include <hspp/Commons/Macros.h>
#include <hspp/Commons/Utils.h>
#include <hspp/Enchants/Effect.h>
#include <hspp/Enchants/Effects.h>
#include <hspp/Enchants/Enchant.h>
#include <hspp/Enchants/Power.h>
#include <hspp/Enchants/Powers.h>
#include <hspp/Enums/CardEnums.h>
#include <hspp/Enums/TaskEnums.h>
#include <hspp/Flatbuffers/generated/FlatData_generated.h>
#include <hspp/Loaders/AccountLoader.h>
#include <hspp/Loaders/CardLoader.h>
#include <hspp/Loaders/PowerLoader.h>
#include <hspp/Managers/GameAgent.h>
#include <hspp/Managers/GameInterface.h>
#include <hspp/Managers/SyncBuffer.h>
#include <hspp/Tasks/BasicTasks/BriefTask.h>
#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>
#include <hspp/Tasks/BasicTasks/DestroyTask.h>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>
#include <hspp/Tasks/BasicTasks/DrawTask.h>
#include <hspp/Tasks/BasicTasks/GameEndTask.h>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>
#include <hspp/Tasks/BasicTasks/ModifyHealthTask.h>
#include <hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp/Tasks/BasicTasks/MulliganTask.h>
#include <hspp/Tasks/BasicTasks/PlayCardTask.h>
#include <hspp/Tasks/BasicTasks/PlayMinionTask.h>
#include <hspp/Tasks/BasicTasks/PlaySpellTask.h>
#include <hspp/Tasks/BasicTasks/PlayWeaponTask.h>
#include <hspp/Tasks/BasicTasks/PlayerSettingTask.h>
#include <hspp/Tasks/BasicTasks/ShuffleTask.h>
#include <hspp/Tasks/BasicTasks/SwapPlayerTask.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/PowerTasks/AddEnchantmentTask.h>
#include <hspp/Tasks/PowerTasks/DiscardTask.h>
#include <hspp/Tasks/PowerTasks/FreezeTask.h>
#include <hspp/Tasks/PowerTasks/HealFullTask.h>
#include <hspp/Tasks/PowerTasks/HealTask.h>
#include <hspp/Tasks/PowerTasks/PoisonousTask.h>
#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/TaskMeta.h>
#include <hspp/Tasks/TaskSerializer.h>
#include <hspp/Tasks/TaskWrapper.h>
#include <hspp/Tasks/Tasks.h>
#include <hspp/hspp.h>

#endif  // HEARTHSTONEPP_HSPP_H
