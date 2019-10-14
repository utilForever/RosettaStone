// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ZONE_HPP
#define ROSETTASTONE_ZONE_HPP

#include <Rosetta/Auras/Aura.hpp>
#include <Rosetta/Zones/IZone.hpp>

#include <algorithm>
#include <stdexcept>

namespace RosettaStone
{
//!
//! \brief Zone class.
//!
//! This class is base implementation of IZone.
//!
template <typename T>
class Zone : public IZone
{
 public:
    //! Default constructor.
    Zone() = default;

    //! Default virtual destructor.
    virtual ~Zone() = default;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity to add.
    //! \param zonePos The zone position of entity.
    void Add(Entity& entity, int zonePos = -1) override = 0;

    //! Removes the specified entity from this zone.
    //! \param entity The entity to remove.
    //! \return The removed entity.
    Entity& Remove(Entity& entity) override = 0;

    //! Moves the specified entity to a new position.
    //! \param entity The entity to move.
    //! \param zonePos The zone position of entity.
    virtual void MoveTo(T& entity, int zonePos = -1) = 0;

    //! Returns the number of entities in this zone.
    //! \return The number of entities in this zone.
    virtual int GetCount() const = 0;

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const override = 0;

    //! Returns a value indicating whether this zone is empty.
    //! \return true if this zone is empty, false otherwise.
    bool IsEmpty() const
    {
        return GetCount() == 0;
    }

 protected:
    Player* m_owner = nullptr;
};  // namespace RosettaStone

//!
//! \brief UnlimitedZone class.
//!
//! This class is base implementation of GraveyardZone and SetasideZone.
//!
class UnlimitedZone : public Zone<Entity>
{
 public:
    //! Default constructor.
    UnlimitedZone() = default;

    //! Destructor.
    ~UnlimitedZone()
    {
        for (auto& entity : m_entities)
        {
            delete entity;
        }

        m_entities.clear();
    }

    //! Deleted copy constructor.
    UnlimitedZone(const UnlimitedZone&) = delete;

    //! Deleted move constructor.
    UnlimitedZone(UnlimitedZone&&) noexcept = delete;

    //! Deleted copy assignment operator.
    UnlimitedZone& operator=(const UnlimitedZone&) = delete;

    //! Deleted move assignment operator.
    UnlimitedZone& operator=(UnlimitedZone&&) noexcept = delete;

    //! Operator overloading for operator[].
    //! \param zonePos The zone position of entity.
    //! \return The entity at \p zonePos.
    Entity* operator[](int zonePos)
    {
        return m_entities[zonePos];
    }

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity to add.
    //! \param zonePos The zone position of entity.
    void Add(Entity& entity, int zonePos = -1) override
    {
        if (entity.owner != m_owner)
        {
            throw std::logic_error(
                "Can't add an opponent's entity to own zones");
        }

        MoveTo(entity, zonePos);
    }

    //! Removes the specified entity from this zone.
    //! \param entity The entity to remove.
    //! \return The removed entity.
    Entity& Remove(Entity& entity) override
    {
        if (entity.zone == nullptr || entity.zone->GetType() != m_type)
        {
            throw std::logic_error("Couldn't remove entity from zone.");
        }

        m_entities.erase(
            std::remove(m_entities.begin(), m_entities.end(), &entity),
            m_entities.end());

        return entity;
    }

    //! Moves the specified entity to a new position.
    //! \param entity The entity to move.
    //! \param zonePos The zone position of entity.
    void MoveTo(Entity& entity, [[maybe_unused]] int zonePos) override
    {
        m_entities.emplace_back(&entity);
        entity.zone = this;
        entity.SetZoneType(m_type);
    }

    //! Returns the number of entities in this zone.
    //! \return The number of entities in this zone.
    int GetCount() const override
    {
        return m_entities.size();
    }

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const override
    {
        return false;
    }

    //! Runs \p functor on each entity of the zone.
    //! \param functor A function to run for each entity.
    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        for (auto& entity : m_entities)
        {
            functor(entity);
        }
    }

 protected:
    std::vector<Entity*> m_entities;
};

//!
//! \brief LimitedZone class.
//!
//! This class is base implementation of zones which have a maximum size.
//!
template <typename T>
class LimitedZone : public Zone<T>
{
 public:
    //! Constructs limited zone with given \p size.
    //! \param size The maximum size of limited zone.
    explicit LimitedZone(int size) : m_maxSize(size)
    {
        m_entities = new T*[m_maxSize];

        for (int i = 0; i < m_maxSize; ++i)
        {
            m_entities[i] = nullptr;
        }
    }

    //! Destructor.
    ~LimitedZone()
    {
        for (int i = 0; i < m_count; ++i)
        {
            delete m_entities[i];
        }

        delete[] m_entities;
    }

    //! Deleted copy constructor.
    LimitedZone(const LimitedZone&) = delete;

    //! Deleted move constructor.
    LimitedZone(LimitedZone&&) noexcept = delete;

    //! Deleted copy assignment operator.
    LimitedZone& operator=(const LimitedZone&) = delete;

    //! Deleted move assignment operator.
    LimitedZone& operator=(LimitedZone&&) noexcept = delete;

    //! Operator overloading for operator[].
    //! \param zonePos The zone position of entity.
    //! \return The entity at \p zonePos.
    T* operator[](int zonePos)
    {
        return m_entities[zonePos];
    }

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity to add.
    //! \param zonePos The zone position of entity.
    void Add(Entity& entity, int zonePos = -1) override
    {
        if (zonePos > m_count)
        {
            throw std::logic_error("Zone position isn't in a valid range.");
        }

        if (entity.owner != Zone<T>::m_owner)
        {
            throw std::logic_error(
                "Can't add an opponent's entity to own zones");
        }

        MoveTo(static_cast<T&>(entity), zonePos < 0 ? m_count : zonePos);
    }

    //! Removes the specified entity from this zone.
    //! \param entity The entity to remove.
    //! \return The removed entity.
    Entity& Remove(Entity& entity) override
    {
        if (entity.zone != this)
        {
            throw std::logic_error("Couldn't remove entity from zone.");
        }

        int pos;
        for (pos = m_count - 1; pos >= 0; --pos)
        {
            if (&entity == dynamic_cast<Entity*>(m_entities[pos]))
            {
                break;
            }
        }

        if (pos < --m_count)
        {
            for (int i = pos + 1; i < m_maxSize; ++i)
            {
                m_entities[i - 1] = m_entities[i];
            }

            m_entities[m_maxSize - 1] = nullptr;
        }

        entity.zone = nullptr;

        if (entity.activatedTrigger != nullptr)
        {
            entity.activatedTrigger->Remove();
        }

        return entity;
    }

    //! Moves the specified entity to a new position.
    //! \param entity The entity to move.
    //! \param zonePos The zone position of entity.
    void MoveTo(T& entity, int zonePos = -1) override
    {
        if (IsFull())
        {
            return;
        }

        if (zonePos < 0 || zonePos == m_count)
        {
            m_entities[m_count] = &entity;
        }
        else
        {
            for (int i = m_count - 1; i >= zonePos; --i)
            {
                m_entities[i + 1] = m_entities[i];
            }

            m_entities[zonePos] = &entity;
        }

        ++m_count;

        dynamic_cast<Entity&>(entity).zone = this;
        dynamic_cast<Entity&>(entity).SetZoneType(Zone<T>::m_type);
    }

    //! Returns the number of entities in this zone.
    //! \return The number of entities in this zone.
    int GetCount() const override
    {
        return m_count;
    }

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const override
    {
        return m_count == m_maxSize;
    }

    //! Returns all entities in this zone (non-const).
    //! \return All entities in this zone.
    virtual std::vector<T*> GetAll()
    {
        std::vector<T*> result;
        result.reserve(m_count);

        for (int i = 0; i < m_count; ++i)
        {
            if (m_entities[i] == nullptr ||
                static_cast<bool>(m_entities[i]->isDestroyed))
            {
                continue;
            }

            result.emplace_back(m_entities[i]);
        }

        return result;
    }

    //! Returns all entities in this zone (const).
    //! \return All entities in this zone.
    virtual std::vector<T*> GetAll() const
    {
        std::vector<T*> result;
        result.reserve(m_count);

        for (int i = 0; i < m_count; ++i)
        {
            if (m_entities[i] == nullptr ||
                static_cast<bool>(m_entities[i]->isDestroyed))
            {
                continue;
            }

            result.emplace_back(m_entities[i]);
        }

        return result;
    }

    //! Runs \p functor on each entity of the zone.
    //! \param functor A function to run for each entity.
    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        for (int i = 0; i < m_count; ++i)
        {
            functor(m_entities[i]);
        }
    }

 protected:
    T** m_entities;

    int m_count = 0;
    int m_maxSize = 0;
};

//!
//! \brief PositioningZone class.
//!
//! This class is base implementation of zones performing strict recalculation
//! of its containing entities' ZonePosition when any member comes and goes.
//!
template <typename T>
class PositioningZone : public LimitedZone<T>
{
 public:
    explicit PositioningZone(int size) : LimitedZone<T>(size)
    {
        // Do nothing
    }

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity to add.
    //! \param zonePos The zone position of entity.
    void Add(Entity& entity, int zonePos = -1) override
    {
        LimitedZone<T>::Add(entity, zonePos);

        Reposition(zonePos);
    }

    //! Removes the specified entity from this zone.
    //! \param entity The entity to remove.
    //! \return The removed entity.
    Entity& Remove(Entity& entity) override
    {
        if (entity.zone != this)
        {
            throw std::logic_error("Couldn't remove entity from zone.");
        }

        const int pos = entity.GetZonePosition();
        int count = LimitedZone<T>::m_count;

        if (pos < --count)
        {
            for (int i = pos + 1; i < LimitedZone<T>::m_maxSize; ++i)
            {
                LimitedZone<T>::m_entities[i - 1] =
                    LimitedZone<T>::m_entities[i];
            }

            LimitedZone<T>::m_entities[LimitedZone<T>::m_maxSize - 1] = nullptr;
        }

        LimitedZone<T>::m_count = count;

        Reposition(pos);

        entity.zone = nullptr;

        if (entity.activatedTrigger != nullptr)
        {
            entity.activatedTrigger->Remove();
        }

        for (std::size_t i = 0; i < auras.size(); ++i)
        {
            auras[i]->RemoveEntity(&entity);
        }

        return entity;
    }

    //! Swaps the positions of both entities in this zone.
    //! Both entities must be contained by this zone.
    //! \param oldEntity The one entity.
    //! \param newEntity The other entity.
    void Swap(T& oldEntity, T& newEntity)
    {
        if (oldEntity.zone->GetType() != newEntity.zone->GetType())
        {
            throw std::logic_error(
                "Swap not possible because of zone mismatch");
        }

        int oldPos = oldEntity.GetZonePosition();
        int newPos = newEntity.GetZonePosition();
        newEntity.SetZonePosition(oldPos);
        oldEntity.SetZonePosition(newPos);
        LimitedZone<T>::m_entities[newPos] = &oldEntity;
        LimitedZone<T>::m_entities[oldPos] = &newEntity;
    }

    std::vector<Aura*> auras;

 private:
    //! Repositions all entities by \p zonePos.
    //! \param zonePos The position of entity to add or remove.
    void Reposition(int zonePos = 0)
    {
        if (zonePos < 0)
        {
            dynamic_cast<Entity*>(
                LimitedZone<T>::m_entities[LimitedZone<T>::m_count - 1])
                ->SetZonePosition(LimitedZone<T>::m_count - 1);
            return;
        }

        for (int i = LimitedZone<T>::m_count - 1; i >= zonePos; --i)
        {
            dynamic_cast<Entity*>(LimitedZone<T>::m_entities[i])
                ->SetZonePosition(i);
        }

        for (std::size_t i = 0; i < auras.size(); ++i)
        {
            auras[i]->SetToBeUpdated(true);
        }
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ZONE_HPP
