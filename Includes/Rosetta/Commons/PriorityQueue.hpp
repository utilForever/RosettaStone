// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PRIOIRTY_QUEUE_HPP
#define ROSETTASTONE_PRIOIRTY_QUEUE_HPP

#include <cstddef>

namespace RosettaStone
{
//!
//! \brief PriorityQueue class.
//!
//! This class is a custom priority queue implementation for convenience.
//!
template <typename T>
class PriorityQueue
{
 public:
    PriorityQueue() : m_head(new Node())
    {
        // Do nothing
    }

    void Push(T value, int priority)
    {
        Node* node = m_head;

        while (node->next != nullptr)
        {
            if (node->next->priority <= priority)
            {
                node = node->next;
            }
            else
            {
                break;
            }
        }

        Node* temp = node->next;
        Node* newNode = new Node(value, priority);
        node->next = newNode;
        newNode->next = temp;

        m_count++;
    }

    T Pop()
    {
        Node* node = m_head->next;
        m_head->next = node->next;
        m_count--;

        return node->value;
    }

    bool IsEmpty() const
    {
        return m_count == 0;
    }

 private:
    struct Node
    {
        Node() = default;

        Node(T _value, int _priority) : value(_value), priority(_priority)
        {
            // Do nothing
        }

        T value = T();
        int priority = 0;

        Node* next = nullptr;
    };

    Node* m_head = nullptr;
    std::size_t m_count = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PRIOIRTY_QUEUE_HPP
