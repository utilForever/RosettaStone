/*************************************************************************
> File Name: Interface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Interface/Interface.h>
#include <Tasks/BasicTask.h>
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
GameInterface::GameInterface(GameAgent& agent,
                             std::ostream& output,
                             std::istream& input)
    : m_agent(agent), m_briefCache(nullptr), m_ostream(output), m_istream(input)
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

        const size_t msg = HandleMessage(m_buffer);
        if (msg == HANDLE_STOP)
        {
            break;
        }
    }

    // join agent thread
    at.join();

    // GameResult is set by GameEndTaskMeta Handler
    return m_result;
}

size_t GameInterface::HandleMessage(const TaskMeta& serialized)
{
    if (m_handler.find(serialized.id) != m_handler.end())
    {
        // find from handler table and call it
        m_handler[serialized.id](*this, serialized);
    }

    if (serialized.id == +TaskID::GAME_END)
    {
        return HANDLE_STOP;
    }

    return HANDLE_CONTINUE;
}

std::ostream& GameInterface::LogWriter(const std::string& name)
{
    m_ostream << "[*] " << name << " : ";
    return m_ostream;
}

template <std::size_t SIZE>
void GameInterface::ShowMenus(const std::array<std::string, SIZE>& menus)
{
    for (auto& menu : menus)
    {
        m_ostream << menu << '\n';
    }
}

void GameInterface::ShowCards(const CardVector& cards)
{
    for (const auto& card : cards)
    {
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

void GameInterface::HandleInvalid(const TaskMeta&)
{
    // Do Nothing
}

void GameInterface::HandlePlayerSetting(const TaskMeta& serialized)
{
    std::string name = "Player Setting";
    std::ostream& stream = LogWriter(name);

    using PlayerSettingTaskMeta = FlatData::PlayerSettingTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandlePlayerSetting : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<PlayerSettingTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        m_users[0] = "Unknown0";
        m_users[1] = "Unknown1";

        stream << "Exception HandlePlayerSetting : PlayerSettingTaskMeta is nullptr\n";
    }
    else
    {
        m_users[0] = meta->firstID()->c_str();
        m_users[1] = meta->secondID()->c_str();

        stream << "second : " << m_users[1] << '\n';
    }
}

void GameInterface::HandleSwap(const TaskMeta&)
{
    std::string name = "Player";
    LogWriter(name) << "Swap\n";
}

void GameInterface::HandleShuffle(const TaskMeta& serialized)
{
    LogWriter(m_users[serialized.userID]) << "Shuffled\n";
}

void GameInterface::HandleDraw(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using DrawTaskMeta = FlatData::DrawTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandleDraw : TaskMeta.GetBuffer is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<DrawTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        stream << "Exception HandleDraw : DrawTaskMeta is nullptr\n";
        return;
    }

    if (serialized.status == MetaData::DRAW_SUCCESS)
    {
        stream << "Draw Success\n";
    }
    else
    {
        if (serialized.status == MetaData::DRAW_EXHAUST ||
            serialized.status == MetaData::DRAW_EXHAUST_OVERDRAW)
        {
            stream << "Draw Exhausted : "
                   << static_cast<int>(meta->numExhausted()) << " Cards, "
                   << static_cast<int>(meta->numHearts()) << " Hearts\n";
        }

        if (serialized.status == MetaData::DRAW_OVERDRAW ||
            serialized.status == MetaData::DRAW_EXHAUST_OVERDRAW)
        {
            stream << "Draw OverDraw : "
                   << static_cast<int>(meta->numOverdraw()) << " Cards\n";
            ShowCards(*meta->burnt());
        }
    }
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

    BYTE mulligan[NUM_BEGIN_DRAW] = { 0, };
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

    TaskMeta result =
        Serializer::CreateRequireMulliganTaskMeta(mulligan, numMulligan);
    m_agent.WriteSyncBuffer(std::move(result));
}

void GameInterface::HandleMulligan(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    switch (serialized.status)
    {
        case MetaData::MULLIGAN_SUCCESS:
            stream << "Mulligan Success\n";
            break;

        case MetaData::MULLIGAN_INDEX_OUT_OF_RANGE:
            stream << "Mulligan Index out of range exception\n";
            break;

        case MetaData::MULLIGAN_DUPLICATED_INDEX:
            stream << "Mulligan Duplicated index exception\n";
            break;
    }
}

void GameInterface::HandleManaModification(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using ModifyManaTaskMeta = FlatData::ModifyManaTaskMeta;
    const auto& buffers = serialized.GetConstBuffer();
    if (buffers == nullptr)
    {
        stream << "Exception HandleManaModification : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<ModifyManaTaskMeta>(buffers.get());
    if (meta == nullptr)
    {
        stream << "Exception HandleManaModification - ModifyManaTaskMeta is nullptr\n";
        return;
    }

    std::string manaMode = "";
    switch (meta->manaMode())
    {
        case BasicTask::MANA_EXIST:
            manaMode = "exist";
            break;
        case BasicTask::MANA_TOTAL:
            manaMode = "total";
            break;
    }

    std::string numMode = "";
    switch (meta->numMode())
    {
        case BasicTask::NUM_ADD:
            numMode = "add";
            break;
        case BasicTask::NUM_SUB:
            numMode = "sub";
            break;
        case BasicTask::NUM_SYNC:
            numMode = "synchronize";
            break;
    }

    stream << "Modify Mana : " << numMode << " "
           << static_cast<int>(meta->object()) << " to " << manaMode << " mana,"
           << " result " << static_cast<int>(meta->result()) << '\n';
}

void GameInterface::HandleHealthModification(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using ModifyHealthTaskMeta = FlatData::ModifyHealthTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandleHealthModification : TaskMets is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<ModifyHealthTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        stream << "Exception HandleHealthModification : ModifyHealthTaskMeta is nullptr\n";
        return;
    }

    stream << "Modify Health : " << meta->card()->name()->c_str() << " get damage "
           << static_cast<int>(meta->damage()) << ", result "
           << static_cast<int>(meta->hurted()) << '\n';
}
//
void GameInterface::HandleSummonMinion(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using SummonMinionTaskMeta = FlatData::SummonMinionTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandleSummonMinion : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<SummonMinionTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        stream << "Exception HandleSummonMinion : SummonMinionTaskMeta is nullptr\n";
        return;
    }

    auto card = meta->card();
    stream << "Summon Minion : ";

    switch (serialized.status)
    {
        case MetaData::SUMMON_SUCCESS:
            stream << card->name()->c_str() << " at " << meta->index() << '\n';
            break;

        case MetaData::SUMMON_CARD_IDX_OUT_OF_RANGE:
            stream << "Card index out of range of hand\n";
            break;

        case MetaData::SUMMON_NOT_ENOUGH_MANA:
            stream << "Not enough mana\n";
            break;

        case MetaData::SUMMON_POSITION_OUT_OF_RANGE:
            stream << "Position out of range of field\n";
            break;
    }
}

void GameInterface::HandleCombat(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using CombatTaskMeta = FlatData::CombatTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        stream << "Exception HandleCombat : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<CombatTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        stream << "Exception HandleCombat : CombatTaskMeta is nullptr\n";
        return;
    }

    stream << "Combat : ";
    switch (serialized.status)
    {
        case MetaData::COMBAT_SUCCESS:
            stream << "{src " << meta->src()->name()->c_str() << "} "
                   << "vs {dst " << meta->dst()->name()->c_str() << "}\n";
            break;
        case MetaData::COMBAT_ALREADY_ATTACKED:
            stream << "Already Attacked Minion\n";
            break;
        case MetaData::COMBAT_DST_IDX_OUT_OF_RANGE:
            stream << "Destination Index Out of Range\n";
            break;
        case MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE:
            stream << "Source Index Out of Range\n";
            break;
        default:
            throw std::runtime_error(
                "GameInterface::HandleCombat::Unknown_Status");
    }
}

void GameInterface::HandleRequire(const TaskMeta& serialized)
{
    std::string name = "Require";

    using RequireTaskMeta = FlatData::RequireTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        LogWriter(name) << "Exception HandleRequire : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        LogWriter(name) << "Exception HandleRequire : RequireTaskMeta is nullptr\n";
        return;
    }

    auto required = TaskID::_from_integral(meta->required());
    if (m_inputHandler.find(required) != m_inputHandler.end())
    {
        // Find and call from Input Handler Table
        m_inputHandler[required](*this, std::move(serialized));
    }
}

void GameInterface::HandleBrief(const TaskMeta& serialized)
{
    std::ostream& stream = LogWriter(m_users[serialized.userID]);

    using BriefTaskMeta = FlatData::BriefTaskMeta;
    const BYTE* buffer = serialized.GetConstBuffer().get();
    size_t size = serialized.GetBufferSize();

    if (buffer == nullptr)
    {
        stream << "Exception HandleBrief : TaskMeta is nullptr\n";

        m_briefCache = nullptr;
        m_briefRawCache = nullptr;

        return;
    }

    // Deep copy of std::unique_ptr
    m_briefRawCache = std::make_unique<BYTE[]>(serialized.GetBufferSize());
    for (BYTE* ptr = m_briefRawCache.get(); size; --size)
    {
        *ptr++ = *buffer++;
    }

    // Deserialize BriefTaskMeta
    m_briefCache = flatbuffers::GetRoot<BriefTaskMeta>(m_briefRawCache.get());
    if (m_briefCache == nullptr)
    {
        stream << "Exception HandlBrief : BriefTaskMeta is nullptr\n";

        m_briefCache = nullptr;
        m_briefRawCache = nullptr;

        return;
    }

    stream << "Game Briefing\n"
           << m_users[m_briefCache->opponentPlayer()] << " - Hero "
           << m_briefCache->opponentHero()->name()->c_str() << ", Health "
           << m_briefCache->opponentHero()->health() << ", Mana "
           << static_cast<int>(m_briefCache->opponentMana()) << ", Hand "
           << static_cast<int>(m_briefCache->numOpponentHand()) << ", Deck "
           << static_cast<int>(m_briefCache->numOpponentDeck()) << '\n';

    stream << m_users[m_briefCache->opponentPlayer()] << " Field\n";
    ShowCards(*m_briefCache->opponentField());

    stream << m_users[m_briefCache->currentPlayer()] << " - Hero "
           << m_briefCache->currentHero()->name()->c_str() << ", Health "
           << m_briefCache->currentHero()->health() << ", Mana "
           << static_cast<int>(m_briefCache->currentMana()) << ", Hand "
           << static_cast<int>(m_briefCache->currentHand()->size()) << ", Deck "
           << static_cast<int>(m_briefCache->numCurrentDeck()) << '\n';

    stream << m_users[m_briefCache->currentPlayer()] << " Field\n";
    ShowCards(*m_briefCache->currentField());

    stream << m_users[m_briefCache->currentPlayer()] << " Hand\n";
    ShowCards(*m_briefCache->currentHand());
}

void GameInterface::InputSelectMenu(const TaskMeta& meta)
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

    TaskMeta result(TaskMetaTrait(TaskID::SELECT_CARD,
                                  static_cast<TaskMeta::status_t>(input)),
                    0, nullptr);
    m_agent.WriteSyncBuffer(std::move(result));
}

void GameInterface::InputSelectCard(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Select Card\n";
    if (m_briefCache == nullptr)
    {
        m_ostream << "Exception InputSelectCard : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
                TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));

        return;
    }

    auto currentHand = m_briefCache->currentHand();

    int numCurrentHand = currentHand->size();
    size_t currentMana = m_briefCache->currentMana();

    int in;
    while (true)
    {
        m_ostream << "Select card index (0 ~ " << numCurrentHand - 1 << ") : ";

        m_istream >> in;
        // Card hand index range verification
        if (in >= 0 && in < numCurrentHand)
        {
            if (currentHand->Get(in)->cost() > currentMana)
            {
                m_ostream << "Not enough mana\n";
            }
            else
            {
                break;
            }
        }
    }

    auto currentField = m_briefCache->currentField();

    int numCurrentField = currentField->size();
    CardType cardType =
        CardType::_from_integral(currentHand->Get(in)->cardType());

    // if selected card type is minion
    if (cardType == +CardType::MINION)
    {
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

        TaskMeta serialized =
            Serializer::CreateRequireSummonMinionTaskMeta(in, pos);
        m_agent.WriteSyncBuffer(std::move(serialized));
    }
    else
    {
        // TODO : if not minion
        m_agent.WriteSyncBuffer(TaskMeta());
    }
}

void GameInterface::InputTargeting(const TaskMeta& meta)
{
    LogWriter(m_users[meta.userID]) << "Targeting\n";
    if (m_briefCache == nullptr)
    {
        m_ostream << "Exception InputTargeting : BriefCache is nullptr\n";
        m_agent.WriteSyncBuffer(
                TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID)));
        return;
    }

    auto currentField = m_briefCache->currentField();
    int numCurrentField = currentField->size();

    m_ostream << "Player field :\n";
    ShowCards(*currentField);

    auto opponentField = m_briefCache->opponentField();
    int numOpponentField = opponentField->size();

    m_ostream << "Opponent field :\n";
    ShowCards(*m_briefCache->opponentField());

    int src;
    while (true)
    {
        m_ostream << "Select source minion (0 ~ " << numCurrentField - 1
                  << ") : ";

        m_istream >> src;
        // Source Field range verification
        if (src >= 0 && src < numCurrentField)
        {
            auto currentAttacked = m_briefCache->currentAttacked();
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

    TaskMeta targeting = Serializer::CreateRequireTargetingTaskMeta(src, dst);
    m_agent.WriteSyncBuffer(std::move(targeting));
}

void GameInterface::HandleTaskTuple(const TaskMeta& serialized)
{
    std::string name = "TaskTuple";
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        LogWriter(name) << "Exception HandleTaskTuple : TaskMeta is nullptr\n";
        return;
    }

    auto metaVector =
        flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());
    if (metaVector == nullptr)
    {
        LogWriter(name) << "Exception HandleTaskTuple : TaskMetaVector is nullptr\n";
        return;
    }

    for (const auto& meta : *metaVector->vector())
    {
        HandleMessage(TaskMeta::ConvertFrom(meta));
    }
}

void GameInterface::HandleGameEnd(const TaskMeta& serialized)
{
    std::string name = "GameEnd";

    using GameEndTaskMeta = FlatData::GameEndTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    if (buffer == nullptr)
    {
        LogWriter(name) << "Exception HandleGameEnd : TaskMeta is nullptr\n";
        return;
    }

    auto meta = flatbuffers::GetRoot<GameEndTaskMeta>(buffer.get());
    if (meta == nullptr)
    {
        LogWriter(name) << "Exception HandleGameEnd : GameEndTaskMeta is nullptr\n";
        return;
    }

    m_result.winnerID = meta->winnerID()->c_str();
    LogWriter(m_result.winnerID) << "Win\n";
}
}  // namespace Hearthstonepp