#include <stdlib.h>
#include <memory>

#pragma once

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

        Node(): _next(nullptr) {}
        Node(const _T &data): _data(data), _next(nullptr) {}

        T _data;
        Node<_T> *_next;
    };

    std::size_t _size;
    Node<T> *_head;
    Node<T> *_tail;
    _Node_alloc_type _alloc;

public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    template <class _T>
    class LinkedListIterator
    {
        Node<T> *_node;

    public:
        using value_type      = T;
        using pointer         = T*;
        using const_pointer   = const T*;
        using reference       = T&;
        using const_reference = const T&;

        LinkedListIterator(Node<_T> *node) : _node(node) {}
        T & operator++()
        {
            _node = _node->_next;
            return _node->_data;
        }
        T operator++(int)
        {
            auto data = _node->_data;
            _node = _node->_next;
            return data;
        }
        bool operator==(const LinkedListIterator &other) const
        {
            if (this == &other)
                return true;
            return _node == other._node;
        }
        bool operator!=(const LinkedListIterator &other) const { return !operator==(other); }
        T & operator*() { return _node->_data; }
    };

    using iterator       = LinkedListIterator<T>;
    using const_iterator = LinkedListIterator<const T>;

    LinkedList() noexcept
        : _size(0), _head(), _tail(), _alloc() {}

    virtual ~LinkedList()
    {
        while (_head)
            remove();
    }

    void append(const T &value)
    {
        //if (Node<T> *node = _alloc.allocate(1))
        if (auto node = _alloc.allocate(1))
        {
            _alloc.construct(node, value);
            node->_next = nullptr;
            if (_head == nullptr)
            {
                _head = node;
                _tail = node;
            }
            else
            {
                _tail->_next = node;
                _tail = node;
            }
        }
    }

    void remove()
    {
        if (_head)
        {
            auto newHead = _head->_next;
            //Node<T> *newHead = _head->_next;
            _alloc.destroy(_head);
            _alloc.deallocate(_head, 1);
            _head = newHead;
        }
    }

    int size() const { return _size; }
    iterator begin() { return iterator(_head); }
    const_iterator begin() const { return const_iterator(_head); }
    iterator end() { return iterator(_tail->_next); }
    const_iterator end() const { return const_iterator(_tail->_next); }
};

}   // namespace my
