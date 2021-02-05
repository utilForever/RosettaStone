// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
#define ROSETTASTONE_PLAYMODE_CARD_DEF_HPP

#include <Rosetta/PlayMode/Enchants/Power.hpp>

#include <map>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief CardDef class.
//!
//! This class stores the card data such as powers and play requirements.
//!
class CardDef
{
 public:
    //! Default constructor.
    CardDef() = default;

    //! Constructs card def with given \p _power.
    //! \param _power The power data.
    explicit CardDef(Power _power);

    //! Constructs card def with given \p _power and \p _playReqs.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    explicit CardDef(Power _power, std::map<PlayReq, int> _playReqs);

    //! Constructs card def with given \p _power and \p _chooseCardIDs.
    //! \param _power The power data.
    //! \param _chooseCardIDs The choose card IDs data.
    explicit CardDef(Power _power, std::vector<std::string> _chooseCardIDs);

    //! Constructs card def with given \p _power and \p _corruptCardID.
    //! \param _power The power data.
    //! \param _corruptCardID The card ID to change when 'Corrupt' is activated.
    explicit CardDef(Power _power, std::string _corruptCardID);

    //! Constructs card def with given \p _power, \p _questProgressTotal
    //! and \p _heroPowerDbfID.
    //! \param _power The power data.
    //! \param _questProgressTotal The quest progress total data.
    //! \param _heroPowerDbfID The hero power defID data.
    explicit CardDef(Power _power, int _questProgressTotal,
                     int _heroPowerDbfID);

    //! Constructs card def with given \p _power, \p _playReqs and
    //! \p _chooseCardIDs.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    //! \param _chooseCardIDs The choose card IDs data.
    explicit CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                     std::vector<std::string> _chooseCardIDs);

    //! Constructs card def with given \p _power, \p _playReqs and
    //! \p _corruptCardID.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    //! \param _corruptCardID The card ID to change when 'Corrupt' is activated.
    explicit CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                     std::string _corruptCardID);

    //! Constructs card def with given \p _power, \p _chooseCardIDs and
    //! \p _corruptCardID.
    //! \param _power The power data.
    //! \param _chooseCardIDs The choose card IDs data.
    //! \param _corruptCardID The card ID to change when 'Corrupt' is activated.
    explicit CardDef(Power _power, std::vector<std::string> _chooseCardIDs,
                     std::string _corruptCardID);

    //! Constructs card def with given \p _power, \p _playReqs,
    //! \p _chooseCardIDs and \p _entourages.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    //! \param _chooseCardIDs The choose card IDs data.
    //! \param _entourages The entourages data.
    explicit CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                     std::vector<std::string> _chooseCardIDs,
                     std::vector<std::string> _entourages);

    Power power;
    std::map<PlayReq, int> playReqs;
    std::vector<std::string> chooseCardIDs;
    std::vector<std::string> entourages;
    std::string corruptCardID;
    int questProgressTotal = 0;
    int heroPowerDbfID = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
