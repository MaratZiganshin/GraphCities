#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <iostream>

template <class T, class Comparator = std::less<typename T>> class PriorityQueue
{
public:

    PriorityQueue() : _storage() {}

    void push(const T& newElement)
    {
        int size = _storage.size();
        int index = 0;
        std::list<T>::const_iterator i;
        Comparator comparator;
        for (i = _storage.begin(); i != _storage.end(); ++i)
            if (comparator(*i,newElement))
                break;
        _storage.insert(i, newElement);
    }

    T pop()
    {
        T temp = _storage.front();
        _storage.pop_front();
        return temp;
    }

    T top()
    {
        return _storage.front();
    }

    size_t size() const
    {
        return _storage.size();
    }

    bool isEmpty() const
    {
        return _storage.empty();
    }

    bool isFull() const
    {
        return false;
    }
private:

    std::list<T> _storage;

};

#endif 
