/*************************************************************************
> File Name: Player.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Player Structure for GameAgent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Commons/Constants.h>
#include <Managers/Player.h>

namespace Hearthstonepp
{
Player::Player(const Account *account, const Deck *deck)
    : totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail())
{
    Cards* cardsInstance = Cards::GetInstance();

    const CardClass cardclass = deck->GetClass();
    const Card* heroCard = cardsInstance->GetHeroCard(cardclass);
    const Card* powerCard = cardsInstance->GetDefaultHeroPower(cardclass);

    for (auto& card : deck->GetPrimitiveDeck())
    {
        cards.emplace_back(new Entity(card));
    }

    hero = new Hero(heroCard);
    power = new HeroPower(powerCard);

    field.reserve(FIELD_SIZE);
    for (size_t i = 0; i < FIELD_SIZE; ++i)
    {
        field.emplace_back(nullptr);
    }
}
}  // namespace Hearthstonepp