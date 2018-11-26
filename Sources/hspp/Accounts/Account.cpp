// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Account.hpp>

#include <iostream>
#include <utility>

namespace Hearthstonepp
{
Account::Account() : m_email("anonymous@gmail.com"), m_nickname("Anonymous")
{
    // Do nothing
}

Account::Account(std::string&& email, std::string&& nickname)
    : m_email(std::move(email)), m_nickname(std::move(nickname))
{
    // Do nothing
}

Account::Account(std::string&& email, std::string&& nickname,
                 std::vector<Deck*> decks)
    : m_email(std::move(email)),
      m_nickname(std::move(nickname)),
      m_decks(std::move(decks))
{
    // Do nothing
}

std::string Account::GetEmail() const
{
    return m_email;
}

std::string Account::GetNickname() const
{
    return m_nickname;
}

size_t Account::GetNumOfDeck() const
{
    return m_decks.size();
}

Deck* Account::GetDeck(size_t idx) const
{
    return m_decks[idx];
}

void Account::ShowDeckList() const
{
    size_t idx = 0;
    for (auto& deck : m_decks)
    {
        std::cout << ++idx << ". " << deck->GetName() << " ("
                  << deck->GetNumOfCards() << " cards)\n";
    }
}

bool Account::CreateDeck(std::string name, CardClass deckClass)
{
    if (deckClass == +CardClass::INVALID)
    {
        return false;
    }

    m_decks.emplace_back(new Deck(name, deckClass));
    return true;
}

bool Account::DeleteDeck(size_t idx)
{
    m_decks.erase(m_decks.begin() + idx);
    return true;
}
}  // namespace Hearthstonepp