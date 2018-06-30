/*************************************************************************
> File Name: TaskSerializer.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Serializer for TaskMeta and MetaData
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Cards/Character.h>
#include <Cards/Weapon.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskSerializer.h>

#include <algorithm>

namespace Hearthstonepp::Serializer
{
BriefTaskMeta::BriefTaskMeta(BYTE currentPlayer, BYTE opponentPlayer,
                             BYTE currentMana, BYTE opponentMana,
                             BYTE numCurrentDeck, BYTE numOpponentDeck,
                             BYTE numOpponentHand,
                             const std::vector<Card*>& currentHand,
                             const std::vector<Card*>& currentField,
                             const std::vector<Card*>& opponentField,
                             const std::vector<Card*>& currentAttacked,
                             const std::vector<Card*>& opponentAttacked,
                             Card* currentHero, Card* opponentHero)
    : currentPlayer(currentPlayer),
      opponentPlayer(opponentPlayer),
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
    flatbuffers::FlatBufferBuilder& builder, Card* card)
{
    std::vector<int> mechanics(card->mechanics.size());
    for (const auto& mechanic : card->mechanics)
    {
        mechanics.emplace_back(static_cast<int>(mechanic));
    }

    size_t attack = 0;
    size_t health = 0;
    size_t durability = 0;

    const Character* character = dynamic_cast<Character*>(card);
    if (character != nullptr)
    {
        attack = character->attack;
        health = character->health;
    }

    const Weapon* weapon = dynamic_cast<Weapon*>(card);
    if (weapon != nullptr)
    {
        durability = weapon->durability;
    }

    return FlatData::CreateCard(
        builder, builder.CreateString(card->id), static_cast<int>(card->rarity),
        static_cast<int>(Faction::INVALID), static_cast<int>(CardSet::INVALID),
        static_cast<int>(card->cardClass), static_cast<int>(card->cardType),
        static_cast<int>(card->race), builder.CreateString(card->name),
        builder.CreateString(""), card->isCollectible,
        static_cast<int>(card->cost), static_cast<uint32_t>(attack),
        static_cast<uint32_t>(health), static_cast<uint32_t>(durability),
        builder.CreateVector(mechanics), 0, 0, card->GetMaxAllowedInDeck());
}

std::unique_ptr<Card> ConvertCardFrom(const FlatData::Card* card)
{ 
	std::unique_ptr<Card> ptrCard;
	if (card->attack() != 0 || card->health() != 0)
	{
        auto character = std::make_unique<Character>();
        character->attack = static_cast<size_t>(card->attack());
        character->health = static_cast<size_t>(card->health());

        ptrCard = std::move(character);
	}
	else if (card->durability() != 0)
	{
        auto weapon = std::make_unique<Weapon>();
        weapon->durability = static_cast<size_t>(card->durability());

		ptrCard = std::move(weapon);
	}
	else
	{
        ptrCard = std::make_unique<Card>();
	}

	Card& newCard = *ptrCard;
	newCard.id = card->id()->str();

    newCard.rarity = Rarity::_from_integral(card->rarity());
    newCard.faction = Faction::_from_integral(card->faction());
    newCard.cardSet = CardSet::_from_integral(card->cardSet());
    newCard.cardClass = CardClass::_from_integral(card->cardClass());
    newCard.cardType = CardType::_from_integral(card->cardType());
    newCard.race = Race::_from_integral(card->race());

    newCard.name = card->name()->str();
    newCard.text = card->text()->str();

	newCard.isCollectible = card->collectible();
    newCard.cost = static_cast<size_t>(card->cost());

	auto mechanics = card->mechanics();
    newCard.mechanics.reserve(mechanics->size());

	for (auto m : *mechanics)
	{
        GameTag tag = GameTag::_from_integral(m);
        newCard.mechanics.emplace_back(tag);
	}

	newCard.maxAllowedInDeck = card->maxAllowedInDeck();

	return ptrCard;
}

TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              MetaData status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    std::vector<flatbuffers::Offset<FlatData::TaskMeta>> flatten;

    // Convert TaskMeta to FlatData::TaskMeta
    for (const auto& task : vector)
    {
        auto trait = FlatData::TaskMetaTrait(static_cast<int>(task.id),
                                             static_cast<status_t>(task.status),
                                             task.userID);
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

TaskMeta CreatePlayerSettingTaskMeta(const std::string& firstPlayerID,
                                     const std::string& secondPlayerID)
{
    flatbuffers::FlatBufferBuilder builder(128);
    auto firstID = builder.CreateString(firstPlayerID);
    auto secondID = builder.CreateString(secondPlayerID);

    auto flat =
        FlatData::CreatePlayerSettingTaskMeta(builder, firstID, secondID);
    builder.Finish(flat);

    return TaskMeta(TaskMetaTrait(TaskID::USER_SETTING), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& meta, MetaData status,
                            BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(512);
    std::vector<flatbuffers::Offset<FlatData::Card>> burnt;

    // Conver burnt vector to FlatData::Card vector
    for (auto& card : meta.burnt)
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
                                  MetaData status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto manaTask = FlatData::CreateModifyManaTaskMeta(
        builder, meta.numMode, meta.manaMode, meta.object, meta.result);

    builder.Finish(manaTask);

    return TaskMeta(TaskMetaTrait(TaskID::MODIFY_MANA, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta,
                                    MetaData status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto card = CreateCard(builder, meta.card);
    auto healthTask = FlatData::CreateModifyHealthTaskMeta(
        builder, card, meta.damage, meta.hurted, meta.isExhausted);

    builder.Finish(healthTask);
    return TaskMeta(TaskMetaTrait(TaskID::MODIFY_HEALTH, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta, MetaData status,
                             BYTE userID)
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
                                      [&builder](Card* card) {
                                          return CreateCard(builder, card);
                                      });

                       return builder.CreateVector(dest);
                   });

    auto brief = FlatData::CreateBriefTaskMeta(
        builder, meta.currentPlayer, meta.opponentPlayer, meta.currentMana,
        meta.opponentMana, CreateCard(builder, meta.currentHero),
        CreateCard(builder, meta.opponentHero), result[0], result[1], result[2],
        meta.numOpponentHand, meta.numCurrentDeck, meta.numOpponentDeck,
        result[3], result[4]);

    builder.Finish(brief);
    return TaskMeta(TaskMetaTrait(TaskID::BRIEF, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait, Card* card,
                                    size_t position)
{
    flatbuffers::FlatBufferBuilder builder(128);
    auto flat = FlatData::CreateSummonMinionTaskMeta(
        builder, CreateCard(builder, card), static_cast<BYTE>(position));

    builder.Finish(flat);
    return TaskMeta(trait, builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, Card* src, Card* dst)
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
