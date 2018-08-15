/*************************************************************************
> File Name: Combat.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement CombatTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/CombatTask.h>
#include <Tasks/BasicTasks/ModifyHealthTask.h>
#include <Tasks/PowerTasks/PoisonousTask.h>
#include <Tasks/PowerTasks/FreezeTask.h>

namespace Hearthstonepp::BasicTasks
{
CombatTask::CombatTask(TaskAgent& agent)
    : m_requirement(TaskID::SELECT_TARGET, agent)
{
    // Do Nothing
}

TaskID CombatTask::GetTaskID() const
{
    return TaskID::COMBAT;
}

MetaData CombatTask::Impl(Player& player1, Player& player2)
{
    TaskMeta serialized;
    // Get Targeting Response from GameInterface
    m_requirement.Interact(player1.id, serialized);

    using RequireTaskMeta = FlatData::ResponseTarget;
    const auto& buffer = serialized.GetConstBuffer();
    auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::COMBAT_FLATBUFFER_NULLPTR;
    }

    BYTE src = req->src();
    BYTE dst = req->dst();

    source = (src > 0) ? dynamic_cast<Character*>(player1.field[src - 1])
                       : dynamic_cast<Character*>(player1.hero);
    target = (dst > 0) ? dynamic_cast<Character*>(player2.field[dst - 1])
                       : dynamic_cast<Character*>(player2.hero);

    // Source Minion Index Verification
    if (src > player1.field.size())
    {
        return MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Source Minion Verification for Attacked Vector
    if (source->attackableCount == 0)
    {
        return MetaData::COMBAT_ALREADY_ATTACKED;
    }

    source->attackableCount--;

    // Destination Verification
    // dst == 0 : hero
    // 1 < dst <= field.size : minion
    if (dst > player2.field.size())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    // Taunt Verification
    if (target->gameTags[+GameTag::TAUNT] == 0)
    for (auto& item: player2.field)
    {
        if (item->gameTags[+GameTag::TAUNT] == 1)
        {
            return MetaData::COMBAT_FIELD_HAVE_TAUNT;
        }
    }

    // Stealth Verification
    if (target->gameTags[+GameTag::STEALTH] == 1)
    {
        return MetaData::COMBAT_TARGET_STEALTH;
    }

    BYTE sourceAttack = static_cast<BYTE>(source->attack);
    BYTE targetAttack = (dst > 0) ? static_cast<BYTE>(target->attack) : 0;

    // Attack : Dst -> Src
    MetaData hurtedSrc =
        ModifyHealthTask(source, targetAttack).Run(player1, player2);
    if (hurtedSrc != MetaData::MODIFY_HEALTH_SUCCESS)
    {
        return hurtedSrc;
    }

    // Attack : Src -> Dst
    MetaData hurtedDst =
        ModifyHealthTask(target, sourceAttack).Run(player1, player2);
    if (hurtedDst != MetaData::MODIFY_HEALTH_SUCCESS)
    {
        return hurtedDst;
    }

    // Divine Shield : Dst
    if (target->gameTags[+GameTag::DIVINE_SHIELD] == 1)
    {
        target->gameTags[+GameTag::DIVINE_SHIELD] = 0;
    }
    else
    {
        // Poisonous : Src -> Dst
        if (source->gameTags[+GameTag::POISONOUS] == 1)
        {
            PowerTask::PoisonousTask(source, target).Run(player1, player2);
        }
    }

    // Divine Shield : Src
    if (source->gameTags[+GameTag::DIVINE_SHIELD] == 1)
    {
        source->gameTags[+GameTag::DIVINE_SHIELD] = 0;
    }
    else
    {
        // Poisonous : Dst -> Src
        if (target->gameTags[+GameTag::POISONOUS] == 1)
        {
            PowerTask::PoisonousTask(target, source).Run(player1, player2);
        }
    }

    // Source Health Check
    if (source->health == 0) 
    {
        auto& field = player1.field;
        auto ptr = std::find(field.begin(), field.end(), source);
        if (ptr != field.end())
        {
            *ptr = nullptr;
            field.erase(ptr);
        }
    }

    // Target Health Check
    if (target->health == 0)
    {
        auto& field = player2.field;
        auto ptr = std::find(field.begin(), field.end(), target);
        if (ptr != field.end())
        {
            *ptr = nullptr;
            field.erase(ptr);
        }        
    }

    return MetaData::COMBAT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks