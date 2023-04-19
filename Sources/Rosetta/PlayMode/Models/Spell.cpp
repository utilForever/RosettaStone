// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Spell::Spell(Player* _player, Card* _card, std::map<GameTag, int> tags, int id)
    : Playable(_player, _card, std::move(tags), id)
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

bool Spell::IsQuestline() const
{
    return GetGameTag(GameTag::QUESTLINE) == 1;
}

bool Spell::IsTwinspell() const
{
    return GetGameTag(GameTag::TWINSPELL) == 1;
}

bool Spell::IsCountered() const
{
    return GetGameTag(GameTag::CANT_PLAY) == 1;
}

bool Spell::TargetingRequirements(Card* _card, Character* target) const
{
    return !target->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS) &&
           Playable::TargetingRequirements(_card, target);
}

bool Spell::IsPlayableByPlayer()
{
    if ((IsSecret() || IsQuest() || IsSidequest() || IsQuestline()) &&
        (player->GetSecretZone()->IsFull() ||
         player->GetSecretZone()->Exist(this)))
    {
        return false;
    }

    if (IsQuest() && player->GetSecretZone()->quest)
    {
        return false;
    }

    return Playable::IsPlayableByPlayer();
}
}  // namespace RosettaStone::PlayMode
