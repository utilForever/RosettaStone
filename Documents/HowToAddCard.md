# How to add card

* [Step 1: Select card](#step-1-select-card)
* [Step 2: Add card to CardSets](#step-2-add-card-to-cardsets)
  * [Cards with power](#cards-with-power)
* [Step 3: Add test code](#step-3-add-test-code)

## Step 1: Select card

The first thing you have to do is to select the cards to add.

See [CardList.md](./CardList.md) for all card list.

* [Basic card list](./CardList.md#basic)
* [Classic card list](./CardList.md#classic)
* [Hall of Fame card list](./CardList.md#hall-of-fame)

Select a card that is not yet implemented in card list.

Let's assume that you have selected the **CS2_124 ("Wolfrider")** card.

## Step 2: Add card to CardSets

The next thing to do is to add selected card to the card set. There are C++ source files for each card set in `Sources/Rosetta/PlayMode/CardSets`.
You need to select right source file by card set.
See [CardList.md](./CardList.md) and watch `Set` label.
Card `CS2_124` that you will add is a `CORE` set card. So this card should be added to `CoreCardsGen.cpp`

The main code for `CoreCardsGen.cpp` is as follows.

```C++
void CoreCardsGen::AddAll(std::map<std::string, Power*>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
```

Now you need to add a card to appropriate function depending on the card class. Do you not know what class of card is? Visit [Hearthstone Wiki](https://hearthstone.gamepedia.com/Hearthstone_Wiki) and search by card name. Search results for [Wolfrider](https://hearthstone.gamepedia.com/Wolfrider) are:

<img src="https://media-hearth.cursecdn.com/avatars/330/147/174.png">

```
Wolfrider is a neutral minion card, from the Basic set.
```

So you can add a card to the `AddNeutral` function.

**NOTE: All of the cards in card list can be collected. Therefore, it doesn't add to AddXXXNonCollect function.**

Wolfrider is a minion with the **Charge** ability. [Charge](https://hearthstone.gamepedia.com/Charge) is an ability allowing a minion to attack the same turn it is summoned or brought under a new player's control. The default abilities such as **Charge**, **Windfury** are saved as GameTag when parsing card data, so you don't need to add power separately. Therefore, you can add a card like this:

```C++
void CoreCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_124", CardDef(power));
}
```

Note that the first parameter is card ID and the second parameter is card power.

That's it! Now, it's time to test the card to see if it works.

**NOTE: There are many abilities that are not yet implemented. A list of currently implemented abilities can be found in [AbilityList.md](./AbilityList.md). If selected card is required an ability to be implemented, please ask collaborators([utilForever](https://github.com/utilForever), [CreatorSeraph](https://github.com/CreatorSeraph), [git-rla](https://github.com/git-rla) [FYLSunghwan](https://github.com/FYLSunghwan), [ShyRoute](https://github.com/ShyRoute)).**

### Cards with power

Some cards such as **CS2_041 ("Ancestral Healing")** require power.

<img src="https://media-hearth.cursecdn.com/avatars/329/970/216.png">

```
Ancestral Healing is a shaman spell card, from the Basic set. It restores a minion to their current maximum Health value and grants it the Taunt ability.
```

This card has two powers: One is the power to restore current maximum health, and the other is the power to grant the Taunt ability. Also, this card is a shaman spell card. So you can add a card to the `AddShaman` function.

```C++
void CoreCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion
    //       to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Tag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealFullTask>(EntityType::TARGET));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_041e", EntityType::TARGET));
    cards.emplace(
        "CS2_041",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));
}
```

Meanwhile, The power to grant the Taunt ability is the enchantment of Ancestral Healing. This enchantment is called **CS2_041e ("Ancestral Infusion")**. Since this card can't be collected, add it to `ShamanNonCollect` function.

```C++
void CoreCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_unique<Enchant>(Effects::Taunt));
    cards.emplace("CS2_041e", CardDef(power));
}
```

**NOTE: There are many tasks that are not yet implemented. A list of currently implemented tasks can be found in [TaskList.md](./TaskList.md). If selected card is required a task to be implemented, please ask collaborators([utilForever](https://github.com/utilForever), [CreatorSeraph](https://github.com/CreatorSeraph), [git-rla](https://github.com/git-rla) [FYLSunghwan](https://github.com/FYLSunghwan), [ShyRoute](https://github.com/ShyRoute)).**

## Step 3: Add test code

The last thing you need to do is test card you've added. There are test files for each card set in `Tests/UnitTests/PlayMode/CardSets`. Card `CS2_124` that you will add is a basic card set. So, you have to see file `CoreCardsGenTests.cpp`.

Test file has the following structure:

```C++
...

// --------------------------------------- MINION - NEUTRAL
// [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
// - Faction: Horde, Set: Core, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_124 : Wolfrider")
{
    ...
}

...
```

To test card, you need to consider play scenario. Also, you need to consider the abilities and powers that the cards have. For example, Wolfrider has **Charge** ability.

```
Charge is an ability allowing a minion to attack the same turn it is summoned or brought under a new player's control.
```

Therefore, you need to create a scenario to ensure that this ability works properly. An example of a scenario is:

```
1. Current player draws "Acidic Swamp Ooze" card.
2. Current player plays "Acidic Swap Ooze" card.
3. Current player ends turn.
4. Opponent player draws "Wolfrider" card.
5. Opponent player plays "Wolfrider" card.
6. Opponent player attacks "Acidic Swamp Ooze" with "Wolfrider".
```

It is important to check whether the processing is normal after each operation. For example, after current player draws "Acidic Swamp Ooze" card, you make sure that there is a card in hand and that card is "Acidic Swamp Ooze". In addition, after opponent player attacks "Acidic Swamp Ooze" with "Wolfrider", you make sure that there are no cards in the field. Let's write test code based on this scenario.

First, you should configure the scenario environment. `Game` is a class that stores player manages game state.

```C++
GameConfig config;
config.player1Class = CardClass::WARRIOR;
config.player2Class = CardClass::ROGUE;
config.startPlayer = PlayerType::PLAYER1;
config.doFillDecks = true;
config.autoRun = false;

Game game(config);
game.Start();
game.ProcessUntil(Step::MAIN_START);

Player& curPlayer = game.GetCurrentPlayer();
Player& opPlayer = game.GetOpponentPlayer();
curPlayer.SetTotalMana(10);
curPlayer.SetUsedMana(0);
opPlayer.SetTotalMana(10);
opPlayer.SetUsedMana(0);
```

Then, you should perform operations according to the scenario and test it.

```C++
// --------------------------------------- MINION - NEUTRAL
// [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
// - Faction: Horde, Set: Core, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_124 : Wolfrider")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    // 1. Current player draws "Acidic Swamp Ooze" card.
    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    // 2. Current player plays "Acidic Swap Ooze" card.
    game.Process(curPlayer, PlayCardTask::Minion(card1));

    // 3. Current player ends turn.
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    // 4. Opponent player draws "Wolfrider" card.
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider"));

    // 5. Opponent player plays "Wolfrider" card.
    game.Process(opPlayer, PlayCardTask::Minion(card2));

    // 6. Opponent player attacks "Acidic Swamp Ooze" with "Wolfrider".
    game.Process(opPlayer, AttackTask(card2, card1));
    EXPECT_EQ(curField.GetCount(), 0);
    EXPECT_EQ(opField.GetCount(), 0);
}
```

When you have finished writing test code, compile and build it. And you have to make sure the test passes.

```
[doctest] doctest version is "2.3.6"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:    583 |    583 passed |      0 failed |      0 skipped
[doctest] assertions:   6336 |   6336 passed |      0 failed |
[doctest] Status: SUCCESS!
```

Good! Now, [let's do a pull request](./PullRequests.md).
