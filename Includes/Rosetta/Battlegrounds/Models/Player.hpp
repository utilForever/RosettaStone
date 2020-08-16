// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP

#include <Rosetta/Battlegrounds/Models/Hero.hpp>
#include <Rosetta/Battlegrounds/Models/Tavern.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskStack.hpp>
#include <Rosetta/Battlegrounds/Zones/FieldZone.hpp>
#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>

#include <array>
#include <functional>
#include <limits>

namespace RosettaStone::Battlegrounds
{
class Battle;

//!
//! \brief Player class.
//!
//! This class stores various information that used in Battlegrounds.
//!
class Player
{
 public:
    //! Returns the field according the status.
    //! \return The field according the status.
    FieldZone& GetField();

    //! Initializes a Hero instance.
    //! \param idx The index of hero choices.
    void SelectHero(std::size_t idx);

    //! Prepare a list of minions in Tavern for purchase.
    void PrepareTavern();

    //! Purchases a minion from Tavern's field.
    //! \param idx The index of a list of minions in Tavern's field.
    void PurchaseMinion(std::size_t idx);

    //! Plays a minion or spell card.
    //! \param handIdx The index of a list of cards in player's hand.
    //! \param fieldIdx The index of player's field to add.
    //! \param targetIdx The index of the target in player's field.
    void PlayCard(std::size_t handIdx, std::size_t fieldIdx,
                  int targetIdx = -1);

    //! Sells a minion to Tavern.
    //! \param idx The index of a list of minions in player's field.
    void SellMinion(std::size_t idx);

    //! Upgrades your Tavern to the next tier.
    void UpgradeTavern();

    //! Refreshes a list of minions in Tavern's field.
    void RefreshTavern();

    //! Freezes a list of minions in Tavern's field.
    void FreezeTavern();

    //! Rearranges a minion to another position on player's field.
    //! \param curIdx The current index of minion.
    //! \param newIdx The new index of minion.
    void RearrangeMinion(std::size_t curIdx, std::size_t newIdx);

    //! Completes recruit phase.
    void CompleteRecruit() const;

    //! Processes the tasks related to defeat.
    void ProcessDefeat();

    PlayState playState = PlayState::INVALID;
    std::size_t idx = 0;
    std::size_t rank = 1;

    Hero hero;

    int remainCoin = 0;
    int totalCoin = 0;
    int currentTier = 0;
    int coinToUpgradeTavern = 0;

    Tavern tavern;
    HandZone hand;
    FieldZone recruitField;
    FieldZone battleField;

    TaskStack taskStack;

    std::function<void(Player&)> selectHeroCallback;
    std::function<void(Player&)> prepareTavernMinionsCallback;
    std::function<void(Player&, std::size_t)> purchaseMinionCallback;
    std::function<int()> getNextCardIndexCallback;
    std::function<void(int)> returnMinionCallback;
    std::function<void(Player&)> clearTavernMinionsCallback;
    std::function<void(Player&)> upgradeTavernCallback;
    std::function<void()> completeRecruitCallback;
    std::function<Player&(Player&)> getOpponentPlayerCallback;
    std::function<Battle&()> getBattleCallback;
    std::function<void(Player&)> processDefeatCallback;

    std::array<int, 4> heroChoices{ 0, 0, 0, 0 };

    std::size_t playerIdxNextFight = std::numeric_limits<std::size_t>::max();
    std::size_t playerIdxFoughtLastTurn =
        std::numeric_limits<std::size_t>::max();

    bool isInCombat = false;
    bool isFoughtGhostLastTurn = false;
    bool freezeTavern = false;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
