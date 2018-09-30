#ifndef HEARTHSTONEPP_PLAYER_H
#define HEARTHSTONEPP_PLAYER_H

#include <hspp/Cards/Deck.h>

#include <vector>

namespace Hearthstonepp
{
//!
//! \brief Account class.
//!
//! This class stores user information such as e-mail address and nickname.
//! Also, it stores a list of decks. A user can construct several decks.
//!
class Account
{
 public:
    //! Constructs anonymous account.
    Account();

    //! Constructs account with given \p email and \p nickname.
    //! \param email E-mail address of user.
    //! \param nickname Nickname of user.
    Account(std::string&& email, std::string&& nickname);

    //! Constructs account with given \p email and \p nickname
    //! and fill deck list with \p decks.
    //! \param email E-mail address of user.
    //! \param nickname Nickname of user.
    //! \param decks A list of decks.
    Account(std::string&& email, std::string&& nickname,
            std::vector<Deck*> decks);

    //! Returns e-mail address of user.
    //! \return E-mail address of user.
    std::string GetEmail() const;

    //! Returns nickname of user.
    //! \return Nickname of user.
    std::string GetNickname() const;

    //! Returns the number of decks.
    //! \return Number of decks.
    size_t GetNumOfDeck() const;

    //! Returns a pointer to deck at \p idx.
    //! \param idx Index of decks.
    //! \return A pointer to deck at \p idx.
    Deck* GetDeck(size_t idx) const;

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
    bool DeleteDeck(size_t idx);

 private:
    std::string m_email;
    std::string m_nickname;
    std::vector<Deck*> m_decks;
};
}  // namespace Hearthstonepp

#endif