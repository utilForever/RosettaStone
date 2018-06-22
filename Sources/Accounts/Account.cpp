/*************************************************************************
> File Name: Account.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Account class that stores a list of decks.
> Created Time: 2017/10/18
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Accounts/Account.h>

#include <iostream>

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
    : m_email(std::move(email)), m_nickname(std::move(nickname)), m_decks(decks)
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

Deck* Account::GetDeck(size_t emailx) const
{
    return m_decks[emailx];
}

void Account::ShowDeckList() const
{
    size_t emailx = 0;
    for (auto& deck : m_decks)
    {
        std::cout << ++emailx << ". " << deck->GetName() << " ("
                  << deck->GetNumOfCards() << " cards)\n";
    }
}

bool Account::CreateDeck(std::string nickname, CardClass deckClass)
{
    if (deckClass == +CardClass::INVALID)
        return false;

    m_decks.emplace_back(new Deck(nickname, deckClass));
    return true;
}

bool Account::DeleteDeck(size_t selectedDeck)
{
    m_decks.erase(m_decks.begin() + selectedDeck);
    return true;
}
}