// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/BoardRefView.hpp>
#include <Rosetta/PlayMode/Views/ReducedBoardView.hpp>

namespace RosettaStone::PlayMode
{
ReducedBoardView::ReducedBoardView(const BoardRefView& view)
    : m_turn(view.GetTurn()), m_side(view.GetSide())
{
    m_myHero.Fill(*view.GetHero(), view.IsHeroAttackable(m_side));
    m_myHeroPower.Fill(view.GetHeroPower(m_side));
    m_myWeapon.Invalidate();
    if (view.GetWeapon(m_side) != nullptr)
    {
        m_myWeapon.Fill(*view.GetWeapon(m_side));
    }
    m_myManaCrystal.Fill(
        view.GetRemainingMana(m_side), view.GetTotalMana(m_side),
        view.GetOverloadOwed(m_side), view.GetOverloadLocked(m_side));
    for (auto& minion : view.GetMinions(m_side))
    {
        ViewTypes::MyMinion myMinion;
        myMinion.Fill(*minion, minion->CanAttack());

        m_myMinions.emplace_back(myMinion);
    }
    for (auto& card : view.GetHandCards())
    {
        ViewTypes::MyHandCard myHandCard;
        myHandCard.Fill(*card);

        m_myHand.emplace_back(myHandCard);
    }
    m_myDeck.Fill(view.GetDeckCardCount(m_side));

    const PlayerType opSide =
        (m_side == PlayerType::PLAYER1 ? PlayerType::PLAYER2
                                       : PlayerType::PLAYER1);

    m_opHero.Fill(*view.GetOpponentHero());
    m_opHeroPower.Fill(view.GetHeroPower(opSide));
    m_opWeapon.Invalidate();
    if (view.GetWeapon(opSide) != nullptr)
    {
        m_opWeapon.Fill(*view.GetWeapon(opSide));
    }
    m_opManaCrystal.Fill(
        view.GetRemainingMana(opSide), view.GetTotalMana(opSide),
        view.GetOverloadOwed(opSide), view.GetOverloadLocked(opSide));
    for (auto& minion : view.GetMinions(opSide))
    {
        ViewTypes::MyMinion opMinion;
        opMinion.Fill(*minion, minion->CanAttack());

        m_opMinions.emplace_back(opMinion);
    }
    for (std::size_t i = 0; i < view.GetOpponentHandCards().size(); ++i)
    {
        ViewTypes::OpHandCard opHandCard;
        m_opHand.emplace_back(opHandCard);
    }
    m_opDeck.Fill(view.GetDeckCardCount(opSide));
}

bool ReducedBoardView::operator==(const ReducedBoardView& rhs) const
{
    return (m_turn == rhs.m_turn) && (m_side == rhs.m_side) &&
           (m_myHero == rhs.m_myHero) && (m_myHeroPower == rhs.m_myHeroPower) &&
           (m_myWeapon == rhs.m_myWeapon) &&
           (m_myManaCrystal == rhs.m_myManaCrystal) &&
           (m_myMinions == rhs.m_myMinions) && (m_myHand == rhs.m_myHand) &&
           (m_myDeck == rhs.m_myDeck) && (m_opHero == rhs.m_opHero) &&
           (m_opHeroPower == rhs.m_opHeroPower) &&
           (m_opWeapon == rhs.m_opWeapon) &&
           (m_opManaCrystal == rhs.m_opManaCrystal) &&
           (m_opMinions == rhs.m_opMinions) && (m_opHand == rhs.m_opHand) &&
           (m_opDeck == rhs.m_opDeck);
}

bool ReducedBoardView::operator!=(const ReducedBoardView& rhs) const
{
    return !(*this == rhs);
}

int ReducedBoardView::GetTurn() const
{
    return m_turn;
}

PlayerType ReducedBoardView::GetSide() const
{
    return m_side;
}

const ViewTypes::MyHero& ReducedBoardView::GetMyHero() const
{
    return m_myHero;
}

const ViewTypes::HeroPower& ReducedBoardView::GetMyHeroPower() const
{
    return m_myHeroPower;
}

const ViewTypes::Weapon& ReducedBoardView::GetMyWeapon() const
{
    return m_myWeapon;
}

const ViewTypes::ManaCrystal& ReducedBoardView::GetMyManaCrystal() const
{
    return m_myManaCrystal;
}

const ViewTypes::MyMinions& ReducedBoardView::GetMyMinions() const
{
    return m_myMinions;
}

const ViewTypes::MyHand& ReducedBoardView::GetMyHand() const
{
    return m_myHand;
}

const ViewTypes::Deck& ReducedBoardView::GetMyDeck() const
{
    return m_myDeck;
}

const ViewTypes::Hero& ReducedBoardView::GetOpHero() const
{
    return m_opHero;
}

const ViewTypes::HeroPower& ReducedBoardView::GetOpHeroPower() const
{
    return m_opHeroPower;
}

const ViewTypes::Weapon& ReducedBoardView::GetOpWeapon() const
{
    return m_opWeapon;
}

const ViewTypes::ManaCrystal& ReducedBoardView::GetOpManaCrystal() const
{
    return m_opManaCrystal;
}

const ViewTypes::Minions& ReducedBoardView::GetOpMinions() const
{
    return m_opMinions;
}

const ViewTypes::OpHand& ReducedBoardView::GetOpHand() const
{
    return m_opHand;
}

const ViewTypes::Deck& ReducedBoardView::GetOpDeck() const
{
    return m_opDeck;
}
}  // namespace RosettaStone::PlayMode