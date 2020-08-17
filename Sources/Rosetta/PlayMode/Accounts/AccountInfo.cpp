// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Accounts/AccountInfo.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

#include <iostream>
#include <utility>

namespace RosettaStone::PlayMode
{
AccountInfo::AccountInfo()
    : m_email("anonymous@gmail.com"), m_nickname("Anonymous")
{
    // Do nothing
}

AccountInfo::AccountInfo(std::string&& email, std::string&& nickname)
    : m_email(std::move(email)), m_nickname(std::move(nickname))
{
    // Do nothing
}

AccountInfo::AccountInfo(std::string&& email, std::string&& nickname,
                         std::vector<DeckInfo*> decks)
    : m_email(std::move(email)),
      m_nickname(std::move(nickname)),
      m_decks(std::move(decks))
{
    // Do nothing
}

std::string AccountInfo::GetEmail() const
{
    return m_email;
}

std::string AccountInfo::GetNickname() const
{
    return m_nickname;
}

std::size_t AccountInfo::GetNumOfDeck() const
{
    return m_decks.size();
}

DeckInfo* AccountInfo::GetDeck(std::size_t idx) const
{
    return m_decks[idx];
}

void AccountInfo::ShowDeckList() const
{
    std::size_t idx = 0;
    for (auto& deck : m_decks)
    {
        std::cout << ++idx << ". " << deck->GetName() << " ("
                  << deck->GetNumOfCards() << " cards)\n";
    }
}

bool AccountInfo::CreateDeck(std::string name, CardClass deckClass)
{
    if (deckClass == CardClass::INVALID)
    {
        return false;
    }

    m_decks.emplace_back(new DeckInfo(name, deckClass));
    return true;
}

bool AccountInfo::CreateDeckWithCode(std::string_view deckCode)
{
    const DeckInfo newDeck = DeckCode::Decode(deckCode);
    m_decks.emplace_back(new DeckInfo(newDeck));
    return true;
}

bool AccountInfo::DeleteDeck(std::size_t idx)
{
    m_decks.erase(m_decks.begin() + idx);
    return true;
}
}  // namespace RosettaStone::PlayMode
