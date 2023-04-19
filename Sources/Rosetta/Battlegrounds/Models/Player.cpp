// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

namespace RosettaStone::Battlegrounds
{
FieldZone& Player::GetField()
{
    return isInCombat ? battleField : recruitField;
}

void Player::SelectHero(std::size_t idx)
{
    const auto heroCard = Cards::FindCardByDbfID(heroChoices.at(idx));
    hero.Initialize(heroCard);

    selectHeroCallback(*this);
}

void Player::PrepareTavern()
{
    prepareTavernMinionsCallback(*this);
}

void Player::PurchaseMinion(std::size_t idx)
{
    if (remainCoin < NUM_COIN_PURCHASE_MINION)
    {
        return;
    }

    purchaseMinionCallback(*this, idx);

    remainCoin -= NUM_COIN_PURCHASE_MINION;
}

void Player::PlayCard(std::size_t handIdx, std::size_t fieldIdx, int targetIdx)
{
    if (std::holds_alternative<Minion>(hand[handIdx]))
    {
        // Check the field is full
        if (recruitField.IsFull())
        {
            return;
        }

        // Check if we can play this card and the target is valid
        if (!std::get<Minion>(hand[handIdx]).IsPlayableByCardReq(*this) ||
            !std::get<Minion>(hand[handIdx])
                 .IsValidPlayTarget(*this, targetIdx))
        {
            return;
        }

        CardData card = hand.Remove(hand[handIdx]);

        auto minion = std::get<Minion>(card);
        minion.getPlayerCallback = [&]() -> Player& { return *this; };
        minion.SetIndex(getNextCardIndexCallback());

        Player& opponent = getOpponentPlayerCallback(*this);

        if (targetIdx == -1)
        {
            recruitField.Add(minion, fieldIdx);

            recruitField.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::SUMMON,
                                                    minion);
            });

            opponent.recruitField.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::SUMMON,
                                                    minion);
            });

            minion.ActivateTask(PowerType::POWER, *this);
        }
        else
        {
            Minion& target = recruitField[targetIdx];

            recruitField.Add(minion, fieldIdx);

            recruitField.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::SUMMON,
                                                    minion);
            });

            opponent.recruitField.ForEachAlive([&](MinionData& aliveMinion) {
                aliveMinion.value().ActivateTrigger(TriggerType::SUMMON,
                                                    minion);
            });

            minion.ActivateTask(PowerType::POWER, *this, target);
        }

        recruitField.ForEachAlive([&](MinionData& aliveMinion) {
            aliveMinion.value().ActivateTrigger(TriggerType::AFTER_PLAY_MINION,
                                                minion);
        });
    }
    else
    {
        // TODO: Cast spell
    }
}

void Player::SellMinion(std::size_t idx)
{
    const auto minion = recruitField.Remove(recruitField[idx]);
    returnMinionCallback(minion.GetPoolIndex());

    remainCoin += 1;
}

void Player::UpgradeTavern()
{
    if (currentTier == TIER_UPPER_LIMIT || remainCoin < coinToUpgradeTavern)
    {
        return;
    }

    remainCoin -= coinToUpgradeTavern;
    upgradeTavernCallback(*this);
}

void Player::RefreshTavern()
{
    if (remainCoin < NUM_COIN_REFRESH_TAVERN)
    {
        return;
    }

    clearTavernMinionsCallback(*this);
    remainCoin -= NUM_COIN_REFRESH_TAVERN;

    prepareTavernMinionsCallback(*this);
}

void Player::FreezeTavern()
{
    freezeTavern = !freezeTavern;
}

void Player::RearrangeMinion(std::size_t curIdx, std::size_t newIdx)
{
    if (curIdx == newIdx ||
        static_cast<int>(curIdx) >= recruitField.GetCount() ||
        static_cast<int>(newIdx) >= recruitField.GetCount())
    {
        return;
    }

    recruitField.Move(static_cast<int>(curIdx), static_cast<int>(newIdx));
}

void Player::CompleteRecruit() const
{
    completeRecruitCallback();
}

void Player::ProcessDefeat()
{
    processDefeatCallback(*this);
}
}  // namespace RosettaStone::Battlegrounds
