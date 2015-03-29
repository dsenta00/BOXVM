#ifndef STACK_H
#define STACK_H

#include "BoxInfo.h"
#include "StaticData.h"
#include "StaticDataNode.h"
#include "DataTree.h"
#include "VirtualStackMemory.h"

class Stack : public Tree
{
	StaticDataNode *root;
    StaticDataNode *last;
    VirtualStackMemory vsm;

    inline StaticData *SearchFor(Count);        //	--	Returns adress value of data by ID
    StaticDataNode *Push(StaticData *);         //	--	Pushing element on AVL tree /Adelson-Velskii & Landis/
public:
	Stack();
    ~Stack();

    Status PushStack(Type, Adress);				//	--	Push data on stack
    Status SetVirtualMemory(Size);				//	--	Set stack limit size
    Adress GetAdress(Count);					//	--	Get adress of data by ID
    Type GetType(Count);						//	--	Get type of data by ID
};

inline StaticData *Stack::SearchFor(Count _count)
{
	StaticDataNode *curr = root;

    while (curr)
	{
		if (curr->GetCount() > _count)
			curr = curr->Left;
		else if (curr->GetCount() < _count)
			curr = curr->Right;
		else
			break;
	}

    if (curr)
		return curr->GetDataInfo();
	else
		return NULL;
}

StaticDataNode *Stack::Push(StaticData *_newelement)
{
	static int counter = 0;
	StaticDataNode *q = new StaticDataNode(_newelement, ++counter);

    if (q)
	{
        if (!root)
		{
			root = q;
			last = root;
		}
		else
		{
			last->Right = q;
			last = q;
			root = Balance(root);
		}
	}
	return root;
}

Stack::Stack()
{
	root = NULL;
    last = NULL;
    status = EVERYTHING_OK;
}

Status Stack::PushStack(Type _type, Adress _value)
{
    StaticData *dataS = NULL;
    Adress startadr = vsm.GetNext();

    if (startadr)
	{
        dataS = new StaticData(startadr, _type);

        if (dataS)
		{
            status = dataS->SetValue(_value);

			if (status == 0)
            {
                root = Push(dataS);
                vsm.SetNext(dataS->GetEndAdress());
			}
			else
				status = STACK_SET_ERR;
		}
		else
			status = STACK_MALL_ERR;
	}
	else
		status = STATIC_OVERFLOW;

	return status;
}

Adress Stack::GetAdress(Count _count)
{
    StaticData *search_data = SearchFor(_count);

    if (!search_data)
		return NULL;
	else
		return search_data->GetStartAdress();
}

Type Stack::GetType(Count _count)
{
    StaticData *search_data = SearchFor(_count);

    if (!search_data)
		return UKNOWN_TYPE_ERR;
	else
		return search_data->GetType();
}

Status Stack::SetVirtualMemory(Size _limit)
{
    return vsm.Initialize(_limit);
}

Stack::~Stack()
{
    last = root = DeleteTree(root);
}

#endif
