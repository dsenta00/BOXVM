#ifndef STACK_H
#define STACK_H

#include "BoxInfo.h"
#include "Data.h"
#include "DataNode.h"
#include "DataTree.h"
#include "VirtualStackMemory.h"

class Stack : public DataTree {
public:
    Stack();
    Status PushStack(Type, Adress);				//	--	Push data on stack
    Status SetVirtualMemory(Size);				//	--	Set stack limit size
    Adress GetAdress(Count);					//	--	Get adress of data by ID
    Type GetType(Count);                        //	--	Get type of data by ID
protected:
    VirtualStackMemory vsm;
};

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
