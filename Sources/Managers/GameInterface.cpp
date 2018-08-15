/*************************************************************************
> File Name: GameInterface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Managers/GameInterface.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
GameInterface::GameInterface(GameAgent& agent, std::ostream& output,
                             std::istream& input)
    : m_agent(agent), m_ostream(output), m_istream(input)
{
    // Do Nothing
}

GameResult GameInterface::StartGame()
{
    std::thread at = m_agent.StartAgent();

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

    // join agent thread
    at.join();

    // GameResult is set by GameEndTaskMeta Handler
    return m_result;
}

HandleStatus GameInterface::HandleMessage(const TaskMeta& serialized)
{
    if (m_handler.find(serialized.id) != m_handler.end())
    {
        // find from handler table and call it
        m_handler[serialized.id](*this, serialized);
    }
    else
    {
        HandleDefault(serialized);
    }

    if (serialized.id == +TaskID::GAME_END)
    {
        return HandleStatus::STOP;
    }

    return HandleStatus::CONTINUE;
}

std::ostream& GameInterface::LogWriter(const std::string& name)
{
    m_ostream << "[*] " << name << " : ";
    return m_ostream;
}

std::ostream& GameInterface::LogWriter(std::string&& name)
{
    return LogWriter(name);
}

template <std::size_t SIZE>
void GameInterface::ShowMenus(const std::array<std::string, SIZE>& menus)
{
    for (auto& menu : menus)
    {
        m_ostream << menu << '\n';
    }
}

void GameInterface::ShowCards(const EntityVector& entities)
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

void GameInterface::HandleDefault(const TaskMeta& meta)
{
    m_ostream << m_users[meta.userID]
              << " TaskID::" << TaskID::_from_integral(meta.id)._to_string()
              << '\n';
}

void GameInterface::HandleTaskVector(const TaskMeta& meta)
{
    auto metas = TaskMeta::ConvertTo<FlatData::TaskMetaVector>(meta);
    if (metas == nullptr)
    {
        LogWriter("TaskVector")
            << "Exception HandleTaskMeta : Invalid FlatBuffers\n";
        return;
    }

    auto vector = metas->vector();
    for (const auto& ind : *vector)
    {
        HandleMessage(TaskMeta::ConvertFrom(ind));
    }
}

void GameInterface::HandlePlayerSetting(const TaskMeta& meta)
{
    auto setting = TaskMeta::ConvertTo<FlatData::PlayerSetting>(meta);
    if (setting != nullptr && meta.status == MetaData::PLAYER_SETTING_REQUEST)
    {
        m_users[0] = setting->player1()->str();
        m_users[1] = setting->player2()->str();

        LogWriter("PlayerSetting") << "player1 - " << m_users[0]
                                   << " / player2 - " << m_users[1] << '\n';
    }
}

void GameInterface::HandleRequire(const TaskMeta& meta)
{
    using RequireTaskMeta = FlatData::RequireTaskMeta;
    auto required = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(meta);
    if (required == nullptr)
    {
        LogWriter("Require")
            << "Exception HandleRequire : TaskMeta is nullptr\n";
        return;
    }

    auto taskid = TaskID::_from_integral(required->required());
    if (m_inputHandler.find(taskid) != m_inputHandler.end())
    {
        // Find and call from Input Handler Table
        m_inputHandler[taskid](*this, meta);
    }
}

void GameInterface::HandleBrief(const TaskMeta& meta)
{
    if (meta.status == MetaData::BRIEF_EXPIRED)
    {
        return;
    }

    std::ostream& stream = LogWriter(m_users[meta.userID]);
    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    if (status == nullptr)
    {
        stream << "Exception HandleBrief : TaskMeta is nullptr\n";
        return;
    }
    
    size_t bufferSize = meta.GetBufferSize();
    m_status = std::make_unique<BYTE[]>(bufferSize);

    const auto& buffer = meta.GetConstBuffer();
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

void GameInterface::HandleGameEnd(const TaskMeta& meta)
{
    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    if (status == nullptr)
    {
        LogWriter("GameEnd")
            << "Exception HandleGameEnd : TaskMeta is nullptr\n";
        return;
    }

    auto hpPlayer1 = status->currentHero()->card()->health();
    auto hpPlayer2 = status->opponentHero()->card()->health();
    if (hpPlayer1 != 0 && hpPlayer2 != 0)
    {
        LogWriter("GameEnd")
            << "Exception HandleGame End : No one end the game - "
            << static_cast<int>(hpPlayer1) << " / "
            << static_cast<int>(hpPlayer2) << '\n';
        return;
    }

    if (hpPlayer1 == 0 && hpPlayer2 == 0)
    {
        m_result.winnerID = "DRAW";
    }
    else if (hpPlayer1 == 0 && hpPlayer2 != 0)
    {
        m_result.winnerID = m_users[status->opponentPlayer()];
    }
    else if (hpPlayer1 != 0 && hpPlayer2 == 0)
    {
        m_result.winnerID = m_users[status->currentPlayer()];
    }
    LogWriter(m_result.winnerID) << "Win\n";
}

void GameInterface::HandleOverDraw(const TaskMeta& meta)
{
    std::ostream& stream = LogWriter(m_users[meta.userID]);

    const auto& buffer = meta.GetConstBuffer();
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

void GameInterface::InputMulligan(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Input Mulligan\n";

    size_t numMulligan;
    while (true)
    {
        m_ostream << "[*] How many cards to mulligan ? (0 ~ 3) ";
        m_istream >> numMulligan;

        if (numMulligan <= NUM_BEGIN_DRAW)
        {
            break;
        }
    }

    BYTE mulligan[NUM_BEGIN_DRAW] = {
        0,
    };
    for (size_t i = 0; i < numMulligan; ++i)
    {
        while (true)
        {
            size_t index = 0;
            m_ostream << "[*] Input card index " << i + 1 << " (0 ~ 2) : ";
            m_istream >> index;

            if (index <= NUM_BEGIN_DRAW - 1)
            {
                mulligan[i] = static_cast<BYTE>(index);
                break;
            }
        }
    }

    TaskMeta result = Serializer::CreateResponseMulligan(mulligan, numMulligan);
    m_agent.WriteSyncBuffer(std::move(result));
}

void GameInterface::InputMenu(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Main Menu\n";
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

void GameInterface::InputCard(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Select Card\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception InputSelectCard : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));

        return;
    }

    auto brief = flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    auto currentHand = brief->currentHand();

    int numCurrentHand = currentHand->size();
    size_t currentMana = brief->currentMana();

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

void GameInterface::InputTarget(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Targeting\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception InputTargeting : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));
        return;
    }

    auto brief = flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    auto currentField = brief->currentField();
    int numCurrentField = currentField->size();

    m_ostream << "Player field :\n";
    ShowCards(*currentField);

    auto opponentField = brief->opponentField();
    int numOpponentField = opponentField->size();

    m_ostream << "Opponent field :\n";
    ShowCards(*brief->opponentField());

    int src;
    while (true)
    {
        m_ostream << "Select source minion (0 ~ " << numCurrentField - 1
                  << ") : ";

        m_istream >> src;
        // Source Field range verification
        if (src >= 0 && src < numCurrentField)
        {
            auto currentAttacked = brief->currentAttacked();
            auto begin = currentAttacked->begin();
            auto end = currentAttacked->end();

            if (std::find(begin, end, currentField->Get(src)) != end)
            {
                m_ostream << "Already attacked minion\n";
            }
            else
            {
                break;
            }
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

void GameInterface::InputPosition(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Input Position\n";
    if (m_status == nullptr)
    {
        m_ostream << "Exception InputPosition : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
            TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));
        return;
    }

    auto brief = flatbuffers::GetRoot<FlatData::GameStatus>(m_status.get());
    auto currentField = brief->currentField();

    int numCurrentField = currentField->size();

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
