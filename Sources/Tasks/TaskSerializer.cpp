/*************************************************************************
> File Name: TaskSerializer.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Serializer for TaskMeta and MetaData
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskSerializer.h>

#include <algorithm>

namespace Hearthstonepp::Serializer
{
BriefTaskMeta::BriefTaskMeta(BYTE currentUser, BYTE opponentUser,
                             BYTE currentMana, BYTE opponentMana,
                             BYTE numCurrentDeck, BYTE numOpponentDeck,
                             BYTE numOpponentHand,
                             const std::vector<Card*>& currentHand,
                             const std::vector<Card*>& currentField,
                             const std::vector<Card*>& opponentField,
                             const std::vector<Card*>& currentAttacked,
                             const std::vector<Card*>& opponentAttacked,
                             Card* currentHero, Card* opponentHero)
    : currentUser(currentUser),
      opponentUser(opponentUser),
      currentMana(currentMana),
      opponentMana(opponentMana),
      numCurrentDeck(numCurrentDeck),
      numOpponentDeck(numOpponentDeck),
      numOpponentHand(numOpponentHand),
      currentHand(currentHand),
      currentField(currentField),
      opponentField(opponentField),
      currentAttacked(currentAttacked),
      opponentAttacked(opponentAttacked),
      currentHero(currentHero),
      opponentHero(opponentHero)
{
    // Do Nothing
}

flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card* card)
{
    std::vector<int> mechanics(card->GetMechanics().size());
    for (const auto& mechanic : card->GetMechanics())
    {
        mechanics.emplace_back(static_cast<int>(mechanic));
    }

    return FlatData::CreateCard(
        builder, builder.CreateString(card->GetID()),
        static_cast<int>(card->GetRarity()), static_cast<int>(Faction::INVALID),
        static_cast<int>(CardSet::INVALID),
        static_cast<int>(card->GetCardClass()),
        static_cast<int>(card->GetCardType()),
        static_cast<int>(card->GetRace()),
        builder.CreateString(card->GetName()), builder.CreateString(""),
        card->GetCollectible(), card->GetCost(), card->GetAttack(),
        card->GetHealth(), card->GetDurability(),
        builder.CreateVector(mechanics), 0, 0, card->GetMaxAllowedInDeck());
}

TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              TaskMeta::status_t status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    std::vector<flatbuffers::Offset<FlatData::TaskMeta>> flatten;

    // Convert TaskMeta to FlatData::TaskMeta
    for (const auto& task : vector)
    {
        auto trait = FlatData::TaskMetaTrait(static_cast<int>(task.id),
                                             task.status, task.userID);
        const auto& unique = task.GetConstBuffer();
        auto buffer = builder.CreateVector(unique.get(), task.GetBufferSize());

        auto temporal = FlatData::CreateTaskMeta(builder, &trait, buffer);
        flatten.emplace_back(std::move(temporal));
    }

    // Convert std::vector to FlatData::TaskMetaVector
    auto integrated =
        FlatData::CreateTaskMetaVector(builder, builder.CreateVector(flatten));
    builder.Finish(integrated);

    return TaskMeta(TaskMetaTrait(TaskID::TASK_TUPLE, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateRequireTaskMeta(TaskID request, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat =
        FlatData::CreateRequireTaskMeta(builder, static_cast<int>(request));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateRequireMulliganTaskMeta(const BYTE* index, size_t size)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto vector = builder.CreateVector(index, size);
    auto flat = FlatData::CreateRequireMulliganTaskMeta(builder, vector);

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::MULLIGAN), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateRequireSummonMinionTaskMeta(int cardIndex, int position)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat = FlatData::CreateRequireSummonMinionTaskMeta(
        builder, static_cast<BYTE>(cardIndex), static_cast<BYTE>(position));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_CARD, MetaData::SELECT_CARD_MINION),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateRequireTargetingTaskMeta(int src, int dst)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat = FlatData::CreateRequireTargetingTaskMeta(
        builder, static_cast<BYTE>(src), static_cast<BYTE>(dst));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::SELECT_TARGET), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateUserSettingTaskMeta(const std::string& firstUserID,
                                   const std::string& secondUserID)
{
    flatbuffers::FlatBufferBuilder builder(128);
    auto firstID = builder.CreateString(firstUserID);
    auto secondID = builder.CreateString(secondUserID);

    auto flat = FlatData::CreateUserSettingTaskMeta(builder, firstID, secondID);
    builder.Finish(flat);

    return TaskMeta(TaskMetaTrait(TaskID::USER_SETTING), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& meta, TaskMeta::status_t status,
                            BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(512);
    std::vector<flatbuffers::Offset<FlatData::Card>> burnt;

    // Conver burnt vector to FlatData::Card vector
    for (const auto& card : meta.burnt)
    {
        burnt.emplace_back(CreateCard(builder, card));
    }

    auto flat = FlatData::CreateDrawTaskMeta(
        builder, meta.numDraw, meta.numExhausted, meta.numHearts,
        meta.numOverdraw, builder.CreateVector(burnt));

    builder.Finish(flat);

    return TaskMeta(TaskMetaTrait(TaskID::DRAW, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateModifyManaTaskMeta(const ModifyManaTaskMeta& meta,
                                  TaskMeta::status_t status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto manaTask = FlatData::CreateModifyManaTaskMeta(
        builder, meta.numMode, meta.manaMode, meta.object, meta.result);

    builder.Finish(manaTask);

    return TaskMeta(TaskMetaTrait(TaskID::MODIFY_MANA, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta,
                                    TaskMeta::status_t status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto card = CreateCard(builder, meta.card);
    auto healthTask = FlatData::CreateModifyHealthTaskMeta(
        builder, card, meta.damage, meta.hurted, meta.isExhausted);

    builder.Finish(healthTask);
    return TaskMeta(TaskMetaTrait(TaskID::MODIFY_HEALTH, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta,
                             TaskMeta::status_t status, BYTE userID)
{
    using CardOffset = flatbuffers::Offset<FlatData::Card>;
    using VectorOffset = flatbuffers::Offset<flatbuffers::Vector<CardOffset>>;

    flatbuffers::FlatBufferBuilder builder(256);

    // Tie multi card vector
    auto target = {meta.currentField, meta.currentHand, meta.opponentField,
                   meta.currentAttacked, meta.opponentAttacked};
    std::vector<VectorOffset> result(target.size());

    // Convert Card vector to FlatData::Card vector
    std::transform(target.begin(), target.end(), result.begin(),
                   [&builder](auto&& vec) -> VectorOffset {
                       std::vector<CardOffset> dest(vec.size());
                       std::transform(vec.begin(), vec.end(), dest.begin(),
                                      [&builder](const Card* card) {
                                          return CreateCard(builder, card);
                                      });

                       return builder.CreateVector(dest);
                   });

    auto brief = FlatData::CreateBriefTaskMeta(
        builder, meta.currentUser, meta.opponentUser, meta.currentMana,
        meta.opponentMana, CreateCard(builder, meta.currentHero),
        CreateCard(builder, meta.opponentHero), result[0], result[1], result[2],
        meta.numOpponentHand, meta.numCurrentDeck, meta.numOpponentDeck,
        result[3], result[4]);

    builder.Finish(brief);
    return TaskMeta(TaskMetaTrait(TaskID::BRIEF, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait,
                                    const Card* card, size_t position)
{
    flatbuffers::FlatBufferBuilder builder(128);
    auto flat = FlatData::CreateSummonMinionTaskMeta(
        builder, CreateCard(builder, card), position);

    builder.Finish(flat);
    return TaskMeta(trait, builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, const Card* src,
                              const Card* dst)
{
    flatbuffers::FlatBufferBuilder builder(256);
    auto flat = FlatData::CreateCombatTaskMeta(
        builder, CreateCard(builder, src), CreateCard(builder, dst));

    builder.Finish(flat);
    return TaskMeta(trait, builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateGameEndTaskMeta(const std::string& winner)
{
    flatbuffers::FlatBufferBuilder builder(128);
    auto winnerID = builder.CreateString(winner);
    auto flat = FlatData::CreateGameEndTaskMeta(builder, winnerID);

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::GAME_END), builder.GetSize(),
                    builder.GetBufferPointer());
}
}  // namespace Hearthstonepp::Serializer
