// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP
#define ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP

#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>

#include <vector>

namespace RosettaStone::Battlegrounds
{
class Minion;

//!
//! \brief Enchant class.
//!
//! This class stores an enchantment, also known as a buff or debuff. It is a
//! special effect gained by a minion, or in rarer occasions by a weapon.
//!
class Enchant
{
 public:
    //! Constructs enchant with given \p effect and \p useScriptTag.
    //! \param effect The effect of the card.
    //! \param useScriptTag A flag to use script tag.
    explicit Enchant(Effect effect, bool useScriptTag = false);

    //! Constructs enchant with given \p effects and \p useScriptTag.
    //! \param effects A list of effect.
    //! \param useScriptTag A flag to use script tag.
    explicit Enchant(std::vector<Effect> effects, bool useScriptTag = false);

    //! Activates enchant to \p minion.
    //! \param minion A minion to which enchant is activated.
    //! \param num The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    void ActivateTo(Minion& minion, int num = 0);

 private:
    std::vector<Effect> m_effects;
    bool m_useScriptTag = false;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP
