// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Cards/CardDefs.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Loaders/InternalCardLoader.hpp>

namespace RosettaStone::PlayMode
{
void InternalCardLoader::Load(const std::vector<Card*>& cards)
{
    for (const auto& card : cards)
    {
        const auto cardDef = CardDefs::GetInstance().FindCardDefByID(card->id);

        card->power = cardDef.power;
        card->playRequirements = cardDef.property.playReqs;
        card->chooseCardIDs = cardDef.property.chooseCardIDs;
        card->entourages = cardDef.property.entourages;
        card->appendages = cardDef.property.appendages;
        card->gameTags[GameTag::QUEST_PROGRESS_TOTAL] =
            cardDef.property.questProgressTotal;
        card->gameTags[GameTag::HERO_POWER] = cardDef.property.heroPowerDbfID;
        card->gameTags[GameTag::CORRUPTEDCARD] =
            Cards::FindCardByID(cardDef.property.corruptCardID)->dbfID;
        card->gameTags[GameTag::NUM_MINIONS_TO_INFUSE] =
            cardDef.property.numMinionsToInfuse;
        card->gameTags[GameTag::INFUSEDCARD] =
            Cards::FindCardByID(cardDef.property.infusedCardID)->dbfID;

        // NOTE: Load some game tag data
        // Scheme series
        // Rafaam's Scheme (DAL_007)
        // Dr. Boom's Scheme (DAL_008)
        // Hagatha's Scheme (DAL_009)
        // Togwaggle's Scheme (DAL_010)
        // Lazul's Scheme (DAL_011)
        if (card->dbfID == 51371 || card->dbfID == 51372 ||
            card->dbfID == 51373 || card->dbfID == 51375 ||
            card->dbfID == 51376)
        {
            card->gameTags[GameTag::TAG_SCRIPT_DATA_NUM_1] = 1;
        }

        // Crystal Stag (DAL_799)
        if (card->dbfID == 53179)
        {
            card->gameTags[GameTag::PLAYER_TAG_THRESHOLD_TAG_ID] = 958;
            card->gameTags[GameTag::PLAYER_TAG_THRESHOLD_VALUE] = 5;
        }
    }
}
}  // namespace RosettaStone::PlayMode
