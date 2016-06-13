#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H
#include "BoxInfo.h"
#include "BoxTrace.h"
#include "MemorySize.h"
#include <list>

class MemoryCollector {
public:
    void add(Address address, Size sizeLevel);
    Address remove(Size sizeLevel);
    Size remove(Address address);
    ~MemoryCollector();
private:
    std::list<Address> memList[SIZE_LEVELS];
    Size size;
};

MemoryCollector::~MemoryCollector()
{
    TRACE("MEMORY_COLLECTOR", "~MemoryCollector()");

    for (Size i = 0; i < SIZE_LEVELS; i++)
    {
        if (memList[i].size() > 0)
        {
            for (std::list<Address>::iterator it = memList[i].begin();
                it != memList[i].end();
                ++it)
            {
                TRACE("MEMORY_COLLECTOR", "deleting: 0x%X", *it);
                free(*it);
            }

            memList[i].clear();
        }
    }
}

void MemoryCollector::add(Address address, Size sizeLevel)
{
    TRACE("MEMORY_COLLECTOR", "add(address 0x%X, sizeLevel %u)", address, sizeLevel);

    memList[sizeLevel].push_front(address);
    size += memorySize[sizeLevel];
}

Address MemoryCollector::remove(Size sizeLevel)
{
    Address addr = null;

    if (memList[sizeLevel].size() > 0)
    {
        addr = *memList[sizeLevel].begin();
        memList[sizeLevel].pop_front();
        size -= memorySize[sizeLevel];
    }

    TRACE("MEMORY_COLLECTOR", "remove(sizeLevel %u) => 0x%X", sizeLevel, addr);

    return addr;
}

Size MemoryCollector::remove(Address address)
{
    TRACE("MEMORY_COLLECTOR", "remove(address 0x%X)", address);

    for (Size i = 0; i < SIZE_LEVELS; i++)
    {
        for (std::list<Address>::iterator it = memList[i].begin();
            it != memList[i].end();
            ++it)
        {
            if (*it == address)
            {
                memList[i].erase(it);
                return i;
            }
        }
    }

    return SIZE_LEVELS + 1;
}

#endif