// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
GameToVec::GameToVec()
{
    // Reproducibility
    m_seed = 1337u;
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Making embedding tables for the task
    const auto MakeTable = [&](torch::nn::Embedding embedding,
                               std::size_t idxSize, std::size_t vecSize) {
        embedding = torch::nn::Embedding(idxSize, vecSize);
        embedding->weight = torch::randn(
            { static_cast<int>(idxSize), static_cast<int>(vecSize) },
            torch::kFloat32);
        embedding->weight.set_requires_grad(false);
    };

    // Generates an embedding table for the Effect task
    MakeTable(m_effectEmbeddingTable, EffectIndexSize, EffectVectorSize);

    // Generates an embedding table for the TaskId
    MakeTable(m_taskIDEmbeddingTable, TaskIdIndexSize, TaskIdVectorSize);

    // Generates an embedding table for the EntityType
    MakeTable(m_entityTypeEmbeddingTable, EntityTypeIndexSize,
              EntityTypeVectorSize);
}

GameToVec::GameToVec(const std::size_t seed) : m_seed(seed)
{
    // Reproducibility
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Making embedding tables for the task
    const auto MakeTable = [&](torch::nn::Embedding embedding,
                               std::size_t idxSize, std::size_t vecSize) {
        embedding = torch::nn::Embedding(idxSize, vecSize);
        embedding->weight = torch::randn(
            { static_cast<int>(idxSize), static_cast<int>(vecSize) },
            torch::kFloat32);
        embedding->weight.set_requires_grad(false);
    };

    // Generates an embedding table for the Effect task
    MakeTable(m_effectEmbeddingTable, EffectIndexSize, EffectVectorSize);

    // Generates an embedding table for the TaskId
    MakeTable(m_taskIDEmbeddingTable, TaskIdIndexSize, TaskIdVectorSize);

    // Generates an embedding table for the EntityType
    MakeTable(m_entityTypeEmbeddingTable, EntityTypeIndexSize,
              EntityTypeVectorSize);
}

torch::Tensor GameToVec::EffectsToTensor(std::vector<Effect*> effects)
{
    const torch::Tensor effectVectors =
        torch::zeros({ static_cast<int>(effects.size()),
                       static_cast<int>(EffectVectorSize) });

    for (std::size_t i = 0; i < effects.size(); ++i)
    {
        auto effectGameTag = effects[i]->GetGameTag();
        auto effectOp = effects[i]->GetEffectOperator();
        // For preventing division by zero exception
        auto effectValue = static_cast<float>(effects[i]->GetValue()) + 1;

        // Getting index of the game tag
        const auto gameTagIter = std::find(EffectGameTag.begin(),
                                           EffectGameTag.end(), effectGameTag);
        const auto effectGameTagIdx =
            std::distance(EffectGameTag.begin(), gameTagIter);

        // Getting index of the effect operator
        const auto gameOpIter = std::find(EffectOperatorTag.begin(),
                                          EffectOperatorTag.end(), effectOp);
        const auto effectGameOpTagIdx =
            std::distance(EffectOperatorTag.begin(), gameOpIter);

        torch::Tensor idx = torch::zeros((1), torch::kInt8);
        idx.add(static_cast<int>(EffectOperationTagSize * effectGameTagIdx +
                                 effectGameOpTagIdx));

        // Normalize the value and multiple to the embedding vector
        effectValue = (effectValue >= CLIP_EFFECT_NORM)
                          ? 1.
                          : effectValue / CLIP_EFFECT_NORM;

        effectVectors[i] = m_effectEmbeddingTable(idx) / effectValue;
    }

    // Average all vectors (effects)
    auto effectVector = torch::mean(effectVectors);

    // excepted (4,) Tensor
    return effectVector;
}

torch::Tensor GameToVec::TasksToTensor(std::vector<ITask*> tasks)
{
    const torch::Tensor taskVectors = torch::empty(
        { static_cast<int>(tasks.size()), static_cast<int>(TaskVectorSize) });

    for (std::size_t i = 0; i < tasks.size(); ++i)
    {
        auto taskID = tasks[i]->GetTaskID();
        auto entityType = tasks[i]->GetEntityType();

        torch::Tensor taskIDIndex = torch::zeros((1), torch::kInt8);
        taskIDIndex.add(static_cast<int>(taskID));

        torch::Tensor entityIndex = torch::zeros((1), torch::kInt8);
        entityIndex.add(static_cast<int>(entityType));

        const auto taskIDEmbed = m_taskIDEmbeddingTable(taskIDIndex);
        const auto entityTypeEmbed = m_entityTypeEmbeddingTable(entityIndex);

        // Concatenating two vectors
        const auto embeddings = torch::cat({ taskIDEmbed, entityTypeEmbed });

        taskVectors[i] = embeddings;
    }

    // Average all vectors (tasks)
    auto taskVector = torch::mean(taskVectors);

    // excepted (8,) Tensor
    return taskVector;
}

torch::Tensor GameToVec::CardToTensor(Entity* entity)
{
    torch::Tensor cardVector = torch::empty(CardVectorSize, torch::kFloat32);

    auto* character = dynamic_cast<Character*>(entity);

    const auto cost = static_cast<float>(character->GetCost());
    const auto attack = static_cast<float>(character->GetAttack());
    const auto health = static_cast<float>(character->GetHealth());

    // Write cost of the card
    cardVector[0] = cost / MANA_UPPER_LIMIT;

    // Write attack of the card
    cardVector[1] = (attack >= CLIP_CARD_NORM) ? 1. : attack / CLIP_CARD_NORM;

    // Write health of the card
    cardVector[2] = (health >= CLIP_CARD_NORM) ? 1. : health / CLIP_CARD_NORM;

    const auto AuraToVector = [&](Aura* aura) -> torch::Tensor {
        if (!aura)
        {
            return torch::zeros(AuraVectorSize);
        }

        torch::Tensor auraVector =
            torch::empty(AuraVectorSize, torch::kFloat32);

        auto type = aura->GetAuraType();
        const auto effects = aura->GetEffects();

        auraVector[0] = static_cast<float>(type);

        const auto effectVector = EffectsToTensor(effects);
        for (size_t i = 0; i < EffectVectorSize; ++i)
        {
            auraVector[1 + i] = effectVector[i];
        }

        return auraVector;
    };

    const auto EnchantToVector =
        [&](Enchant* enchant) -> torch::Tensor {
        if (!enchant)
        {
            return torch::zeros(EnchantVectorSize);
        }

        // Enchant only has the 'Effect' task
        auto effectsVector = EffectsToTensor(enchant->effects);

        return effectsVector;
    };

    const auto WriteVector = [&](size_t startIdx, size_t vecSize,
                                 const torch::Tensor& tensor) {
        for (size_t i = startIdx; i < startIdx + vecSize; ++i)
        {
            cardVector[i] = tensor[i];
        }
    };

    auto ability = character->card->power;

    auto aura = ability.GetAura();
    const auto enchant = ability.GetEnchant();
    const auto deathrattle = ability.GetDeathrattleTask();
    const auto power = ability.GetPowerTask();

    // Write aura vector
    const auto auraVector = AuraToVector(aura);
    WriteVector(3, AuraVectorSize, auraVector);

    // Write enchant vector
    const auto enchantVector = EnchantToVector(enchant);
    WriteVector(3 + AuraVectorSize, EnchantVectorSize, enchantVector);

    // Write deathrattle vector
    const auto deathrattleVector = TasksToTensor(deathrattle);
    WriteVector(3 + AuraVectorSize + EnchantVectorSize, TaskVectorSize,
                deathrattleVector);

    // Write power vector
    const auto powerVector = TasksToTensor(power);
    WriteVector(3 + AuraVectorSize + EnchantVectorSize + TaskVectorSize,
                TaskVectorSize, powerVector);

    return cardVector;
}

torch::Tensor GameToVec::GenerateTensor(Game& game)
{
    // vector shape : [1 + 1 + 1 + n * 7 + n * 7 + n * 10 = 3 + n * 24 = 675]
    // # 1      : number of opponent player's cards on hand.
    // # 1      : number of opponent player's left cards at deck.
    // # 1      : number of current player's left cards at deck.
    // # n * 7  : opponent player's representation vectors of card at the deck.
    //            each card has a dimensionality of n.
    // # n * 7  : current player's representation vectors of card at the deck.
    //            each card has a dimensionality of n.
    // # n * 10 : current player's representation vectors of card in the hand.
    //            each card has a dimensionality of n.

    // each card is represented as a vector which has n dimensionality.
    // it includes, cost, attack, health, ability.
    // vector shape : [1 + 1 + 1 + 25 = n = 28]
    // # 1  : cost
    // # 1  : attack
    // # 1  : health
    // # 25 : ability

    // each card's abilities are represented as a vector which has m
    // dimensionality. it includes, ... vector shape : [m]
    // vector shape : [5 + 4 + 8 + 8 = m = 25]
    // # 5 : Aura Vector
    // # 4 : Enchant Vector
    // # 8 : Deathrattle Vector
    // # 8 : Power Vector
    torch::Tensor tensor = torch::empty(GameVectorSize, torch::kFloat32);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    // Write number of opponent player's cards, normalized, on the hand.
    tensor[0] =
        static_cast<float>(opPlayer.GetHandZone().GetCount()) / MAX_HAND_SIZE;

    // Write number of opponent player's cards, normalized, on the deck.
    tensor[1] =
        static_cast<float>(opPlayer.GetDeckZone().GetCount()) / MAX_DECK_SIZE;

    // Write number of current player's cards, normalized, on the deck.
    tensor[2] =
        static_cast<float>(curPlayer.GetDeckZone().GetCount()) / MAX_DECK_SIZE;

    const auto FieldWrite = [&](std::size_t start, Player& player) {
        auto field = player.GetFieldZone();
        const int numOfMinions = field.GetCount();

        int i = 0;
        for (; i < numOfMinions; ++i)
        {
            tensor[start + i] = CardToTensor(field[i]);
        }

        for (; i < MAX_FIELD_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    const auto HandWrite = [&](std::size_t start, Player& player) {
        auto hand = player.GetHandZone();
        const int numOfCards = hand.GetCount();

        int i = 0;
        for (; i < numOfCards; ++i)
        {
            tensor[start + i] = CardToTensor(hand[i]);
        }

        for (; i < MAX_HAND_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    // Write opponent player's field cards
    FieldWrite(PlayerMetaSize, opPlayer);

    // Write current player's field cards
    FieldWrite(PlayerMetaSize + 1 * MAX_FIELD_SIZE, curPlayer);

    // Write current player's hand cards
    HandWrite(PlayerMetaSize + 2 * MAX_FIELD_SIZE, curPlayer);

    return tensor;
}

torch::nn::Embedding GameToVec::GetEffectEmbeddingTable() const
{
    return m_effectEmbeddingTable;
}

torch::nn::Embedding GameToVec::GetEntityTypeEmbeddingTable()
{
    return m_entityTypeEmbeddingTable;
}

torch::nn::Embedding GameToVec::GetTaskIDEmbeddingTable() const
{
    return m_taskIDEmbeddingTable;
}
}  // namespace RosettaTorch