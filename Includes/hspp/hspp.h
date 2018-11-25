// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HSPP_H
#define HEARTHSTONEPP_HSPP_H

#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Accounts/Account.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Accounts/Player.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Actions/Generic.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/CardSets/BasicCardsGen.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Card.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Cards.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Character.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Deck.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Entity.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Hero.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/HeroPower.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Minion.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Spell.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Cards/Weapon.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Commons/Constants.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Commons/EnumMacros.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Commons/Macros.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Commons/Utils.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enchants/Effect.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enchants/Effects.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enchants/Enchant.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enchants/Power.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enchants/Powers.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enums/CardEnums.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Enums/TaskEnums.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Flatbuffers/generated/FlatData_generated.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Loaders/AccountLoader.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Loaders/CardLoader.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Loaders/PowerLoader.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Managers/GameAgent.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Managers/GameInterface.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Managers/SyncBuffer.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/BriefTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/DamageTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/DestroyMinionTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/DestroyTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/DestroyWeaponTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/DrawTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/GameEndTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/InitAttackCountTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/MulliganTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/PlayCardTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/PlayMinionTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/PlaySpellTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/PlayWeaponTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/PlayerSettingTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/BasicTasks/ShuffleTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/MetaData.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/AddEnchantmentTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/DiscardTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/FreezeTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/HealFullTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/HealTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/PowerTasks/PoisonousTask.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/Requirement.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/TaskAgent.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/TaskMeta.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/TaskSerializer.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/TaskWrapper.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/Tasks/Tasks.h>
#include <hspp//home/jwkim/development/HearthStone/Hearthstonepp/Scripts/../Includes/hspp/hspp.h>

#endif  // HEARTHSTONEPP_HSPP_H
