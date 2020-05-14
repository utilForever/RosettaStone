// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/Types/Player.hpp>
#include <Rosetta/PlayMode/Views/Types/UnknownCards.hpp>

namespace RosettaStone::PlayMode::Views::Types
{
void Hero::Parse(BoardRefView gameState, PlayerType side)
{
    if (side == gameState.GetSide())
    {
        Parse(gameState.GetHero());
    }
    else
    {
        Parse(gameState.GetOpponentHero());
    }
}

void Hero::Parse(PlayMode::Hero* hero)
{
    cardID = hero->card->id;
    attack = hero->GetAttack();
    health = hero->GetHealth();
    maxHealth = hero->GetMaxHealth();
    armor = hero->GetArmor();
    isExhausted = hero->IsExhausted();
}

void HeroPower::Parse(BoardRefView gameState, PlayerType side)
{
    cardID = gameState.GetHeroPower(side).card->id;
    isExhausted = gameState.GetHeroPower(side).IsExhausted();
}

void ManaCrystal::Parse(int usedMana, int totalMana, int overloadOwedMana,
                        int overloadLockedMana)
{
    used = usedMana;
    total = totalMana;
    overloadOwed = overloadOwedMana;
    overloadLocked = overloadLockedMana;
}

void Minion::Parse(const PlayMode::Minion& minion)
{
    cardID = minion.card->id;
    attack = minion.GetAttack();
    health = minion.GetHealth();
    maxHealth = minion.GetMaxHealth();
    spellPower = minion.GetSpellPower();
    isExhausted = minion.IsExhausted();
}

void Minions::Parse(BoardRefView gameState, PlayerType side)
{
    minions.clear();

    gameState.ForEachMinion(side, [&](PlayMode::Minion* minion) {
        minions.emplace_back();
        minions.back().Parse(*minion);
    });
}

void Player::Parse(BoardRefView gameState, PlayerType side,
                   UnknownCardsInfo& unknownCardsInfo)
{
    hero.Parse(gameState, side);
    heroPower.Parse(gameState, side);
    manaCrystal.Parse(gameState.GetUsedMana(side), gameState.GetTotalMana(side),
                      gameState.GetOverloadOwed(side),
                      gameState.GetOverloadLocked(side));
    minions.Parse(gameState, side);
    fatigue = gameState.GetFatigueDamage(side);

    int blockID = UnknownCardsInfo::DECK_BLOCK_ID;

    deck.clear();
    for (int i = 0; i < gameState.GetDeckCardCount(side); ++i)
    {
        deck.push_back(
            ParseCardInfo(INVALID_CARD_ID, blockID, unknownCardsInfo));
    }

    hand.clear();
    if (side == gameState.GetSide())
    {
        gameState.ForEachCurHandCard([&](const std::string& cardID) {
            hand.push_back(ParseCardInfo(cardID, blockID, unknownCardsInfo));
        });
    }
    else
    {
        gameState.ForEachOpHandCard([&](const std::string& cardID) {
            hand.push_back(ParseCardInfo(cardID, blockID, unknownCardsInfo));
        });
    }
}

CardInfo Player::ParseCardInfo(const std::string& cardID, int blockID,
                               UnknownCardsInfo& unknownCardsInfo)
{
    CardInfo info;

    auto BlockCardsGetter = [&]() {
        // if (blockID == UnknownCardsInfo::DECK_BLOCK_ID)
        //{
        //    return unknownCardsInfo.deckCards;
        //}
        // else
        //{
        //    return unknownCardsInfo.deckCards;
        //}
        return unknownCardsInfo.deckCards;
    };

    if (cardID != INVALID_CARD_ID)
    {
        const std::size_t cardsSetID =
            GetUnknownCardSetID(blockID, BlockCardsGetter, unknownCardsInfo);
        unknownCardsInfo.unknownCardsSets.RemoveCardFromSet(cardsSetID, cardID);

        info.SetAsRevealedCard(cardID);
    }
    else
    {
        const std::size_t cardsSetID =
            GetUnknownCardSetID(blockID, BlockCardsGetter, unknownCardsInfo);
        const std::size_t cardSetsSetCardIdx =
            unknownCardsInfo.unknownCardsSets.AssignCardToSet(cardsSetID);

        info.SetAsHiddenCard(cardsSetID, cardSetsSetCardIdx);
    }

    return info;
}
}  // namespace RosettaStone::PlayMode::Views::Types