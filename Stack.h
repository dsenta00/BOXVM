#ifndef STACK_H
#define STACK_H

#include "BoxInfo.h"
#include "Data.h"
#include "OrderedCollection.h"
#include "MemoryHandler.h"
#include "BoxTrace.h"

class Stack : public OrderedCollection <Data>, public MemoryHandler {
public:
    void addData(Type, Address);
};

void Stack::addData(Type type, Address value)
{
    Data *data;
    Size size;

    TRACE("STACK", "addData(type %u, value 0x%X)", type, value);

    if (type == BOX_STRING)
        size = strlen(value);
    else
        size = DATA_TYPES_SIZE[type];

    data = new Data(type);

    data->setSize(size);
    data->setAddress(this->allocate(size));
    data->setVal(value);

    add(data);
}

#endif
