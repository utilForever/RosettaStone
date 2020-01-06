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
    explicit NeuralNetRefInputGetter(const nlohmann::json& obj);

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetField(NeuralNet::FieldSide fieldSide,
                    NeuralNet::FieldType fieldType, int arg = 0) const final;

 private:
    //! Returns the value of the field according the side of the player.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param side The side of the player.
    //! \return The value of the field according the side of the player.
    double GetSideField(NeuralNet::FieldType fieldType, int arg,
                        const nlohmann::json& side) const;

    //! Returns the value of the mana crystal field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param manaCrystal The JSON object that contains mana crystal info.
    //! \return The value of the mana crystal field.
    double GetManaCrystalField(NeuralNet::FieldType fieldType,
                               [[maybe_unused]] int arg,
                               const nlohmann::json& manaCrystal) const;

    //! Returns the value of the hero field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param hero The JSON object that contains hero info.
    //! \return The value of the hero field.
    double GetHeroField(NeuralNet::FieldType fieldType,
                        [[maybe_unused]] int arg,
                        const nlohmann::json& hero) const;

    //! Returns the value of the minion field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param minionIdx The index of minion in field zone.
    //! \param minions The JSON object that contains minions info.
    //! \return The value of the minion field.
    double GetMinionsField(NeuralNet::FieldType fieldType, int minionIdx,
                           const nlohmann::json& minions) const;

    //! Returns the value of the hand field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param handIdx The index of card in hand zone.
    //! \param hand The JSON object that contains card info.
    //! \return The value of the hand field.
    double GetHandField(NeuralNet::FieldType fieldType, int handIdx,
                        const nlohmann::json& hand) const;

    //! Returns the value of the hero power field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \param heroPower The JSON object that contains hero power info.
    //! \return The value of the hero power field.
    double GetHeroPowerField(NeuralNet::FieldType fieldType,
                             [[maybe_unused]] int arg,
                             const nlohmann::json& heroPower) const;

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
    explicit NeuralNetInputGetter(nlohmann::json obj);

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetField(NeuralNet::FieldSide fieldSide,
                    NeuralNet::FieldType fieldType, int arg = 0) const final;

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
                const nlohmann::json& game = obj[idx]["field"];

                int label = IsCurrentPlayerWin(game, result) ? 1 : -1;
                callback(GetterType(game), label);
            }
        }
    }

 private:
    //! Returns the result of the game.
    //! \param obj The JSON object that contains game info.
    //! \result The result of the game.
    std::string GetResult(const nlohmann::json& obj);

    //! Returns the flag whether the current player won the game.
    //! \param game The JSON object that contains game info.
    //! \param result The result of the game.
    //! \result The flag whether the current player won the game.
    bool IsCurrentPlayerWin(const nlohmann::json& game,
                            const std::string& result);

    //! Returns the flag whether player 1 won the game.
    //! \param winPlayer The string that indicates winner of the game.
    //! \result The flag whether the current player won the game.
    bool IsResultWin(const std::string& winPlayer);
};
}  // namespace RosettaTorch::Judges::JSON

#endif  // ROSETTASTONE_TORCH_JUDGES_READER_HPP