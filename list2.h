#include <stdlib.h>
#include <memory>

#pragma once

namespace my
{

template <typename T>
struct Node
{
    using value_type = T;
    Node(): _next(nullptr) {}
    Node(const T &data): _data(data), _next(nullptr) {}

    T _data;
    Node *_next;
};

template <typename T, typename Alloc = std::allocator<Node<T>>>
class LinkedList
{
    template <class TNode>
    class LinkedListIterator
    {
        friend class LinkedList<typename TNode::value_type>;

        TNode *_p;

    public:
        LinkedListIterator(TNode *p) : _p(p) {}
        LinkedListIterator & operator++() { _p = _p->_next; return *this; }
        LinkedListIterator operator++(int)
        {
            LinkedListIterator it(*this);
            _p = _p->_next;
            return it;
        }
        bool operator!=(const LinkedListIterator &other) { return _p != other._p; }
        const typename TNode::value_type & operator*() const { return _p->_data; }
    };

    std::size_t _size;
//    std::unique_ptr<Node> _head;
//    std::unique_ptr<Node> _tail;
    Node<T> *_head;
    Node<T> *_tail;
    Alloc alloc;

public:
    using value_type = T;
    using iterator = LinkedListIterator<Node<T>>;
    using const_iterator = LinkedListIterator<const Node<T>>;

    LinkedList()
    {
        _size = 0;
        _head = nullptr;// .reset(new Node);
        _tail = nullptr;//.reset(new Node);
        //_head->_next = _tail.get();
    }

    virtual ~LinkedList()
    {
        while (_size != 0)
        {
            auto tmp = _head;
            _head = _head->_next;
            alloc.deallocate(tmp, size_t(1));
            --_size;
        }
    }

    void append(const T &value)
    {
        auto tmp = new Node<T>(value);

        if (_head == nullptr)
        {
            _head = tmp;
            _tail = tmp;
        }
        else
        {
            _tail->_next = tmp;
            _tail = tmp;
        }

        _size++;
    }

    int size() const { return _size; }
    iterator begin() { return iterator(_head); }
    const_iterator begin() const { return const_iterator(_head); }
    //iterator end() { return iterator(_tail.get()); }
    iterator end() { return iterator(_tail->_next); }
    //const_iterator end() const { return const_iterator(_tail.get()); }
    const_iterator end() const { return const_iterator(_tail->_next); }
};

}
