// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Views/BoardRefView.hpp>
#include <Rosetta/Views/ReducedBoardView.hpp>

namespace RosettaStone
{
ReducedBoardView::ReducedBoardView(const BoardRefView& board)
    : m_turn(board.GetTurn()), m_playerType(board.GetPlayerType())
{
    m_myHero.Fill(*board.GetHero(), board.IsHeroAttackable(m_playerType));
    m_myHeroPower.Fill(*board.GetHeroPower(m_playerType));
    m_myWeapon.Invalidate();
    m_myWeapon.Fill(*board.GetWeapon(m_playerType));
    m_myManaCrystal.Fill(board.GetCurrentPlayer());
    for (auto& minion : board.GetMinions(m_playerType))
    {
        ViewTypes::MyMinion myMinion;
        myMinion.Fill(*minion, minion->CanAttack());

        m_myMinions.emplace_back(myMinion);
    }
    for (auto& card : board.GetHandCards())
    {
        ViewTypes::MyHandCard myHandCard;
        myHandCard.Fill(*card);

        m_myHand.emplace_back(myHandCard);
    }
    m_myDeck.Fill(board.GetDeckCardCount(m_playerType));

    m_opHero.Fill(*board.GetOpponentHero());
    m_opHeroPower.Fill(*board.GetHeroPower(m_playerType));
    m_opWeapon.Invalidate();
    m_opWeapon.Fill(*board.GetWeapon(m_playerType));
    m_opManaCrystal.Fill(*board.GetCurrentPlayer().opponent);
    for (auto& minion : board.GetMinions(m_playerType))
    {
        ViewTypes::MyMinion opMinion;
        opMinion.Fill(*minion, minion->CanAttack());

        m_opMinions.emplace_back(opMinion);
    }
    for (size_t i = 0; i < board.GetHandCards().size(); ++i)
    {
        ViewTypes::OpHandCard opHandCard;
        m_opHand.emplace_back(opHandCard);
    }
    m_opDeck.Fill(board.GetDeckCardCount(m_playerType));
}

bool ReducedBoardView::operator==(const ReducedBoardView& rhs) const
{
    static_assert(changeID == 3);

    if (m_turn != rhs.m_turn)
    {
        return false;
    }
    if (m_playerType != rhs.m_playerType)
    {
        return false;
    }

    if (m_myHero != rhs.m_myHero)
    {
        return false;
    }
    if (m_myHeroPower != rhs.m_myHeroPower)
    {
        return false;
    }
    if (m_myWeapon != rhs.m_myWeapon)
    {
        return false;
    }
    if (m_myManaCrystal != rhs.m_myManaCrystal)
    {
        return false;
    }
    if (m_myMinions != rhs.m_myMinions)
    {
        return false;
    }
    if (m_myHand != rhs.m_myHand)
    {
        return false;
    }
    if (m_myDeck != rhs.m_myDeck)
    {
        return false;
    }

    if (m_opHero != rhs.m_opHero)
    {
        return false;
    }
    if (m_opHeroPower != rhs.m_opHeroPower)
    {
        return false;
    }
    if (m_opWeapon != rhs.m_opWeapon)
    {
        return false;
    }
    if (m_opManaCrystal != rhs.m_opManaCrystal)
    {
        return false;
    }
    if (m_opMinions != rhs.m_opMinions)
    {
        return false;
    }
    if (m_opHand != rhs.m_opHand)
    {
        return false;
    }
    if (m_opDeck != rhs.m_opDeck)
    {
        return false;
    }

    return true;
}

bool ReducedBoardView::operator!=(const ReducedBoardView& rhs) const
{
    return !(*this == rhs);
}

int ReducedBoardView::GetTurn() const
{
    return m_turn;
}

PlayerType ReducedBoardView::GetPlayerType() const
{
    return m_playerType;
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
}  // namespace RosettaStone

namespace std
{
using namespace RosettaStone;

template <>
struct hash<ReducedBoardView>
{
    std::size_t operator()(const ReducedBoardView& rhs) const noexcept
    {
        static_assert(ReducedBoardView::changeID == 3);

        std::size_t result = 0;
        CombineHash(result, rhs.m_turn);
        CombineHash(result, static_cast<int>(rhs.m_playerType));

        CombineHash(result, rhs.m_myHero);
        CombineHash(result, rhs.m_myHeroPower);
        CombineHash(result, rhs.m_myWeapon);
        CombineHash(result, rhs.m_myManaCrystal);
        CombineHash(result, rhs.m_myMinions);
        CombineHash(result, rhs.m_myHand);
        CombineHash(result, rhs.m_myDeck);

        CombineHash(result, rhs.m_opHero);
        CombineHash(result, rhs.m_opHeroPower);
        CombineHash(result, rhs.m_opWeapon);
        CombineHash(result, rhs.m_opManaCrystal);
        CombineHash(result, rhs.m_opMinions);
        CombineHash(result, rhs.m_opHand);
        CombineHash(result, rhs.m_opDeck);

        return result;
    }
};
}  // namespace std