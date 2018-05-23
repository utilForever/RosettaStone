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

#include <Tasks/TaskMeta.h>

namespace Hearthstonepp
{
    namespace MetaData
    {
        constexpr TaskMeta::status_t INVALID = 0;

        constexpr TaskMeta::status_t SWAP = 1;
        constexpr TaskMeta::status_t SWAP_SUCCESS = 2;

        constexpr TaskMeta::status_t DRAW = 3;
        constexpr TaskMeta::status_t DRAW_SUCCESS = 4;
        constexpr TaskMeta::status_t DRAW_EXHAUST = 5;
        constexpr TaskMeta::status_t DRAW_OVERDRAW = 6;
        constexpr TaskMeta::status_t DRAW_EXHAUST_OVERDRAW = 7;

        constexpr TaskMeta::status_t SHUFFLE = 8;
        constexpr TaskMeta::status_t SHUFFLE_SUCCESS = 9;

        constexpr TaskMeta::status_t BRIEF = 10;

        constexpr TaskMeta::status_t MULLIGAN = 11;
        constexpr TaskMeta::status_t MULLIGAN_SUCCESS = 12;
        constexpr TaskMeta::status_t MULLIGAN_INDEX_OUT_OF_RANGE = 13;
        constexpr TaskMeta::status_t MULLIGAN_DUPLICATED_INDEX = 14;

        constexpr TaskMeta::status_t MODIFY_MANA = 15;
        constexpr TaskMeta::status_t MODIFY_MANA_SUCCESS = 16;

        constexpr TaskMeta::status_t SELECT_CARD_MINION = 17;

        constexpr TaskMeta::status_t SUMMON = 18;
        constexpr TaskMeta::status_t SUMMON_SUCCESS = 19;
        constexpr TaskMeta::status_t SUMMON_CARD_IDX_OUT_OF_RANGE = 20;
        constexpr TaskMeta::status_t SUMMON_POSITION_OUT_OF_RANGE = 21;
        constexpr TaskMeta::status_t SUMMON_NOT_ENOUGH_MANA = 22;

        constexpr TaskMeta::status_t MODIFY_HEALTH = 23;
        constexpr TaskMeta::status_t MODIFY_HEALTH_SUCCESS = 24;

        constexpr TaskMeta::status_t COMBAT = 25;
        constexpr TaskMeta::status_t COMBAT_SUCCESS = 26;
        constexpr TaskMeta::status_t COMBAT_SRC_IDX_OUT_OF_RANGE = 27;
        constexpr TaskMeta::status_t COMBAT_DST_IDX_OUT_OF_RANGE = 28;
        constexpr TaskMeta::status_t COMBAT_ALREADY_ATTACKED = 29;

        constexpr TaskMeta::status_t GAME_END = std::numeric_limits<TaskMeta::status_t>::max();

    }
}

#endif //HEARTHSTONEPP_METADATA_H
