#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <iostream>

template <class T, class Comparator = std::less<typename T>> class PriorityQueue
{
public:

    PriorityQueue() : _storage() {}

    void push(const T& newElement)
    {
        _storage.push_back(newElement);
        int index = _storage.size() - 1;
        Comparator comparator;
        while (comparator(_storage[index], _storage[(index - 1) / 2]))
        {
            T t = _storage[index];
            _storage[index] = _storage[(index - 1) / 2];
            _storage[(index - 1) / 2] = t;
            index = (index - 1) / 2;
        }
    }

    T pop()
    {
        T temp = _storage.front();
        _storage.erase(_storage.begin());
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

    std::vector<T> _storage;

};

#endif 
