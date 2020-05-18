// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_JSON_SERIALIZER_HPP
#define ROSETTASTONE_PLAYMODE_JSON_SERIALIZER_HPP

#include <Rosetta/PlayMode/Games/Game.hpp>

#include <json/json.hpp>

namespace RosettaStone::PlayMode
{
class Spell;

class JSONSerializer
{
 public:
    //! Serializes the game data.
    //! \param game The game context.
    //! \return The serialized game data.
    static nlohmann::json Serialize(Game& game);

    //! Returns the string that represents the player.
    //! \param player The player to create string.
    //! \return The string that represents the player.
    static std::string GetPlayerString(const Player* player);

 private:
    //! Serializes the game data.
    //! \param game The game context.
    //! \return The serialized game data.
    static nlohmann::json SerializeGame(Game& game);

    //! Serializes the player data.
    //! \param player The player context.
    //! \return The serialized player data.
    static nlohmann::json SerializePlayer(const Player* player);

    //! Serializes the hero data.
    //! \param hero The hero context.
    //! \return The serialized hero data.
    static nlohmann::json SerializeHero(const Hero& hero);

    //! Serializes the hero power data.
    //! \param heroPower The hero power context.
    //! \return The serialized hero power data.
    static nlohmann::json SerializeHeroPower(const HeroPower& heroPower);

    //! Serializes the weapon data.
    //! \param weapon The weapon context.
    //! \return The serialized weapon data.
    static nlohmann::json SerializeWeapon(const Weapon& weapon);

    //! Serializes the mana crystal data.
    //! \param player The player context.
    //! \return The serialized mana crystal data.
    static nlohmann::json SerializeManaCrystal(const Player* player);

    //! Serializes the deck data.
    //! \param deck The deck context.
    //! \return The serialized deck data.
    static nlohmann::json SerializeDeck(const DeckZone* deck);

    //! Serializes the hand data.
    //! \param hand The hand context.
    //! \return The serialized hand data.
    static nlohmann::json SerializeHand(const HandZone* hand);

    //! Serializes the field data.
    //! \param field The field context.
    //! \return The serialized field data.
    static nlohmann::json SerializeField(const FieldZone* field);

    //! Serializes the secrets data.
    //! \param secrets The secrets context.
    //! \return The serialized secrets data.
    static nlohmann::json SerializeSecrets(const SecretZone* secrets);

    //! Serializes the hand card data.
    //! \param handCard The hand card context.
    //! \return The serialized hand card data.
    static nlohmann::json SerializeHandCard(const Playable& handCard);

    //! Serializes the minion data.
    //! \param minion The minion context.
    //! \return The serialized minion data.
    static nlohmann::json SerializeMinion(const Minion& minion);

    //! Serializes the secret data.
    //! \param secret The secret context.
    //! \return The serialized secret data.
    static nlohmann::json SerializeSecret(const Spell& secret);

    //! Adds the playable card info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    //! \param isOpponent The flag that indicates it is the opponent player.
    static void AddPlayableCardInfo(nlohmann::json& obj, Game& game,
                                    bool isOpponent = false);

    //! Adds the playable hero power info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    //! \param isOpponent The flag that indicates it is the opponent player.
    static void AddPlayableHeroPowerInfo(nlohmann::json& obj, Game& game,
                                         bool isOpponent = false);

    //! Adds the attackable info.
    //! \param obj The JSON object to add info.
    //! \param game The game context.
    //! \param isOpponent The flag that indicates it is the opponent player.
    static void AddAttackableInfo(nlohmann::json& obj, Game& game,
                                  bool isOpponent = false);
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_JSON_SERIALIZER_HPP
