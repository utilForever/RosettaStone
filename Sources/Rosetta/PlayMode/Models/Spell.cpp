// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Spell::Spell(Player* player, Card* card, std::map<GameTag, int> tags, int id)
    : Playable(player, card, std::move(tags), id)
{
    // Do nothing
}

SpellSchool Spell::GetSpellSchool() const
{
    return static_cast<SpellSchool>(GetGameTag(GameTag::SPELL_SCHOOL));
}

int Spell::GetQuestProgress() const
{
    return GetGameTag(GameTag::QUEST_PROGRESS);
}

int Spell::GetQuestProgressTotal() const
{
    return GetGameTag(GameTag::QUEST_PROGRESS_TOTAL);
}

void Spell::IncreaseQuestProgress()
{
    const int val = GetGameTag(GameTag::QUEST_PROGRESS);
    SetGameTag(GameTag::QUEST_PROGRESS, val + 1);
}

bool Spell::IsSecret() const
{
    return GetGameTag(GameTag::SECRET) == 1;
}

bool Spell::IsQuest() const
{
    return GetGameTag(GameTag::QUEST) == 1;
}

bool Spell::IsSidequest() const
{
    return GetGameTag(GameTag::SIDEQUEST) == 1;
}

bool Spell::IsTwinspell() const
{
    return GetGameTag(GameTag::TWINSPELL) == 1;
}

bool Spell::IsCountered() const
{
    return GetGameTag(GameTag::CANT_PLAY) == 1;
}

bool Spell::TargetingRequirements(Card* card, Character* target) const
{
    return !target->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS) &&
           Playable::TargetingRequirements(card, target);
}

bool Spell::IsPlayableByPlayer()
{
    if ((IsSecret() || IsSidequest()) && (player->GetSecretZone()->IsFull() ||
                                          player->GetSecretZone()->Exist(this)))
    {
        return false;
    }

    if (IsQuest() && player->GetSecretZone()->quest != nullptr)
    {
        return false;
    }

    return Playable::IsPlayableByPlayer();
}
}  // namespace RosettaStone::PlayMode
