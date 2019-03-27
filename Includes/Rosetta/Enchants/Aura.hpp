// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AURA_HPP
#define ROSETTASTONE_AURA_HPP

#include <string>

namespace RosettaStone
{
//! Aura types. Indicates the range of auras.
enum class AuraType
{
    INVALID,             //!< Invalid type.
    FIELD_EXCEPT_SOURCE  //!< This type of aura affects all friendly minions
                         //!< except the source of the aura.
};

//!
//! \brief Aura class.
//!
//! This class represent aura. Auras can affect entities and change the applied
//! entities attack, cost and so on. Aura must be activated first to affect
//! entities.
//!
class Aura
{
 public:
    //! Default constructor.
    Aura() = default;

    //! Constructs enchant with given \p enchantmentID and \p type.
    //! \param enchantmentID The enchantment card ID.
    //! \param type The type of aura.
    Aura(std::string&& enchantmentID, AuraType type);

 private:
    std::string m_enchantmentID;
    AuraType m_type = AuraType::INVALID;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_HPP
