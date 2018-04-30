#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>

namespace my
{

template <class T, class Alloc = std::allocator<T>>
class Node
{
public:
    using value_type = T;

private:
    friend class List<T, Alloc>;

    Node(): _next(nullptr) {}
    Node(const T &data): _data(data), _next(nullptr) {}

private:
    T _data;
    Node<T, Alloc> *_next;
};

template <class TNode>
class ListIterator
{
public:
    ListIterator(TNode *p): _p(p) {}
    ListIterator(const ListIterator &other): _p(other.p) {}
//    ListIterator & operator=(ListIterator other) { std::swap}
    ListIterator & operator++()
    {
        _p = _p->next;
        return *this;
    }
    ListIterator & operator++(int)
    {
        ListIterator it(*this);
        _p = _p->next;
        return it;
    }
    bool operator==(const ListIterator &other) { return _p == other._p; }
    bool operator!=(const ListIterator &other) { return _p != other._p; }
    const TNode::value_type & operator*() const { return p->data; }
    ListIterator<TNode> operator+(int i)
    {
        ListIterator<TNode> iter = *this;
        while (i-- > 0 && iter.p)
            ++iter;
        return iter;
    }

private:
//    friend class List<typename TNode::value_type>;

    TNode *_p;
};

template <class T, class Alloc = std::allocator<T>> class List
{
public:
    using node = Node<T, Alloc>;
    using iterator = ListIterator<node>;
    using const_iterator = ListIterator<const node>;

    List() { init(); }
    List(const List &other)
    {
        init();
        const_iterator i = other.begin();
        while (i != other.begin())
        {
            add(*i);
            ++i;
        }
        _head.reset(other._head.get());
        _tail.reset(other._tail.get());
    }

    virtual ~List()
    {
        while (_head->_next != _tail.get())
            remove(begin());
    }

    void add(const T &value)
    {
        node *first = new node(value);
        first->next = _head->next;
        _head->next = first;
    }

    void remove(iterator &removeIter)
    {
        node *last = _head.get();
        iterator i = begin();

        while (i != removeIter)
        {
            last = i.p;
            ++i;
        }

        if (i != end())
        {
            last->next = i.p->next;
            --size;
            delete i.p;
        }
    }

    int size() const { return _size; }
    iterator begin() { return iterator(_head->_next); }
    const_iterator begin() const { return const_iterator(_head->_next); }
    iterator end() { return iterator(_tail.get()); }
    const_iterator end() const { return iterator(_tail.get()); }

private:
    void init()
    {
        _size = 0;
        _head.reset(new node);
        _tail.reset(new node);
        _head->_next = _tail.get();
    }

private:
    std::size_t _size;
    std::unique_ptr<node> _head;
    std::unique_ptr<node> _tail;
};

}

