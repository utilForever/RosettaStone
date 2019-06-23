// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP

#include "EdgeAddon.hpp"
#include "TreeNodeAddon.hpp"

namespace RosettaTorch::MCTS
{
//!
//! \brief ChildNodeMap class.
//!
//! NOTE: This is not thread safe. Do not expose it to outside!
//!
class ChildNodeMap
{
 public:
    const EdgeAddon* GetEdgeAddon(int choice) const
    {
        return Get(choice).first;
    }

    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreateNewNode(
        int choice, std::unique_ptr<TreeNode> node)
    {
        return GetOrCreate(
            choice, [&](ChildType& child) { child.node = std::move(node); });
    }
    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreateRedirectNode(int choice)
    {
        return GetOrCreate(choice, [](ChildType& child) {
            assert(child.node.get() == nullptr);
        });
    }

    bool HasChild(int choice) const
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

        return (m_map.find(choice) != m_map.end());
    }

    std::pair<EdgeAddon const*, TreeNode*> Get(int choice) const
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

        const auto it = m_map.find(choice);
        if (it == m_map.end())
        {
            return { nullptr, nullptr };
        }
        else
        {
            return { &it->second.edgeAddon, it->second.node.get() };
        }
    }

    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

        for (auto const& kv : m_map)
        {
            if (!functor(kv.first, &kv.second.edgeAddon, kv.second.node.get()))
            {
                return;
            }
        }
    }

    template <typename Functor>
    void ForEach(Functor&& functor)
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

        for (auto& kv : m_map)
        {
            if (!functor(kv.first, &kv.second.edgeAddon, kv.second.node.get()))
            {
                return;
            }
        }
    }

 private:
    template <class CreateFunctor>
    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreate(
        int choice, CreateFunctor&& createChildFunctor)
    {
        {
            std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

            auto it = m_map.find(choice);
            if (it != m_map.end())
            {
                return { false, &it->second.edgeAddon, it->second.node.get() };
            }
        }

        {
            std::lock_guard<RosettaStone::SharedSpinLock> writeLock(m_mapMutex);

            auto it = m_map.find(choice);
            if (it != m_map.end())
            {
                return { false, &it->second.edgeAddon, it->second.node.get() };
            }

            auto& child = m_map[choice];
            createChildFunctor(child);

            return { true, &child.edgeAddon, child.node.get() };
        }
    }

    struct ChildType
    {
        EdgeAddon edgeAddon;
        std::unique_ptr<TreeNode> node;
    };

    mutable RosettaStone::SharedSpinLock m_mapMutex;
    std::unordered_map<int, ChildType> m_map;
};

//!
//! \brief TreeNode struct.
//!
struct TreeNode
{
    ChildNodeMap children;
    TreeNodeAddon addon;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP