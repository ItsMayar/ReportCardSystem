#pragma once

#include "LinkedList.h"

template <class StackItem>
class Queue
{
private:
    LinkedList<StackItem> list;

public:
    Queue();
    ~Queue();

    bool is_empty();
    bool enqueue(const StackItem);
    bool dequeue(StackItem&);
    bool get_front(StackItem&);
    bool get_back(StackItem&);
    int get_size();
};

template <class StackItem>
Queue<StackItem>::Queue() {}

template <class StackItem>
Queue<StackItem>::~Queue()
{
    list.clear();
}


template <class StackItem>
bool Queue<StackItem>::is_empty()
{
    return list.is_empty();
}

template <class StackItem>
bool Queue<StackItem>::enqueue(const StackItem newItem)
{
    return list.push_back(newItem);
}

template <class StackItem>
bool Queue<StackItem>::dequeue(StackItem& item)
{
    return list.pop_front(item);
}

template <class StackItem>
bool Queue<StackItem>::get_front(StackItem& item)
{
    return list.peek_front(item);
}

template <class StackItem>
bool Queue<StackItem>::get_back(StackItem& item)
{
    return list.peek_back(item);
}

template <class StackItem>
int Queue<StackItem>::get_size()
{
    return list.get_size();
}
