// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_BATTLEFIELD_HPP
#define HEARTHSTONEPP_BATTLEFIELD_HPP

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Character.hpp>
#include <hspp/Models/Minion.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief Battlefield class.
//!
//! This class is where the action takes place, representing the board on which
//! each game is played out. Around the battlefield are various important UI
//! elements, such as each player's hand, deck and Mana Crystals, as well as the
//! two heroes themselves. Each battlefield features its own design and numerous
//! interactive elements, but play is in no way affected or determined by
//! battlefield selection. Battlefields are chosen at random and are independent
//! of the heroes chosen by players or used by the Innkeeper.
//!
class Battlefield
{
 public:
    //! Default constructor.
    Battlefield();

    //! Returns the owner of battlefield.
    //! \return The owner of battlefield.
    Player& GetOwner() const;

    //! Sets the owner of battlefield.
    //! \param owner The owner of battlefield.
    void SetOwner(Player& owner);

    //! Returns the number of minions in battlefield.
    //! \return The number of minions in battlefield.
    std::size_t GetNumOfMinions() const;

    //! Returns minion in battlefield.
    //! \param pos The position of minion in battlefield.
    //! \return A minion in battlefield at \p pos.
    Character* GetMinion(std::size_t pos);

    //! Returns all minions in battlefield.
    //! \return A list of minions in battlefield.
    std::vector<Character*> GetAllMinions();

    //! Returns the position of minion in battlefield.
    //! \return The position of minion in battlefield.
    optional<std::size_t> FindMinionPos(Minion& minion);

    //! Returns The empty position in battlefield.
    //! \return The empty position in battlefield.
    optional<std::size_t> FindEmptyPos() const;

    //! Adds minion to battlefield.
    //! \param minion The minion to add to battlefield.
    //! \param pos The position of minion in battlefield.
    void AddMinion(Minion& minion, std::size_t pos);

    //! Removes minion from battlefield.
    //! \param minion The minion to remove from battlefield.
    void RemoveMinion(Minion& minion);

 private:
    Player* m_owner = nullptr;

    std::array<Character*, FIELD_SIZE> m_minions{};
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_BATTLEFIELD_HPP