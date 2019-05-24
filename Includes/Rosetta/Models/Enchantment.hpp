// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ENCHANTMENT_HPP
#define ROSETTASTONE_ENCHANTMENT_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
{
class Player;

//!
//! \brief Enchantment class.
//!
//! This class inherits from Entity structure.
//!
class Enchantment : public Entity
{
 public:
    //! Default constructor.
    Enchantment() = default;

    //! Constructs enchantment with given \p _owner, \p _card, \p tags and \p target.
    //! \param _owner The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param target A target of enchantment.
    Enchantment(Player& _owner, Card& _card, std::map<GameTag, int> tags,
                Entity* target);

    //! Default destructor.
    ~Enchantment() = default;

    //! Default copy constructor.
    Enchantment(const Enchantment& spell) = default;

    //! Default move constructor.
    Enchantment(Enchantment&& spell) = default;

    //! Default copy assignment operator.
    Enchantment& operator=(const Enchantment& spell) = default;

    //! Default move assignment operator.
    Enchantment& operator=(Enchantment&& spell) = default;

    //! Creates and adds a new Enchantment to the given player's game.
    //! \param player The controller of the enchantment.
    //! \param card The card from which the enchantment must be derived.
    //! \param target The entity who is subjected to the enchantment.
    //! \return The resulting enchantment entity.
    static Enchantment* GetInstance(Player& player, Card& card, Entity* target);

    //! Returns the target of enchantment.
    //! \return The target of enchantment.
    Entity* GetTarget() const;

    //! Removes enchantment.
    void Remove();

 private:
    Entity* m_target = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANTMENT_HPP
