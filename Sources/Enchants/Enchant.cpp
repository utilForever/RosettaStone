#include <Enchants/Enchant.h>

namespace Hearthstonepp
{
Enchant::Enchant(Effect& effect)
{
    m_effects.emplace_back(effect);
}

Enchant::Enchant(std::vector<Effect>& effects)
{
    m_effects = effects;
}

void Enchant::ActivateTo(Character* character)
{
    for (auto& effect : m_effects)
    {
        effect.Apply(character);
    }
}
}  // namespace Hearthstonepp