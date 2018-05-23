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
            return TaskMeta(TaskID::SWAP, MetaData::SWAP_SUCCESS);
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

            return TaskMeta(TaskID::SHUFFLE, MetaData::SHUFFLE_SUCCESS, user.id);
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
    }
}