# How to add task

- [Step 1: Define task](#step-1-define-task)
- [Step 2: Select TaskID](#step-2-select-taskid)
- [Step 3: Implement task interface ITask](#step-3-implement-task-interface-itask)
- [Step 4: Add test code](#step-4-add-test-code)

## Step 1: Define task

The first thing you have to do is defining task. There are some tasks composing the card effect. And it could be already implemented as `BasicTasks` or `PowerTasks`, but some are not implemented yet.

Let's define task! There are two things you need to consider: How task affect the game and what `TaskID` you want to use. Assume that you have selected the task `ShuffleTask`.

1. You can define task which shuffle the deck.
2. And it can use `TaskID` relative to shuffle.

## Step 2: Select `TaskID`

Next thing you have to do is select `TaskID`. 

In [TaskEnums.h](../Includes/Enums/TaskEnums.h), TaskID is listed by `BETTER_ENUM` macro. You can choose one of them or add new `TaskID`.

```C++
BETTER_ENUM(TaskID, int, INVALID = 0, TASK_VECTOR = 1, REQUIRE = 2,
            PLAYER_SETTING = 3, SWAP = 4, DRAW = 5, OVER_DRAW = 6,
            ...)
```

We suggest you to add new one, because old one would be implemented in `BasicTasks` with specific way. If you use old one, you have to check new task doesn't affect existing task routines.

Let's add task ID for `ShuffleTask` that you need to create.

```C++
BETTER_ENUM(TaskID, int, INVALID = 0, TASK_VECTOR = 1, REQUIRE = 2,
            PLAYER_SETTING = 3, SWAP = 4, SHUFFLE = 5, DRAW = 6, OVER_DRAW = 7, 
            ...)
```

## Step 3: Implement task interface `ITask`

`ITask` is task interface which can be run by `TaskAgent`.

Hearthstone++ task system is consists of three classes: `GameAgent`, `TaskAgent` and `GameInterface`.

- `GameAgent` class manages game phase and `Player` structure.
- `TaskAgent` class manages `ITask`. It run the task for `GameAgent` and communicate with `GameInterface`.
- `GameInterface` class interacts with user using I/O serialization.

You can implement `ITask` to control `Player` structure to affect the game.

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

There are two virtual methods you have to implement.

- `GetTaskID` method returns proper TaskID.
- `Impl` method implements task logic and takes two player as arguments.

First, declare `ShuffleTask` class which inherits `ITask` class.

```C++
class ShuffleTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) override;
};
```

Next you need to write implementation code. `GetTaskID()` method returns `TaskID` type, so you can write to return `TaskID::SHUFFLE` that task ID you choose. `Impl()` method takes two player as arguments and processes actual task logic for its purpose. The purpose of `ShuffleTask` is to shuffle multiple cards in random order. Finally, if shuffle succeeds, it returns `MetaData::SHUFFLE_SUCCESS` to indicate that shuffle was success.

```C++
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

MetaData ShuffleTask::Impl(Player& player1, Player&)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(player1.cards.begin(), player1.cards.end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
```

**NOTE: `player1` is current player and `player2` is opponent player. In common way, we use `player1` as default.**

**NOTE: `MetaData` enum represents result of tasks. You can add another `MetaData` enum to [MetaData.h](../Includes/Tasks/MetaData.h).**

`ITask` class provides `Run` method. it runs `Impl` method of `TaskAgent` class. For your convenience, we have implemented `Run` method so that you can call it directly or indirectly by `TaskAgent` class.

*Direct call*

```C++
BasicTasks::ShuffleTask task;
MetaData status = task.Run(player1, player2);
```

*Indirect call*

```C++
TaskAgent agent;
TaskMeta meta;
agent.Run(meta, player1, player2, BasicTasks::ShuffleTask());
```

## Step 4: Add test code

The last thing you need to do is test task you've added. We propose [BriefTaskTests](../Tests/UnitTests/Tasks/BasicTasks/BriefTaskTests.cpp). This is simplest task to learn how to test. When `GetTaskID()` of this task is called, it just returns `TaskID::BRIEF`. You can verify that your test code returns this value.

```C++
TEST(BriefTask, GetTaskID)
{
    BasicTasks::BriefTask brief;
    EXPECT_EQ(brief.GetTaskID(), +TaskID::BRIEF);
}

TEST(BriefTask, Run)
{
    BasicTasks::BriefTask brief;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);
    ...
}    
```

In [TestUtils.h](../Tests/UnitTests/Utils/TestUtils.h), struct `PlayerGenerator` generates default user with given `CardClass`.
You can use it to test task. We suggest you to test behavior and returned `MetaData` type. 


When you have finished writing test code, compile and build it. And you have to make sure the test passes.

```
[==========] Running 77 tests from 16 test cases.
[----------] Global test environment set-up.

...

[----------] 2 tests from BriefTask
[ RUN      ] BriefTask.GetTaskID
[       OK ] BriefTask.GetTaskID (0 ms)
[ RUN      ] BriefTask.Run
[       OK ] BriefTask.Run (0 ms)
[----------] 2 tests from BriefTask (0 ms total)

...

[----------] Global test environment tear-down
[==========] 77 tests from 16 test cases ran. (501 ms total)
[  PASSED  ] 77 tests.
```

Good! Now, [let's do a pull request](./PullRequests.md).