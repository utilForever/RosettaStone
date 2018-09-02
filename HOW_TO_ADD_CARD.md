# How to add card

* [Step 1: Select card](#step-1-select-card)
* [Step 2: Add card to CardSets](#step-2-add-card-to-cardsets)
  * [Cards with power](#cards-with-power)
* [Step 3: Add test code](#step-3-add-test-code)

## Step 1: Select card

The first thing you have to do is to select the cards to add.

See [Issues](https://github.com/utilForever/Hearthstonepp/issues) for card list.

* [Basic(CORE) card implementation progress](https://github.com/utilForever/Hearthstonepp/issues/132)
* [Classic(EXPERT1) card implementation progress](https://github.com/utilForever/Hearthstonepp/issues/133)

Select a card that is not yet implemented in card list.

Let's assume that you have selected the **CS2_124 ("Wolfrider")** card.

## Step 2: Add card to CardSets

The next thing to do is to add selected card to the card set. There are C++ source files for each card set in `Sources/CardSets`. Card that you will add is a basic card set. This card should be added to `BasicCardsGen.cpp`.

The main code for `BasicCardsGen.cpp` is as follows.

```C++
void BasicCardsGen::AddAll(std::map<std::string, Power*>& cards)
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

<img src = "https://d1u5p3l4wpay3k.cloudfront.net/hearthstone_gamepedia/6/6a/Wolfrider%28174%29_Gold.png?version=0090eebf6442e780166b854676450b01">

```
Wolfrider is a neutral minion card, from the Basic set.
```

So you can add a card to the `AddNeutral` function.

**NOTE: All of the cards in card list can be collected. Therefore, it doesn't add to AddXXXNonCollect function.**

Wolfrider is a minion with the **Charge** ability. [Charge](https://hearthstone.gamepedia.com/Charge) is an ability allowing a minion to attack the same turn it is summoned or brought under a new player's control. The default abilities such as **Charge**, **Windfury** are saved as GameTag when parsing card data, so you don't need to add power separately. Therefore, you can add a card like this:

```C++
void BasicCardsGen::AddNeutral(std::map<std::string, Power*>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_124", nullptr);
}
```

Note that the first parameter is card ID and the second parameter is card power.

That's it! Now, it's time to test the card to see if it works.

**NOTE: There are many abilities that are not yet implemented. A list of currently implemented abilities can be found in [AbilityList.md](https://github.com/utilForever/Hearthstonepp/blob/master/AbilityList.md). If selected card is required an ability to be implemented, please ask collaborators([utilForever](https://github.com/utilForever), [revsic](https://github.com/revsic), [FuZer](https://github.com/FuZer)).**

### Cards with power

Some cards such as **CS2_041 ("Ancestral Healing")** require power.

<img src="https://d1u5p3l4wpay3k.cloudfront.net/hearthstone_gamepedia/1/1c/Ancestral_Healing%28216%29_Gold.png?version=261ab29ee760e8865377052d2b414322">

```
Ancestral Healing is a shaman spell card, from the Basic set. It restores a minion to their current maximum Health value and grants it the Taunt ability.
```

This card has two powers: One is the power to restore current maximum health, and the other is the power to grant the Taunt ability. Also, this card is a shaman spell card. So you can add a card to the `AddShaman` function.

```C++
void BasicCardsGen::AddShaman(std::map<std::string, Power*>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Basic, Rarity: Free
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
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::HealFullTask(EntityType::TARGET));
    p->powerTask.emplace_back(new PowerTask::AddEnchantmentTask("CS2_041e", EntityType::TARGET));
    cards.emplace("CS2_041", p);
}
```

Meanwhile, The power to grant the Taunt ability is the enchantment of Ancestral Healing. This enchantment is called **CS2_041e ("Ancestral Infusion")**. Since this card can't be collected, add it to `ShamanNonCollect` function.

```C++
void BasicCardsGen::AddShamanNonCollect(std::map<std::string, Power*>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: core,
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->enchant = new Enchant(Effects::Taunt);
    cards.emplace("CS2_041e", p);
}
```

**NOTE: There are many tasks that are not yet implemented. A list of currently implemented tasks can be found in [TaskList.md](https://github.com/utilForever/Hearthstonepp/blob/master/TaskList.md). If selected card is required a task to be implemented, see [How to add task](https://github.com/utilForever/Hearthstonepp/blob/master/HOW_TO_ADD_TASK.md) or please ask collaborators([utilForever](https://github.com/utilForever), [revsic](https://github.com/revsic), [FuZer](https://github.com/FuZer)).**

## Step 3: Add test code