# How to add task

- [Step 1: Define task](#step-1-define-task)
- [Step 2: Implement task interface ITask](#step-2-implement-task-interface-itask)
- [Step 3: Add test code](#step-3-add-test-code)

## Step 1: Define task

The first thing you have to do is defining task. There are some tasks composing the card effect. And it could be already implemented as `PlayerTasks` or `SimpleTasks`, but some are not implemented yet.

Let's define task! You need to consider that how task affect the game. Assume that you have selected the task `DestroyTask` which destroys something such as minion.

## Step 2: Implement task interface `ITask`

*In source file [Tasks.hpp](../Includes/Tasks/Tasks.hpp)*

```C++
class ITask
{
...
 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing. 
    virtual TaskStatus Impl(Player& player) = 0;

    //! Internal method of Clone().
    //! \return The cloned task.
    virtual ITask* CloneImpl() = 0;
};
```

There are two virtual methods you have to implement.

- Method `Impl` processes task logic internally and returns meta data.
- Method `CloneImpl` is internal method of `Clone()`.

First, declare class `DestroyTask` which inherits class `ITask`.

```C++
//!
//! \brief DestroyTask class.
//!
//! This class represents the task for destroying something such as minion.
//!
class DestroyTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to destroy.
    explicit DestroyTask(EntityType entityType);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;
};
```

Next you need to write implementation code. Method `Impl()` takes entity type as arguments and processes actual task logic for its purpose. The purpose of `DestroyTask` is to destroy something such as minion. Finally, if destroy succeeds, it returns `TaskStatus::COMPLETE` to indicate that destroy was success. Method `CloneImpl()` allocates `DestroyTask` instance dynamically.

```C++
TaskStatus DestroyTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        entity->Destroy();
    }

    return TaskStatus::COMPLETE;
}

ITask* DestroyTask::CloneImpl()
{
    return new DestroyTask(m_entityType);
}
```

`ITask` class provides method `Run()`. It calls method `Impl()`.

```C++
DestroyTask task(EntityType::TARGET);
task.SetPlayer(&player1);
task.SetTarget(player2.GetFieldZone()[0]);

TaskStatus result = task.Run();
```

## Step 3: Add test code

The last thing you need to do is test task you've added. We propose [DestroyTaskTests](../Tests/UnitTests/Tasks/SimpleTasks/DestroyTaskTests.cpp). This is simplest task to learn how to test.

```C++
TEST_CASE("[DestroyTask] - Run")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion1", 1, 1);
    const std::map<GameTag, int> tags;

    // Destroy Source Minion
    const auto minion1 = new Minion(player1, &card, tags);
    minion1->owner = &player1;
    player1.GetFieldZone().Add(*minion1, 0);

    DestroyTask task1(EntityType::SOURCE);
    task1.SetPlayer(&player1);
    task1.SetSource(player1.GetFieldZone()[0]);

    TaskStatus result = task1.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(player1.GetFieldZone().GetCount(), 0);

    // Destroy Target Minion
    const auto minion2 = new Minion(player2, &card, tags);
    minion2->owner = &player2;
    player2.GetFieldZone().Add(*minion2, 0);

    DestroyTask task2(EntityType::TARGET);
    task2.SetPlayer(&player1);
    task2.SetTarget(player2.GetFieldZone()[0]);

    TaskStatus result2 = task2.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result2, TaskStatus::COMPLETE);
    EXPECT_EQ(player2.GetFieldZone().GetCount(), 0);

    // Destroy Target Weapon
    Card weaponCard;
    player2.GetHero()->weapon = new Weapon(player2, &weaponCard, tags);
    player2.GetWeapon().owner = &player2;

    DestroyTask task3(EntityType::ENEMY_WEAPON);
    task3.SetPlayer(&player1);

    TaskStatus result3 = task3.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result3, TaskStatus::COMPLETE);
    EXPECT_EQ(player2.GetHero()->HasWeapon(), false);
}
```

When you have finished writing test code, compile and build it. And you have to make sure the test passes.

```
[==========] Running 77 tests from 16 test cases.
[----------] Global test environment set-up.

...

[----------] 1 tests from DestroyTask
[ RUN      ] DestroyTask.Run
[       OK ] DestroyTask.Run (0 ms)
[----------] 1 tests from DestroyTask (0 ms total)

...

[----------] Global test environment tear-down
[==========] 77 tests from 16 test cases ran. (501 ms total)
[  PASSED  ] 77 tests.
```

Good! Now, [let's do a pull request](./PullRequests.md).