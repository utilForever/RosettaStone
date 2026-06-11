// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PRIORITY_QUEUE_HPP
#define ROSETTASTONE_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <cstddef>
#include <stdexcept>

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
    //! Constructor.
    PriorityQueue() : m_head(new Node())
    {
        // Do nothing
    }

    //! Destructor.
    ~PriorityQueue()
    {
        Clear();
        delete m_head;
    }

    //! Copy constructor.
    PriorityQueue(const PriorityQueue& rhs) : m_count(rhs.m_count)
    {
        const Node* rhsNode = rhs.m_head;
        Node* curNode = nullptr;

        if (rhsNode)
        {
            m_head = new Node(rhsNode->value, rhsNode->priority);
            curNode = m_head;

            rhsNode = rhsNode->next;
        }

        while (rhsNode)
        {
            Node* newNode = new Node(rhsNode->value, rhsNode->priority);
            curNode->next = newNode;

            curNode = curNode->next;
            rhsNode = rhsNode->next;
        }
    }

    //! Move constructor.
    PriorityQueue(PriorityQueue&& rhs) noexcept : PriorityQueue()
    {
        std::swap(m_head, rhs.m_head);
        std::swap(m_count, rhs.m_count);
    }

    //! Copy assignment operator.
    PriorityQueue& operator=(const PriorityQueue& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        PriorityQueue<T> temp(rhs);
        std::swap(temp.m_head, m_head);
        std::swap(temp.m_count, m_count);
        return *this;
    }

    //! Move assignment operator.
    PriorityQueue& operator=(PriorityQueue&& rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }

        PriorityQueue<T> temp;
        std::swap(temp.m_head, rhs.m_head);
        std::swap(temp.m_count, rhs.m_count);
        std::swap(m_head, temp.m_head);
        std::swap(m_count, temp.m_count);
        return *this;
    }

    //! Gets the count of the elements.
    //! \return The count of the elements.
    std::size_t GetCount() const
    {
        return m_count;
    }

    //! Inserts element and sorts the underlying container.
    //! \param value The value of the element to push.
    //! \param priority The priority of the element to push.
    void Push(T value, int priority)
    {
        Node* node = m_head;

        while (node->next)
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

    //! Removes the top element from the priority queue.
    //! \return The top element that is removed.
    T Pop()
    {
        if (IsEmpty())
        {
            throw std::out_of_range("Cannot pop from an empty priority queue");
        }

        Node* node = m_head->next;
        m_head->next = node->next;
        m_count--;

        T value = node->value;
        delete node;

        return value;
    }

    //! Checks if the value of the element exists.
    //! \param value The value of the element to check.
    //! \return true if the the value of the element exists, false otherwise.
    bool IsExist(T value)
    {
        Node* node = m_head->next;

        while (node)
        {
            if (node->value == value)
            {
                return true;
            }

            node = node->next;
        }

        return false;
    }

    //! Checks if the underlying container has no elements.
    //! \return true if the underlying container is empty, false otherwise.
    bool IsEmpty() const
    {
        return m_count == 0;
    }

 private:
    //!
    //! \brief Node struct.
    //!
    //! This struct stores the value and the priority of the element.
    //! Also, it contains a pointer that points to the next element.
    //!
    struct Node
    {
        //! Default constructor.
        Node() = default;

        //! Constructs node with given \p _value and \p _priority.
        //! \param _value The value of the element.
        //! \param _priority The priority of the element.
        Node(T _value, int _priority) : value(_value), priority(_priority)
        {
            // Do nothing
        }

        T value = T();
        int priority = 0;

        Node* next = nullptr;
    };

    //!
    //! \brief Clears the priority queue.
    //!
    //! This function deletes all the nodes in the priority queue and resets the
    //! count to 0.
    //!
    void Clear()
    {
        if (!m_head)
        {
            return;
        }

        Node* node = m_head->next;
        while (node)
        {
            Node* next = node->next;
            delete node;
            node = next;
        }

        m_head->next = nullptr;
        m_count = 0;
    }

    Node* m_head = nullptr;
    std::size_t m_count = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PRIORITY_QUEUE_HPP
