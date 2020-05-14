// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_ACCOUNT_INFO_HPP
#define ROSETTASTONE_PLAYMODE_ACCOUNT_INFO_HPP

#include <Rosetta/PlayMode/Accounts/DeckInfo.hpp>

#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief AccountInfo class.
//!
//! This class stores account information such as e-mail address and nickname.
//! Also, it stores a list of decks. An account can make several decks.
//! This information imports/exports from/to json file.
//!
class AccountInfo
{
 public:
    //! Constructs anonymous account.
    AccountInfo();

    //! Constructs account with given \p email and \p nickname.
    //! \param email E-mail address of account.
    //! \param nickname Nickname of account.
    AccountInfo(std::string&& email, std::string&& nickname);

    //! Constructs account with given \p email and \p nickname
    //! and fill deck list with \p decks.
    //! \param email E-mail address of account.
    //! \param nickname Nickname of account.
    //! \param decks A list of decks.
    AccountInfo(std::string&& email, std::string&& nickname,
                std::vector<DeckInfo*> decks);

    //! Returns e-mail address of account.
    //! \return E-mail address of account.
    std::string GetEmail() const;

    //! Returns nickname of account.
    //! \return Nickname of account.
    std::string GetNickname() const;

    //! Returns the number of decks.
    //! \return Number of decks.
    std::size_t GetNumOfDeck() const;

    //! Returns a pointer to deck at \p idx.
    //! \param idx Index of decks.
    //! \return A pointer to deck at \p idx.
    DeckInfo* GetDeck(std::size_t idx) const;

    //! Prints a list of decks.
    void ShowDeckList() const;

    //! Creates a deck with given \p name and \p deckClass.
    //! \param name The name of deck.
    //! \param deckClass The class of deck.
    //! \return true if deck is created successfully, and false otherwise.
    bool CreateDeck(std::string name, CardClass deckClass);

    //! Deletes a deck at \p idx.
    //! \param idx Index of decks.
    //! \return true if deck is deleted successfully, and false otherwise.
    bool DeleteDeck(std::size_t idx);

 private:
    std::string m_email;
    std::string m_nickname;
    std::vector<DeckInfo*> m_decks;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACCOUNT_INFO_HPP