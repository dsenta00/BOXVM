#ifndef HEAP_H
#define HEAP_H

#include "BoxInfo.h"
#include "MemoryPool.h"
#include "DataNode.h"
#include "DataTree.h"
#include "Registry.h"

class Heap : public DataTree {
public:
    Heap();
    Heap(Size, ProgramMonitor *);
    ~Heap();

    void Lea(Registry &, Type *, Count, Count, Count); //	--	Sets in register [base by id][count][register]
    void PushPointer(Type);                       //	--	Push new data type in tree
    void Malloc(Count, Size);                     //	--	Dynamic allocation of data by id of N elements
    void MallocDefrag(Count, Size);
    void Free(Count);
private:
    void SetNewAddresses(DataNode *, DSize &);
    void SetNewAddresses(DataNode *, Address, Size);  //  --  Sets new addresses in Data tree.
    void ReserveMemory(Data *, Size);
protected:
    MemoryPool *memoryPool;
};

Heap::Heap(Size _poolsize, ProgramMonitor *_monitor)
{
    root = null;
    last = null;
    monitor = _monitor;
    memoryPool = new MemoryPool(_poolsize, monitor);

    if (!memoryPool)
        SETERR(POOL_MAL_ERR);
}

void Heap::SetNewAddresses(DataNode *element, Address _address, Size _size)
{
    Address curradr = null;

	if (element)
	{
        curradr = element->GetDataInfo()->GetAddress();

        SetNewAddresses(element->Left, _address, _size);

        if (_address < curradr)
            element->GetDataInfo()->SetAddress(curradr - _size);

        SetNewAddresses(element->Right, _address, _size);
	}
}

void Heap::SetNewAddresses(DataNode *element, DSize &change)
{
    Address curradr = null;

    if (element)
    {
        curradr = element->GetDataInfo()->GetAddress();
        SetNewAddresses(element->Left, change);
        element->GetDataInfo()->SetAddress(curradr + change);
        SetNewAddresses(element->Right, change);
    }
}

Heap::Heap()
{
    root = null;
    last = null;
    monitor = null;
    memoryPool = null;
}

void Heap::Lea(Registry &opqueue, Type *_type, Count _count, Count _position, Count _regnum)
{
    Data *dat = SearchFor(_count);

    if (dat)
    {
        *_type = dat->GetType();

        if (EOK)
        {
            if(_position)
                opqueue.SetRegistry(dat, _regnum, _position);
            else
                opqueue.SetRegistry(dat, _regnum);
        }
        else
        {
            SETERR(BUFF_NULL_ERR);
        }
    }
    else
    {
        SETERR(HEAP_UNEX_ERR);
    }
}

void Heap::PushPointer(Type _type)
{
    Data *ptr = new Data(_type);

	if (ptr)
		root = Push(ptr);
	else
        SETERR(HEAP_SET_ERR);
}

void Heap::Free(Count _count)
{
    Data *del = null;
    Address address = null;
	Size size = 0;

	del = SearchFor(_count);

	if (del)
	{
        address = del->GetAddress();
		size = del->GetSize();

		switch (del->GetType())
		{
            case _INT: case _FLOAT:
                size *= 4;
            break;
            case _SHORT:
                size *= 2;
            break;
            case _LONG: case _DOUBLE:
                size *= 3;
            break;
		}

        memoryPool->Free(address, size);
        SetNewAddresses(root, address, size);

        del->SetAddress(null);
		del->SetSize(0);
	}
	else
    {
        SETERR(FREE_OPER_ERR);
    }
}

void Heap::ReserveMemory(Data *_mal, Size _size)
{
    Address address = null;
    DSize change = 0;

	if (_mal)
	{
		switch (_mal->GetType())
		{
            case _INT: case _FLOAT:
                address = memoryPool->Malloc(_size * 4, change);
            break;
            case _SHORT:
                address = memoryPool->Malloc(_size * 2, change);
            break;
            case _LONG: case _DOUBLE:
                address = memoryPool->Malloc(_size * 8, change);
            break;
            case _CHAR:
                address = memoryPool->Malloc(_size, change);
            break;
		}

        if(change)
            SetNewAddresses(root, change);

        if (address)
        {
            _mal->SetAddress(address);
            _mal->SetSize(_size);
        }
        else
        {
            SETERR(DYN_MALLOC_ERR);
        }
	}
	else
    {
        SETERR(HEAP_MALL_ERR);
    }
}

void Heap::Malloc(Count _count, Size _size)
{
    ReserveMemory(SearchFor(_count), _size);
}

void Heap::MallocDefrag(Count _count, Size _size)
{
    Address address = null;
	Size size = 0;
    DSize change = 0;
    Data *mal = SearchFor(_count);

	if (mal)
	{
		size = mal->GetSize();

		if (size == 0)
        {
            ReserveMemory(mal, _size);
        }
		else
		{
			switch (mal->GetType())
			{
                case _SHORT:
                    size *= 2; _size *= 2;
                break;
                case _INT: case _FLOAT:
                    size *= 4; _size *= 4;
                break;
                case _LONG: case _DOUBLE:
                    size *= 8; _size *= 8;
                break;
                case _CHAR:
                break;
			}

            address = mal->GetAddress();

            if (size == _size)
            {
                memset(address, 0, size);
            }
            else
            {
                memoryPool->Free(address, size);
                address = memoryPool->Malloc(_size, change);

                if(change)
                    SetNewAddresses(root, change);

                if (EOK)
                {
                    mal->SetAddress(address);
                    mal->SetSize(_size);
                }
            }
		}

	}
	else
    {
        SETERR(HEAP_MALL_ERR);
    }
}

Heap::~Heap()
{
    root = DeleteTree(root);

	if (memoryPool)
		delete memoryPool;
}

#endif
