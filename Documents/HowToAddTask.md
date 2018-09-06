# How to add task

- [Step 1: Define task](#step-1-define-task)
- [Step 2: Select TaskID](#step-2-select-taskid)
- [Step 3: Implement task interface ITask](#step-3-implement-task-interface-itask)
- [Step 4: Add test code](#step-4-add-test-code)

## Step 1: Define task

The first thing you have to do is defining task.

There are some tasks composing the card effects.
And it could be already implemented as `BasicTasks` or `PowerTasks`, but some are not implemented yet.

So what you have to do first is defining task. 
How task affect the game and what `TaskID` you want to use. 

Let's assume that we have selected the task `ShuffleTask`.

1. we can define task which shuffle the deck.
2. And it can use `TaskID` relative to shuffle.

## Step 2: Select `TaskID`

Next thing we have to do is select `TaskID`. 

In source file [TaskEnums](../Includes/Enums/TaskEnums.h), TaskID is listed with `better-enums`.
You can choose one of them or add new `TaskID`.

```C++
BETTER_ENUM(TaskID, int, INVALID = 0, TASK_VECTOR = 1, REQUIRE = 2,
            PLAYER_SETTING = 3, SWAP = 4, SHUFFLE = 5, DRAW = 6, OVER_DRAW = 7, ...)
```

We suggest you to add new one,
because old one would be implemented in `BasicTasks` with specific way.
If you use old one, you have to check new task doesn't affect existing routines.

In `ShuffleTask`, we choose `TaskID::SHUFFLE`.

## Step 3: Implement task interface `ITask`

`ITask` is task interface which can be run by `TaskAgent`.

Hearthstonepp is consists of `GameAgent`, `TaskAgent` and `GameInterface`.
- `GameAgent` is game implementation to manage the `Player` structure.
- `TaskAgent` manage the `ITask`. It run the task for `GameAgent` and communicate with `GameInterface`.
- `GameInterface` interact with user with some I/O.

So, we can implement `ITask` to control the `Player` structure to affect the game.

*In source file [Tasks.h](../Includes/Tasks/Tasks.h)*
```C++
class ITask
{
...
    virtual TaskID GetTaskID() const = 0;

 private:
    virtual MetaData Impl(Player& player1, Player& player2) = 0;
};
```

There are two virtual methods we have to implement.
- `GetTaskID` return the proper TaskID.
- `Impl` is task implementation with given player.

```C++
class ShuffleTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) override;
};
```

In `ShuffleTask`, we already choose `TaskID::SHUFFLE` to use.
```C++
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}
```

And it purpose to shuffle the deck.
```C++
MetaData ShuffleTask::Impl(Player& player1, Player&)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(player1.cards.begin(), player1.cards.end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
```

`Impl` give two players, player1 is current, player2 is opponent.
In common way, we use player1 as default.

`MetaData` enums represents result of tasks.
You can add proper `MetaData` enums to file [MetaData.h](../Includes/Tasks/MetaData.h).

`ITask` provides discrete method `Run` to run method `Impl` for `TaskAgent`.
```C++
BasicTasks::ShuffleTask task;
MetaData status = task.Run(player1, player2);
```
We can directly call the method `Run` or indirectly by `TaskAgent`.
```C++
TaskAgent agent;
TaskMeta meta;
agent.Run(meta, player1, player2, BasicTasks::ShuffleTask());
```

## Step 4: Add test code

As we implement two virtual methods, we need to test it.

Baseline I suggest is [BriefTaskTests](../Tests/UnitTests/Tasks/BasicTasks/BriefTaskTests.cpp), it just return `MetaData::BRIEF`.
```C++
TEST(BriefTask, GetTaskID)
{
    BasicTasks::BriefTask brief;
    EXPECT_EQ(brief.GetTaskID(), +TaskID::BRIEF);
}
```

`GetTaskID` tests check it return proper TaskID.

```C++
TEST(BriefTask, Run)
{
    BasicTasks::BriefTask brief;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);
    ...
}    
```

In source file [TestUtils](../Tests/UnitTests/Utils/TestUtils.h), struct `PlayerGenerator` generates default user with given `CardClass`.
You can use it to test the tasks. 

We suggest you to test task behavior and returned `MetaData`. 

All tests pass, you can make a pull requests.
