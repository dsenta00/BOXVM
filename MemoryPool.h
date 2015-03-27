#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include "BoxInfo.h"

class MemoryPool
{
    Adress vmp;         //  --  Virtual memory pool
    Adress resaddr;     //  --  Next adress to reserve
    Size size;          //  --  Memory pool size
    Status status;
public:
	MemoryPool();
    MemoryPool(Size);
    ~MemoryPool();

    Status GetStatus();
    Status ExpandSize(Size);
    Status Free(Adress, Size);
    Adress Malloc(Size);
};

MemoryPool::MemoryPool()
{
    vmp = NULL;
    resaddr = NULL;
	size = 0;
	status = EVERYTHING_OK;
}

MemoryPool::MemoryPool(Size _size)
{
	if (_size > 0)
	{
		size = _size + EXTRASPACE;
        vmp = resaddr = (Adress)calloc(size, 1);

        if (vmp != NULL)
			status = EVERYTHING_OK;
		else
			status = POOL_RESERVE_ERR;
	}
    else
    {
        vmp = NULL;
        resaddr = NULL;
        size = 0;
		status = POOL_SIZE_ERR;
    }
}

Status MemoryPool::GetStatus()
{
	return status;
}

Status MemoryPool::ExpandSize(Size _size)
{
    Adress newVM = NULL;
	size += _size + EXTRASPACE;

    newVM = (Adress)realloc(vmp, size);

	if (newVM != NULL)
	{
        if (newVM != vmp)
            free(vmp);

        vmp = newVM;
	}
	else
		status = POOL_RESERVE_ERR;

	return status;
}

Adress MemoryPool::Malloc(Size _size)
{
    Adress retAdress = NULL;
    Size diff = (Size)(resaddr + _size - vmp - size);

	if (diff > 0)
        status = ExpandSize(diff);

	if (status == EVERYTHING_OK)
	{
        retAdress = resaddr;
        resaddr += _size;
	}

	return retAdress;
}

Status MemoryPool::Free(Adress _addr, Size _size)
{
    Adress nextaddr = _addr + _size;
    Size nextsize = (Size)(resaddr - nextaddr);

    if (_addr != NULL)
    {
        memcpy(_addr, nextaddr, nextsize);
        resaddr = _addr + nextsize;
        memset(resaddr, 0, (int)(vmp + size - resaddr));
	}
	else
		status = FREE_OPER_ERR;

	return status;
}

MemoryPool::~MemoryPool()
{
    if (vmp != NULL)
	{
        memset(vmp, 0, size);
        free(vmp);
	}
}

#endif
