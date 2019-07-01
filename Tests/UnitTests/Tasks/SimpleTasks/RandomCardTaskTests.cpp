#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddStackToTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

class RandomCardTestPolicy : public BasicPolicy
{
 public:
    explicit RandomCardTestPolicy(
        std::function<void(const TaskMeta&)>&& overdrawHandler)
        : m_overdrawHandler(std::move(overdrawHandler))
    {
        // Do nothing
    }

    void NotifyOverDraw(const TaskMeta& meta) override
    {
        m_overdrawHandler(meta);
    }

 private:
    std::function<void(const TaskMeta&)> m_overdrawHandler;
};

TEST(RandomCardTask, GetTaskID)
{
    const auto rct = new RandomCardTask(
        CardType::INVALID, CardClass::INVALID, Race::INVALID);
    EXPECT_EQ(rct->GetTaskID(), TaskID::RANDOM_CARD);
}

TEST(RandomCardTask, Run)
{
    const auto Check = [](std::string id, CardType cardType = CardType::INVALID,
                        CardClass cardClass = CardClass::INVALID, Race cardRace = Race::INVALID) {
        GameConfig config;
        config.player1Class = CardClass::WARLOCK;
        config.startPlayer = PlayerType::PLAYER1;
        config.doFillDecks = true;
        config.autoRun = false;
        Game game(config);
        Player& p = game.GetPlayer1();
    
        game.StartGame();
        game.ProcessUntil(Step::MAIN_START);

        game.Process(p, new RandomCardTask(cardType, cardClass, cardRace));
        game.Process(p, new AddStackToTask(EntityType::HAND));

        const auto hand = p.GetHandZone().GetAll();
        const auto target = hand.at(hand.size() - 1);

        if (cardType == CardType::INVALID)
        {
            if (target->card.GetCardType() != CardType::MINION &&
                target->card.GetCardType() != CardType::SPELL)
            {
                EXPECT_EQ(target->card.GetCardType(), CardType::INVALID);
            }
        }
        else
        {
            EXPECT_EQ(target->card.GetCardType(), cardType);
        }

        if (cardClass != CardClass::INVALID)   
        { 
            EXPECT_EQ(target->card.GetCardClass(), cardClass);
        }

        if (cardRace != Race::INVALID) 
        {
            EXPECT_EQ(target->card.GetRace(), cardRace);
        }
    };

    const std::string id = "card";
    const std::vector<CardClass> classes {
        CardClass::DRUID, CardClass::HUNTER, CardClass::MAGE, CardClass::PALADIN,
        CardClass::PRIEST, CardClass::ROGUE, CardClass::SHAMAN, CardClass::WARLOCK, CardClass::WARRIOR};

    int n = 0;
    for (auto iter : classes)
    {
        Check(id + std::to_string(n), CardType::MINION, iter);
        ++n;
        Check(id + std::to_string(n), CardType::SPELL, iter);
        ++n;
    }
    Check(id + std::to_string(n), CardType::MINION, CardClass::NEUTRAL); ++n;
    Check(id + std::to_string(n), CardType::MINION); ++n;
    Check(id + std::to_string(n), CardType::SPELL); ++n;
    Check(id + std::to_string(n)); ++n;
}
