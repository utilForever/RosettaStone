#include <Commons/Constants.h>
#include <Managers/Player.h>
#include <Tasks/TaskMeta.h>

namespace Hearthstonepp
{
Player::Player(const Account* account, const Deck* deck)
    : id(USER_INVALID),
      totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail()),
      hero(nullptr),
      power(nullptr)
{
    Cards* cardsInstance = Cards::GetInstance();
    const CardClass cardclass = deck->GetClass();

    const Card* heroCard = cardsInstance->GetHeroCard(cardclass);
    if (heroCard != nullptr)
    {
        hero = new Hero(heroCard);
    }

    const Card* powerCard = cardsInstance->GetDefaultHeroPower(cardclass);
    if (powerCard != nullptr)
    {
        power = new HeroPower(powerCard);
    }

    for (auto& card : deck->GetPrimitiveDeck())
    {
        if (card == nullptr)
        {
            continue;
        }

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
