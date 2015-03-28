#ifndef HEAP_H
#define HEAP_H

#include "BoxInfo.h"
#include "MemoryPool.h"
#include "PointerNode.h"
#include "DataTree.h"
#include "OperandQueue.h"

class Heap : public Tree
{
	PointerNode *root;
	PointerNode *last;
	MemoryPool *memoryPool;

    PointerNode *Push(Pointer *);                   //	--	Pushing element in pointer tree
    void SetNewAdresses(PointerNode *, Adress, Size);//  --  Sets new adresses in pointer tree.
    Status ReserveMemory(Pointer *, Size);
public:

	Heap();
    Heap(Size);
	~Heap();

    inline Pointer *SearchFor(Count);                   //	--	Returns pointer by ID
    Status Lea(OperandQueue *, Type *, Count, int);   //	--	Sets in operation queue [base by id][count]
    Status PushPointer(Type);							//	--	Push new data type in tree
    Status Malloc(Count, Size);							//	--	Dynamic allocation of data by id of N elements
    Status MallocDefrag(Count, Size);
    Status Free(Count);
};

Heap::Heap(Size _poolsize)
{
	root = NULL;
	last = NULL;
	status = EVERYTHING_OK;
	memoryPool = new MemoryPool(_poolsize);

	if (memoryPool != NULL)
		status = memoryPool->GetStatus();
	else
		status = POOL_MAL_ERR;
}

inline Pointer *Heap::SearchFor(Count _count)
{
	PointerNode *curr = root;

	while (curr != NULL)
	{
		if (curr->GetCount() > _count)
			curr = curr->Left;
		else if (curr->GetCount() < _count)
			curr = curr->Right;
		else
			break;
	}

	if (curr != NULL)
		return curr->GetPointer();
	else
		return NULL;
}

PointerNode *Heap::Push(Pointer *new_element)
{
    static Count counter = 0;
	PointerNode *q = new PointerNode(new_element, ++counter);

	if (q != NULL)
	{
		if (root == NULL)
			last = root = q;
		else
		{
			last->Right = q;
			last = q;
			root = Balance(root);
		}
	}

	return root;
}

void Heap::SetNewAdresses(PointerNode *element, Adress _adress, Size _size)
{
    Adress curradr = NULL;

	if (element != NULL)
    {
        curradr = element->GetPointer()->GetAdress();

        SetNewAdresses(element->Left, _adress, _size);

		if (_adress < curradr)
            element->GetPointer()->SetAdress(curradr - _size);

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

Status Heap::Lea(OperandQueue *opqueue, Type *_type, Count _count, int _position)
{
	Pointer *dat = NULL;
    Adress starta = NULL;

	if (_count == -1)
		dat = root->GetPointer();
	else
		dat = SearchFor(_count);

	if (dat != NULL)
	{
        starta = dat->GetAdress(_position);
        *_type = dat->GetType();

        if (starta != NULL && *_type != 0)
            status = opqueue->Push(starta, *_type);
		else
            status = BUFF_NULL_ERR;
	}
	else
        status = HEAP_UNEX_ERR;

    return status;
}

Status Heap::PushPointer(Type _type)
{
    Pointer *ptr = new Pointer(_type);

    if (ptr != NULL)
        root = Push(ptr);
	else
        status = HEAP_SET_ERR;

    return status;
}

Status Heap::Free(Count _count)
{
	Pointer *del = NULL;
    Adress adress = NULL;
    Size size = 0;

	del = SearchFor(_count);

	if (del != NULL)
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

Status Heap::ReserveMemory(Pointer *_mal, Size _size)
{
    Adress adress = NULL;

	if (_mal != NULL)
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
            if (adress != NULL)
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
	Pointer *mal = SearchFor(_count);
	return ReserveMemory(mal, _size);
}

Status Heap::MallocDefrag(Count _count, Size _size)
{
    Adress adress = NULL;
    Size size = 0;
    Pointer *mal = SearchFor(_count);

	if (mal != NULL)
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

            if (status == EVERYTHING_OK)
            {
                adress = mal->GetAdress();

                if (size == _size)
                    memset(adress, 0, size);
                else
                {
                    memoryPool->Free(adress, size);
                    adress = memoryPool->Malloc(_size);

                    if (adress != NULL)
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

	if (memoryPool != NULL)
		delete memoryPool;
}

#endif
