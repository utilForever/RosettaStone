/*************************************************************************
> File Name: Combat.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement CombatTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/Combat.h>
#include <Tasks/BasicTasks/ModifyHealth.h>

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
    std::vector<Character*>& attacked = player1.attacked;
    if (std::find(attacked.begin(), attacked.end(), source) != attacked.end())
    {
        return MetaData::COMBAT_ALREADY_ATTACKED;
    }

    attacked.emplace_back(source);

    // Destination Verification
    // dst == 0 : hero
    // 1 < dst <= field.size : minion
    if (dst > player2.field.size())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
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

    return MetaData::COMBAT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks