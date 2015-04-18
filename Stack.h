#ifndef STACK_H
#define STACK_H

#include "BoxInfo.h"
#include "Data.h"
#include "DataNode.h"
#include "DataTree.h"
#include "VirtualStackMemory.h"

<<<<<<< HEAD
class Stack : public DataTree {
=======
class Stack : public Tree
{
	StaticDataNode *root;
	StaticDataNode *last;
	VirtualStackMemory vsm;
    int counter;

	inline StaticData *SearchFor(Count);        //	--	Returns adress value of data by ID
	StaticDataNode *Push(StaticData *);         //	--	Pushing element on AVL tree /Adelson-Velskii & Landis/
>>>>>>> dc573c73fbc89a1fd726f4bd7e6faffc7f3b1af8
public:
    Stack();
    Status PushStack(Type, Adress);				//	--	Push data on stack
    Status SetVirtualMemory(Size);				//	--	Set stack limit size
    Adress GetAdress(Count);					//	--	Get adress of data by ID
    Type GetType(Count);                        //	--	Get type of data by ID
protected:
    VirtualStackMemory vsm;
};

<<<<<<< HEAD
=======
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

>>>>>>> dc573c73fbc89a1fd726f4bd7e6faffc7f3b1af8
Stack::Stack()
{
	root = NULL;
	last = NULL;
    counter = 0;
	status = EVERYTHING_OK;
    counter = 0;
}

Status Stack::PushStack(Type _type, Adress _value)
{
    Data *dataS = NULL;
	Adress startadr = vsm.GetNext();

	if (startadr)
	{
        dataS = new Data(startadr, _type);

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
    Data *search_data = SearchFor(_count);

	if (!search_data)
		return NULL;
	else
        return search_data->GetAdress();
}

Type Stack::GetType(Count _count)
{
    Data *search_data = SearchFor(_count);

	if (!search_data)
		return UKNOWN_TYPE_ERR;
	else
		return search_data->GetType();
}

Status Stack::SetVirtualMemory(Size _limit)
{
	return vsm.Initialize(_limit);
}

#endif
