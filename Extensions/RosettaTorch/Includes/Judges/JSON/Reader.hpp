// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_READER_HPP
#define ROSETTASTONE_TORCH_JUDGES_READER_HPP

#include <NeuralNet/IInputGetter.hpp>

#include <json/json.hpp>

#include <utility>

namespace RosettaTorch::Judges::JSON
{
//!
//! \brief NeuralNetRefInputGetter class.
//!
//! This class inherits from NeuralNet::IInputGetter class.
//!
class NeuralNetRefInputGetter : public NeuralNet::IInputGetter
{
 public:
    //! Constructs neural net ref input getter with given \p obj.
    //! \param obj The JSON object.
    NeuralNetRefInputGetter(const nlohmann::json& obj) : m_obj(obj)
    {
        // Do nothing
    }

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetField(NeuralNet::FieldSide fieldSide,
                    NeuralNet::FieldType fieldType,
                    int arg = 0) const override final
    {
        if (fieldSide == NeuralNet::FieldSide::CURRENT)
        {
            return GetSideField(fieldType, arg, m_obj["current_player"]);
        }
        if (fieldSide == NeuralNet::FieldSide::OPPONENT)
        {
            return GetSideField(fieldType, arg, m_obj["opponent_player"]);
        }

        throw std::runtime_error("Invalid side");
    }

 private:
    //! Returns the value of the field according the side of the player.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param side The side of the player.
    //! \return The value of the field according the side of the player.
    double GetSideField(NeuralNet::FieldType fieldType, int arg,
                        const nlohmann::json& side) const
    {
        switch (fieldType)
        {
            case NeuralNet::FieldType::MANA_CRYSTAL_CURRENT:
            case NeuralNet::FieldType::MANA_CRYSTAL_TOTAL:
            case NeuralNet::FieldType::MANA_CRYSTAL_OVERLOAD_OWED:
            case NeuralNet::FieldType::MANA_CRYSTAL_OVERLOAD_LOCKED:
                return GetManaCrystalField(fieldType, arg,
                                           side["mana_crystal"]);
            case NeuralNet::FieldType::HERO_HEALTH:
            case NeuralNet::FieldType::HERO_ARMOR:
                return GetHeroField(fieldType, arg, side["hero"]);
            case NeuralNet::FieldType::MINION_COUNT:
            case NeuralNet::FieldType::MINION_HEALTH:
            case NeuralNet::FieldType::MINION_MAX_HEALTH:
            case NeuralNet::FieldType::MINION_ATTACK:
            case NeuralNet::FieldType::MINION_ATTACKABLE:
            case NeuralNet::FieldType::MINION_TAUNT:
            case NeuralNet::FieldType::MINION_DIVINE_SHIELD:
            case NeuralNet::FieldType::MINION_STEALTH:
                return GetMinionsField(fieldType, arg, side["minions"]);
            case NeuralNet::FieldType::HAND_COUNT:
            case NeuralNet::FieldType::HAND_PLAYABLE:
            case NeuralNet::FieldType::HAND_COST:
                return GetHandField(fieldType, arg, side["hand"]);
            case NeuralNet::FieldType::HERO_POWER_PLAYABLE:
                return GetHeroPowerField(fieldType, arg, side["hero_power"]);
            default:
                throw std::runtime_error("Unknown field type");
        }
    }

    //! Returns the value of the mana crystal field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param manaCrystal The JSON object that contains mana crystal info.
    //! \return The value of the mana crystal field.
    double GetManaCrystalField(NeuralNet::FieldType fieldType,
                               [[maybe_unused]] int arg,
                               const nlohmann::json& manaCrystal) const
    {
        switch (fieldType)
        {
            case NeuralNet::FieldType::MANA_CRYSTAL_CURRENT:
                return manaCrystal["remaining"];
            case NeuralNet::FieldType::MANA_CRYSTAL_TOTAL:
                return manaCrystal["total"];
            case NeuralNet::FieldType::MANA_CRYSTAL_OVERLOAD_OWED:
                return manaCrystal["overload_owed"];
            case NeuralNet::FieldType::MANA_CRYSTAL_OVERLOAD_LOCKED:
                return manaCrystal["overload_locked"];
            default:
                throw std::runtime_error("Unknown field type");
        }
    }

    //! Returns the value of the hero field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param hero The JSON object that contains hero info.
    //! \return The value of the hero field.
    double GetHeroField(NeuralNet::FieldType fieldType,
                        [[maybe_unused]] int arg,
                        const nlohmann::json& hero) const
    {
        switch (fieldType)
        {
            case NeuralNet::FieldType::HERO_HEALTH:
                return hero["health"];
            case NeuralNet::FieldType::HERO_ARMOR:
                return hero["armor"];
            default:
                throw std::runtime_error("Unknown field type");
        }
    }

    //! Returns the value of the minion field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param minionIdx The index of minion in field zone.
    //! \param minions The JSON object that contains minions info.
    //! \return The value of the minion field.
    double GetMinionsField(NeuralNet::FieldType fieldType, int minionIdx,
                           const nlohmann::json& minions) const
    {
        switch (fieldType)
        {
            case NeuralNet::FieldType::MINION_COUNT:
                return minions.size();
            case NeuralNet::FieldType::MINION_HEALTH:
                return minions[minionIdx]["health"];
            case NeuralNet::FieldType::MINION_MAX_HEALTH:
                return minions[minionIdx]["max_health"];
            case NeuralNet::FieldType::MINION_ATTACK:
                return minions[minionIdx]["attack"];
            case NeuralNet::FieldType::MINION_ATTACKABLE:
                return minions[minionIdx]["attackable"];
            case NeuralNet::FieldType::MINION_TAUNT:
                return minions[minionIdx]["taunt"];
            case NeuralNet::FieldType::MINION_DIVINE_SHIELD:
                return minions[minionIdx]["divine_shield"];
            case NeuralNet::FieldType::MINION_STEALTH:
                return minions[minionIdx]["stealth"];
            default:
                throw std::runtime_error("Unknown field type");
        }
    }

    //! Returns the value of the hand field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param handIdx The index of card in hand zone.
    //! \param hand The JSON object that contains card info.
    //! \return The value of the hand field.
    double GetHandField(NeuralNet::FieldType fieldType, int handIdx,
                        const nlohmann::json& hand) const
    {
        switch (fieldType)
        {
            case NeuralNet::FieldType::HAND_COUNT:
                return hand.size();
            case NeuralNet::FieldType::HAND_PLAYABLE:
                return static_cast<double>(
                    hand[handIdx]["playable"].get<bool>());
            case NeuralNet::FieldType::HAND_COST:
                return hand[handIdx]["cost"];
            default:
                throw std::runtime_error("Unknown field type");
        }
    }

    //! Returns the value of the hero power field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param heroPower The JSON object that contains hero power info.
    //! \return The value of the hero power field.
    double GetHeroPowerField(NeuralNet::FieldType fieldType,
                             [[maybe_unused]] int arg,
                             const nlohmann::json& heroPower) const
    {
        if (fieldType == NeuralNet::FieldType::HERO_POWER_PLAYABLE)
        {
            return static_cast<double>(heroPower["playable"].get<bool>());
        }

        throw std::runtime_error("Unknown field type");
    }

    const nlohmann::json& m_obj;
};

//!
//! \brief NeuralNetInputGetter class.
//!
//! This class inherits from NeuralNet::IInputGetter class.
//!
class NeuralNetInputGetter : public NeuralNet::IInputGetter
{
 public:
    //! Constructs neural net input getter with given \p obj.
    //! \param obj The JSON object.
    NeuralNetInputGetter(nlohmann::json obj) : m_obj(std::move(obj))
    {
        // Do nothing
    }

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetField(NeuralNet::FieldSide fieldSide,
                    NeuralNet::FieldType fieldType,
                    int arg = 0) const override final
    {
        return NeuralNetRefInputGetter(m_obj).GetField(fieldSide, fieldType,
                                                       arg);
    }

 private:
    nlohmann::json m_obj;
};

//!
//! \brief Reader class.
//!
//! This class is created to record the game data.
//!
class Reader
{
 public:
    //! Parses the JSON object and runs function to add data.
    //! \param obj The JSON object that contains game info.
    //! \param callback A function to add data.
    template <class Callback, class GetterType = NeuralNetInputGetter>
    void Parse(const nlohmann::json& obj, Callback&& callback)
    {
        const std::string result = GetResult(obj);

        for (std::size_t idx = 0; idx < obj.size(); ++idx)
        {
            if (obj[idx]["type"] == "MAIN_ACTION")
            {
                const nlohmann::json& game = obj[idx]["game"];

                int label = IsCurrentPlayerWin(game, result) ? 1 : -1;
                callback(GetterType(game), label);
            }
        }
    }

 private:
    //! Returns the result of the game.
    //! \param obj The JSON object that contains game info.
    //! \result The result of the game.
    std::string GetResult(const nlohmann::json& obj)
    {
        for (std::size_t idx = 0; idx < obj.size(); ++idx)
        {
            if (obj[idx]["type"] == "END")
            {
                return obj[idx]["result"];
            }
        }

        throw std::runtime_error("Cannot find win player");
    }

    //! Returns the flag whether the current player won the game.
    //! \param game The JSON object that contains game info.
    //! \param result The result of the game.
    //! \result The flag whether the current player won the game.
    bool IsCurrentPlayerWin(const nlohmann::json& game,
                            const std::string& result)
    {
        const std::string curPlayer = game["current_player_id"];

        bool isCurPlayerP1;
        if (curPlayer == "Player1")
        {
            isCurPlayerP1 = true;
        }
        else if (curPlayer == "Player2")
        {
            isCurPlayerP1 = false;
        }
        else
        {
            throw std::runtime_error("Failed to parse current player");
        }

        // NOTE: AI is always helping Player 1
        const bool isWinPlayerP1 = IsResultWin(result);

        return isCurPlayerP1 == isWinPlayerP1;
    }

    //! Returns the flag whether player 1 won the game.
    //! \param winPlayer The string that indicates winner of the game.
    //! \result The flag whether the current player won the game.
    bool IsResultWin(const std::string& winPlayer)
    {
        if (winPlayer == "PLAYER1_WIN")
        {
            return true;
        }
        if (winPlayer == "PLAYER2_WIN")
        {
            return false;
        }
        if (winPlayer == "DRAW")
        {
            return false;
        }

        throw std::runtime_error("Failed to parse winning player");
    }
};
}  // namespace RosettaTorch::Judges::JSON

#endif  // ROSETTASTONE_TORCH_JUDGES_READER_HPP