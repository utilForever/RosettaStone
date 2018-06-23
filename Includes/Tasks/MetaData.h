/*************************************************************************
> File Name: MetaData.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: MetaData for TaskMeta
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_METADATA_H
#define HEARTHSTONEPP_METADATA_H

namespace Hearthstonepp
{
using status_t = unsigned int;
enum class MetaData : status_t
{
    INVALID,

    SWAP,
    SWAP_SUCCESS,

    DRAW,
    DRAW_SUCCESS,
    DRAW_EXHAUST,
    DRAW_OVERDRAW,
    DRAW_EXHAUST_OVERDRAW,

    SHUFFLE,
    SHUFFLE_SUCCESS,

    BRIEF,

    MULLIGAN,
    MULLIGAN_SUCCESS,
    MULLIGAN_INDEX_OUT_OF_RANGE,
    MULLIGAN_DUPLICATED_INDEX,

    MODIFY_MANA,
    MODIFY_MANA_SUCCESS,

    SELECT_CARD_MINION,

    SUMMON,
    SUMMON_SUCCESS,
    SUMMON_CARD_IDX_OUT_OF_RANGE,
    SUMMON_POSITION_OUT_OF_RANGE,
    SUMMON_NOT_ENOUGH_MANA,

    MODIFY_HEALTH,
    MODIFY_HEALTH_SUCCESS,

    COMBAT,
    COMBAT_SUCCESS,
    COMBAT_SRC_IDX_OUT_OF_RANGE,
    COMBAT_DST_IDX_OUT_OF_RANGE,
    COMBAT_ALREADY_ATTACKED,

    GAME_END
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_METADATA_H
