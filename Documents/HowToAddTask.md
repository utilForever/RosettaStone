# How to add task

- [Step 1: Define task](#step-1-define-task)
- [Step 2: Select TaskID](#step-2-select-taskid)
- [Step 3: Implement task interface ITask](#step-3-implement-task-interface-itask)
- [Step 4: Add test code](#step-4-add-test-code)

## Step 1: Define task

The first thing you have to do is defining task. There are some tasks composing the card effect. And it could be already implemented as `PlayerTasks` or `SimpleTasks`, but some are not implemented yet.

Let's define task! There are two things you need to consider: How task affect the game and what `TaskID` you want to use. Assume that you have selected the task `DestroyTask`.

1. You can define task which destroys something such as minion.
2. And it can use `TaskID` relative to destroy.

## Step 2: Select `TaskID`

Next thing you have to do is select `TaskID`. 

In [TaskEnums.h](../Includes/Enums/TaskEnums.h), TaskID is listed by `BETTER_ENUM` macro. You can choose one of them or add new `TaskID`.

```C++
BETTER_ENUM(TaskID, int, INVALID, DRAW, OVERDRAW, MODIFY_MANA, DAMAGE, ...)
```

We suggest you to add new one, because old one would be implemented in `SimpleTasks` with specific way. If you use old one, you have to check new task doesn't affect existing task routines.

Let's add task ID for `DestroyTask` that you need to create.

```C++
BETTER_ENUM(TaskID, int, INVALID, DRAW, OVERDRAW, MODIFY_MANA, DAMAGE, SHUFFLE, ...)
```

## Step 3: Implement task interface `ITask`

*In source file [Tasks.h](../Includes/Tasks/Tasks.h)*

```C++
class ITask
{
...
    virtual TaskID GetTaskID() const = 0;

 private:
    virtual MetaData Impl(Player& player) = 0;
};
```

There are two virtual methods you have to implement.

- `GetTaskID` method returns proper TaskID.
- `Impl` method implements task logic and takes player as arguments.

First, declare `DestroyTask` class which inherits `ITask` class.

```C++
class DestroyTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player) override;
};
```

Next you need to write implementation code. `GetTaskID()` method returns `TaskID` type, so you can write to return `TaskID::DESTROY` that task ID you choose. `Impl()` method takes player as arguments and processes actual task logic for its purpose. The purpose of `DestroyTask` is to destroy something such as minion. Finally, if destroy succeeds, it returns `MetaData::COMPLETE` to indicate that destroy was success.

```C++
TaskID DestroyTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        entity->Destroy();
    }

    return TaskStatus::COMPLETE;
}
```

**NOTE: `MetaData` enum represents result of tasks. You can add another `MetaData` enum to [MetaData.h](../Includes/Tasks/MetaData.h).**

`ITask` class provides `Run` method. It calls `Impl` method.

```C++
DestroyTask task1(EntityType::SOURCE);
task1.SetSource(player1.GetField().GetMinion(0));

TaskStatus result = task1.Run(player1);
```

## Step 4: Add test code

The last thing you need to do is test task you've added. We propose [DestroyTaskTests](../Tests/UnitTests/Tasks/SimpleTasks/DestroyTaskTests.cpp). This is simplest task to learn how to test. When `GetTaskID()` of this task is called, it just returns `TaskID::DESTROY`. You can verify that your test code returns this value.

```C++
TEST(DestroyTask, GetTaskID)
{
    const DestroyTask task(EntityType::EMPTY);
    EXPECT_EQ(task.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyTask, Run)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion1", 1, 1);

    // Destroy Source Minion
    auto minion1 = new Minion(player1, card);
    minion1->SetOwner(player1);
    player1.GetField().AddMinion(*minion1, 0);

    DestroyTask task1(EntityType::SOURCE);
    task1.SetSource(player1.GetField().GetMinion(0));

    TaskStatus result = task1.Run(player1);
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(player1.GetField().GetNumOfMinions(), 0u);

    // Destroy Target Minion
    auto minion2 = new Minion(player2, card);
    minion2->SetOwner(player2);
    player2.GetField().AddMinion(*minion2, 0);

    DestroyTask task2(EntityType::TARGET);
    task2.SetTarget(player2.GetField().GetMinion(0));

    TaskStatus result2 = task2.Run(player1);
    EXPECT_EQ(result2, TaskStatus::COMPLETE);
    EXPECT_EQ(player2.GetField().GetNumOfMinions(), 0u);

    // Destroy Target Weapon
    Card weaponCard;
    player2.GetHero()->weapon = new Weapon(player2, weaponCard);
    player2.GetHero()->weapon->SetOwner(player2);

    DestroyTask task3(EntityType::ENEMY_WEAPON);

    TaskStatus result3 = task3.Run(player1);
    EXPECT_EQ(result3, TaskStatus::COMPLETE);
    EXPECT_EQ(player2.GetHero()->HasWeapon(), false);
}
```

When you have finished writing test code, compile and build it. And you have to make sure the test passes.

```
[==========] Running 77 tests from 16 test cases.
[----------] Global test environment set-up.

...

[----------] 2 tests from DestroyTask
[ RUN      ] DestroyTask.GetTaskID
[       OK ] DestroyTask.GetTaskID (0 ms)
[ RUN      ] DestroyTask.Run
[       OK ] DestroyTask.Run (0 ms)
[----------] 2 tests from DestroyTask (0 ms total)

...

[----------] Global test environment tear-down
[==========] 77 tests from 16 test cases ran. (501 ms total)
[  PASSED  ] 77 tests.
```

Good! Now, [let's do a pull request](./PullRequests.md).