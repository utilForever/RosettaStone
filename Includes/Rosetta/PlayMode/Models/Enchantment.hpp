// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_ENCHANTMENT_HPP
#define ROSETTASTONE_PLAYMODE_ENCHANTMENT_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
class Player;

//!
//! \brief Enchantment class.
//!
//! This class inherits from Playable class.
//!
class Enchantment : public Playable
{
 public:
    //! Constructs enchantment with given \p _player, \p _card, \p tags,
    //! \p owner and \p target.
    //! \param _player The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param owner The owner of enchantment.
    //! \param target A target of enchantment.
    //! \param id The ID.
    Enchantment(Player* _player, Card* _card, std::map<GameTag, int> tags,
                Playable* owner, Entity* target, int id);

    //! Default destructor.
    ~Enchantment() = default;

    //! Deleted copy constructor.
    Enchantment(const Enchantment&) = delete;

    //! Deleted copy assignment operator.
    Enchantment& operator=(const Enchantment&) = delete;

    //! Deleted move constructor.
    Enchantment(Enchantment&&) noexcept = delete;

    //! Deleted move assignment operator.
    Enchantment& operator=(Enchantment&&) noexcept = delete;

    //! Creates and adds a new Enchantment to the given player's game.
    //! \param owner The owner of the enchantment.
    //! \param _card The card from which the enchantment must be derived.
    //! \param target The entity who is subjected to the enchantment.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    //! \return The resulting enchantment entity.
    static std::shared_ptr<Enchantment> GetInstance(Playable* owner,
                                                    Card* _card, Entity* target,
                                                    int num1 = 0, int num2 = 0);

    //! Returns the owner of enchantment.
    //! \return the owner of enchantment.
    Playable* GetOwner() const;

    //! Returns the target of enchantment.
    //! \return The target of enchantment.
    Entity* GetTarget() const;

    //! Returns the number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \return The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    int GetScriptTag1() const;

    //! Returns the number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    //! \return The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    int GetScriptTag2() const;

    //! Returns the flag that indicates whether it is one turn active.
    //! \return The flag that indicates whether it is one turn active.
    bool IsOneTurnActive() const;

    //! Returns the captured card.
    //! \return The captured card.
    Card* GetCapturedCard() const;

    //! Sets the captured card.
    //! \param _card The captured card to set.
    void SetCapturedCard(Card* _card);

    //! Removes enchantment.
    void Remove();

 private:
    Playable* m_owner = nullptr;
    Entity* m_target = nullptr;
    Card* m_capturedCard = nullptr;

    bool m_isOneTurnActive = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ENCHANTMENT_HPP
