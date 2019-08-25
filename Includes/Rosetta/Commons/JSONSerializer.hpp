// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_JSON_SERIALIZER_HPP
#define ROSETTASTONE_JSON_SERIALIZER_HPP

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
    static nlohmann::json Serialize(const Game& game)
    {
        nlohmann::json obj;

        nlohmann::json gameObj = SerializeGame(game);
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
    static nlohmann::json SerializeGame(const Game& game)
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
        obj["weapon"] = SerializeWeapon(player.GetWeapon());
        obj["mana_crystal"] = SerializeManaCrystal(player);
        obj["fatigue"] = player.GetHero()->fatigue;

        obj["deck"] = SerializeDeck(player.GetDeckZone());
        obj["hand"] = SerializeHand(player.GetHandZone());
        obj["minions"] = SerializeField(player.GetFieldZone());

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

        return obj;
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_JSON_SERIALIZER_HPP
