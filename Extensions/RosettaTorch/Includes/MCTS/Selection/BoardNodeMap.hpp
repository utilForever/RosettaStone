// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP
#define ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP

#include <Rosetta/Commons/SpinLocks.hpp>
#include <Rosetta/Views/Board.hpp>
#include <Rosetta/Views/ReducedBoardView.hpp>

#include <memory>
#include <shared_mutex>
#include <unordered_map>

using namespace RosettaStone;

namespace RosettaTorch::MCTS
{
struct TreeNode;

//!
//! \brief BoardNodeMap class.
//!
class BoardNodeMap
{
    using MapType =
        std::unordered_map<ReducedBoardView, std::unique_ptr<TreeNode>>;

 public:
    TreeNode* GetOrCreateNode(const Board& board,
                              bool* newNodeCreated = nullptr);

    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        std::shared_lock<SharedSpinLock> lock(m_mutex);

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

    mutable SharedSpinLock m_mutex;
    std::unique_ptr<MapType> m_map;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP