// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP
#define ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP

#include <Rosetta/Commons/SpinLocks.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Views/ReducedBoardView.hpp>

#include <memory>
#include <shared_mutex>
#include <unordered_map>

namespace RosettaTorch::MCTS
{
struct TreeNode;

//!
//! \brief BoardNodeMap class.
//!
class BoardNodeMap
{
    using MapType = std::unordered_map<RosettaStone::ReducedBoardView,
                                       std::unique_ptr<TreeNode>>;

 public:
    TreeNode* GetOrCreateNode(const RosettaStone::Game& game,
                              bool* newNodeCreated = nullptr);

    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mutex);

        if (!m_map)
        {
            return;
        }

        for (const auto& kv : *m_map)
        {
            if (!functor(kv.first, kv.second.get()))
            {
                return;
            }
        }
    }

 private:
    MapType& GetLockedMap()
    {
        if (!m_map)
        {
            m_map.reset(new MapType());
        }

        return *m_map;
    }

    mutable RosettaStone::SharedSpinLock m_mutex;
    std::unique_ptr<MapType> m_map;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP