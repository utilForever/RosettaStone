// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_FIELD_ZONE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_FIELD_ZONE_HPP

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <array>
#include <optional>

namespace RosettaStone::Battlegrounds
{
using MinionData = std::optional<Minion>;

//!
//! \brief FieldZone class.
//!
//! This class is where the action takes place, representing the board on which
//! each game is played out. Around the battlefield are various important UI
//! elements, such as each player's hand, deck and Mana Crystals, as well as the
//! two heroes themselves. Each battlefield features its own design and numerous
//! interactive elements, but play is in no way affected or determined by
//! battlefield selection. Battlefields are chosen at random and are independent
//! of the heroes chosen by players or used by the Innkeeper.
//!
class FieldZone
{
 public:
    //! Default constructor.
    FieldZone() = default;

    //! Default destructor.
    ~FieldZone() = default;

    //! Default copy constructor.
    FieldZone(const FieldZone& rhs) = default;

    //! Deleted move constructor.
    FieldZone(FieldZone&& rhs) noexcept = delete;

    //! Copy assignment operator.
    FieldZone& operator=(const FieldZone& rhs);

    //! Deleted Move assignment operator.
    FieldZone& operator=(FieldZone&& rhs) noexcept = delete;

    //! Operator overloading for operator[].
    //! \param zonePos The zone position of minion.
    //! \return The minion at \p zonePos.
    Minion& operator[](std::size_t zonePos);

    //! Operator overloading for operator[].
    //! \param zonePos The zone position of minion.
    //! \return The minion at \p zonePos.
    const Minion& operator[](std::size_t zonePos) const;

    //! Adds the specified minion into this zone, at the given position.
    //! \param minion The minion to add.
    //! \param zonePos The zone position.
    void Add(Minion& minion, int zonePos = -1);

    //! Removes the specified minion from this zone.
    //! \param minion The minion context to remove.
    //! \return The removed minion.
    const Minion Remove(Minion& minion);

    //! Repositions all minions by \p zonePos.
    //! \param zonePos The position of minion to add or remove.
    void Reposition(int zonePos = 0);

    //! Moves the specified minion to another position.
    //! \param curPos The current position of minion.
    //! \param newPos The new position of minion.
    void Move(int curPos, int newPos);

    //! Returns the number of minions in this zone.
    //! \return The number of minions in this zone.
    int GetCount() const;

    //! Returns a value indicating whether this zone is empty.
    //! \return true if this zone is empty, false otherwise.
    bool IsEmpty() const;

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const;

    //! Returns all minions in this zone.
    //! \return All minions in this zone.
    std::vector<std::reference_wrapper<Minion>> GetAll();

    //! Runs \p functor on each minion.
    //! \param functor A function to run for each minion.
    template <typename Functor>
    void ForEach(Functor&& functor)
    {
        for (auto& minion : m_minions)
        {
            if (minion.has_value())
            {
                functor(minion);
            }
        }
    }

    //! Runs \p functor on each minion.
    //! \param functor A function to run for each minion.
    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        for (const auto& minion : m_minions)
        {
            if (minion.has_value())
            {
                functor(minion);
            }
        }
    }

    //! Runs \p functor on each minion that is alive.
    //! \param functor A function to run for each minion.
    template <typename Functor>
    void ForEachAlive(Functor&& functor)
    {
        for (auto& minion : m_minions)
        {
            if (minion.has_value() && !minion.value().IsDestroyed())
            {
                functor(minion);
            }
        }
    }

    //! Runs \p functor on each minion that is alive.
    //! \param functor A function to run for each minion.
    template <typename Functor>
    void ForEachAlive(Functor&& functor) const
    {
        for (const auto& minion : m_minions)
        {
            if (minion.has_value() && !minion.value().IsDestroyed())
            {
                functor(minion);
            }
        }
    }

 private:
    const ZoneType m_type = ZoneType::PLAY;

    std::array<MinionData, MAX_FIELD_SIZE> m_minions;
    int m_count = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_FIELD_ZONE_HPP
