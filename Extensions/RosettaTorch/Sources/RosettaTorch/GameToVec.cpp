// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/Tasks.hpp>
#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
GameToVec::GameToVec()
{
    // Reproducibility
    m_seed = 1337u;
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Making embedding tables for the task
    auto MakeTable = [&](torch::nn::Embedding embedding, std::size_t idx_size,
                         std::size_t vec_size) {
        embedding = torch::nn::Embedding(idx_size, vec_size);
        embedding->weight = torch::randn(
            { static_cast<int>(idx_size), static_cast<int>(vec_size) },
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
    auto MakeTable = [&](torch::nn::Embedding embedding, std::size_t idx_size,
                         std::size_t vec_size) {
        embedding = torch::nn::Embedding(idx_size, vec_size);
        embedding->weight = torch::randn(
            { static_cast<int>(idx_size), static_cast<int>(vec_size) },
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

torch::Tensor GameToVec::EffectsToTensor(std::vector<Effect> effects)
{
    torch::Tensor effectVectors =
        torch::zeros({ static_cast<int>(effects.size()),
                       static_cast<int>(EffectVectorSize) });

    for (std::size_t i = 0; i < effects.size(); ++i)
    {
        auto effectGameTag = effects[i].GetGameTag();
        auto effectOp = effects[i].GetEffectOperator();
        // For preventing division by zero exception
        auto effectValue = static_cast<float>(effects[i].GetValue()) + 1;

        // Getting index of the game tag
        std::vector<GameTag>::iterator gameTagIter = std::find(
            EffectGameTag.begin(), EffectGameTag.end(), effectGameTag);
        auto effectGameTagIdx =
            std::distance(EffectGameTag.begin(), gameTagIter);

        // Getting index of the effect operator
        std::vector<EffectOperator>::iterator gameOpIter = std::find(
            EffectOperatorTag.begin(), EffectOperatorTag.end(), effectOp);
        auto effectGameOpTagIdx =
            std::distance(EffectOperatorTag.begin(), gameOpIter);

        torch::Tensor idx = torch::zeros((1), torch::kInt8);
        idx.add(
            static_cast<int>(EffectOperationTagSize * effectGameTagIdx +
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
    torch::Tensor taskVectors = torch::empty(
        { static_cast<int>(tasks.size()), static_cast<int>(TaskVectorSize) });

    for (std::size_t i = 0; i < tasks.size(); ++i)
    {
        auto taskID = tasks[i]->GetTaskID();
        auto entityType = tasks[i]->GetEntityType();

        torch::Tensor taskIDIndex = torch::zeros((1), torch::kInt8);
        taskIDIndex.add(static_cast<int>(taskID));

        torch::Tensor entityIndex = torch::zeros((1), torch::kInt8);
        entityIndex.add(static_cast<int>(entityType));

        auto taskIDEmbed = m_taskIDEmbeddingTable(taskIDIndex);
        auto entityTypeEmbed = m_entityTypeEmbeddingTable(entityIndex);

        // Concatenating two vectors
        auto embeddings = torch::cat({ taskIDEmbed, entityTypeEmbed });

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

    Character* character = dynamic_cast<Character*>(entity);

    auto cost = static_cast<float>(character->GetCost());
    auto attack = static_cast<float>(character->GetAttack());
    auto health = static_cast<float>(character->GetHealth());

    // Write cost of the card
    cardVector[0] = cost / MANA_UPPER_LIMIT;

    // Write attack of the card
    cardVector[1] = (attack >= CLIP_CARD_NORM) ? 1. : attack / CLIP_CARD_NORM;

    // Write health of the card
    cardVector[2] = (health >= CLIP_CARD_NORM) ? 1. : health / CLIP_CARD_NORM;

    auto AuraToVector = [&](std::optional<Aura> aura) -> torch::Tensor {
        if (!aura.has_value())
        {
            return torch::zeros(AuraVectorSize);
        }

        torch::Tensor auraVector =
            torch::empty(AuraVectorSize, torch::kFloat32);

        auto type = aura->GetAuraType();
        auto effects = aura->GetEffects();

        auraVector[0] = static_cast<float>(type);

        auto effectVector = EffectsToTensor(effects);
        for (size_t i = 0; i < EffectVectorSize; ++i)
        {
            auraVector[1 + i] = effectVector[i];
        }

        return auraVector;
    };

    auto EnchantToVector =
        [&](std::optional<Enchant> enchant) -> torch::Tensor {
        if (!enchant.has_value())
        {
            return torch::zeros(EnchantVectorSize);
        }

        // Enchant only has the 'Effect' task
        auto effectsVector = EffectsToTensor(enchant->effects);

        return effectsVector;
    };

    auto WriteVector = [&](size_t start_idx, size_t vec_size,
                            torch::Tensor tensor) {
        for (size_t i = start_idx; i < start_idx + vec_size; ++i)
        {
            cardVector[i] = tensor[i];
        }
    };

    auto ability = character->card.power;

    auto aura = ability.GetAura();
    auto enchant = ability.GetEnchant();
    auto deathrattle = ability.GetDeathrattleTask();
    auto power = ability.GetPowerTask();

    // Write AuraVector
    auto AuraVector = AuraToVector(aura);
    WriteVector(3, AuraVectorSize, AuraVector);

    // Write EnchantVector
    auto EnchantVector = EnchantToVector(enchant);
    WriteVector(3 + AuraVectorSize, EnchantVectorSize, EnchantVector);

    // Write DeathrattleVector
    auto DeathrattleVector = TasksToTensor(deathrattle);
    WriteVector(3 + AuraVectorSize + EnchantVectorSize, TaskVectorSize,
                 DeathrattleVector);

    // Write PowerVector
    auto PowerVector = TasksToTensor(power);
    WriteVector(3 + AuraVectorSize + EnchantVectorSize + TaskVectorSize,
                 TaskVectorSize, PowerVector);

    return cardVector;
}

torch::Tensor GameToVec::GenerateTensor(const Game& game)
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
        static_cast<float>(opPlayer.GetHand().GetNumOfCards()) / HAND_SIZE;

    // Write number of opponent player's cards, normalized, on the deck.
    tensor[1] =
        static_cast<float>(opPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    // Write number of current player's cards, normalized, on the deck.
    tensor[2] =
        static_cast<float>(curPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    auto FieldWrite = [&](std::size_t start, Player& player) {
        auto field = player.GetField();
        std::size_t numOfMinions = field.GetNumOfMinions();

        std::size_t i = 0;
        for (; i < numOfMinions; ++i)
        {
            tensor[start + i] = CardToTensor(field.GetMinion(i));
        }

        for (; i < FIELD_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    auto HandWrite = [&](std::size_t start, Player& player) {
        auto hand = player.GetHand();
        std::size_t numOfCards = hand.GetNumOfCards();

        std::size_t i = 0;
        for (; i < numOfCards; ++i)
        {
            tensor[start + i] = CardToTensor(hand.GetCard(i));
        }

        for (; i < HAND_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    // Write opponent player's field cards
    FieldWrite(PlayerMetaSize, opPlayer);

    // Write current player's field cards
    FieldWrite(PlayerMetaSize + 1 * FIELD_SIZE, curPlayer);

    // Write current player's hand cards
    HandWrite(PlayerMetaSize + 2 * FIELD_SIZE, curPlayer);

    return tensor;
}

torch::nn::Embedding GameToVec::GetEffectEmbeddingTable()
{
    return m_effectEmbeddingTable;
}

torch::nn::Embedding GameToVec::GetEntityTypeEmbeddingTable()
{
    return m_entityTypeEmbeddingTable;
}

torch::nn::Embedding GameToVec::GetTaskIdEmbeddingTable()
{
    return m_taskIDEmbeddingTable;
}
}  // namespace RosettaTorch