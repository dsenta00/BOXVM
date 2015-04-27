#ifndef VIRTUALSTACKMEMORY_H
#define VIRTUALSTACKMEMORY_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class VirtualStackMemory {
public:
    VirtualStackMemory();
    ~VirtualStackMemory();
    inline void Initialize(Size, ProgramMonitor *);
    Adress GetNext();
    void SetNext(Adress);
protected:
    ProgramMonitor *monitor;
    Adress memory;
    Adress nextaddr;
    Size limit;
};

VirtualStackMemory::VirtualStackMemory()
{
    memory = null;
    nextaddr = null;
    limit = null;
}

VirtualStackMemory::~VirtualStackMemory()
{
    if(memory)
    {
        memset(memory, null, limit);
        free(memory);
    }

    memory = nextaddr = null;
    limit = 0;
}

inline void VirtualStackMemory::Initialize(Size _limit, ProgramMonitor *_monitor)
{
    monitor = _monitor;

    if (_limit > 0)
    {
        limit = _limit;
        memory = nextaddr = (Adress)calloc(limit, sizeof(char));

        if (!memory)
        {
            SETERR(VM_MALL_ERR);
        }
    }
    else
    {
        SETERR(ZERO_VM_ERR);
    }
}

Adress VirtualStackMemory::GetNext()
{
    if(nextaddr < memory + limit)
    {
        return nextaddr;
    }
    else
    {
        SETERR(STATIC_OVERFLOW);
        return null;
    }
}

void VirtualStackMemory::SetNext(Adress _nextaddr)
{
    nextaddr = _nextaddr;
}

#endif // VIRTUALSTACKMEMORY_H
