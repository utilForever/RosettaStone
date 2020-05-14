// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>
#include <Rosetta/PlayMode/Utils/JSONSerializer.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

namespace RosettaStone::PlayMode
{
nlohmann::json JSONSerializer::Serialize(Game& game)
{
    nlohmann::json obj;

    nlohmann::json gameObj = SerializeGame(game);

    obj["current_player_id"] = gameObj["current_player"];
    obj["turn"] = gameObj["turn"];

    if (game.GetCurrentPlayer()->playerType == PlayerType::PLAYER1)
    {
        obj["current_player"] = gameObj["player1"];
        obj["opponent_player"] = gameObj["player2"];
    }
    else
    {
        obj["current_player"] = gameObj["player2"];
        obj["opponent_player"] = gameObj["player1"];
    }

    AddPlayableCardInfo(obj["current_player"]["hand"], game);
    AddPlayableHeroPowerInfo(obj["current_player"]["hero_power"], game);
    AddAttackableInfo(obj["current_player"], game);

    AddPlayableCardInfo(obj["opponent_player"]["hand"], game, true);
    AddPlayableHeroPowerInfo(obj["opponent_player"]["hero_power"], game, true);
    AddAttackableInfo(obj["opponent_player"], game, true);

    return obj;
}

std::string JSONSerializer::GetPlayerString(const Player* player)
{
    if (player->playerType == PlayerType::PLAYER1)
    {
        return "Player1";
    }

    if (player->playerType == PlayerType::PLAYER2)
    {
        return "Player2";
    }

    throw std::runtime_error("Unknown player");
}

nlohmann::json JSONSerializer::SerializeGame(Game& game)
{
    nlohmann::json obj;

    obj["current_player"] = GetPlayerString(game.GetCurrentPlayer());
    obj["turn"] = game.GetTurn();
    obj["player1"] = SerializePlayer(game.GetPlayer1());
    obj["player2"] = SerializePlayer(game.GetPlayer2());

    return obj;
}

nlohmann::json JSONSerializer::SerializePlayer(const Player* player)
{
    nlohmann::json obj;

    obj["hero"] = SerializeHero(*player->GetHero());
    obj["hero_power"] = SerializeHeroPower(player->GetHeroPower());
    if (player->GetHero()->HasWeapon())
    {
        obj["weapon"] = SerializeWeapon(player->GetWeapon());
    }
    obj["mana_crystal"] = SerializeManaCrystal(player);
    obj["fatigue"] = player->GetHero()->fatigue;

    obj["deck"] = SerializeDeck(player->GetDeckZone());
    obj["hand"] = SerializeHand(player->GetHandZone());
    obj["minions"] = SerializeField(player->GetFieldZone());
    obj["secrets"] = SerializeSecrets(player->GetSecretZone());

    return obj;
}

nlohmann::json JSONSerializer::SerializeHero(const Hero& hero)
{
    nlohmann::json obj;

    obj["card_id"] = hero.card->dbfID;
    obj["health"] = hero.GetHealth();
    obj["max_health"] = hero.GetMaxHealth();
    obj["attack"] = hero.GetAttack();
    obj["armor"] = hero.GetArmor();

    return obj;
}

nlohmann::json JSONSerializer::SerializeHeroPower(const HeroPower& heroPower)
{
    nlohmann::json obj;

    obj["card_id"] = heroPower.card->dbfID;
    obj["usable"] = !heroPower.IsExhausted();

    return obj;
}

nlohmann::json JSONSerializer::SerializeWeapon(const Weapon& weapon)
{
    nlohmann::json obj;

    obj["card_id"] = weapon.card->dbfID;
    obj["attack"] = weapon.GetAttack();
    obj["durability"] = weapon.GetDurability();

    return obj;
}

nlohmann::json JSONSerializer::SerializeManaCrystal(const Player* player)
{
    nlohmann::json obj;

    obj["remaining"] = player->GetRemainingMana();
    obj["total"] = player->GetTotalMana();
    obj["overload_owed"] = player->GetOverloadOwed();
    obj["overload_locked"] = player->GetOverloadLocked();

    return obj;
}

nlohmann::json JSONSerializer::SerializeDeck(const DeckZone* deck)
{
    nlohmann::json obj;

    obj["count"] = deck->GetCount();

    return obj;
}

nlohmann::json JSONSerializer::SerializeHand(const HandZone* hand)
{
    nlohmann::json obj;

    for (const auto& card : hand->GetAll())
    {
        obj.emplace_back(SerializeHandCard(*card));
    }

    return obj;
}

nlohmann::json JSONSerializer::SerializeField(const FieldZone* field)
{
    nlohmann::json obj;

    for (const auto& card : field->GetAll())
    {
        obj.emplace_back(SerializeMinion(*card));
    }

    return obj;
}

nlohmann::json JSONSerializer::SerializeSecrets(const SecretZone* secrets)
{
    nlohmann::json obj;

    for (const auto& secret : secrets->GetAll())
    {
        obj.emplace_back(SerializeSecret(*secret));
    }

    return obj;
}

nlohmann::json JSONSerializer::SerializeHandCard(const Playable& handCard)
{
    nlohmann::json obj;

    obj["card_id"] = handCard.card->dbfID;
    obj["cost"] = const_cast<Playable&>(handCard).GetCost();

    return obj;
}

nlohmann::json JSONSerializer::SerializeMinion(const Minion& minion)
{
    nlohmann::json obj;

    obj["card_id"] = minion.card->dbfID;
    obj["cost"] = const_cast<Minion&>(minion).GetCost();
    obj["attack"] = minion.GetAttack();
    obj["health"] = minion.GetHealth();
    obj["max_health"] = minion.GetMaxHealth();
    obj["taunt"] = minion.GetGameTag(GameTag::TAUNT);
    obj["divine_shield"] = minion.GetGameTag(GameTag::DIVINE_SHIELD);
    obj["stealth"] = minion.GetGameTag(GameTag::STEALTH);

    return obj;
}

nlohmann::json JSONSerializer::SerializeSecret(const Spell& secret)
{
    nlohmann::json obj;

    obj["card_id"] = secret.card->dbfID;

    return obj;
}

void JSONSerializer::AddPlayableCardInfo(nlohmann::json& obj, Game& game,
                                         bool isOpponent)
{
    for (std::size_t idx = 0; idx < obj.size(); ++idx)
    {
        obj[idx]["playable"] = 0;
    }

    if (isOpponent)
    {
        return;
    }

    const ActionValidGetter getter(game);
    getter.ForEachPlayableCard([&](Entity* card) {
        const Player* curPlayer = game.GetCurrentPlayer();
        const int handIdx = curPlayer->GetHandZone()->FindIndex(card);
        obj[handIdx]["playable"] = 1;
        return true;
    });
}

void JSONSerializer::AddPlayableHeroPowerInfo(nlohmann::json& obj, Game& game,
                                              bool isOpponent)
{
    ActionValidGetter getter(game);
    obj["playable"] =
        isOpponent ? 0 : static_cast<int>(getter.CanUseHeroPower());
}

void JSONSerializer::AddAttackableInfo(nlohmann::json& obj, Game& game,
                                       bool isOpponent)
{
    for (std::size_t idx = 0; idx < obj["minions"].size(); ++idx)
    {
        obj["minions"][idx]["attackable"] = 0;
    }
    obj["hero"]["attackable"] = 0;

    if (isOpponent)
    {
        return;
    }

    const ActionValidGetter getter(game);
    getter.ForEachAttacker([&](Character* character) {
        if (dynamic_cast<Hero*>(character))
        {
            obj["hero"]["attackable"] = 1;
        }
        else
        {
            const auto minion = dynamic_cast<Minion*>(character);
            const Player* curPlayer = game.GetCurrentPlayer();
            const int minionIdx = curPlayer->GetFieldZone()->FindIndex(minion);
            obj["minions"][minionIdx]["attackable"] = 1;
            return true;
        }

        return true;
    });
}
}  // namespace RosettaStone::PlayMode
