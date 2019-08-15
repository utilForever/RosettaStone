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

#include <functional>
#include <memory>
#include <shared_mutex>
#include <unordered_map>

using namespace RosettaStone;

namespace RosettaTorch::MCTS
{
struct TreeNode;

using MapType = std::unordered_map<ReducedBoardView, std::unique_ptr<TreeNode>>;

//!
//! \brief BoardNodeMap class.
//!
//! This class stores several boards that are reduced by hash function.
//!
class BoardNodeMap
{
 public:
    //! Creates an new node or returns an node if the board already exists.
    //! \param board The game board.
    //! \param newNodeCreated The flag indicates whether to create new node.
    //! \return An node that is newly created or is already existed.
    TreeNode* GetOrCreateNode(const Board& board,
                              bool* newNodeCreated = nullptr);

    //! Runs \p functor on each element of the map.
    //! \param functor A function to run for each element.
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
    //! Returns the map that stores several boards.
    //! \return The map that stores several boards.
    MapType& GetLockedMap();

    mutable SharedSpinLock m_mutex;
    std::unique_ptr<MapType> m_map;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_HPP