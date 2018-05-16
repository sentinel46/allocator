#pragma once

#include <cstdlib>
#include <memory>

namespace my
{

template <typename T, typename Alloc = std::allocator<T>>
class LinkedList
{
    template <typename _T>
    struct Node;

public:
    using _Tp_alloc_type     = typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<T>::other;
    using _Tp_alloc_traits   = __gnu_cxx::__alloc_traits<_Tp_alloc_type>;
    using _Node_alloc_type   = typename _Tp_alloc_traits::template rebind<Node<T>>::other;
    using _Node_alloc_traits = __gnu_cxx::__alloc_traits<_Node_alloc_type>;

private:
    template <typename _T>
    struct Node
    {
        using value_type = _T;

        Node(): m_next{nullptr} {}
        Node(const _T &data): m_data{data}, m_next{nullptr} {}

        T m_data;
        std::shared_ptr<Node<_T>> m_next;
    };

    std::size_t m_size;
    std::shared_ptr<Node<T>> m_head;
    std::shared_ptr<Node<T>> m_tail;
    _Node_alloc_type m_alloc;

public:
    using value_type      = T;
    using pointer         = T *;
    using const_pointer   = const T *;
    using reference       = T &;
    using const_reference = const T &;

    template <class _T>
    class LinkedListIterator
    {
    public:
        using iterator_tag    = std::forward_iterator_tag;
        using value_type      = T;
        using pointer         = T *;
        using const_pointer   = const T *;
        using reference       = T &;
        using const_reference = const T &;

        LinkedListIterator(std::shared_ptr<Node<_T>> node) : m_node{node} {}

        T & operator++()
        {
            m_node = m_node->m_next;
            return m_node->m_data;
        }
        T operator++(int)
        {
            auto data = m_node->m_data;
            m_node = m_node->m_next;
            return data;
        }
        bool operator==(const LinkedListIterator &other) const
        {
            if (this == &other)
                return true;
            return m_node == other.m_node;
        }
        bool operator!=(const LinkedListIterator &other) const { return !operator==(other); }
        T & operator*() { return m_node->m_data; }

    private:
        std::shared_ptr<Node<T>> m_node;
    };

    using iterator       = LinkedListIterator<T>;
    using const_iterator = LinkedListIterator<const T>;

    LinkedList() noexcept
        : m_size{0}, m_head{}, m_tail{}, m_alloc{} {}
/*
    virtual ~LinkedList()
    {
        while (m_head)
            pop_front();
    }
*/
    void push_back(const T &value)
    {
        if (auto node = std::allocate_shared<Node<T>, _Node_alloc_type>(m_alloc, value)) {
            node->m_next = nullptr;
            if (m_head == nullptr) {
                m_head = node;
                m_tail = node;
            } else {
                m_tail->m_next = node;
                m_tail = node;
            }
            ++m_size;
        }
    }

    void pop_front()
    {
        if (m_head) {
            auto newHead = m_head->m_next;
//            m_alloc.destroy(m_head);
//            m_alloc.deallocate(m_head, 1);
            m_head = newHead;
        }
    }

    int size() const { return m_size; }
    iterator begin() { return iterator(m_head); }
    const_iterator begin() const { return const_iterator(m_head); }
    iterator end() { return iterator(m_tail->m_next); }
    const_iterator end() const { return const_iterator(m_tail->m_next); }
};

}   // namespace my
