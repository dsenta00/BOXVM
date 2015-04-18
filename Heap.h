#ifndef HEAP_H
#define HEAP_H

#include "BoxInfo.h"
#include "MemoryPool.h"
#include "DataNode.h"
#include "DataTree.h"
#include "OperandQueue.h"

class Heap : public DataTree {
public:
    Heap();
    Heap(Size);
    ~Heap();

    Status Lea(OperandQueue *, Type *, Count, Count); //	--	Sets in operation queue [base by id][count]
    Status LeaReg(OperandQueue *, Type *, Count, Count, Count); //	--	Sets in register [base by id][count][register]
    Status PushPointer(Type);                       //	--	Push new data type in tree
    Status Malloc(Count, Size);                     //	--	Dynamic allocation of data by id of N elements
    Status MallocDefrag(Count, Size);
    Status Free(Count);
private:
    void SetNewAdresses(DataNode *, Adress, Size);  //  --  Sets new adresses in Data tree.
    Status ReserveMemory(Data *, Size);
protected:
    MemoryPool *memoryPool;
};

Heap::Heap(Size _poolsize)
{
	root = NULL;
	last = NULL;
	status = EVERYTHING_OK;
	memoryPool = new MemoryPool(_poolsize);

	if (memoryPool)
		status = memoryPool->GetStatus();
	else
		status = POOL_MAL_ERR;
}

void Heap::SetNewAdresses(DataNode *element, Adress _adress, Size _size)
{
	Adress curradr = NULL;

	if (element)
	{
        curradr = element->GetDataInfo()->GetAdress();

		SetNewAdresses(element->Left, _adress, _size);

		if (_adress < curradr)
            element->GetDataInfo()->SetAdress(curradr - _size);

		SetNewAdresses(element->Right, _adress, _size);
	}
}

Heap::Heap()
{
	root = NULL;
	last = NULL;
	status = EVERYTHING_OK;
	memoryPool = NULL;
}

Status Heap::Lea(OperandQueue *opqueue, Type *_type, Count _count, Count _position)
{
    Data *dat = NULL;

	if (_count == -1)
        dat = root->GetDataInfo();
	else
		dat = SearchFor(_count);

	if (dat)
    {
		*_type = dat->GetType();

        if (*_type)
        {
            if(_position)
                status = opqueue->Push(dat, _position);
            else
                status = opqueue->Push(dat);
        }
		else
            status = BUFF_NULL_ERR;
	}
	else
		status = HEAP_UNEX_ERR;

	return status;
}

Status Heap::LeaReg(OperandQueue *opqueue, Type *_type, Count _count, Count _position, Count _regnum)
{
    Data *dat = NULL;

    if (_count == -1)
        dat = root->GetDataInfo();
    else
        dat = SearchFor(_count);

    if (dat)
    {
        *_type = dat->GetType();

        if (*_type)
        {
            if(_position)
                status = opqueue->SetRegistry(dat, _regnum, _position);
            else
                status = opqueue->Push(dat, _regnum);
        }
        else
            status = BUFF_NULL_ERR;
    }
    else
        status = HEAP_UNEX_ERR;

    return status;
}

Status Heap::PushPointer(Type _type)
{
    Data *ptr = new Data(_type);

	if (ptr)
		root = Push(ptr);
	else
		status = HEAP_SET_ERR;

	return status;
}

Status Heap::Free(Count _count)
{
    Data *del = NULL;
	Adress adress = NULL;
	Size size = 0;

	del = SearchFor(_count);

	if (del)
	{
		adress = del->GetAdress();
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

		status = memoryPool->Free(adress, size);
		SetNewAdresses(root, adress, size);

		del->SetAdress(NULL);
		del->SetSize(0);
	}
	else
		status = FREE_OPER_ERR;

	return status;
}

Status Heap::ReserveMemory(Data *_mal, Size _size)
{
	Adress adress = NULL;

	if (_mal)
	{
		switch (_mal->GetType())
		{
            case _INT: case _FLOAT:
                adress = memoryPool->Malloc(_size * 4);
            break;
            case _SHORT:
                adress = memoryPool->Malloc(_size * 2);
            break;
            case _LONG: case _DOUBLE:
                adress = memoryPool->Malloc(_size * 8);
            break;
            case _CHAR:
                adress = memoryPool->Malloc(_size);
            break;
            default:
                status = DYN_TYPE_ERR;
            break;
		}

		if (status != DYN_TYPE_ERR)
		{
			if (adress)
			{
				_mal->SetAdress(adress);
				_mal->SetSize(_size);
			}
			else
				status = DYN_MALLOC_ERR;
		}
	}
	else
		status = HEAP_MALL_ERR;

	return status;
}

Status Heap::Malloc(Count _count, Size _size)
{
    Data *mal = SearchFor(_count);
	return ReserveMemory(mal, _size);
}

Status Heap::MallocDefrag(Count _count, Size _size)
{
	Adress adress = NULL;
	Size size = 0;
    Data *mal = SearchFor(_count);

	if (mal)
	{
		size = mal->GetSize();

		if (size == 0)
			status = ReserveMemory(mal, _size);
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
                default:
                    status = DYN_TYPE_ERR;
                break;
			}

			if (!status)
			{
				adress = mal->GetAdress();

				if (size == _size)
					memset(adress, 0, size);
				else
				{
					memoryPool->Free(adress, size);
					adress = memoryPool->Malloc(_size);

					if (adress)
					{
						mal->SetAdress(adress);
						mal->SetSize(_size);
					}
					else
						status = DYN_MALLOC_ERR;
				}
			}
		}

	}
	else
		status = HEAP_MALL_ERR;

	return status;
}

Heap::~Heap()
{
    root = DeleteTree(root);

	if (memoryPool)
		delete memoryPool;
}

#endif
