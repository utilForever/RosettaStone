// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP

#include <MCTS/Selection/EdgeAddon.hpp>
#include <MCTS/Selection/TreeNodeAddon.hpp>

#include <Rosetta/Common/SpinLocks.hpp>

#include <functional>
#include <memory>
#include <tuple>
#include <unordered_map>

namespace RosettaTorch::MCTS
{
struct TreeNode;

//!
//! \brief ChildNodeMap class.
//!
//! This class stores several child nodes and has shared spin lock to run in
//! multi-thread. Note that this class is not thread safe. Do not expose it to
//! outside!
//!
class ChildNodeMap
{
 public:
    //! Returns the edge addon of child node.
    //! \param choice The index of child node.
    //! \return The edge addon of child node.
    const EdgeAddon* GetEdgeAddon(int choice) const;

    //! Creates an new child node or returns a child node if it exists.
    //! \param choice The index of child node.
    //! \param node A node of child node.
    //! \return First element is the flag indicates whether to create new node.
    //! Second element is the edge addon of child node. Third element is an
    //! child node that is newly created or is already existed.
    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreateNewNode(
        int choice, std::unique_ptr<TreeNode> node);

    //! Creates an redirect child node or returns a child node if it exists.
    //! \param choice The index of child node.
    //! \return First element is the flag indicates whether to create redirect
    //! node. Second element is the edge addon of child node. Third element is
    //! an child node that is redirected or is already existed.
    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreateRedirectNode(int choice);

    //! Returns child node.
    //! \param choice The index of child node.
    //! \return The flag indicates the presence of child node.
    bool HasChild(int choice) const;

    //! Gets the child node.
    //! \param choice The index of child node.
    //! \return First element is the edge addon of child node. Second element is
    //! an child node. If child node doesn't exist, both value are nullptr.
    std::pair<const EdgeAddon*, TreeNode*> Get(int choice) const;

    //! Runs \p functor on each child node (const).
    //! \param functor A function to run for each child node.
    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mapMutex);

        for (const auto& kv : m_map)
        {
            if (!functor(kv.first, &kv.second.edgeAddon, kv.second.node.get()))
            {
                return;
            }
        }
    }

    //! Runs \p functor on each child node (non-const).
    //! \param functor A function to run for each child node.
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
    //! Creates an new child node or returns a child node if it exists.
    //! \param choice The index of child node.
    //! \param createChildFunctor A function to run when new node creates.
    //! \return First element is the flag indicates whether to create new node.
    //! Second element is the edge addon of child node. Third element is an
    //! child node that is newly created or is already existed.
    template <class CreateFunctor>
    std::tuple<bool, EdgeAddon*, TreeNode*> GetOrCreate(
        int choice, CreateFunctor&& createChildFunctor);

    //!
    //! \brief ChildType struct.
    //!
    //! This struct contains self node and addon that checks consistency,
    //! records leading node and so on.
    //!
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
//! This struct contains children and addon that checks consistency,
//! records leading node and so on.
//!
struct TreeNode
{
    ChildNodeMap children;
    TreeNodeAddon addon;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_NODE_HPP