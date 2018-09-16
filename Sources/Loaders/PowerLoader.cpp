#include <Loaders/PowerLoader.h>
#include <Enchants/Powers.h>

namespace Hearthstonepp
{
void PowerLoader::LoadData(std::vector<Card*>& cards) const
{
    Powers* powers = Powers::GetInstance();

    for (auto& card : cards)
    {
        card->power = powers->FindPowerByCardID(card->id);
    }
}
}  // namespace Hearthstonepp