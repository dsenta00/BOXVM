#ifndef HEAP_H
#define HEAP_H

#include "BoxInfo.h"
#include "OrderedCollection.h"
#include "MemoryHandler.h"
#include "BoxTrace.h"

class Heap : public OrderedCollection <Data>, public MemoryHandler {
public:
    void addPointer(Type);
    void allocateMemory(Data *, Size);
    void freeMemory(Data *);
};

void Heap::addPointer(Type type)
{
    TRACE("HEAP", "addPointer(%d)", type);

    add(new Data(type));
}

void Heap::freeMemory(Data *data)
{
    TRACE("HEAP", "freeMemory(Data {address: %0x%X, type: %u, size: %d})",
        data->getAddress(), data->getType(), data->getSize());

    this->free(data->getAddress());
    data->setAddress(null);
    data->setSize(null);
}

void Heap::allocateMemory(Data *data, Size size)
{
    TRACE("HEAP", "allocate(Data {address: %0x%X, type: %u, size: %d}, size %d)",
        data->getAddress(), data->getType(), data->getSize(), size);

    data->setAddress(this->allocate(DATA_TYPES_SIZE[data->getType()] * size));
    data->setSize(size);
}

#endif
