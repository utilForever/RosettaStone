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

#include <Enums/TaskEnums.h>
#include <Managers/GameAgent.h>
#include <Tasks/TaskMeta.h>

#include <Flatbuffers/generated/FlatData_generated.h>

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

enum class HandleStatus
{
    CONTINUE = 0,
    STOP = 1,
};

class GameInterface
{
 public:
    GameInterface(GameAgent& agent, std::ostream& output = std::cout,
                  std::istream& input = std::cin);

    GameResult StartGame();

 private:
    GameAgent& m_agent;
    // Temporal TaskMeta got from GameAgent
    TaskMeta m_buffer;

    GameResult m_result;

    std::ostream& m_ostream;
    std::istream& m_istream;

    // user id
    std::string m_users[2];

    std::unique_ptr<BYTE[]> m_brief;

    HandleStatus HandleMessage(const TaskMeta& meta);
    std::ostream& LogWriter(const std::string& name);

    const FlatData::GameStatus* ConvertToGameStatus(const TaskMeta& meta) const;

    template <std::size_t SIZE>
    void ShowMenus(const std::array<std::string, SIZE>& menus);

    using EntityVector =
        flatbuffers::Vector<flatbuffers::Offset<FlatData::Entity>>;
    void ShowCards(const EntityVector& entities);

    // TaskMeta Handler
    void HandleInvalid(const TaskMeta& meta);
    void HandleTaskVector(const TaskMeta& meta);
    void HandleRequire(const TaskMeta& meta);
    void HandlePlayerSetting(const TaskMeta& meta);
    void HandleSwap(const TaskMeta& meta);
    void HandleShuffle(const TaskMeta& meta);
    void HandleDraw(const TaskMeta& meta);
    void HandleModifyMana(const TaskMeta& meta);
    void HandleModifyHealth(const TaskMeta& meta);
    void HandleBrief(const TaskMeta& meta);
    void HandleMulligan(const TaskMeta& meta);
    void HandleCombat(const TaskMeta& meta);
    void HandlePlayCard(const TaskMeta& meta);
    void HandlePlayMinion(const TaskMeta& meta);
    void HandlePlayWeapon(const TaskMeta& meta);
    void HandleGameEnd(const TaskMeta& meta);

    void HandleOverDraw(const TaskMeta& meta);

    // Input Task Handler
    void InputMulligan(const TaskMeta& meta);
    void InputMenu(const TaskMeta& meta);
    void InputCard(const TaskMeta& meta);
    void InputTarget(const TaskMeta& meta);
    void InputPosition(const TaskMeta& meta);

    // Handler table
    std::map<TaskID, std::function<void(GameInterface&, const TaskMeta&)>>
        m_handler = {
            {TaskID::INVALID, &GameInterface::HandleInvalid},
            {TaskID::TASK_VECTOR, &GameInterface::HandleTaskVector},
            {TaskID::REQUIRE, &GameInterface::HandleRequire},
            {TaskID::PLAYER_SETTING, &GameInterface::HandlePlayerSetting},
            {TaskID::SWAP, &GameInterface::HandleSwap},
            {TaskID::SHUFFLE, &GameInterface::HandleShuffle},
            {TaskID::DRAW, &GameInterface::HandleDraw},
            {TaskID::MODIFY_MANA, &GameInterface::HandleModifyMana},
            {TaskID::MODIFY_HEALTH, &GameInterface::HandleModifyHealth},
            {TaskID::BRIEF, &GameInterface::HandleBrief},
            {TaskID::MULLIGAN, &GameInterface::HandleMulligan},
            {TaskID::COMBAT, &GameInterface::HandleCombat},
            {TaskID::PLAY_CARD, &GameInterface::HandlePlayCard},
            {TaskID::PLAY_MINION, &GameInterface::HandlePlayMinion},
            {TaskID::PLAY_WEAPON, &GameInterface::HandlePlayWeapon},
            {TaskID::GAME_END, &GameInterface::HandleGameEnd},
            {TaskID::OVER_DRAW, &GameInterface::HandleOverDraw},
    };

    // Input Handler Table
    std::map<TaskID, std::function<void(GameInterface&, const TaskMeta&)>>
        m_inputHandler = {
            {TaskID::MULLIGAN, &GameInterface::InputMulligan},
            {TaskID::SELECT_MENU, &GameInterface::InputMenu},
            {TaskID::SELECT_CARD, &GameInterface::InputCard},
            {TaskID::SELECT_TARGET, &GameInterface::InputTarget},
            {TaskID::SELECT_POSITION, &GameInterface::InputPosition},
    };

    std::array<std::string, GAME_MAIN_MENU_SIZE> m_mainMenuStr = {
        "1. Use Card", "2. Combat", "3. Stop"};
};
}  // namespace Hearthstonepp

#endif
