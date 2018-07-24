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
Player::Player(const Account* account, const Deck* deck)
    : totalMana(0), existMana(0), exhausted(0), email(account->GetEmail())
{
    Cards* cardsInstance = Cards::GetInstance();
    const CardClass cardclass = deck->GetClass();

    const Card* heroCard = cardsInstance->GetHeroCard(cardclass);
    hero = new Hero(heroCard);

    const Card* powerCard = cardsInstance->GetDefaultHeroPower(cardclass);
    power = new HeroPower(powerCard);

    for (auto& card : deck->GetPrimitiveDeck())
    {
        Entity* entity = nullptr;
        switch (card->cardType)
        {
            case CardType::MINION:
                entity = new Minion(card);
                break;
            case CardType::WEAPON:
                entity = new Weapon(card);
                break;
            default:
                entity = new Entity(card);
                break;
        }

        cards.emplace_back(entity);
    }
}
}  // namespace Hearthstonepp