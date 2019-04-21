// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/Tasks.hpp>
#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
GameToVec::GameToVec(size_t seed) : m_seed(seed)
{
    // Reproducibility
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Making embedding tables for the task
    auto make_table = [&](torch::nn::Embedding embedding, size_t idx_size, size_t vec_size) {
        embedding = torch::nn::Embedding(idx_size, vec_size);
        embedding->weight = torch::randn(
            { static_cast<int>(idx_size), static_cast<int>(vec_size) },
            torch::kFloat32
        );
        embedding->weight.set_requires_grad(false);
    };

    // Generates an embedding table for the Effect task
    make_table(EffectEmbeddingTable, EffectIndexSize, EffectVectorSize);

    // Generates an embedding table for the TaskId
    make_table(TaskIdEmbeddingTable, TaskIdIndexSize, TaskIdVectorSize);

    // Generates an embedding table for the EntityType
    make_table(EntityTypeEmbeddingTable, EntityTypeIndexSize, EntityTypeVectorSize);
}

torch::Tensor GameToVec::EffectsToTensor(std::vector<Effect> effects)
{
    torch::Tensor EffectVectors = torch::zeros(
        { static_cast<int>(effects.size()), static_cast<int>(EffectVectorSize) }
    );

    for (size_t i = 0; i < effects.size(); ++i)
    {
        auto effect_game_tag = effects[i].GetGameTag();
        auto effect_op = effects[i].GetEffectOperator();
        // For preventing division by zero exception
        auto effect_value = static_cast<float>(effects[i].GetValue()) + 1;

        // Getting index of the game tag
        std::vector<GameTag>::iterator game_tag_it =
            std::find(EffectGameTag.begin(), EffectGameTag.end(), effect_game_tag);
        auto effect_game_tag_idx =
            std::distance(EffectGameTag.begin(), game_tag_it);

        // Getting index of the effect operator
        std::vector<EffectOperator>::iterator game_op_it = std::find(
            EffectOperatorTag.begin(), EffectOperatorTag.end(), effect_op);
        auto effect_game_op_tag_idx =
            std::distance(EffectOperatorTag.begin(), game_op_it);

        torch::Tensor index = torch::zeros((1), torch::kInt8);
        index.add(
            static_cast<int>(EffectOperationTagSize * effect_game_tag_idx +
                             effect_game_op_tag_idx));

        // Normalize the value and multiple to the embedding vector
        effect_value = (effect_value >= CLIP_EFFECT_NORM)
                           ? 1.
                           : effect_value / CLIP_EFFECT_NORM;

        EffectVectors[i] = EffectEmbeddingTable(index) / effect_value;
    }
    
    // Average all vectors (effects)
    auto EffectVector = torch::mean(EffectVectors);

    // excepted (4,) Tensor
    return EffectVector;
}

torch::Tensor GameToVec::TasksToTensor(std::vector<ITask*> tasks)
{
    torch::Tensor task_vectors = torch::empty(
        { static_cast<int>(tasks.size()), static_cast<int>(TaskVectorSize) }
    );

    for (size_t i = 0; i < tasks.size(); ++i)
    {
        auto task_id = tasks[i]->GetTaskID();
        auto entity_type = tasks[i]->GetEntityType();

        torch::Tensor task_id_index = torch::zeros((1), torch::kInt8);
        task_id_index.add(static_cast<int>(task_id));

        torch::Tensor entity_index = torch::zeros((1), torch::kInt8);
        entity_index.add(static_cast<int>(entity_type));

        auto task_id_embed = TaskIdEmbeddingTable(task_id_index);
        auto entity_type_embed = EntityTypeEmbeddingTable(entity_index);

        // Concatenating two vectors
        auto embeddings = torch::cat({task_id_embed, entity_type_embed});

        task_vectors[i] = embeddings;
    }

    // Average all vectors (tasks)
    auto task_vector = torch::mean(task_vectors);

    // excepted (4,) Tensor
    return task_vector;
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

        torch::Tensor aura_vector = torch::empty(AuraVectorSize, torch::kFloat32);

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

    auto EnchantToVector = [&](std::optional<Enchant> enchant) -> torch::Tensor {
        if (!enchant.has_value())
        {
            return torch::zeros(EnchantVectorSize);
        }

        // Enchant only has the 'Effect' task
        auto effects_vector = EffectsToTensor(enchant->effects);

        return effects_vector;
    };

    auto write_vector = [&](size_t start_idx, size_t vec_size, torch::Tensor tensor) {
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
    auto aura_vector = AuraToVector(aura);
    write_vector(3,
        AuraVectorSize, aura_vector);

    // Write EnchantVector
    auto enchant_vector = EnchantToVector(enchant);
    write_vector(3 + AuraVectorSize,
        EnchantVectorSize, enchant_vector);

    // Write DeathrattleVector
    auto deathrattle_vector = TasksToTensor(deathrattle);
    write_vector(3 + AuraVectorSize + EnchantVectorSize,
        TaskVectorSize, deathrattle_vector);

    // Write PowerVector
    auto power_vector = TasksToTensor(power);
    write_vector(3 + AuraVectorSize + EnchantVectorSize + TaskVectorSize,
        TaskVectorSize, power_vector);

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
    // # 1 : cost
    // # 1 : attack
    // # 1 : health
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
    Player& oppPlayer = game.GetOpponentPlayer();

    // Write number of opponent player's cards, normalized, on the hand.
    tensor[0] =
        static_cast<float>(oppPlayer.GetHand().GetNumOfCards()) / HAND_SIZE;

    // Write number of opponent player's cards, normalized, on the deck.
    tensor[1] =
        static_cast<float>(oppPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    // Write number of current player's cards, normalized, on the deck.
    tensor[2] =
        static_cast<float>(curPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    auto field_write = [&](size_t start, Player& player) {
        auto field = player.GetField();
        size_t NumOfMinions = field.GetNumOfMinions();

        size_t i = 0;
        for (; i < NumOfMinions; ++i)
        {
           tensor[start + i] = CardToTensor(field.GetMinion(i));
        }

        for (; i < FIELD_SIZE; ++i)
        {
            tensor[start + i] = torch::zeros(CardVectorSize);
        }
    };

    auto hand_write = [&](size_t start, Player& player) {
        auto hand = player.GetHand();
        size_t NumOfCards = hand.GetNumOfCards();

        size_t i = 0;
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
    field_write(PlayerMetaSize, oppPlayer);

    // Write current player's field cards
    field_write(PlayerMetaSize + 1 * FIELD_SIZE, curPlayer);

    // Write current player's hand cards
    hand_write(PlayerMetaSize + 2 * FIELD_SIZE, curPlayer);

    return tensor;
}
}  // namespace RosettaTorch