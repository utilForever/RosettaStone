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
        obj["player1"] = SerializePlayer(game, game.GetPlayer1());
        obj["player2"] = SerializePlayer(game, game.GetPlayer2());

        return obj;
    }

    //! Serializes the player data.
    //! \param game The game context.
    //! \param player The player context.
    //! \return The serialized player data.
    static nlohmann::json SerializePlayer(const Game& game,
                                          const Player& player)
    {
        nlohmann::json obj;

        obj["hero"] = SerializeHero(game, *player.GetHero());
        // obj["hero_power"] = SerializeHeroPower(game, player.GetHeroPower());

        return obj;
    }

    //! Serializes the hero data.
    //! \param game The game context.
    //! \param hero The hero context.
    //! \return The serialized hero data.
    static nlohmann::json SerializeHero(const Game& game, const Hero& hero)
    {
        nlohmann::json obj;

        obj["card_id"] = hero.card->id;
        obj["health"] = hero.GetHealth();
        obj["max_health"] = hero.GetMaxHealth();
        obj["attack"] = hero.GetAttack();
        obj["armor"] = hero.GetArmor();

        return obj;
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_JSON_SERIALIZER_HPP
