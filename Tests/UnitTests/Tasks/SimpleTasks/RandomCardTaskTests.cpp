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

const auto Check = [](std::string id, std::vector<CardType> cardTypes,
                        std::vector<CardClass> cardClasses = std::vector<CardClass>(),
                        std::vector<Race> cardRaces = std::vector<Race>()) {
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;
    Game game(config);

    Player& p = game.GetPlayer1();

    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    {
        SCOPED_TRACE("process RandomCardTask");
        game.Process(p, new RandomCardTask(cardTypes, cardClasses, cardRaces));
    }

    {
        SCOPED_TRACE("process AddStackToTask");
        game.Process(p, new AddStackToTask(EntityType::HAND));
    }

    const auto hand = p.GetHandZone().GetAll();
    const auto target = hand.at(hand.size() - 1);

    bool isCorrectType = false, isCorrectClass = false, isCorrectRace = false;

    if (std::find(cardTypes.begin(), cardTypes.end(), target->card.GetCardType()) != cardTypes.end())
    {
        isCorrectType = true;
    }

    if (cardClasses.empty() || (std::find(cardClasses.begin(), cardClasses.end(), target->card.GetCardClass()) != cardClasses.end()))
    {
        isCorrectClass = true;
    }
    
    if (cardRaces.empty() || (std::find(cardRaces.begin(), cardRaces.end(), target->card.GetRace()) != cardRaces.end()))
    {
        isCorrectRace = true;
    }

    EXPECT_TRUE(isCorrectType);
    EXPECT_TRUE(isCorrectClass);
    EXPECT_TRUE(isCorrectRace);
};

const std::vector<CardClass> classes {
        CardClass::DRUID, CardClass::HUNTER, CardClass::MAGE, CardClass::PALADIN,
        CardClass::PRIEST, CardClass::ROGUE, CardClass::SHAMAN, CardClass::WARLOCK, CardClass::WARRIOR};

TEST(RandomCardTask, Run_GetMinions)
{
    const std::string id = "minion";
    int n = 0;
    for (auto iter : classes)
    {
        Check(id + std::to_string(n), { CardType::MINION }, { iter });
        ++n;
    }
}

TEST(RandomCardTask, Run_GetSpells)
{
    const std::string id = "spell";
    int n = 0;
    for (auto iter : classes)
    {
        Check(id + std::to_string(n), { CardType::SPELL }, { iter });
        ++n;
    }
}

TEST(RandomCardTask, Run_GetMinionsAndSpells)
{
    const std::string id = "card";
    int n = 0;
    for (auto iter : classes)
    {
        Check(id + std::to_string(n), { CardType::MINION, CardType::SPELL }, { iter });
        ++n;
    }
}

TEST(RandomCardTask, Run_GetRegardlessOfClass)
{
    const std::string id = "card";
    Check(id, { CardType::MINION, CardType::SPELL });
}