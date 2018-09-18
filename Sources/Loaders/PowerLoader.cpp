#include <Enchants/Powers.h>
#include <Loaders/PowerLoader.h>

namespace Hearthstonepp
{
void PowerLoader::Load(std::vector<Card*>& cards) const
{
    Powers* powers = Powers::GetInstance();

    for (auto& card : cards)
    {
        card->power = powers->FindPowerByCardID(card->id);
    }
}
}  // namespace Hearthstonepp