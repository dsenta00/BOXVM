#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "MemoryCollector.h"

class MemoryHandler {
public:
    Address allocate(Size size);
    void free(Address addr);
private:
    Size toLevelSize(Size size);

    MemoryCollector activeMemory;
    MemoryCollector nonActiveMemory;
};

Address MemoryHandler::allocate(Size size)
{
    Size levelSize = toLevelSize(size);
    Address addr = nonActiveMemory.remove(levelSize);

    if (NULL == addr)
    {
        addr = (Address)calloc(memorySize[levelSize], 1);
    }

    if (NULL == addr)
    {
        SETERR(POOL_RESERVE_ERR);
        return null;
    }

    activeMemory.add(addr, levelSize);
    return addr;
}

void MemoryHandler::free(Address addr)
{
    Size levelSize;

    if (NULL == addr)
    {
        return;
    }

    levelSize = activeMemory.remove(addr);

    if (levelSize != SIZE_LEVELS + 1)
    {
        nonActiveMemory.add(addr, levelSize);
    }
}

Size MemoryHandler::toLevelSize(Size size)
{
    for (Size i = 0; i < SIZE_LEVELS; i++)
    {
        if (size < memorySize[i])
        {
            return i;
        }
    }

    SETERR(MEM_ALOC_ERROR);
    return 0;
}

#endif