// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/BoardNodeMap.hpp>
#include <MCTS/Selection/TreeNode.hpp>

namespace RosettaTorch::MCTS
{
using MapType = std::unordered_map<ReducedBoardView, std::unique_ptr<TreeNode>>;

TreeNode* BoardNodeMap::GetOrCreateNode(const Board& board,
                                        bool* newNodeCreated)
{
    const auto boardView = board.CreateView();

    {
        std::shared_lock<SharedSpinLock> lock(m_mutex);

        if (m_map)
        {
            const auto it = m_map->find(boardView);
            if (it != m_map->end())
            {
                return it->second.get();
            }
        }
    }

    {
        std::lock_guard<SharedSpinLock> lock(m_mutex);
        auto& item = GetLockedMap()[boardView];
        if (!item)
        {
            item.reset(new TreeNode());

            if (newNodeCreated)
            {
                *newNodeCreated = true;
            }
        }

        return item.get();
    }
}

MapType& BoardNodeMap::GetLockedMap()
{
    if (!m_map)
    {
        m_map.reset(new MapType());
    }

    return *m_map;
}
}  // namespace RosettaTorch::MCTS