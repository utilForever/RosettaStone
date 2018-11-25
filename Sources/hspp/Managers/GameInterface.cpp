// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Managers/GameInterface.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
GameInterface::GameInterface(GameAgent& agent, std::ostream& output,
                             std::istream& input)
    : m_agent(agent), m_ostream(output), m_istream(input)
{
    // Do nothing
}

GameResult GameInterface::StartGame()
{
    std::thread at = m_agent.Start();

    while (true)
    {
        // Pass task meta from TaskAgent
        m_agent.GetTaskMeta(m_buffer);

        const HandleStatus status = HandleMessage(m_buffer);
        if (status == HandleStatus::STOP)
        {
            break;
        }
    }

    // Join agent thread
    at.join();

    // GameResult is set by GameEndTaskMeta handler
    return m_result;
}

HandleStatus GameInterface::HandleMessage(const TaskMeta& meta)
{
    if (m_handler.find(meta.GetID()) != m_handler.end())
    {
        // Find from handler table and call it
        m_handler[meta.GetID()](*this, meta);
    }
    else
    {
        HandleDefault(meta);
    }

    if (meta.GetID() == +TaskID::GAME_END)
    {
        return HandleStatus::STOP;
    }

    return HandleStatus::CONTINUE;
}

std::ostream& GameInterface::WriteLog(const std::string& name) const
{
    m_ostream << "[*] " << name << " : ";
    return m_ostream;
}

std::ostream& GameInterface::WriteLog(std::string&& name) const
{
    return WriteLog(name);
}

template <std::size_t SIZE>
void GameInterface::ShowMenus(const std::array<std::string, SIZE>& menus)
{
    for (auto& menu : menus)
    {
        m_ostream << menu << '\n';
    }
}

void GameInterface::ShowCards(const EntityVector& entities) const
{
    for (const auto& entity : entities)
    {
        const auto card = entity->card();
        CardType cardType = CardType::_from_integral(card->cardType());
        m_ostream << '[' << card->name()->c_str() << '('
                  << cardType._to_string() << " / " << card->cost() << ")] ";

        if (cardType == +CardType::MINION)
        {
            m_ostream << "(ATK " << card->attack() << "/HP " << card->health()
                      << ")";
        }
        m_ostream << '\n';
    }
}

void GameInterface::HandleDefault(const TaskMeta& meta) const
{
    m_ostream << m_users[meta.GetUserID()] << " TaskID::"
              << TaskID::_from_integral(meta.GetID())._to_string() << ' '
              << static_cast<int>(meta.GetStatus()) << '\n';
}

void GameInterface::HandleTaskVector(const TaskMeta& meta)
{
    const auto metas = TaskMeta::ConvertTo<FlatData::TaskMetaVector>(meta);
    if (metas == nullptr)
    {
        WriteLog("TaskVector")
            << "Exception HandleTaskMeta : Invalid FlatBuffers\n";
        return;
    }

    const auto vector = metas->vector();
    for (const auto& ind : *vector)
    {
        HandleMessage(TaskMeta::ConvertFrom(ind));
    }
}

void GameInterface::HandlePlayerSetting(const TaskMeta& meta)
{
    const auto setting = TaskMeta::ConvertTo<FlatData::PlayerSetting>(meta);
    if (setting != nullptr &&
        meta.GetStatus() == MetaData::PLAYER_SETTING_REQUEST)
    {
        m_users[0] = setting->player1()->str();
        m_users[1] = setting->player2()->str();

        WriteLog("PlayerSetting") << "player1 - " << m_users[0]
                                  << " / player2 - " << m_users[1] << '\n';
    }
}

void GameInterface::HandleRequire(const TaskMeta& meta)
{
    const auto required = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(meta);
    if (required == nullptr)
    {
        WriteLog("Require")
            << "Exception HandleRequire : TaskMeta is nullptr\n";
        return;
    }

    const auto taskID = TaskID::_from_integral(required->required());
    if (m_inputHandler.find(taskID) != m_inputHandler.end())
    {
        // Find and call from input handler table
        m_inputHandler[taskID](*this, meta);
    }
}

void GameInterface::HandleBriefing(const TaskMeta& meta)
{
    if (meta.GetStatus() == MetaData::BRIEF_EXPIRED)
    {
        return;
    }

    std::ostream& stream = WriteLog(m_users[meta.GetUserID()]);

    const auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    if (status == nullptr)
    {
        stream << "Exception HandleBriefing : TaskMeta is nullptr\n";
        return;
    }

    const size_t bufferSize = meta.GetBufferSize();
    m_status = std::make_unique<BYTE[]>(bufferSize);

    const auto& buffer = meta.GetBuffer();
    std::copy(buffer.get(), buffer.get() + bufferSize, m_status.get());

    stream << "Game Briefing\n"
           << m_users[status->opponentPlayer()] << " - Hero "
           << status->opponentHero()->card()->name()->c_str() << ", Health "
           << status->opponentHero()->card()->health() << ", Mana "
           << static_cast<int>(status->opponentMana()) << ", Hand "
           << static_cast<int>(status->numOpponentHand()) << ", Deck "
           << static_cast<int>(status->numOpponentDeck()) << '\n';

    stream << m_users[status->opponentPlayer()] << " Field\n";
    ShowCards(*status->opponentField());

    stream << m_users[status->currentPlayer()] << " - Hero "
           << status->currentHero()->card()->name()->c_str() << ", Health "
           << status->currentHero()->card()->health() << ", Mana "
           << static_cast<int>(status->currentMana()) << ", Hand "
           << static_cast<int>(status->currentHand()->size()) << ", Deck "
           << static_cast<int>(status->numCurrentDeck()) << '\n';

    stream << m_users[status->currentPlayer()] << " Field\n";
    ShowCards(*status->currentField());

    stream << m_users[status->currentPlayer()] << " Hand\n";
    ShowCards(*status->currentHand());
}

void GameInterface::HandleGameOver(const TaskMeta& meta)
{
    const auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    if (status == nullptr)
    {
        WriteLog("GameEnd")
            << "Exception HandleGameOver : TaskMeta is nullptr\n";
        return;
    }

    const auto player1Health = status->currentHero()->card()->health();
    const auto player2Health = status->opponentHero()->card()->health();
    if (player1Health != 0 && player2Health != 0)
    {
        WriteLog("GameEnd")
            << "Exception HandleGame End : No one end the game - "
            << static_cast<int>(player1Health) << " / "
            << static_cast<int>(player2Health) << '\n';
        return;
    }

    if (player1Health == 0 && player2Health == 0)
    {
        m_result.winnerID = "DRAW";
    }
    else if (player1Health == 0 && player2Health != 0)
    {
        m_result.winnerID = m_users[status->opponentPlayer()];
    }
    else if (player1Health != 0 && player2Health == 0)
    {
        m_result.winnerID = m_users[status->currentPlayer()];
    }
    WriteLog(m_result.winnerID) << "Win\n";
}

void GameInterface::HandleOverDraw(const TaskMeta& meta) const
{
    std::ostream& stream = WriteLog(m_users[meta.GetUserID()]);

    const auto& buffer = meta.GetBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandleOverDraw : TaskMeta is nullptr\n";
        return;
    }

    const auto& entities =
        flatbuffers::GetRoot<FlatData::EntityVector>(buffer.get());
    if (entities == nullptr)
    {
        stream << "Exception HandleOverDraw : EntityVector is nullptr\n";
        return;
    }

    stream << "Over Draw : " << entities->vector()->size() << '\n';
    ShowCards(*entities->vector());
}

void GameInterface::HandleMulliganInput(const TaskMeta& meta) const
{
    WriteLog(m_users[meta.GetUserID()]) << "Input Mulligan\n";

    size_t numMulligan;
    while (true)
    {
        m_ostream << "[*] How many cards to mulligan ? (0 ~ 3) ";
        m_istream >> numMulligan;

        if (numMulligan <= NUM_DRAW_CARDS_AT_START_FIRST)
        {
            break;
        }
    }

    BYTE mulligan[NUM_DRAW_CARDS_AT_START_FIRST] = {
        0,
    };
    for (size_t i = 0; i < numMulligan; ++i)
    {
        while (true)
        {
            size_t index = 0;
            m_ostream << "[*] Input card index " << i + 1 << " (0 ~ 2) : ";
            m_istream >> index;

            if (index <= NUM_DRAW_CARDS_AT_START_FIRST - 1)
            {
                mulligan[i] = static_cast<BYTE>(index);
                break;
            }
        }
    }

    TaskMeta result = Serializer::CreateResponseMulligan(mulligan, numMulligan);
    m_agent.WriteSyncBuffer(std::move(result));
}

void GameInterface::HandleMenuInput(const TaskMeta& meta)
{
    WriteLog(m_users[meta.GetUserID()]) << "Main Menu\n";
    ShowMenus(m_mainMenuStr);

    size_t input;
    while (true)
    {
        m_ostream << "[*] Input menu : ";
        m_istream >> input;

        // Input range verification
        if (input > 0 && input <= GAME_MAIN_MENU_SIZE)
        {
            input -= 1;
            break;
        }
    }

    TaskMeta result(
        TaskMetaTrait(TaskID::SELECT_CARD, static_cast<MetaData>(input)));
    m_agent.WriteSyncBuffer(std::move(result));
}

void GameInterface::HandleCardInput(const TaskMeta& meta) const
{
    WriteLog(m_users[meta.GetUserID()]) << "Select Card\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception InputSelectCard : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));

        return;
    }

    const auto brief =
        flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    const auto currentHand = brief->currentHand();
    const int numCurrentHand = currentHand->size();
    const size_t currentMana = brief->currentMana();

    int in;
    while (true)
    {
        m_ostream << "Select card index (0 ~ " << numCurrentHand - 1 << ") : ";

        m_istream >> in;
        // Card hand index range verification
        if (in >= 0 && in < numCurrentHand)
        {
            if (currentHand->Get(in)->card()->cost() > currentMana)
            {
                m_ostream << "Not enough mana\n";
            }
            else
            {
                break;
            }
        }
    }

    TaskMeta serialized = Serializer::CreateResponsePlayCard(in);
    m_agent.WriteSyncBuffer(std::move(serialized));
}

void GameInterface::HandleTargetInput(const TaskMeta& meta) const
{
    WriteLog(m_users[meta.GetUserID()]) << "Targeting\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception InputTargeting : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));
        return;
    }

    const auto brief =
        flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    const auto currentField = brief->currentField();
    const int numCurrentField = currentField->size();

    m_ostream << "Player field :\n";
    ShowCards(*currentField);

    const auto opponentField = brief->opponentField();
    const int numOpponentField = opponentField->size();

    m_ostream << "Opponent field :\n";
    ShowCards(*brief->opponentField());

    int src;
    while (true)
    {
        m_ostream << "Select source minion (0 for hero, 1 ~ " << numCurrentField
                  << " for minion) : ";

        m_istream >> src;
        // Source Field range verification
        if (src >= 0 && src <= numCurrentField)
        {
            break;
        }
    }

    int dst;
    while (true)
    {
        m_ostream << "Select destination (0 for hero, 1 ~ " << numOpponentField
                  << " for minion) : ";

        m_istream >> dst;
        // Destination Field range verification
        if (dst >= 0 && dst <= numOpponentField)
        {
            break;
        }
    }

    TaskMeta targeting = Serializer::CreateResponseTarget(src, dst);
    m_agent.WriteSyncBuffer(std::move(targeting));
}

void GameInterface::HandlePositionInput(const TaskMeta& meta) const
{
    WriteLog(m_users[meta.GetUserID()]) << "Input Position\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception HandlePositionInput : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));
        return;
    }

    const auto brief =
        flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    const auto currentField = brief->currentField();
    const int numCurrentField = currentField->size();

    int pos;
    while (true)
    {
        m_ostream << "Select Position (0 ~ " << numCurrentField << ") : ";

        m_istream >> pos;
        // Field position range verification
        if (pos >= 0 && pos <= numCurrentField)
        {
            break;
        }
    }

    TaskMeta response = Serializer::CreateResponsePlayMinion(pos);
    m_agent.WriteSyncBuffer(std::move(response));
}
}  // namespace Hearthstonepp
