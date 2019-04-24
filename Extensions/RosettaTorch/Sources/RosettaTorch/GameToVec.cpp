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
    auto make_table = [&](torch::nn::Embedding embedding, std::size_t idx_size,
                          std::size_t vec_size) {
        embedding = torch::nn::Embedding(idx_size, vec_size);
        embedding->weight = torch::randn(
            { static_cast<int>(idx_size), static_cast<int>(vec_size) },
            torch::kFloat32);
        embedding->weight.set_requires_grad(false);
    };

    // Generates an embedding table for the Effect task
    make_table(m_effectEmbeddingTable, EffectIndexSize, EffectVectorSize);

    // Generates an embedding table for the TaskId
    make_table(m_taskIDEmbeddingTable, TaskIdIndexSize, TaskIdVectorSize);

    // Generates an embedding table for the EntityType
    make_table(m_entityTypeEmbeddingTable, EntityTypeIndexSize,
               EntityTypeVectorSize);
}

GameToVec::GameToVec(const std::size_t seed) : m_seed(seed)
{
    // Reproducibility
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Making embedding tables for the task
    auto make_table = [&](torch::nn::Embedding embedding, std::size_t idx_size,
                          std::size_t vec_size) {
        embedding = torch::nn::Embedding(idx_size, vec_size);
        embedding->weight = torch::randn(
            { static_cast<int>(idx_size), static_cast<int>(vec_size) },
            torch::kFloat32);
        embedding->weight.set_requires_grad(false);
    };

    // Generates an embedding table for the Effect task
    make_table(m_effectEmbeddingTable, EffectIndexSize, EffectVectorSize);

    // Generates an embedding table for the TaskId
    make_table(m_taskIDEmbeddingTable, TaskIdIndexSize, TaskIdVectorSize);

    // Generates an embedding table for the EntityType
    make_table(m_entityTypeEmbeddingTable, EntityTypeIndexSize,
               EntityTypeVectorSize);
}

torch::Tensor GameToVec::EffectsToTensor(std::vector<Effect> effects)
{
    torch::Tensor EffectVectors =
        torch::zeros({ static_cast<int>(effects.size()),
                       static_cast<int>(EffectVectorSize) });

    for (std::size_t i = 0; i < effects.size(); ++i)
    {
        auto EffectGameTag_ = effects[i].GetGameTag();
        auto EffectOp = effects[i].GetEffectOperator();
        // For preventing division by zero exception
        auto EffectValue = static_cast<float>(effects[i].GetValue()) + 1;

        // Getting index of the game tag
        std::vector<GameTag>::iterator GameTagIter = std::find(
            EffectGameTag.begin(), EffectGameTag.end(), EffectGameTag_);
        auto EffectGameTagIdx =
            std::distance(EffectGameTag.begin(), GameTagIter);

        // Getting index of the effect operator
        std::vector<EffectOperator>::iterator GameOpIter = std::find(
            EffectOperatorTag.begin(), EffectOperatorTag.end(), EffectOp);
        auto EffectGameOpTagIdx =
            std::distance(EffectOperatorTag.begin(), GameOpIter);

        torch::Tensor index = torch::zeros((1), torch::kInt8);
        index.add(
            static_cast<int>(EffectOperationTagSize * EffectGameTagIdx +
                             EffectGameOpTagIdx));

        // Normalize the value and multiple to the embedding vector
        EffectValue = (EffectValue >= CLIP_EFFECT_NORM)
                           ? 1.
                           : EffectValue / CLIP_EFFECT_NORM;

        EffectVectors[i] = m_effectEmbeddingTable(index) / EffectValue;
    }

    // Average all vectors (effects)
    auto EffectVector = torch::mean(EffectVectors);

    // excepted (4,) Tensor
    return EffectVector;
}

torch::Tensor GameToVec::TasksToTensor(std::vector<ITask*> tasks)
{
    torch::Tensor TaskVectors = torch::empty(
        { static_cast<int>(tasks.size()), static_cast<int>(TaskVectorSize) });

    for (std::size_t i = 0; i < tasks.size(); ++i)
    {
        auto task_id = tasks[i]->GetTaskID();
        auto entity_type = tasks[i]->GetEntityType();

        torch::Tensor TaskIDIndex = torch::zeros((1), torch::kInt8);
        TaskIDIndex.add(static_cast<int>(task_id));

        torch::Tensor EntityIndex = torch::zeros((1), torch::kInt8);
        EntityIndex.add(static_cast<int>(entity_type));

        auto TaskIDEmbed = m_taskIDEmbeddingTable(TaskIDIndex);
        auto EntityTypeEmbed = m_entityTypeEmbeddingTable(EntityIndex);

        // Concatenating two vectors
        auto Embeddings = torch::cat({ TaskIDEmbed, EntityTypeEmbed });

        TaskVectors[i] = Embeddings;
    }

    // Average all vectors (tasks)
    auto TaskVector = torch::mean(TaskVectors);

    // excepted (8,) Tensor
    return TaskVector;
}

torch::Tensor GameToVec::CardToTensor(Entity* entity)
{
    torch::Tensor CardVector = torch::empty(CardVectorSize, torch::kFloat32);

    Character* character = dynamic_cast<Character*>(entity);

    auto cost = static_cast<float>(character->GetCost());
    auto attack = static_cast<float>(character->GetAttack());
    auto health = static_cast<float>(character->GetHealth());

    // Write cost of the card
    CardVector[0] = cost / MANA_UPPER_LIMIT;

    // Write attack of the card
    CardVector[1] = (attack >= CLIP_CARD_NORM) ? 1. : attack / CLIP_CARD_NORM;

    // Write health of the card
    CardVector[2] = (health >= CLIP_CARD_NORM) ? 1. : health / CLIP_CARD_NORM;

    auto AuraToVector = [&](std::optional<Aura> aura) -> torch::Tensor {
        if (!aura.has_value())
        {
            return torch::zeros(AuraVectorSize);
        }

        torch::Tensor aura_vector =
            torch::empty(AuraVectorSize, torch::kFloat32);

        auto type = aura->GetAuraType();
        auto effects = aura->GetEffects();

        aura_vector[0] = static_cast<float>(type);

        auto effect_vector = EffectsToTensor(effects);
        for (size_t i = 0; i < EffectVectorSize; ++i)
        {
            aura_vector[1 + i] = effect_vector[i];
        }

        return aura_vector;
    };

    auto EnchantToVector =
        [&](std::optional<Enchant> enchant) -> torch::Tensor {
        if (!enchant.has_value())
        {
            return torch::zeros(EnchantVectorSize);
        }

        // Enchant only has the 'Effect' task
        auto effects_vector = EffectsToTensor(enchant->effects);

        return effects_vector;
    };

    auto write_vector = [&](size_t start_idx, size_t vec_size,
                            torch::Tensor tensor) {
        for (size_t i = start_idx; i < start_idx + vec_size; ++i)
        {
            CardVector[i] = tensor[i];
        }
    };

    auto ability = character->card.power;

    auto aura = ability.GetAura();
    auto enchant = ability.GetEnchant();
    auto deathrattle = ability.GetDeathrattleTask();
    auto power = ability.GetPowerTask();

    // Write AuraVector
    auto AuraVector = AuraToVector(aura);
    write_vector(3, AuraVectorSize, AuraVector);

    // Write EnchantVector
    auto EnchantVector = EnchantToVector(enchant);
    write_vector(3 + AuraVectorSize, EnchantVectorSize, EnchantVector);

    // Write DeathrattleVector
    auto DeathrattleVector = TasksToTensor(deathrattle);
    write_vector(3 + AuraVectorSize + EnchantVectorSize, TaskVectorSize,
                 DeathrattleVector);

    // Write PowerVector
    auto PowerVector = TasksToTensor(power);
    write_vector(3 + AuraVectorSize + EnchantVectorSize + TaskVectorSize,
                 TaskVectorSize, PowerVector);

    return CardVector;
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

    Player& CurPlayer = game.GetCurrentPlayer();
    Player& OppPlayer = game.GetOpponentPlayer();

    // Write number of opponent player's cards, normalized, on the hand.
    tensor[0] =
        static_cast<float>(OppPlayer.GetHand().GetNumOfCards()) / HAND_SIZE;

    // Write number of opponent player's cards, normalized, on the deck.
    tensor[1] =
        static_cast<float>(OppPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    // Write number of current player's cards, normalized, on the deck.
    tensor[2] =
        static_cast<float>(CurPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    auto field_write = [&](std::size_t start, Player& player) {
        auto field = player.GetField();
        std::size_t NumOfMinions = field.GetNumOfMinions();

        std::size_t i = 0;
        for (; i < NumOfMinions; ++i)
        {
            tensor[start + i] = CardToTensor(field.GetMinion(i));
        }

        for (; i < FIELD_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    auto hand_write = [&](std::size_t start, Player& player) {
        auto hand = player.GetHand();
        std::size_t NumOfCards = hand.GetNumOfCards();

        std::size_t i = 0;
        for (; i < NumOfCards; ++i)
        {
            tensor[start + i] = CardToTensor(hand.GetCard(i));
        }

        for (; i < HAND_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    // Write opponent player's field cards
    field_write(PlayerMetaSize, OppPlayer);

    // Write current player's field cards
    field_write(PlayerMetaSize + 1 * FIELD_SIZE, CurPlayer);

    // Write current player's hand cards
    hand_write(PlayerMetaSize + 2 * FIELD_SIZE, CurPlayer);

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