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
    MULLIGAN_FLATBUFFER_NULLPTR,
    MULLIGAN_INDEX_OUT_OF_RANGE,
    MULLIGAN_DUPLICATED_INDEX,

    MODIFY_MANA,
    MODIFY_MANA_SUCCESS,

    SELECT_CARD,
    SELECT_POSITION,
    SELECT_TARGET,

    PLAY_CARD,
    PLAY_CARD_SUCCESS,
    PLAY_CARD_FLATBUFFER_NULLPTR,
    PLAY_CARD_IDX_OUT_OF_RANGE,
    PLAY_CARD_NOT_ENOUGH_MANA,
    PLAY_CARD_INVALID_CARD_TYPE,

    PLAY_MINION,
    PLAY_MINION_SUCCESS,
    PLAY_MINION_FLATBUFFER_NULLPTR,
    PLAY_MINION_POSITION_OUT_OF_RANGE,
    PLAY_MINION_MODIFY_MANA_FAIL,

    PLAY_WEAPON,
    PLAY_WEAPON_SUCCESS,

    MODIFY_HEALTH,
    MODIFY_HEALTH_SUCCESS,

    COMBAT,
    COMBAT_SUCCESS,
    COMBAT_FLATBUFFER_NULLPTR,
    COMBAT_SRC_IDX_OUT_OF_RANGE,
    COMBAT_DST_IDX_OUT_OF_RANGE,
    COMBAT_ALREADY_ATTACKED,

    GAME_END
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_METADATA_H
