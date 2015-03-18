#ifndef VIRTUALSTACKMEMORY_H
#define VIRTUALSTACKMEMORY_H
#include "BoxInfo.h"

class VirtualStackMemory
{
    Adress memory;
    Adress nextaddr;
    Size limit;
public:
    VirtualStackMemory();
    ~VirtualStackMemory();

    inline Status Initialize(Size);
    Adress GetNext();
    void SetNext(Adress);
};

VirtualStackMemory::VirtualStackMemory()
{
    memory = NULL;
    nextaddr = NULL;
    limit = 0;
}

VirtualStackMemory::~VirtualStackMemory()
{
    if(memory != NULL)
    {
        memset(memory, 0, limit);
        free(memory);
    }

    memory = nextaddr = NULL;
    limit = 0;
}

inline Status VirtualStackMemory::Initialize(Size _limit)
{
    if (_limit > 0)
    {
        limit = _limit;
        memory = nextaddr = (Adress)calloc(limit, sizeof(char));

        if (memory == NULL)
            return VM_MALL_ERR;
    }
    else
        return ZERO_VM_ERR;

    return EVERYTHING_OK;
}

Adress VirtualStackMemory::GetNext()
{
    if(nextaddr < memory + limit)
        return nextaddr;
    else
        return NULL;
}

void VirtualStackMemory::SetNext(Adress _nextaddr)
{
    nextaddr = _nextaddr;
}

#endif // VIRTUALSTACKMEMORY_H
