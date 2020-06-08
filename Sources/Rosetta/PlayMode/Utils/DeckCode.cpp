// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
DeckInfo DeckCode::Decode(const std::string& deckCode)
{
    std::size_t pos = 0;
    std::vector<unsigned char> code = DecodeBase64(deckCode);

    const auto ReadVarint = [&] {
        int shift = 0, result = 0;

        while (true)
        {
            if (pos >= code.size())
                throw std::runtime_error("Unexpected EOF while reading varint");

            const int ch = code[pos];
            ++pos;

            result |= (ch & 0x7f) << shift;
            shift += 7;

            if ((ch & 0x80) == 0)
            {
                break;
            }
        }

        return result;
    };

    if (code[pos] != '\0')
    {
        throw std::runtime_error("Invalid deck code");
    }
    ++pos;

    if (ReadVarint() != DECK_CODE_VERSION)
    {
        throw std::runtime_error("Version mismatch");
    }

    const auto format = static_cast<FormatType>(ReadVarint());
    if (format != FormatType::STANDARD && format != FormatType::WILD)
    {
        throw std::runtime_error("Invalid format type");
    }

    int num = ReadVarint();
    if (num != 1)
    {
        throw std::runtime_error("Hero count must be 1");
    }

    Card* hero = Cards::FindCardByDbfID(ReadVarint());
    if (hero->GetCardClass() == CardClass::INVALID)
    {
        throw std::runtime_error("Invalid hero");
    }

    DeckInfo deckInfo("EMPTY", hero->GetCardClass());

    // Single-copy cards
    num = ReadVarint();
    for (int i = 0; i < num; ++i)
    {
        const int cardID = ReadVarint();
        deckInfo.AddCard(Cards::FindCardByDbfID(cardID)->id, 1);
    }

    // 2-copy cards
    num = ReadVarint();
    for (int i = 0; i < num; ++i)
    {
        const int cardID = ReadVarint();
        deckInfo.AddCard(Cards::FindCardByDbfID(cardID)->id, 2);
    }

    // n-copy cards
    num = ReadVarint();
    for (int i = 0; i < num; ++i)
    {
        const int cardID = ReadVarint();
        const int count = ReadVarint();
        deckInfo.AddCard(Cards::FindCardByDbfID(cardID)->id, count);
    }

    return deckInfo;
}
}  // namespace RosettaStone::PlayMode
