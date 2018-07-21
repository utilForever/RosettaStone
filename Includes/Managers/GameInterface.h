/*************************************************************************
> File Name: GameInterface.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_INTERFACE_H
#define HEARTHSTONEPP_INTERFACE_H

#include <Enums/CardEnums.h>
#include <InGame/GameAgent.h>
#include <Tasks/TaskMeta.h>

#include <Flatbuffers/generated/MetaData_generated.h>

#include <array>
#include <functional>
#include <iostream>
#include <map>

namespace Hearthstonepp
{
struct GameResult
{
    std::string winnerID;
};

class GameInterface
{
 public:
    GameInterface(GameAgent& agent, std::ostream& output = std::cout,
                  std::istream& input = std::cin);

    GameResult StartGame();

 private:
    const size_t HANDLE_CONTINUE = 0;
    const size_t HANDLE_STOP = 1;

    GameAgent& m_agent;
    // Temporal TaskMeta got from GameAgent
    TaskMeta m_buffer;

    GameResult m_result;

    // Variable for storing serialized brief cache
    std::unique_ptr<BYTE[]> m_briefRawCache;
    // Deserialized brief cache
    const FlatData::BriefTaskMeta* m_briefCache;

    std::ostream& m_ostream;
    std::istream& m_istream;

    // user id
    std::string m_users[2];

    size_t HandleMessage(const TaskMeta& meta);
    std::ostream& LogWriter(const std::string& name);

    template <std::size_t SIZE>
    void ShowMenus(const std::array<std::string, SIZE>& menus);

    using EntityVector =
        flatbuffers::Vector<flatbuffers::Offset<FlatData::Entity>>;
    void ShowCards(const EntityVector& entities);

    // TaskMeta Handler
    void HandleInvalid(const TaskMeta& meta);
    void HandlePlayerSetting(const TaskMeta& meta);
    void HandleSwap(const TaskMeta& meta);
    void HandleShuffle(const TaskMeta& meta);
    void HandleDraw(const TaskMeta& meta);
    void HandleMulligan(const TaskMeta& meta);
    void HandleManaModification(const TaskMeta& meta);
    void HandleHealthModification(const TaskMeta& meta);
    void HandleSummonMinion(const TaskMeta& meta);
    void HandleCombat(const TaskMeta& meta);
    void HandleRequire(const TaskMeta& meta);
    void HandleBrief(const TaskMeta& meta);
    void HandleTaskTuple(const TaskMeta& meta);
    void HandleGameEnd(const TaskMeta& meta);

    // Input Task Handler
    void InputMulligan(const TaskMeta& meta);
    void InputSelectMenu(const TaskMeta& meta);
    void InputSelectCard(const TaskMeta& meta);
    void InputTargeting(const TaskMeta& meta);

    // Handler table
    std::map<TaskID, std::function<void(GameInterface&, const TaskMeta&)>>
        m_handler = {
            {TaskID::INVALID, &GameInterface::HandleInvalid},
            {TaskID::USER_SETTING, &GameInterface::HandlePlayerSetting},
            {TaskID::SWAP, &GameInterface::HandleSwap},
            {TaskID::SHUFFLE, &GameInterface::HandleShuffle},
            {TaskID::DRAW, &GameInterface::HandleDraw},
            {TaskID::MULLIGAN, &GameInterface::HandleMulligan},
            {TaskID::MODIFY_MANA, &GameInterface::HandleManaModification},
            {TaskID::SUMMON_MINION, &GameInterface::HandleSummonMinion},
            {TaskID::COMBAT, &GameInterface::HandleCombat},
            {TaskID::MODIFY_HEALTH, &GameInterface::HandleHealthModification},
            {TaskID::REQUIRE, &GameInterface::HandleRequire},
            {TaskID::BRIEF, &GameInterface::HandleBrief},
            {TaskID::TASK_TUPLE, &GameInterface::HandleTaskTuple},
            {TaskID::GAME_END, &GameInterface::HandleGameEnd},
    };

    // Input Handler Table
    std::map<TaskID, std::function<void(GameInterface&, const TaskMeta&)>>
        m_inputHandler = {
            {TaskID::MULLIGAN, &GameInterface::InputMulligan},
            {TaskID::SELECT_MENU, &GameInterface::InputSelectMenu},
            {TaskID::SELECT_CARD, &GameInterface::InputSelectCard},
            {TaskID::SELECT_TARGET, &GameInterface::InputTargeting},
    };

    std::array<std::string, GAME_MAIN_MENU_SIZE> m_mainMenuStr = {
        "1. Use Card", "2. Combat", "3. Stop"};
};
}  // namespace Hearthstonepp

#endif
