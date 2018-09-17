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
//!
//! \brief GameResult structure.
//!
//! This structure stores the result of Hearthstone game.
//!
struct GameResult
{
    std::string winnerID;
};

//! \brief An enumerator for identifying handle status.
enum class HandleStatus
{
    CONTINUE = 0,  //!< Continues the game.
    STOP = 1,      //!< Ends the game.
};

//!
//! \brief GameInterface class.
//!
//! This class is a interface for Hearthstone game agent.
//! Also, it handles various messages and tasks. All tasks are logged.
//!
class GameInterface
{
 public:

    //! Constructs game interface with given \p agent, \p output and \p input.
    //! \param agent The agent for the game.
    //! \param output The output stream. (std::cout as default)
    //! \param input The input stream. (std::cin as default)
    GameInterface(GameAgent& agent, std::ostream& output = std::cout,
                  std::istream& input = std::cin);

    //! Starts the game. And over and over again, until it's done.
    //! \return The result of the game.
    GameResult StartGame();

 private:
    GameAgent& m_agent;
    TaskMeta m_buffer;
    GameResult m_result;

    std::ostream& m_ostream;
    std::istream& m_istream;

    std::string m_users[2];
    //! Cached game status for processing some requirements.
    std::unique_ptr<BYTE[]> m_status;

    HandleStatus HandleMessage(const TaskMeta& meta);

    std::ostream& LogWriter(std::string&& name);
    std::ostream& LogWriter(const std::string& name);

    template <std::size_t SIZE>
    void ShowMenus(const std::array<std::string, SIZE>& menus);

    using EntityVector =
        flatbuffers::Vector<flatbuffers::Offset<FlatData::Entity>>;
    void ShowCards(const EntityVector& entities);

    // TaskMeta Handler
    void HandleDefault(const TaskMeta& meta);
    void HandleTaskVector(const TaskMeta& meta);
    void HandlePlayerSetting(const TaskMeta& meta);
    void HandleRequire(const TaskMeta& meta);
    void HandleBrief(const TaskMeta& meta);
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
            {TaskID::TASK_VECTOR, &GameInterface::HandleTaskVector},
            {TaskID::PLAYER_SETTING, &GameInterface::HandlePlayerSetting},
            {TaskID::REQUIRE, &GameInterface::HandleRequire},
            {TaskID::BRIEF, &GameInterface::HandleBrief},
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
