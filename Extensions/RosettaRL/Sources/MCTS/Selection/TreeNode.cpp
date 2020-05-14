// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/TreeNode.hpp>

#include <cassert>

namespace RosettaTorch::MCTS
{
const EdgeAddon* ChildNodeMap::GetEdgeAddon(int choice) const
{
    return Get(choice).first;
}

std::tuple<bool, EdgeAddon*, TreeNode*> ChildNodeMap::GetOrCreateNewNode(
    int choice, std::unique_ptr<TreeNode> node)
{
    return GetOrCreate(choice,
                       [&](ChildType& child) { child.node = std::move(node); });
}

std::tuple<bool, EdgeAddon*, TreeNode*> ChildNodeMap::GetOrCreateRedirectNode(
    int choice)
{
    return GetOrCreate(
        choice, [](ChildType& child) { assert(child.node.get() == nullptr); });
}

bool ChildNodeMap::HasChild(int choice) const
{
    std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

    return (m_map.find(choice) != m_map.end());
}

std::pair<const EdgeAddon*, TreeNode*> ChildNodeMap::Get(int choice) const
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

template <class CreateFunctor>
std::tuple<bool, EdgeAddon*, TreeNode*> ChildNodeMap::GetOrCreate(
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
}  // namespace RosettaTorch::MCTS