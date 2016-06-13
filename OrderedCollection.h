#ifndef ORDERED_COLLECTON_H
#define ORDERED_COLLECTON_H
#include "BoxInfo.h"
#include <map>

template <class T>
class OrderedCollection {
public:
    OrderedCollection();
    T *find(Count count);
    void add(T *data);
    void add(Count count, T *data);
    ~OrderedCollection();
private:
    void clear();
    Count counter;
    std::map<Count, T *> root;
};

template <class T>
OrderedCollection<T>::OrderedCollection()
{
    counter = null;
}

template <class T>
T *OrderedCollection<T>::find(Count count)
{
    return root[count];
}

template <class T>
void OrderedCollection<T>::add(T *member)
{
    root[++counter] = member;
}

template <class T>
void OrderedCollection<T>::add(Count count, T *member)
{
    root[count] = member;
}

template <class T>
void OrderedCollection<T>::clear()
{
    std::map<Count, T *>::iterator iterator = root.begin();

    while (iterator != root.end())
    {
        delete iterator->second;
        ++iterator;
    }

    root.clear();
}

template <class T>
OrderedCollection<T>::~OrderedCollection()
{
    clear();
}

#endif