/*************************************************************************
> File Name: BasicTask.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implementation of Basic Task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Cards/Hero.h>
#include <Cards/Minion.h>
#include <Commons/Constants.h>
#include <Tasks/BasicTask.h>
#include <Tasks/MetaData.h>
#include <Tasks/PowerTask.h>
#include <Tasks/TaskSerializer.h>

#include <algorithm>
#include <random>

namespace Hearthstonepp::BasicTask
{
std::function<TaskMeta()> RequireMethod(TaskID request, BYTE userID,
                                        TaskAgent& agent)
{
    auto response = [request, userID, &agent]() -> TaskMeta {
        TaskMeta meta = Serializer::CreateRequireTaskMeta(request, userID);

        // Notify TaskMeta to main channel
        agent.Notify(std::move(meta));
        // Read TaskMeta from side channel
        agent.Read(meta, true);

        return meta;
    };

    return response;
}

Task DoBothPlayer(Task&& task)
{
    auto role = [role = task.GetTaskRole()](Player & current, Player & opponent)
                    ->TaskMeta
    {
        std::vector<TaskMeta> vector;
        // Current Player Action
        vector.emplace_back(role(current, opponent));
        // Opponent Player Action
        vector.emplace_back(role(opponent, current));
        return Serializer::CreateTaskMetaVector(vector);
    };

    return Task(TaskID::TASK_TUPLE, std::move(role));
}

Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition)
{
    auto role = [ role = task.GetTaskRole(), condition = condition ](
                    Player & current, Player & opponent)
                    ->TaskMeta
    {
        TaskMeta meta;
        while (true)
        {
            meta = role(current, opponent);
            // Do until the condition satisfied
            if (condition(meta))
            {
                break;
            }
        }

        return meta;
    };

    return Task(task.GetTaskID(), std::move(role));
}

TaskMeta RawPlayerSetting(Player& current, Player& opponent)
{
    current.id = 0;
    opponent.id = 0;

    return Serializer::CreatePlayerSettingTaskMeta(current.email,
                                                   opponent.email);
}

Task PlayerSettingTask()
{
    return Task(TaskID::USER_SETTING, RawPlayerSetting);
}

TaskMeta RawSwapPlayer(Player& current, Player& opponent)
{
    std::swap(current, opponent);
    return TaskMeta(TaskMetaTrait(TaskID::SWAP, MetaData::SWAP_SUCCESS));
}

Task SwapPlayerTask()
{
    return Task(TaskID::SWAP, RawSwapPlayer);
}

TaskMeta RawShuffle(Player& user)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(user.cardsPtrInDeck.begin(), user.cardsPtrInDeck.end(), gen);

    return TaskMeta(
        TaskMetaTrait(TaskID::SHUFFLE, MetaData::SHUFFLE_SUCCESS, user.id));
}

Task ShuffleTask()
{
    auto role = [](Player& current, Player&) -> TaskMeta {
        return RawShuffle(current);
    };

    return Task(TaskID::SHUFFLE, std::move(role));
}

TaskMeta RawDraw(Player& user, size_t num)
{
    Serializer::DrawTaskMeta meta;
    TaskMeta::status_t result = MetaData::DRAW_SUCCESS;

    std::vector<Card*>& deck = user.cardsPtrInDeck;
    std::vector<Card*>& hand = user.hand;

    // when deck is exhausted
    if (deck.size() < num)
    {
        size_t rest = num - deck.size();
        meta.numExhausted = static_cast<BYTE>(rest);

        // sigma (i = 1 to rest) { current.exhausted + i }
        int hurts =
            static_cast<int>(user.exhausted * rest + rest * (rest + 1) / 2);
        int hurted = static_cast<int>(user.hero->health) - hurts;

        meta.numHearts = static_cast<BYTE>(hurts);

        user.hero->health = hurted;
        user.exhausted += static_cast<BYTE>(rest);

        // calculating rest deck size
        num = deck.size();

        // full draw is fail
        result = MetaData::DRAW_EXHAUST;
    }

    // when hand size over 10, over draw
    if (hand.size() + num > 10)
    {
        // number of over draw
        size_t over = hand.size() + num - 10;

        meta.numOverdraw = static_cast<BYTE>(over);
        meta.burnt.resize(over);

        // draw burnt card
        for (size_t i = 0; i < over; ++i)
        {
            meta.burnt[i] = deck.back();
            deck.pop_back();
        }

        num = 10 - hand.size();

        // draw is fail
        if (result == MetaData::DRAW_EXHAUST)
        {
            result = MetaData::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = MetaData::DRAW_OVERDRAW;
        }
    }

    // successful draw
    for (size_t i = 0; i < num; ++i)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    meta.numDraw = static_cast<BYTE>(num);
    return Serializer::CreateDrawTaskMeta(meta, result, user.id);
}

Task DrawTask(size_t num)
{
    auto role = [=](Player& current, Player&) -> TaskMeta {
        return RawDraw(current, num);
    };

    return Task(TaskID::DRAW, std::move(role));
}

TaskMeta RawDraw(Player& user, Card* card)
{
    Serializer::DrawTaskMeta meta;
    TaskMeta::status_t result = MetaData::DRAW_SUCCESS;

    std::vector<Card*>& deck = user.cardsPtrInDeck;
    std::vector<Card*>& hand = user.hand;

    // successful draw
    hand.push_back(card);
    deck.pop_back();

    meta.numDraw = static_cast<BYTE>(1);
    return Serializer::CreateDrawTaskMeta(meta, result, user.id);
}

Task DrawTask(Card* card)
{
    auto role = [=](Player& current, Player&) -> TaskMeta {
        return RawDraw(current, card);
    };

    return Task(TaskID::DRAW, std::move(role));
}

TaskMeta RawModifyMana(Player& user, size_t numMode, size_t manaMode,
                       BYTE object)
{
    auto get = [](Player& user, size_t type) -> BYTE& {
        if (type == MANA_EXIST)
            return user.existMana;
        else if (type == MANA_TOTAL)
            return user.totalMana;
        else
            throw std::runtime_error("RawModifyMana return non-reference");
    };

    BYTE& mana = get(user, manaMode);
    switch (numMode)
    {
        case NUM_ADD:
            mana += object;
            break;
        case NUM_SUB:
            mana -= object;
            break;
        case NUM_SYNC:
            mana = object;
            break;
    }

    // Mana overflow
    if (mana > 10)
    {
        mana = 10;
    }
    // Mana underflow
    else if (mana < 0)
    {
        mana = 0;
    }

    Serializer::ModifyManaTaskMeta meta;
    meta.numMode = static_cast<BYTE>(numMode);
    meta.manaMode = static_cast<BYTE>(manaMode);
    meta.object = object;
    meta.result = mana;
    return Serializer::CreateModifyManaTaskMeta(
        meta, MetaData::MODIFY_MANA_SUCCESS, user.id);
}

Task ModifyManaTask(size_t numMode, size_t manaMode, BYTE object)
{
    auto role = [=](Player& current, Player&) -> TaskMeta {
        return RawModifyMana(current, numMode, manaMode, object);
    };

    return Task(TaskID::MODIFY_MANA, std::move(role));
}

Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object)
{
    auto role = [numMode, manaMode, &object](Player& current,
                                             Player&) -> TaskMeta {
        return RawModifyMana(current, numMode, manaMode, object);
    };

    return Task(TaskID::MODIFY_MANA, std::move(role));
}

TaskMeta RawModifyHealth(Player& user, Character* card, BYTE damage)
{
    Serializer::ModifyHealthTaskMeta meta;
    meta.card = card;
    meta.damage = damage;

    int hurted = static_cast<int>(card->health) - damage;
    // if minion is alive
    if (hurted > 0)
    {
        meta.isExhausted = false;
        meta.hurted = static_cast<BYTE>(hurted);
    }
    // if minion is exhausted
    else
    {
        meta.isExhausted = true;
        meta.hurted = 0;

        user.usedMinion.emplace_back(card);

        // find minion and remove it from field
        auto& field = user.field;
        auto ptr = std::find(field.begin(), field.end(), card);
        if (ptr != field.end())
        {
            field.erase(ptr);
        }
    }

    // adjust health
    card->health = meta.hurted;
    return Serializer::CreateModifyHealthTaskMeta(
        meta, MetaData::MODIFY_HEALTH_SUCCESS, user.id);
}

TaskMeta RawBrief(const Player& current, const Player& opponent)
{
    Serializer::BriefTaskMeta meta(
        current.id, opponent.id, current.existMana, opponent.existMana,
        static_cast<BYTE>(current.cardsPtrInDeck.size()),
        static_cast<BYTE>(opponent.cardsPtrInDeck.size()),
        static_cast<BYTE>(opponent.hand.size()), current.hand, current.field,
        opponent.field, current.attacked, opponent.attacked, current.hero,
        opponent.hero);

    return Serializer::CreateBriefTaskMeta(meta, TaskID::BRIEF, current.id);
}

Task BriefTask()
{
    return Task(TaskID::BRIEF, RawBrief);
}

Task SelectMenuTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_MENU
    auto role = [&agent](Player& current, Player&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_MENU, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_MENU, std::move(role));
}

Task SelectCardTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_CARD
    auto role = [&agent](Player& current, Player&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_CARD, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_CARD, std::move(role));
}

Task SelectTargetTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_TARGET
    auto role = [&agent](Player& current, Player&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_TARGET, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_TARGET, std::move(role));
}

TaskMeta RawMulligan(Player& user, std::function<TaskMeta()>&& method)
{
    TaskMetaTrait meta(TaskID::MULLIGAN);
    meta.userID = user.id;

    // Get Mulligan Input from Interface
    TaskMeta serialized = method();

    using RequireTaskMeta = FlatData::RequireMulliganTaskMeta;
    const auto& buffer = serialized.GetConstBuffer();
    auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    const BYTE* data = req->mulligan()->data();
    size_t read = req->mulligan()->size();

    // Copy data from input
    BYTE index[NUM_BEGIN_DRAW] = {
        0,
    };
    std::copy(data, data + read, index);

    // Mulligan doesn't require
    if (read == 0)
    {
        meta.status = MetaData::MULLIGAN_SUCCESS;
        return TaskMeta(meta);
    }

    // Sort decreasing order
    std::sort(index, index + read, [](BYTE a, BYTE b) { return a > b; });
    // Range verification
    if (index[0] >= NUM_BEGIN_DRAW)
    {
        meta.status = MetaData::MULLIGAN_INDEX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    // Duplicated Element Verification
    for (size_t i = 1; i < read; ++i)
    {
        if (index[i] == index[i - 1])
        {
            meta.status = MetaData::MULLIGAN_DUPLICATED_INDEX;
            return TaskMeta(meta);
        }
    }

    std::vector<Card*>& deck = user.cardsPtrInDeck;
    std::vector<Card*>& hand = user.hand;

    for (size_t i = 0; i < read; ++i)
    {
        deck.emplace_back(hand[index[i]]);
        hand.erase(hand.begin() + index[i]);
    }

    meta.status = MetaData::MULLIGAN_SUCCESS;
    TaskMeta mulligan(meta);
    TaskMeta shuffle = RawShuffle(user);
    TaskMeta draw = RawDraw(user, read);

    std::vector<TaskMeta> vector;
    vector.emplace_back(std::move(mulligan));
    vector.emplace_back(std::move(shuffle));
    vector.emplace_back(std::move(draw));

    return Serializer::CreateTaskMetaVector(vector, meta.status);
}

Task MulliganTask(TaskAgent& agent)
{
    auto role = [&agent](Player& current, Player&) -> TaskMeta {
        return RawMulligan(current,
                           RequireMethod(TaskID::MULLIGAN, current.id, agent));
    };

    return Task(TaskID::MULLIGAN, std::move(role));
}

TaskMeta PlayCard(Player& player, Player& opponent, size_t cardIndex, size_t position)
{
    TaskMetaTrait meta(TaskID::SUMMON_MINION);
    meta.userID = player.id;

    // Card Hand Index Verification
    if (cardIndex >= player.hand.size())
    {
        meta.status = MetaData::SUMMON_CARD_IDX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }
    // Sufficient Mana Verification
    if (player.hand[cardIndex]->cost > player.existMana)
    {
        meta.status = MetaData::SUMMON_NOT_ENOUGH_MANA;
        return TaskMeta(meta);
    }

    Card* card = player.hand[cardIndex];

    // erase from user's hand
    player.hand.erase(player.hand.begin() + cardIndex);

    switch (card->cardType)
    {
        case CardType::MINION:
            return PlayMinion(player, opponent, card, position);
        case CardType::WEAPON:
            return PlayWeapon(player, opponent, card);
        default:
            const std::vector<TaskMeta> vector;
            return Serializer::CreateTaskMetaVector(vector);
    }
}

Task PlayCardTask(size_t cardIndex, int position)
{
    auto role = [=](Player& current, Player& opponent) -> TaskMeta {
        return PlayCard(current, opponent, cardIndex, position);
    };

    return Task(TaskID::SUMMON_MINION, std::move(role));
}

TaskMeta PlayMinion(Player& player, Player& opponent, Card* card, size_t position)
{
    TaskMetaTrait meta(TaskID::SUMMON_MINION);
    meta.userID = player.id;

    // Field Position Verification
    if (position > player.field.size())
    {
        meta.status = MetaData::SUMMON_POSITION_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    if (player.field[position] != nullptr)
    {
        meta.status = MetaData::SUMMON_POSITION_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    player.field[position] = card;

    int cost = static_cast<int>(card->cost);

    // Summoned minion can't attack right turn
    player.attacked.emplace_back(card);
    TaskMeta modified =
        RawModifyMana(player, NUM_SUB, MANA_EXIST, static_cast<BYTE>(cost));

    // summon minion at field
    player.field.insert(player.field.begin() + position, card);
    meta.status = MetaData::SUMMON_SUCCESS;

    TaskMeta summon =
        Serializer::CreateSummonMinionTaskMeta(meta, card, position);

    if (card->power.powerTask != +PowerTaskType::EMPTY)
    {
        PowerTask::ProcessPower(player, opponent, card->power.powerTask);
    }

    std::vector<TaskMeta> vector;
    vector.emplace_back(std::move(summon));
    vector.emplace_back(std::move(modified));

    return Serializer::CreateTaskMetaVector(vector);
}

TaskMeta PlayWeapon(Player& player, Player& opponent, Card* card)
{
    (void)opponent;

    player.hero->weapon = dynamic_cast<Weapon*>(card);

    std::vector<TaskMeta> vector;
    return Serializer::CreateTaskMetaVector(vector);
}

TaskMeta RawCombat(Player& current, Player& opponent, size_t src, size_t dst)
{
    TaskMetaTrait meta(TaskID::COMBAT);
    meta.userID = current.id;

    // Source Minion Index Verification
    if (src >= current.field.size())
    {
        meta.status = MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    // Source Minion Verification By Attacked Vector
    std::vector<Card*>& attacked = current.attacked;
    if (std::find(attacked.begin(), attacked.end(), current.field[src]) !=
        attacked.end())
    {
        meta.status = MetaData::COMBAT_ALREADY_ATTACKED;
        return TaskMeta(meta);
    }

    attacked.emplace_back(current.field[src]);

    // Destination Verification, dst == 0 : hero / 1 < dst <= field.size :
    // minion
    if (dst > opponent.field.size())
    {
        meta.status = MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    Character* source = dynamic_cast<Character*>(current.field[src]);
    Character* target = (dst > 0)
                            ? dynamic_cast<Character*>(opponent.field[dst - 1])
                            : dynamic_cast<Character*>(opponent.hero);
    BYTE targetAttack = (dst > 0) ? static_cast<BYTE>(target->attack) : 0;

    meta.status = MetaData::COMBAT_SUCCESS;
    TaskMeta combat = Serializer::CreateCombatTaskMeta(meta, source, target);
    TaskMeta hurtedSrc = RawModifyHealth(current, source, targetAttack);
    TaskMeta hurtedDst =
        RawModifyHealth(opponent, target, static_cast<BYTE>(source->attack));

    std::vector<TaskMeta> vector;
    vector.emplace_back(std::move(combat));
    vector.emplace_back(std::move(hurtedSrc));
    vector.emplace_back(std::move(hurtedDst));

    return Serializer::CreateTaskMetaVector(vector);
}

Task CombatTask(size_t src, size_t dst)
{
    auto role = [=](Player& current, Player& opponent) -> TaskMeta {
        return RawCombat(current, opponent, src, dst);
    };

    return Task(TaskID::COMBAT, std::move(role));
}

TaskMeta RawGameEnd(Player& current, Player& opponent)
{
    std::string winner = "";
    if (current.hero->health <= 0)
    {
        winner = current.email;
    }
    else
    {
        winner = opponent.email;
    }

    return Serializer::CreateGameEndTaskMeta(winner);
}

Task GameEndTask()
{
    return Task(TaskID::GAME_END, RawGameEnd);
}
}  // namespace Hearthstonepp::BasicTask