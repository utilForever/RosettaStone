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
      email(player->GetEmail()),
      weapon(nullptr)
{
    Cards* cards = Cards::GetInstance();

    Deck* tmpDeck = player->GetDeck(deckID);
    const CardClass cardclass = tmpDeck->GetClass();

    const Card* heroCard = cards->GetHeroCard(cardclass);
    const Card* powerCard = cards->GetDefaultHeroPower(cardclass);

    cardDeck.reserve(sizeof(Card) * (MAXIMUM_NUM_CARDS_IN_DECK + 2));
    for (auto& ptrCard : tmpDeck->GetPrimitiveDeck())
    {
        // Deep copy of card data
        cardDeck.emplace_back(Card(*ptrCard));
        deck.emplace_back(&cardDeck.back());
    }

    cardDeck.emplace_back(Hero(*reinterpret_cast<const Hero*>(heroCard)));
    hero = reinterpret_cast<Hero*>(&cardDeck.back());

    cardDeck.emplace_back(
        HeroPower(*reinterpret_cast<const HeroPower*>(powerCard)));
    power = reinterpret_cast<HeroPower*>(&cardDeck.back());
}
}  // namespace Hearthstonepp
