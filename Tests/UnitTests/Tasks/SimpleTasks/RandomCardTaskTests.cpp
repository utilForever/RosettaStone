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
    const auto Check = [](std::string id, CardType cardType, CardClass cardClass, Race cardRace = Race::INVALID) {
        GameConfig config;
        config.player1Class = cardClass;
        config.player2Class = cardClass;
        config.startPlayer = PlayerType::PLAYER1;
        config.doFillDecks = true;
        config.autoRun = false;
        Game game(config);
        Player& p = game.GetPlayer1();
    
        game.StartGame();
        game.ProcessUntil(Step::MAIN_START);

        auto rct = RandomCardTask(cardType, cardClass, cardRace);
        rct.SetPlayer(&p);
        auto result = Task::Run(&rct);
        EXPECT_EQ(result, TaskStatus::COMPLETE);

        auto ast = AddStackToTask(EntityType::HAND);
        ast.SetPlayer(&p);
        result = Task::Run(&ast);
        EXPECT_EQ(result, TaskStatus::COMPLETE);

        const auto hand = p.GetHandZone().GetAll();
        const auto target = hand.at(hand.size() - 1);

        EXPECT_EQ(target->card.GetCardType(), cardType);
        EXPECT_EQ(target->card.GetCardClass(), cardClass);
        EXPECT_EQ(target->card.GetRace(), cardRace);
    };

    const std::string id = "card_";
    const std::vector<CardClass> classes {
        CardClass::DRUID, CardClass::HUNTER, CardClass::MAGE, CardClass::PALADIN,
        CardClass::PRIEST, CardClass::ROGUE, CardClass::SHAMAN, CardClass::WARLOCK, CardClass::WARRIOR};

    int n = 0;
    for (auto iter : classes)
    {
        Check(id + std::to_string(++n), CardType::MINION, iter);
        Check(id + std::to_string(++n), CardType::SPELL, iter);
    }
}
