// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/DeckString.hpp>
#include <Rosetta/Commons/Utils.hpp>

#include <stdexcept>

namespace RosettaStone
{
DeckInfo DeckString::ParseFromString(const std::string& deckString)
{
    std::size_t pos = 0;
    std::vector<unsigned char> code = Base64Decode(deckString);

    const auto read_varint = [&] {
        int shift = 0, result = 0;

        while (true)
        {
            if (pos >= code.size())
                throw std::runtime_error("Unexpected EOF while reading varint");

            int ch = code[pos];
            ++pos;

            result |= (ch & 0x7f) << shift;
            shift += 7;

            if ((ch & 0x80) == 0)
                break;
        }

        return result;
    };

    if (code[pos] != '\0')
        throw std::runtime_error("Invalid deckstring");
    ++pos;

    if (read_varint() != DECKSTRING_VERSION)
        throw std::runtime_error("Version mismatch");

    FormatType format = static_cast<FormatType>(read_varint());
    if (format != FormatType::STANDARD && format != FormatType::WILD)
        throw std::runtime_error("Invalid format type");

    int num = read_varint();
    if (num != 1)
        throw std::runtime_error("Heros count must be 1");

	Card* hero = Cards::FindCardByDbfId(read_varint());
    if (hero->GetCardClass() == CardClass::INVALID)
        throw std::runtime_error("Invalid hero");

    DeckInfo deckInfo("EMPTY", hero->GetCardClass());

    // single-copy cards
    num = read_varint();
    for (int i = 0; i < num; ++i)
    {
        int card_id = read_varint();
        deckInfo.AddCard(Cards::FindCardByDbfId(card_id)->id, 1);
    }

    // 2-copy cards
    num = read_varint();
    for (int i = 0; i < num; ++i)
    {
        int card_id = read_varint();
        deckInfo.AddCard(Cards::FindCardByDbfId(card_id)->id, 2);
    }

    // n-copy cards
    num = read_varint();
    for (int i = 0; i < num; ++i)
    {
        int card_id = read_varint();
        int count = read_varint();
        deckInfo.AddCard(Cards::FindCardByDbfId(card_id)->id, count);
    }

    return deckInfo;
}
}  // namespace RosettaStone
