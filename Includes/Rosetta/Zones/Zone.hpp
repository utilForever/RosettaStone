// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ZONE_HPP
#define ROSETTASTONE_ZONE_HPP

#include <Rosetta/Enchants/Aura.hpp>
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

    //! Constructor with given \p size.
    //! \param size The size of container that stores entities.
    Zone(int size) : m_entities(size)
    {
        // Do nothing
    }

    //! Operator overloading for operator[].
    T* operator[](int zonePos)
    {
        return m_entities[zonePos];
    }

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Entity& entity, int zonePos = -1) override = 0;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    Entity& Remove(Entity& entity) override = 0;

    //! Moves the specified entity to a new position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    virtual void MoveTo(T& entity, int zonePos = -1) = 0;

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

        int oldPos = oldEntity.zonePos;
        int newPos = newEntity.zonePos;
        newEntity.zonePos = oldPos;
        oldEntity.zonePos = newPos;
        m_entities[newPos] = &oldEntity;
        m_entities[oldPos] = &newEntity;
    }

    //! Returns the number of entities in this zone.
    //! \return The number of entities in this zone.
    virtual int GetCount() const = 0;

    //! Returns a value indicating whether this zone is empty.
    //! \return true if this zone is empty, false otherwise.
    bool IsEmpty() const
    {
        return GetCount() == 0;
    }

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    virtual bool IsFull() const = 0;

 protected:
    std::vector<T*> m_entities;
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
    void Add(Entity& entity, int zonePos = -1) override
    {
        if (entity.owner != m_owner)
        {
            throw std::logic_error(
                "Can't add an opponent's entity to own zones");
        }

        MoveTo(entity, zonePos);
    }

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

    void MoveTo(Entity& entity, int) override
    {
        m_entities.emplace_back(&entity);
        entity.zone = this;
        entity.SetZoneType(m_type);
    }

    int GetCount() const override
    {
        return m_entities.size();
    }

    bool IsFull() const override
    {
        return false;
    }
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
    LimitedZone(int size) : Zone(size), m_maxSize(size)
    {
        // Do nothing
    }

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

        MoveTo((T&)(entity), zonePos < 0 ? m_count : zonePos);
    }

    Entity& Remove(Entity& entity) override
    {
        if (entity.zone == nullptr || entity.zone->GetType() != Zone<T>::m_type)
        {
            throw std::logic_error("Couldn't remove entity from zone.");
        }

        int pos;
        for (pos = m_count - 1; pos >= 0; --pos)
        {
            if (&entity == dynamic_cast<Entity*>(Zone<T>::m_entities[pos]))
            {
                break;
            }
        }

        --m_count;

        if (pos < m_count)
        {
            std::copy(Zone<T>::m_entities.begin() + pos + 1,
                      Zone<T>::m_entities.end(),
                      Zone<T>::m_entities.begin() + pos);
        }

        Zone<T>::m_entities[m_count] = nullptr;
        entity.zone = nullptr;

        if (entity.activatedTrigger != nullptr)
        {
            entity.activatedTrigger->Remove();
        }

        return entity;
    }

    void MoveTo(T& entity, int zonePos = -1) override
    {
        if (IsFull())
        {
            return;
        }

        if (zonePos < 0)
        {
            zonePos = m_count;
        }

        if (zonePos == m_count)
        {
            Zone<T>::m_entities[zonePos] = &entity;
        }
        else
        {
            for (int i = m_count - 1; i >= zonePos; --i)
            {
                Zone<T>::m_entities[i + 1] = Zone<T>::m_entities[i];
            }

            Zone<T>::m_entities[zonePos] = &entity;
        }

        ++m_count;

        dynamic_cast<Entity&>(entity).zone = this;
        dynamic_cast<Entity&>(entity).SetZoneType(Zone<T>::m_type);
    }

    int GetCount() const override
    {
        return m_count;
    }

    bool IsFull() const override
    {
        return m_count == m_maxSize;
    }

    virtual std::vector<T*> GetAll()
    {
        std::vector<T*> result;
        result.reserve(m_count);

        for (int i = 0; i < m_count; ++i)
        {
            if (Zone<T>::m_entities[i] == nullptr)
            {
                continue;
            }

            result.emplace_back(Zone<T>::m_entities[i]);
        }

        return result;
    }

 protected:
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
    PositioningZone(int size) : LimitedZone<T>(size)
    {
        // Do nothing
    }

    void Add(Entity& entity, int zonePos = -1) override
    {
        LimitedZone<T>::Add(entity, zonePos);

        Reposition(zonePos);
    }

    Entity& Remove(Entity& entity) override
    {
        if (entity.zone == nullptr ||
            entity.zone->GetType() != LimitedZone<T>::m_type)
        {
            throw std::logic_error("Couldn't remove entity from zone.");
        }

        int pos;
        for (pos = LimitedZone<T>::m_count - 1; pos >= 0; --pos)
        {
            if (&entity == dynamic_cast<Entity*>(Zone<T>::m_entities[pos]))
            {
                break;
            }
        }

        --LimitedZone<T>::m_count;

        if (pos < LimitedZone<T>::m_count)
        {
            std::copy(LimitedZone<T>::m_entities.begin() + pos + 1,
                      LimitedZone<T>::m_entities.end(),
                      LimitedZone<T>::m_entities.begin() + pos);
        }

        Reposition(pos);

        Zone<T>::m_entities[LimitedZone<T>::m_count] = nullptr;
        entity.zone = nullptr;

        if (entity.activatedTrigger != nullptr)
        {
            entity.activatedTrigger->Remove();
        }

        for (std::size_t i = 0; i < auras.size(); ++i)
        {
            auras[i]->RemoveEntity(entity);
        }

        return entity;
    }

    std::vector<Aura*> auras;

 private:
    void Reposition(int zonePos = 0)
    {
        if (zonePos < 0)
        {
            zonePos = LimitedZone<T>::m_count - 1;
        }

        for (int i = LimitedZone<T>::m_count - 1; i >= zonePos; --i)
        {
            dynamic_cast<Entity*>(LimitedZone<T>::m_entities[i])->zonePos = i;
        }

        for (std::size_t i = 0; i < auras.size(); ++i)
        {
            auras[i]->SetToBeUpdated(true);
        }
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ZONE_HPP
