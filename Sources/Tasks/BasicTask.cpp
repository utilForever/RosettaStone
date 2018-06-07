/*************************************************************************
> File Name: BasicTask.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implementation of Basic Task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Commons/Constants.h>
#include <Tasks/BasicTask.h>
#include <Tasks/MetaData.h>
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

Task DoBothUser(Task&& task)
{
    auto role = [role = task.GetTaskRole()](
                    User& current, User& opponent) -> TaskMeta {
        std::vector<TaskMeta> vector;
        // Current User Action
        vector.emplace_back(role(current, opponent));
        // Opponent User Action
        vector.emplace_back(role(opponent, current));
        return Serializer::CreateTaskMetaVector(vector);
    };

    return Task(TaskID::TASK_TUPLE, std::move(role));
}

Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition)
{
    auto role = [role = task.GetTaskRole(),
                 condition = condition](User& current,
                                                   User& opponent) -> TaskMeta {
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

TaskMeta RawUserSetting(User& current, User& opponent)
{
    current.id = 0;
    opponent.id = 0;

    return Serializer::CreateUserSettingTaskMeta(current.email, opponent.email);
}

Task UserSettingTask()
{
    return Task(TaskID::USER_SETTING, RawUserSetting);
}

TaskMeta RawSwapUser(User& current, User& opponent)
{
    std::swap(current, opponent);
    return TaskMeta(TaskMetaTrait(TaskID::SWAP, MetaData::SWAP_SUCCESS));
}

Task SwapUserTask()
{
    return Task(TaskID::SWAP, RawSwapUser);
}

TaskMeta RawShuffle(User& user)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(user.deck.begin(), user.deck.end(), gen);

    return TaskMeta(
        TaskMetaTrait(TaskID::SHUFFLE, MetaData::SHUFFLE_SUCCESS, user.id));
}

Task ShuffleTask()
{
    auto role = [](User& current, User&) -> TaskMeta {
        return RawShuffle(current);
    };

    return Task(TaskID::SHUFFLE, std::move(role));
}

TaskMeta RawDraw(User& user, size_t num)
{
    Serializer::DrawTaskMeta meta;
    TaskMeta::status_t result = MetaData::DRAW_SUCCESS;

    std::vector<Card*>& deck = user.deck;
    std::vector<Card*>& hand = user.hand;

    // when deck is exhausted
    if (deck.size() < num)
    {
        size_t rest = num - deck.size();
        meta.numExhausted = static_cast<BYTE>(rest);

        // sigma (i = 1 to rest) { current.exhausted + i }
        int hurts =
            static_cast<int>(user.exhausted * rest + rest * (rest + 1) / 2);
        int hurted = static_cast<int>(user.hero->GetHealth()) - hurts;

        meta.numHearts = static_cast<BYTE>(hurts);

        user.hero->SetHealth(hurted);
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
    auto role = [=](User& current, User&) -> TaskMeta {
        return RawDraw(current, num);
    };

    return Task(TaskID::DRAW, std::move(role));
}

TaskMeta RawModifyMana(User& user, size_t numMode, size_t manaMode, BYTE object)
{
    auto get = [](User& user, size_t type) -> BYTE& {
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
    auto role = [=](User& current, User&) -> TaskMeta {
        return RawModifyMana(current, numMode, manaMode, object);
    };

    return Task(TaskID::MODIFY_MANA, std::move(role));
}

Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object)
{
    auto role = [numMode, manaMode, &object](User& current, User&) -> TaskMeta {
        return RawModifyMana(current, numMode, manaMode, object);
    };

    return Task(TaskID::MODIFY_MANA, std::move(role));
}

TaskMeta RawModifyHealth(User& user, Card* card, BYTE damage)
{
    Serializer::ModifyHealthTaskMeta meta;
    meta.card = card;
    meta.damage = damage;

    int hurted = static_cast<int>(card->GetHealth()) - damage;
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
    card->SetHealth(meta.hurted);
    return Serializer::CreateModifyHealthTaskMeta(
        meta, MetaData::MODIFY_HEALTH_SUCCESS, user.id);
}

TaskMeta RawBrief(const User& current, const User& opponent)
{
    Serializer::BriefTaskMeta meta(
        current.id, opponent.id, current.existMana, opponent.existMana,
        static_cast<BYTE>(current.deck.size()),
        static_cast<BYTE>(opponent.deck.size()), 
        static_cast<BYTE>(opponent.hand.size()),
        current.hand, current.field, opponent.field, current.attacked,
        opponent.attacked, current.hero, opponent.hero);

    return Serializer::CreateBriefTaskMeta(meta, TaskID::BRIEF, current.id);
}

Task BriefTask()
{
    return Task(TaskID::BRIEF, RawBrief);
}

Task SelectMenuTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_MENU
    auto role = [&agent](User& current, User&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_MENU, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_MENU, std::move(role));
}

Task SelectCardTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_CARD
    auto role = [&agent](User& current, User&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_CARD, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_CARD, std::move(role));
}

Task SelectTargetTask(TaskAgent& agent)
{
    // Call RequireMethod with TaskID::SELECT_TARGET
    auto role = [&agent](User& current, User&) -> TaskMeta {
        auto method = RequireMethod(TaskID::SELECT_TARGET, current.id, agent);
        return method();
    };

    return Task(TaskID::SELECT_TARGET, std::move(role));
}

TaskMeta RawMulligan(User& user, std::function<TaskMeta()>&& method)
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
    BYTE index[NUM_BEGIN_DRAW] = { 0, };
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

    std::vector<Card*>& deck = user.deck;
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
    auto role = [&agent](User& current, User&) -> TaskMeta {
        return RawMulligan(current,
                           RequireMethod(TaskID::MULLIGAN, current.id, agent));
    };

    return Task(TaskID::MULLIGAN, std::move(role));
}

TaskMeta RawSummonMinion(User& current, size_t cardIndex, size_t position)
{
    TaskMetaTrait meta(TaskID::SUMMON_MINION);
    meta.userID = current.id;

    // Card Hand Index Verification
    if (cardIndex >= current.hand.size())
    {
        meta.status = MetaData::SUMMON_CARD_IDX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }
    // Sufficient Mana Verification
    if (current.hand[cardIndex]->GetCost() > current.existMana)
    {
        meta.status = MetaData::SUMMON_NOT_ENOUGH_MANA;
        return TaskMeta(meta);
    }
    // Field Position Verification
    if (position > current.field.size())
    {
        meta.status = MetaData::SUMMON_POSITION_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    Card* card = current.hand[cardIndex];
    int cost = static_cast<int>(card->GetCost());

    // Summoned minion can't attack right turn
    current.attacked.emplace_back(card);
    TaskMeta modified =
        RawModifyMana(current, NUM_SUB, MANA_EXIST, static_cast<BYTE>(cost));

    // summon minion at field
    current.field.insert(current.field.begin() + position, card);
    // erase from user's hand
    current.hand.erase(current.hand.begin() + cardIndex);
    meta.status = MetaData::SUMMON_SUCCESS;

    TaskMeta summon =
        Serializer::CreateSummonMinionTaskMeta(meta, card, position);

    std::vector<TaskMeta> vector;
    vector.emplace_back(std::move(summon));
    vector.emplace_back(std::move(modified));

    return Serializer::CreateTaskMetaVector(vector);
}

Task SummonMinionTask(size_t cardIndex, size_t position)
{
    auto role = [=](User& current, User&) -> TaskMeta {
        return RawSummonMinion(current, cardIndex, position);
    };

    return Task(TaskID::SUMMON_MINION, std::move(role));
}

TaskMeta RawCombat(User& current, User& opponent, size_t src, size_t dst)
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

    // Destination Verification, dst == 0 : hero / 1 < dst <= field.size : minion
    if (dst > opponent.field.size())
    {
        meta.status = MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
        return TaskMeta(meta);
    }

    Card* source = current.field[src];
    Card* target = opponent.hero;
    BYTE targetAttack = 0;
    if (dst > 0)
    {
        target = opponent.field[dst - 1];
        targetAttack = static_cast<BYTE>(target->GetAttack());
    }

    meta.status = MetaData::COMBAT_SUCCESS;
    TaskMeta combat = Serializer::CreateCombatTaskMeta(meta, source, target);
    TaskMeta hurtedSrc = RawModifyHealth(current, source, targetAttack);
    TaskMeta hurtedDst = RawModifyHealth(
        opponent, target, static_cast<BYTE>(source->GetAttack()));

    std::vector<TaskMeta> vector;
    vector.emplace_back(std::move(combat));
    vector.emplace_back(std::move(hurtedSrc));
    vector.emplace_back(std::move(hurtedDst));

    return Serializer::CreateTaskMetaVector(vector);
}

Task CombatTask(size_t src, size_t dst)
{
    auto role = [=](User& current, User& opponent) -> TaskMeta {
        return RawCombat(current, opponent, src, dst);
    };

    return Task(TaskID::COMBAT, std::move(role));
}

TaskMeta RawGameEnd(User& current, User& opponent)
{
    std::string winner = "";
    if (current.hero->GetHealth() <= 0)
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