/*************************************************************************
> File Name: BasicTask.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implementation of Basic Task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTask.h>
#include <Tasks/TaskSerializer.h>

#include <algorithm>
#include <random>

namespace Hearthstonepp
{
    namespace BasicTask
    {
        std::function<TaskMeta()>
        RequireMethod(TaskID request, BYTE userID, TaskAgent& agent)
        {
            auto response = [request, userID, &agent]() -> TaskMeta {
                TaskMeta meta = Serializer::CreateRequireTaskMeta(request, userID);

                agent.Notify(std::move(meta), true);
                agent.Read(meta, true);

                return meta;
            };

            return response;
        }

        Task DoBothUser(Task&& task)
        {
            auto role = [role = std::move(task.GetTaskRole())](User& current, User& opponent) -> TaskMeta {
                std::vector<TaskMeta> vector = { role(current, opponent), role(opponent, current) };
                return Serializer::CreateTaskMetaVector(meta, vector);
            };

            return Task(TaskID::TASK_TUPLE, std::move(role));
        }

        Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition)
        {
            auto role = [role = std::move(task.GetTaskRole())](User& current, User& opponent) -> TaskMeta {
                TaskMeta meta;
                while (true)
                {
                    meta = std::move(role(current, opponent));
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

            return Serializer::CreateUserSettingTaskMeta(current.userID, opponent.userID);
        }

        Task UserSettingTask()
        {
            return Task(TaskID::USER_SETTING, RawUserSEtting);
        }

        TaskMeta RawUserSwap(User& current, User& opponent)
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

            return TaskMeta(TaskMetaTrait(TaskID::SHUFFLE, MetaData::SHUFFLE_SUCCESS, user.id));
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
                int hurts = static_cast<int>(user.exhausted * rest + rest * (rest + 1) / 2);
                int hurted = user.hero->GetHealth() - hurts;

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

            for (size_t i = 0; i < num; ++i)
            {
                hand.push_back(deck.back());
                deck.pop_back();
            }

            meta.numDraw = num;
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
            auto get = [](User& user, size_t type) -> BYTE&
            {
                if (type == MANA_EXIST)
                    return user.existMana;
                else if (type == MANA_TOTAL)
                    return user.totalMana;
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

            if (mana > 10)
            {
                mana = 10;
            }
            else if (mana < 0)
            {
                mana = 0;
            }

            Serializer::ModifyManaTaskMeta meta;
            meta.numMode = static_cast<BYTE>(numMode);
            meta.manaMode = static_cast<BYTE>(manaMode);
            meta.object = object;
            meta.result = mana;
            return Serializer::CreateModifyManaTaskMeta(meta, MetaData::MODIFY_MANA_SUCCESS, user.id);
        }

        Task ModifyManaTask(size_t numMode, size_t manaMode, BYTE object)
        {
            auto role = [=](User& current, User&) -> TaskMeta
            {
                return RawModifyManaTask(current, numMode, manaMode, object);
            };

            return Task(TaskID::MODIFY_MANA, std::move(role));
        }

        Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object)
        {
            auto role = [numMode, manaMode, &object](User& current, User&) -> TaskMeta
            {
                return RawModifyManaTask(current, numMode, manaMode, object);
            };

            return Task(TaskID::MODIFY_MANA, std::move(role));
        }

        TaskMeta RawModifyHealth(User& user, Card* card, BYTE damage)
        {
            Serializer::ModifyHealthTaskMeta meta;
            meta.card = card;
            meta.damage = damage;
            meta.hurted = card->GetHealth();

            if (damage > 0)
            {
                int hurted = card->GetHealth() - damage;
                card->SetHealth(hurted);
                meta.hurted = hurted

                if (hurted > 0)
                {
                    meta.isExhausted = false;
                }
                else
                {
                    meta.isExhausted = true;

                    user.usedMinion.emplace_back(card);

                    auto& field = user.field;
                    std::remove_if(field.begin(), field.end(), [card](const Card* tmp) { return tmp == card; });
                }
            }

            return Serializer::CreateModifyHealthTaskMeta(meta, MetaData::MODIFY_HEALTH_SUCCESS, user.id);
        }

        TaskMeta RawBrief(const User& current, const User& opponent)
        {
            Serializer::BriefTaskMeta meta(
                    current.id, opponent.id, current.existMana, opponent.existMana, opponent.hand.size(),
                    current.hand, current.field, opponent.field, current.attacked, opponent.attacked,
                    current.hero, opponent.hero);

            return Serializer::CreateBriefTaskMeta(meta, TaskID::BRIEF, user.id);
        }

        Task BriefTask()
        {
            return Task(TaskID::BRIEF, RawBrief);
        }

        Task SelectMenuTask(TaskAgent& agent)
        {
            auto role = [&agent](User& current, User&) -> TaskMeta {
                auto method = RequireMethod(TaskID::SELECT_MENU, current.id, agent);
                return method();
            };

            return Task(TaskID::SELECT_MENU, std::move(role));
        }

        Task SelectCardTask(TaskAgent& agent)
        {
            auto role = [&agent](User& current, User&) -> TaskMeta {
                auto method = RequireMethod(TaskID::SELECT_CARD, current.id, agent);
                return method();
            };

            return Task(TaskID::SELECT_CARD, std::move(role));
        }

        Task SelectTargetTask(TaskAgent& agent)
        {
            auto role = [&agent](User& current) -> TaskMeta {
                auto method = RequireMethod(TaskID::SELECT_TARGET, current.id, agent);
                return method();
            };

            return Task(TaskID::SELECT_TARGET, std::move(role));
        }

        TaskMeta RawMulligan(User& user, std::function<TaskMeta()>&& method)
        {
            TaskMetaTrait meta(TaskID::MULLIGAN);
            meta.userID = user.id;

            TaskMeta serialized = method();

            using RequireTaskMeta = MetaData::RequireMulliganTaskMeta;
            auto buffer = serialized.GetBuffer();
            auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

            auto index = req->mulligan();
            size_t read = index->size();

            if (read == 0)
            {
                meta.status = MetaData::MULLIGAN_SUCCESS;
                return TaskMeta(meta);
            }

            std::sort(index, index + read, [](BYTE a, BYTE b) { return a > b; });
            if (index[0] >= size)
            {
                meta.status = MetaData::MULLIGAN_INDEX_OUT_OF_RANGE;
                return TaskMeta(meta);
            }

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

            auto total = { mulligan, shuffle, draw };
            return Serializer::CreateTaskMetaVector(total);
        }

        Task MulliganTask(TaskAgent& agent)
        {
            auto role = [&agent](User& current, User&) -> TaskMeta {
                return RawMulligan(current, RequireMethod(TaskID::MULLIGAN, current.userID, agent));
            };

            return Task(TaskID::MULLIGAN, std::move(role));
        }

        TaskMeta RawGameEnd(User& current, User& opponent)
        {
            std::string winner = "";
            if (current.hero->GetHealth() <= 0)
            {
                winnerID = current.userID;
            }
            else
            {
                winnerID = opponent.userID;
            }

            return Serializer::CreateGameEndTaskMeta(winner);
        }

        Task GameEndTask()
        {
            return Task(TaskID::GAME_END, RawGameEnd);
        }
    }
}