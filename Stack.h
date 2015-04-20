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
    void SetMonitor(ProgramMonitor *);
    void PushStack(Type, Adress);				//	--	Push data on stack
    void SetVirtualMemory(Size);				//	--	Set stack limit size
    Adress GetAdress(Count);					//	--	Get adress of data by ID
    Type GetType(Count);                        //	--	Get type of data by ID
protected:
    VirtualStackMemory vsm;
};

Stack::Stack()
{
    root = NULL;
    last = NULL;
    monitor = NULL;
    counter = 0;
}

void Stack::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void Stack::PushStack(Type _type, Adress _value)
{
    Data *dataS = NULL;
	Adress startadr = vsm.GetNext();

	if (startadr)
	{
        dataS = new Data(startadr, _type);

		if (dataS)
		{
            SETERR(dataS->SetValue(_value));

            if (EOK)
			{
				root = Push(dataS);
				vsm.SetNext(dataS->GetEndAdress());
			}
			else
            {
                SETERR(STACK_SET_ERR);
            }
		}
		else
        {
            SETERR(STACK_MALL_ERR);
        }
	}
	else
    {
        SETERR(STATIC_OVERFLOW);
    }
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
    {
        SETERR(UKNOWN_TYPE_ERR);
        return 0;
    }
	else
		return search_data->GetType();
}

void Stack::SetVirtualMemory(Size _limit)
{
    vsm.Initialize(_limit, monitor);
}

#endif
