#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class MemoryPool {
public:
	MemoryPool();
    MemoryPool(Size, ProgramMonitor *);
    ~MemoryPool();
    void ExpandSize(Size, DSize &);
    void Free(Address, Size);
    Address Malloc(Size, DSize &);
protected:
    Address vmp;         //  --  Virtual memory pool
    Address resaddr;     //  --  Next adress to reserve
    Size size;          //  --  Memory pool size
    ProgramMonitor *monitor;
};

MemoryPool::MemoryPool()
{
    vmp = null;
    resaddr = null;
    monitor = null;
    size = 0;
}

MemoryPool::MemoryPool(Size _size, ProgramMonitor *_monitor)
{
    monitor = _monitor;

	if (_size > 0)
	{
		size = _size + EXTRASPACE;
        vmp = resaddr = (Address)calloc(size, 1);

        if (!vmp)
        {
            SETERR(POOL_RESERVE_ERR);
        }
	}
	else
    {
        SETERR(POOL_SIZE_ERR);
	}
}

void MemoryPool::ExpandSize(Size _size, DSize &change)
{
    Address newvmp = null;
    size += _size + EXTRASPACE;

    newvmp = (Address)realloc(vmp, size);

    if (newvmp)
	{
        if (newvmp != vmp)
        {
            change = (DSize)(vmp - newvmp);
        }

        vmp = newvmp;
	}
	else
    {
        SETERR(POOL_RESERVE_ERR);
    }
}

Address MemoryPool::Malloc(Size _size, DSize &change)
{
    Address retAdress = null;
	Size diff = (Size)(resaddr + _size - vmp - size);

	if (diff > 0)
    {
        ExpandSize(diff, change);
    }

    if (EOK)
	{
		retAdress = resaddr;
		resaddr += _size;
	}

	return retAdress;
}

void MemoryPool::Free(Address _addr, Size _size)
{
    Address nextaddr = _addr + _size;
	Size nextsize = (Size)(resaddr - nextaddr);

	if (_addr)
	{
		memcpy(_addr, nextaddr, nextsize);
		resaddr = _addr + nextsize;
		memset(resaddr, 0, (int)(vmp + size - resaddr));
	}
	else
    {
        SETERR(FREE_OPER_ERR);
    }
}

MemoryPool::~MemoryPool()
{
	if (vmp)
    {
		free(vmp);
	}
}

#endif
