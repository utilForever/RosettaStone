# How to add card

* [Step 1: Select card](#step-1-select-card)
* [Step 2: Add card to CardSets](#step-2-add-card-to-cardsets)
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

```
Wolfrider is a neutral minion card, from the Basic set.
...
```

So you can add a card to the `AddNeutral` function.

**NOTE: All of the cards in card list can be collected. Therefore, it doesn't add to AddXXXNonCollect function.**

## Step 3: Add test code
