// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_JSON_SERIALIZER_HPP
#define ROSETTASTONE_JSON_SERIALIZER_HPP

#include <Rosetta/Actions/ActionValidGetter.hpp>
#include <Rosetta/Games/Game.hpp>

#include <json/json.hpp>

namespace RosettaStone
{
class JSONSerializer
{
 public:
    //! Serializes the game data.
    //! \param game The game context.
    //! \return The serialized game data.
    static nlohmann::json Serialize(Game& game)
    {
        nlohmann::json obj;

        nlohmann::json gameObj = SerializeGame(game);

        obj["current_player_id"] = gameObj["current_player"];
        obj["turn"] = gameObj["turn"];

        if (game.GetCurrentPlayer().playerType == PlayerType::PLAYER1)
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

        return obj;
    }

    //! Returns the string that represents the player.
    //! \param player The player to create string.
    //! \return The string that represents the player.
    static std::string GetPlayerString(const Player& player)
    {
        if (player.playerType == PlayerType::PLAYER1)
        {
            return "Player1";
        }

        if (player.playerType == PlayerType::PLAYER2)
        {
            return "Player2";
        }

        throw std::runtime_error("Unknown player");
    }

 private:
    //! Serializes the game data.
    //! \param game The game context.
    //! \return The serialized game data.
    static nlohmann::json SerializeGame(Game& game)
    {
        nlohmann::json obj;

        obj["current_player"] = GetPlayerString(game.GetCurrentPlayer());
        obj["turn"] = game.GetTurn();
        obj["player1"] = SerializePlayer(game.GetPlayer1());
        obj["player2"] = SerializePlayer(game.GetPlayer2());

        return obj;
    }

    //! Serializes the player data.
    //! \param player The player context.
    //! \return The serialized player data.
    static nlohmann::json SerializePlayer(const Player& player)
    {
        nlohmann::json obj;

        obj["hero"] = SerializeHero(*player.GetHero());
        obj["hero_power"] = SerializeHeroPower(player.GetHeroPower());
        if (&player.GetWeapon() != nullptr)
        {
            obj["weapon"] = SerializeWeapon(player.GetWeapon());
        }
        obj["mana_crystal"] = SerializeManaCrystal(player);
        obj["fatigue"] = player.GetHero()->fatigue;

        obj["deck"] = SerializeDeck(player.GetDeckZone());
        obj["hand"] = SerializeHand(player.GetHandZone());
        obj["minions"] = SerializeField(player.GetFieldZone());
        obj["secrets"] = SerializeSecrets(player.GetSecretZone());

        return obj;
    }

    //! Serializes the hero data.
    //! \param hero The hero context.
    //! \return The serialized hero data.
    static nlohmann::json SerializeHero(const Hero& hero)
    {
        nlohmann::json obj;

        obj["card_id"] = hero.card->id;
        obj["health"] = hero.GetHealth();
        obj["max_health"] = hero.GetMaxHealth();
        obj["attack"] = hero.GetAttack();
        obj["armor"] = hero.GetArmor();

        return obj;
    }

    //! Serializes the hero power data.
    //! \param heroPower The hero power context.
    //! \return The serialized hero power data.
    static nlohmann::json SerializeHeroPower(const HeroPower& heroPower)
    {
        nlohmann::json obj;

        obj["card_id"] = heroPower.card->id;
        obj["usable"] = !heroPower.IsExhausted();

        return obj;
    }

    //! Serializes the weapon data.
    //! \param weapon The weapon context.
    //! \return The serialized weapon data.
    static nlohmann::json SerializeWeapon(const Weapon& weapon)
    {
        nlohmann::json obj;

        obj["card_id"] = weapon.card->id;
        obj["attack"] = weapon.GetAttack();
        obj["durability"] = weapon.GetDurability();

        return obj;
    }

    //! Serializes the mana crystal data.
    //! \param player The player context.
    //! \return The serialized mana crystal data.
    static nlohmann::json SerializeManaCrystal(const Player& player)
    {
        nlohmann::json obj;

        obj["remaining"] = player.GetRemainingMana();
        obj["total"] = player.GetTotalMana();
        obj["overload_owed"] = player.GetOverloadOwed();
        obj["overload_locked"] = player.GetOverloadLocked();

        return obj;
    }

    //! Serializes the deck data.
    //! \param deck The deck context.
    //! \return The serialized deck data.
    static nlohmann::json SerializeDeck(const DeckZone& deck)
    {
        nlohmann::json obj;

        obj["count"] = deck.GetCount();

        return obj;
    }

    //! Serializes the hand data.
    //! \param hand The hand context.
    //! \return The serialized hand data.
    static nlohmann::json SerializeHand(const HandZone& hand)
    {
        nlohmann::json obj;

        for (const auto& card : hand.GetAll())
        {
            obj.emplace_back(SerializeHandCard(*card));
        }

        return obj;
    }

    //! Serializes the field data.
    //! \param field The field context.
    //! \return The serialized field data.
    static nlohmann::json SerializeField(const FieldZone& field)
    {
        nlohmann::json obj;

        for (const auto& card : field.GetAll())
        {
            obj.emplace_back(SerializeMinion(*card));
        }

        return obj;
    }

    //! Serializes the secrets data.
    //! \param secrets The secrets context.
    //! \return The serialized secrets data.
    static nlohmann::json SerializeSecrets(const SecretZone& secrets)
    {
        nlohmann::json obj;

        for (const auto& secret : secrets.GetAll())
        {
            obj.emplace_back(SerializeSecret(*secret));
        }

        return obj;
    }

    //! Serializes the hand card data.
    //! \param handCard The hand card context.
    //! \return The serialized hand card data.
    static nlohmann::json SerializeHandCard(const Entity& handCard)
    {
        nlohmann::json obj;

        obj["card_id"] = handCard.card->id;
        obj["cost"] = handCard.GetCost();

        return obj;
    }

    //! Serializes the minion data.
    //! \param minion The minion context.
    //! \return The serialized minion data.
    static nlohmann::json SerializeMinion(const Minion& minion)
    {
        nlohmann::json obj;

        obj["card_id"] = minion.card->id;
        obj["cost"] = minion.GetCost();
        obj["attack"] = minion.GetAttack();
        obj["health"] = minion.GetHealth();
        obj["max_health"] = minion.GetMaxHealth();
        obj["taunt"] = minion.GetGameTag(GameTag::TAUNT);
        obj["divine_shield"] = minion.GetGameTag(GameTag::DIVINE_SHIELD);
        obj["stealth"] = minion.GetGameTag(GameTag::STEALTH);

        return obj;
    }

    //! Serializes the secret data.
    //! \param secret The secret context.
    //! \return The serialized secret data.
    static nlohmann::json SerializeSecret(const Spell& secret)
    {
        nlohmann::json obj;

        obj["card_id"] = secret.card->id;

        return obj;
    }

    //! Adds the playable card info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    static void AddPlayableCardInfo(nlohmann::json& obj, Game& game)
    {
        for (std::size_t idx = 0; idx < obj.size(); ++idx)
        {
            obj[idx]["playable"] = false;
        }

        const ActionValidGetter getter(game);
        getter.ForEachPlayableCard([&](Entity* card) {
            const Player& curPlayer = game.GetCurrentPlayer();
            const int handIdx = curPlayer.GetHandZone().FindIndex(*card);
            obj[handIdx]["playable"] = true;
            return true;
        });
    }

    //! Adds the playable hero power info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    static void AddPlayableHeroPowerInfo(nlohmann::json& obj, Game& game)
    {
        ActionValidGetter getter(game);
        obj["playable"] = getter.CanUseHeroPower();
    }

    //! Adds the attackable info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    static void AddAttackableInfo(nlohmann::json& obj, Game& game)
    {
        for (std::size_t idx = 0; idx < obj["minions"].size(); ++idx)
        {
            obj["minions"][idx]["attackable"] = false;
        }
        obj["hero"]["attackable"] = false;

        const ActionValidGetter getter(game);
        getter.ForEachAttacker([&](Character* character) {
            if (dynamic_cast<Hero*>(character))
            {
                obj["hero"]["attackable"] = true;
            }
            else
            {
                const Player& curPlayer = game.GetCurrentPlayer();
                const int minionIdx =
                    curPlayer.GetFieldZone().FindIndex(*character);
                obj["minions"][minionIdx]["attackable"] = true;
                return true;
            }

            return true;
        });
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_JSON_SERIALIZER_HPP
