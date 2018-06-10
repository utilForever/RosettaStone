/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/AgentStructures.h>
#include <Commons/Constants.h>

namespace Hearthstonepp
{
User::User(Player* player, int deckID)
    : totalMana(0),
      existMana(0),
      exhausted(0),
      userID(player->GetID()),
      weapon(nullptr)
{
    Cards* cards = Cards::GetInstance();

    Deck* tmpDeck = player->GetDeck(deckID);
    const CardClass cardclass = tmpDeck->GetClass();

    const Card* heroCard = cards->GetHeroCard(cardclass);
    const Card* powerCard = cards->GetDefaultHeroPower(cardclass);

    cardsInDeck.reserve(sizeof(Card) * (MAXIMUM_NUM_CARDS_IN_DECK + 2));
    for (auto& ptrCard : tmpDeck->GetPrimitiveDeck())
    {
        // Deep copy of card data
        cardsInDeck.emplace_back(Card(*ptrCard));
        cardsPtrInDeck.emplace_back(&cardsInDeck.back());
    }

    cardsInDeck.emplace_back(Hero(*reinterpret_cast<const Hero*>(heroCard)));
    hero = reinterpret_cast<Hero*>(&cardsInDeck.back());

    cardsInDeck.emplace_back(
        HeroPower(*reinterpret_cast<const HeroPower*>(powerCard)));
    power = reinterpret_cast<HeroPower*>(&cardsInDeck.back());
}
}  // namespace Hearthstonepp